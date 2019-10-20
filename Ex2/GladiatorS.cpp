#include "GladiatorS.h"


//GladiatorS::GladiatorS(){
//
//}

GladiatorS::GladiatorS(int Id, int score, int group){
    this->ID = Id;
    this->Score = score;
    this->trainingGroupID = group;
}

//GladiatorS::GladiatorS(const GladiatorS& gladi){
//
//}

//GladiatorS::~GladiatorS(){
//
//}

//GladiatorS& GladiatorS::operator=(const GladiatorS& gladi){
//
//}

bool GladiatorS::operator==(const GladiatorS& gladi){
    if (gladi.getSroce() == this->getSroce() && gladi.getID() == this->getID()){
        return true;
    } else{
        return false;
    }
}

bool GladiatorS::operator>(const GladiatorS& gladi){
    if (gladi.getSroce() > this->getSroce()){
        return true;
    } else if (gladi.getSroce() == this->getSroce() &&
               gladi.getID() > this->getID()){
        return true;
    } else {
        return false;
    }
}

bool GladiatorS::operator<(const GladiatorS& gladi){
    if (gladi.getSroce() < this->getSroce()){
        return true;
    } else if (gladi.getSroce() == this->getSroce() &&
               gladi.getID() < this->getID()){
        return true;
    } else {
        return false;
    }
}

int GladiatorS::getID() const{
    return this->ID;
}

int GladiatorS::getSroce() const{
    return this->Score;
}

int GladiatorS::setGroup() const{
    return this->trainingGroupID;
}
