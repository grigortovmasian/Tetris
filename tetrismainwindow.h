#ifndef TETRISMAINWINDOW_H
#define TETRISMAINWINDOW_H

#include <QMainWindow>

class TetrisViewer;
class SharedData;

class TetrisMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TetrisMainWindow(QWidget *parent = nullptr);
    ~TetrisMainWindow(){};

signals:
private:
    TetrisViewer *m_viewer;
    SharedData * m_sharedData;

};

#endif // TETRISMAINWINDOW_H
