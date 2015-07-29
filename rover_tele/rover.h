#ifndef ROVER_H
#define ROVER_H

/*
 * Basic code that makes a driveable rover with
 * a controller
 * 
 * Jason Ernst, 2015
 * Redtree Robotics
 */

#include <rtr.h>
#include <rt_input_user.h>
#include <rt_ddb_user.h>
#include <vector>
#include <iostream>

void configure(void) {}
void initialize(void) {}
void setup(void) {}
void start(void) {}

class virtual_joystick : public m_device
{
	public:
		using m_device::m_device;
		
		m_num<int> Poll_Period{this, "Poll_Period"};
		m_num<float> Left_Joystick_X{this, "Left_Joystick_X"};
		m_num<int> Left_Joystick_Y{this, "Left_Joystick_Y"};
		m_num<float> Right_Joystick_X{this, "Right_Joystick_X"};
		m_num<int> Right_Joystick_Y{this, "Right_Joystick_Y"};
		m_num<float> Right_Trigger{this, "Right_Trigger"};
		m_num<float> Left_Trigger{this, "Left_Trigger"};
		
		m_worker<void, void> JoyStickPoll{this, "JoyStickPoll", std::bind(&virtual_joystick::poll, this)};

		void configure(void);
		void start(void) { Started = true; };
		void poll(void);
	protected:
	private:
		int timeout_sec;
		int timeout_usec;
};

class redtree_rover : public m_device
{
	public:
		using m_device::m_device;
			
		m_worker<void, void> Control_Routine{this, "Control_Routine", std::bind(&redtree_rover::control, this)};
		
		void configure(void);
		void start(void);
		void control(void);
};

#endif
