#pragma once

#include <list>
#include <memory>
#include <vector>
#include <utility>

#include <SDL_rect.h>
#include "../GraphicsSystem/newSystem/UtilityStructs.h"

using std::pair;
using std::list;
using std::vector;

class TileMapManager
{
    using Path = std::unique_ptr<list<pair<int, int>>>;

public:

    explicit TileMapManager(vector<vector<int> >& aMapTemplate);

    bool waveAlgo(pair<int, int> aStartVertex, pair<int, int> aEndVertex);
    Path getPath(pair<int, int> aEndVertex);

    int getRowCount() const;
    int getColumnCount() const;
    Size getCellSize() const;
    Size getMapSize() const;

    pair<int, int> getPosFromGlobalCoords(Position aGlobalPos) const;
    Position getGlobalPosFromLocalCoords(pair<int, int> aLocalPos) const;

    bool IsFilledCell(pair<int, int> aLocalPos) const;
    bool IsFilledCell(Position aGlobalPosition) const;

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
