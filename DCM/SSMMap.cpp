#include "SSMMap.h"
#include "SSMMapEnums.h"
#include <stdio.h>
#include <map>
#include "RESTServer.h"
using namespace std;

SSMMap::SSMMap(){}
SSMMap::~SSMMap(){
	printf(" %s deleted\n", getclass_name().c_str());
}

void SSMMap::setpfxlst_name(string pfxlst_name){
	m_pfxlst_name = pfxlst_name;
}

string SSMMap::getpfxlst_name(){
	return m_pfxlst_name;
}

void SSMMap::setsrc_address(string src_address){
	m_src_address = src_address;
}

string SSMMap::getsrc_address(){
	return m_src_address;
}

int SSMMap::validation(DCMENUMS *attr, void *value){
	switch(attr[0]){
		case SSMMAP_SRC_ADDRESS:
			break;
		case SSMMAP_PFXLST_NAME:
		{
			string new_val = *(string *)value;
			if(new_val.length() > 32){
				printf("Error : SSM prefix list should not exceed 32 chars\n");
				return -1;
			}
		}
		break;
	}
	return 0;
}

string SSMMap::getclass_name(){
	return "SSMMap.class";
}

int SSMMap::update(DCMENUMS *attr, void *new_value){

	if(validation(attr, new_value)){
		return -1;
	}

	switch(attr[0]){
		case SSMMAP_PFXLST_NAME:
		{
			string new_val = *(string *)new_value;
			setpfxlst_name(new_val);
		}
			break;
		case SSMMAP_SRC_ADDRESS:
		{
			string new_val = *(string *)new_value;
			setsrc_address(new_val);
		}
			break;
		default:
			printf("%s(): Unknown Attribute\n", __FUNCTION__);
	}
	return 0;
}


string 
SSMMap::getAttributeStr(int attr){
	switch(attr){
		case SSMMAP_PFXLST_NAME:
			return "SSMMAP_PFXLST_NAME";
		case SSMMAP_SRC_ADDRESS:
			return "SSMMAP_SRC_ADDRESS";	
	}
}

int 
SSMMap::rest_get(DCMENUMS *attr, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	switch(attr[0]){
		case SSMMAP_PFXLST_NAME:
			{
				(*_map)[getAttributeStr(attr[0])] = getpfxlst_name();
			}
			break;
		case SSMMAP_SRC_ADDRESS:
			{
				(*_map)[getAttributeStr(attr[0])] = getsrc_address();
			}
			break;
		case SELF_COMPLETE:
			{
				DCMENUMS _attr;
				_attr = SSMMAP_PFXLST_NAME;	rest_get(&_attr, (void *)_map);
				_attr = SSMMAP_SRC_ADDRESS;	rest_get(&_attr, (void *)_map);
			}
			break;
		default:
			printf("%s(): Unknown Attribute\n", __FUNCTION__);
	}
}


void
SSMMap::load_enums_for_rest(){
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(SSMMAP_PFXLST_NAME)]
		= SSMMAP_PFXLST_NAME;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(SSMMAP_SRC_ADDRESS)]
		= SSMMAP_SRC_ADDRESS;
}


void
SSMMap::dump(){
	printf("  SSMMAP:\n");
	printf("	pfxlst_name = %s\n", getpfxlst_name().c_str());
	printf("	src_address = %s\n", getsrc_address().c_str()); 
}
