#include "RouterOspfCallpointWorker.h"
#include "DCM.h"
#include "VRF.h"
#include <stdio.h>
#include "RouterOspf.h"
#include "DCMEnums.h"
#include "RouterModuleGenericCallpoint.h"

RouterOspf*
RouterOspfCallpointWorker::cmdRouterOspf(string vrf_name){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error: vrf %s do not exist\n", vrf_name.c_str());
		return NULL;
	}
	return RouterOspf::instantiateRouterOspf(vrf);
}

void
RouterOspfCallpointWorker::noRouterOspf(string vrf_name){
        VRF *vrf = DCM::getVRF(vrf_name);
        if(!vrf){
                printf("Error: vrf %s do not exist\n", vrf_name.c_str());
                return;
        }
        vrf->delete_routingModulebyClassName("RouterOspf.class");
}

void
RouterOspfCallpointWorker::RouterOspfCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REST_REQ_TYPE, void *rest_out){
	RouterModuleGenericCallpoint::RouterModuleCallpoint(vrf_name, attr, new_val, REST_REQ_TYPE, rest_out, string("RouterOspf.class"));
}

