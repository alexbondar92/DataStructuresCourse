#ifndef GROUP_H_
#define GROUP_H_

#include <stdio.h>
#include "RankSplayTree.h"
#include "GladiatorS.h"


class Group{
    int ID;
//    int Size;
    bool flagConquered/* = false*/;
    RankSplayTree<GladiatorS> gladiators;
public:
    Group();
    
    Group(int Id);
    
    Group(const Group& group);
    
//    ~Group();        // ======================== defualt is good enough
    
    Group& operator=(const Group& group);
    
    void addGladiator(int gladiatorID, int score, int trainingGroupID);
    
    int getMaxSelect(int k1);
    
    void setConq(bool f);
    
    bool isConq();
};


#endif /* GROUP_H_ */
