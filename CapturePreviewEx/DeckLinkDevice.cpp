#ifdef WIN32
#include <atlstr.h>
#include <atlconv.h>
#endif // WIN32

#include "DeckLinkDevice.h"
#include <loom_shell.h>
#include <loom_shell_util.h>
#include <comutil.h>
#include "CapturePreviewExWindow.h"

//extern vx_status createOpenCLContext(const char * platform, const char * device, cl_context * opencl_context);
//extern vx_status createBuffer(cl_context opencl_context, vx_uint32 size, cl_mem * mem);
//extern int64_t GetClockCounter();
//extern int64_t GetClockCounter();
//extern int64_t GetClockFrequency();
//extern cl_command_queue GetCmdqCached(cl_mem mem);
//extern vx_status loadBuffer(cl_mem mem, const char * fileName);
//extern vx_status saveBuffer(cl_mem mem, const char * fileName);
//extern vx_status saveBufferToImage(cl_mem mem, const char * fileName, vx_df_image buffer_format, vx_uint32 buffer_width, vx_uint32 buffer_height, vx_uint32 stride_in_bytes);
//extern vx_status setGlobalAttribute(vx_uint32 offset, float value);

int Error(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	if (format[strlen(format) - 1] != '\n') printf("\n");
	fflush(stdout);
	return -1;
}

void Message(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	fflush(stdout);
}

DeckLinkDevice::DeckLinkDevice(CapturePreviewExWindow* uiDelegate, IDeckLink* device)
: m_uiDelegate(uiDelegate)
, m_deckLink(device)
, m_deckLinkInput(nullptr)
, m_yuvFrame(nullptr)
, m_outputCard(nullptr)
, m_supportsFormatDetection(false)
, m_refCount(1)
, m_currentlyCapturing(false)
, m_applyDetectedInputMode(false)
{
	m_deckLink->AddRef();
}

int DeckLinkDevice::releaseAllResources()
{
	num_context_ = DEFAULT_LS_CONTEXT_COUNT;
	num_openvx_context_ = DEFAULT_VX_CONTEXT_COUNT;
	num_opencl_context_ = DEFAULT_CL_CONTEXT_COUNT;
	num_opencl_buf_ = DEFAULT_CL_BUFFER_COUNT;
	if (opencl_buf_mem_) {
		for (vx_uint32 i = 0; i < num_opencl_context_; i++) {
			if (opencl_buf_mem_[i]) {
				cl_int status = clReleaseMemObject(opencl_buf_mem_[i]);

				opencl_buf_mem_[i] = nullptr;

			}
		}
	}
	if (context_) {
		for (vx_uint32 i = 0; i < num_context_; i++) {
			if (context_[i]) {
				vx_status status = lsReleaseContext(&context_[i]);

			}
		}
	}
	if (openvx_context_ && openvx_context_allocated_) {
		for (vx_uint32 i = 0; i < num_openvx_context_; i++) {
			if (openvx_context_[i]) {
				if (openvx_context_allocated_[i]) {
					vx_status status = vxReleaseContext(&openvx_context_[i]);

				}
				else {
					openvx_context_[i] = nullptr;
				}
			}
		}
	}
	if (opencl_context_ && opencl_context_allocated_) {
		for (vx_uint32 i = 0; i < num_opencl_context_; i++) {
			if (opencl_context_[i]) {
				if (opencl_context_allocated_[i]) {
					cl_int status = clReleaseContext(opencl_context_[i]);

				}
				opencl_context_[i] = nullptr;
			}
		}
	}


	delete context_;
	delete openvx_context_;
	delete opencl_context_;
	delete openvx_context_allocated_;
	delete opencl_context_allocated_;
	delete opencl_buf_mem_;

	return 0;
}

bool DeckLinkDevice::initStitching()
{
	// initialize
	decl_ls_disabled = false;
	decl_vx_disabled = false;
	decl_cl_disabled = false;
	decl_buf_disabled = false;
	num_context_ = DEFAULT_LS_CONTEXT_COUNT;
	num_openvx_context_ = DEFAULT_VX_CONTEXT_COUNT;
	num_opencl_context_ = DEFAULT_CL_CONTEXT_COUNT;
	num_opencl_buf_ = DEFAULT_CL_BUFFER_COUNT;
	// set log callback
	//lsGlobalSetLogCallback(stitch_log_callback);
	// name of contexts
	strcpy(name_ls, "ls");
	strcpy(name_vx, "vx");
	strcpy(name_cl, "cl");
	strcpy(name_buf, "buf");
	// create array for contexts, cmd_queues, and buffers
	context_ = new ls_context[num_context_]();
	openvx_context_ = new vx_context[num_openvx_context_]();
	opencl_context_ = new cl_context[num_opencl_context_]();
	openvx_context_allocated_ = new bool[num_openvx_context_]();
	opencl_context_allocated_ = new bool[num_opencl_context_]();
	opencl_buf_mem_ = new cl_mem[num_opencl_buf_]();
	// misc
	memset(attr_buf_, 0, sizeof(attr_buf_));
	//memset(des_buffer, 0, 1920 * 1080 * 2);
	//memset(fbuffer, 0, 3840 * 1920 * 2);

	//LIVE_STITCH_API_ENTRY vx_status VX_API_CALL lsGlobalSetAttributes(vx_uint32 attr_offset, vx_uint32 attr_count, const vx_float32 * attr_ptr)
	//1 setGlobalAttribute(0,2); // process the command

	vx_uint32 attr_offset = 0;
	float value = 2.000f;
	if (setGlobalAttribute(attr_offset, value) != VX_SUCCESS)
		return false;

	//2 cl_context clc;	//name_cl = "clc" // process the command
	strcpy(name_cl, "clc");
	num_opencl_context_ = 1;
	Message("..cl_context %s[%d] created\n", name_cl, num_opencl_context_);

	//3 createOpenCLContext("Advanced Micro Devices, Inc.", "0", &clc);
	char platform[64], device[64];
	vx_uint32 clIndex = 0;
	strcpy(platform, "Advanced Micro Devices, Inc.");


	strcpy(device, "0");
	cl_int cl_status = createOpenCLContext(platform, device, &opencl_context_[clIndex]);
	if (cl_status)
		return cl_status;
	opencl_context_allocated_[clIndex] = true;

	//4 cl_mem buf[2];// process the command
	num_opencl_buf_ = 2;
	strcpy(name_buf, "buf");
	Message("..cl_mem %s[%d] created\n", name_buf, num_opencl_buf_);

	//5 createBuffer(clc, 6220800, &buf[0]);
	clIndex = 0;
	vx_uint32 bufIndex = 0, bufSize = 4147200; //1920 * 1080 * 2
	strcpy(name_cl, "clc");
	clIndex = 0;
	if (clIndex >= num_opencl_context_) return Error("ERROR: OpenCL context out-of-range: expects: 0..%d", num_opencl_context_ - 1);
	if (!opencl_context_[clIndex]) return Error("ERROR: OpenCL context %s[%d] doesn't exist", name_cl, clIndex);
	if (bufIndex >= num_opencl_buf_) return Error("ERROR: OpenCL buffer out-of-range: expects: 0..%d", num_opencl_buf_ - 1);
	if (opencl_buf_mem_[bufIndex]) return Error("ERROR: OpenCL buffer %s[%d] already exists", name_buf, bufIndex);
	cl_status = createBuffer(opencl_context_[clIndex], bufSize, &opencl_buf_mem_[bufIndex]);
	if (cl_status)
		return cl_status;
	//6 createBuffer(clc, 22118400, &buf[1]); 
	clIndex = 0;
	bufSize = 14745600; //14745600,&buf[1]);// 3840*1920*2
	bufIndex = 1;
	if (clIndex >= num_opencl_context_) return Error("ERROR: OpenCL context out-of-range: expects: 0..%d", num_opencl_context_ - 1);
	if (!opencl_context_[clIndex]) return Error("ERROR: OpenCL context %s[%d] doesn't exist", name_cl, clIndex);
	if (bufIndex >= num_opencl_buf_) return Error("ERROR: OpenCL buffer out-of-range: expects: 0..%d", num_opencl_buf_ - 1);
	if (opencl_buf_mem_[bufIndex]) return Error("ERROR: OpenCL buffer %s[%d] already exists", name_buf, bufIndex);
	cl_status = createBuffer(opencl_context_[clIndex], bufSize, &opencl_buf_mem_[bufIndex]);
	if (cl_status)
		return cl_status;

	// 7 ls_context lsc;
	strcpy(name_ls, "lsc");
	num_context_ = 1;
	//8 lsc = lsCreateContext();
	// process the command
	vx_uint32 contextIndex = 0;
	num_context_ = 1;
	if (contextIndex >= num_context_) return Error("ERROR: context out-of-range: expects: 0..%d", num_context_ - 1);
	if (context_[contextIndex]) return Error("ERROR: context %s[%d] already exists", name_ls, contextIndex);
	context_[contextIndex] = lsCreateContext();
	if (!context_[contextIndex]) return Error("ERROR: lsCreateContext() failed");
	Message("..lsCreateContext: created context %s[%d]\n", name_ls, contextIndex);

	//9 lsSetOpenCLContext(lsc, clc);
	contextIndex = 0;
	clIndex = 0;
	//ParseContextWithErrorCheck(s, contextIndex, invalidSyntax));
	if (contextIndex >= num_context_)
		return false;

	if (!context_[contextIndex])
		return false;
	//process the command
	vx_status vx_status = lsSetOpenCLContext(context_[contextIndex], opencl_context_[clIndex]);
	if (vx_status) return Error("ERROR: lsSetOpenCLContext(%s[%d],%s[%d]) failed (%d)", name_ls, contextIndex, name_cl, clIndex, vx_status);
	Message("..lsSetOpenCLContext: set OpenCL context %s[%d] for %s[%d]\n", name_cl, clIndex, name_ls, contextIndex);

	//10 lsSetCameraConfig(lsc, 1, 2, RGB2, 1920, 1080);
	vx_uint32  camera_rows = 0, camera_cols = 0, buffer_width = 0, buffer_height = 0;
	vx_df_image buffer_format = VX_DF_IMAGE_UYVY; //   VX_DF_IMAGE_UYVY  VX_DF_IMAGE_YUYV VX_DF_IMAGE_RGB
	//ParseContextWithErrorCheck
	if (contextIndex >= num_context_) {

		return false;
	}
	if (!context_[contextIndex]) {

		return false;
	}
	contextIndex = 0;
	camera_rows = 1;
	camera_cols = 2;
	//buffer_format = 0x32424752;
	buffer_width = 1920;
	buffer_height = 1080;
	//process the command
	vx_status = lsSetCameraConfig(context_[contextIndex], camera_rows, camera_cols, buffer_format, buffer_width, buffer_height);
	if (vx_status) return Error("ERROR: lsSetCameraConfig(%s[%d],*) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsSetCameraConfig: successful for %s[%d]\n", name_ls, contextIndex);

	//11 lsSetOutputConfig(lsc, RGB2, 3840, 1920);// process the command
	contextIndex = 0;
	//ParseContextWithErrorCheck(s, contextIndex, invalidSyntax));
	if (contextIndex >= num_context_)
		return false;
	if (!context_[contextIndex])
		return false;
	buffer_format = VX_DF_IMAGE_UYVY; //VX_DF_IMAGE_UYVY VX_DF_IMAGE_RGB
	buffer_width = 3840;
	buffer_height = 1920;
	vx_status = lsSetOutputConfig(context_[contextIndex],
		buffer_format, buffer_width, buffer_height);
	if (vx_status) return Error("ERROR: lsSetOutputConfig(%s[%d],*) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsSetOutputConfig: successful for %s[%d]\n", name_ls, contextIndex);

	//12 lsSetCameraBufferStride(lsc, 2880);
	vx_uint32 buffer_stride_in_bytes = 3840;// 2880; //
	contextIndex = 0;
	vx_status = lsSetCameraBufferStride(context_[contextIndex], buffer_stride_in_bytes);
	if (vx_status) return Error("ERROR: lsSetCameraBufferStride(%s[%d],*) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsSetCameraBufferStride: successful for %s[%d]\n", name_ls, contextIndex);


	//13 lsSetOutputBufferStride(lsc, 11520);
	// process the command
	contextIndex = 0;
	buffer_stride_in_bytes = 7680; //3840*2
	vx_status = lsSetOutputBufferStride(context_[contextIndex], buffer_stride_in_bytes);
	if (vx_status) return Error("ERROR: lsSetOutputBufferStride(%s[%d],*) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsSetOutputBufferStride: successful for %s[%d]\n", name_ls, contextIndex);

	//14 rig_params rig_par = { 0,0,0,0 };	// process the command

	char parName[64];
	rig_params rig_par = { 0 };
	rig_par.yaw = 0.0f;
	rig_par.pitch = 0.0f;
	rig_par.roll = 0.0f;
	rig_par.d = 0.0f;
	strcpy(parName, "rig_par");
	if (rigParList.find(parName) != rigParList.end()) return Error("ERROR: rig_params %s already exists", parName);

	rigParList[parName] = rig_par;
	Message("..rig_params %s declared\n", parName);

	//15 lsSetRigParams(lsc, &rig_par);
	contextIndex = 0;
	vx_status = lsSetRigParams(context_[contextIndex], &rig_par);
	if (vx_status) return Error("ERROR: lsSetRigParams(%s[%d],*) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsSetRigParams: successful for %s[%d]\n", name_ls, contextIndex);

	//16 camera_params cam_par0 = { { 0,0,90,0,0,0 },{ 180,842.2,421.1,0,-60,ptgui_lens_fisheye_circ,-0.190745733,0.189054235,0.998701352 } };
	char   lensType[64];
	camera_params camera_par = { 0 };
	strcpy(parName, "cam_par0");
	camera_par.focal.yaw = 0.0f;
	camera_par.focal.pitch = 0.0f;
	camera_par.focal.roll = 90.0f;
	camera_par.focal.tx = 0.0f;
	camera_par.focal.ty = 0.0f;
	camera_par.focal.tz = 0.0f;

	camera_par.lens.hfov = 180.0f;
	camera_par.lens.haw = 842.2;
	camera_par.lens.r_crop = 421.1;
	camera_par.lens.du0 = 0.0f;
	camera_par.lens.dv0 = -60.0f;
	camera_par.lens.lens_type = ptgui_lens_fisheye_circ;

	//strcpy(lensType, "ptgui_lens_fisheye_circ");

	camera_par.lens.k1 = -0.190745733;
	camera_par.lens.k2 = 0.189054235;
	camera_par.lens.k3 = 0.998701352;
	if (camParList.find(parName) != camParList.end()) return Error("ERROR: camera_params %s already exists", parName);
	// process the command
	camParList[parName] = camera_par;



	//17 lsSetCameraParams(lsc, 0, &cam_par0);
	bool isCamera = true;
	vx_uint32  index = 0;
	memcpy(&camera_par, &camParList[parName], sizeof(camera_par));
	vx_status = lsSetCameraParams(context_[contextIndex], index, &camera_par);
	if (vx_status) return Error("ERROR: lsSetCameraParams(%s[%d],%d,*) failed (%d)", name_ls, contextIndex, index, vx_status);
	Message("..lsSetCameraParams: successful for %s[%d] and camera#%d\n", name_ls, contextIndex, index);

	//18 camera_params cam_par1 = { { 180,0,-90,0,0,0 },{ 180,842.2,421.1,0,-60,ptgui_lens_fisheye_circ,-0.190745733,0.189054235,0.998701352 } };
	strcpy(parName, "cam_par1");
	camera_par.focal.yaw = 180.0f;
	camera_par.focal.pitch = 0.0f;
	camera_par.focal.roll = -90.0f;
	camera_par.focal.tx = 0.0f;
	camera_par.focal.ty = 0.0f;
	camera_par.focal.tz = 0.0f;

	camera_par.lens.hfov = 180.0f;
	camera_par.lens.haw = 842.2;
	camera_par.lens.r_crop = 421.1;
	camera_par.lens.du0 = 0.0f;
	camera_par.lens.dv0 = -60.0f;


	camera_par.lens.lens_type = ptgui_lens_fisheye_circ;

	camera_par.lens.k1 = -0.190745733;
	camera_par.lens.k2 = 0.189054235;
	camera_par.lens.k3 = 0.998701352;
	if (camParList.find(parName) != camParList.end()) return Error("ERROR: camera_params %s already exists", parName);
	camParList[parName] = camera_par;
	Message("..camera_params %s declared\n", parName);
	//19 lsSetCameraParams(lsc, 1, &cam_par1);
	isCamera = true;
	index = 1;

	memcpy(&camera_par, &camParList[parName], sizeof(camera_par));
	vx_status = lsSetCameraParams(context_[contextIndex], index, &camera_par);
	if (vx_status) return Error("ERROR: lsSetCameraParams(%s[%d],%d,*) failed (%d)", name_ls, contextIndex, index, vx_status);
	Message("..lsSetCameraParams: successful for %s[%d] and camera#%d\n", name_ls, contextIndex, index);

	//20 lsInitialize(lsc);
	contextIndex = 0;
	double clk2msec = 1000.0 / GetClockFrequency();
	int64_t clk = GetClockCounter();
	vx_status = lsInitialize(context_[contextIndex]);
	double msec = clk2msec * (GetClockCounter() - clk);
	if (vx_status) return Error("ERROR: lsInitialize(%s[%d]) failed (%d)", name_ls, contextIndex, vx_status);
	Message("..lsInitialize: successful for %s[%d] (%7.3lf ms)\n", name_ls, contextIndex, msec);


	//22 lsSetCameraBuffer(lsc, &buf[0]);

	contextIndex = 0;	bufIndex = 0;
	vx_status = lsSetCameraBuffer(context_[contextIndex], &opencl_buf_mem_[bufIndex]);

	//23 lsSetOutputBuffer(lsc, &buf[1]);
	contextIndex = 0, bufIndex = 1;
	vx_status = lsSetOutputBuffer(context_[contextIndex], &opencl_buf_mem_[bufIndex]);


	m_outputCard->CreateVideoFrame(3840, 2160, 7680, bmdFormat8BitYUV, 0, &m_yuvFrame);

	m_yuvFrame->GetBytes(&frameBytesDest);
	memset(frameBytesDest, 0, 3840 * 2160 * 2);

	return true;
}

DeckLinkDevice::~DeckLinkDevice()
{
	releaseAllResources();

	if (m_yuvFrame != nullptr)
	{
		m_yuvFrame->Release();
		m_yuvFrame = nullptr;
	}
	
	if (frameBytesDest)
		frameBytesDest = nullptr;

	if (m_outputCard != nullptr)
	{
		m_outputCard->Release();
		m_outputCard = nullptr;
	}

	if (m_deckLinkInput != nullptr)
	{
		m_deckLinkInput->Release();
		m_deckLinkInput = nullptr;
	}

	while (!m_modeList.empty())
	{
		m_modeList.back()->Release();
		m_modeList.pop_back();
	}

	if (m_deckLink != nullptr)
	{
		m_deckLink->Release();
		m_deckLink = nullptr;
	}
}

bool DeckLinkDevice::Init()
{
	IDeckLinkAttributes*            deckLinkAttributes = NULL;
	IDeckLinkDisplayModeIterator*   displayModeIterator = NULL;
	IDeckLinkDisplayMode*           displayMode = NULL;
	//BSTR							deviceNameBSTR = NULL;

	// Get input interface
	if (m_deckLink->QueryInterface(IID_IDeckLinkInput, (void**)&m_deckLinkInput) != S_OK)
		return false;


	// Check if input mode detection is supported.
	if (m_deckLink->QueryInterface(IID_IDeckLinkAttributes, (void**)&deckLinkAttributes) == S_OK)
	{
		if (deckLinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &m_supportsFormatDetection) != S_OK)
			m_supportsFormatDetection = false;

		deckLinkAttributes->Release();
	}

	// Retrieve and cache mode list
	if (m_deckLinkInput->GetDisplayModeIterator(&displayModeIterator) == S_OK)
	{
		while (displayModeIterator->Next(&displayMode) == S_OK)
			m_modeList.push_back(displayMode);

		displayModeIterator->Release();
	}

#if WIN32
	// Get device name
	BSTR deviceNameBSTR = NULL;
	if (m_deckLink->GetDisplayName(&deviceNameBSTR) == S_OK)
	{
		m_deviceName = std::string(_com_util::ConvertBSTRToString(deviceNameBSTR));
		::SysFreeString(deviceNameBSTR);
	}
	else
	{
		m_deviceName = std::string("DeckLink");
	}
#elif __APPLE_CC__
#elif defined(__linux__)
#endif

	//
	if (m_deckLink->QueryInterface(IID_IDeckLinkOutput, (void**)&m_outputCard) != S_OK)
	{
		m_deckLinkInput->Release();
		return false;
	}
	// initialize default counts
	bool btemp = initStitching();
	if (!btemp)
		return false;
	return true;
}

void DeckLinkDevice::GetDisplayModeNames(std::vector<std::string>& modeNames)
{
	unsigned int	modeIndex;

#if WIN32
	BSTR			modeNameBstr;
	for (modeIndex = 0; modeIndex < m_modeList.size(); modeIndex++)
	{
		if (m_modeList[modeIndex]->GetName(&modeNameBstr) == S_OK)
		{
			std::string	modeName = std::string(_com_util::ConvertBSTRToString(modeNameBstr));
			modeNames.push_back(modeName);
			SysFreeString(modeNameBstr);
		}
		else
		{
			modeNames.push_back(std::string("Unknown mode"));
		}
	}
#elif __APPLE_CC__
#elif defined(__linux__)
#endif

}

bool DeckLinkDevice::StartCapture(int videoModeIndex, IDeckLinkScreenPreviewCallback* screenPreviewCallback, bool applyDetectedInputMode)
{
	BMDVideoInputFlags		videoInputFlags = bmdVideoInputFlagDefault;

	m_applyDetectedInputMode = applyDetectedInputMode;

	// Enable input video mode detection if the device supports it
	if (m_supportsFormatDetection == TRUE)
		videoInputFlags |= bmdVideoInputEnableFormatDetection;

	// Get the IDeckLinkDisplayMode from the given index
	if ((videoModeIndex < 0) || (videoModeIndex >= m_modeList.size()))
	{
		m_uiDelegate->ShowErrorMessage(("An invalid display mode was selected."), ("Error starting the capture"));
		return false;
	}

	// Set capture callback
	m_deckLinkInput->SetCallback(this);
	// Set the screen preview
	m_deckLinkInput->SetScreenPreviewCallback(screenPreviewCallback);

	//videoInputFlags |= bmdVideoInputDualStream3D;

	// Set the video input mode
	if (m_deckLinkInput->EnableVideoInput(m_modeList[videoModeIndex]->GetDisplayMode(), bmdFormat8BitYUV, videoInputFlags) != S_OK)
	{
		BMDDisplayMode a;
		a = m_modeList[videoModeIndex]->GetDisplayMode();
		m_uiDelegate->ShowErrorMessage(("This application was unable to select the chosen video mode. Perhaps, the selected device is currently in-use."), ("Error starting the capture"));
		return false;
	}

	//kevin begin

	// Turn on video output
	//HRESULT		 theResult = m_pOutputCard->EnableVideoOutput(m_modeList[videoModeIndex]->GetDisplayMode(), bmdVideoOutputFlagDefault);//displayMode keypoint
	//BMDDisplayMode bmode = m_modeList[videoModeIndex]->GetDisplayMode();
	HRESULT		 theResult = m_outputCard->EnableVideoOutput(bmdMode4K2160p30, bmdVideoOutputFlagDefault);//displayMode keypoint
	//BMDDisplayMode bmode = m_modeList[videoModeIndex]->GetDisplayMode();

	if (theResult != S_OK)
		//TRACE("EnableVideoOutput failed with result 0x%08x\n", theResult); Jimmy
	//  virtual HRESULT STDMETHODCALLTYPE StartScheduledPlayback( BMDTimeValue playbackStartTime, BMDTimeScale timeScale, double playbackSpeed) = 0;	

	theResult = m_outputCard->StartScheduledPlayback(0, 24000, 1.0);

	if (theResult != S_OK)
		//TRACE("StartScheduledPlayback failed with result 0x%08x\n", theResult); //Jimmy
	//kevin end
	//	IDeckLinkMutableVideoFrame *m_yuvFrame;
	//	HRESULT res = m_pOutputCard->CreateVideoFrame(3840, 2160, 7680, bmdFormat8BitYUV, 0, &m_yuvFrame);//bmdFormat8BitBGRA bmdFormat8BitYUV


	// Start the capture
	if (m_deckLinkInput->StartStreams() != S_OK)
	{
		m_uiDelegate->ShowErrorMessage(("This application was unable to start the capture. Perhaps, the selected device is currently in-use."), ("Error starting the capture"));
		return false;
	}

	m_currentlyCapturing = true;

	return true;
}

void DeckLinkDevice::StopCapture()
{
	if (m_deckLinkInput != nullptr)
	{
		// Stop the capture
		m_deckLinkInput->StopStreams();

		//
		m_deckLinkInput->SetScreenPreviewCallback(nullptr);

		// Delete capture callback
		m_deckLinkInput->SetCallback(nullptr);
	}

	m_outputCard->StopScheduledPlayback(0, nullptr, 24000);
	m_outputCard->DisableVideoOutput();

	m_currentlyCapturing = false;
}

//platform relative: Jimmy Hua
#if WIN32
HRESULT STDMETHODCALLTYPE DeckLinkDevice::VideoInputFormatChanged(/* in */ BMDVideoInputFormatChangedEvents notificationEvents, /* in */ IDeckLinkDisplayMode *newDisplayMode, /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags)
{
	unsigned int	modeIndex = 0;

	// Restart capture with the new video mode if told to
	if (!m_applyDetectedInputMode)
		goto bail;

	// Stop the capture
	m_deckLinkInput->StopStreams();

	// Set the video input mode
	if (m_deckLinkInput->EnableVideoInput(newDisplayMode->GetDisplayMode(), bmdFormat8BitYUV, bmdVideoInputEnableFormatDetection) != S_OK)
	{
		// Let the UI know we couldnt restart the capture with the detected input mode
		emit m_uiDelegate->ErrorRestartingCaptureMessage();
		goto bail;
	}

	// Start the capture
	if (m_deckLinkInput->StartStreams() != S_OK)
	{
		// Let the UI know we couldnt restart the capture with the detected input mode
		emit m_uiDelegate->ErrorRestartingCaptureMessage();
		goto bail;
	}

	// Find the index of the new mode in the mode list so we can update the UI
	while (modeIndex < m_modeList.size()) 
	{
		if (m_modeList[modeIndex]->GetDisplayMode() == newDisplayMode->GetDisplayMode())
		{
			emit m_uiDelegate->SelectVideoModeMessage(modeIndex);
			break;
		}
		modeIndex++;
	}

bail:
	return S_OK;
}

HRESULT STDMETHODCALLTYPE DeckLinkDevice::VideoInputFrameArrived(/* in */ IDeckLinkVideoInputFrame* videoFrame, /* in */ IDeckLinkAudioInputPacket* audioPacket)
{
	//Jimmy
	AncillaryDataStruct		ancillaryData;

	if (videoFrame == nullptr)
		return S_OK;

	// Get the various timecodes and userbits attached to this frame
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeVITC, ancillaryData.vitcF1Timecode, ancillaryData.vitcF1UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeVITCField2, ancillaryData.vitcF2Timecode, ancillaryData.vitcF2UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188VITC1, ancillaryData.rp188vitc1Timecode, ancillaryData.rp188vitc1UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188LTC, ancillaryData.rp188ltcTimecode, ancillaryData.rp188ltcUserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188VITC2, ancillaryData.rp188vitc2Timecode, ancillaryData.rp188vitc2UserBits);

	m_uiDelegate->UpdateAncillaryData(ancillaryData);

	// Update the UI
	emit m_uiDelegate->RefreshInputStreamDataMessage(videoFrame->GetFlags() & bmdFrameHasNoInputSource);

	void * inputBytes;
	long textureSize;
	HRESULT 	r;
	cl_command_queue cmdq;
	vx_uint32	contextIndex;
	vx_status vx_status;
	BMDTimeValue	frameTime, frameDuration;

	if (!(videoFrame->GetFlags() & bmdFrameHasNoInputSource))
	{
		inputBytes = nullptr;
		textureSize = videoFrame->GetRowBytes() * videoFrame->GetHeight();
		r = videoFrame->GetBytes(&inputBytes);
		//bufIndex = 0;
		cmdq = GetCmdqCached(opencl_buf_mem_[0]);
		if (!cmdq)
			return -1;

		clEnqueueWriteBuffer(cmdq, opencl_buf_mem_[0], CL_TRUE, 0, textureSize, inputBytes, NULL, NULL, NULL);
		clFlush(cmdq);

		//contextIndex = 0;
		vx_status = lsScheduleFrame(context_[0]);
		//25 lsWaitForCompletion(lsc);	// process the command
		//contextIndex = 0;
		vx_status = lsWaitForCompletion(context_[0]);  //6-9ms

		//bufIndex = 1;
		//int npixelnum = 3840 * 1920;
		//IDeckLinkMutableVideoFrame *m_yuvFrame = NULL;
		//HRESULT res = m_pOutputCard->CreateVideoFrame(3840, 2160, 7680, bmdFormat8BitYUV, 0, &m_yuvFrame);//bmdFormat8BitBGRA bmdFormat8BitYUV
		//void *frameBytesDest;
		//m_yuvFrame->GetBytes(&frameBytesDest);
		//memset(frameBytesDest, 0, 3840 * 2160 * 2);
		clEnqueueReadBuffer(cmdq, opencl_buf_mem_[1], CL_TRUE, 0, 14745600, frameBytesDest, 0, NULL, NULL); // 5-6ms 14745600  22118400
		clFlush(cmdq);

		videoFrame->GetStreamTime(&frameTime, &frameDuration, 100);
		r = m_outputCard->ScheduleVideoFrame(m_yuvFrame, frameTime, frameDuration, 24000);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE DeckLinkDevice::QueryInterface(REFIID iid, LPVOID *ppv)
{
	HRESULT			result = E_NOINTERFACE;

	if (ppv == NULL)
		return E_INVALIDARG;

	// Initialise the return result
	*ppv = NULL;

	// Obtain the IUnknown interface and compare it the provided REFIID
	if (iid == IID_IUnknown)
	{
		*ppv = this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkInputCallback)
	{
		*ppv = (IDeckLinkInputCallback*)this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkNotificationCallback)
	{
		*ppv = (IDeckLinkNotificationCallback*)this;
		AddRef();
		result = S_OK;
	}

	return result;
}

ULONG STDMETHODCALLTYPE DeckLinkDevice::AddRef()
{
	return InterlockedIncrement((LONG*)&m_refCount);
}

ULONG STDMETHODCALLTYPE DeckLinkDevice::Release()
{
	int		newRefValue;

	newRefValue = InterlockedDecrement((LONG*)&m_refCount);
	if (newRefValue == 0)
	{
		delete this;
		return 0;
	}

	return newRefValue;
}
#elif __APPLE_CC__
#elif defined(__linux__) 
#error "Unsupported platform"
#endif

void DeckLinkDevice::GetAncillaryDataFromFrame(IDeckLinkVideoInputFrame* videoFrame, BMDTimecodeFormat timecodeFormat, std::string& timecodeString, std::string& userBitsString)
{
#if WIN32
	IDeckLinkTimecode*		timecode = NULL;
	BSTR					timecodeBstr;
	BMDTimecodeUserBits		userBits = 0;

	

	if ((videoFrame != NULL) && (videoFrame->GetTimecode(timecodeFormat, &timecode) == S_OK))
	{
		if (timecode->GetString(&timecodeBstr) == S_OK)
		{
			timecodeString = std::string(_com_util::ConvertBSTRToString(timecodeBstr));
			SysFreeString(timecodeBstr);
		}
		else
		{
			timecodeString = std::string("");
		}

		timecode->GetTimecodeUserBits(&userBits);

		CString userBitsCString;
		USES_CONVERSION;
		userBitsCString.Format(_T("0x%08X"), userBits);
		userBitsString = std::string(T2A(userBitsCString.GetBuffer()));
		userBitsCString.ReleaseBuffer();

		timecode->Release();
	}
	else
	{
		timecodeString = std::string("");
		userBitsString = std::string("");
	}
#elif __APPLE_CC__
#elif defined(__linux__) 
#error "Unsupported platform"
#endif
}

DeckLinkDeviceDiscovery::DeckLinkDeviceDiscovery(CapturePreviewExWindow* uiDelegate)
: m_uiDelegate(uiDelegate)
, m_deckLinkDiscovery(nullptr)
, m_refCount(1)
{
	if (CoCreateInstance(CLSID_CDeckLinkDiscovery, NULL, CLSCTX_ALL, IID_IDeckLinkDiscovery, (void**)&m_deckLinkDiscovery) != S_OK)
		m_deckLinkDiscovery = nullptr;
}

DeckLinkDeviceDiscovery::~DeckLinkDeviceDiscovery()
{
	if (m_deckLinkDiscovery != nullptr)
	{
		// Uninstall device arrival notifications and release discovery object
		m_deckLinkDiscovery->UninstallDeviceNotifications();
		m_deckLinkDiscovery->Release();
		m_deckLinkDiscovery = nullptr;
	}
}

bool DeckLinkDeviceDiscovery::Enable()
{
	HRESULT     result = E_FAIL;

	// Install device arrival notifications
	if (m_deckLinkDiscovery != NULL)
		result = m_deckLinkDiscovery->InstallDeviceNotifications(this);

	return result == S_OK;
}

void DeckLinkDeviceDiscovery::Disable()
{
	if (m_deckLinkDiscovery != NULL)
		m_deckLinkDiscovery->UninstallDeviceNotifications();
}

//platform relative: Jimmy Hua
#if WIN32
HRESULT	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::DeckLinkDeviceArrived(/* in */ IDeckLink* deckLink)
{
	deckLink->AddRef();
	// Update UI (add new device to menu) from main thread
	emit m_uiDelegate->AddDeviceMessage(deckLink);
	return S_OK;
}

HRESULT	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::DeckLinkDeviceRemoved(/* in */ IDeckLink* deckLink)
{
	// Update UI (remove device from menu) from main thread
	emit m_uiDelegate->RemoveDeviceMessage(deckLink);
	deckLink->Release();
	return S_OK;
}

HRESULT	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::QueryInterface(REFIID iid, LPVOID *ppv)
{
	HRESULT			result = E_NOINTERFACE;

	if (ppv == NULL)
		return E_INVALIDARG;

	// Initialise the return result
	*ppv = NULL;

	// Obtain the IUnknown interface and compare it the provided REFIID
	if (iid == IID_IUnknown)
	{
		*ppv = this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkDeviceNotificationCallback)
	{
		*ppv = (IDeckLinkDeviceNotificationCallback*)this;
		AddRef();
		result = S_OK;
	}

	return result;
}

ULONG	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::AddRef()
{
	return InterlockedIncrement((LONG*)&m_refCount);
}

ULONG	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::Release()
{
	ULONG		newRefValue;

	newRefValue = InterlockedDecrement((LONG*)&m_refCount);
	if (newRefValue == 0)
	{
		delete this;
		return 0;
	}

	return newRefValue;
}
#elif __APPLE_CC__
#elif defined(__linux__) 
#error "Unsupported platform"
#endif