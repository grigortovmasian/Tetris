#include "tetrisviewer.h"
#include "tetrisscene.h"
#include "shareddata.h"

TetrisViewer::TetrisViewer(SharedData *data):m_sharedData(data)
{
    m_scene = new TetrisScene(m_sharedData);
    setScene(m_scene);
//    scale(1,-1);
//    QGraphicsView::fitInView ( m_sharedData->gameArea()->boundingRect(), Qt::KeepAspectRatio );
}
