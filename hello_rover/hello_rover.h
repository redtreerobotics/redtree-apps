#ifndef HELLO_ROVER_H
#define HELLO_ROVER_H

/*
 * Basic code that makes a driveable rover with
 * a controller
 * 
 * Jason Ernst, 2015
 * Redtree Robotics
 */

#include <rtr.h>
#include <rt_input_user.h>

void configure(void) {}
void initialize(void) {}
void setup(void) {}
void start(void) {}

class redtree_rover : public m_device
{
	public:
		using m_device::m_device;
		
		XBOX_Joystick Joystick{"Joystick"};
		m_worker<void, void> Control_Routine{this, "Control_Routine", std::bind(&redtree_rover::control, this)};
		
		void configure(void);
		void start(void);
		void control(void);
};

#endif