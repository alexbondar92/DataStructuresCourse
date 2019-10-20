#ifndef GLADIATORS_H_
#define GLADIATORS_H_

#include <stdio.h>

class GladiatorS{
    int ID;
    int Score;
    int trainingGroupID;
    
public:
    GladiatorS();
    
    GladiatorS(int Id, int score, int group);
    
//    GladiatorS(const GladiatorS& gladi);        // ======================== defualt is good enough
    
//    ~GladiatorS();        // ======================== defualt is good enough
    
    bool operator=(const GladiatorS& gladi);
    
    bool operator==(const GladiatorS& gladi);
    
    bool operator>(const GladiatorS& gladi);
    
    bool operator<(const GladiatorS& gladi);
    
    
    int getID() const;
    
    int getSroce() const;
    
    int setGroup() const;
};

#endif /* GLADIATORS_H_ */

