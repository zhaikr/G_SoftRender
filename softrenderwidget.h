#ifndef SOFTRENDERWIDGET_H
#define SOFTRENDERWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <softrendercore.h>
#include "shader.hpp"
#include "model.h"

namespace Ui {
class SoftRenderWidget;
}

class SoftRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoftRenderWidget(QWidget *parent = nullptr);
    ~SoftRenderWidget();
    void SetRenderColor(const Color& color);  //set background color
    void InitRender();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    int _width_;
    int _height_;
    Ui::SoftRenderWidget *ui;
    Model* model;

public slots:
    void Render();


};

#endif // SOFTRENDERWIDGET_H
