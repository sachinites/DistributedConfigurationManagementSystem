#include "RESTServer.h"
#include "RESTServerInitParams.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <memory.h>
#include <signal.h>
#include "Utils.h"

pthread_t* RESTServer::thread = (pthread_t*)calloc(1, sizeof(pthread_t));
int RESTServer::sockfd = 0;
map<string, DCMENUMS> RESTServer::DCM_ENUM_MAPPING;
map<string, callPointWorker> RESTServer::CALL_POINT_MAPPING;

void
RESTServer::create_html_response(int sockfd, void *rest_out){
	map<string, string> *_map = static_cast<map<string, string> *>(rest_out);
	int content_len = 0;
	string identifier, value;
	char buff[32];

	if(_map->size() == 0){
		identifier = "Resource not found";
		value = "Nil";
	}

	for (map<string,string>::iterator it = _map->begin(); it != _map->end(); it++){
		printf("%s:%s\n", (it->first).c_str(), (it->second).c_str());
	}

	string body = 
		"<html>"
		"<head>"
			"<title>REST Response</title>"
			"<style>"
				"table, th, td {"
					"border: 1px solid black;}"
			"</style>"
		"</head>"
		"<body>"
		"<table>"
		"<tr>"
			"<th> Attribute </th>"
			"<th> Value </th>"
		"</tr>";

	for(map<string,string>::iterator it = _map->begin(); it != _map->end(); it++){
	    identifier = it->first;
	    value      = it->second;
	    body.append("<tr><td>");
				body.append(identifier);body.append(
			"</td>"
			"<td>");
				body.append(value);body.append(
			"</td></tr>");
	}

   body.append( "</table>"
		"</body>"
	        "</html>");

	content_len = body.length();
	string content_len_str = string(itoa(content_len, buff, 10));

	string header = 
	"HTTP/1.1 200 OK\n";	  header.append(
	"Server: REST\n"	);header.append(
	"Content-Length: "	);header.append(content_len_str);header.append("\n");header.append(
	"Connection: close\n"	);header.append(
	"Content-Type: text/html; charset=UTF-8\n");header.append(
	"\n");

	string result = header + body ;
	send(sockfd, result.c_str(), result.length(), 0);
	close(sockfd);
}


static void
process_rest_GET_VRF_request(int sockfd, string *token_array, int size){
	printf("%s called, size = %d\n", __FUNCTION__, size);
	string vrf_name = token_array[2];
	map<string, string> rest_out;
	DCMENUMS enum_array[MAX_URL_SIZE -2];
	callPointWorker callback = NULL;
	int i = 0, j = 0;
	for( i = 3; i <= size; i++){
		enum_array[j++] = RESTServer::DCM_ENUM_MAPPING[token_array[i]];
	}
	callback = RESTServer::CALL_POINT_MAPPING["VRF.class"];
	if(!callback){
		printf("CallPoint not Registered with Rest\n");
		goto incomplete_url_error;
	}

	callback(vrf_name, enum_array, NULL, REST_GET_REQ, (void *)&rest_out);
	RESTServer::create_html_response(sockfd, (void *)&rest_out);

	return;
	incomplete_url_error:
		printf("Error : Incomplete URL\n");
		close(sockfd);
		return;
	
}

static void
process_rest_GET_global_plugin_request(int sockfd, string *token_array, int size){
	// note : token[0] is empty
	// token[1] = "vrf";
	map<string, string> rest_out;
	string vrf_name, plugin_name;
	int i = 0, j = 0;
	map<string,DCMENUMS>::iterator it;
	DCMENUMS enum_array[MAX_URL_SIZE -2];
	callPointWorker callback = NULL;
	if(size < 3){
		goto incomplete_url_error;
	}
	
	vrf_name = token_array[2];
	plugin_name = token_array[3];

	for( i = 4; i <= size; i++){
		/* Condition check if ENUM exists*/
		 it = RESTServer::DCM_ENUM_MAPPING.find(token_array[i]);
		 if (it == RESTServer::DCM_ENUM_MAPPING.end())
			goto incomplete_url_error;
		enum_array[j++] = RESTServer::DCM_ENUM_MAPPING[token_array[i]];
	}

	callback = RESTServer::CALL_POINT_MAPPING[plugin_name];
	if(!callback){
		printf("CallPoint not Registered with Rest\n");
		goto incomplete_url_error;
	}

	callback(vrf_name, enum_array, NULL, REST_GET_REQ, (void *)&rest_out);

	RESTServer::create_html_response(sockfd, (void *)&rest_out);
	        
	return;
	incomplete_url_error:
		printf("Error : Incomplete URL\n");
		close(sockfd);
		return;
}


static void
process_rest_GET_interface_plugin_request(int sockfd, string *token_array, int size){
	
}

static void
process_GET_request(int sockfd, char *url){
	string token[MAX_URL_SIZE];
	string str_url(url);
	string del = "/";
	int i = 0, j = 0;
	map<string,DCMENUMS>::iterator it;

	size_t pos = 0;
	while ((pos = str_url.find(del)) != string::npos) {
		if(i == MAX_URL_SIZE){
			printf("URL too large\n");
			close(sockfd);
			return;
		}
		token[i++] = str_url.substr(0, pos);
		str_url.erase(0, pos + del.length());
	}

	token[i] = str_url.substr(0, pos);
	str_url.erase(0, pos + del.length());

	for(j = 0; j <= i ; j++){
		printf("token[%d] = %s\n", j, token[j].c_str());
	}

	if(token[1] == "vrf"){
		 if(i < 3){
			printf("Incomlete URL, specify the attribute\n");
			close(sockfd);
			return;	
		 }
		 it = RESTServer::DCM_ENUM_MAPPING.find(token[3]);
                 if (it == RESTServer::DCM_ENUM_MAPPING.end())
			process_rest_GET_global_plugin_request(sockfd, token, i);
		else
			process_rest_GET_VRF_request(sockfd, token, i);
	}	
	else if(token[1] == "interface"){
		process_rest_GET_interface_plugin_request(sockfd, token, i);
	}
	else{
		printf("Unknown plugin request\n");
		close(sockfd);
		return;
	}
}

static void
process_POST_request(int sockfd, char *url){

}


static void
process_recv_msg(int sockfd, char *url){	
	/* Here you will need to understand the HTTP request response message type/format
	A great description is here : http://www2.ic.uff.br/~michael/kr1999/2-application/2_02-http.htm	       */
	
	char del[2] = "\n", *request_line = NULL, 
			    *method = NULL, *URL = NULL;
	if(!url){
		close(sockfd);
		return;
	}

	/* fetching the Request line of HTTP message*/
	request_line = strtok(url, del);
	printf("request_line = %s\n", request_line);
	del[0] = ' ';
	method = strtok(request_line, del);
	URL = strtok(NULL, del);
	printf("Method = %s\n", method);
	printf("URL = %s\n", URL);

	if(strncmp(method, "GET", strlen("GET")) == 0){
		process_GET_request(sockfd, URL);
	}
	else if(strncmp(method, "POST", strlen("POST")) == 0){
		process_POST_request(sockfd, URL);
	}
	else{
		printf("Unsupported URL method request\n");
		close(sockfd);
		return;
	}
}


static void*
REST_server_start(void *arg){
	char buffer[4098];
	printf("REST Server Started\n");
	fd_set readfds;
	struct sockaddr_in client_addr;
	int sockfd = *(int *)arg;
	int new_socket = 0, rc = 0; 
	socklen_t addr_len = sizeof(struct sockaddr_in);
	while(1){
		FD_ZERO(&readfds);	
		FD_SET(sockfd, &readfds);
		printf("waiting on select system call\n");
		select(sockfd+1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(sockfd, &readfds)){
			if ((new_socket = 
				accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0){
				printf("Failed to accept connection\n");
				close(new_socket);
			}	
			printf("Connection accepted\n");		
			memset(buffer, 0 , sizeof(buffer));
			rc = read(new_socket, buffer, sizeof(buffer));
			printf("msg recieved = %s, size = %d bytes\n", buffer, rc);
			process_recv_msg(new_socket, buffer);
		}
	}	
	return NULL;
}

void
ctrlC_signal_handler(int sig){
	printf("ctrl C pressed\n");
	RESTServer::stop_rest_server();
	exit(0);
}


void
RESTServer::stop_rest_server(){
	close(sockfd);
	pthread_cancel(*thread);
	free(thread);
	thread = NULL;
	printf("REST Server is stopped\n");
}


void
RESTServer::start_rest_server(){		
	rest_register_modules();
	int opt = 1, rc = 0;
	struct sockaddr_in server_addr;
	pthread_attr_t attr;

	/* create TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==0){
		printf("TCP socket creation failed\n");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0){
		printf("TCP socket creation failed for multiple connections\n");
                exit(EXIT_FAILURE);
        }

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(LISTENING_PORT);

	if ((rc = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) 
	{
		printf("Bind error, error code  = %d\n", rc);
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 5) < 0)
	{
		printf("listen error\n");
		exit(EXIT_FAILURE);
	}


	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	rc = pthread_create(thread, &attr, REST_server_start, (void *)&sockfd);		
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
	}
	/* regiaster signal handler for ctrl C*/
	signal(SIGINT, ctrlC_signal_handler);
}
