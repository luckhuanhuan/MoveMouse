#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <KF5/KWindowSystem/KWindowSystem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedSize(QApplication::desktop()->width(),QApplication::desktop()->height());
    setMouseTracking(true);

    QList<WId> windows = KWindowSystem::windows();
    for (long long unsigned int const id: windows)
    {
        KWindowInfo info(id, NET::WMGeometry);
        rects.append(info.frameGeometry());
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
   QPoint p = e->globalPos();
   //int t_screen = QApplication::desktop()->screenNumber(p);
   //QRect  m_backgroundRect = QApplication::desktop()->screen(t_screen)->geometry();
   //qDebug() << m_backgroundRect;
   for(QRect const rect : rects)
   {
     if(rect.contains(p))
         qDebug() << rect;
   }
}


Widget::~Widget()
{
    delete ui;
}
