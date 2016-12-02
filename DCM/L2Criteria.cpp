#include "L2Criteria.h"
#include "AbstractInterface.h"

L2Criteria::L2Criteria(){

}

L2Criteria::~L2Criteria(){
	
}

bool L2Criteria::HasL2Config(AbstractInterface *intf){
	if(intf->m_l2configs.size() == 0)
		return false;
	return true;
}
