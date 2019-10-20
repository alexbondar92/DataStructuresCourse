//
//  Colusseum.cpp
//  DS-wet2
//

#include "Colusseum.h"
#include <assert.h>


//Colusseum::Colusseum();

Colusseum::Colusseum(int n, int *trainingGroupsIDs){
    assert(2 <= n);
    try{
        this->MinHeapGroups = new MinHeap<int>(trainingGroupsIDs, n);
        this->Groups = new Hash<Group>(n);
    } catch (std::bad_alloc){
        throw ColuBadAlloc();
    }
    for (int i=0; i< n; i++) {
        try{
            Group* tmp_group = new Group(trainingGroupsIDs[i]);
            this->Groups->HashInsertElement(tmp_group, trainingGroupsIDs[i]);
        } catch (std::bad_alloc){
            throw ColuBadAlloc();
        }
    }
}

Colusseum::~Colusseum(){
    delete this->MinHeapGroups;
    delete this->Groups;
//    this->Groups.DeleteAll();
}

//Colusseum::Colusseum(const Colusseum::Colusseum& colu);
//
//Colusseum& Colusseum::operator=(const Colusseum& colu);
//

void Colusseum::addTrainingGroup(int trainingGroupID){
    assert(0 <= trainingGroupID);
    
    if (this->Groups->HashFindElement(trainingGroupID) != NULL) {
        throw ColuFailure();
    }
    
    try{
        this->MinHeapGroups->Insert(trainingGroupID);
        Group* tmp_group = new Group(trainingGroupID);
        this->Groups->HashInsertElement(tmp_group, trainingGroupID);
    } catch (std::bad_alloc){
        throw ColuBadAlloc();
    }
}

void Colusseum::addGladiator(int gladiatorID, int score, int trainingGroupID){
    assert(0 <= trainingGroupID && 0 <= score && 0<= gladiatorID);
    if (this->Groups->HashFindElement(trainingGroupID) == NULL){
        throw ColuFailure();
    }
    if (this->gladiators.Find(Gladiator(gladiatorID, score, trainingGroupID)) != NULL){
        throw ColuFailure();
    }
    try{
        Group* tmp = this->Groups->HashFindElement(trainingGroupID);
        tmp->addGladiator(gladiatorID, score, trainingGroupID);
        this->gladiators.Insert(Gladiator(gladiatorID, score, trainingGroupID));
    } catch (std::bad_alloc) {
        throw ColuBadAlloc();
    }
}

void Colusseum::trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2){
    assert (0 < k1 && 0 < k2 && 0 <= trainingGroup1 && 0 <= trainingGroup2 && trainingGroup1 != trainingGroup2);
    Group* g1 = this->Groups->HashFindElement(trainingGroup1);
    Group* g2 = this->Groups->HashFindElement(trainingGroup2);
    if (g1 == NULL || g2 == NULL || g1->isConq() == true || g2->isConq() == true){
        throw ColuFailure();
    }
    int sum1,sum2 = 0;
    try {
        sum1 = g1->getMaxSelect(k1);
        if (sum1 == -1){
            throw ColuFailure();
        }
        sum2 = g2->getMaxSelect(k2);
        if (sum2 == -1 || sum1 == -1){
            throw ColuFailure();
        }
    } catch (RankSplayRankInvalid){
        throw ColuFailure();
    } catch (std::exception){
        throw ColuFailure();
    }
//    if (sum1 == 0 || sum2 == 0){
//        throw ColuFailure();
//    }
    if (sum1 == sum2){
        if (trainingGroup1 < trainingGroup2){
            g2->setConq(true);
            this->removeIfMin(trainingGroup2);
        } else{
            g1->setConq(true);
            this->removeIfMin(trainingGroup1);
        }
    } else if (sum1 > sum2){
        g2->setConq(true);
        this->removeIfMin(trainingGroup2);
    } else if (sum2 > sum1){
        g1->setConq(true);
        this->removeIfMin(trainingGroup1);
    }
}

int Colusseum::getMinTrainingGroup(){
    return this->MinHeapGroups->FindMin();
}

void Colusseum::removeIfMin(int group_id){
    if (this->MinHeapGroups->FindMin() == group_id){
        this->MinHeapGroups->DelMin();
        int tmp_min;
        try {
            tmp_min = this->MinHeapGroups->FindMin();
        } catch (EmptyHeap) {
            return;
        }
        while (this->Groups->HashFindElement(tmp_min)->isConq() != false){
            this->MinHeapGroups->DelMin();
            try {
                tmp_min = this->MinHeapGroups->FindMin();
            } catch (EmptyHeap) {
                return;
            }
        }
    }
}
