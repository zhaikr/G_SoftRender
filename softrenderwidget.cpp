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
    SoftRenderCore::Init(300, 300);
    SoftRenderCore::GetInstance().shader = std::make_unique<Shader>();
}

void SoftRenderWidget::SetRenderColor(const Color& color)
{
    SoftRenderCore::GetInstance().clearcolor = color;
}

void SoftRenderWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0,0, SoftRenderCore::GetInstance().GetBuffer());
}

void SoftRenderWidget::Render()
{
    SetRenderColor({0.98f, 0.98f, 0.98f});
    SoftRenderCore::GetInstance().ClearBuffer();
    std::vector<Vertex> vertex_list;
    Vertex v1, v2, v3;
    //v1.screen_position_ = Coord2D(300, 0);
    //v2.screen_position_ = Coord2D(0, 0);
    //v3.screen_position_ = Coord2D(150, 300);
    v1.ndc_space_position_ = Coord4D(-0.5f, -0.5f, 0.f, 1.f);
    v2.ndc_space_position_ = Coord4D(0.5f, -0.5f, 0.f, 1.f);
    v3.ndc_space_position_ = Coord4D(0.f, 0.5f, 0.f, 1.f);
    v1.color_ = Color(1.f, 0.f, 0.f);
    v2.color_ = Color(0.f, 1.f, 0.f);
    v3.color_ = Color(0.f, 0.f, 1.f);
    vertex_list = {v1, v2, v3};
    model->ProcessNode(vertex_list);
    model->DrawModel();
    //update();
}
