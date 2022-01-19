#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include <QGraphicsRectItem>

class GameAreaGItem;
class TetrisViewer;
class ScoreLevelItem;
class NextItemsArea;

class SharedData
{
public:
    SharedData();
    GameAreaGItem *gameArea() const;
    void setGameArea(GameAreaGItem *gameArea);

    int globalSize() const;
    void setGlobalSize(const int &globalSize);

    TetrisViewer *viewer() const;
    void setViewer(TetrisViewer *viewer);

    ScoreLevelItem *score() const;
    void setScore(ScoreLevelItem *score);

    ScoreLevelItem *level() const;
    void setLevel(ScoreLevelItem *level);

    NextItemsArea *getNextItemArea() const;
    void setNextItemArea(NextItemsArea *value);

private:
    GameAreaGItem *m_gameArea{nullptr};
    int m_globalSize{30};
    TetrisViewer *m_viewer{nullptr};
    ScoreLevelItem * m_score;
    ScoreLevelItem *m_level;
    NextItemsArea *nextItemArea;

};

#endif // SHAREDDATA_H
