/*
 * Data Source Generator for Sharing a Tag on the Local Swarm Network
 * 
 * Jason Ernst
 * Redtree Robotics, 2015
 * 
 * This illustrates how to randomly change a tag value every x number
 * of seconds and make the tag available for other Redtree Hydra's 
 * in the local swarm network.
 */

#include <rtr.h>
#include <iostream>
using namespace std;

void configure(void) {}
void initialize(void) {}
void setup(void) {}
void start(void) {}

class data_source : public m_device
{
	public:
		using m_device::m_device;	
	
	m_num<int> SomeNumber{this, "SomeNumber"};
	
	//generates a new random tag value every second between 0 and 100
	m_worker<void,void> generator_task{this, "generator_task", [&](){
		cout << "Generating number change: " << SomeNumber() << endl;
		
		//we use the () at the end of the tag to turn the tag into its atomic value, instead of a tag object
		SomeNumber() = drand48()*100; 
	}};
	
	void initialize(void)
	{
		//set the random number generator task to fire every second when
		//the data_source module is Started
		generator_task.run_every_when(1000000, Started);
	}
	
	void start(void)
	{
		//start the module
		Started = true;
	}
	
};

data_source generator{"generator"};