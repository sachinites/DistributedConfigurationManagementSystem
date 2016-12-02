#include "PIMConfigCallpointWorker.h"
#include "DCM.h"
#include <stdio.h>
#include "DCMEnums.h"
#include "PIMConfigEnums.h"
#include "AbstractInterface.h"
#include "PIMConfig.h"

void
PIMConfigCallpointWorker::PIMConfigCallpoint(string if_name, DCMENUMS *attr, void *new_val){
        AbstractInterface *interface = DCM::getIF(if_name);
	if(!interface){
		printf("%s() Error : interface %s do not exist\n", __FUNCTION__, if_name.c_str());
		return;
	}
	PIMConfig *pimc = static_cast<PIMConfig *>(interface->getl3configbyClassName("PIMConfig.class"));
	if(!pimc){
		pimc = PIMConfig::instantiatePIMConfig(interface);
	}
	if(attr[0] == DUMP){
		pimc->dump();
		return;
	}
	pimc->update(attr, new_val);
}
