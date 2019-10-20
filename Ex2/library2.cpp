//
//  library2.cpp
//  DS-wet2
//

#include <stdio.h>
#include "library2.h"
#include "Colusseum.h"

void* init(int n, int *trainingGroupsIDs){
    if (n < 2 || trainingGroupsIDs == NULL){
        return NULL;
    }
    for (int i=0; i<n; i++){
        if (trainingGroupsIDs[i] < 0){
            return NULL;
        }
    }
    Colusseum* DS;
    try{
        DS = new Colusseum(n, trainingGroupsIDs);
    } catch(std::bad_alloc) {
        return NULL;
    } catch (ColuBadAlloc){
        return NULL;
    }
    return DS;
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if (DS == NULL || trainingGroupID < 0){
        return INVALID_INPUT;
    }
    try{
        ((Colusseum*)DS)->addTrainingGroup(trainingGroupID);
    } catch (ColuBadAlloc) {
        return ALLOCATION_ERROR;
    } catch (ColuFailure) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if (DS == NULL || trainingGroup < 0 || score < 0 || gladiatorID < 0){
        return INVALID_INPUT;
    }
    try {
        ((Colusseum*)DS)->addGladiator(gladiatorID, score, trainingGroup);
    } catch (ColuBadAlloc) {
        return ALLOCATION_ERROR;
    } catch (ColuFailure) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (DS == NULL || k1 <=0 || k2 <= 0 || trainingGroup1 < 0 || trainingGroup2 < 0){
        return INVALID_INPUT;
    }
    if (trainingGroup1 == trainingGroup2){
        return FAILURE;
    }
    try {
        ((Colusseum*)DS)->trainingGroupFight(trainingGroup1, trainingGroup2, k1, k2);
    } catch (ColuFailure) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType getMinTrainingGroup(void *DS, int *trainingGroup){
    if (DS == NULL || trainingGroup == NULL){
        return INVALID_INPUT;
    }

    try {
        *trainingGroup = ((Colusseum*)DS)->getMinTrainingGroup();
    } catch (ColuFailure) {
        return FAILURE;
    }
    return SUCCESS;
}

void quit(void** DS){
    if (DS != NULL && *DS != NULL){
        Colusseum* tmp = (Colusseum*)*DS;
        delete  tmp;
    }
    *DS = NULL;
}

