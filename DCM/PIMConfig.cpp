#include "PIMConfig.h"
#include <stdio.h>
#include "VRF.h"
#include "VEInterface.h"
#include "PIMConfigEnums.h"
#include "L2Criteria.h"

void PIMConfig::setpim_sparse(bool pim_sparse){
	m_pim_sparse = pim_sparse;
}

bool PIMConfig::getpim_sparse(){
	return m_pim_sparse;
}

void PIMConfig::setdr_priority(unsigned int dr_priority){
	m_dr_priority = dr_priority;
}

unsigned int PIMConfig::getdr_priority(){
	return m_dr_priority;
}

void PIMConfig::setttl_threshold(unsigned int ttl_threshold){
	m_ttl_threshold = ttl_threshold;
}

unsigned int PIMConfig::getttl_threshold(){
	return m_ttl_threshold;
}

string PIMConfig::getclass_name(){
	return "PIMConfig.class";
}

PIMConfig::PIMConfig(){
	setpim_sparse(true);
	setdr_priority(1);
	setttl_threshold(1);
}

PIMConfig::~PIMConfig(){
	printf("%s L3 config object deleted\n", getclass_name().c_str());	
}

PIMConfig* PIMConfig::instantiatePIMConfig(AbstractInterface *interface){
	if(!interface) return NULL;
	
	if(L2Criteria::HasL2Config(interface) == true){
		printf("Error: Interface has L2 config, remove L2 config first\n");
		return NULL;
	}

	VRF *vrf = NULL;
	vrf = interface->getVRF();

	// should be handle by create rule
	if(!vrf->isRoutingModulePresentinVRF("RouterPim.class")){
		printf("Error : Router pim is not enabled on VRF %s", vrf->getvrf_name().c_str());
		return NULL;
	}

	PIMConfig* conf = new PIMConfig();
	if(interface->addl3config(conf) == 0)
		return conf;
	delete conf;
	return NULL;
}

int PIMConfig::validation(DCMENUMS *attr, void *new_value){
	return 0;
}

int PIMConfig::update(DCMENUMS *attr, void *value){

	 if(validation(attr, value)){
                //printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
                return -1;
        }

	switch(attr[0]){
		case PIMCONFIG_PIM_SPARSE:
			setpim_sparse(*(bool *)value);
			break;
		case PIMCONFIG_DR_PRIORITY:
			setdr_priority(*(unsigned int *)value);
			break;
		case PIMCONFIG_TTL_THRESHOLD:
			setttl_threshold(*(unsigned int *)value);
			break;
		default:
			this->AbstractL3Config::update(attr, value);
	}
	return 0;
}

string PIMConfig::getAttributeStr(int attr){
	switch(attr){
		case PIMCONFIG_PIM_SPARSE:
			return "PIMCONFIG_PIM_SPARSE";
		case PIMCONFIG_DR_PRIORITY:
			return "PIMCONFIG_DR_PRIORITY";
		case PIMCONFIG_TTL_THRESHOLD:
			return "PIMCONFIG_TTL_THRESHOLD";
		default:
			return "UNKNOWN";
	}
}

void PIMConfig::dump(){
	this->AbstractL3Config::dump();
	printf("	pim sparse	= %s\n", getpim_sparse() ? "Enable" : "Disable");
	printf("	dr_priority     = %u\n", getdr_priority());
	printf("	ttl_threshold   = %u\n", getttl_threshold());
	printf("	class name      = %s\n", getclass_name().c_str());
}
