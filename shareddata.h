#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include <QGraphicsRectItem>

class GameAreaGItem;

class SharedData
{
public:
    SharedData();
    GameAreaGItem *gameArea() const;
    void setGameArea(GameAreaGItem *gameArea);

    int globalSize() const;
    void setGlobalSize(const int &globalSize);

private:
    GameAreaGItem *m_gameArea{nullptr};
    int m_globalSize{30};
};

#endif // SHAREDDATA_H
