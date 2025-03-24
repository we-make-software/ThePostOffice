#ifndef TheNetworkAdapter_H
#define TheNetworkAdapter_H
#include "../TheMaintainer/TheMaintainer.h"

struct ThePostOffice{
    SetupEWB;
};
#define GetThePostOfficeTM()TM(ThePostOffice,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255)
#define GetThePostOfficeTMFailback(failback)TMFailback(ThePostOffice,failback,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255)
#endif