#ifndef TETRISVIEWER_H
#define TETRISVIEWER_H

#include <QObject>
#include <QGraphicsView>


class TetrisScene;
class SharedData;

class TetrisViewer : public QGraphicsView
{
    Q_OBJECT

public:
    TetrisViewer(SharedData * data);
    ~TetrisViewer() {};
private:
    TetrisScene *m_scene;
    SharedData *m_sharedData;
};

#endif // TETRISVIEWER_H
