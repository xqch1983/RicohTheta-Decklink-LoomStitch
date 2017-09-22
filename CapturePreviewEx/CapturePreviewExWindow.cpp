#include "CapturePreviewExWindow.h"
#include <QIcon>
#include <QMessageBox>
#include <QString>
#include <QVariant>
#include "PreviewWindow.h"

CapturePreviewExWindow::CapturePreviewExWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_deviceCount(0U)
	, m_selectedDevice(nullptr)
	, m_selectedDevice2(nullptr)
	, m_selectedDevice3(nullptr)
	, m_selectedDevice4(nullptr)
{
	ui.setupUi(this);

	setWindowIconText(QString("AMD"));

	ui.LoomLogoBox->setPixmap(QPixmap("Resources\\LoomLogo256.bmp"));
	ui.LoomLogoBox->setScaledContents(true);

	QObject::connect(ui.deviceListComboBox, SIGNAL(currentIndexChanged), this, SLOT(OnNewDeviceSelected));
	QObject::connect(ui.startStopButton, SIGNAL(clicked), this, SLOT(OnStartStopBnClicked));
	QObject::connect(ui.startStopButton2, SIGNAL(clicked), this, SLOT(OnStartStopBnClicked2));
	QObject::connect(ui.startStopButton3, SIGNAL(clicked), this, SLOT(OnStartStopBnClicked3));
	QObject::connect(ui.startStopButton4, SIGNAL(clicked), this, SLOT(OnStartStopBnClicked4));
	QObject::connect(this, SIGNAL(close), this, SLOT(OnClose));

	QObject::connect(this, SIGNAL(RefreshInputStreamDataMessage(unsigned long)), this, SLOT(OnRefreshInputStreamData(unsigned long)));
	QObject::connect(this, SIGNAL(SelectVideoModeMessage(unsigned int)), this, SLOT(OnSelectVideoMode(unsigned int)));
	QObject::connect(this, SIGNAL(AddDeviceMessage(IDeckLink*)), this, SLOT(OnAddDevice(IDeckLink*)));
	QObject::connect(this, SIGNAL(RemoveDeviceMessage(IDeckLink*)), this, SLOT(OnRemoveDevice(IDeckLink*)));
	QObject::connect(this, SIGNAL(ErrorRestartingCaptureMessage), this, SLOT(OnErrorRestartingCapture));
}

bool CapturePreviewExWindow::Init()
{
	EnableInterface(false);
	m_previewWindow = new PreviewWindow(ui.openGLWidget);
	m_previewWindow2 = new PreviewWindow(ui.openGLWidget2);
	m_previewWindow3 = new PreviewWindow(ui.openGLWidget3);
	m_previewWindow4 = new PreviewWindow(ui.openGLWidget4);

	if (!m_previewWindow->init())
	{
		ShowErrorMessage("This application was unable to initialise the preview window 1.", "Error");
		return false;
	}
	if (!m_previewWindow2->init())
	{
		ShowErrorMessage("This application was unable to initialise the preview window 2.", "Error");
		return false;
	}
	if (!m_previewWindow3->init())
	{
		ShowErrorMessage("This application was unable to initialise the preview window 3.", "Error");
		return false;
	}
	if (!m_previewWindow4->init())
	{
		ShowErrorMessage("This application was unable to initialise the preview window 4.", "Error");
		return false;
	}

	m_deckLinkDiscovery = new DeckLinkDeviceDiscovery(this);
	if (!m_deckLinkDiscovery->Enable())
	{
		ShowErrorMessage("Please install the Blackmagic Desktop Video drivers to use the features of this application.", 
			"This application requires the Desktop Video drivers installed.");
		return false;
	}

	return true;
}

void CapturePreviewExWindow::ShowErrorMessage(const std::string& msg, const std::string& title)
{
	QMessageBox messageBox(QMessageBox::NoIcon, QString::fromStdString(title), QString::fromStdString(msg));
	messageBox.exec();
}

void CapturePreviewExWindow::UpdateAncillaryData(AncillaryDataStruct& ancillaryData)
{
	m_mutex.lock();
	m_ancillaryData = ancillaryData;
	m_mutex.unlock();
}

void CapturePreviewExWindow::EnableInterface(bool enabled)
{
	ui.deviceListComboBox->setEnabled(enabled);
	ui.videoFormatComboBox->setEnabled(enabled);

	if (enabled)
	{
		if (m_selectedDevice != nullptr && m_selectedDevice->SupportsFormatDetection())
		{
			ui.applyDetectedInputForwardCheckBox->setEnabled(true);
		}
		else
		{
			ui.applyDetectedInputForwardCheckBox->setEnabled(false);
			ui.applyDetectedInputForwardCheckBox->setCheckState(Qt::Unchecked);
		}
	}
	else
	{
		ui.applyDetectedInputForwardCheckBox->setEnabled(false);
	}
}

void CapturePreviewExWindow::RefreshVideoModeList()
{
	std::vector<std::string> modeNames;
	unsigned int modeIndex = 0;

	m_selectedDevice->GetDisplayModeNames(modeNames);

	ui.videoFormatComboBox->clear();

	while (modeIndex < modeNames.size())
	{
		ui.videoFormatComboBox->addItem(QString::fromStdString(modeNames.at(modeIndex++)));
	}

	ui.videoFormatComboBox->setCurrentIndex(0);
}

void CapturePreviewExWindow::StartCapture(DeckLinkDevice* selectedDevice, PreviewWindow* previewWindow)
{
	bool applyDetectedInputMode = ui.applyDetectedInputForwardCheckBox->isChecked();

	if (selectedDevice != nullptr &&
		selectedDevice->StartCapture(ui.videoFormatComboBox->currentIndex(), previewWindow, applyDetectedInputMode))
	{
		ui.startStopButton->setText("Stop Capture");
		EnableInterface(false);
	}
}

void CapturePreviewExWindow::StartCapture()
{
	StartCapture(m_selectedDevice, m_previewWindow);
}

void CapturePreviewExWindow::StopCapture(DeckLinkDevice* selectedDevice)
{
	if (selectedDevice != nullptr)
	{
		selectedDevice->StopCapture();
	}

	ui.startStopButton->setText("Start Capture And Stitching");
	EnableInterface(true);
	
	ui.signalInfoLabel->setVisible(false);
}

void CapturePreviewExWindow::StopCapture()
{
	StopCapture(m_selectedDevice);
}

void CapturePreviewExWindow::AddDevice(IDeckLink* deckLink)
{
	m_deckLink = deckLink;
	DeckLinkDevice* newDevice = new DeckLinkDevice(this, deckLink);

	if (!newDevice->Init())
	{
		newDevice->Release();
		return;
	}

	char s[12];
	itoa(m_deviceCount, s, 10);
	std::string str, str2;
	str = s;
	str2 = newDevice->GetDeviceName();
	str2 += " ";
	str2 += str;
	ui.deviceListComboBox->addItem(QString::fromStdString(str2), QVariant(0, reinterpret_cast<void*>(newDevice)));

	int selectedDeviceIndex = 0;
	if (ui.deviceListComboBox->count() == 1)
	{
		selectedDeviceIndex = 0;
		ui.deviceListComboBox->setCurrentIndex(selectedDeviceIndex);
		OnNewDeviceSelected();

		ui.startStopButton->setEnabled(true);
		EnableInterface(true);
	}
	else if (ui.deviceListComboBox->count() == 2)
	{
		selectedDeviceIndex = 1;
		ui.deviceListComboBox->setCurrentIndex(selectedDeviceIndex);
		OnNewDeviceSelected();

		m_selectedDevice2 = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(selectedDeviceIndex).data());
		ui.startStopButton2->setEnabled(true);
		EnableInterface(true);
	}
	else if (ui.deviceListComboBox->count() == 3)
	{
		selectedDeviceIndex = 2;
		ui.deviceListComboBox->setCurrentIndex(selectedDeviceIndex);
		OnNewDeviceSelected();

		m_selectedDevice3 = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(selectedDeviceIndex).data());
		ui.startStopButton3->setEnabled(true);
		EnableInterface(true);
	}
	else if (ui.deviceListComboBox->count() == 4)
	{
		selectedDeviceIndex = 3;
		ui.deviceListComboBox->setCurrentIndex(selectedDeviceIndex);
		OnNewDeviceSelected();

		m_selectedDevice4 = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(selectedDeviceIndex).data());
		ui.startStopButton4->setEnabled(true);
		EnableInterface(true);
	}
}

void CapturePreviewExWindow::RemoveDevice(IDeckLink* deckLink)
{
	int deviceIndex = -1;
	DeckLinkDevice* deviceToRemove = nullptr;

	for (deviceIndex = 0; deviceIndex < ui.deviceListComboBox->count(); ++deviceIndex)
	{
		deviceToRemove = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(deviceIndex).data());
		if (deviceToRemove->DeckLinkInstance() == deckLink)
		{
			ui.deviceListComboBox->removeItem(deviceIndex);
			break;
		}
	}

	if (deviceToRemove == nullptr)
		return;

	if (deviceToRemove->IsCapturing())
		deviceToRemove->StopCapture();

	ui.startStopButton->setText("Capture And Stitching");

	if (ui.deviceListComboBox->count() == 0)
	{
		ui.startStopButton->setEnabled(false);
		EnableInterface(false);
		m_selectedDevice = nullptr;
	}
	else if (m_selectedDevice == deviceToRemove)
	{
		ui.deviceListComboBox->setCurrentIndex(0);
		OnNewDeviceSelected();
		ui.startStopButton->setEnabled(true);
		ui.signalInfoLabel->setVisible(false);
	}

	deviceToRemove->Release();
}

void CapturePreviewExWindow::OnNewDeviceSelected()
{
	int selectedDeviceIndex = ui.deviceListComboBox->currentIndex();
	if (selectedDeviceIndex < 0)
		return;

	m_selectedDevice = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(selectedDeviceIndex).data());

	RefreshVideoModeList();
	EnableInterface(true);

	if (m_selectedDevice != nullptr && m_selectedDevice->SupportsFormatDetection())
		ui.applyDetectedInputForwardCheckBox->setChecked(true);
}

void CapturePreviewExWindow::OnStartStopBnClicked()
{
	if (m_selectedDevice == nullptr)
		return;

	if (m_selectedDevice->IsCapturing())
		StopCapture();
	else
		StartCapture();
}

void CapturePreviewExWindow::OnClose()
{
	RemoveDevice(m_deckLink);

	for (int index = 0; index < ui.deviceListComboBox->count(); ++index)
	{
		DeckLinkDevice* deckLinkDevice = reinterpret_cast<DeckLinkDevice*>(ui.deviceListComboBox->itemData(index).data());
		deckLinkDevice->Release();
	}

	if (m_previewWindow != nullptr)
	{
		delete m_previewWindow;
		m_previewWindow = nullptr;
	}

	if (m_previewWindow2 != nullptr)
	{
		delete m_previewWindow2;
		m_previewWindow2 = nullptr;
	}

	if (m_previewWindow3 != nullptr)
	{
		delete m_previewWindow3;
		m_previewWindow3 = nullptr;
	}

	if (m_previewWindow4 != nullptr)
	{
		delete m_previewWindow4;
		m_previewWindow4 = nullptr;
	}

	if (m_deckLinkDiscovery != nullptr)
	{
		m_deckLinkDiscovery->Disable();
		m_deckLinkDiscovery->Release();
		m_deckLinkDiscovery = nullptr;
	}
}

void CapturePreviewExWindow::OnStartStopBnClicked2()
{
	if (m_selectedDevice2 == nullptr)
		return;

	if (m_selectedDevice2->IsCapturing())
		StopCapture(m_selectedDevice2);
	else
		StartCapture(m_selectedDevice2, m_previewWindow2);
}

void CapturePreviewExWindow::OnStartStopBnClicked3()
{
	if (m_selectedDevice3 == nullptr)
		return;

	if (m_selectedDevice3->IsCapturing())
		StopCapture(m_selectedDevice3);
	else
		StartCapture(m_selectedDevice3, m_previewWindow3);
}

void CapturePreviewExWindow::OnStartStopBnClicked4()
{
	if (m_selectedDevice4 == nullptr)
		return;

	if (m_selectedDevice4->IsCapturing())
		StopCapture(m_selectedDevice4);
	else
		StartCapture(m_selectedDevice4, m_previewWindow4);
}

void CapturePreviewExWindow::OnRefreshInputStreamData(unsigned long flag)
{
	m_mutex.lock();
	ui.vitcTcF1->setText(QString::fromStdString(m_ancillaryData.vitcF1Timecode));
	ui.vitcUbF1->setText(QString::fromStdString(m_ancillaryData.vitcF1UserBits));
	ui.vitcTcF2->setText(QString::fromStdString(m_ancillaryData.vitcF2Timecode));
	ui.vitcUbF2->setText(QString::fromStdString(m_ancillaryData.vitcF2UserBits));
	ui.rp188Vitc1Tc->setText(QString::fromStdString(m_ancillaryData.rp188vitc1Timecode));
	ui.rp188Vitc1Ub->setText(QString::fromStdString(m_ancillaryData.rp188vitc1UserBits));
	ui.rp188Vitc2Tc->setText(QString::fromStdString(m_ancillaryData.rp188vitc2Timecode));
	ui.rp188Vitc2Ub->setText(QString::fromStdString(m_ancillaryData.rp188vitc2UserBits));
	ui.rp188LtcTc->setText(QString::fromStdString(m_ancillaryData.rp188ltcTimecode));
	ui.rp188LtcUb->setText(QString::fromStdString(m_ancillaryData.rp188ltcUserBits));
	m_mutex.unlock();

	ui.signalInfoLabel->setVisible(flag != 0);
}

void CapturePreviewExWindow::OnSelectVideoMode(unsigned int index)
{
	ui.videoFormatComboBox->setCurrentIndex(index);
}

void CapturePreviewExWindow::OnAddDevice(IDeckLink* deckLink)
{
	AddDevice(deckLink);
	++m_deviceCount;
}

void CapturePreviewExWindow::OnRemoveDevice(IDeckLink* deckLink)
{
	RemoveDevice(deckLink);
	--m_deviceCount;
}

void CapturePreviewExWindow::OnErrorRestartingCapture()
{
	StopCapture();
	ShowErrorMessage("This application was unable to apply the detected input video mode.", "Error restarting the capture.");
}
