#pragma once
#include<vector>
#include <list>
#include <utility>
using std::pair;
using std::list;
using std::vector;
#include <SDL_rect.h>
#include <memory>
#include "../GraphicsSystem/newSystem/UtilityStructs.h"

class TileMapManager
{
    using Path = std::unique_ptr<list<pair<int, int>>>;

public:

    explicit TileMapManager(vector<vector<int> > &aMapTemplate);
    bool waveAlgo(pair<int, int> startVertex, pair<int, int> endVertex);
    Path getPath(pair<int, int> endVertex);
    int getRowCount() const;
    int getColumnCount() const;
    Size getCellSize() const;
    Size getMapSize() const;
    pair<int, int> getPosFromGlobalCoords(Position pos);

    Position getGlobalPosFromLocalCoords(pair<int, int> localPos);
    bool IsFilledCell(pair<int, int> localPos) const;
    const constexpr static int FilledCell = -2;
    const constexpr static int StartingCell = 0;
    const constexpr static int EmptyCell = -1;

private:

    Path getAvaliableNeightbours(int aRow, int aColumn);
    vector<vector<int> > mapTemplate;
    vector<vector<int> > waveZone;
    list<pair<int, int> > oldFront;
    list<pair<int, int> > newFront;

    const constexpr static int columnSize = 48;
    const constexpr static int rowSize = 48;

};
