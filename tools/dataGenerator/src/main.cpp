#include "DataGenerator.h"

int main()
{
    DataGenerator dataGenerator;
    dataGenerator.saveAnim();
    dataGenerator.saveTowerTree();
    dataGenerator.saveItems();
    dataGenerator.saveMission();
    dataGenerator.saveMonsterCollection();

    dataGenerator.saveMineCollection();
    dataGenerator.savePositions();
    return 0;
}
