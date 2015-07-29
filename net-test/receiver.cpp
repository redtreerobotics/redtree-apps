#include <rtr.h>
#include <rt_ddb_user.h>
#include <string.h>				// memset()
#include <iostream>				// cout, endl
#include <sstream>				// stringstream
#include <sys/socket.h>			// socket
#include <sys/ioctl.h>			// SIOCGIFCONF, ioctl()
#include <net/if.h>				// AF_INET, SOCK_DGRAM, struct ifconf
#include <netinet/in.h>			// sockaddr_in
#include <arpa/inet.h>			// inet_ntop()
#include <unistd.h>				// close()

using namespace std;

void configure(void) {}
void initialize(void) {}
void setup(void) {}
void start(void) {}


class receiver : public m_module
{
	public:
		using m_module::m_module;
		
		void start(void);
		
	private:
		m_job<void, void> receiver{this, "receiver", std::bind(&receiver::receive, this)};
		void receive(void);
};

receiver r{"r"};

void receiver::start(void)
{
	Started = true;
	receiver();
}

void receiver::receive()
{
	int parentfd;
	int on = 1;
	struct sockaddr_in server_socket;
		
	if((parentfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cerr << "Error creating a socket for the DDB daemon to listen on" << endl;
		return;
	}
		
	memset(&server_socket, 0, sizeof(struct sockaddr_in));
	server_socket.sin_family = AF_INET;
	server_socket.sin_port = htons(10101);
	server_socket.sin_addr.s_addr = INADDR_ANY;
		
	if(bind(parentfd, (struct sockaddr *)&server_socket, sizeof(server_socket)) < 0)
	{
		cerr << "Error binding the DDB daemon to the port: " << 10101 << endl;
		return;
	}
	
	if(setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		cerr << "Error making the socket re-usable for the DDB daemon" << endl;
		return; 
	}
	
	while(1)
	{
		char buffer[1024] = {0};		
		struct sockaddr_in connect_socket; socklen_t len;
			
		//receive the request
		len = sizeof(struct sockaddr_in);
		recv_buffer(parentfd, buffer, 1024, 0, (struct sockaddr *)&connect_socket, &len);
		
		cout << "RECV: " << buffer << endl;
	}
}