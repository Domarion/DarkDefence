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
    return 0;
}
