#include "Group.h"

//Group::Group(){
//
//}

Group::Group(int Id){
    this->flagConquered = false;
    this->ID = Id;

}

//Group::Group(const Group& group){
//
//}
//
//Group::~Group(){
//
//}
//
//Group::Group& operator=(const Group& group){
//
//}

void Group::addGladiator(int gladiatorID, int score, int trainingGroupID){
    this->gladiators.Insert(GladiatorS(gladiatorID, score, trainingGroupID), score);
}

int Group::getMaxSelect(int k1){
    return this->gladiators.SelectRankBySize(k1);
}

void Group::setConq(bool f){
    this->flagConquered = f;
}

bool Group::isConq() {
    return this->flagConquered;
}
