#ifndef __VRFCALLPOINTWORKER__
#define __VRFCALLPOINTWORKER__
#include "string"
using namespace std;
#include "DCMEnums.h"

class VRF;

class VRFCallpointWorker{
	private:
		VRFCallpointWorker();
	public:
		/* VRF create/delete commands*/
		static VRF* cmdVRF(string vrf_name);
		static void cmdnoVRF(string vrf_name);
		
		/* VRF attributes set/unset commands*/
		static void VRFCallpoint(string vrf_name, DCMENUMS* attr, void *new_val, int REQ_TYPE, void *rest_out);
};
#endif 
