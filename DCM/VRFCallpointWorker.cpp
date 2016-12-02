#include "VRFCallpointWorker.h"
#include "VRF.h"
#include "stdio.h"
#include "DCM.h"


VRF*
VRFCallpointWorker::cmdVRF(string vrf_name){
	return VRF::instantiateVRF(vrf_name);
}

void
VRFCallpointWorker::cmdnoVRF(string vrf_name){
	delete DCM::getVRF(vrf_name);
}

void
VRFCallpointWorker::VRFCallpoint(string vrf_name, DCMENUMS* attr, void *new_val, int REST_REQ_TYPE, void *rest_out){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error : vrf %s do not exist\n", vrf_name.c_str());
		return;
	}

	switch(REST_REQ_TYPE){
		case NO_REST_REQ:
			{
				switch(attr[0]){
					case DUMP:
						vrf->dump();
						break;
				}
			}
			break;
		case REST_POST_REQ:
			break;
		case REST_GET_REQ:
			{
				if(attr[0] == DUMP){
					printf("DUMP attibute not supported in REST\n");
					return;
				}
				vrf->rest_get(attr, rest_out);
			}
			break;
		default:
			printf("UNKNOWN Request\n");
			return;
	}
}
