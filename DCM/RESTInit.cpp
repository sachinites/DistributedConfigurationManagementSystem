#include "RESTServer.h"

/* Global Modules*/
#include "RouterPim.h"
#include "SSMMap.h"

#include "RouterOspf.h"
#include "RouterBgp.h"

#include "VRF.h"

#include "AbstractInterface.h"

void
RESTServer::rest_register_modules(){
	DCM_ENUM_MAPPING[""] = SELF_COMPLETE;

	VRF::load_enums_for_rest();
	VRF::load_callpoint_for_rest();

	AbstractRouterVRF::load_enums_for_rest();

	RouterPim::load_enums_for_rest();
		SSMMap::load_enums_for_rest();
	RouterPim::load_callpoint_for_rest();


	RouterOspf::load_enums_for_rest();
	RouterOspf::load_callpoint_for_rest();

	RouterBgp::load_enums_for_rest();
	RouterBgp::load_callpoint_for_rest();

	AbstractInterface::load_enums_for_rest();
}
