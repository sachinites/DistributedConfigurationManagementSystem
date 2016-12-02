#include "RouterBgp.h"
#include <stdio.h>
#include "VRF.h"
#include "DCM.h"
#include "RouterBgpEnums.h"
#include "Rule.h"
#include "RESTServer.h"
#include "RouterBgpCallpointWorker.h"
#include "Utils.h"

RouterBgp::RouterBgp(VRF *vrf){
	setVRF(vrf);
	load_rules();
}

RouterBgp::~RouterBgp(){
	printf(" %s deleted\n", getclass_name().c_str());
}

void RouterBgp::setbgparea(unsigned int area){
	m_bgparea = area;
}

void RouterBgp::setbgpdistance(unsigned int distance){
	m_bgpdistance = distance;
}

unsigned int RouterBgp::getbgparea(){
	return m_bgparea;
}

unsigned int RouterBgp::getbgpdistance(){
	return m_bgpdistance;
}

string RouterBgp::getclass_name(){
	return "RouterBgp.class";
}

void
RouterBgp::load_rules(){

}

void
RouterBgp::load_enums_for_rest(){
        RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERBGP_BGPAREA)]
                = ROUTERBGP_BGPAREA;
        RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERBGP_BGPDISTANCE)]
                = ROUTERBGP_BGPDISTANCE;
}

void
RouterBgp::load_callpoint_for_rest(){
        RESTServer::CALL_POINT_MAPPING[string("RouterBgp.class")]
                        = RouterBgpCallpointWorker::RouterBgpCallpoint;
}



RouterBgp* RouterBgp::instantiateRouterBgp(VRF *vrf){
	/* validaton check that RouterBgp Object is not already present in VRF module list*/
	RouterBgp *module = new RouterBgp(vrf);
	if(vrf->add_routingModule(module) == 0){
		return module;
	}
	delete module;
	return NULL;
}

int
RouterBgp::validation(DCMENUMS *attr, void *new_value){

        return 0; // success
}


int RouterBgp::update(DCMENUMS *attr, void *new_value){

       if(validation(attr, new_value)){
//                printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
                return -1;
        }

        switch (attr[0])
        {
                case ROUTERBGP_BGPAREA:
                        setbgparea(*(unsigned int *)new_value);
                        break;
                case ROUTERBGP_BGPDISTANCE:
                        setbgpdistance(*(unsigned int *)new_value);
                        break;
                default:
			this->AbstractRouterVRF::update(attr, new_value);
        }
        return 0;
}


int
RouterBgp::rest_get(DCMENUMS *attr, void *rest_out){
        map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
        switch(attr[0]){
                case ROUTERBGP_BGPAREA:
                        {
				char buff[32];
                                (*_map)[getAttributeStr(attr[0])] = string(itoa(getbgparea(), buff, 10));
                        }
                        break;
                case ROUTERBGP_BGPDISTANCE:
                        {
                                char buff[32];
                                (*_map)[getAttributeStr(attr[0])] =
                                                string(itoa(getbgpdistance(), buff, 10));
                        }
                        break;
 		case SELF_COMPLETE:
			DCMENUMS _attr;
			_attr = ROUTERBGP_BGPAREA;     rest_get(&_attr, (void *)_map);
			_attr = ROUTERBGP_BGPDISTANCE; rest_get(&_attr, (void *)_map);
			/* for compostion attributes*/
			this->AbstractRouterVRF::rest_get(attr, rest_out);
                  	break;
                default:
                        /* if no Child class Attribute is to be updated, might be parent class
                        attribute needs updattion*/
                        this->AbstractRouterVRF::rest_get(attr, rest_out);
        }
        return 0;
}




string
RouterBgp::getAttributeStr(int attr){
	switch(attr){
		case ROUTERBGP_BGPAREA:
			return "ROUTERBGP_BGPAREA";
		case ROUTERBGP_BGPDISTANCE:
			return "ROUTERBGP_BGPDISTANCE";
		default:
			return "UNKNOWN";
	}
}


void RouterBgp::dump(){
	this->AbstractRouterVRF::dump();
	printf("  class Name :  %s\n" , getclass_name().c_str());
	printf("  bgparea    :  %u\n",  getbgparea());
	printf("  bgpdistance:  %u\n",  getbgpdistance());
	printf(" ----------------------\n");
}
