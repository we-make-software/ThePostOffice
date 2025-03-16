#include "../ExpiryWorkBase/ExpiryWorkBase.h"
#include <linux/netdevice.h>
#include <linux/if_packet.h>
#include <linux/net.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/ipv6.h>
struct NetworkAdapterTable {
    struct net_device*dev;
    struct ExpiryWorkBase expiryWorkBase;
    struct list_head routers,list;
};
struct RouterTable{
    struct ExpiryWorkBase expiryWorkBase;
    struct NetworkAdapterTable*networkAdapterTable;
    struct list_head list;
};
static DEFINE_MUTEX(NetworkAdapterListMutex);
static LIST_HEAD(NetworkAdapterList);
static struct NetworkAdapterTable*GetNetworkAdapter(struct net_device*dev);
static struct NetworkAdapterTable*GetNetworkAdapter(struct net_device*dev){
    struct NetworkAdapterTable*adapter;
    mutex_lock(&NetworkAdapterListMutex);
    list_for_each_entry(adapter,&NetworkAdapterList,list)
        if(adapter->dev==dev){
            mutex_unlock(&NetworkAdapterListMutex);
            return adapter;
        }
    mutex_unlock(&NetworkAdapterListMutex);
    return NULL;
}
static void AutoDeleteNetworkAdapter(void*adapter){
	struct NetworkAdapterTable*net_adapter=(struct NetworkAdapterTable*)adapter;
	mutex_lock(&NetworkAdapterListMutex);
	struct RouterTable*router,*tmp;
	list_for_each_entry_safe(router,tmp,&net_adapter->routers,list)
        CancelExpiryWorkBase(&router->expiryWorkBase);
	mutex_unlock(&NetworkAdapterListMutex);
}
static struct NetworkAdapterTable*AddNetworkAdapter(struct net_device*dev);
static struct NetworkAdapterTable*AddNetworkAdapter(struct net_device*dev){
	struct NetworkAdapterTable*adapter=kmalloc(sizeof(struct NetworkAdapterTable),GFP_KERNEL);
	if(!adapter)return NULL;
	adapter->dev=dev;
	INIT_LIST_HEAD(&adapter->list);
    INIT_LIST_HEAD(&adapter->routers);
	SetupExpiryWorkBase(&adapter->expiryWorkBase,NULL,adapter,AutoDeleteNetworkAdapter);
	mutex_lock(&NetworkAdapterListMutex);
	list_add(&adapter->list,&NetworkAdapterList);
	mutex_unlock(&NetworkAdapterListMutex);
	return adapter;
}
struct PacketConversion{
    u16 SourcePort;
    bool IsTransmissionControlProtocol;
    bool IsVersion6;
    struct sk_buff *skb;
    struct net_device *dev;
    struct work_struct work;
};
extern void TheMailConditionerPacketWorkHandler(struct NetworkAdapterTable*,struct PacketConversion*);
static void PacketConversionTask(struct PacketConversion*packet_work){
    struct NetworkAdapterTable*adapter=GetNetworkAdapter(packet_work->dev)?:AddNetworkAdapter(packet_work->dev);
    if(!adapter||adapter->expiryWorkBase.Invalid)return;
    TheMailConditionerPacketWorkHandler(adapter,packet_work);
}
static void PacketWorkHandler(struct work_struct *work) {
    struct PacketConversion *packet_work = container_of(work, struct PacketConversion, work);
    PacketConversionTask(packet_work);
    kfree_skb(packet_work->skb);
    kfree(packet_work); 
}
static int ThePostOfficeReceivePacket(struct sk_buff*skb,struct net_device*dev,struct packet_type*pt,struct net_device*orig_dev){
	if(!strcmp(dev->name,"lo")||skb->len<14||skb->pkt_type==PACKET_OUTGOING)return 0;
	u8*data=skb_mac_header(skb);
	if((data[0]&2))return 0;
	u16 SourcePort;
	bool IsTransmissionControlProtocol;
	bool IsVersion6=false;
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
	struct PacketConversion*pc=kmalloc(sizeof(struct PacketConversion),GFP_KERNEL);
	if(!pc){
		kfree_skb(skb);
		return 1;
	}
	pc->SourcePort=SourcePort;
	pc->IsTransmissionControlProtocol=IsTransmissionControlProtocol;
	pc->IsVersion6=IsVersion6;
	pc->skb=skb;
	pc->dev=dev;
	INIT_WORK(&pc->work,PacketWorkHandler);
	queue_work(system_bh_highpri_wq ,&pc->work);
	return 1;
}
static void CancelAllNetworkAdapters(void){
    struct NetworkAdapterTable*adapter, *tmp;
    list_for_each_entry_safe(adapter, tmp, &NetworkAdapterList, list)
        CancelExpiryWorkBase(&adapter->expiryWorkBase);
}
static struct packet_type ThePostOfficePacketType;
static void BindNetworkAdapterToTheProject(void){
    ThePostOfficePacketType.type=htons(ETH_P_ALL);
    ThePostOfficePacketType.func=ThePostOfficeReceivePacket;
    dev_add_pack(&ThePostOfficePacketType);
}
static void UnbindNetworkAdapterToTheProject(void){
    dev_remove_pack(&ThePostOfficePacketType);
}
Setup("ThePostOffice", 
    BindNetworkAdapterToTheProject(),
    UnbindNetworkAdapterToTheProject();
    CancelAllNetworkAdapters();
    )


    /*
bool ThePostOfficeSendPacket(struct IEEE8021Router* router){
    struct sk_buff *skb;
    skb=netdev_alloc_skb(router->NetworkInterfaces->dev,14+NET_IP_ALIGN);
    if(!skb)return false;
    skb_reserve(skb,NET_IP_ALIGN);
    skb_put_data(skb,router->MediaAccessControl,6);
    skb_put_data(skb,router->NetworkInterfaces->dev->dev_addr,6); 
    u16 Ethertype=htons(router->IsVersion6?34525:2048); 
    skb_put_data(skb,&Ethertype,2); 
    skb->dev=router->NetworkInterfaces->dev;
    skb->protocol=htons(ETH_P_IP);
    skb->priority=0;
    if(dev_queue_xmit(skb)<0){
        kfree_skb(skb);
        return false;
    }
    return true;
}
*/




