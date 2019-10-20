//
//  Gladiator.h
//  DataStructure-wet1
//
#ifndef GLADIATOR_H_
#define GLADIATOR_H_

#include <stdio.h>
#include "Trainer.h"

namespace DS {
    class Gladiator{
        int Id;
        int level;
        Trainer* trainer;
    
    public:
        Gladiator();
        Gladiator(int ID, int level, Trainer* tranier_ptr);
        Gladiator(const Gladiator& gladiator);
        Gladiator& operator=(const Gladiator& gladiator);
        bool operator<(const Gladiator& gladi);
        bool operator==(const Gladiator& gladi);
        bool operator>(const Gladiator& gladi);
        bool operator!=(const Gladiator& gladi);
    
        int getId() const;
    
        int getLevel() const;
        
        void setId(int new_id);
        
        void setLevel(int new_level);
        
        void setTrainerPtr(Trainer* trainer);
        
        Trainer* getTrainerPtr() const;
    };
    
}

#endif /* GLADIATOR_H_ */
