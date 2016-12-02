#ifndef __ROUTERBGP__
#define __ROUTEROBGP__

#include "AbstractRouterVRF.h"

class VRF;

class RouterBgp: public AbstractRouterVRF{
	private:
		unsigned int m_bgparea;
		unsigned int m_bgpdistance;
		void load_rules();
	public:
		RouterBgp(VRF *vrf);
		virtual ~RouterBgp(); 
		void setbgparea(unsigned int area);
		void setbgpdistance(unsigned int distance);
		unsigned int getbgparea();
		unsigned int getbgpdistance();
		static RouterBgp* instantiateRouterBgp(VRF *vrf);
		virtual string getclass_name();
		virtual void dump();
		virtual int update(DCMENUMS *attr, void *value);
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
		virtual int validation(DCMENUMS *attr, void *new_value);
		static void load_enums_for_rest();
		static void load_callpoint_for_rest();
		static string getAttributeStr(int attr);
};

#endif /* __ROUTERBGP__ */
