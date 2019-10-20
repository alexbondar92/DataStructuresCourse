#ifndef GLADIATOR_H_
#define GLADIATOR_H_

#include <stdio.h>

class Gladiator{
    int ID;
    int Score;
    int trainingGroupID;
    
public:
    Gladiator();
    
    Gladiator(int Id, int score, int group);
    
//    Gladiator(const Gladiator& gladi);        // ======================== defualt is good enough
    
//    ~Gladiator();        // ======================== defualt is good enough
    
    bool operator=(const Gladiator& gladi);
    
    bool operator==(const Gladiator& gladi);
    
    bool operator>(const Gladiator& gladi);
    
    bool operator<(const Gladiator& gladi);
    
    
    int getID() const;
    
    int getSroce() const;
    
    int setGroup() const;
};

#endif /* GLADIATOR_H_ */
