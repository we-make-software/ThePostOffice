#ifndef ThePostOffice_H
#define ThePostOffice_H
#include "../TheMaintainer/TheMaintainer.h"
struct ThePostOffice{
    u8 test;
};
#define GetThePostOfficeTM()TM(ThePostOffice,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255)
#endif