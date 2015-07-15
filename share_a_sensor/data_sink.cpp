/*
 * Data Sink Receiver for receiving a Tag on the local swarm network
 * 
 * Jason Ernst
 * Redtree Robotics, 2015
 * 
 * This illustrates how to receive a swarm tag from other Redtree Hydras
 * in the local swarm network.
 */

#include <rtr.h>
#include <rt_ddb_user.h>
#include <iostream>

using namespace std;

/*
 * Outputs a tag
 */
void print_tag(m_tag * tag)
{
	m_numeric * nt = dynamic_cast<m_numeric*>(tag);
	if(nt)
	{
		cnumber val = nt->get(0,4);
		if(real(val) != 0)
		{
			Robot_Servos::motor1_power(0);
			Robot_Servos::motor2_power(0);
		}
		else
		{
			cnumber val1 = nt->get(0,1);
			cnumber val2 = nt->get(0,3);
		}
	}
}

void configure(void) {}
void initialize(void) {}
void setup(void)
{	
	vector<remote_subscription *> s = subscribe_broadcast("controller", 1);
	//setup subscription for all of the tags we get back
	for(i = 0; i < (int)s.size(); i++)
	{
		m_tag * tag = s.at(i)->get_tag();
		m_value_simple_subscription sub(&print_tag);
		tag->subscribe(sub);
	}	
}

void start(void)
{
	Started = true;
}
