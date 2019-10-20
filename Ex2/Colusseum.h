//
//  Colusseum.h
//  DS-wet2
//
#ifndef COLUSSEUM_H_
#define COLUSSEUM_H_

#include <stdio.h>
#include "MinHeap.h"
#include "SplayTree.h"
#include "hash.h"
#include "Gladiator.h"
#include "Group.h"

class ColusseumException{};
class ColuSuccess : public ColusseumException{};
class ColuFailure : public ColusseumException{};
class ColuBadAlloc : public ColusseumException{};
class ColuInvalid : public ColusseumException{};

class Colusseum{
    Hash<Group>* Groups;
    MinHeap<int>* MinHeapGroups;
    SplayTree<Gladiator> gladiators;
    
    void removeIfMin(int group_id);
    
public:
    Colusseum();
    
    Colusseum(int n, int *trainingGroupsIDs);
    
    Colusseum(const Colusseum& colu);
    
    ~Colusseum();
    
    Colusseum& operator=(const Colusseum& colu);
    
    void addTrainingGroup(int trainingGroupID);
    
    void addGladiator(int gladiatorID, int score, int trainingGroupID);
    
    void trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    
    int getMinTrainingGroup();
};


#endif /* COLUSSEUM_H_ */
