#include "shareddata.h"
#include "gameobjects.h"
#include "tetrisviewer.h"

SharedData::SharedData()
{

}

GameAreaGItem *SharedData::gameArea() const
{
    return m_gameArea;
}

void SharedData::setGameArea(GameAreaGItem *gameArea)
{
    m_gameArea = gameArea;
}

int SharedData::globalSize() const
{
    return m_globalSize;
}

void SharedData::setGlobalSize(const int &globalSize)
{
    m_globalSize = globalSize;
}

TetrisViewer *SharedData::viewer() const
{
    return m_viewer;
}

void SharedData::setViewer(TetrisViewer *viewer)
{
    m_viewer = viewer;
}

ScoreLevelItem *SharedData::score() const
{
    return m_score;
}

void SharedData::setScore(ScoreLevelItem *score)
{
    m_score = score;
}

ScoreLevelItem *SharedData::level() const
{
    return m_level;
}

void SharedData::setLevel(ScoreLevelItem *level)
{
    m_level = level;
}

NextItemsArea *SharedData::getNextItemArea() const
{
    return nextItemArea;
}

void SharedData::setNextItemArea(NextItemsArea *value)
{
    nextItemArea = value;
}
