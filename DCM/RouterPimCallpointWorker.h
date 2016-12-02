#ifndef __ROUTERPIMCALLPOINTWORKER__
#define __ROUTERPIMCALLPOINTWORKER__
using namespace std;

#include <string>
#include "DCMEnums.h"
class RouterPim;

class RouterPimCallpointWorker{
	private:
		RouterPimCallpointWorker();
	public:
		static RouterPim* cmdRouterPim(string vrf_name);
		static void noRouterPim(string vrf_name);
		/* Pim attributes set/unset commands*/
		static void RouterPimCallpoint(string vrf_name, DCMENUMS *attr, void *new_val, int REQ_TYPE, void *rest_out);
};
#endif 
