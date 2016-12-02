#include "DCM.h"
#include <stdio.h>
#include "VRF.h"
#include "AbstractInterface.h"

map<string, VRF*> DCM::VRFDB;
map<string, AbstractInterface*> DCM::IFDB;

char DCM::saveVRF(VRF *vrf){
	if(isVRFPresent(vrf->getvrf_name())){
		printf("Error : VRF %s already exist\n", vrf->getvrf_name().c_str());
		return 0;
	}

	VRFDB[vrf->getvrf_name()] = vrf;
	return 0;
}

VRF* DCM::getVRF(string vrf_name){
	if(isVRFPresent(vrf_name)){
		return VRFDB[vrf_name];
	}
	return NULL;
}

bool DCM::isVRFPresent(string vrf_name){
	 for (map<string,VRF*>::iterator it=VRFDB.begin(); it!=VRFDB.end(); it++){
		if(it->first == vrf_name)
			return true;
	 }
	 return false;
}

void DCM::removeVRF(string vrf_name){
	VRFDB.erase (vrf_name);  
}

char DCM::saveIF(AbstractInterface *intf){
	if(isIFPresent(intf->getinterface_name())){
		printf("Error : Interface %s already exist\n", intf->getinterface_name().c_str());
		return 0;
	}

	IFDB[intf->getinterface_name()] = intf;
	return 0;
}


bool DCM::isIFPresent(string if_name){
	 for (map<string,AbstractInterface*>::iterator it=IFDB.begin(); it!=IFDB.end(); it++){
		if(it->first == if_name)
			return true;
	 }
	 return false;
}


void DCM::removeIF(string if_name){
	IFDB.erase (if_name);  
}

AbstractInterface* DCM::getIF(string if_name){
        if(isIFPresent(if_name)){
                return IFDB[if_name];
        }
        return NULL;
}

