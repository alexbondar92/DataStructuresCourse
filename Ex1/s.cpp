//
//  library1.cpp
//  DataStructure-wet1
//
#include <stdio.h>
#include "library1.h"
#include "Colosseum.h"

void* Init(){
    try{
        Colosseum* DS = (Colosseum*)new Colosseum();
        return DS;
    } catch (BadAlloc){
      return NULL;
    }
}

StatusType AddTrainer(void *DS, int trainerID){
    if (DS == NULL || trainerID <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Colosseum*)DS)->AddTrainer(trainerID);
    } catch(Failure){
        return FAILURE;
    } catch(BadAlloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType BuyGladiator(void *DS, int gladiatorID, int trainerID, int level){
    if (DS == NULL || gladiatorID <= 0 || trainerID <= 0 || level <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Colosseum*)DS)->buyGladiator(gladiatorID, trainerID, level);
    } catch(Failure){
        return FAILURE;
    } catch(BadAlloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType FreeGladiator(void *DS, int gladiatorID){
    if (DS == NULL || gladiatorID <= 0){
        return INVALID_INPUT;
    }
    
    try {
        ((Colosseum*)DS)->FreeGladiator(gladiatorID);
    } catch (Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType LevelUp(void *DS, int gladiatorID, int levelIncrease){
    if (DS == NULL || gladiatorID <= 0 || levelIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Colosseum*)DS)->LevelUp(gladiatorID, levelIncrease);
    } catch (Failure){
        return FAILURE;
    } catch (BadAlloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType UpgradeGladiator(void *DS, int gladiatorID, int upgradedID){
    if (DS == NULL || gladiatorID <= 0 || upgradedID <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Colosseum*)DS)->UpgradeGladiator(gladiatorID, upgradedID);
    } catch (Failure){
        return FAILURE;
    } catch (BadAlloc){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetTopGladiator(void *DS, int trainerID, int *gladiatorID){
    if (DS == NULL || trainerID == 0 || gladiatorID == NULL){
        return INVALID_INPUT;
    }
    try {
        ((Colosseum*)DS)->GetTopGladiator(trainerID, gladiatorID);
    } catch (BadAlloc) {
        return ALLOCATION_ERROR;
    } catch (Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators, int *numOfGladiator){
    if (DS == NULL || trainerID == 0 || gladiators == NULL || numOfGladiator == NULL){
        return INVALID_INPUT;
    }
    
    try {
        ((Colosseum*)DS)->GetAllGladiatorsByLevel(trainerID, gladiators, numOfGladiator);
    } catch (BadAlloc) {
        return ALLOCATION_ERROR;
    } catch (Failure){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType UpdateLevels(void *DS, int stimulantCode, int stimulantFactor){
    if (DS == NULL || stimulantCode < 1 || stimulantFactor < 1){
        return INVALID_INPUT;
    }
    try {
        ((Colosseum*)DS)->UpdateLevels(stimulantCode, stimulantFactor);
    } catch (BadAlloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if (DS != NULL && *DS != NULL){
        Colosseum* tmp = (Colosseum*)*DS;
        tmp->Quit();
        *DS = NULL;
    }
}

