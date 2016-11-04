#include "TileMapManager.h"
#include <algorithm>
using std::find;

TileMapManager::TileMapManager(vector<vector<int> > &aMapTemplate)
    :mapTemplate(aMapTemplate)
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
        for(auto currentVertex: oldFront)
        {
            TileMapManager::Path vertexNeightbours = getAvaliableNeightbours(currentVertex.first, currentVertex.second);

            if (!vertexNeightbours->empty())
                 for(auto neightbour: *vertexNeightbours)
                    if (EmptyCell == waveZone[neightbour.first][neightbour.second])
                    {
                        waveZone[neightbour.first][neightbour.second] = startVertexDistance + 1;
                        newFront.push_back(neightbour);
                    }
        }

        if (newFront.empty())
            return false;

        if (find(newFront.begin(), newFront.end(), endVertex) != newFront.end())
        {
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

    for(;startVertexDistance > 0; --startVertexDistance)
    {
        TileMapManager::Path vertexNeightbours = getAvaliableNeightbours(currentVertex.first, currentVertex.second);

        if (!vertexNeightbours->empty())
             for(auto neightbour: *vertexNeightbours)
             {
                 size_t startPointDistance = waveZone[neightbour.first][neightbour.second];

                 if (0 == startPointDistance)
                 {
                     path->push_back(neightbour);
                     break;
                 }
                 else
                     if (startVertexDistance - 1 == startPointDistance)
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



pair<int,int> TileMapManager::getPosFromGlobalCoords(SDL_Point pos)
{
    pair<int, int> localPoint = std::make_pair(0, 0);
    if (columnSize > 0 && rowSize > 0)
    {
        if (pos.x >= columnSize)
        localPoint.first = pos.x/columnSize + (pos.x % columnSize == 0) - 1;
        if (pos.y >= rowSize)
        localPoint.second = pos.y/rowSize + (pos.x % rowSize == 0) - 1;
    }
    return localPoint;
}

SDL_Point TileMapManager::getGlobalPosFromLocalCoords(pair<int,int> localPos)
{
    SDL_Point globalPos = {0,0};
    if (columnSize > 0 && rowSize > 0)
    {
            globalPos.x = localPos.first*columnSize;
            globalPos.y = (localPos.second + 1)*rowSize;
    }
    return globalPos;
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
