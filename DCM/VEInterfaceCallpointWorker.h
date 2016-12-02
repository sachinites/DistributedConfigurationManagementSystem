#ifndef __VEInterfaceCallpointWorker__
#define __VEInterfaceCallpointWorker__
#include "DCMEnums.h"
#include <string>
using namespace std;
class VEInterface;

class VEInterfaceCallpointWorker{
	private:
		VEInterfaceCallpointWorker();
	public:
		static void createVe(string vrf_name, string ifname, unsigned int vlanid);
		static void delVe(string ifname);
		static void VEInterfaceCallpoint(string if_name, DCMENUMS *attr, void *new_val);

};
#endif
