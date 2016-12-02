
#ifndef __VRF__
#define __VRF__


#include <string>
#include <vector>
#include "DCMEnums.h"

using namespace std;

class AbstractRouterVRF;
class AbstractInterface;

class VRF{
	private:
		string m_vrf_name; 
	public:
		/* Aggregation relation ship*/
		vector<AbstractRouterVRF *> m_modules;
		vector<AbstractInterface *> m_interfaces;
		VRF();
		VRF(string vrf_name);
		virtual ~VRF();
		void setvrf_name(string vrf_name);
		string getvrf_name();
		static string getclass_name();
		int add_routingModule(AbstractRouterVRF *module);
		AbstractRouterVRF* get_routingModule(string class_name);
		int delete_routingModule(AbstractRouterVRF *module);
		int delete_routingModulebyClassName(string module_name);
		int remove_routingModule(AbstractRouterVRF *module);
		int remove_routingModulebyClassName(string module_name);
		int add_interface(AbstractInterface *interface);
		//AbstractInterface *get_interfacebyClassName(string if_class_name);
		int delete_interface(AbstractInterface *interface);
		int delete_interfacebyClassName(string if_class_name);
		int delete_interfacebyIfndex(unsigned int ifindex);
		int remove_interface(AbstractInterface *interface);
		int remove_interfacebyClassName(string if_class_name);
		char isinterfacePresentinVRF(unsigned int ifindex);
		char isRoutingModulePresentinVRF(string module_class_name);
		static VRF* instantiateVRF(string vrf_name);
		static void load_enums_for_rest();
		static void load_callpoint_for_rest();
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
		static string getAttributeStr(int attr);
		void dump();
};

#endif /* __VRF__*/
