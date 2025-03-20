#ifndef ThePostOffice_H
#define ThePostOffice_H
#include "../TheMailConditioner/TheMailConditioner.h"
extern bool IsNetworkVersion4Used(u8*value);
extern struct TheMailConditioner*GetNetworkVersion4(u8*value);
extern bool IsNetworkVersion6Used(u8*value);
extern struct TheMailConditioner*GetNetworkVersion6(u8*value);
#endif