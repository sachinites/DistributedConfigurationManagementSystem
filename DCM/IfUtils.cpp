#include "IfUtils.h"
using namespace std;
string IfUtils::getIfType(interface_type_t type){
	switch(type){
		case ETHERNET:
			return "ETHERNET";
		case VE:
			return "VE";
		case VLAN:
			return "VLAN";
		case PO:
			return "PO";
		case ISL:
			return "ISL";
		return "UNKNOWN";
	}
}


string IfUtils::getIfOperationMode(if_op_mode_t mode){
	switch(mode){
		case L2_MODE:
			return "L2_MODE";
		case L3_MODE:
			return "L3_MODE";
		case AGGREGATE_MODE:
			return "AGGREGATE_MODE";
		case TUNNEL_MODE:
			return "TUNNEL_MODE";
		default:
			return "";
	}
}
