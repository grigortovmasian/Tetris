#include "tetrisscene.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include "shareddata.h"
#include "gameobjects.h"

TetrisScene::TetrisScene(SharedData *data):m_sharedData(data)
{
    //letsAssume tetris size is 10/20
    qreal step=30;
    if(m_sharedData) {
        step=m_sharedData->globalSize();
    }
    GameAreaGItem *rect =new GameAreaGItem(step*11,step*21,m_sharedData);
    addItem(rect);
    setBackgroundBrush(QBrush(Qt::black,Qt::SolidPattern));
    m_sharedData->setGameArea(rect);
    createSpace();
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

void TetrisScene::createSpace()
{
    qreal step=30;
    if(m_sharedData) {
        step=m_sharedData->globalSize();
    }
    ScoreLevelItem *score = new ScoreLevelItem(-8*step,20*step,-step,21*step,"SCORE",true,m_sharedData);
    addItem(score);
    if(m_sharedData) {
        m_sharedData->setScore(score);
    }

    ScoreLevelItem *level = new ScoreLevelItem(-8*step,18*step,-step,19*step,"LEVEL",false,m_sharedData);
    addItem(level);
    if(m_sharedData) {
        m_sharedData->setLevel(level);
    }

    NextItemsArea *nextItems = new NextItemsArea(-8*step,0*step,-step,17*step,m_sharedData);
    addItem(nextItems);
    if(m_sharedData) {
        m_sharedData->setNextItemArea(nextItems);
    }
}
