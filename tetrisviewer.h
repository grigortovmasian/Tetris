#ifndef TETRISVIEWER_H
#define TETRISVIEWER_H

#include <QObject>
#include <QGraphicsView>

class TetrisViewer : public QGraphicsView
{
    Q_OBJECT

public:
    TetrisViewer();
    ~TetrisViewer() {};
};

#endif // TETRISVIEWER_H
