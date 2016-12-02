#ifndef __ABSTRACTL3CONFIG__
#define __ABSTRACTL3CONFIG__

using namespace std;
#include <string>
#include "DCMEnums.h"

class AbstractL3Config{
	private:
	string m_ip_address;
	public:
	AbstractL3Config();
	virtual ~AbstractL3Config();
	void setip_address(string ip_address);
	string getip_address();
	virtual void dump();
	virtual string getclass_name();
	virtual int update(DCMENUMS *attr, void *new_value);
	int validation(int *attr, void *new_value);
}; 
#endif
