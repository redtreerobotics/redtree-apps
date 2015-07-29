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
#include <rt_types.h>
#include <rt_ddb_user.h>
#include <iostream>

using namespace std;

class data_sink : public m_device
{
	public:
		using m_device::m_device;
		void configure(void){}
		void initialize(void);
		void setup(void){}
		void start(void){Started = true;};
	private:
		void main();
		m_worker<void, void> data_sink_main{this, "data_sink_main", std::bind(&data_sink::main, this)};
};

void data_sink::main()
{
	unsigned int i;
	vector<m_tag *> tags = get_tag_broadcast("generator.SomeNumber", 1, 500000);
	
	for(i = 0; i < tags.size(); i++)
	{
		m_tag * t = tags.at(i);
		m_num<int> *nt = dynamic_cast<m_num<int>*>(t);
		if(nt != NULL)
		{
			int val = *nt;
			cout << nt->name << ":" << val << endl;
		}
	}
}

void data_sink::initialize()
{
	data_sink_main.run_when(Started);
}

data_sink receiver{"receiver"};

void configure(void){};
void initialize(void){};
void setup(void){};
void start(void){};