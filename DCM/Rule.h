#ifndef __RULES__
#define __RULES__

#include <string>
using namespace std;

typedef enum{
	DELETE,
	CREATE
} RULE_TYPE;

typedef enum{
	ONE_ONE,   // Action on one class object affect to only one another class object
	ONE_MANY,  // Action on one class object affect to many objects of other class of same type, eg :  Disable Router pim under VRF, should disable all PIMconfig from all interface under matching VRF
	MANY_MANY, // Action on many class objects affect to many objects other classes of same type
	MANY_ONE   // Action on many class objects affect to only one class object	
} CARDINALITY;

typedef enum{
	GtoL3,
	L3toL3
} RELATION;

class Rule{
	private:
	public:
		RULE_TYPE rtype;
		string independantclassname;
		string dependantclassname;
		CARDINALITY cardinality;
		RELATION rel;
		Rule(RULE_TYPE rtype, string independantclassname, string dependantclassname, CARDINALITY cardinality, RELATION rel);
		virtual ~Rule();
		void execute_rule(void *param);
		
		
}; 

#endif /*__RULES__*/
