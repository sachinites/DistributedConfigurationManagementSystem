#ifndef __ABSTRACTINTERFACE__
#define __ABSTRACTINTERFACE__

using namespace std;
#include "IfUtils.h"
#include <string>
#include <vector>
#include "DCMEnums.h"

class VRF;
class AbstractL3Config;

class AbstractInterface{
	private:
		static unsigned int ifindex_counter;
		string m_interface_name;;
		interface_type_t m_if_type;
		unsigned int m_ifindex;
		bool m_isup;
		VRF *m_vrf;
		int validation(DCMENUMS* attr, void *new_value);
	public:
		static void load_enums_for_rest();
		vector <AbstractL3Config *>m_l3configs;		
		vector <AbstractL3Config *>m_l2configs;		
		AbstractInterface();
		virtual ~AbstractInterface();
		void setisup(bool isup);
		bool getisup();
		void setVRF(VRF *vrf);
		VRF* getVRF();
		void setinterface_name(string ifname);
		virtual string getinterface_name();
		void setif_type(interface_type_t if_type);
		interface_type_t getif_type();
		void setifindex();
		unsigned int getifindex();
		virtual void dump();
		static string getclass_name();
		char addl3config(AbstractL3Config *l3config);
		char dell3config(AbstractL3Config *l3config);
		char dell3configbyClassName(string class_name);
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
		AbstractL3Config* getl3configbyClassName(string class_name);
		virtual int update(DCMENUMS* attr, void *new_value);
		static string getAttributeStr(int attr);
};

#endif /*__ABSTRACTINTERFACE__*/
