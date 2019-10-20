//
//  Gladiator.cpp
//  DataStructure-wet1
//
#include "Gladiator.h"

using namespace DS;


Gladiator::Gladiator(int ID, int level,Trainer* trainer_ptr){
    assert(ID > 0);
    assert(level >0);
    this->Id = ID;
    this->level = level;
    this->trainer = trainer_ptr;
}

Gladiator::Gladiator(const Gladiator& gladiator){
    *this = gladiator;
}

Gladiator& Gladiator::operator=(const Gladiator& gladiator){
    this->Id = gladiator.getId();
    this->level = gladiator.getLevel();
    this->trainer = gladiator.getTrainerPtr();
    return *this;
}

int Gladiator::getId() const{
    return this->Id;
}

int Gladiator::getLevel() const{
    return this->level;
}

void Gladiator::setId(int new_Id){
    assert(new_Id > 0);
    this->Id = new_Id;
}

void Gladiator::setLevel(int new_level){
    assert(new_level > 0);
    this->level = new_level;
}

void Gladiator::setTrainerPtr(Trainer* trainer){
    this->trainer = trainer;
}

Trainer* Gladiator::getTrainerPtr() const{
    return this->trainer;
}

bool Gladiator::operator==(const Gladiator& gladi){
    if (gladi.getId() == this->getId()){
        return true;
    }
    return false;
}

bool Gladiator::operator<(const Gladiator& gladi){
    if (this->getId() < gladi.getId()){
        return true;
    }
    return false;
}

bool Gladiator::operator>(const Gladiator& gladi){
    if (this->getId() > gladi.getId()){
        return true;
    }
    return false;
}

bool Gladiator::operator!=(const Gladiator& gladi){
    if (gladi.getId() != this->getId()){
        return true;
    }
    return false;
}


