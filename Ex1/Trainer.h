//
//  Trainer.h
//  DataStructure-wet1
//
#ifndef TRAINER_H_
#define TRAINER_H_

#include <stdio.h>
#include "GladiatorL.h"
#include "SplayTree.h"
#include <ostream>
#include <stdlib.h>

using namespace DS;
namespace DS {
    class Trainer{
        int ID;
        SplayTree<GladiatorL> gladi_tree_level;
        int best_gladiator_id;
        int best_gladiator_level;
    
    public:
        Trainer();
        
        Trainer(int ID);
    
        Trainer(const Trainer& trainer);
        
        Trainer& operator=(const Trainer& trainer);
        
        bool operator<(const Trainer& trainer);
        bool operator==(const Trainer& trainer);
        bool operator>(const Trainer& trainer);
        bool operator!=(const Trainer& trainer);
        
        ~Trainer();
    
        int getID() const;
    
        int getGladiatorsNumber();
    
        int getBestGladiator();
    
        int getBestGladiatorLevel();
    
        void addGladiator(const GladiatorL& gladiator);
    
        void removeGladiator(const GladiatorL& gladiator);
        
        bool setGladiatorID(int old_id, int new_id);
        
        void updateGladiatorLevel(int gladiator_id, int current_level, int level_increase);
        
        void UpdateLevels(int stimulant_code, int stimulant_factor);
        
        Trainer* getTrainerPtr() const;
    
        GladiatorL* getGladiatorsList();
    };
}












#endif /* TRAINER_H_ */
