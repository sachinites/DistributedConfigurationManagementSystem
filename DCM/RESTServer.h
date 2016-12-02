#ifndef __RESTSERVER__
#define __RESTSERVER__

#include <string>
#include <pthread.h>
#include "DCMEnums.h"
#include <map>

#define MAX_URL_SIZE 32
using namespace std;

typedef void (*callPointWorker) (string, DCMENUMS* , void*, int, void *);

class RESTServer{
	private:
		RESTServer();
		~RESTServer();
	public:
		static map<string, DCMENUMS> DCM_ENUM_MAPPING; 
		static map<string, callPointWorker> CALL_POINT_MAPPING;
		static pthread_t *thread;
		static int sockfd;
		static void start_rest_server();
		static void stop_rest_server();
		static void create_html_response(int sockfd, void *);
		static void rest_register_modules();
};


#endif

