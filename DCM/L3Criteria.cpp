#include "L3Criteria.h"
#include "AbstractInterface.h"

L3Criteria::L3Criteria(){

}

L3Criteria::~L3Criteria(){
	
}

bool L3Criteria::HasL3Config(AbstractInterface *intf){
	if(intf->m_l3configs.size() == 0)
		return false;
	return true;
}
