#define vrf(_arg)		VRFCallpointWorker::cmdVRF(_arg)
#define novrf(_arg)		VRFCallpointWorker::cmdnoVRF(_arg)
#define router_pim(_arg)	RouterPimCallpointWorker::cmdRouterPim(_arg)
#define norouter_pim(_arg)	RouterPimCallpointWorker::noRouterPim(_arg)

#define rp_address(_vrf, _rp)								\
do{											\
string _rp_arg2 = _rp;									\
DCMENUMS arr[] = {ROUTERPIM_RP_ADDR};							\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf, arr, &_rp_arg2, NO_REST_REQ, NULL);	\
}while(0);										\


#define pim_hello_timer(_vrf, _time)   							\
do{				       							\
unsigned int _hello_timer = _time;     							\
DCMENUMS arr[] = {ROUTERPIM_HELLO_TIMER};						\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&_hello_timer, NO_REST_REQ, NULL);\
}while(0);			       							\

#define pim_max_cache(_vrf, _max_cache)   						\
do{				       							\
unsigned int __max_cache = _max_cache;							\
DCMENUMS arr[] = {ROUTERPIM_MAX_CACHE};							\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__max_cache, NO_REST_REQ, NULL); \
}while(0);			       							\


#define pim_nbr_to(_vrf, _nbt_to)	   						\
do{				       							\
unsigned int __nbt_to = _nbt_to;							\
DCMENUMS arr[] = {ROUTERPIM_NBR_TIMEOUT};						\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__nbt_to, NO_REST_REQ, NULL); 	\
}while(0);			       							\


#define pim_jp_int(_vrf, _jp_int)	   						\
do{				       							\
unsigned int __jp_int = _jp_int;							\
DCMENUMS arr[] = {ROUTERPIM_JOIN_PRUNE_INTERVAL};					\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__jp_int, NO_REST_REQ, NULL); 	\
}while(0);			       							\


#define pim_inact(_vrf, _inact)		   						\
do{				       							\
unsigned int __inact = _inact;								\
DCMENUMS arr[] = {ROUTERPIM_INACTIVITY_INTERVAL};					\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__inact, NO_REST_REQ, NULL); 	\
}while(0);			       							\



#define pim_prw_int(_vrf, _arg)		   						\
do{				       							\
unsigned int __arg = _arg;								\
DCMENUMS arr[] = {ROUTERPIM_PRUNE_WAIT_INTERVAL};					\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__arg, NO_REST_REQ, NULL); 	\
}while(0);			       							\


#define pim_spt_th(_vrf, _arg)		   						\
do{				       							\
unsigned int __arg = _arg;								\
DCMENUMS arr[] = {ROUTERPIM_SPT_THRESHOLD};						\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf,arr,&__arg, NO_REST_REQ, NULL); 	\
}while(0);			       							\


#define ve(_vrf, _veid, _vlanid)							\
do{											\
char _temp[32];										\
sprintf(_temp, "ve%d", _veid);								\
VEInterfaceCallpointWorker::createVe(_vrf, string (_temp), _vlanid);			\
}while(0);										\

#define nove(if_name)									\
do{											\
VEInterfaceCallpointWorker::delVe(if_name);						\
}while(0);										\

#define ssmmap(_vrf, _pfxlst, _src_addr)						\
do{											\
DCMENUMS arr1[] = {ROUTERPIM_SSMMAP, SSMMAP_SRC_ADDRESS}; 				\
string 	attr_str = _src_addr;								\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf, arr1, &attr_str, NO_REST_REQ, NULL);	\
DCMENUMS arr2[] = {ROUTERPIM_SSMMAP, SSMMAP_PFXLST_NAME};				\
attr_str = _pfxlst;									\
RouterPimCallpointWorker::RouterPimCallpoint(_vrf, arr2, &attr_str, NO_REST_REQ, NULL);	\
}while(0);										\

#define venosh(ifname)									\
do{											\
bool _status = true;									\
DCMENUMS arr[] = {ABSTRACTINTERFACE_ISUP};						\
VEInterfaceCallpointWorker::VEInterfaceCallpoint(ifname, arr, &_status);		\
}while(0);										\


#define vesh(ifname)									\
do{											\
bool _status = false;									\
DCMENUMS arr[] = {ABSTRACTINTERFACE_ISUP};						\
VEInterfaceCallpointWorker::VEInterfaceCallpoint(ifname, arr, &_status);		\
}while(0);										\

/* Interface config Macros*/
#define pimsp(_ifname)									\
do{											\
bool _enable = true;									\
DCMENUMS arr[] = {PIMCONFIG_PIM_SPARSE};						\
PIMConfigCallpointWorker::PIMConfigCallpoint(_ifname, arr, &_enable);  			\
}while(0);										\

#define nopimsp(_ifname)								\
do{											\
bool _enable = false;									\
DCMENUMS arr[] = {PIMCONFIG_PIM_SPARSE};						\
PIMConfigCallpointWorker::PIMConfigCallpoint(_ifname, arr, &_enable);		        \
}while(0);										\

#define pimdrp(_ifname, _drp)								\
do{											\
unsigned int __drp = _drp;								\
DCMENUMS arr[] = {PIMCONFIG_DR_PRIORITY};						\
PIMConfigCallpointWorker::PIMConfigCallpoint(_ifname, arr, &__drp);			\
}while(0);										\

#define pimttl(_ifname, _ttl)								\
do{											\
unsigned int __ttl = _ttl;								\
DCMENUMS arr[] = {PIMCONFIG_TTL_THRESHOLD};						\
PIMConfigCallpointWorker::PIMConfigCallpoint(_ifname, arr, &__ttl);			\
}while(0);										\


#define ipaddr(_ifname, _ipaddr)							\
do{											\
string __ipaddr = _ipaddr;								\
DCMENUMS arr[] = {ABSTRACTL3CONFIG_IP_ADDRESS};						\
PIMConfigCallpointWorker::PIMConfigCallpoint(_ifname, arr, &__ipaddr);			\
}while(0);										\

#define pvrf(arg)									\
do{											\
DCMENUMS arr[] = {DUMP};								\
VRFCallpointWorker::VRFCallpoint(arg, arr, 0, NO_REST_REQ, NULL);			\
}while(0);										\

/* Ospf commands*/
#define router_ospf(_arg)	RouterOspfCallpointWorker::cmdRouterOspf(_arg)
#define norouter_ospf(_arg)	RouterOspfCallpointWorker::noRouterOspf(_arg)

#define ospfar(_vrf, _arg)								\
do{											\
unsigned int __area = _arg;								\
DCMENUMS arr[] = {ROUTEROSPF_OSPFAREA}; 	                                        \
RouterOspfCallpointWorker::RouterOspfCallpoint(_vrf,arr,&__area, NO_REST_REQ, NULL);	\
}while(0);										\


#define ospfdis(_vrf, _arg)								\
do{											\
unsigned int __dis = _arg;								\
DCMENUMS arr[] = {ROUTEROSPF_OSPFDISTANCE}; 	                                        \
RouterOspfCallpointWorker::RouterOspfCallpoint(_vrf,arr,&__dis, NO_REST_REQ, NULL);	\
}while(0);										\

/* Bgp Commands*/

#define router_bgp(_arg)	RouterBgpCallpointWorker::cmdRouterBgp(_arg)
#define norouter_bgp(_arg)	RouterBgpCallpointWorker::noRouterBgp(_arg)

#define bgpar(_vrf, _arg)								\
do{											\
unsigned int __area = _arg;								\
DCMENUMS arr[] = {ROUTERBGP_BGPAREA};	 	                                        \
RouterBgpCallpointWorker::RouterBgpCallpoint(_vrf,arr,&__area, NO_REST_REQ, NULL);	\
}while(0);										\


#define bgpdis(_vrf, _arg)								\
do{											\
unsigned int __dis = _arg;								\
DCMENUMS arr[] = {ROUTERBGP_BGPDISTANCE}; 	                                        \
RouterBgpCallpointWorker::RouterBgpCallpoint(_vrf,arr,&__dis, NO_REST_REQ, NULL);	\
}while(0);										\

