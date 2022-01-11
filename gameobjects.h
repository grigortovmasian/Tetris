#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QPolygon>
#include <QGraphicsItem>

class SharedData;

enum GAMEOBJECTSTYPE {
    GAME_AREA,
    ORANGE_RICKY,
    BLUE_RICKY,
    CLEVELAND_Z,
    RHODE_ISLAND_Z,
    HERO,
    TEEWEE,
    SMASHBOY
};

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

class OrangeRickyObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::ORANGE_RICKY};
    OrangeRickyObject(int x,int y,SharedData *data);

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

class BlueRickyObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::BLUE_RICKY};
    BlueRickyObject(int x,int y,SharedData *data);

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

class CleveleandZObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::CLEVELAND_Z};
    CleveleandZObject(int x,int y,SharedData *data);

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

class RhodeIslandZObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    RhodeIslandZObject(int x,int y,SharedData *data);

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

class TeeWeeObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    TeeWeeObject(int x,int y,SharedData *data);

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

class SmashBoyObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    SmashBoyObject(int x,int y,SharedData *data);

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

class HeroObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)

public:
    enum { Type = UserType + GAMEOBJECTSTYPE::RHODE_ISLAND_Z};
    HeroObject(int x,int y,SharedData *data);

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


#endif // GAMEOBJECTS_H
