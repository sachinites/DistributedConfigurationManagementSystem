#include <stdio.h>
#include <stdlib.h>
/* CallpointWorkers*/
#include "VRFCallpointWorker.h"
#include "RouterPimCallpointWorker.h"
#include "RouterOspfCallpointWorker.h"
#include "RouterBgpCallpointWorker.h"
#include "VEInterfaceCallpointWorker.h"
#include "PIMConfigCallpointWorker.h"
/*Enums*/
#include "DCMEnums.h"
#include "RouterPimEnums.h"
#include "RouterOspfEnums.h"
#include "RouterBgpEnums.h"
#include "VEInterfaceEnums.h"
#include "SSMMapEnums.h"
#include "PIMConfigEnums.h"
/* UI */
#include "userInterface.h"
/* REST Support*/
#include "RESTServer.h"


int
main(int argc, char **argv){
	RESTServer::start_rest_server();
	// vrf green
	vrf("green");
	vrf("red");
	//router pim vrf green
	router_pim("green");
	router_pim("red");
	router_ospf("green");	
	router_ospf("red");	
	router_bgp("green");	
	router_bgp("red");	
	rp_address("green", "122.1.1.1");
	rp_address("red", "122.122.1.1");
	ospfar("green", 20);
	ospfdis("green", 100);	
	ospfar("red", 200);
	ospfdis("red", 150);
	bgpar("green", 120);
	bgpdis("green", 130);	
	bgpar("red", 210);
	bgpdis("red", 170);	

	// hello-timer 123	
	pim_hello_timer("green", 123);
	pim_hello_timer("red", 332);
	pim_max_cache("green", 2024);
	pim_max_cache("red", 4048);


	pim_nbr_to("green" , 1000);
	pim_jp_int("green" , 2000);
	pim_inact("green" , 1200);
	pim_prw_int("green" , 25);
	pim_spt_th("green" , 60);

	ssmmap("green", "myprefix", "10.10.10.10");
	ssmmap("red", "myprefix2", "11.10.10.10");
	//RouterPimCallpointWorker::RouterPimCallpoint("red", arr1, &src_addr);

	ve("green", 9, 9);
	ve("green", 10, 20);
	ve("red", 100, 200);
	
	// no int ve 11
	//VEInterfaceCallpointWorker::delVe("ve11");
	// show running-config router pim vf green
	pimsp("ve10");
	pimdrp("ve10", 10);
	pimttl("ve10", 22);
	venosh("ve10");
	ipaddr("ve10", "122.10.1.2");	
	ipaddr("ve9", "123.10.1.2");	
	pimsp("ve100");
	pimdrp("ve100", 100);
	pimttl("ve100", 220);
	nove("ve100");
	venosh("ve10");	
	//pvrf("green");
	//pvrf("red");
	//novrf("green");	
	//novrf("red");
	scanf("\n");
	//pthread_join(*RESTServer::thread, NULL);
	RESTServer::stop_rest_server();
	return 0;
}

