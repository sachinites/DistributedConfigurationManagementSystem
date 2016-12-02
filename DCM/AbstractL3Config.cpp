#include "AbstractL3Config.h"
#include <stdio.h>
#include "AbstractL3ConfigEnums.h"

AbstractL3Config::AbstractL3Config(){}
AbstractL3Config::~AbstractL3Config(){}

void AbstractL3Config::setip_address(string ip_address){
	m_ip_address = ip_address;
}

string AbstractL3Config::getip_address(){
	return m_ip_address;
}

string AbstractL3Config::getclass_name(){
	return "AbstractL3Config.class";
}

void AbstractL3Config::dump(){
	printf("	ip address 	= %s\n", getip_address().c_str());
}

int
AbstractL3Config::validation(int *attr, void *new_value){
	return 0;
}

int
AbstractL3Config::update(int *attr, void *new_value){
	if(validation(attr, new_value)){
		//printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
		return -1;
	}

	switch(attr[0]){
		case ABSTRACTL3CONFIG_IP_ADDRESS:
			setip_address(*(string *)new_value);
			break;
		default:
			;
				
	}
}
