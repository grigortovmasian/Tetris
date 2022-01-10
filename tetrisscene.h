#ifndef TETRISSCENE_H
#define TETRISSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>

class TetrisScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TetrisScene();
    ~TetrisScene() {}
};

#endif // TETRISSCENE_H
