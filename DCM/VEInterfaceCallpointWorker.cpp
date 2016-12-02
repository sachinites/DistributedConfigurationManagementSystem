#include "stdio.h"
#include "VEInterfaceCallpointWorker.h"
#include "VEInterface.h"
#include "DCM.h"
#include "VRF.h"
#include "DCMEnums.h"

using namespace std;

VEInterfaceCallpointWorker::VEInterfaceCallpointWorker(){}

void
VEInterfaceCallpointWorker::createVe(string vrf_name, string ifname, unsigned int vlanid){
	VEInterface::instantiateVEInterface(vrf_name, ifname, vlanid);		
}

void VEInterfaceCallpointWorker::delVe(string ifname){
	VEInterface* ve_intf = static_cast<VEInterface *>(DCM::getIF(ifname));
	if(!ve_intf){
		printf("%s():Error : Interface %s do not exist\n", __FUNCTION__, ifname.c_str());
		return;
	}

	// remove interface from Hashmap
	DCM::removeIF(ifname);
	VRF *vrf = ve_intf->getVRF();
	// remove interface from VRF List
	vrf->delete_interface(ve_intf);
}


void VEInterfaceCallpointWorker::VEInterfaceCallpoint(string if_name, DCMENUMS *attr, void *new_val){
	AbstractInterface *interface = DCM::getIF(if_name);
	if(!interface){
		printf("%s():Error : Interface %s is not found\n", __FUNCTION__, if_name.c_str());
		return;
	}	
	if(attr[0] == DUMP){
		interface->dump();
		return;
	}		
	
	interface->update(attr, new_val);
}
