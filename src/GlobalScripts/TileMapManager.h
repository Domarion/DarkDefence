#pragma once
#include<vector>
#include <list>
#include <utility>
using std::pair;
using std::list;
using std::vector;
#include <SDL_rect.h>
#include <memory>
class TileMapManager
{
    using Path = std::unique_ptr<list<pair<int, int>>>;

public:

    explicit TileMapManager(vector<vector<int> > &aMapTemplate);
    bool waveAlgo(pair<int, int> startVertex, pair<int, int> endVertex);
    Path getPath(pair<int, int> endVertex);
    int getRowCount() const;
    int getColumnCount() const;

     pair<int, int> getPosFromGlobalCoords(SDL_Point pos);

     SDL_Point getGlobalPosFromLocalCoords(pair<int, int> localPos);

     const static int FilledCell = 0;
     const static int StartingCell = -1;
     const static int EmptyCell = 1;

private:

    Path getAvaliableNeightbours(int aRow, int aColumn);
    vector<vector<int> > mapTemplate;
    vector<vector<int> > waveZone;
    list<pair<int, int> > oldFront;
    list<pair<int, int> > newFront;


    const static int columnSize = 48;
    const static int rowSize = 48;
};
