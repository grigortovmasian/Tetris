#include "gamemanager.h"
#include "shareddata.h"
#include "tetrisviewer.h"
#include <QDebug>

GameManager::GameManager(SharedData *data):m_sharedData(data)
{

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateCurrentPosition()));
}

TetrisFigure *GameManager::createObject(GAMEOBJECTSTYPE type,int x,int y)
{
    TetrisFigure *it=nullptr;
    switch (type) {
    case ORANGE_RICKY: it = new OrangeRickyObject(x,y,m_sharedData); break;
    case BLUE_RICKY: it = new BlueRickyObject(x,y,m_sharedData); break;
    case CLEVELAND_Z: it = new CleveleandZObject(x,y,m_sharedData); break;
    case RHODE_ISLAND_Z: it = new RhodeIslandZObject(x,y,m_sharedData); break;
    case TEEWEE: it = new TeeWeeObject(x,y,m_sharedData); break;
    case SMASHBOY: it = new SmashBoyObject(x,y,m_sharedData); break;
    case HERO: it = new HeroObject(x,y,m_sharedData); break;
    default: break;
    }
    return it;
}

void GameManager::setOrientation(TetrisFigure *it, FIGUREORIENTATION site)
{
    if(!it)
        return;
    QTransform t;
    it->setTransform(t);
    qreal w = it->boundingRect().width();
    qreal h = it->boundingRect().height();
    switch(site){
    case LEFT: t.rotate(90).translate(0,-w);  break;
    case RIGHT: t.rotate(-90).translate(-w,0);  break;
    case DOWN: t.rotate(180).translate(-w,-h);  break;
    case UP: break;
    default: break;
    }
    it->setNewRotation(site);
    it->setTransform(t);
}

bool GameManager::validateNewPos(int x, int y)
{
    if(!m_currentObject)
        return false;
    bool ret=false;
    int oldX = m_currentObject->getXPos();
    int oldY = m_currentObject->getYPos();
    m_currentObject->setNewPos(x,y);
    qreal step = m_sharedData->globalSize();
    QRectF rect=m_currentObject->mapRectToScene(m_currentObject->boundingRect());
    qreal maxX= qMax(rect.bottomLeft().x(), qMax(rect.bottomRight().x(),rect.topLeft().x()));
    qreal minX= qMin(rect.bottomLeft().x(), qMin(rect.bottomRight().x(),rect.topLeft().x()));
    qreal minY= qMin(rect.bottomLeft().y(), qMin(rect.bottomRight().y(),rect.topLeft().y()));
//    qreal maxY= qMax(m_currentObject->boundingRect().bottomLeft().x(), qMax(m_currentObject->boundingRect().bottomRight().x(),m_currentObject->boundingRect().topLeft().x()));
    if(minX<0 || minY<0 || maxX>step*11)
        ret=false;
    else
        ret =true;
    if(ret) {
        ret = !m_currentObject->isIntersect(m_canvas);
    }

    m_currentObject->setNewPos(oldX,oldY);
    return ret;
}

bool GameManager::validateRotation(FIGUREORIENTATION site)
{
    if(!m_currentObject)
        return false;
    bool ret=false;
    qreal step = m_sharedData->globalSize();
    FIGUREORIENTATION oldORient=m_currentObject->getRotation();
    setOrientation(m_currentObject,site);
    QRectF rect=m_currentObject->mapRectToScene(m_currentObject->boundingRect());
    qreal maxX= qMax(rect.bottomLeft().x(), qMax(rect.bottomRight().x(),rect.topLeft().x()));
    qreal minX= qMin(rect.bottomLeft().x(), qMin(rect.bottomRight().x(),rect.topLeft().x()));
    qreal minY= qMin(rect.bottomLeft().y(), qMin(rect.bottomRight().y(),rect.topLeft().y()));
//    qreal maxY= qMax(m_currentObject->boundingRect().bottomLeft().x(), qMax(m_currentObject->boundingRect().bottomRight().x(),m_currentObject->boundingRect().topLeft().x()));
    if(minX<0 || minY<0 || maxX>step*11)
        ret=false;
    else
        ret =true;
    if(ret) {
        ret = !m_currentObject->isIntersect(m_canvas);
    }

    setOrientation(m_currentObject,oldORient);
    return ret;
}

void GameManager::checkForFullLinesAndUpdateScore()
{
    bool noChanges = true;
    do {
        noChanges = true;
        for(int y=m_downBorder;y<m_upBorder;++y) {
            bool isFullLine =true;
            for(int x=m_leftBorder;x<m_rightBoder;++x) {
                if(!m_canvas[x][y]) {
                    isFullLine=false;
                    break;
                }
            }
            if(isFullLine) {
                noChanges=false;
                deleteLine(y);
                break;
            }
        }
    } while (!noChanges);
}

void GameManager::deleteLine(int lineToDelete)
{
    qDebug()<<"delete line "<<lineToDelete;
    if(!m_sharedData)
        return;

    for(int y=lineToDelete;y<m_upBorder+1;++y) {
        for(int x=m_leftBorder;x<m_rightBoder;++x) {
            PlacedFigure * it = m_canvas[x][y];
            m_canvas[x][y] = m_canvas[x][y+1];
            if(it && (y == lineToDelete))
                m_sharedData->viewer()->scene()->removeItem(it);
            if(m_canvas[x][y]){
                m_canvas[x][y]->setNewPos(x,y);
            }
        }
    }
    m_sharedData->viewer()->scene()->update();
}

bool GameManager::isLost()
{
    bool ret = false;
    for(int x = m_leftBorder; x<m_rightBoder;++x) {
        if(m_canvas[x][m_upBorder-1]){
            ret=true;
            break;
        }
    }
    return ret;
}

void GameManager::startNewFigure()
{
    if(m_nextItems.isEmpty())
        return;
    m_currentObject = m_nextItems.last();
    placeNewObject();
    m_nextItems.removeLast();
    TetrisFigure *newItem = createRandomOject(0,0);
    m_sharedData->viewer()->scene()->addItem(newItem);
    m_nextItems.insert(0,newItem);
    for(int i=0;i<m_nextItems.size();++i){
       m_nextItems.at(i)->setNewPos(-6,i*5+2);
    }
}

TetrisFigure *GameManager::createRandomOject(int x,int y)
{
    int figureCount=7,orientationCount=4;
    int figure = qrand() % figureCount;
    int orientation = qrand() % orientationCount;
    TetrisFigure * it=createObject((GAMEOBJECTSTYPE)figure,x,y);
    if(!it)
        return it;
    setOrientation(it,FIGUREORIENTATION(orientation));
    return it;

}

void GameManager::startGame()
{
    m_canvas.clear();
    for(int x=m_leftBorder;x<m_rightBoder;++x) {
        QVector <PlacedFigure *> v;
        for(int y=m_downBorder;y<m_upBorder+5;++y) {
            v.push_back(nullptr);
        }
        m_canvas.push_back(v);
    }

    m_nextItems.clear();
    for(int i=0;i<3;++i){
        TetrisFigure *it = createRandomOject(-6,i*5+2);
        m_sharedData->viewer()->scene()->addItem(it);
        m_nextItems.append(it);
    }
    m_currentObject = createRandomOject(0,0);
    m_sharedData->viewer()->scene()->addItem(m_currentObject);
    placeNewObject();
}

void GameManager::placeNewObject()
{
    int randomStartPos = qrand()%5;
    m_currentObject->setNewPos(2+randomStartPos,20);
    startTimer(1000);
}

void GameManager::startTimer(int milisecs)
{
    m_timer.start(milisecs);
}

void GameManager::moveLeft()
{
    if(m_isPaused)
        return;
    if(m_currentObject&&validateNewPos(m_currentObject->getXPos()-1,m_currentObject->getYPos())){
        m_currentObject->setNewPos(m_currentObject->getXPos()-1,m_currentObject->getYPos());
    }
}

void GameManager::moveRight()
{
    if(m_isPaused)
        return;
    if(m_currentObject && validateNewPos(m_currentObject->getXPos()+1,m_currentObject->getYPos())){
        m_currentObject->setNewPos(m_currentObject->getXPos()+1,m_currentObject->getYPos());
    }
}

void GameManager::moveDown()
{
    if(m_isPaused)
        return;
    if(m_currentObject&&validateNewPos(m_currentObject->getXPos(),m_currentObject->getYPos()-1)){
        validateNewPos(m_currentObject->getXPos(),m_currentObject->getYPos()-1);
        m_currentObject->setNewPos(m_currentObject->getXPos(),m_currentObject->getYPos()-1);
    } else {
        m_currentObject->fillAreaMap(m_canvas);
        m_sharedData->viewer()->scene()->removeItem(m_currentObject);
        delete m_currentObject;
        m_currentObject=nullptr;
        if(isLost()) {
            pauseGame();
        } else {
            checkForFullLinesAndUpdateScore();
            startNewFigure();
        }
    }
}

void GameManager::rotate()
{
    if(m_isPaused)
        return;

    if(m_currentObject){
        FIGUREORIENTATION newRot;
        switch(m_currentObject->getRotation()) {
        case LEFT:newRot=UP; ; break;
        case RIGHT:newRot=DOWN; break;
        case DOWN: newRot=LEFT;; break;
        case UP: newRot=RIGHT;break;
        default: break;
        }
        if(validateRotation(newRot)) {
            setOrientation(m_currentObject,newRot);
        }
     }
}

void GameManager::pauseGame()
{
    m_isPaused=true;
}

void GameManager::resumeGame()
{
    m_isPaused=false;
}

void GameManager::updateCurrentPosition()
{
    moveDown();
    startTimer(1000);
}
