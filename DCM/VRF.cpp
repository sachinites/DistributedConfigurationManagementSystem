#include "DCM.h"
#include <stdio.h>
#include "AbstractRouterVRF.h"
#include "AbstractInterface.h"
#include "AbstractL3Config.h"
#include "VRF.h"
#include "RESTServer.h"
#include "Utils.h"
#include "VRFCallpointWorker.h"
#include "VRFEnums.h"

VRF::VRF(string vrf_name){
	m_vrf_name = vrf_name;
}

VRF::VRF(){
	m_vrf_name = "default-vrf";
}

void VRF::setvrf_name(string vrf_name){
	m_vrf_name = vrf_name;	
}

string VRF::getvrf_name(){
	return m_vrf_name;
}

VRF::~VRF(){
	AbstractRouterVRF *module = NULL;
	AbstractInterface *intf = NULL;

	printf("VRF instance %s deleted.\n Cleaning up %d modules ... \n", getvrf_name().c_str(), m_modules.size());
	while(!m_modules.empty()){
		module = m_modules.back();
		m_modules.pop_back();
		delete module;
	}

	printf(" Cleaning up %d interfaces ...\n",  m_interfaces.size());
	while(!m_interfaces.empty()){
		intf = m_interfaces.back();
		m_interfaces.pop_back();

		/* ToDo : Delete all config on that inteface */

		AbstractL3Config *l3config = NULL;
		while(!intf->m_l3configs.empty()){
			l3config = intf->m_l3configs.back();
			intf->m_l3configs.pop_back();
			delete l3config;
		}				

		delete intf;
	}
	DCM::removeVRF(getvrf_name());
}

VRF* VRF::instantiateVRF(string vrf_name){
	if(DCM::isVRFPresent(vrf_name)){
		printf("VRF %s already exist\n", vrf_name.c_str());
		return DCM::getVRF(vrf_name);
	}

	VRF *vrf = new VRF(vrf_name);
	if(DCM::saveVRF(vrf) == 0)
		return vrf;
	delete vrf;
	return NULL;
}

string VRF::getclass_name(){
	return "VRF.class";
}

int VRF::add_routingModule(AbstractRouterVRF *module){
	if(!module) return 0;
	
	if(module->getVRF()->getvrf_name() == getvrf_name()){
		for(int i = 0; i < m_modules.size(); i++){
			if(m_modules[i]->getclass_name() == module->getclass_name()){
				printf("Error : duplicate modules association with same VRF. Module = %s, VRF = %s\n", module->getclass_name().c_str(), getvrf_name().c_str());
				return -1;
			}
		}
		m_modules.push_back(module);
		return 0;
	}
	else{
		printf("Error : unmatched VRF Association tried. VRF = %s, associated child VRF = %s, module = %s\n", 
			getvrf_name().c_str(), module->getVRF()->getvrf_name().c_str(), module->getclass_name().c_str());
		return -1;
	}
}

AbstractRouterVRF* 
VRF::get_routingModule(string class_name){
	for(int i = 0; i < m_modules.size(); i++){
		if(m_modules[i]->getclass_name() == class_name){
			return m_modules[i];
		}
	}
	return NULL;
}


int VRF::delete_routingModule(AbstractRouterVRF *module){
	if(!m_modules.size() || !module)
		return 0;

	for(int i = 0; i < m_modules.size(); i++){
		if(m_modules[i] == module){
			m_modules.erase(m_modules.begin() + i);
			delete module;
			return 0;
		}
	}
	return 0;	
}

int VRF::delete_routingModulebyClassName(string module_name){

	if(!m_modules.size()) return 0;
	AbstractRouterVRF *module = NULL;
	for(int i = 0; i < m_modules.size(); i++){
		if(m_modules[i]->getclass_name() == module_name){
			module = m_modules[i];
			m_modules.erase(m_modules.begin() + i);
			delete module;
			return 0;
		}
	}
	
}


int VRF::remove_routingModule(AbstractRouterVRF *module){
	if(!m_modules.size() || !module)
		return 0;

	for(int i = 0; i < m_modules.size(); i++){
		if(m_modules[i] == module){
			m_modules.erase(m_modules.begin() + i);
			return 0;
		}
	}
	return 0;	
}

int VRF::remove_routingModulebyClassName(string module_name){

	if(!m_modules.size()) return 0;
	for(int i = 0; i < m_modules.size(); i++){
		if(m_modules[i]->getclass_name() == module_name){
			m_modules.erase(m_modules.begin() + i);
			return 0;
		}
	}
	
}
/* Interface Management functions for VRF*/

int VRF::add_interface(AbstractInterface *interface){
	if(!interface) return 0;
	
	if(interface->getVRF()->getvrf_name() == getvrf_name()){
		m_interfaces.push_back(interface);
		return 0;
	}
	else{
		printf("Error : unmatched VRF Association tried. VRF = %s, associated child VRF = %s, interface = %s\n", 
			getvrf_name().c_str(), interface->getVRF()->getvrf_name().c_str(), interface->getinterface_name().c_str());
		return -1;
	}
}

int VRF::delete_interface(AbstractInterface *interface){
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i]->getifindex() == interface->getifindex()){
			m_interfaces.erase(m_interfaces.begin() + i);
			delete interface;
			return 0;
		}
	}
	return 0;
}

int VRF::delete_interfacebyClassName(string if_class_name){
	AbstractInterface *interface = NULL;
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i]->getclass_name() == if_class_name){
			interface = m_interfaces[i];
			m_interfaces.erase(m_interfaces.begin() + i);
			delete interface;
			return 0;
		}
	}
	return 0;
}

int VRF::remove_interface(AbstractInterface *interface){
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i] == interface){
			m_interfaces.erase(m_interfaces.begin() + i);
			return 0;
		}
	}
	return 0;
}


int VRF::remove_interfacebyClassName(string if_class_name){
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i]->getclass_name() == if_class_name){
			m_interfaces.erase(m_interfaces.begin() + i);
			return 0;
		}
	}
	return 0;
}


int VRF::delete_interfacebyIfndex(unsigned int ifindex){
	AbstractInterface *interface = NULL;
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i]->getifindex() == ifindex){
			interface = m_interfaces[i];
			m_interfaces.erase(m_interfaces.begin() + i);
			delete interface;
			return 0;
		}
	}
	return 0;
}

char VRF::isinterfacePresentinVRF(unsigned int ifindex){
	for(int i = 0; i < m_interfaces.size(); i++){
		if(m_interfaces[i]->getifindex() == ifindex)
			return 1;
	}
	return 0;
}

char VRF::isRoutingModulePresentinVRF(string module_class_name){
	for(int i = 0 ; i < m_modules.size(); i++){
		if( m_modules[i]->getclass_name() == module_class_name)
			return 1;
	}
	return 0;
}

void VRF::dump(){
	printf("\n **Dumping VRF : %s**\n", getvrf_name().c_str());
	printf("No of Modules enabled : %d\n", m_modules.size());
	for(int i = 0 ; i < m_modules.size(); i++){
		m_modules[i]->dump();
	}
	printf("No of Interfaces : %d\n", m_interfaces.size());
	for(int i = 0 ; i < m_interfaces.size(); i++){
		m_interfaces[i]->dump();
	}
	
	printf("**VRF : %s End**\n", getvrf_name().c_str());
}


void 
VRF::load_enums_for_rest(){
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(VRF_VRF_NAME)]
		= VRF_VRF_NAME;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(VRF_ROUTING_MODULES)]
		= VRF_ROUTING_MODULES;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(VRF_INTERFACES)]
		= VRF_INTERFACES;
}

string 
VRF::getAttributeStr(int attr){
	switch(attr){
		case VRF_VRF_NAME:
			return "VRF_VRF_NAME";
		case VRF_ROUTING_MODULES:
			return "VRF_ROUTING_MODULES";
		case VRF_INTERFACES:
			return "VRF_INTERFACES";
		default:
			return "UNKNOWN";
	}
}

void 
VRF::load_callpoint_for_rest(){
	RESTServer::CALL_POINT_MAPPING[string("VRF.class")]
                        = VRFCallpointWorker::VRFCallpoint;
}

int 
VRF::rest_get(DCMENUMS *attr, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	switch(attr[0]){
		case VRF_VRF_NAME:
			{
				(*_map)[getAttributeStr(attr[0])] = getvrf_name();
			}
			break;
		case VRF_ROUTING_MODULES:
			{
				int i = 0;
				DCMENUMS _attr = SELF_COMPLETE;
				for(i = 0; i < m_modules.size(); i++){
					m_modules[i]->rest_get(&_attr, (void *)_map);
				}
			}
			break;
		case VRF_INTERFACES:
			{
				#if 0
				int i = 0;
				DCMENUMS _attr = SELF_COMPLETE;
				for(i = 0; i < m_interfaces.size(); i++){
					m_interfaces[i]->rest_get(&_attr, (void *)_map);
				}
				#endif
			}
			break;
		case SELF_COMPLETE:
			{
				DCMENUMS _attr;
				_attr = VRF_VRF_NAME;		rest_get(&_attr, (void *)_map);
				_attr = VRF_ROUTING_MODULES; 	rest_get(&_attr, (void *)_map);
				_attr = VRF_INTERFACES; 	rest_get(&_attr, (void *)_map);
				break;
			}
		default:
			printf("%s(): Unknown Attribute\n", __FUNCTION__);
	}	
	return 0;
}

