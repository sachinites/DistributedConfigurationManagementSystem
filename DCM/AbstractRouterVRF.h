
#ifndef __ABSTRACTROUTERVRF__
#define __ABSTRACTROUTERVRF__

#include <map>
#include <string>
#include "DCMEnums.h"

using namespace std;
class VRF;
class Rule;

class AbstractRouterVRF{
	private:
		VRF *m_vrf;
		int validation(int *attr, void *new_value);
	public:
	static void load_enums_for_rest();
	map<unsigned int, Rule*> m_rules;
	AbstractRouterVRF();
	virtual ~AbstractRouterVRF();
	VRF* getVRF();
	void setVRF(VRF *vrf);
	virtual string getclass_name();
	virtual void dump();
	virtual int update(DCMENUMS *attr, void *new_value);
	virtual int rest_get(DCMENUMS *attr, void *rest_out);
	void add_rule(unsigned int index, Rule *rule);
	static string getAttributeStr(int attr);
	virtual void load_rules() = 0;
	virtual void execute_delete_rules();
	virtual void execute_create_rules();
	 
};

#endif /*__ABSTRACTROUTERVRF__*/
