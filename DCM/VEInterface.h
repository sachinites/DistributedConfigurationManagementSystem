#ifndef __VEINTERFACE__
#define __VEINTERFACE__


#include "AbstractInterface.h"
#include "DCMEnums.h"

class VRF;

class VEInterface: public AbstractInterface {
	private:
		unsigned int m_vlanid;
		string m_ipaddress;
	public:
		VEInterface(string vrf_name, string ifname, unsigned int vlanid);
		virtual ~VEInterface();
		void setvlanid(unsigned int vlanid);
		unsigned int getvlanid();
		void setipaddress(string ip);
		string getipaddress();
		static string getclass_name();
		virtual void dump();
		static VEInterface* instantiateVEInterface(string vrf_name, string ifname, unsigned int vlanid);
		virtual int update(DCMENUMS *attr, void *new_value);
		static string getAttributeStr(int attr);
};

#endif

