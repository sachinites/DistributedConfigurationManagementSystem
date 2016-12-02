#ifndef __IfUtils__
#define __IfUtils__


#include <string>
using namespace std;

typedef enum{
	ETHERNET =0,
	VE,
	VLAN,
	PO,
	ISL
} interface_type_t;

typedef enum{
	L2_MODE,
	L3_MODE,
	AGGREGATE_MODE,
	TUNNEL_MODE
} if_op_mode_t;

class IfUtils{
	public:
	static string getIfType(interface_type_t type);
	static string getIfOperationMode(if_op_mode_t mode);
};
#endif
