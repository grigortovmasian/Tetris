#include "tetrismainwindow.h"
#include "tetrisviewer.h"
#include "shareddata.h"

TetrisMainWindow::TetrisMainWindow(QWidget *parent) : QMainWindow(parent),m_sharedData(new SharedData)
{
//    setGeometry(200,200,500,700);

    this->setGeometry(100,100,100+768,100+768);
    m_sharedData->setGlobalSize(30);
    m_viewer = new TetrisViewer(m_sharedData);
    setCentralWidget(m_viewer);
    showMaximized();
}
