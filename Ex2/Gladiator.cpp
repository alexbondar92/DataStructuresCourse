#include "Gladiator.h"


//Gladiator::Gladiator(){
//
//}

Gladiator::Gladiator(int Id, int score, int group){
    this->ID = Id;
    this->Score = score;
    this->trainingGroupID = group;
}

//Gladiator::Gladiator(const Gladiator& gladi){
//
//}

//Gladiator::~Gladiator(){
//
//}

//Gladiator& Gladiator::operator=(const Gladiator& gladi){
//
//}

bool Gladiator::operator==(const Gladiator& gladi){
    if (gladi.getID() == this->getID()){
        return true;
    } else{
        return false;
    }
}

bool Gladiator::operator>(const Gladiator& gladi){
    if (gladi.getID() > this->getID()){
        return true;
    } else{
        return false;
    }
}

bool Gladiator::operator<(const Gladiator& gladi){
    if (gladi.getID() < this->getID()){
        return true;
    } else{
        return false;
    }
}

int Gladiator::getID() const{
    return this->ID;
}

int Gladiator::getSroce() const{
    return this->Score;
}

int Gladiator::setGroup() const{
    return this->trainingGroupID;
}
