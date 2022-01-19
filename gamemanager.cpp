#include "gamemanager.h"
#include "shareddata.h"
#include <QDebug>

GameManager::GameManager(SharedData *data):m_sharedData(data)
{

}

TetrisFigure *GameManager::createObject(GAMEOBJECTSTYPE type)
{
    TetrisFigure *it=nullptr;
    switch (type) {
    case ORANGE_RICKY: it = new OrangeRickyObject(0,0,m_sharedData); break;
    case BLUE_RICKY: it = new BlueRickyObject(0,0,m_sharedData); break;
    case CLEVELAND_Z: it = new CleveleandZObject(0,0,m_sharedData); break;
    case RHODE_ISLAND_Z: it = new RhodeIslandZObject(0,0,m_sharedData); break;
    case HERO: it = new TeeWeeObject(0,0,m_sharedData); break;
    case TEEWEE: it = new SmashBoyObject(0,0,m_sharedData); break;
    case SMASHBOY: it = new HeroObject(0,0,m_sharedData); break;
    default: break;
    }
    return it;
}

void GameManager::setOrientation(TetrisFigure *it, FIGUREORIENTATION site)
{
    if(!it)
        return;
    switch(site){
    case LEFT: it->setRotation(-90); break;
    case RIGHT:it->setRotation(+90); break;
    case DOWN: it->setRotation(180); break;
    case UP: break;
    default: break;

    }
}

TetrisFigure *GameManager::createRandomOject()
{
    int figureCount=7,orientationCount=4;
    int figure = qrand() % figureCount;
    int orientation = qrand() % orientationCount;
    TetrisFigure * it=createObject((GAMEOBJECTSTYPE)figure);
    if(!it)
        return it;
    setOrientation(it,FIGUREORIENTATION(orientation));
    return it;

}
