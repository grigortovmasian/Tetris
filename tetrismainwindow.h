#ifndef TETRISMAINWINDOW_H
#define TETRISMAINWINDOW_H

#include <QMainWindow>

class TetrisViewer;
class SharedData;
class GameManager;

class TetrisMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TetrisMainWindow(QWidget *parent = nullptr);
    ~TetrisMainWindow(){};
    void createMenuBar();
    void keyPressEvent(QKeyEvent *event);
private slots:
    void startNewGAme();

signals:
private:
    TetrisViewer *m_viewer;
    SharedData *m_sharedData;
    GameManager *m_gameManager;

    void resetScene();
};

#endif // TETRISMAINWINDOW_H
