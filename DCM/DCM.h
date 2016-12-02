#ifndef __DCM__
#define __DCM__

#include <map>
#define MAX_VRF 256
#include <string>
using namespace std;

class VRF;
class AbstractInterface;
class DCM{
	private:
		static map<string, VRF*> VRFDB;
		static map<string, AbstractInterface*> IFDB;
		/* Make constructor private to make the class non instantiable*/
		DCM();
	public:
		static char saveVRF(VRF *vrf);
		static VRF* getVRF(string vrf_name);
		static bool isVRFPresent(string vrf_name);
		static void removeVRF(string vrf_name);

		static char saveIF(AbstractInterface *intf);
		static AbstractInterface* getIF(string if_name);
		static bool isIFPresent(string if_name);
		static void removeIF(string if_name);
};

#endif
