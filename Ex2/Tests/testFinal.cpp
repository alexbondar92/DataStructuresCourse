#include <iostream>
#include "Colusseum.h"
#include <iostream>
#include "stdio.h"
#include "library2.h"


#define ASSERT(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed at %s:%d %s\n",__FILE__,__LINE__,#b); \
                return false; \
        } \
} while (0)

//General Test with basic Structure
void test1(){
    int exeption=0;
    int arr[]={2,1};
    Colusseum DS(2,arr); //Initial with Team:1,2
    int minGroup;

    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==1);
    DS.addTrainingGroup(0); //Add Team 0
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==0);

    DS.addGladiator(100,20,0); //Add Gladiator ID:100 Score:20 to Team:0
    DS.addGladiator(101,20,0); //Add Gladiator ID:101 Score:20 to Team:0
    DS.addGladiator(102,20,0); //Add Gladiator ID:102 Score:20 to Team:0

    DS.addGladiator(110,20,1); //Add Gladiator ID:110 Score:20 to Team:1
    DS.addGladiator(111,20,1);//Add Gladiator ID:111 Score:20 to Team:1

    DS.addGladiator(120,20,2); //Add Gladiator ID:120 Score:20 to Team:2
    DS.addGladiator(121,20,2); //Add Gladiator ID:121 Score:20 to Team:2
    DS.addGladiator(122,20,2); //Add Gladiator ID:122 Score:20 to Team:2

    DS.trainingGroupFight(0,2,3,3); //Team 2 lost
    try{
        DS.trainingGroupFight(0,2,3,3); //Team 2 is not Active
    }catch (ColusseumExceptions::Failure){
        exeption++; //exception=1
    }
    assert(exeption==1);
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==0);

    DS.trainingGroupFight(0,1,3,2); //Team 1 lost
    try {
        DS.trainingGroupFight(0,1,1,1); //Team 1 is not Active
    }
    catch (ColusseumExceptions::Failure) {
        exeption++; //exception=2
    }
    assert(exeption==2);

    DS.addTrainingGroup(3); //Add Team 3
    DS.addGladiator(130,30,3); //Add Gladiator ID:130 Score:30 to Team:3
    DS.addGladiator(131,30,3); //Add Gladiator ID:131 Score:30 to Team:3

    DS.trainingGroupFight(0,3,1,1); //Team 0 lost
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==3);
    try {
        DS.trainingGroupFight(0,3,1,1); //Team 0 is not Active
    }
    catch (ColusseumExceptions::Failure) {
        exeption++; //exception=3
    }

    DS.addTrainingGroup(4); //Add Team 4
    DS.addGladiator(140,40,4); //Add Gladiator ID:140 Score:40 to Team:4
    DS.addGladiator(141,40,4); //Add Gladiator ID:141 Score:40 to Team:4
    DS.addGladiator(142,40,4); //Add Gladiator ID:142 Score:40 to Team:4

    DS.addTrainingGroup(5); //Add Team 5
    DS.addGladiator(150,50,5); //Add Gladiator ID:150 Score:50 to Team:5
    DS.addGladiator(151,50,5); //Add Gladiator ID:151 Score:50 to Team:5

    DS.trainingGroupFight(4,5,2,1); //Team 5 lost
    try {
        DS.trainingGroupFight(5,3,1,1); //Team 5 is not Active
    }
    catch (ColusseumExceptions::Failure) {
        exeption++; //exception=4
    }

    DS.trainingGroupFight(3,4,1,1); //Team 3 lost
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==4);
    try {
        DS.trainingGroupFight(4,3,1,1); //Team 3 is not Active
    }
    catch (ColusseumExceptions::Failure) {
        exeption++; //exception=5
    }


    assert(exeption==5);
    std::cout << "Passed1 ";
}

//General Test with bigger Structure
void test2() {
    int arrF[] = {-10,30,20,40,50};
    int arr[] = {1,3,2,4,5};
    int min=0;
    if(min == 1) {
        return;
    }
    void* DS=init(0,arr);
    assert(DS == NULL); //number of array is less than 2
    DS = init(1,arr);
    assert(DS == NULL); //number of array is less than 2
    DS = init(5,arrF);
    assert(DS == NULL); //array include negative number
    DS = init(5,arr); //Create Structore with 5 Teams: 1 3 2 4 5
    assert(DS != NULL); //Succeed

    //Invalid Input || Failure of AddTrainingGroup
    assert(addTrainingGroup(NULL,10) == INVALID_INPUT);
    assert(addTrainingGroup(DS,-1) == INVALID_INPUT);
    assert(addTrainingGroup(DS,3) == FAILURE);

    //AddTrainingGroup
    assert(addTrainingGroup(DS,9) == SUCCESS); //Add Team: 9
    assert(addTrainingGroup(DS,6) == SUCCESS); //Add Team: 6
    assert(addTrainingGroup(DS,8) == SUCCESS); //Add Team: 8
    assert(addTrainingGroup(DS,7) == SUCCESS); //Add Team: 7

    //Invalid Input || Failure of AddGladiator
    assert(addGladiator(NULL,5,50,5) == INVALID_INPUT);
    assert(addGladiator(DS,-1,50,5) == INVALID_INPUT);
    assert(addGladiator(DS,1,50,-5) == INVALID_INPUT);
    assert(addGladiator(DS,1,-1,5) == INVALID_INPUT);
    assert(addGladiator(DS,100,20,11) == FAILURE); //Team doesnt exist

    //AddGladiator
    assert(addGladiator(DS,10,100,1) == SUCCESS); //Add Gladiator: 10 with Score: 100 to Team: 1
    assert(addGladiator(DS,14,140,1) == SUCCESS); //Add Gladiator: 14 with Score: 140 to Team: 1
    assert(addGladiator(DS,12,120,1) == SUCCESS); //Add Gladiator: 12 with Score: 120 to Team: 1
    assert(addGladiator(DS,13,130,1) == SUCCESS); //Add Gladiator: 13 with Score: 130 to Team: 1

    assert(addGladiator(DS,37,370,3) == SUCCESS); //Add Gladiator: 37 with Score: 370 to Team: 3
    assert(addGladiator(DS,32,320,3) == SUCCESS); //Add Gladiator: 32 with Score: 320 to Team: 3
    assert(addGladiator(DS,35,320,3) == SUCCESS); //Add Gladiator: 32 with Score: 320 to Team: 3

    assert(addGladiator(DS,73,130,7) == SUCCESS); //Add Gladiator: 73 with Score: 130 to Team: 7
    assert(addGladiator(DS,77,770,7) == SUCCESS); //Add Gladiator: 77 with Score: 770 to Team: 7

    assert(addGladiator(DS,13,150,1) == FAILURE); //Gladiator Already Exists
    assert(addGladiator(DS,77,150,1) == FAILURE); //Gladiator Already Exists
    assert(addGladiator(DS,37,150,3) == FAILURE); //Gladiator Already Exists

    //GetMinTrainingGroup
    assert(getMinTrainingGroup(NULL,&min) == INVALID_INPUT);
    assert(getMinTrainingGroup(DS,NULL) == INVALID_INPUT);
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 1);

    //TrainingGroupFight
    assert(trainingGroupFight(NULL,1,2,2,2) == INVALID_INPUT);
    assert(trainingGroupFight(DS,1,-1,1,2) == INVALID_INPUT);
    assert(trainingGroupFight(DS,1,1,-1,2) == INVALID_INPUT);
    assert(trainingGroupFight(DS,1,1,1,-2) == INVALID_INPUT);
    assert(trainingGroupFight(DS,5,3,0,1) == INVALID_INPUT);

    assert(trainingGroupFight(DS,1,1,1,2) == FAILURE);
    assert(trainingGroupFight(DS,1,11,1,2) == FAILURE); //Team 11 doesnt Exists
    assert(trainingGroupFight(DS,1,3,5,2) == FAILURE); //Team 1 has 4 Gladiators
    assert(trainingGroupFight(DS,1,3,4,4) == FAILURE); //Team 3 has 3 Gladiators
    assert(trainingGroupFight(DS,1,5,2,1) == FAILURE); //Team 5 has 0 Gladiators

    assert(trainingGroupFight(DS,7,3,1,3) == SUCCESS); //Team 7: 770 against Team 3: 1010 => Team 7 lost
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 1);

    assert(trainingGroupFight(DS,3,1,2,2) == SUCCESS); //Team 3: 690 against Team 1: 270 => Team 1 lost
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 2);


    assert(addGladiator(DS,20,200,2) == SUCCESS); //Add Gladiator: 20 with Score: 200 to Team: 2
    assert(addGladiator(DS,20,200,2) == FAILURE); //Gladiator Already Exists
    assert(addGladiator(DS,25,200,2) == SUCCESS); //Add Gladiator: 25 with Score: 200 to Team: 2
    assert(addGladiator(DS,29,290,2) == SUCCESS); //Add Gladiator: 29 with Score: 290 to Team: 2
    assert(addGladiator(DS,23,230,2) == SUCCESS); //Add Gladiator: 29 with Score: 230 to Team: 2
    assert(addGladiator(DS,24,240,2) == SUCCESS); //Add Gladiator: 24 with Score: 240 to Team: 2
    assert(addGladiator(DS,28,200,2) == SUCCESS); //Add Gladiator: 24 with Score: 200 to Team: 2

    assert(addGladiator(DS,90,100,9) == SUCCESS); //Add Gladiator: 90 with Score: 100 to Team: 9
    assert(addGladiator(DS,94,120,9) == SUCCESS); //Add Gladiator: 94 with Score: 120 to Team: 9
    assert(addGladiator(DS,92,900,9) == SUCCESS); //Add Gladiator: 92 with Score: 900 to Team: 9
    assert(addGladiator(DS,95,150,9) == SUCCESS); //Add Gladiator: 95 with Score: 150 to Team: 9
    assert(addGladiator(DS,97,200,9) == SUCCESS); //Add Gladiator: 97 with Score: 200 to Team: 9

    assert(trainingGroupFight(DS,9,1,2,2) == FAILURE); //Team 1 lost
    assert(trainingGroupFight(DS,9,7,1,1) == FAILURE); //Team 7 lost

    assert(trainingGroupFight(DS,9,3,3,6) == FAILURE); //Team 9 has 5 Gladiators
    assert(trainingGroupFight(DS,9,3,4,5) == FAILURE); //Team 3 has 4 Gladiators

    assert(trainingGroupFight(DS,2,3,2,1) == SUCCESS); //Team 2: 530 against Team 3: 370 => Team 3 lost
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 2);

    assert(trainingGroupFight(DS,9,2,5,6) == SUCCESS); //Team 9: 1470 against Team 2: 1360 => Team 2 lost
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 4);

    assert(addGladiator(DS,40,400,4) == SUCCESS); //Add Gladiator: 40 with Score: 400 to Team: 4

    assert(trainingGroupFight(DS,9,4,1,2) == FAILURE); //Team 4 has 1 Gladiators
    assert(trainingGroupFight(DS,9,4,1,1) == SUCCESS); //Team 9: 900 against Team 2: 1360 => Team 4 lost
    assert(getMinTrainingGroup(DS,&min) == SUCCESS);
    assert(min == 5);

    assert(addGladiator(DS,20,200,5) == FAILURE); //Gladiator already exists
    assert(addTrainingGroup(DS,4) == FAILURE); //Team already exists
    assert(addTrainingGroup(DS,2) == FAILURE); //Team already exists
    assert(addTrainingGroup(DS,1) == FAILURE); //Team already exists


    quit(&DS);
    std::cout << "Passed2 ";

}

//Init Test
bool InitTest(){
    int* arr=new int[3];
    arr[0]=2;
    arr[1]=-3;
    arr[2]=4;
    void* DS=init(0,arr);
    ASSERT(!DS);
    DS=init(3,arr);
    ASSERT(!DS);
    delete[] (arr);
    return true;
}

//Add Training Group Test
bool addTrainingGroupTest(void* DS){
    int min=0;
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==2);
    ASSERT(addTrainingGroup(NULL,1)==INVALID_INPUT);
    ASSERT(addTrainingGroup(DS,-3)==INVALID_INPUT);
    ASSERT(addTrainingGroup(DS,4)==FAILURE);
    ASSERT(addTrainingGroup(DS,2)==FAILURE);
    ASSERT(addTrainingGroup(DS,3)==FAILURE);
    ASSERT(addTrainingGroup(DS,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);
    return true;
}

//Add Gladiator Test
bool addGladiatorTest(void* DS){
    ASSERT(addGladiator(NULL,100,10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,-100,10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,100,-10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,100,10,-1)==INVALID_INPUT);

    ASSERT(addGladiator(DS,301,10,5)==FAILURE);

    ASSERT(addGladiator(DS,101,30,1)==SUCCESS);
    ASSERT(addGladiator(DS,102,10,1)==SUCCESS);
    ASSERT(addGladiator(DS,103,10,1)==SUCCESS);

    ASSERT(addGladiator(DS,101,10,1)==FAILURE);
    ASSERT(addGladiator(DS,102,10,1)==FAILURE);
    ASSERT(addGladiator(DS,103,10,1)==FAILURE);

    ASSERT(addGladiator(DS,201,20,2)==SUCCESS);
    ASSERT(addGladiator(DS,202,20,2)==SUCCESS);
    ASSERT(addGladiator(DS,203,20,2)==SUCCESS);

    ASSERT(addGladiator(DS,201,20,2)==FAILURE);
    ASSERT(addGladiator(DS,202,20,2)==FAILURE);
    ASSERT(addGladiator(DS,203,20,2)==FAILURE);

    ASSERT(addGladiator(DS,301,30,3)==SUCCESS);
    ASSERT(addGladiator(DS,302,30,3)==SUCCESS);
    ASSERT(addGladiator(DS,303,30,3)==SUCCESS);

    ASSERT(addGladiator(DS,401,30,4)==SUCCESS);
    ASSERT(addGladiator(DS,402,30,4)==SUCCESS);
    ASSERT(addGladiator(DS,403,30,4)==SUCCESS);
    return true;
}

//Training Group Fight Test
bool trainingGroupFightTest(void* DS){
    int min=0;
    ASSERT(trainingGroupFight(NULL,1,2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,-1,2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,1,-2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,1,2,0,1)==INVALID_INPUT);

    ASSERT(trainingGroupFight(DS,1,2,5,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,5,2,1,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,1,1,1,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,1,2,1,5)==FAILURE);

    ASSERT(trainingGroupFight(DS,1,2,1,1)==SUCCESS);//group 1 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);

    ASSERT(trainingGroupFight(DS,1,2,1,1)==FAILURE);//group 2 can't fight
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);

    ASSERT(trainingGroupFight(DS,3,1,3,3)==SUCCESS);//group 3 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,1,4,1,1)==FAILURE);//group 1 can't fight

    ASSERT(trainingGroupFight(DS,3,4,3,3)==SUCCESS);//group 3 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,1,4,1,1)==FAILURE);//group 4 can't fight
    ASSERT(addGladiator(DS,404,30,4)==SUCCESS);
    ASSERT(addTrainingGroup(DS,4)==FAILURE);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);
    return true;
}

//General Test
bool advancedTest1(void* DS){
    int min=0;
    ASSERT(addTrainingGroup(DS,5)==SUCCESS);
    ASSERT(addGladiator(DS,501,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,502,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,503,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,504,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,505,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,506,1000,5)==SUCCESS);

    ASSERT(addTrainingGroup(DS,6)==SUCCESS);
    ASSERT(addGladiator(DS,601,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,602,300,6)==SUCCESS);
    ASSERT(addGladiator(DS,603,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,604,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,605,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,606,20,6)==SUCCESS);

    ASSERT(addTrainingGroup(DS,7)==SUCCESS);
    ASSERT(addGladiator(DS,701,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,702,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,703,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,704,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,705,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,706,20,7)==SUCCESS);

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,4,5,1,1)==FAILURE);//group 4 can't fight
    ASSERT(trainingGroupFight(DS,5,7,10,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,5,7,3,6)==SUCCESS);//group 5 is winning
    ASSERT(trainingGroupFight(DS,5,3,1,1)==SUCCESS);//group 5 is winning

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(trainingGroupFight(DS,5,6,1,1)==SUCCESS);//group 5 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(addTrainingGroup(DS,8)==SUCCESS);
    ASSERT(trainingGroupFight(DS,5,8,1,1)==FAILURE);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(addTrainingGroup(DS,0)==SUCCESS);
    ASSERT(addGladiator(DS,1234,1000,0)==SUCCESS);
    ASSERT(trainingGroupFight(DS,5,0,1,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==0);

    ASSERT(trainingGroupFight(DS,0,5,1,1)==FAILURE);//group 5 can't fight

    return true;
}

//General Test
bool advancedTest2(void* DS){
    int min=0;
    ASSERT(addTrainingGroup(DS,9)==SUCCESS);
    ASSERT(addTrainingGroup(DS,10)==SUCCESS);
    ASSERT(addTrainingGroup(DS,11)==SUCCESS);
    ASSERT(addTrainingGroup(DS,12)==SUCCESS);
    ASSERT(addTrainingGroup(DS,13)==SUCCESS);
    ASSERT(addTrainingGroup(DS,14)==SUCCESS);
    ASSERT(addGladiator(DS,140,1400,14)==SUCCESS);
    ASSERT(addGladiator(DS,141,1400,11)==SUCCESS);
    ASSERT(addGladiator(DS,142,1400,12)==SUCCESS);
    ASSERT(addGladiator(DS,143,1400,13)==SUCCESS);
    ASSERT(addGladiator(DS,144,100,8)==SUCCESS);

    ASSERT(trainingGroupFight(DS,0,14,1,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==8);

    ASSERT(trainingGroupFight(DS,11,14,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,13,14,1,1)==FAILURE);//group 14 can't fight
    ASSERT(trainingGroupFight(DS,11,12,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,11,13,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,11,8,1,1)==SUCCESS);

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==9);

    return true;
}

//larger input
bool advancedTest3(void* DS){
    int min=0;
    for(int i=10000;i>=5;i--){
        ASSERT(addTrainingGroup(DS,i)==SUCCESS);
    }
    ASSERT(addTrainingGroup(DS,0)==SUCCESS);
    ASSERT(addTrainingGroup(DS,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==0);

    for(int i=10000;i>=0;i--){
        ASSERT(addTrainingGroup(DS,i)==FAILURE);
    }

    for(int i=0;i<=10000;i++) {
        ASSERT(addGladiator(DS, 10 + i, 300 + i, i) == SUCCESS);
    }


    for(int i=0;i<=1000;i++){
        ASSERT(trainingGroupFight(DS,i,i+2,1,1)==SUCCESS);
        ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
        ASSERT(min==i+1);
    }

    return true;
}


bool test3(){
    InitTest();
    int* arr=new int[3];
    arr[0]=2;
    arr[1]=3;
    arr[2]=4;
    void* DS=init(3,arr);
    ASSERT(DS!=NULL);

    addTrainingGroupTest(DS);
    addGladiatorTest(DS);
    trainingGroupFightTest(DS);
    advancedTest1(DS);
    advancedTest2(DS);
    quit(&DS);

    void* DS2=init(3,arr);
    advancedTest3(DS2);
    quit(&DS2);

    delete[] arr;
    std::cout<< "Passed 3 " << std::endl << "Passed All";
    return true;
}

int main() {
    test1();
    test2();
    test3();

    return 0;
}
