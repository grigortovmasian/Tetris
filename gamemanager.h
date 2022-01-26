#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include <QTimer>
#include <QVector>
#include "gameobjects.h"
class SharedData;

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(SharedData * data);
    ~GameManager() {}
    TetrisFigure *createRandomOject(int x, int y);
    void startGame();
    void placeNewObject();
    void startTimer(int milisecs);
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotate();//always clockwise
    void pauseGame();
    void resumeGame();

public slots:
    void updateCurrentPosition();
private:
    SharedData *m_sharedData;
    TetrisFigure *m_currentObject{nullptr};
    QList <TetrisFigure*> m_nextItems;
    QTimer m_timer;
    QVector<QVector <bool>> m_canvas;
    const int m_leftBorder=0;
    const int m_rightBoder=11;
    const int m_upBorder=21;
    const int m_downBorder=0;
    bool m_isPaused{false};


    TetrisFigure * createObject(GAMEOBJECTSTYPE type, int x, int y);
    void  setOrientation(TetrisFigure *it,FIGUREORIENTATION site);
    bool validateNewPos(int x,int y);
    bool validateRotation(FIGUREORIENTATION site);
    bool isOnTheBottom();
    void checkFullLines();
    void deleteLine();
    bool isLost();
    void startNewFigure();
};

#endif // GAMEMANAGER_H
