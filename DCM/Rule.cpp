#include "Rule.h"
#include "stdio.h"
#include "VRF.h"
#include "AbstractInterface.h"
#include "AbstractL3Config.h"

Rule::Rule(RULE_TYPE rtype, string independantclassname, string dependantclassname, CARDINALITY cardinality, RELATION rel){
	this->rtype = rtype;
	this->independantclassname = independantclassname;
	this->dependantclassname = dependantclassname;
	this->cardinality = cardinality;
	this->rel = rel;
}

Rule::~Rule(){
	printf("Rule :: %d, %s, %s, %d, %d is deleted\n", rtype, independantclassname.c_str(),
			dependantclassname.c_str(), cardinality, rel);
}

void
Rule::execute_rule(void *param){
	switch(rtype){
		case DELETE:
		{
			switch(rel){
				case GtoL3:
				{
					VRF *vrf = (VRF *)param;
					for(int i = 0; i < vrf->m_interfaces.size(); i++){
						AbstractInterface *interface = vrf->m_interfaces[i];
						for(int j =0; j < interface->m_l3configs.size(); i++){
							AbstractL3Config *l3config = interface->m_l3configs[j];
							if(l3config->getclass_name() != dependantclassname)
								continue;
							interface->dell3config(l3config);
						}
					}
				}
				break;
			}
		}
		break;
	}	
}
