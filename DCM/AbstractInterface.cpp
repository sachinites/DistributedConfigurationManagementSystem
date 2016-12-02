#include <stdio.h>
#include "AbstractInterface.h"
#include "AbstractL3Config.h"
#include "VRF.h"
#include "DCM.h"
#include "AbstractInterfaceEnums.h"
#include "RESTServer.h"
#include "Utils.h"

unsigned int AbstractInterface::ifindex_counter = 1;

AbstractInterface::AbstractInterface(){}

AbstractInterface::~AbstractInterface(){
}


void
AbstractInterface::load_enums_for_rest(){
        RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTINTERFACE_INTERFACE_NAME)]
                        = ABSTRACTINTERFACE_INTERFACE_NAME;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTINTERFACE_IF_TYPE)]
			= ABSTRACTINTERFACE_IF_TYPE;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTINTERFACE_IFINDEX)]
			= ABSTRACTINTERFACE_IFINDEX;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTINTERFACE_ISUP)]
			= ABSTRACTINTERFACE_ISUP;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ABSTRACTINTERFACE_VRF)]
			= ABSTRACTINTERFACE_VRF;
}

void AbstractInterface::setisup(bool isup){
	m_isup = isup;
}

bool AbstractInterface::getisup(){
	return m_isup;
}

void AbstractInterface::setinterface_name(string ifname){
	m_interface_name = ifname;
}

string AbstractInterface::getinterface_name(){
	return m_interface_name;
}

void AbstractInterface::setif_type(interface_type_t if_type){
	m_if_type = if_type;
}

interface_type_t AbstractInterface::getif_type(){
	return m_if_type;
}


void AbstractInterface::setifindex(){
	m_ifindex = ifindex_counter++;
}

unsigned int AbstractInterface::getifindex(){
	return m_ifindex;
}

void AbstractInterface::setVRF(VRF *vrf){
	m_vrf = vrf;
}

VRF* AbstractInterface::getVRF(){
	return m_vrf;
}

string AbstractInterface::getclass_name(){
	return "AbstractInterface.class";	
}

char AbstractInterface::addl3config(AbstractL3Config *l3config){
	if(!l3config) return 0;
	for(int i =0; i < m_l3configs.size(); i++){
		if(m_l3configs[i]->getclass_name() == l3config->getclass_name()){
			printf("Error : Duplicate l3 config add attempt on interface %s, l3config = %s\n", 
						getinterface_name().c_str(), l3config->getclass_name().c_str());
			return -1;
		}
	}
	m_l3configs.push_back(l3config);
	return 0;
}


char AbstractInterface::dell3config(AbstractL3Config *l3config){
	if(!l3config) return 0;
	for(int i =0; i < m_l3configs.size(); i++){
		if(m_l3configs[i] == l3config){
			m_l3configs.erase(m_l3configs.begin() + i);
			delete l3config;
			return 0;
		}
	}
	return 0;
}

char AbstractInterface::dell3configbyClassName(string class_name){
	AbstractL3Config *l3config = NULL;
	for(int i =0; i < m_l3configs.size(); i++){
		if(m_l3configs[i]->getclass_name() == class_name){
			l3config = m_l3configs[i];
			m_l3configs.erase(m_l3configs.begin() + i);
			delete l3config;
			return 0;
		}
	}
	return 0;
}

AbstractL3Config*  AbstractInterface::getl3configbyClassName(string class_name){

	for(int i =0; i < m_l3configs.size(); i++){
		if(m_l3configs[i]->getclass_name() == class_name){
			return m_l3configs[i];
		}
	}
	return NULL;
}

int
validation(DCMENUMS* attr, void *new_value){
	return 0;
}

int AbstractInterface::update(DCMENUMS *attr, void *new_value){
	switch(attr[0]){
		case ABSTRACTINTERFACE_VRF:
			{
				string new_vrf_name = *(string *)new_value;
				if(new_vrf_name == getVRF()->getvrf_name())
					return 0;
				VRF* vrf = DCM::getVRF(new_vrf_name);
				getVRF()->remove_interface(this);
				setVRF(vrf);
				vrf->add_interface(this);
			}
			break;
		case ABSTRACTINTERFACE_INTERFACE_NAME:
		case ABSTRACTINTERFACE_IFINDEX:
			printf("Error : Invalid Operation : Immutable attribute :%s\n", (*(string *)new_value).c_str());
			break;
		case ABSTRACTINTERFACE_ISUP:
			setisup(*(bool *)new_value);
			break;
		default:
			;/* if no case is hit, then it may not be error*/
	}
	return 0;
}


int AbstractInterface::rest_get(DCMENUMS *attr, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	switch(attr[0]){
		case ABSTRACTINTERFACE_VRF:
			{
				(*_map)[getAttributeStr(attr[0])] = getVRF()->getvrf_name();
			}
			break;
		case ABSTRACTINTERFACE_INTERFACE_NAME:
			{
				(*_map)[getAttributeStr(attr[0])] = getinterface_name();
			}
			break;
		case ABSTRACTINTERFACE_IFINDEX:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] = string(itoa(getifindex(), buff, 10));
			}
			break;
		case ABSTRACTINTERFACE_ISUP:
			{
				(*_map)[getAttributeStr(attr[0])] = (getisup() ? string("UP") : string("DOWN"));
			}
			break;
		case SELF_COMPLETE:
			{
				DCMENUMS _attr;
				_attr = ABSTRACTINTERFACE_VRF;			rest_get(&_attr, (void *)_map);
				_attr = ABSTRACTINTERFACE_INTERFACE_NAME;	rest_get(&_attr, (void *)_map);
				_attr = ABSTRACTINTERFACE_IFINDEX;		rest_get(&_attr, (void *)_map);
				_attr = ABSTRACTINTERFACE_ISUP;			rest_get(&_attr, (void *)_map);
			}
		default:
			;/* if no case is hit, then it may not be error*/
	}
	return 0;
}


string AbstractInterface::getAttributeStr(int attr){
	switch(attr){
		case ABSTRACTINTERFACE_VRF:
			return "ABSTRACTINTERFACE_VRF";
		case ABSTRACTINTERFACE_IF_TYPE:
			return "ABSTRACTINTERFACE_IF_TYPE";
		case ABSTRACTINTERFACE_IFINDEX:
			return "ABSTRACTINTERFACE_IFINDEX";
		case ABSTRACTINTERFACE_ISUP:
			return "ABSTRACTINTERFACE_ISUP";
		case ABSTRACTINTERFACE_INTERFACE_NAME:
			return "ABSTRACTINTERFACE_INTERFACE_NAME";
		default:
			return "UNKNWON";
		
	}
}


void AbstractInterface::dump(){
	printf("Interface       : %s\n", getinterface_name().c_str());
        printf("If_type         : %u\n", getif_type());
        printf("ifindex         : %u\n", getifindex());
	printf("isup		: %s\n", getisup() ? "UP" : "DOWN");
	printf("VRF		: %s\n", getVRF()->getvrf_name().c_str());
	printf("config : ");
	printf("L3 config\n");
	if(!m_l3configs.size()){
		printf("No L3Config\n");
		goto printL2Config;
	}
	for(int i =0; i < m_l3configs.size(); i++){
		m_l3configs[i]->dump();
	}
	printL2Config:
	;
#if 0	
	if(!m_l2configs.size()){
		printf("No L2Config");
	}

	for(int i =0; i < m_l3configs.size(); i++){
		m_l2configs[i]->dump_l3_config();
	}
#endif
}
