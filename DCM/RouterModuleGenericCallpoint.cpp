#include "RouterModuleGenericCallpoint.h"
#include "VRF.h"
#include "AbstractRouterVRF.h"
#include "DCM.h"
#include <stdio.h>
using namespace std;

void 
RouterModuleGenericCallpoint::RouterModuleCallpoint(string vrf_name,
                                                         DCMENUMS *attr,
                                                         void *new_val,
                                                         int REST_REQ_TYPE,
                                                         void *rest_out,
                                                         string moduleclassname ){
	VRF *vrf = DCM::getVRF(vrf_name);
	if(!vrf){
		printf("Error : vrf %s do not exist\n", vrf_name.c_str());
		return;
	}
	AbstractRouterVRF* module = vrf->get_routingModule(moduleclassname);
	if(!module){
		printf("Error : %s module is not present in VRF %s\n", moduleclassname.c_str(), vrf->getvrf_name().c_str());                 
		return;
	}

	switch(REST_REQ_TYPE){

		case NO_REST_REQ:
			{
				if(attr[0] == DUMP){
					module->dump();
					return;
				}
				module->update(attr, new_val);
			}
			break;

		case REST_POST_REQ:
			{

			}
			break;
		case REST_GET_REQ:
			{
				if(attr[0] == DUMP){
					printf("DUMP attibute not supported in REST\n");
					return;
				}
				module->rest_get(attr, rest_out);
			}
			break;
		default:
			printf("UNKNOWN Request\n");
			return;
	} // switch ends
}
