#include "tetrismainwindow.h"
#include "tetrisviewer.h"
#include "shareddata.h"
#include "gamemanager.h"
#include <QAction>
#include <QToolBar>
#include "gameobjects.h"
#include <QDebug>
#include <QMessageBox>

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
    setFocus();
    setWindowIcon(QIcon(QString::fromUtf8(":/tetrisLogo.jpg")));
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

void TetrisMainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    if(!m_gameManager)
        return;
    switch (event->key()) {
    case Qt::Key_Left: m_gameManager->moveLeft(); break;
    case Qt::Key_Right: m_gameManager->moveRight(); break;
    case Qt::Key_Down: m_gameManager->moveDown(); break;
    case Qt::Key_Space: m_gameManager->rotate(); break;
    case Qt::Key_Escape: m_gameManager->pauseGame();
        auto answer = QMessageBox::information(this, "Paused", "Click Ok to continue?", QMessageBox::Ok);
        if (QMessageBox::Ok == answer)
        {
            m_gameManager->resumeGame();
        }
    }
}

void TetrisMainWindow::startNewGAme()
{
    //generate random 5 objects with random rotation
    if(!m_gameManager)
        return;

    resetScene();
    m_gameManager->startGame();
    return;
}

void TetrisMainWindow::resetScene()
{
    for(QGraphicsItem * it : m_viewer->scene()->items()) {
        TetrisFigure * fig = qgraphicsitem_cast<TetrisFigure*>(it);
        if(fig) {
            m_viewer->scene()->removeItem(fig);
        }
    }

}

