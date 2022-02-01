#include "gameobjects.h"
#include "shareddata.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QTransform>
#include "tetrisviewer.h"

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

OrangeRickyObject::OrangeRickyObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(2*step,step));
    m_polygon.append(QPointF(2*step,2*step));
    m_polygon.append(QPointF(3*step,2*step));
    m_polygon.append(QPointF(3*step,0));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::darkYellow;
}

void OrangeRickyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void OrangeRickyObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case UP: areaMap[m_x][m_y]= new PlacedFigure(m_x,m_y,m_col,m_sharedData);
             areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
             areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
             areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
             placedFigured.append(areaMap[m_x][m_y]);
             placedFigured.append(areaMap[m_x+1][m_y]);
             placedFigured.append(areaMap[m_x+2][m_y]);
             placedFigured.append(areaMap[m_x+2][m_y+1]);
             break;
    case DOWN: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
               areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
               areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
               areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x][m_y]);
               placedFigured.append(areaMap[m_x][m_y+1]);
               placedFigured.append(areaMap[m_x+1][m_y+1]);
               placedFigured.append(areaMap[m_x+2][m_y+1]);
               break;
    case LEFT:; areaMap[m_x+1][m_y+2]=new PlacedFigure(m_x+1,m_y+2,m_col,m_sharedData);
                areaMap[m_x+2][m_y+2]=new PlacedFigure(m_x+2,m_y+2,m_col,m_sharedData);
                areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x+1][m_y+2]);
                placedFigured.append(areaMap[m_x+2][m_y+2]);
                placedFigured.append(areaMap[m_x+2][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y]);
                break;
    case RIGHT: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x][m_y+2]=new PlacedFigure(m_x,m_y+2,m_col,m_sharedData);
                areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x][m_y+2]);
                placedFigured.append(areaMap[m_x+1][m_y]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }

}

bool OrangeRickyObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case UP:  ret = areaMap[m_x][m_y] || areaMap[m_x+1][m_y] || areaMap[m_x+2][m_y] || areaMap[m_x+2][m_y+1];
             break;
    case DOWN: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1];
               break;
    case LEFT:; ret = areaMap[m_x+1][m_y+2] || areaMap[m_x+2][m_y+2] || areaMap[m_x+2][m_y+1] || areaMap[m_x+2][m_y];
                break;
    case RIGHT: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] ||  areaMap[m_x][m_y+2] || areaMap[m_x+1][m_y];
                break;
    default: break;
    }
    return ret;
}

BlueRickyObject::BlueRickyObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(0,2*step));
    m_polygon.append(QPointF(step,2*step));
    m_polygon.append(QPointF(step,step));
    m_polygon.append(QPointF(3*step,step));
    m_polygon.append(QPointF(3*step,0));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::blue;
}

void BlueRickyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void BlueRickyObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case UP: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
             areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
             areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
             areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
             placedFigured.append(areaMap[m_x][m_y]);
             placedFigured.append(areaMap[m_x][m_y+1]);
             placedFigured.append(areaMap[m_x+1][m_y]);
             placedFigured.append(areaMap[m_x+2][m_y]);
             break;
    case DOWN: areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
               areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
               areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
               areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x+2][m_y]);
               placedFigured.append(areaMap[m_x][m_y+1]);
               placedFigured.append(areaMap[m_x+1][m_y+1]);
               placedFigured.append(areaMap[m_x+2][m_y+1]);
               break;
    case LEFT:  areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
                areaMap[m_x+2][m_y+2]=new PlacedFigure(m_x+2,m_y+2,m_col,m_sharedData);
                areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x+1][m_y]);
                placedFigured.append(areaMap[m_x+2][m_y+2]);
                placedFigured.append(areaMap[m_x+2][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y]);
                break;
    case RIGHT: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x][m_y+2]=new PlacedFigure(m_x,m_y+2,m_col,m_sharedData);
                areaMap[m_x+1][m_y+2]=new PlacedFigure(m_x+1,m_y+2,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x][m_y+2]);
                placedFigured.append(areaMap[m_x+1][m_y+2]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }

}

bool BlueRickyObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case UP: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y] ||  areaMap[m_x+2][m_y];
             break;
    case DOWN: ret = areaMap[m_x+2][m_y] || areaMap[m_x][m_y+1]|| areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1];
               break;
    case LEFT: ret = areaMap[m_x+1][m_y] || areaMap[m_x+2][m_y+2] || areaMap[m_x+2][m_y+1] || areaMap[m_x+2][m_y];
                break;
    case RIGHT: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x][m_y+2] || areaMap[m_x+1][m_y+2];
                break;
    default: break;
    }
    return ret;
}

CleveleandZObject::CleveleandZObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(0,2*step));
    m_polygon.append(QPointF(2*step,2*step));
    m_polygon.append(QPointF(2*step,step));
    m_polygon.append(QPointF(3*step,step));
    m_polygon.append(QPointF(3*step,0));
    m_polygon.append(QPointF(step,0));
    m_polygon.append(QPointF(step,step));
    m_polygon.append(QPointF(0,step));
    setPos(x*step,y*step);
    m_col = Qt::red;
}

void CleveleandZObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void CleveleandZObject::fillAreaMap(QVector<QVector<PlacedFigure*> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case DOWN: ;
    case UP: areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
             areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
             areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
             areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
             placedFigured.append(areaMap[m_x][m_y+1]);
             placedFigured.append(areaMap[m_x+1][m_y+1]);
             placedFigured.append(areaMap[m_x+1][m_y]);
             placedFigured.append(areaMap[m_x+2][m_y]);
             break;
    case LEFT:  areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
                areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y+2]=new PlacedFigure(m_x+2,m_y+2,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x+1][m_y]);
                placedFigured.append(areaMap[m_x+1][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y+2]);
                break;
    case RIGHT: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
                areaMap[m_x+1][m_y+2]=new PlacedFigure(m_x+1,m_y+2,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x+1][m_y+1]);
                placedFigured.append(areaMap[m_x+1][m_y+2]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }
}

bool CleveleandZObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case DOWN: ;
    case UP: ret = areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y+1] || areaMap[m_x+1][m_y] || areaMap[m_x+2][m_y];
             break;
    case LEFT:ret = areaMap[m_x+1][m_y] || areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1] || areaMap[m_x+2][m_y+2];
              break;
    case RIGHT: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y+1] || areaMap[m_x+1][m_y+2];
                break;
    default: break;
    }
    return ret;
}

RhodeIslandZObject::RhodeIslandZObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(step,step));
    m_polygon.append(QPointF(step,2*step));
    m_polygon.append(QPointF(3*step,2*step));
    m_polygon.append(QPointF(3*step,step));
    m_polygon.append(QPointF(2*step,step));
    m_polygon.append(QPointF(2*step,0));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::green;
}

void RhodeIslandZObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void RhodeIslandZObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case UP: ;
    case DOWN: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
               areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
               areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
               areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x][m_y]);
               placedFigured.append(areaMap[m_x+1][m_y]);
               placedFigured.append(areaMap[m_x+1][m_y+1]);
               placedFigured.append(areaMap[m_x+2][m_y+1]);
               break;
    case LEFT: areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
               areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
               areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
               areaMap[m_x+1][m_y+2]=new PlacedFigure(m_x+1,m_y+2,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x+2][m_y]);
               placedFigured.append(areaMap[m_x+1][m_y+1]);
               placedFigured.append(areaMap[m_x+2][m_y+1]);
               placedFigured.append(areaMap[m_x+1][m_y+2]);
               break;
    case RIGHT: areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
                areaMap[m_x][m_y+2]=new PlacedFigure(m_x,m_y+2,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x+1][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x+1][m_y+1]);
                placedFigured.append(areaMap[m_x][m_y+2]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }
}

bool RhodeIslandZObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case UP: ;
    case DOWN: ret = areaMap[m_x][m_y] || areaMap[m_x+1][m_y] || areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1];
               break;
    case LEFT: ret = areaMap[m_x+2][m_y] || areaMap[m_x+1][m_y+1]|| areaMap[m_x+2][m_y+1] ||  areaMap[m_x+1][m_y+2];
               break;
    case RIGHT: ret = areaMap[m_x+1][m_y] || areaMap[m_x][m_y+1]|| areaMap[m_x+1][m_y+1] ||  areaMap[m_x][m_y+2];
                break;
    default: break;
    }
    return ret;
}

TeeWeeObject::TeeWeeObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(3*step,0));
    m_polygon.append(QPointF(3*step,step));
    m_polygon.append(QPointF(2*step,step));
    m_polygon.append(QPointF(2*step,2*step));
    m_polygon.append(QPointF(step,2*step));
    m_polygon.append(QPointF(step,step));
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::magenta;
}

void TeeWeeObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void TeeWeeObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case UP: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
             areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
             areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
             areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
             placedFigured.append(areaMap[m_x][m_y]);
             placedFigured.append(areaMap[m_x+1][m_y]);
             placedFigured.append(areaMap[m_x+2][m_y]);
             placedFigured.append(areaMap[m_x+1][m_y+1]);
             break;
    case DOWN: areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
               areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
               areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
               areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x][m_y+1]);
               placedFigured.append(areaMap[m_x+1][m_y+1]);
               placedFigured.append(areaMap[m_x+2][m_y+1]);
               placedFigured.append(areaMap[m_x+1][m_y]);
               break;
    case LEFT:  areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
                areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y+1]=new PlacedFigure(m_x+2,m_y+1,m_col,m_sharedData);
                areaMap[m_x+2][m_y+2]=new PlacedFigure(m_x+2,m_y+2,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x+2][m_y]);
                placedFigured.append(areaMap[m_x+1][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y+1]);
                placedFigured.append(areaMap[m_x+2][m_y+2]);
                break;
    case RIGHT: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x][m_y+2]=new PlacedFigure(m_x,m_y+2,m_col,m_sharedData);
                areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x][m_y+2]);
                placedFigured.append(areaMap[m_x+1][m_y+1]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }
}

bool TeeWeeObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case UP: ret = areaMap[m_x][m_y] || areaMap[m_x+1][m_y] || areaMap[m_x+2][m_y] || areaMap[m_x+1][m_y+1];
             break;
    case DOWN: ret = areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1] || areaMap[m_x+1][m_y];
               break;
    case LEFT: ret = areaMap[m_x+2][m_y] || areaMap[m_x+1][m_y+1] || areaMap[m_x+2][m_y+1] || areaMap[m_x+2][m_y+2];
                break;
    case RIGHT: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x][m_y+2] || areaMap[m_x+1][m_y+1];
                break;
    default: break;
    }
    return ret;
}

SmashBoyObject::SmashBoyObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(2*step,0));
    m_polygon.append(QPointF(2*step,2*step));
    m_polygon.append(QPointF(0,2*step));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::yellow;
}

void SmashBoyObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void SmashBoyObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
    areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
    areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
    areaMap[m_x+1][m_y+1]=new PlacedFigure(m_x+1,m_y+1,m_col,m_sharedData);
    placedFigured.append(areaMap[m_x][m_y]);
    placedFigured.append(areaMap[m_x][m_y+1]);
    placedFigured.append(areaMap[m_x+1][m_y]);
    placedFigured.append(areaMap[m_x+1][m_y+1]);

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }
}

bool SmashBoyObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x+1][m_y] || areaMap[m_x+1][m_y+1];
    return ret;
}

HeroObject::HeroObject(int x, int y, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(4*step,0));
    m_polygon.append(QPointF(4*step,step));
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(0,0));
    setPos(x*step,y*step);
    m_col = Qt::cyan;
}

void HeroObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
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

void HeroObject::fillAreaMap(QVector<QVector<PlacedFigure *> > &areaMap)
{
    QList <PlacedFigure *> placedFigured;
    switch(m_currentTransformation) {
    case UP: ;
    case DOWN: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
               areaMap[m_x+1][m_y]=new PlacedFigure(m_x+1,m_y,m_col,m_sharedData);
               areaMap[m_x+2][m_y]=new PlacedFigure(m_x+2,m_y,m_col,m_sharedData);
               areaMap[m_x+3][m_y]=new PlacedFigure(m_x+3,m_y,m_col,m_sharedData);
               placedFigured.append(areaMap[m_x][m_y]);
               placedFigured.append(areaMap[m_x+1][m_y]);
               placedFigured.append(areaMap[m_x+2][m_y]);
               placedFigured.append(areaMap[m_x+3][m_y]);
               break;
    case LEFT:areaMap[m_x+3][m_y]=new PlacedFigure(m_x+3,m_y,m_col,m_sharedData);
              areaMap[m_x+3][m_y+1]=new PlacedFigure(m_x+3,m_y+1,m_col,m_sharedData);
              areaMap[m_x+3][m_y+2]=new PlacedFigure(m_x+3,m_y+2,m_col,m_sharedData);
              areaMap[m_x+3][m_y+3]=new PlacedFigure(m_x+3,m_y+3,m_col,m_sharedData);
              placedFigured.append(areaMap[m_x+3][m_y]);
              placedFigured.append(areaMap[m_x+3][m_y+1]);
              placedFigured.append(areaMap[m_x+3][m_y+2]);
              placedFigured.append(areaMap[m_x+3][m_y+3]);
              break;
    case RIGHT: areaMap[m_x][m_y]=new PlacedFigure(m_x,m_y,m_col,m_sharedData);
                areaMap[m_x][m_y+1]=new PlacedFigure(m_x,m_y+1,m_col,m_sharedData);
                areaMap[m_x][m_y+2]=new PlacedFigure(m_x,m_y+2,m_col,m_sharedData);
                areaMap[m_x][m_y+3]=new PlacedFigure(m_x,m_y+3,m_col,m_sharedData);
                placedFigured.append(areaMap[m_x][m_y]);
                placedFigured.append(areaMap[m_x][m_y+1]);
                placedFigured.append(areaMap[m_x][m_y+2]);
                placedFigured.append(areaMap[m_x][m_y+3]);
                break;
    default: break;
    }

    if(!m_sharedData || !m_sharedData->viewer())
        return;

    for(PlacedFigure * it: placedFigured) {
        m_sharedData->viewer()->scene()->addItem(it);
    }
}

bool HeroObject::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    bool ret=false;
    switch(m_currentTransformation) {
    case UP: ;
    case DOWN: ret = areaMap[m_x][m_y] || areaMap[m_x+1][m_y] || areaMap[m_x+2][m_y] || areaMap[m_x+3][m_y];
               break;
    case LEFT: ret = areaMap[m_x+3][m_y] || areaMap[m_x+3][m_y+1] || areaMap[m_x+3][m_y+2] || areaMap[m_x+3][m_y+2];
               break;
    case RIGHT: ret = areaMap[m_x][m_y] || areaMap[m_x][m_y+1] || areaMap[m_x][m_y+2] || areaMap[m_x][m_y+2];
                break;
    default: break;
    }
    return ret;
}


ScoreLevelItem::ScoreLevelItem(qreal x1, qreal y1, qreal x2, qreal y2, QString label,bool isScore, SharedData *data):m_sharedData(data),m_label(label),m_num(0),m_isScore(isScore)
{
    m_polygon.append(QPointF(x1,y1));
    m_polygon.append(QPointF(x1,y2));
    m_polygon.append(QPointF(x2,y2));
    m_polygon.append(QPointF(x2,y1));
    m_polygon.append(QPointF(x1,y1));

    m_text = new QGraphicsSimpleTextItem(this);
    m_text->setBrush(QBrush(Qt::darkGray,Qt::Dense1Pattern));
    m_text->setFont(QFont("Arial",16,QFont::Bold));
    if(m_isScore) {
        m_text->setText(QString("%1 000000000").arg(m_label));
    } else {
        m_label.append("               ");
        m_text->setText(QString("%1 00").arg(m_label));
    }
    m_text->setPos(x1+12,y1+5);
    QTransform t;
    t.scale(1,-1);
    m_text->setTransform(t);
}

void ScoreLevelItem::addScore(int num)
{
    m_num+=num;
    num=m_num;
    QString numStr;
    for(int i =0;i<9;++i) {
        int n=num%10;
        numStr.prepend(QString("%1").arg(n));
        num/=10;
    }
    m_text->setText(QString("%1 %2").arg(m_label).arg(numStr));
}

void ScoreLevelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    painter->setPen(pen);
//    painter->drawPolygon(m_polygon);

    qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (!qFuzzyCompare(1/lod, m_text->scale())) {
        m_text->setScale(1/lod);
    }
}

NextItemsArea::NextItemsArea(qreal x1, qreal y1, qreal x2, qreal y2, SharedData *data):m_sharedData(data)
{
    m_polygon.append(QPointF(x1,y1));
    m_polygon.append(QPointF(x1,y2));
    m_polygon.append(QPointF(x2,y2));
    m_polygon.append(QPointF(x2,y1));
    m_polygon.append(QPointF(x1,y1));

}

void NextItemsArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawPolygon(m_polygon);
}

TetrisFigure::TetrisFigure(int x, int y, SharedData *data):m_sharedData(data),m_x(x),m_y(y),m_currentTransformation(UP)
{

}

void TetrisFigure::setNewPos(int x, int y)
{
    int step = m_sharedData->globalSize();
    setPos(x*step,y*step);
    m_x=x;
    m_y=y;

}

PlacedFigure::PlacedFigure(int x, int y, QColor col, SharedData *data):TetrisFigure(x,y,data)
{
    setZValue(10000);
    int step = m_sharedData->globalSize();
    m_polygon.clear();
    m_polygon.append(QPointF(0,0));
    m_polygon.append(QPointF(0,step));
    m_polygon.append(QPointF(step,step));
    m_polygon.append(QPointF(step,0));
    m_currentTransformation = UP;
    setPos(x*step,y*step);
    m_col = col;
}

void PlacedFigure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setCosmetic(true);
    pen.setColor(Qt::white);
    pen.setWidth(2);
    QBrush br(m_col,Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(br);
    painter->drawPolygon(m_polygon);
}

void PlacedFigure::fillAreaMap(QVector<QVector<PlacedFigure*> > &areaMap)
{
    return;
}

bool PlacedFigure::isIntersect(QVector<QVector<PlacedFigure *> > &areaMap)
{
    return false;
}
