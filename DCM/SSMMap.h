#ifndef __SSMMAP__
#define __SSMMAP__

#include <string>
#include "DCMEnums.h"
using namespace std;

class SSMMap{
	private:
		string m_pfxlst_name;
		string m_src_address;

		static int validation(DCMENUMS *attr, void *new_value);
		static string getAttributeStr(int attr);
	public:
		SSMMap();
		virtual ~SSMMap();
		void setpfxlst_name(string pfxlst_name);
		string getpfxlst_name();
		void setsrc_address(string src_address);
		string getsrc_address();
		virtual int update(DCMENUMS *attr, void *value);
		string getclass_name();
		virtual void dump();
		virtual int rest_get(DCMENUMS *attr, void *rest_out);
		static void load_enums_for_rest();
}; 

#endif /* __SSMMAP__ */
