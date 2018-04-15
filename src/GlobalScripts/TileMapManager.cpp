#include <algorithm>

#include "TileMapManager.h"

TileMapManager::TileMapManager(vector<vector<int> >& aMapTemplate)
    : mapTemplate(aMapTemplate)
{
}

bool TileMapManager::waveAlgo(pair<int, int> aStartVertex, pair<int, int> aEndVertex)
{
    waveZone = mapTemplate;

    if (aStartVertex.first < 0 || aStartVertex.second < 0)
    {
        return false;
    }

    if (static_cast<size_t>(aStartVertex.first) >= waveZone.size()
        || static_cast<size_t>(aStartVertex.second) >= waveZone[0].size())
    {
        return false;
    }

    waveZone[aStartVertex.first][aStartVertex.second] = StartingCell;

    size_t startVertexDistance = 0;
    oldFront.push_back(aStartVertex);

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

        if (std::find(newFront.cbegin(), newFront.cend(), aEndVertex) != newFront.cend())
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

TileMapManager::Path TileMapManager::getPath(pair<int, int> aEndVertex)
{
    auto path = std::make_unique<list<pair<int, int>>>();
    path->push_back(aEndVertex);

    size_t startVertexDistance = waveZone[aEndVertex.first][aEndVertex.second];

    pair<int, int> currentVertex = aEndVertex;

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
        TileMapManager::columnSize * this->getColumnCount(),
        TileMapManager::rowSize * this->getRowCount()
    };
}

pair<int,int> TileMapManager::getPosFromGlobalCoords(Position aGlobalPos) const
{
    auto localPoint = std::make_pair(0, 0);

    if (columnSize > 0 && rowSize > 0)
    {
        if (aGlobalPos.y >= rowSize)
        {
            localPoint.first = aGlobalPos.y/rowSize;
        }

        if (aGlobalPos.x >= columnSize)
        {
            localPoint.second = aGlobalPos.x/columnSize;
        }
    }

    return localPoint;
}

Position TileMapManager::getGlobalPosFromLocalCoords(pair<int,int> aLocalPos) const
{
    if (columnSize > 0 && rowSize > 0)
    {
        return Position(aLocalPos.second * columnSize, aLocalPos.first * rowSize);
    }

    return Position{};
}

bool TileMapManager::IsFilledCell(pair<int, int> aLocalPos) const
{
    return mapTemplate[aLocalPos.first][aLocalPos.second] == FilledCell;
}

bool TileMapManager::IsFilledCell(Position aGlobalPosition) const
{
    return IsFilledCell(getPosFromGlobalCoords(aGlobalPosition));
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
