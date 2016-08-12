#pragma once
#include<vector>
#include <list>
#include <utility>
using std::pair;
using std::list;
using std::vector;
#include <SDL_rect.h>
class TileMapManager
{
public:
    explicit TileMapManager(vector<vector<int> > &aMapTemplate);
    bool waveAlgo(pair<int, int> startVertex, pair<int, int> endVertex);
    list<pair<int, int> > * getPath(pair<int, int> endVertex);
    int getRowCount() const;
    int getColumnCount() const;

     pair<int, int> getPosFromGlobalCoords(SDL_Point pos);

     SDL_Point getGlobalPosFromLocalCoords(pair<int, int> localPos);


private:

    list<pair<int, int> >* getAvaliableNeightbours(int aRow, int aColumn);
    vector<vector<int> > mapTemplate;
    vector<vector<int> > waveZone;
    list<pair<int, int> > oldFront;
    list<pair<int, int> > newFront;

    const static int FilledCell = -2;
    const static int StartingCell = 0;
    const static int EmptyCell = -1;

    const static int columnSize = 80;
    const static int rowSize = 80;
};
