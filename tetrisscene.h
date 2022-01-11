#ifndef TETRISSCENE_H
#define TETRISSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>

class SharedData;

class TetrisScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TetrisScene(SharedData *data);
    ~TetrisScene() {}
private:
   SharedData  *m_sharedData;
};

#endif // TETRISSCENE_H
