#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include "gameobjects.h"

class SharedData;

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(SharedData * data);
    ~GameManager() {}
    TetrisFigure *createRandomOject();

private:
    SharedData *m_sharedData;


    TetrisFigure * createObject(GAMEOBJECTSTYPE type);
    void  setOrientation(TetrisFigure *it,FIGUREORIENTATION site);
};

#endif // GAMEMANAGER_H
