//
//  Trainer.cpp
//  DataStructure-wet1
//
#include "Trainer.h"


using namespace DS;

Trainer::Trainer(int ID) : gladi_tree_level(){
    this->ID = ID;
    this->best_gladiator_id = -1;
    this->best_gladiator_level = -1;
}

Trainer& Trainer::operator=(const Trainer& trainer){
    this->ID = trainer.getID();
    this->best_gladiator_id = trainer.best_gladiator_id;
    this->best_gladiator_level = trainer.best_gladiator_level;
    return *this;
}

Trainer::Trainer(const Trainer& trainer) : gladi_tree_level(){
    if (trainer.gladi_tree_level.getSize() != 0){
        assert(1==2);
    }
    this->ID = trainer.getID();
    this->best_gladiator_id = trainer.best_gladiator_id;
    this->best_gladiator_level = trainer.best_gladiator_level;
}

Trainer::~Trainer(){
}

int Trainer::getID() const{
    return this->ID;
}

int Trainer::getGladiatorsNumber(){
    return this->gladi_tree_level.getSize();
}

int Trainer::getBestGladiator(){
    return this->best_gladiator_id;
}

int Trainer::getBestGladiatorLevel(){
    return this->best_gladiator_level;
}

void Trainer::addGladiator(const GladiatorL& gladiator){
    try {
        this->gladi_tree_level.Insert(gladiator);
    } catch(std::bad_alloc){
        throw std::bad_alloc();
    }
    if (this->best_gladiator_level < gladiator.getLevel()){
        this->best_gladiator_level = gladiator.getLevel();
        this->best_gladiator_id = gladiator.getId();
    } else if (this->best_gladiator_level == gladiator.getLevel()){
        if(this->best_gladiator_id > gladiator.getId()){
            this->best_gladiator_level = gladiator.getLevel();
            this->best_gladiator_id = gladiator.getId();
        }
    }
}

void Trainer::removeGladiator(const GladiatorL& gladiator){
    this->gladi_tree_level.Delete(gladiator);
    
    if (gladiator.getId() == this->getBestGladiator()){
        if (this->gladi_tree_level.getSize() != 0){
            this->best_gladiator_id = this->gladi_tree_level.FindMax()->getId();
            this->best_gladiator_level = this->gladi_tree_level.FindMax()->getLevel();
        } else {
            this->best_gladiator_level = -1;
            this->best_gladiator_id = -1;
        }
    }
}

bool Trainer::operator==(const Trainer& trainer){
    if (trainer.getID() == this->getID()){
        return true;
    }
    return false;
}

bool Trainer::operator<(const Trainer& trainer){
    if (this->getID() < trainer.getID()){
        return true;
    }
    return false;
}

bool Trainer::operator>(const Trainer& trainer){
    if (this->getID() > trainer.getID()){
        return true;
    }
    return false;
}

bool Trainer::operator!=(const Trainer& trainer){
    if (trainer.getID() != this->getID()){
        return true;
    }
    return false;
}

void Trainer::updateGladiatorLevel(int gladiator_id, int current_level, int level_increase){
    GladiatorL tmp_gladiator = GladiatorL(gladiator_id, current_level);
    this->gladi_tree_level.Delete(tmp_gladiator);
    tmp_gladiator.setLevel(current_level+level_increase);
    this->gladi_tree_level.Insert(tmp_gladiator);
    
    
    
    if (this->best_gladiator_level < tmp_gladiator.getLevel()){
        this->best_gladiator_level = tmp_gladiator.getLevel();
        this->best_gladiator_id = gladiator_id;
    } else if (this->best_gladiator_level == tmp_gladiator.getLevel()){
        if (this->best_gladiator_id > gladiator_id){
            this->best_gladiator_level = tmp_gladiator.getLevel();
            this->best_gladiator_id = gladiator_id;
        }
    }
}

GladiatorL* Trainer::getGladiatorsList(){
    return this->gladi_tree_level.rPreOrder();
}

void Trainer::UpdateLevels(int stimulant_code, int stimulant_factor){
    GladiatorL* gladi_list_level = this->gladi_tree_level.rPreOrder();
    GladiatorL* to_factor = (GladiatorL*)malloc(this->gladi_tree_level.getSize()*sizeof(GladiatorL));
    if (to_factor == NULL){
        throw std::bad_alloc();
    }
    GladiatorL* not_to_factor = (GladiatorL*)malloc(this->gladi_tree_level.getSize()*sizeof(GladiatorL));
    if (not_to_factor == NULL){
        free(to_factor);
        throw std::bad_alloc();
    }
    int factor_i = 0;
    int not_factor_i = 0;
    for( int i=0; i < this->gladi_tree_level.getSize(); i++){
        if (gladi_list_level[i].getId() %stimulant_code == 0){
            to_factor[factor_i] = gladi_list_level[i];
            to_factor[factor_i].setLevel(to_factor[factor_i].getLevel()*stimulant_factor);
            factor_i++;
        } else {
            not_to_factor[not_factor_i] = gladi_list_level[i];
            not_factor_i++;
        }
    }
    int tree_size = this->gladi_tree_level.getSize();
    SplayTree<GladiatorL> T1;
    this->gladi_tree_level.Swap(T1);
    int factor_j = 0;
    int not_factor_j = 0;
    this->best_gladiator_id = -1;
    this->best_gladiator_level = -1;
    for( int i=0; i < tree_size; i++){
        if (factor_j < factor_i && not_factor_j < not_factor_i){
            if (to_factor[factor_j] > not_to_factor[not_factor_j]){
                this->gladi_tree_level.Insert(to_factor[factor_j]);
                factor_j++;
            } else if (to_factor[factor_j] < not_to_factor[not_factor_j]){
                this->gladi_tree_level.Insert(not_to_factor[not_factor_j]);
                not_factor_j++;
            }
        } else if (factor_j < factor_i){
            this->gladi_tree_level.Insert(to_factor[factor_j]);
            factor_j++;
        } else if (not_factor_j < not_factor_i){
            this->gladi_tree_level.Insert(not_to_factor[not_factor_j]);
            not_factor_j++;
        }
    }
    
    if (this->gladi_tree_level.getSize() != 0){
        this->best_gladiator_id = this->gladi_tree_level.FindMax()->getId();
        this->best_gladiator_level = this->gladi_tree_level.FindMax()->getLevel();
    } else {
        this->best_gladiator_id = -1;
        this->best_gladiator_level = -1;
    }
    free(gladi_list_level);
    free(to_factor);
    free(not_to_factor);
}
