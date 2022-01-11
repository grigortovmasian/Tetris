#include "tetrisscene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include "shareddata.h"
#include "gameobjects.h"

TetrisScene::TetrisScene(SharedData *data):m_sharedData(data)
{
    //letsAssume tetris size is 10/20
    qreal step=30;
    GameAreaGItem *rect =new GameAreaGItem(step*11,step*21,m_sharedData);
    addItem(rect);
    setBackgroundBrush(QBrush(Qt::black,Qt::SolidPattern));
    m_sharedData->setGameArea(rect);    
    OrangeRickyObject *piece =new OrangeRickyObject(0,0,m_sharedData);
    addItem(piece);
    BlueRickyObject *blue =new BlueRickyObject(3,0,m_sharedData);
    addItem(blue);
    CleveleandZObject *red =new CleveleandZObject(5,0,m_sharedData);
    addItem(red);
    RhodeIslandZObject *green =new RhodeIslandZObject(8,0,m_sharedData);
    addItem(green);
    TeeWeeObject *violet =new TeeWeeObject(0,2,m_sharedData);
    addItem(violet);
    SmashBoyObject *yellow =new SmashBoyObject(3,2,m_sharedData);
    addItem(yellow);
    HeroObject *cyan =new HeroObject(5,2,m_sharedData);
    addItem(cyan);
}
