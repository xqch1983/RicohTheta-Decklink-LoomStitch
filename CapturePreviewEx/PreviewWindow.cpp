#include "PreviewWindow.h"
//#include "loom_shell_util.h"
//#include <loom_shell.h>

PreviewWindow::PreviewWindow(QOpenGLWidget* openGLWidget)
 : m_openGLWidget(openGLWidget)
 , m_deckLinkScreenPreviewHelper(nullptr)
 , m_refCount(1)
{

}

PreviewWindow::~PreviewWindow()
{
	if (m_deckLinkScreenPreviewHelper != nullptr)
	{
		m_deckLinkScreenPreviewHelper->Release();
		m_deckLinkScreenPreviewHelper = nullptr;
	}
}

bool PreviewWindow::init()
{
	// Create the DeckLink screen preview helper
	if (CoCreateInstance(CLSID_CDeckLinkGLScreenPreviewHelper, NULL, CLSCTX_ALL, IID_IDeckLinkGLScreenPreviewHelper, (void**)&m_deckLinkScreenPreviewHelper) != S_OK)
		return false;

	bool result = false;
	if (!m_openGLWidget->isValid())
		return false;

	if (m_deckLinkScreenPreviewHelper->InitializeGL() == S_OK)
		result = true;

	m_openGLWidget->doneCurrent();

	return result;
}

//platform relative: Jimmy Hua
#if WIN32
HRESULT STDMETHODCALLTYPE PreviewWindow::DrawFrame(IDeckLinkVideoFrame* theFrame)
{
	if (m_deckLinkScreenPreviewHelper == NULL || m_openGLWidget->isValid())
		return E_FAIL;

	// First, pass the frame to the DeckLink screen preview helper
	m_deckLinkScreenPreviewHelper->SetFrame(theFrame);

	m_openGLWidget->makeCurrent();

	// and let the helper take care of the drawing
	m_deckLinkScreenPreviewHelper->PaintGL();

	m_openGLWidget->doneCurrent();

	return S_OK;
}
#elif __APPLE_CC__
#elif defined(__linux__) 
#endif
