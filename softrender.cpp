#include "softrender.h"
#include "./ui_softrender.h"
#include "softrenderwidget.h"


SoftRender::SoftRender(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoftRender)
{
    ui->setupUi(this);
}

SoftRender::~SoftRender()
{
    delete ui;
}

