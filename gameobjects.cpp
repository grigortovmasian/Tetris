#include "gameobjects.h"
#include "shareddata.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>

GameAreaGItem::GameAreaGItem(qreal w, qreal h, SharedData *data):m_sharedData(data)
{
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(0,h));
    m_polygon.append(QPointF(w,h));
    m_polygon.append(QPointF(w,0));
    m_polygon.append(QPointF(0,0));
}

void GameAreaGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawPolygon(m_polygon);


    if(!m_sharedData)
        return;

    int step=m_sharedData->globalSize();
    qreal w = m_polygon.boundingRect().width();
    qreal h = m_polygon.boundingRect().height();
    for(int x = step; x<w;x+=step){
        painter->drawLine(x,0,x,h);
    }

    for(int y = step; y<h; y+=step){
        painter->drawLine(0,y,w,y);
    }

}

OrangeRickyObject::OrangeRickyObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y+2)*step));
    m_polygon.append(QPointF((x+3)*step,(y+2)*step));
    m_polygon.append(QPointF((x+3)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));
}

void OrangeRickyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::darkYellow,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y,x+2*step,y+step));
        painter->drawLine(QLineF(x+2*step,y+step,x+3*step,y+step));
    }
}

BlueRickyObject::BlueRickyObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y+2)*step));
    m_polygon.append(QPointF((x+1)*step,(y+2)*step));
    m_polygon.append(QPointF((x+1)*step,(y+1)*step));
    m_polygon.append(QPointF((x+3)*step,(y+1)*step));
    m_polygon.append(QPointF((x+3)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));

}

void BlueRickyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::blue,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y,x+2*step,y+step));
        painter->drawLine(QLineF(x,y+step,x+step,y+step));
    }
}

CleveleandZObject::CleveleandZObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y+2)*step));
    m_polygon.append(QPointF((x+2)*step,(y+2)*step));
    m_polygon.append(QPointF((x+2)*step,(y+1)*step));
    m_polygon.append(QPointF((x+3)*step,(y+1)*step));
    m_polygon.append(QPointF((x+3)*step,(y)*step));
    m_polygon.append(QPointF((x+1)*step,(y)*step));
    m_polygon.append(QPointF((x+1)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y+1)*step));

}

void CleveleandZObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::red,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y,x+2*step,y-step));
        painter->drawLine(QLineF(x+step,y,x+2*step,y));
    }
}

RhodeIslandZObject::RhodeIslandZObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y+1)*step));
    m_polygon.append(QPointF((x+1)*step,(y+1)*step));
    m_polygon.append(QPointF((x+1)*step,(y+2)*step));
    m_polygon.append(QPointF((x+3)*step,(y+2)*step));
    m_polygon.append(QPointF((x+3)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));
}

void RhodeIslandZObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::green,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y+step,x+2*step,y+2*step));
        painter->drawLine(QLineF(x+step,y+step,x+2*step,y+step));
    }
}

TeeWeeObject::TeeWeeObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x+3)*step,(y)*step));
    m_polygon.append(QPointF((x+3)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y+1)*step));
    m_polygon.append(QPointF((x+2)*step,(y+2)*step));
    m_polygon.append(QPointF((x+1)*step,(y+2)*step));
    m_polygon.append(QPointF((x+1)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));

}

void TeeWeeObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::magenta,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y,x+2*step,y+step));
        painter->drawLine(QLineF(x+step,y+step,x+2*step,y+step));
    }
}

SmashBoyObject::SmashBoyObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x+2)*step,(y)*step));
    m_polygon.append(QPointF((x+2)*step,(y+2)*step));
    m_polygon.append(QPointF((x)*step,(y+2)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));
}

void SmashBoyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::yellow,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+2*step));
        painter->drawLine(QLineF(x,y+step,x+2*step,y+step));
    }
}

HeroObject::HeroObject(int x, int y, SharedData *data):m_sharedData(data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.append(QPointF((x)*step,(y)*step));
    m_polygon.append(QPointF((x+4)*step,(y)*step));
    m_polygon.append(QPointF((x+4)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y+1)*step));
    m_polygon.append(QPointF((x)*step,(y)*step));
}

void HeroObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(Qt::cyan,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
    if(!m_polygon.isEmpty()&&m_sharedData) {
        int step = m_sharedData->globalSize();
        qreal x= m_polygon[0].x();
        qreal y= m_polygon[0].y();
        painter->drawLine(QLineF(x+step,y,x+step,y+step));
        painter->drawLine(QLineF(x+2*step,y,x+2*step,y+step));
        painter->drawLine(QLineF(x+3*step,y,x+3*step,y+step));
    }
}
