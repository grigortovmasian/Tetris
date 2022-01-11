#include "shareddata.h"
#include "gameobjects.h"

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
