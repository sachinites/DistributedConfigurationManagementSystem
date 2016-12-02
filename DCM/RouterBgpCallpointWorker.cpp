#include "RouterBgpCallpointWorker.h"
#include "DCM.h"
#include "VRF.h"
#include <stdio.h>
#include "RouterBgp.h"
#include "DCMEnums.h"
#include "RouterModuleGenericCallpoint.h"

RouterBgp*
RouterBgpCallpointWorker::cmdRouterBgp(string vrf_name){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error: vrf %s do not exist\n", vrf_name.c_str());
		return NULL;
	}
	return RouterBgp::instantiateRouterBgp(vrf);
}

void
RouterBgpCallpointWorker::noRouterBgp(string vrf_name){
        VRF *vrf = DCM::getVRF(vrf_name);
        if(!vrf){
                printf("Error: vrf %s do not exist\n", vrf_name.c_str());
                return;
        }
        vrf->delete_routingModulebyClassName("RouterBgp.class");

}

void
RouterBgpCallpointWorker::RouterBgpCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REST_REQ_TYPE, void *rest_out){
        RouterModuleGenericCallpoint::RouterModuleCallpoint(vrf_name, attr, new_val, REST_REQ_TYPE, rest_out, string("RouterBgp.class"));
}

