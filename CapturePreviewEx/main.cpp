#include "CapturePreviewExWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CapturePreviewExWindow w;
	w.Init();
    w.show();
    return a.exec();
}
