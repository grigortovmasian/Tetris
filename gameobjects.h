#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QPolygon>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QList>

class SharedData;

enum GAMEOBJECTSTYPE {
    ORANGE_RICKY=0,
    BLUE_RICKY,
    CLEVELAND_Z,
    RHODE_ISLAND_Z,
    HERO,
    TEEWEE,
    SMASHBOY,
    SCORELEVEL,
    NEXTITEM,
    GAME_AREA,
    TETRISFIGURE
};

enum FIGUREORIENTATION {
    UP=0,//0
    RIGHT,//+90
    DOWN,//180
    LEFT//-90

};

class TetrisFigure;

class GameAreaGItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::GAME_AREA};
    GameAreaGItem(qreal w,qreal h,SharedData *data);

public:
    QRectF boundingRect() const {
        return m_polygon.boundingRect();
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addPolygon(m_polygon);
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const { return Type; }
    QPolygonF polygon() { return m_polygon; }


private:
    QPolygonF m_polygon;
    SharedData *m_sharedData{nullptr};

};
class NextItemsArea : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::NEXTITEM};
    NextItemsArea(qreal x1, qreal y1, qreal x2, qreal y2, SharedData *data);

public:
    QRectF boundingRect() const {
        return m_polygon.boundingRect();
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addPolygon(m_polygon);
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const { return Type; }
    QPolygonF polygon() { return m_polygon; }
private:
    QPolygonF m_polygon;
    SharedData *m_sharedData{nullptr};

};

class ScoreLevelItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::SCORELEVEL};
    ScoreLevelItem(qreal x1, qreal y1, qreal x2, qreal y2, QString label, bool isScore, SharedData *data);

public:
    QRectF boundingRect() const {
        return m_polygon.boundingRect();
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addPolygon(m_polygon);
        return path;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const { return Type; }
    QPolygonF polygon() { return m_polygon; }


private:
    QPolygonF m_polygon;
    SharedData *m_sharedData{nullptr};
    QGraphicsSimpleTextItem *m_text;
    QString m_label;
    long m_num;
    bool m_isScore;

};

class TetrisFigure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    TetrisFigure(int x, int y,SharedData *data);
public:
    QRectF boundingRect() const {
        return m_polygon.boundingRect();
    }
    QPainterPath shape() const
    {
        QPainterPath path;
        path.addPolygon(m_polygon);
        return path;
    }
    QPolygonF polygon() { return m_polygon; }
    enum { Type = UserType + GAMEOBJECTSTYPE::TETRISFIGURE};
    int type() const { return Type; }
    void setNewPos(int x,int y);
    virtual void fillAreaMap(QVector<QVector <bool>>& areaMap)=0;
    virtual bool isIntersect(QVector<QVector <bool>>& areaMap)=0;
    void setNewRotation(FIGUREORIENTATION site) {
        m_currentTransformation=site;
    }
    FIGUREORIENTATION getRotation() {return m_currentTransformation;}
    int getXPos() {return m_x;}
    int getYPos() {return m_y;}

protected:
    QPolygonF m_polygon;
    SharedData *m_sharedData{nullptr};
    int m_x;
    int m_y;
    FIGUREORIENTATION m_currentTransformation;

};


class OrangeRickyObject : public TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::ORANGE_RICKY};
    OrangeRickyObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};


class BlueRickyObject : public TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::BLUE_RICKY};
    BlueRickyObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};

class CleveleandZObject : public TetrisFigure
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::CLEVELAND_Z};
    CleveleandZObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};

class RhodeIslandZObject : public TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    RhodeIslandZObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};

class TeeWeeObject : public TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    TeeWeeObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};

class SmashBoyObject : public TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    SmashBoyObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};

class HeroObject : public  TetrisFigure
{
public:
//    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    HeroObject(int x,int y,SharedData *data);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    int type() const { return Type; }
    void fillAreaMap(QVector<QVector <bool>>& areaMap);
    bool isIntersect(QVector<QVector <bool>>& areaMap);
};


#endif // GAMEOBJECTS_H
