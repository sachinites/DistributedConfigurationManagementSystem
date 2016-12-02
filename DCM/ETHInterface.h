#ifndef __ETHINTERFACE__
#define __ETHINTERFACE__


#include "AbstractInterface.h"
#include "DCMEnums.h"

class VRF;
class ETHInterface: public AbstractInterface {
	private:
		unsigned int m_vlanid;
		if_op_mode_t m_oper_mode;
		
	public:
		ETHInterface(VRF *vrf, string ifname, unsigned int vlanid, if_op_mode_t mode);
		virtual ~ETHInterface();
		void setvlanid(unsigned int vlanid);
		unsigned int getvlanid();
		void setOperatingMode(if_op_mode_t oper_mode);
		if_op_mode_t getOperatingMode();
		static string getclass_name();
		virtual void dump();
		static ETHInterface* instantiateETHInterface(VRF *vrf, string ifname, unsigned int vlanid, if_op_mode_t mode);
		virtual int update(DCMENUMS *attr, void *new_value);
		static string getAttributeStr(int attr);
};

#endif

