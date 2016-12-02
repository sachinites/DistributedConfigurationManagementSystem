#ifndef __ROUTEROSPFCALLPOINTWORKER__
#define __ROUTEROSPFCALLPOINTWORKER__
using namespace std;
#include "string"
#include "DCMEnums.h"
class RouterOspf;
class RouterOspfCallpointWorker{
	private:
		RouterOspfCallpointWorker();
	public:
		static RouterOspf* cmdRouterOspf(string vrf_name);
		static void noRouterOspf(string vrf_name);
		/* Pim attributes set/unset commands*/
		static void RouterOspfCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REQ_TYPE, void  *ret_out);
};
#endif 
