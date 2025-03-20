#include "../TheMailConditioner/TheMailConditioner.h"
bool IsNetworkVersion4Used(u8*value);
bool IsNetworkVersion4Used(u8*value){
    return GetTheMailConditioner((u8[]){value[0],value[1],value[2],value[3]},4,false)!=NULL;
}
EXPORT_SYMBOL(IsNetworkVersion4Used);
struct TheMailConditioner*GetNetworkVersion4(u8*value);
struct TheMailConditioner*GetNetworkVersion4(u8*value){
    return GetTheMailConditioner((u8[]){value[0],value[1],value[2],value[3]},4,true);
}
EXPORT_SYMBOL(GetNetworkVersion4);
bool IsNetworkVersion6Used(u8*value);
bool IsNetworkVersion6Used(u8*value){
    return GetTheMailConditioner((u8[]){value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7],value[8],value[9],value[10],value[11],value[12],value[13],value[14],value[15]},16,false)!=NULL;
}
EXPORT_SYMBOL(IsNetworkVersion6Used);
struct TheMailConditioner*GetNetworkVersion6(u8*value);
struct TheMailConditioner*GetNetworkVersion6(u8*value){
    return GetTheMailConditioner((u8[]){value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7],value[8],value[9],value[10],value[11],value[12],value[13],value[14],value[15]},16,true);
}
EXPORT_SYMBOL(GetNetworkVersion6);
static void Layer1End(void){}
static void Layer0Start(void){}
Layer0_1Setup("ThePostOffice",0,0)