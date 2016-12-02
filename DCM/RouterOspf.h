#ifndef __ROUTEROSPF__
#define __ROUTEROSPF__

#include "AbstractRouterVRF.h"
//#include "VRF.h"
class VRF;

class RouterOspf: public AbstractRouterVRF{
	private:
		unsigned int m_area;
		unsigned int m_distance;
		void load_rules();
	public:
		RouterOspf();
		RouterOspf(VRF *vrf);
		virtual ~RouterOspf(); 
		void setarea(unsigned int area);
		void setdistance(unsigned int distance);
		unsigned int getarea();
		unsigned int getdistance();
		static RouterOspf* instantiateRouterOspf(VRF *vrf);
		virtual string getclass_name();
		virtual void dump();
		virtual int update(DCMENUMS *attr, void *value);
		virtual int validation(DCMENUMS *attr, void *new_value);
		static string getAttributeStr(int attr);
		static void load_enums_for_rest();
		static void load_callpoint_for_rest();
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
};

#endif /* __ROUTEROSPF__ */
