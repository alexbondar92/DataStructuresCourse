//
//  GladiatorL.cpp
//  DataStructure-wet1
//

#include "GladiatorL.h"
#include <assert.h>
using namespace DS;


GladiatorL::GladiatorL(int ID, int level){
    assert(ID > 0);
    assert(level >0);
    this->Id = ID;
    this->level = level;
}

GladiatorL::GladiatorL(const GladiatorL& gladiator){
    *this = gladiator;
}

int GladiatorL::getId() const{
    return this->Id;
}

int GladiatorL::getLevel() const{
    return this->level;
}

void GladiatorL::setId(int new_Id){
    assert(new_Id > 0);
    this->Id = new_Id;
}

void GladiatorL::setLevel(int new_level){
    assert(new_level > 0);
    this->level = new_level;
}

GladiatorL& GladiatorL::operator=(const GladiatorL& gladiator){
    this->Id = gladiator.getId();
    this->level = gladiator.getLevel();
    return *this;
}

bool GladiatorL::operator==(const GladiatorL& gladi) const{
    if (gladi.getLevel() == this->getLevel() && gladi.getId() == this->getId()){
        return true;
    }
    return false;
}

bool GladiatorL::operator<(const GladiatorL& gladi){
    if (this->getLevel() < gladi.getLevel()){
        return true;
    } else if (gladi.getLevel() == this->getLevel() &&
               this->getId() > gladi.getId()){
        return true;
    }
    return false;
}

bool GladiatorL::operator>(const GladiatorL& gladi){
    if (this->getLevel() > gladi.getLevel()){
        return true;
    } else if (gladi.getLevel() == this->getLevel() &&
               this->getId() < gladi.getId()){
        return true;
    }
    return false;
}

bool GladiatorL::operator!=(const GladiatorL& gladi) const{
    if (!(gladi == *this)){
        return true;
    }
    return false;
}


