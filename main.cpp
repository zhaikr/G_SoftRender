#include "softrender.h"
#include "softrenderwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoftRender w;
    w.show();
    //SoftRenderWidget w;
    //w.show();
    return a.exec();
}
