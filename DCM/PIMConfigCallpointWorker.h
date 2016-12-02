#ifndef __PIMCONFIGCALLPOINTWORKER__
#define __PIMCONFIGCALLPOINTWORKER__
#include "string"
using namespace std;
//#include "VRF.h"
//#include "RouterPim.h"
#include "DCMEnums.h"
class PIMConfigCallpointWorker{
	private:
		PIMConfigCallpointWorker();
	public:
		static void PIMConfigCallpoint(string if_name, DCMENUMS *attr, void *new_val);
};
#endif 
