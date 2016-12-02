#ifndef __ROUTERBGPCALLPOINTWORKER__
#define __ROUTERBGPCALLPOINTWORKER__
using namespace std;

#include <string>
#include "DCMEnums.h"
class RouterBgp;

class RouterBgpCallpointWorker{
	private:
		RouterBgpCallpointWorker();
	public:
		static RouterBgp* cmdRouterBgp(string vrf_name);
		static void noRouterBgp(string vrf_name);
		/* Pim attributes set/unset commands*/
		static void RouterBgpCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REQ_TYPE, void *rest_out);
};
#endif 
