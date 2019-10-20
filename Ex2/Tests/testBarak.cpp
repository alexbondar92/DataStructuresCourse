
 //Created by barak on 12/28/2017.

#include <iostream>
#include "stdio.h"
#include "library2.h"
//#include "operate.h"

#define ASSERT(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed at %s:%d %s\n",__FILE__,__LINE__,#b); \
                return false; \
        } \
} while (0)

bool testInit(){
    int* arr = new int[5];
    arr[0] = 200;
    arr[1] = 40;
    arr[2] = 60;
    arr[3] = 10;
    arr[4] = 20;
    void* oper = init(5,arr); // making a system of size 5 nodes.
    ASSERT(oper !=NULL);

    ASSERT(addTrainingGroup(oper,90)==SUCCESS);
    ASSERT(addTrainingGroup(oper,4)==SUCCESS);
    ASSERT(addTrainingGroup(oper,88)==SUCCESS);
    ASSERT(addTrainingGroup(oper,66)==SUCCESS);
    ASSERT(addTrainingGroup(oper,44)==SUCCESS); // the system is now full.
    ASSERT(addTrainingGroup(oper,33)==SUCCESS); // the array should be X2 right now.
    int* a = new int;
    // minimum is 4//
    ASSERT(getMinTrainingGroup(oper,a)==SUCCESS);
                                                            /*
                                                            //              4
                                                            //          /      \
                                                            //         20        10
                                                            //       /   \       / \
                                                            //     40  33       90  60
                                                            //    /  \ /   \   / \   / \
                                                            //  88  66 200  44 x  x  x  x
                                                             */
    ASSERT(*a == 4);
    ASSERT(addGladiator(oper,2,100,20)==SUCCESS);
    ASSERT(addGladiator(oper,3,100,10)==SUCCESS);
    ASSERT(addGladiator(oper,4,40,20)==SUCCESS);
    ASSERT(addGladiator(oper,4,100,20)==FAILURE); // should not add/
    ASSERT(addGladiator(oper,5,80,44)==SUCCESS);
    ASSERT(addGladiator(oper,6,600,20)==SUCCESS);
    ASSERT(addGladiator(oper,12,80,44)==SUCCESS); // team 44: 5 - 80, 12-80, 11 - 160, 10 -240
    ASSERT(addGladiator(oper,11,160,44)==SUCCESS);// team 20: gladiator 2 - 100, 4- 40, 6 - 600
    ASSERT(addGladiator(oper,10,240,44)==SUCCESS);  // team 10: 3 - 100
    ASSERT(trainingGroupFight(oper,44,20,2,1)==SUCCESS); // now group 44 is dead.
    ASSERT(trainingGroupFight(oper,44,20,2,1)== FAILURE); // now should not let fight.
    ASSERT(trainingGroupFight(oper,20,10,3,3)==FAILURE); // team 10 doesnt have 3 gladiators.
    ASSERT(trainingGroupFight(oper,20,10,3,1)==SUCCESS); // team 10 will lose/
    ASSERT(trainingGroupFight(oper,20,10,3,1)==FAILURE); // team 10 should not be able to fight.
    ASSERT(addGladiator(oper,200,50,4)==SUCCESS);
    ASSERT(addGladiator(oper,19,200,20)==SUCCESS);
    ASSERT(addGladiator(oper,16,140,20)==SUCCESS);
    ASSERT(getMinTrainingGroup(oper,a)==SUCCESS);// still 4 is minimum
    ASSERT(*a == 4);
    ASSERT(trainingGroupFight(oper,20,4,4,1)==SUCCESS); // team 20 has
                                                // 2 - 100, 4- 40, 6 - 600
                                                // 19 - 200 , 16- 140
                                                // team 4 has id 200 - 50
    ASSERT(getMinTrainingGroup(oper,a)== SUCCESS);// the minimum should be 20 ( 4 and 10 are dead)
    ASSERT(*a == 20);
    ASSERT(trainingGroupFight(oper,20,4,5,1)==FAILURE); // team 4 should be dead.
    ASSERT(addGladiator(oper,1211,120,20)==SUCCESS);
    ASSERT(addGladiator(oper,1200,80,200)==SUCCESS);
    ASSERT(addGladiator(oper,1201,4000,200)==SUCCESS);
    ASSERT(trainingGroupFight(oper,20,200,5,2)==SUCCESS); // team 20 should LOSE
    ASSERT(getMinTrainingGroup(oper,a)== SUCCESS);
    ASSERT(*a == 33); // A NEW MINIMUM !
    delete[] arr;
    delete a;
    quit(&oper);
    printf("TEST IS FINISHED");
    return 0;
}



int main(){
    bool check = testInit();
    return check;
}
