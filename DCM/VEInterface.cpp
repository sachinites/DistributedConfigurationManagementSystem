#include "VEInterface.h"
#include <stdio.h>
#include "VRF.h"
#include "DCM.h"
#include "VEInterfaceEnums.h"

void VEInterface::setvlanid(unsigned int vlanid){
	m_vlanid = vlanid;
}

unsigned int VEInterface::getvlanid(){
	return m_vlanid;
}

void VEInterface::setipaddress(string ip){
	m_ipaddress = ip;
}

string VEInterface::getipaddress(){
	return m_ipaddress;
}

string VEInterface::getclass_name(){
	return "VEInterface.class";
}

VEInterface::~VEInterface(){
}

VEInterface::VEInterface(string vrf_name, string ifname, unsigned int vlanid){
	setinterface_name(ifname);
	setif_type(VE);
	setifindex();
	setVRF(DCM::getVRF(vrf_name));
	setvlanid(vlanid);
	setipaddress("Not assigned");
	setisup(false);
}

VEInterface* VEInterface::instantiateVEInterface(string vrf_name, string ifname, unsigned int vlanid){
	if(ifname.compare(0,2,"ve")) {
		printf("Error: Invalid interface name : %s for instantiating %s object\n", 
			ifname.c_str(), getclass_name().c_str());
		return NULL;
	}

	VRF *vrf = NULL;
	vrf = DCM::getVRF(vrf_name);
	if(!vrf) return NULL;
	if(DCM::isIFPresent(ifname)){
		printf("Error : Interface %s already exists in VRF %s\n", ifname.c_str(), vrf->getvrf_name().c_str());
		return NULL;
	}
	VEInterface *ve_intf = new VEInterface(vrf_name, ifname, vlanid);
	vrf->add_interface(ve_intf);
	DCM::saveIF(dynamic_cast<AbstractInterface *>(ve_intf));		
	return ve_intf;
}

int VEInterface::update(DCMENUMS *attr, void *new_value){
	switch(attr[0]){
		case VEINTERFACE_VLANID:
			setvlanid(*(unsigned int *)new_value);
			break;
		case VEINTERFACE_IPADDRESS:
			setipaddress(*(string *)new_value);
			break;
		default:
			this->AbstractInterface::update(attr, new_value);
	}
	return 0;
}

string VEInterface::getAttributeStr(int attr){
	switch(attr){
		case VEINTERFACE_VLANID:
			return "VEINTERFACE_VLANID";
		case VEINTERFACE_IPADDRESS:
			return "VEINTERFACE_IPADDRESS";
		default:
			return "UNKNOWN";
	}
}


void VEInterface::dump(){
	this->AbstractInterface::dump();
	printf("class_name	: %s\n", getclass_name().c_str());
	printf("vlanid		: %u\n", getvlanid());
	printf("Ip-address      : %s\n", getipaddress().c_str());
	printf("--------------------------\n\n");
}

