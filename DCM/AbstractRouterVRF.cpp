#include "AbstractRouterVRF.h"
#include <stdio.h>
#include "VRF.h"
#include "DCM.h"
#include "Rule.h"
#include "AbstractRouterVRFEnums.h"
#include "AbstractInterface.h"
#include "AbstractL3Config.h"
#include "RESTServer.h"
using namespace std;

string AbstractRouterVRF::getclass_name(){
	return "AbstractRouterVRF.class";
}

void
AbstractRouterVRF::load_enums_for_rest(){
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTROUTERVRF_VRF)]
			= ABSTRACTROUTERVRF_VRF;
}


AbstractRouterVRF::AbstractRouterVRF(){
}

AbstractRouterVRF::~AbstractRouterVRF(){
/* Delete Rules objects here */
	for (map<unsigned int , Rule*>::iterator it=m_rules.begin(); it!=m_rules.end(); it++){
		delete it->second;
	}
}

void AbstractRouterVRF::dump(){
	printf("  vrf        :  %s\n",  getVRF()->getvrf_name().c_str());
}

VRF* AbstractRouterVRF::getVRF(){
	return m_vrf;
}

void AbstractRouterVRF::setVRF(VRF *vrf){
	m_vrf = vrf;
}

int 
AbstractRouterVRF::validation(int *attr, void *new_value){

	return 0; // success
}

int AbstractRouterVRF::update(int *attr, void *new_value){
	if(validation(attr, new_value)){
		//printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
		return -1;
	}

	switch(attr[0]){
		case ABSTRACTROUTERVRF_VRF:
			{
				string new_vrf_name = *(string *)new_value;
				if(new_vrf_name == getVRF()->getvrf_name())
					return 0;
				VRF* vrf = DCM::getVRF(new_vrf_name);
				getVRF()->remove_routingModule(this);
				setVRF(vrf);
				vrf->add_routingModule(this);
			}
			break;
		default:
			;/* if no case is hit, then it may not be error*/
	}
	return 0;
}


int AbstractRouterVRF::rest_get(int *attr, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	switch(attr[0]){
		case ABSTRACTROUTERVRF_VRF:
			{
				(*_map)[getAttributeStr(attr[0])] = getVRF()->getvrf_name();	
			}
			break;
		/* More Aggregated Attributes here*/
		 case SELF_COMPLETE:
				DCMENUMS _attr;
				_attr = ABSTRACTROUTERVRF_VRF; AbstractRouterVRF::rest_get(&_attr, (void *)_map);
                	        break;
		default:
			;/* if no case is hit, then it may not be error*/
	}
	return 0;
}

string AbstractRouterVRF::getAttributeStr(int attr){
	switch(attr){
		case ABSTRACTROUTERVRF_VRF:
			return "ABSTRACTROUTERVRF_VRF";
		default:
			return "UNKNOWN";
	}
}

void AbstractRouterVRF::add_rule(unsigned int index, Rule *rule){
	m_rules[index] = rule;
}

#if 1
void
AbstractRouterVRF::execute_delete_rules(){
	for (map<unsigned int , Rule*>::iterator it=m_rules.begin(); it!=m_rules.end(); it++){
		Rule *rule = it->second;
		if(rule->rtype == DELETE)
			rule->execute_rule(getVRF());
	}
}


void
AbstractRouterVRF::execute_create_rules(){
	for (map<unsigned int , Rule*>::iterator it=m_rules.begin(); it!=m_rules.end(); it++){
		Rule *rule = it->second;
		if(rule->rtype == CREATE)
			rule->execute_rule(NULL);
	}
}

#endif


