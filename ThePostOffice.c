#include "../TheRouter/TheRouter.h"make
#include "ThePostOffice.h"

#include <linux/netdevice.h>
SetupTM(ThePostOffice,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255)
struct ReviewPacketData{
    u8 reverse[(3*sizeof(void*))+2]; 
    u8*data;
    u16 SourcePort;
    bool IsTransmissionControlProtocol;
    bool IsVersion6;
    struct sk_buff*skb;
    struct work_struct work;
};
static void SlowReviewPacket(struct work_struct *work) {
    struct ReviewPacketData*rpd=container_of(work,struct ReviewPacketData, work);
    if(!rpd)return;
    GetTheRouterTM();
    TheRouterTM->ReviewPacket(rpd);
    kfree_skb(rpd->skb);
    kfree(rpd); 
}
static int FastReviewPacket(struct sk_buff*skb,struct net_device*dev,struct packet_type*pt,struct net_device*orig_dev){
    if(!strcmp(dev->name,"lo")||skb->len<14||skb->pkt_type==PACKET_OUTGOING)return 0;
    u16 SourcePort;
	bool IsTransmissionControlProtocol;
	bool IsVersion6=false;
    u8*data=skb_mac_header(skb);
	u16 ethertype=ntohs(*(u16*)(data+12));
	switch(ethertype){
		case 2048:{
			if(data[14]!=69){
				kfree_skb(skb);
				return 1;
			}
			SourcePort=ntohs(*(u16*)(data+36));
			if((IsTransmissionControlProtocol=(data[23]==6))&&SourcePort==22)return 0;
			break;
		}
		case 34525:{
			IsVersion6=true;
			SourcePort=ntohs(*(u16*)(data+56));
			if((data[22]==254&&(data[23]&192)==128)||(data[38]==254&&(data[39]&192)==128))return 0;
			if((IsTransmissionControlProtocol=(data[20]==6))&&SourcePort==22)return 0;
			break;
		}
		default:return 0;
	}
	struct ReviewPacketData*rpd=kmalloc(sizeof(struct ReviewPacketData),GFP_KERNEL);
	if(!rpd){
		kfree_skb(skb);
		return 1;
	}
	rpd->SourcePort=SourcePort;
	rpd->IsTransmissionControlProtocol=IsTransmissionControlProtocol;
	rpd->IsVersion6=IsVersion6;
	rpd->skb=skb;
    rpd->data=data;
	INIT_WORK(&rpd->work,SlowReviewPacket);
	queue_work(system_bh_highpri_wq ,&rpd->work);
	return 1;
}
static struct packet_type PacketType;
static void TMStart(void){
    TMKeepAliveStart();
    PacketType.type=htons(ETH_P_ALL);
    PacketType.func=FastReviewPacket;
    dev_add_pack(&PacketType);
    printk(KERN_INFO "ThePostOffice: The ThePostOffice TM has been started.\n");
}
static void TMEnd(void*data){
    TMKeepAliveEnd();
    dev_remove_pack(&PacketType);
}