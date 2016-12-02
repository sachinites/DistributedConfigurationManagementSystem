#include "RouterOspf.h"
#include <stdio.h>
#include "VRF.h"
#include "DCM.h"
#include "RouterOspfEnums.h"
#include "Rule.h"
#include "RESTServer.h"
#include "RouterOspfCallpointWorker.h"
#include "Utils.h"

RouterOspf::RouterOspf(VRF *vrf){
	setVRF(vrf);
	load_rules();
}


RouterOspf::~RouterOspf(){
	printf(" %s deleted\n", getclass_name().c_str());
}

void
RouterOspf::load_enums_for_rest(){
        RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTEROSPF_OSPFAREA)]
                = ROUTEROSPF_OSPFAREA;
        RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTEROSPF_OSPFDISTANCE)]
                = ROUTEROSPF_OSPFDISTANCE;
}


void
RouterOspf::load_callpoint_for_rest(){
        RESTServer::CALL_POINT_MAPPING[string("RouterOspf.class")]
                        = RouterOspfCallpointWorker::RouterOspfCallpoint;
}

int
RouterOspf::rest_get(DCMENUMS *attr, void *rest_out){
        map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
        switch(attr[0]){
                case ROUTEROSPF_OSPFAREA:
                        {
				char buff[32];
                                (*_map)[getAttributeStr(attr[0])] = 
					string(itoa(getarea(), buff, 10));
                        }
                        break;
                case ROUTEROSPF_OSPFDISTANCE:
                        {
                                char buff[32];
                                (*_map)[getAttributeStr(attr[0])] =
                                                string(itoa(getdistance(), buff, 10));
                        }
                        break;
		 case SELF_COMPLETE:
                        DCMENUMS _attr;
                        _attr = ROUTEROSPF_OSPFAREA;     rest_get(&_attr, (void *)_map);
                        _attr = ROUTEROSPF_OSPFDISTANCE; rest_get(&_attr, (void *)_map);
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


void RouterOspf::setarea(unsigned int area){
	m_area = area;
}

void RouterOspf::setdistance(unsigned int distance){
	m_distance = distance;
}

unsigned int RouterOspf::getarea(){
	return m_area;
}

unsigned int RouterOspf::getdistance(){
	return m_distance;
}

string RouterOspf::getclass_name(){
	return "RouterOspf.class";
}

void
RouterOspf::load_rules(){

}


RouterOspf* RouterOspf::instantiateRouterOspf(VRF *vrf){
	/* validaton check that RouterOspf Object is not already present in VRF module list*/
	RouterOspf *module = new RouterOspf(vrf);
	if(vrf->add_routingModule(module) == 0){
		return module;
	}
	delete module;
	return NULL;
}

int
RouterOspf::validation(DCMENUMS *attr, void *new_value){

        return 0; // success
}


int RouterOspf::update(DCMENUMS *attr, void *new_value){

       if(validation(attr, new_value)){
    //            printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
                return -1;
        }

        switch (attr[0])
        {
                case ROUTEROSPF_OSPFAREA:
                        setarea(*(unsigned int *)new_value);
                        break;
                case ROUTEROSPF_OSPFDISTANCE:
                        setdistance(*(unsigned int *)new_value);
                        break;
                default:
			/* if no Child class Attribute is to be updated, might be parent class
			   attribute needs updattion*/
			this->AbstractRouterVRF::update(attr, new_value);

        }
        return 0;
}

string
RouterOspf::getAttributeStr(int attr){
	switch(attr){
		case ROUTEROSPF_OSPFAREA:
			return "ROUTEROSPF_OSPFAREA";
		case ROUTEROSPF_OSPFDISTANCE:
			return "ROUTEROSPF_OSPFDISTANCE";
		default:
		        return "UNKNOWN";
}
}

void RouterOspf::dump(){
	this->AbstractRouterVRF::dump();
	printf("  class Name :  %s\n" , getclass_name().c_str());
	printf("  area	     :  %u\n",  getarea());
	printf("  distance   :  %u\n",  getdistance());
	printf(" ----------------------\n");
}
