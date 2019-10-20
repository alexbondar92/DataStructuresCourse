//
//  Colosseum.cpp
//  DataStructure-wet1
//
#include "Colosseum.h"
#include <iostream>
#include <stdlib.h>



Colosseum::Colosseum(){
    this->best_gladi_id = -1;
    this->best_gladi_level = -1;
}

Colosseum::~Colosseum(){
    return;
}


void Colosseum::AddTrainer(int trainer_id){
    assert(0 < trainer_id);
    if (this->trainers.Find(Trainer(trainer_id)) !=NULL){
        throw Failure();
    }
    try {
        this->trainers.Insert(Trainer(trainer_id));
    } catch (std::bad_alloc) {
        throw BadAlloc();
    }
}

void Colosseum::buyGladiator(int gladiator_id, int trainer_id, int level){
    assert(0 < trainer_id && 0 < gladiator_id && 0 < level);
    
    Trainer tmp_trainer = Trainer(trainer_id);
    Trainer* ptr_trainer = this->trainers.Find(tmp_trainer);
    if(ptr_trainer == NULL){
        throw Failure();
    }
    Gladiator tmp_gladiator = Gladiator(gladiator_id, level, ptr_trainer);
    if (this->gladiators_id.Find(tmp_gladiator) != NULL){
        throw Failure();
    }
    
    try{
        this->gladiators_id.Insert(tmp_gladiator);
    } catch(std::bad_alloc) {
        throw BadAlloc();
    }
    
    GladiatorL tmp_gladiatorL = GladiatorL(gladiator_id, level);
    try {
        this->gladiators_level.Insert(tmp_gladiatorL);
    } catch (std::bad_alloc) {
        this->gladiators_id.Delete(tmp_gladiator);
        throw BadAlloc();
    }
    
    try {
        ptr_trainer->addGladiator(tmp_gladiatorL);
    } catch (std::bad_alloc) {
        this->gladiators_id.Delete(tmp_gladiator);
        this->gladiators_level.Delete(tmp_gladiatorL);
        throw BadAlloc();
    }
    
    if (this->best_gladi_level < level){
        this->best_gladi_level = level;
        this->best_gladi_id = gladiator_id;
    } else if (this->best_gladi_level == level){
        if(this->best_gladi_id > gladiator_id){
            this->best_gladi_level = level;
            this->best_gladi_id = gladiator_id;
        }
    }
}

void Colosseum::FreeGladiator(int gladiator_id){
    assert(0 < gladiator_id);
    
    Gladiator tmp_gladiator = Gladiator(gladiator_id, 999, NULL);
    Gladiator* gladiator_ptr = this->gladiators_id.Find(tmp_gladiator);
    if (gladiator_ptr == NULL){
        throw Failure();
    }
    tmp_gladiator.setLevel(gladiator_ptr->getLevel());
    tmp_gladiator.setTrainerPtr(gladiator_ptr->getTrainerPtr());
    this->gladiators_id.Delete(tmp_gladiator);
    GladiatorL tmp_gladiatorL = GladiatorL(gladiator_id, tmp_gladiator.getLevel());
    this->gladiators_level.Delete(tmp_gladiatorL);
    tmp_gladiator.getTrainerPtr()->removeGladiator(tmp_gladiatorL);
    
    if (this->best_gladi_id == gladiator_id){
        this->best_gladi_id = -1;
        this->best_gladi_level = -1;
        Trainer* trainers_list;
        try {
            trainers_list = this->trainers.rPreOrder();
        } catch (std::bad_alloc) {
            throw BadAlloc();
        }
        for (int i=0; i<this->trainers.getSize(); i++){
            if (trainers_list[i].getBestGladiatorLevel() > this->best_gladi_level){
                this->best_gladi_level = trainers_list[i].getBestGladiatorLevel();
                this->best_gladi_id = trainers_list[i].getBestGladiator();
            } else if (this->best_gladi_level == trainers_list[i].getBestGladiatorLevel()){
                if (this->best_gladi_id > trainers_list[i].getBestGladiator()){
                    this->best_gladi_level = trainers_list[i].getBestGladiatorLevel();
                    this->best_gladi_id = trainers_list[i].getBestGladiator();
                }
            }
        }
        free(trainers_list);
    }
}

void Colosseum::LevelUp(int gladiator_id, int level_increase){
    assert(0 < gladiator_id && 0 < level_increase);
    
    Gladiator tmp_gladiator = Gladiator(gladiator_id, 999, NULL);
    Gladiator* ptr_gladiator;
    try{
        ptr_gladiator = (this->gladiators_id.Find(tmp_gladiator));
    } catch(SplayNotFound){
        throw Failure();
    }
    if (ptr_gladiator == NULL){
        throw Failure();
    }
    GladiatorL tmp_gladiatorL = GladiatorL(gladiator_id, ptr_gladiator->getLevel());
    this->gladiators_level.Delete(tmp_gladiatorL);
    tmp_gladiatorL.setLevel(tmp_gladiatorL.getLevel()+level_increase);
    this->gladiators_level.Insert(tmp_gladiatorL);
    ptr_gladiator->getTrainerPtr()->updateGladiatorLevel(gladiator_id, ptr_gladiator->getLevel(), level_increase);
    ptr_gladiator->setLevel(ptr_gladiator->getLevel()+level_increase);
    
    if (this->best_gladi_level < ptr_gladiator->getLevel()){
        this->best_gladi_level = ptr_gladiator->getLevel();
        this->best_gladi_id = gladiator_id;
    } else if (this->best_gladi_level == ptr_gladiator->getLevel()){
        if (this->best_gladi_id > gladiator_id){
            this->best_gladi_level = ptr_gladiator->getLevel();
            this->best_gladi_id = gladiator_id;
        }
    }
}

void Colosseum::GetTopGladiator(int trainer_id, int* gladiator_id){
    assert(0 != trainer_id && gladiator_id != NULL);
    if (trainer_id < 0){
        *gladiator_id = this->best_gladi_id;
    } else{
        Trainer* ptr_trainer = this->trainers.Find(Trainer(trainer_id));
        if (0 < trainer_id && ptr_trainer == NULL){
            throw Failure();
        }
        *gladiator_id = ptr_trainer->getBestGladiator();
    }
}

void Colosseum::GetAllGladiatorsByLevel(int trainer_id, int** gladiator,
                                        int* num_of_gladiators){
    assert(trainer_id != 0 && gladiator != NULL && gladiator != NULL &&
           num_of_gladiators != NULL);
    GladiatorL* gladiators_list = NULL;
    if (trainer_id < 0){
        try{
            gladiators_list = this->gladiators_level.rPreOrder();
        } catch(std::bad_alloc){
            throw BadAlloc();
        }
        *num_of_gladiators = this->gladiators_id.getSize();
    } else if (0 < trainer_id){
        Trainer* ptr_trainer = this->trainers.Find(Trainer(trainer_id));
        if (ptr_trainer == NULL){
            throw Failure();
        }
        if (ptr_trainer->getGladiatorsNumber() == 0){
            *num_of_gladiators = 0;
            *gladiator = NULL;
            return;
        }
        try {
            gladiators_list = ptr_trainer->getGladiatorsList();
        } catch (std::bad_alloc) {
            throw BadAlloc();
        }
        *num_of_gladiators = ptr_trainer->getGladiatorsNumber();
    }
    
    *gladiator = (int*)malloc(*num_of_gladiators*sizeof(int));
    if (*gladiator == NULL){
        free(gladiators_list);
        throw BadAlloc();
    }
    for (int i=0; i<*num_of_gladiators; i++){
        (*gladiator)[i] = gladiators_list[i].getId();
    }
    free(gladiators_list);
}

void Colosseum::UpgradeGladiator(int gladiator_id, int upgraded_id){
    assert(0 < gladiator_id && 0 < upgraded_id);
    if (gladiator_id == upgraded_id){
        throw Failure();
    }
    if (this->gladiators_id.Find(Gladiator(gladiator_id, 999, NULL)) == NULL){
        throw Failure();
    }
    if (this->gladiators_id.Find(Gladiator(upgraded_id,999,NULL)) != NULL){
        throw Failure();
    }
    Gladiator tmp_gladiator = *this->gladiators_id.Find(Gladiator(gladiator_id, 999, NULL));
    this->gladiators_id.Delete(tmp_gladiator);
    tmp_gladiator.setId(upgraded_id);
    try {
        this->gladiators_id.Insert(tmp_gladiator);
    } catch (std::bad_alloc) {
        throw BadAlloc();
    }
    GladiatorL tmp_gladiatorL = GladiatorL(gladiator_id, tmp_gladiator.getLevel());
    this->gladiators_level.Delete(tmp_gladiatorL);
    tmp_gladiator.getTrainerPtr()->removeGladiator(tmp_gladiatorL);

    tmp_gladiatorL.setId(upgraded_id);
    try{
        this->gladiators_level.Insert(tmp_gladiatorL);
        tmp_gladiator.getTrainerPtr()->addGladiator(tmp_gladiatorL);
    } catch (std::bad_alloc){
        throw BadAlloc();
    }
    if (this->best_gladi_id == gladiator_id){
        this->best_gladi_id = upgraded_id;
    }
}

void Colosseum::UpdateLevels(int stimulant_code, int stimulant_factor){
    assert(stimulant_code >= 1 && stimulant_factor >= 1);
    if (this->gladiators_id.getSize() == 0){
        return;
    }
    this->UpdateLevelsID(stimulant_code, stimulant_factor);
    this->UpdateLevelsLevel(stimulant_code, stimulant_factor);
    this->UpdateLevelsTrainers(stimulant_code, stimulant_factor);
    if (this->gladiators_id.getSize() != 0){
        this->best_gladi_level = this->gladiators_level.FindMax()->getLevel();
        this->best_gladi_id = this->gladiators_level.FindMax()->getId();
    } else {
        this->best_gladi_level = -1;
        this->best_gladi_id = -1;
    }
}

void Colosseum::UpdateLevelsLevel(int stimulant_code, int stimulant_factor){
    GladiatorL* gladi_list_level = this->gladiators_level.rPreOrder();
    GladiatorL* to_factor = (GladiatorL*)malloc(this->gladiators_level.getSize()*sizeof(GladiatorL));
    if (to_factor == NULL){
        free(gladi_list_level);
        throw BadAlloc();
    }
    GladiatorL* not_to_factor = (GladiatorL*)malloc(this->gladiators_level.getSize()*sizeof(GladiatorL));
    if (not_to_factor == NULL){
        free(gladi_list_level);
        free(to_factor);
        throw BadAlloc();
    }
    int factor_i = 0;
    int not_factor_i = 0;
    for( int i=0; i < this->gladiators_level.getSize(); i++){
        if (gladi_list_level[i].getId() %stimulant_code == 0){
            to_factor[factor_i] = gladi_list_level[i];
            to_factor[factor_i].setLevel(to_factor[factor_i].getLevel()*stimulant_factor);
            factor_i++;
        } else {
            not_to_factor[not_factor_i] = gladi_list_level[i];
            not_factor_i++;
        }
    }
    int tree_size = this->gladiators_level.getSize();
    SplayTree<GladiatorL> T1;
    this->gladiators_level.Swap(T1);
    int factor_j = 0;
    int not_factor_j = 0;
    for( int i=0; i < tree_size; i++){
        if (factor_j < factor_i && not_factor_j < not_factor_i){
            if (to_factor[factor_j] > not_to_factor[not_factor_j]){
                this->gladiators_level.Insert(to_factor[factor_j]);
                factor_j++;
            } else if (to_factor[factor_j] < not_to_factor[not_factor_j]){
                this->gladiators_level.Insert(not_to_factor[not_factor_j]);
                not_factor_j++;
            }
        } else if (factor_j < factor_i){
            this->gladiators_level.Insert(to_factor[factor_j]);
            factor_j++;
        } else if (not_factor_j < not_factor_i){
            this->gladiators_level.Insert(not_to_factor[not_factor_j]);
            not_factor_j++;
        }
    }
    free(gladi_list_level);
    free(to_factor);
    free(not_to_factor);
}


void Colosseum::UpdateLevelsID(int stimulant_code, int stimulant_factor){
    Gladiator* gladi_list_id = this->gladiators_id.rPreOrder();
    Gladiator* to_factor = (Gladiator*)malloc(this->gladiators_id.getSize()*sizeof(Gladiator));
    if (to_factor == NULL){
        throw BadAlloc();
    }
    Gladiator* not_to_factor = (Gladiator*)malloc(this->gladiators_id.getSize()*sizeof(Gladiator));
    if (not_to_factor == NULL){
        free(to_factor);
        free(gladi_list_id);
        throw BadAlloc();
    }
    int factor_i = 0;
    int not_factor_i = 0;
    for( int i=0; i < this->gladiators_id.getSize(); i++){
        if (gladi_list_id[i].getId() %stimulant_code == 0){
            to_factor[factor_i] = gladi_list_id[i];
            to_factor[factor_i].setLevel(to_factor[factor_i].getLevel()*stimulant_factor);
            factor_i++;
        } else {
            not_to_factor[not_factor_i] = gladi_list_id[i];
            not_factor_i++;
        }
    }
    int tree_size = this->gladiators_id.getSize();
    SplayTree<Gladiator> T1;
    this->gladiators_id.Swap(T1);
    int factor_j = 0;
    int not_factor_j = 0;
    for( int i=0; i < tree_size; i++){
        if (factor_j < factor_i && not_factor_j < not_factor_i){
            if (to_factor[factor_j] > not_to_factor[not_factor_j]){
                this->gladiators_id.Insert(to_factor[factor_j]);
                factor_j++;
            } else if (to_factor[factor_j] < not_to_factor[not_factor_j]){
                this->gladiators_id.Insert(not_to_factor[not_factor_j]);
                not_factor_j++;
            }
        } else if (factor_j < factor_i){
            this->gladiators_id.Insert(to_factor[factor_j]);
            factor_j++;
        } else if (not_factor_j < not_factor_i){
            this->gladiators_id.Insert(not_to_factor[not_factor_j]);
            not_factor_j++;
        }
    }
    free(gladi_list_id);
    free(to_factor);
    free(not_to_factor);
}


void Colosseum::UpdateLevelsTrainers(int stimulant_code, int stimulant_factor){
    Trainer** trainers_list = this->trainers.rPreOrderPtr();
    for (int i=0; i < this->trainers.getSize(); i++){
        trainers_list[i]->UpdateLevels(stimulant_code, stimulant_factor);
    }
    free(trainers_list);
}

void Colosseum::Quit(){
    delete this;
}

