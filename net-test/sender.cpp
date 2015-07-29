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


class sender : public m_module
{
	public:
		using m_module::m_module;
		
		void start(void);
		
	private:
		m_job<void, void> sender{this, "sender", std::bind(&sender::send, this)};
		void send(void);
};

sender s{"s"};

void sender::start(void)
{
	Started = true;
	sender();
}

void sender::send()
{
	struct sockaddr_in servaddr;
	int sockfd = 0;
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cerr << "  Error, could not create a socket during the api_broadcast_msg function" << endl;
		return;
	}
	
	//allow this socket to broadcast
	int broadcastON = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastON, sizeof(broadcastON)) < 0)
	{
		cerr << "  Error, could not broadcast on the socket during the api_broadcast_msg function" << endl;
		return;
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = INADDR_ANY;
	servaddr.sin_addr.s_addr=inet_addr("255.255.255.255");
	servaddr.sin_port=htons(10101);
	
	char buffer[] = "TEST";
	cout << "SENDING: " << endl;
	send_buffer(sockfd, buffer, strlen(buffer), 0, (sockaddr*)&servaddr, sizeof(servaddr));
}