#include "TileMapManager.h"
#include <algorithm>

using std::find;

TileMapManager::TileMapManager(vector<vector<int> >& aMapTemplate)
    : mapTemplate(aMapTemplate)
{
}

bool TileMapManager::waveAlgo(pair<int, int> startVertex, pair<int, int> endVertex)
{
    waveZone = mapTemplate;

    if (startVertex.first >= waveZone.size() || startVertex.second >= waveZone[0].size())
        return false;
    waveZone[startVertex.first][startVertex.second] = StartingCell;

    size_t startVertexDistance = 0;
    oldFront.push_back(startVertex);

    while (!oldFront.empty())
    {
        for(const auto& currentVertex: oldFront)
        {
            TileMapManager::Path vertexNeightbours = getAvaliableNeightbours(
                        currentVertex.first,
                        currentVertex.second);

            for(const auto& neightbour: *vertexNeightbours)
            {
                if (EmptyCell == waveZone[neightbour.first][neightbour.second])
                {
                    waveZone[neightbour.first][neightbour.second] = startVertexDistance + 1;
                    newFront.push_back(neightbour);
                }
            }
        }

        if (newFront.empty())
        {
            oldFront.clear();
            return false;
        }

        if (find(newFront.cbegin(), newFront.cend(), endVertex) != newFront.cend())
        {
            oldFront.clear();
            newFront.clear();
            return true;
        }

        oldFront.clear();

        oldFront.insert(oldFront.end(), newFront.begin(), newFront.end());
        newFront.clear();

        ++startVertexDistance;
    }

    oldFront.clear();
    newFront.clear();

    return false;
}

TileMapManager::Path TileMapManager::getPath(pair<int, int> endVertex)
{
    auto path = std::make_unique<list<pair<int, int>>>();
    path->push_back(endVertex);

    size_t startVertexDistance = waveZone[endVertex.first][endVertex.second];

    pair<int, int> currentVertex = endVertex;

    for(; startVertexDistance > 0; --startVertexDistance)
    {
        TileMapManager::Path vertexNeightbours = getAvaliableNeightbours(currentVertex.first, currentVertex.second);

        for(const auto& neightbour: *vertexNeightbours)
        {
            size_t startPointDistance = waveZone[neightbour.first][neightbour.second];

            if (0 == startPointDistance)
            {
                path->push_back(neightbour);
                break;
            }
            else if (startVertexDistance - 1 == startPointDistance)
            {
                path->push_back(neightbour);
                currentVertex = neightbour;
                break;
            }
        }
    }

    return path;
}



int TileMapManager::getRowCount() const
{
    return mapTemplate.size();
}

int TileMapManager::getColumnCount() const
{
    return mapTemplate[0].size();
}

Size TileMapManager::getCellSize() const
{
    return Size{TileMapManager::columnSize, TileMapManager::rowSize};
}

Size TileMapManager::getMapSize() const
{
    return Size
    {
        TileMapManager::columnSize* this->getColumnCount(),
        TileMapManager::rowSize* this->getRowCount()
    };
}

pair<int,int> TileMapManager::getPosFromGlobalCoords(Position pos)
{
    pair<int, int> localPoint = std::make_pair(0, 0);

    if (columnSize > 0 && rowSize > 0)
    {
        if (pos.y >= rowSize)
        {
            localPoint.first = pos.y/rowSize;
        }

        if (pos.x >= columnSize)
        {
            localPoint.second = pos.x/columnSize;
        }
    }

    return localPoint;
}

Position TileMapManager::getGlobalPosFromLocalCoords(pair<int,int> localPos)
{
    Position globalPos{};

    if (columnSize > 0 && rowSize > 0)
    {
        globalPos.x = localPos.second * columnSize;
        globalPos.y = localPos.first * rowSize;
    }

    return globalPos;
}

bool TileMapManager::IsFilledCell(pair<int, int> localPos) const
{
    return mapTemplate[localPos.first][localPos.second] == FilledCell;
}

TileMapManager::Path TileMapManager::getAvaliableNeightbours(int aRow, int aColumn)
{
    auto neightbourList = std::make_unique<list<pair<int, int>>>();

    int rowCount = getRowCount();
    int columnCount = getColumnCount();

    if (aRow + 1 < rowCount && waveZone[aRow + 1][aColumn] != FilledCell)
        neightbourList->push_front(std::make_pair(aRow + 1, aColumn));

    if (aRow > 0 && waveZone[aRow - 1][aColumn] != FilledCell)
        neightbourList->push_front(std::make_pair(aRow - 1, aColumn));

    if (aColumn + 1 < columnCount && waveZone[aRow][aColumn + 1] != FilledCell)
        neightbourList->push_front(std::make_pair(aRow, aColumn + 1));

    if (aColumn > 0 && waveZone[aRow][aColumn - 1] != FilledCell)
        neightbourList->push_front(std::make_pair(aRow, aColumn - 1));

    return neightbourList;
}
