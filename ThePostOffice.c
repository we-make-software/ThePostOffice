#include "../TheMailConditioner/TheMailConditioner.h"
static void Layer1End(void){
    printk(KERN_INFO "TheMailConditioner: Layer 1 shutdown complete.\n");
}
static void Layer0Start(void){
  
    ktime_t start, end;
    u8*testvalue=kmalloc(4,GFP_KERNEL);
    if(!testvalue){
        printk(KERN_INFO "TheMailConditioner: Layer 0 startup failed.\n");
        return;
    }
    testvalue[0]=1;
    testvalue[1]=2;
    testvalue[2]=240;
    testvalue[3]=255;

    start = ktime_get();  // Start timing
    struct TheMailConditioner*Test1=GetTheMailConditioner(testvalue,4,true); 
    end = ktime_get();  // End timing

    if(!Test1){
        printk(KERN_INFO "TheMailConditioner: Layer 0 startup failed.\n");
        return;
    }

    printk(KERN_INFO "TheMailConditioner: First call took %llu ns, returned pointer: %p\n", 
           ktime_to_ns(ktime_sub(end, start)), Test1);

    start = ktime_get();
    struct TheMailConditioner*Test2=GetTheMailConditioner(testvalue,4,true); 
    end = ktime_get();

    printk(KERN_INFO "TheMailConditioner: Second call took %llu ns, returned pointer: %p\n", 
           ktime_to_ns(ktime_sub(end, start)), Test2);

    if(!Test2){
        printk(KERN_INFO "1:TheMailConditioner: Layer 0 startup failed.\n");
        return;
    }

    if (Test1 == Test2)
        printk(KERN_INFO "TheMailConditioner: The same object was returned.\n");
    else
        printk(KERN_INFO "TheMailConditioner: A new object was created.\n");

    kfree(testvalue);

    printk(KERN_INFO "TheMailConditioner: Layer 0 startup initialized test 1.\n");
}


Layer0_1Setup("ThePostOffice",0,0)