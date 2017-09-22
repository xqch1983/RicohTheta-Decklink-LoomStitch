#ifndef DECK_LINK_DEVICE_H
#define DECK_LINK_DEVICE_H

#include <vector>
#include <map>
#include "DeckLinkAPI_h.h"
#include <VX/vx.h>
#include <Cl\cl.h>
#include <live_stitch_api.h>

class CapturePreviewExWindow;

class DeckLinkDevice : public IDeckLinkInputCallback
{
public:
	DeckLinkDevice(CapturePreviewExWindow* uiDelegate, IDeckLink* device);
	virtual ~DeckLinkDevice();

	bool Init();
	const std::string& GetDeviceName() { return m_deviceName; };
	void GetDisplayModeNames(std::vector<std::string>& modeNames);
	bool SupportsFormatDetection() { return m_supportsFormatDetection; };
	bool IsCapturing() { return m_currentlyCapturing; };
	bool StartCapture(int videoModeIndex, IDeckLinkScreenPreviewCallback* screenPreviewCallback, bool applyDetectedInputMode);
	void StopCapture();
	IDeckLink* DeckLinkInstance() { return m_deckLink; }

	//platform relative: Jimmy Hua
#if WIN32
	virtual HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(/* in */ BMDVideoInputFormatChangedEvents notificationEvents, /* in */ IDeckLinkDisplayMode *newDisplayMode, /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(/* in */ IDeckLinkVideoInputFrame* videoFrame, /* in */ IDeckLinkAudioInputPacket* audioPacket);
	// IUnknown needs only a dummy implementation
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

	BOOL m_supportsFormatDetection;
#elif __APPLE_CC__
	virtual HRESULT VideoInputFormatChanged(/* in */ BMDVideoInputFormatChangedEvents notificationEvents, /* in */ IDeckLinkDisplayMode *newDisplayMode, /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags);
	virtual HRESULT VideoInputFrameArrived(/* in */ IDeckLinkVideoInputFrame* videoFrame, /* in */ IDeckLinkAudioInputPacket* audioPacket);
	// IUnknown needs only a dummy implementation
	virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv);
	virtual ULONG AddRef();
	virtual ULONG Release();
	bool m_supportsFormatDetection;
#elif defined(__linux__) 
	#error "Unsupported platform"
#endif
	
protected:
	static void	GetAncillaryDataFromFrame(IDeckLinkVideoInputFrame* frame, BMDTimecodeFormat format, std::string& timecodeString, std::string& userBitsString);

	int releaseAllResources();
	bool initStitching();

	CapturePreviewExWindow* m_uiDelegate;
	unsigned int m_refCount;
	std::string m_deviceName;
	IDeckLink* m_deckLink;
	IDeckLinkInput* m_deckLinkInput;
	IDeckLinkOutput* m_outputCard;
	std::vector<IDeckLinkDisplayMode*> m_modeList;
	bool m_currentlyCapturing;
	bool m_applyDetectedInputMode;

private:
	bool decl_ls_disabled, decl_vx_disabled, decl_cl_disabled, decl_buf_disabled;
	char name_ls[64], name_vx[64], name_cl[64], name_buf[64];
	vx_uint32 num_context_, num_openvx_context_, num_opencl_context_, num_opencl_buf_;
	ls_context * context_;
	vx_context * openvx_context_;
	cl_context * opencl_context_;
	bool * openvx_context_allocated_;
	bool * opencl_context_allocated_;
	cl_mem * opencl_buf_mem_;
	std::map<std::string, camera_params> camParList;
	std::map<std::string, rig_params> rigParList;
	vx_float32 attr_buf_[LIVE_STITCH_ATTR_MAX_COUNT];
	IDeckLinkMutableVideoFrame *m_yuvFrame;
	void *frameBytesDest;
};

class DeckLinkDeviceDiscovery : public IDeckLinkDeviceNotificationCallback
{
public:
	DeckLinkDeviceDiscovery(CapturePreviewExWindow* uiDelegate);
	virtual ~DeckLinkDeviceDiscovery();

	bool Enable();
	void Disable();

	//platform relative interfaces: Jimmy Hua
#if WIN32
	// IDeckLinkDeviceNotificationCallback interface
	virtual HRESULT	STDMETHODCALLTYPE	DeckLinkDeviceArrived(/* in */ IDeckLink* deckLink);
	virtual HRESULT	STDMETHODCALLTYPE	DeckLinkDeviceRemoved(/* in */ IDeckLink* deckLink);
	// IUnknown needs only a dummy implementation
	virtual HRESULT	STDMETHODCALLTYPE	QueryInterface(REFIID iid, LPVOID *ppv);
	virtual ULONG	STDMETHODCALLTYPE	AddRef();
	virtual ULONG	STDMETHODCALLTYPE	Release();
#elif __APPLE_CC__
	virtual HRESULT	DeckLinkDeviceArrived(/* in */ IDeckLink* deckLink);
	virtual HRESULT	DeckLinkDeviceRemoved(/* in */ IDeckLink* deckLink);
	// IUnknown needs only a dummy implementation
	virtual HRESULT	QueryInterface(REFIID iid, LPVOID *ppv);
	virtual ULONG	AddRef();
	virtual ULONG	Release();
#elif defined(__linux__) 
	#error "Unsupported platform"
#endif

private:
	IDeckLinkDiscovery*	m_deckLinkDiscovery;
	CapturePreviewExWindow* m_uiDelegate;
	unsigned int m_refCount;
};

#endif // !DECK_LINK_DEVICE_H