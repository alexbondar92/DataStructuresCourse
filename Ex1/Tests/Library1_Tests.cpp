#include <iostream>
#include "assert.h"
#include "library1.h"
#include <cstdlib>


bool testAddTrainer(void *DS){
    assert(AddTrainer(DS,1)==SUCCESS);
    assert(AddTrainer(DS,2)==SUCCESS);
    assert(AddTrainer(DS,3)==SUCCESS);
    assert(AddTrainer(NULL,1)==INVALID_INPUT);
    assert(AddTrainer(DS,-1)==INVALID_INPUT);
    assert(AddTrainer(DS,1)==FAILURE);
    assert(AddTrainer(DS,2)==FAILURE);
    assert(AddTrainer(DS,3)==FAILURE);
    std::cout<< "testAddTrainer : success" << std::endl;
    return true;
}

bool testBuyGladiator(void *DS){
    assert(BuyGladiator(NULL,1,1,1)==INVALID_INPUT);
    assert(BuyGladiator(DS,-1,1,1)==INVALID_INPUT);
    assert(BuyGladiator(DS,1,-1,1)==INVALID_INPUT);
    assert(BuyGladiator(DS,1,1,-1)==INVALID_INPUT);
    assert(BuyGladiator(DS,100,1,20)==SUCCESS);
    assert(BuyGladiator(DS,101,1,20)==SUCCESS);
    assert(BuyGladiator(DS,102,1,20)==SUCCESS);
    assert(BuyGladiator(DS,103,1,20)==SUCCESS);
    assert(BuyGladiator(DS,104,1,20)==SUCCESS);
    assert(BuyGladiator(DS,200,2,20)==SUCCESS);
    assert(BuyGladiator(DS,201,2,20)==SUCCESS);
    assert(BuyGladiator(DS,202,2,20)==SUCCESS);
    assert(BuyGladiator(DS,203,2,20)==SUCCESS);
    assert(BuyGladiator(DS,204,2,20)==SUCCESS);
    assert(BuyGladiator(DS,100,1,20)==FAILURE);
    assert(BuyGladiator(DS,200,1,20)==FAILURE);
    assert(BuyGladiator(DS,101,1,20)==FAILURE);
    assert(BuyGladiator(DS,100,5,20)==FAILURE);
    std::cout<< "testBuyGladiator : success" << std::endl;
    return true;
}

bool testFreeGladiator(void *DS){
    assert(FreeGladiator(NULL,1)==INVALID_INPUT);
    assert(FreeGladiator(DS,0)==INVALID_INPUT);
    assert(FreeGladiator(DS,300)==FAILURE);
    assert(FreeGladiator(DS,102)==SUCCESS);
    assert(FreeGladiator(DS,103)==SUCCESS);
    assert(FreeGladiator(DS,200)==SUCCESS);
    std::cout<< "testFreeGladiator : success" << std::endl;
    return true;
}

bool testLevelUp(void *DS){
    assert(LevelUp(NULL,100,20)==INVALID_INPUT);
    assert(LevelUp(DS,-100,20)==INVALID_INPUT);
    assert(LevelUp(DS,100,0)==INVALID_INPUT);
    assert(LevelUp(DS,100,10)==SUCCESS);
    assert(LevelUp(DS,104,10)==SUCCESS);
    assert(LevelUp(DS,203,40)==SUCCESS);
    assert(LevelUp(DS,300,10)==FAILURE);
    std::cout<< "testLevelUp : success" << std::endl;
    return true;
}

bool testUpgradeGladiator(void *DS, int gladiatorID, int upgradedID);

bool testGetTopGladiator(void *DS, int trainerID, int *gladiatorID);

bool testGetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators, int *numOfGladiator);

bool testUpdateLevels(void *DS, int stimulantCode, int stimulantFactor);

void testQuit(void** DS);

void testFinalTest(void *DS) {
    assert(AddTrainer(DS,1) == SUCCESS); //Trainer 1
    assert(AddTrainer(DS,-2) == INVALID_INPUT);
    assert(AddTrainer(DS,0) == INVALID_INPUT);
    assert(AddTrainer(DS,5) == SUCCESS); //Trainer 5
    assert(AddTrainer(DS,3) == SUCCESS); //Trainer 3
    assert(AddTrainer(DS,3) == FAILURE);

    assert(BuyGladiator(DS,1,1,3) == SUCCESS); //Gladiator ID:1 Trainer:1 Level:3
    assert(BuyGladiator(DS,1,1,5) == FAILURE);
    assert(BuyGladiator(DS,2,4,5) == FAILURE);
    assert(BuyGladiator(DS,-1,-1,2) == INVALID_INPUT);
    assert(BuyGladiator(DS,1,-1,3) == INVALID_INPUT);
    assert(BuyGladiator(DS,-1,3,7) == INVALID_INPUT);
    assert(BuyGladiator(DS,10,5,7) == SUCCESS); //Gladiator ID:10 Trainer:5 Level:7
    assert(BuyGladiator(DS,9,1,4) == SUCCESS); //Gladiator ID:9 Trainer:1 Level:4
    assert(BuyGladiator(DS,12,1,4) == SUCCESS); //Gladiator ID:12 Trainer:1 Level:4
    assert(BuyGladiator(DS,8,5,3) == SUCCESS); //Gladiator ID:8 Trainer:5 Level:3

    int max=0;
    if(max == -1000) {
        return;
    }
    assert(GetTopGladiator(DS,1,&max) == SUCCESS); //max == 9
    assert(max == 9);
    assert(GetTopGladiator(DS,-1,&max) == SUCCESS); //max == 10
    assert(max == 10);
    assert(GetTopGladiator(DS,0,&max) == INVALID_INPUT);
    assert(GetTopGladiator(DS,4,&max) == FAILURE);
    assert(GetTopGladiator(DS,3,&max) == SUCCESS); //max == -1
    assert(max == -1);

    int* gladiators= NULL;
    int numOfGlad=0;
    if(numOfGlad == -1000) {
        return;
    }
    assert(GetAllGladiatorsByLevel(DS,1,&gladiators,&numOfGlad) == SUCCESS); //gladiators[0] == 9 && gladiators[1] == 12 && gladiators[2] == 1 && numOfGlad == 3
    assert(gladiators[0] == 9 && gladiators[1] == 12 && gladiators[2] == 1 && numOfGlad == 3);
    free(gladiators);
    assert(GetAllGladiatorsByLevel(DS,-1,&gladiators,&numOfGlad) == SUCCESS); //gladiators[0] == 10 && gladiators[1] == 9 && gladiators[2] == 12 && gladiators[3] == 1 && gladiators[4] == 8 && numOfGlad == 5
    assert(gladiators[0] == 10 && gladiators[1] == 9 && gladiators[2] == 12 && gladiators[3] == 1 && gladiators[4] == 8 && numOfGlad == 5);
    free(gladiators);
    assert(GetAllGladiatorsByLevel(DS,3,&gladiators,&numOfGlad) == SUCCESS); //gladiators == NULL && numOfGlad == 0
    assert(gladiators == NULL && numOfGlad == 0);
    free(gladiators);
    assert(GetAllGladiatorsByLevel(DS,0,&gladiators,&numOfGlad) == INVALID_INPUT);
    assert(GetAllGladiatorsByLevel(DS,0,&gladiators,&numOfGlad) == INVALID_INPUT);
    assert(GetAllGladiatorsByLevel(DS,5, NULL,&numOfGlad) == INVALID_INPUT);
    assert(GetAllGladiatorsByLevel(DS,5, NULL,&numOfGlad) == INVALID_INPUT);
    assert(GetAllGladiatorsByLevel(DS,8, &gladiators,&numOfGlad) == FAILURE);

    assert(LevelUp(DS,2,2) == FAILURE);
    assert(LevelUp(DS,0,2) == INVALID_INPUT);
    assert(LevelUp(DS,12,-5) == INVALID_INPUT);
    assert(LevelUp(DS,-5,2) == INVALID_INPUT);
    assert(LevelUp(DS,1,0) == INVALID_INPUT);
    assert(LevelUp(DS,1,-5) == INVALID_INPUT);
    assert(LevelUp(DS,9,1) == SUCCESS); //Gladiator ID:9 has Level:5
    assert(GetTopGladiator(DS,1,&max) == SUCCESS); //max=9
    assert(max == 9);
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=10
    assert(max == 10);
    assert(LevelUp(DS,8,5) == SUCCESS); ////Gladiator ID:8 has Level:8
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=8
    assert(max == 8);
    assert(GetTopGladiator(DS,5,&max) == SUCCESS); //max=8
    assert(max == 8);

    assert(UpgradeGladiator(DS,20,-55) == INVALID_INPUT);
    assert(UpgradeGladiator(DS,-1,55) == INVALID_INPUT);
    assert(UpgradeGladiator(DS,0,55) == INVALID_INPUT);
    assert(UpgradeGladiator(DS,1,0) == INVALID_INPUT);
    assert(UpgradeGladiator(DS,20,5) == FAILURE);
    assert(UpgradeGladiator(DS,20,-5) == INVALID_INPUT);
    assert(UpgradeGladiator(DS,9,9) == FAILURE);
    assert(UpgradeGladiator(DS,9,8) == FAILURE);
    assert(UpgradeGladiator(DS,8,5) == SUCCESS); //Gladiator ID:8 has ID:5
    assert(GetTopGladiator(DS,5,&max) == SUCCESS); //max=5
    assert(max == 5);
    assert(GetTopGladiator(DS,-10,&max) == SUCCESS); //max=5
    assert(max == 5);

    assert(FreeGladiator(DS,-5) == INVALID_INPUT);
    assert(FreeGladiator(DS,0) == INVALID_INPUT);
    assert(FreeGladiator(DS,8) == FAILURE);
    assert(FreeGladiator(DS,5) == SUCCESS); //Delete Gladiator ID:5
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=10
    assert(max == 10);
    assert(GetTopGladiator(DS,5,&max) == SUCCESS); //max=10
    assert(max == 10);
    assert(GetAllGladiatorsByLevel(DS,-5,&gladiators,&numOfGlad) == SUCCESS); //gladiators[0] == 10 && gladiators[1] == 9 && gladiators[2] == 12 && gladiators[3] == 1 && numOfGlad == 4
    assert(gladiators[0] == 10 && gladiators[1] == 9 && gladiators[2] == 12 && gladiators[3] == 1 && numOfGlad == 4);
    free(gladiators);

    assert(BuyGladiator(DS,5,5,8) == SUCCESS); ////Gladiator ID:5 Trainer:5 Level:8

    assert(UpdateLevels(DS,0,5) == INVALID_INPUT);
    assert(UpdateLevels(DS,-5,5) == INVALID_INPUT);
    assert(UpdateLevels(DS,5,0) == INVALID_INPUT);
    assert(UpdateLevels(DS,5,-2) == INVALID_INPUT);
    assert(UpdateLevels(DS,12,3) == SUCCESS); //Gladiator ID:12 has Level:12
    assert(GetTopGladiator(DS,1,&max) == SUCCESS); //max=12
    assert(max == 12);
    assert(GetTopGladiator(DS,-1,&max) == SUCCESS); //max=12
    assert(max == 12);
    assert(GetAllGladiatorsByLevel(DS,-1,&gladiators,&numOfGlad) == SUCCESS); //gladiators[0] == 12 && gladiators[1] == 5 && gladiators[2] == 10 && gladiators[3] == 9 && gladiators[4] == 1 && numOfGlad == 5
    assert(gladiators[0] == 12 && gladiators[1] == 5 && gladiators[2] == 10 && gladiators[3] == 9 && gladiators[4] == 1 && numOfGlad == 5);
    free(gladiators);

    assert(FreeGladiator(DS,12) == SUCCESS); //Delete Gladiator ID:12
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=5
    assert(max == 5);
    assert(FreeGladiator(DS,5) == SUCCESS); //Delete Gladiator ID:5
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=10
    assert(max == 10);
    assert(FreeGladiator(DS,9) == SUCCESS); //Delete Gladiator ID:9
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=10
    assert(max == 10);
    assert(FreeGladiator(DS,10) == SUCCESS); //Delete Gladiator ID:10
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=1
    assert(max == 1);
    assert(FreeGladiator(DS,1) == SUCCESS); //Delete Gladiator ID:1
    assert(FreeGladiator(DS,1) == FAILURE);
    assert(FreeGladiator(DS,12) == FAILURE);
    assert(GetTopGladiator(DS,-5,&max) == SUCCESS); //max=-1
    assert(max == -1);

    Quit(NULL);

    Quit(&DS);


    std::cout<< "testFinalTest : success" << std::endl;
}

int main() {
    void* DS=Init();
    testAddTrainer(DS);
    testBuyGladiator(DS);
    testFreeGladiator(DS);
    Quit(&DS);
    void* DS2=Init();
    testFinalTest(DS2);

    return 0;
}


