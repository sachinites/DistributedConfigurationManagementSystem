#include "ETHInterface.h"
#include <stdio.h>
#include "VRF.h"
#include "ETHInterfaceEnums.h"

void ETHInterface::setvlanid(unsigned int vlanid){
	m_vlanid = vlanid;
}

unsigned int ETHInterface::getvlanid(){
	return m_vlanid;
}

string ETHInterface::getclass_name(){
	return "ETHInterface.class";
}

ETHInterface::~ETHInterface(){
	printf("%s deleted\n", getclass_name().c_str());
}

void ETHInterface::setOperatingMode(if_op_mode_t mode){
	m_oper_mode = mode;	
}

if_op_mode_t
ETHInterface::getOperatingMode(){
	return m_oper_mode;
}

ETHInterface::ETHInterface(VRF *vrf, string ifname, unsigned int vlanid, if_op_mode_t mode){
	setinterface_name(ifname);
	setif_type(ETHERNET);
	setifindex();
	setvlanid(vlanid);
	setVRF(vrf);
	setOperatingMode(mode);
}

ETHInterface* ETHInterface::instantiateETHInterface(VRF *vrf, string ifname, unsigned int vlanid, if_op_mode_t mode){
	if(!vrf) return NULL;
	if(ifname.compare(0,2,"eth")) {
		printf("Error: Invalid interface name for instantiating %s object\n", getclass_name().c_str());
		return NULL;
	}

	ETHInterface *eth_intf = new ETHInterface(vrf, ifname, vlanid, mode);
	vrf->add_interface(eth_intf);
		
	return eth_intf;
}

int ETHInterface::update(DCMENUMS *attr, void *new_value){
	switch(attr[0]){
		case ETHINTERFACE_VLANID:
			setvlanid(*(unsigned int *)new_value);
			break;
		case ETHINTERFACE_OP_MODE:
			setOperatingMode(*(if_op_mode_t *)new_value);
			break;
		default:
			this->AbstractInterface::update(attr, new_value);
	}
	return 0;
}

string ETHInterface::getAttributeStr(int attr){
	switch(attr){
		case ETHINTERFACE_VLANID:
			return "ETHINTERFACE_VLANID";
		case ETHINTERFACE_OP_MODE:	
			return "ETHINTERFACE_OP_MODE";
		default:
			return "UNKNOWN";
	}
}

void ETHInterface::dump(){
	this->AbstractInterface::dump();
	printf("class_name	: %s\n", getclass_name().c_str());
	if(getOperatingMode() == L2_MODE)
		printf("vlanid		: %u\n\n", getvlanid());
	printf("Operating Mode  : %s\n", IfUtils::getIfOperationMode(getOperatingMode()).c_str());
}

