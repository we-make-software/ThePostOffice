#include "../TheMaintainer/TheMaintainer.h"
bool IsNetworkVersion4Used(u8*value);
bool IsNetworkVersion4Used(u8*value){
    return GetTheMailConditioner(value,4,false)!=NULL;
}
EXPORT_SYMBOL(IsNetworkVersion4Used);
struct TheMailConditioner*GetNetworkVersion4(u8*value);
struct TheMailConditioner*GetNetworkVersion4(u8*value){
    return GetTheMailConditioner(value,4,true);
}
EXPORT_SYMBOL(GetNetworkVersion4);
bool IsNetworkVersion6Used(u8*value);
bool IsNetworkVersion6Used(u8*value){
    return GetTheMailConditioner(value,16,false)!=NULL;
}
EXPORT_SYMBOL(IsNetworkVersion6Used);
struct TheMailConditioner*GetNetworkVersion6(u8*value);
struct TheMailConditioner*GetNetworkVersion6(u8*value){
    return GetTheMailConditioner(value,16,true);
}
EXPORT_SYMBOL(GetNetworkVersion6);
bool IsMediaAccessControlUsed(u8*value);
bool IsMediaAccessControlUsed(u8*value){
    return GetTheMailConditioner(value,6,false)!=NULL;
}
EXPORT_SYMBOL(IsMediaAccessControlUsed);
struct TheMailConditioner*GetMediaAccessControl(u8*value);
struct TheMailConditioner*GetMediaAccessControl(u8*value){
   return GetTheMailConditioner(value,6,true);
}
EXPORT_SYMBOL(GetMediaAccessControl);
static void End(void){
    //need to be call to the last project
//    StopExpiryWorkBase();

}
static void Start(void){
    
}
Setup("ThePostOffice",0,0)