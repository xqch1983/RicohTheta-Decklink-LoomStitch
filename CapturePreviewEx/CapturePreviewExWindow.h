#ifndef CAPTURE_PREVIEW_EX_WINDOW_H
#define CAPTURE_PREVIEW_EX_WINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_CapturePreviewEx.h"
#include <string>
#include "DeckLinkDevice.h"
#include <QMutex>

#ifndef _OLEAUTO_H_
typedef std::wstring AmdString;
#else
typedef std::string AmdString;
#endif

struct AncillaryDataStruct
{
	// VITC timecodes and user bits for field 1 & 2
	std::string vitcF1Timecode;
	std::string	vitcF1UserBits;
	std::string	vitcF2Timecode;
	std::string	vitcF2UserBits;

	// RP188 timecodes and user bits (VITC1, VITC2 and LTC)
	std::string	rp188vitc1Timecode;
	std::string	rp188vitc1UserBits;
	std::string	rp188vitc2Timecode;
	std::string	rp188vitc2UserBits;
	std::string	rp188ltcTimecode;
	std::string	rp188ltcUserBits;
};

class PreviewWindow;

class CapturePreviewExWindow : public QMainWindow
{
    Q_OBJECT

public:
    CapturePreviewExWindow(QWidget *parent = Q_NULLPTR);
	bool Init();

	void ShowErrorMessage(const std::string& msg, const std::string& title);
	void UpdateAncillaryData(AncillaryDataStruct& ancillaryData);

signals:
	void RefreshInputStreamDataMessage(unsigned long flag);
	void SelectVideoModeMessage(unsigned int index);
	void AddDeviceMessage(IDeckLink* deckLink);
	void RemoveDeviceMessage(IDeckLink* deckLink);
	void ErrorRestartingCaptureMessage();

protected:
	void EnableInterface(bool enabled);
	void RefreshVideoModeList();
	void StartCapture();
	void StartCapture(DeckLinkDevice* selectedDevice, PreviewWindow* previewWindow);
	void StopCapture();
	void StopCapture(DeckLinkDevice* selectedDevice);
	void AddDevice(IDeckLink* deckLink);
	void RemoveDevice(IDeckLink* deckLink);

protected slots:
	void OnNewDeviceSelected();
	void OnStartStopBnClicked();
	void OnClose();
	void OnStartStopBnClicked2();
	void OnStartStopBnClicked3();
	void OnStartStopBnClicked4();

	void OnRefreshInputStreamData(unsigned long flag);
	void OnSelectVideoMode(unsigned int index);
	void OnAddDevice(IDeckLink* deckLink);
	void OnRemoveDevice(IDeckLink* deckLink);
	void OnErrorRestartingCapture();

private:
    Ui::CapturePreviewExClass ui;
	unsigned int m_deviceCount;

	AncillaryDataStruct m_ancillaryData;
	QMutex m_mutex; // to synchronise access to the above structure

	DeckLinkDevice*	m_selectedDevice;
	DeckLinkDevice*	m_selectedDevice2;
	DeckLinkDevice*	m_selectedDevice3;
	DeckLinkDevice*	m_selectedDevice4;

	PreviewWindow* m_previewWindow;
	PreviewWindow* m_previewWindow2;
	PreviewWindow* m_previewWindow3;
	PreviewWindow* m_previewWindow4;

	DeckLinkDeviceDiscovery* m_deckLinkDiscovery;
	IDeckLink* m_deckLink;
};

#endif
