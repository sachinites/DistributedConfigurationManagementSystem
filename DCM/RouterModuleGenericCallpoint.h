#ifndef __ROUTERMODULEGENERICCALLPOINT__
#define __ROUTERMODULEGENERICCALLPOINT__

#include "DCMEnums.h"
#include <string>
using namespace std;

class RouterModuleGenericCallpoint{
	private:
		RouterModuleGenericCallpoint(){}
		~RouterModuleGenericCallpoint(){}
	public:
		static void RouterModuleCallpoint(string vrf_name, 
							 DCMENUMS *attr, 
							 void *new_val,
							 int REST_REQ_TYPE,
							 void *rest_out,
							 string moduleclassname );



}; 

#endif
