#include "softrenderwidget.h"
#include "ui_softrenderwidget.h"


SoftRenderWidget::SoftRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftRenderWidget)
{
    ui->setupUi(this);
    InitRender();
    model = new Model;
    Render();
}


SoftRenderWidget::~SoftRenderWidget()
{
    delete ui;
    delete model;
}

void SoftRenderWidget::InitRender()
{
    SoftRenderCore::Init(600, 600);
}

void SoftRenderWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0,0, SoftRenderCore::GetInstance().GetBuffer());
}

void SoftRenderWidget::Render()
{
    SoftRenderCore::GetInstance().ClearBuffer();
    std::vector<Vertex> vertex_list;
    Vertex v1, v2, v3;
    v1.screen_position_ = Coord2D(200, 0);
    v2.screen_position_ = Coord2D(100, 0);
    v3.screen_position_ = Coord2D(150, 150);
    v1.color_ = Color(255.f, 0.f, 0.f, 255.f);
    v2.color_ = Color(0.f, 255.f, 0.f, 255.f);
    v3.color_ = Color(0.f, 0.f, 255.f, 255.f);
    vertex_list = {v1, v2, v3};
    model->ProcessNode(vertex_list);
    model->DrawModel();
    //update();
}
