#ifndef PREVIEW_WINDOW_H
#define PREVIEW_WINDOW_H

#include "DeckLinkAPI_h.h"
#include <live_stitch_api.h>
#include <QOpenGLWidget>

class PreviewWindow : public IDeckLinkScreenPreviewCallback
{
public:
	PreviewWindow(QOpenGLWidget* openGLWidget);
	virtual ~PreviewWindow();

	bool init();

	//platform relative: Jimmy Hua
#if WIN32
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv) override { return E_NOINTERFACE; }
	virtual ULONG	STDMETHODCALLTYPE AddRef() override { return 1; }
	virtual ULONG	STDMETHODCALLTYPE Release() override { return 1; }
	virtual HRESULT STDMETHODCALLTYPE DrawFrame(IDeckLinkVideoFrame* theFrame) override;
#elif __APPLE_CC__
	virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override { return E_NOINTERFACE; }
	virtual ULONG	AddRef() override { return 1; }
	virtual ULONG	Release() override { return 1; }
	virtual HRESULT DrawFrame(IDeckLinkVideoFrame* theFrame) override;
#elif defined(__linux__) 
	#error "Unsupported platform"
#endif


private:
	IDeckLinkGLScreenPreviewHelper* m_deckLinkScreenPreviewHelper;
	QOpenGLWidget* m_openGLWidget;
	LONG m_refCount;
};

#endif