#include "RouterPim.h"
#include <stdio.h>
#include "VRF.h"
#include "DCM.h"
#include "RouterPimEnums.h"
#include "SSMMap.h"
#include "Rule.h"
#include "RESTServer.h"
#include "RouterPimCallpointWorker.h"
#include "Utils.h"

RouterPim::RouterPim(VRF *vrf){
	m_ssmmap = new SSMMap();
	setVRF(vrf);
	load_rules();
}

void
RouterPim::load_enums_for_rest(){
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_RP_ADDR)]
		= ROUTERPIM_RP_ADDR;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_HELLO_TIMER)]
		= ROUTERPIM_HELLO_TIMER;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_SSMMAP)]
		=  ROUTERPIM_SSMMAP;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_MAX_CACHE)]
		= ROUTERPIM_MAX_CACHE;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_NBR_TIMEOUT)]
		= ROUTERPIM_NBR_TIMEOUT;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_JOIN_PRUNE_INTERVAL)]
		= ROUTERPIM_JOIN_PRUNE_INTERVAL;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_INACTIVITY_INTERVAL)]
		= ROUTERPIM_INACTIVITY_INTERVAL;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_PRUNE_WAIT_INTERVAL)]
		= ROUTERPIM_PRUNE_WAIT_INTERVAL;
	RESTServer::DCM_ENUM_MAPPING[getAttributeStr(ROUTERPIM_SPT_THRESHOLD)]
		= ROUTERPIM_SPT_THRESHOLD;
}

void
RouterPim::load_callpoint_for_rest(){
	RESTServer::CALL_POINT_MAPPING[string("RouterPim.class")] 
			= RouterPimCallpointWorker::RouterPimCallpoint;
}

RouterPim::~RouterPim(){
	delete m_ssmmap;
	execute_delete_rules();
	printf(" %s deleted\n", getclass_name().c_str());
}

void RouterPim::setrp_address(string rp_address){
	m_rp_address = rp_address;
}

void RouterPim::setssmmap(SSMMap* ssmmap){
	m_ssmmap = ssmmap;
}

SSMMap* RouterPim::getssmmap(){
	return m_ssmmap;
}

void RouterPim::sethello_timer(unsigned int hello_timer){
	m_hello_timer = hello_timer;
}

string RouterPim::getrp_address(){
	return m_rp_address;
}

unsigned int RouterPim::gethello_timer(){
	return m_hello_timer;
}

unsigned int RouterPim::getmax_cache(){
	return m_max_cache;
}

void
RouterPim::setmax_cache(unsigned int max_cache){
	m_max_cache = max_cache;
}



unsigned int RouterPim::getnbr_timeout(){
	return m_nbr_timeout;
}

void
RouterPim::setnbr_timeout(unsigned int nbr_timeout){
	m_nbr_timeout = nbr_timeout;
}


unsigned int RouterPim::getjoin_prune_interval(){
	return m_join_prune_interval;
}

void
RouterPim::setjoin_prune_interval(unsigned int join_prune_interval){
	m_join_prune_interval = join_prune_interval;
}


unsigned int RouterPim::getinact_interval(){
	return m_inact_interval;
}

void
RouterPim::setinact_interval(unsigned int inact_interval){
	m_inact_interval = inact_interval;
}

void
RouterPim::setprune_w_interval(unsigned int prune_w_interval){
	m_prune_w_interval = prune_w_interval;
} 

unsigned int RouterPim::getprune_w_interval(){
	return m_prune_w_interval;
}


unsigned int RouterPim::getspt_th(){
	return m_spt_th;
}

void
RouterPim::setspt_th(unsigned int spt_th){
	m_spt_th = spt_th;
}

string RouterPim::getclass_name(){
	return "RouterPim.class";
}

void
RouterPim::load_rules(){
  add_rule(1, new Rule(DELETE, getclass_name(), "PIMConfig.class", ONE_MANY, GtoL3));
}

RouterPim* RouterPim::instantiateRouterPim(VRF *vrf){
	RouterPim *module = new RouterPim(vrf);
	if(vrf->add_routingModule(module) == 0){
		return module;
	}
	delete module;
	return NULL;	
}

int
RouterPim::validation(DCMENUMS *attr, void *new_value){

        return 0; // success
}


int 
RouterPim::update(DCMENUMS *attr, void *new_value){
       if(validation(attr, new_value)){
                //printf("INFO : Validation failed for Attribute %s in %s\n", DCMEnums::getAttributeStr(attr).c_str(), __FUNCTION__);
                return -1;
        }

	switch(attr[0]){
		case ROUTERPIM_RP_ADDR:
			setrp_address(*(string *)new_value);
			break;
		case ROUTERPIM_HELLO_TIMER:
			sethello_timer(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_SSMMAP:
			m_ssmmap->update(attr + 1, new_value);
			break;
		case ROUTERPIM_MAX_CACHE:
			setmax_cache(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_NBR_TIMEOUT:
			setnbr_timeout(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_JOIN_PRUNE_INTERVAL:
			setjoin_prune_interval(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_INACTIVITY_INTERVAL:
			setinact_interval(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_PRUNE_WAIT_INTERVAL:
			setprune_w_interval(*(unsigned int *)new_value);
			break;
		case ROUTERPIM_SPT_THRESHOLD:
			setspt_th(*(unsigned int *)new_value);
			break;
		default:
			/* if no Child class Attribute is to be updated, might be parent class
			attribute needs updattion*/
			this->AbstractRouterVRF::update(attr, new_value);
	}
	return 0;
}

int 
RouterPim::rest_get(DCMENUMS *attr, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	switch(attr[0]){
		case ROUTERPIM_RP_ADDR:
			{
				(*_map)[getAttributeStr(attr[0])] = getrp_address();
			}
			break;
		case ROUTERPIM_HELLO_TIMER:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] = 
						string(itoa(gethello_timer(), buff, 10));
			}
			break;
		case ROUTERPIM_SSMMAP:
			{
				m_ssmmap->rest_get(attr + 1, rest_out);
			}
			break;
		case ROUTERPIM_MAX_CACHE:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
						string(itoa(getmax_cache(), buff, 10));
			}
			break;
		case ROUTERPIM_NBR_TIMEOUT:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
					string(itoa(getnbr_timeout(), buff, 10));
			}
			break;
		case ROUTERPIM_JOIN_PRUNE_INTERVAL:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
					string(itoa(getjoin_prune_interval(), buff, 10));
			}
			break;
		case ROUTERPIM_INACTIVITY_INTERVAL:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
					string(itoa(getinact_interval(), buff, 10));
			}
			break;
		case ROUTERPIM_PRUNE_WAIT_INTERVAL:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
					 string(itoa(getprune_w_interval(), buff, 10));
			}
			break;
		case ROUTERPIM_SPT_THRESHOLD:
			{
				char buff[32];
				(*_map)[getAttributeStr(attr[0])] =
					string(itoa(getspt_th(), buff, 10));
			}
			break;
		case SELF_COMPLETE:
			{
				DCMENUMS _attr;
				_attr = ROUTERPIM_RP_ADDR;     rest_get(&_attr, (void *)_map);	
				_attr = ROUTERPIM_HELLO_TIMER; rest_get(&_attr, (void *)_map);
				/* for compostion attributes*/	
				m_ssmmap->rest_get(attr, (void *)_map);
				_attr = ROUTERPIM_MAX_CACHE;  	  	rest_get(&_attr, (void *)_map);
				_attr = ROUTERPIM_NBR_TIMEOUT;	        rest_get(&_attr, (void *)_map);
				_attr = ROUTERPIM_JOIN_PRUNE_INTERVAL;  rest_get(&_attr, (void *)_map);
				_attr = ROUTERPIM_INACTIVITY_INTERVAL;  rest_get(&_attr, (void *)_map);
				_attr = ROUTERPIM_PRUNE_WAIT_INTERVAL;  rest_get(&_attr, (void *)_map);
				_attr = ROUTERPIM_SPT_THRESHOLD;	rest_get(&_attr, (void *)_map);
				this->AbstractRouterVRF::rest_get(attr, rest_out);
			}
			break;
		default:
			/* if no Child class Attribute is to be updated, might be parent class
			attribute needs updattion*/
			this->AbstractRouterVRF::rest_get(attr, rest_out);
	}
	return 0;
}

string RouterPim::getAttributeStr(int attr){
	switch(attr){
		case ROUTERPIM_RP_ADDR:
			return "ROUTERPIM_RP_ADDR";
		case ROUTERPIM_HELLO_TIMER:
			return "ROUTERPIM_HELLO_TIMER";
		case ROUTERPIM_SSMMAP:
			return "ROUTERPIM_SSMMAP";
		case ROUTERPIM_MAX_CACHE:
			return "ROUTERPIM_MAX_CACHE";
		case ROUTERPIM_NBR_TIMEOUT:
			return "ROUTERPIM_NBR_TIMEOUT";
		case ROUTERPIM_JOIN_PRUNE_INTERVAL:
			return "ROUTERPIM_JOIN_PRUNE_INTERVAL";
		case ROUTERPIM_INACTIVITY_INTERVAL:
			return "ROUTERPIM_INACTIVITY_INTERVAL";
		case ROUTERPIM_PRUNE_WAIT_INTERVAL:
			return "ROUTERPIM_PRUNE_WAIT_INTERVAL";
		case ROUTERPIM_SPT_THRESHOLD:
			return "ROUTERPIM_SPT_THRESHOLD";
		default:
			return "UNKNOWN";
	}
}

void RouterPim::dump(){
	this->AbstractRouterVRF::dump();
	printf("  class Name :  %s\n" , getclass_name().c_str());
	printf("  rp_address :  %s\n",  getrp_address().c_str());
	printf("  hello_timer:  %u\n",  gethello_timer());
	printf("  max_cache  :  %u\n",  getmax_cache());
	printf("  Neighbor Timeout : %u\n",  getnbr_timeout());
	printf("  Join/Prune Interval : %u\n",  getjoin_prune_interval());
	printf("  InActivity Interval : %u\n",  getinact_interval());
	printf("  Prune Wait Interval : %u\n",  getprune_w_interval());
	printf("  SPT Threshold	      : %u\n",  getspt_th());
	m_ssmmap->dump();
	printf(" ----------------------\n");
}
