#include "ThePostOffice.h"
#include "../TheNetworkAdapter/TheNetworkAdapter.h"
SetupTM(ThePostOffice,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255)
static void TMStart(void){
    GetTheNetworkAdapterTM();
    TheNetworkAdapterTM->GetAdd();
    printk(KERN_INFO "ThePostOffice: The ThePostOffice TM has been started.\n");
}
static void TMEnd(void*){

 
    printk(KERN_INFO "ThePostOffice: The ThePostOffice TM has been ended.\n");
}