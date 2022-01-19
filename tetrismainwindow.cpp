#include "tetrismainwindow.h"
#include "tetrisviewer.h"
#include "shareddata.h"
#include "gamemanager.h"
#include <QAction>
#include <QToolBar>
#include "gameobjects.h"

TetrisMainWindow::TetrisMainWindow(QWidget *parent) : QMainWindow(parent),m_sharedData(new SharedData)
{
//    setGeometry(200,200,500,700);

    this->setGeometry(100,100,100+768,100+768);
    m_sharedData->setGlobalSize(30);
    m_viewer = new TetrisViewer(m_sharedData);
    m_sharedData->setViewer(m_viewer);
    setCentralWidget(m_viewer);
    m_gameManager = new GameManager(m_sharedData);
    createMenuBar();
}

void TetrisMainWindow::createMenuBar()
{

    QToolBar * newGame = addToolBar(tr("Options"));
    //   QAction * resetConstraintsAct = new QAction(QIcon(":/images/Concert_icons/reset_constraints.png"),tr("&Reset Constraints"),this);
    QAction * ng = new QAction(tr("&New Game"),this);
    ng->setShortcuts(QKeySequence::New);
    ng->setStatusTip(tr("New Game"));
    newGame->addAction(ng);
    connect(ng, SIGNAL(triggered()), this, SLOT(startNewGAme()));
}

void TetrisMainWindow::startNewGAme()
{
    //generate random 5 objects with random rotation
    if(!m_gameManager || !m_sharedData)
        return;

    resetScene();
    QList <TetrisFigure *> newItems;
    for(int i=0;i<=5;++i){
        TetrisFigure *it = m_gameManager->createRandomOject();
        newItems.append(it);
    }

//    TetrisFigure *startObject = newItems.first();
//    newItems.removeFirst();
    if(m_sharedData->getNextItemArea()){
        for(TetrisFigure * item : newItems) {
            m_viewer->scene()->addItem(item);
            m_sharedData->getNextItemArea()->addNextItem(item);
        }
    }

}

void TetrisMainWindow::resetScene()
{
    for(QGraphicsItem * it : m_viewer->scene()->items()) {
        TetrisFigure * fig = qgraphicsitem_cast<TetrisFigure*>(it);
        if(fig) {
            m_viewer->scene()->removeItem(fig);;
        }
    }

}

