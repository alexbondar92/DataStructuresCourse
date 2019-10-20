//
//  Colosseum.h
//  DataStructure-wet1
//
#ifndef COLOSSEUM_H_
#define COLOSSEUM_H_

#include <stdio.h>
#include "SplayTree.h"
#include "Gladiator.h"
#include "Trainer.h"
#include "GladiatorL.h"

namespace DS {
    class ColException{};

    class BadAlloc : public ColException{};
    class InvalidInput : public ColException{};
    class Failure : public ColException{};


    class Colosseum{
        SplayTree<Trainer> trainers;
        SplayTree<Gladiator> gladiators_id;
        SplayTree<GladiatorL> gladiators_level;
        int best_gladi_id;
        int best_gladi_level;
        
    
    public:
        Colosseum();
        Colosseum(const Colosseum& col);
        bool operator=(const Colosseum& col);
        ~Colosseum();
    
        void AddTrainer(int trainer_id);
        void buyGladiator(int gladiator_id, int trainer_id, int level);
        void FreeGladiator(int gladiator_id);
        void LevelUp(int gladiator_id, int level_increase);
        void GetTopGladiator(int trainer_id, int* gladiator_id);
        void GetAllGladiatorsByLevel(int trainer_id, int** gladiator, int* num_of_gladiators);
        void UpgradeGladiator(int gladiator_id, int upgraded_id);
        void UpdateLevels(int stimulant_code, int stimulant_factor);
        void Quit();
        
        void UpdateLevelsID(int stimulant_code, int stimulant_factor);
        void UpdateLevelsLevel(int stimulant_code, int stimulant_factor);
        void UpdateLevelsTrainers(int stimulant_code, int stimulant_factor);
    };
}


#endif /* COLOSSEUM_H_ */
