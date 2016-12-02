#include "RouterPimCallpointWorker.h"
#include "DCM.h"
#include "VRF.h"
#include <stdio.h>
#include "DCMEnums.h"
#include "RouterPim.h"
#include "RouterModuleGenericCallpoint.h"

RouterPim*
RouterPimCallpointWorker::cmdRouterPim(string vrf_name){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error: vrf %s do not exist\n", vrf_name.c_str());
		return NULL;
	}
	return RouterPim::instantiateRouterPim(vrf);
}

void
RouterPimCallpointWorker::noRouterPim(string vrf_name){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error: vrf %s do not exist\n", vrf_name.c_str());
		return;
	}
	vrf->delete_routingModulebyClassName("RouterPim.class");
}

void
RouterPimCallpointWorker::RouterPimCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REST_REQ_TYPE, void *rest_out){
	RouterModuleGenericCallpoint::RouterModuleCallpoint(vrf_name, attr, new_val, REST_REQ_TYPE, rest_out, string("RouterPim.class"));
}
