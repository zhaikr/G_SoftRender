#ifndef SOFTRENDER_H
#define SOFTRENDER_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class SoftRender; }
QT_END_NAMESPACE

class SoftRender : public QMainWindow
{
    Q_OBJECT

public:
    SoftRender(QWidget *parent = nullptr);
    ~SoftRender();

private:
    Ui::SoftRender *ui;

};
#endif // SOFTRENDER_H
