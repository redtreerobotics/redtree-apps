#include "rover.h"
#include <iostream>

/*
 * Basic code that makes a drivable tele-op rover
 * 
 * Jason Ernst, 2015
 * Redtree Robotics
 */

redtree_rover rover{"Rover"};
virtual_joystick Joystick{"Joystick"};

void redtree_rover::configure(void)
{
	Control_Routine.run_every_when(100000, Joystick.Started);
}

void redtree_rover::start(void)
{
	Started = true;
}

void redtree_rover::control(void)
{
	if(m_fpga::isFound())
	{
		m_fpga::write(0xC00,1500 + (int32_t)scale_deadband(0.01, 3200, Joystick.Left_Joystick_Y()));
		m_fpga::write(0x800, 1500 + (int32_t)scale_deadband(0.01, 3200, -1*Joystick.Right_Joystick_Y()));
		//std::cout << "  " << Joystick.Left_Joystick_Y() << " " << Joystick.Right_Joystick_Y() << std::endl;
	}
	else
	{
		//std::cout << "NO FPGA FOUND" << std::endl;
		//td::cout << "  " << Joystick.Left_Joystick_Y() << " " << Joystick.Right_Joystick_Y() << std::endl;
	}
}

void virtual_joystick::configure()
{
	timeout_sec = 1;
	timeout_usec = 500000;
	JoyStickPoll.run_when(Started);
}

void virtual_joystick::poll()
{
	while(true) {}; //temp disable
	
	//std::cout << "POLL RUNNING" << std::endl;
	unsigned int i;
	std::vector<m_tag *> tags = get_tag_broadcast("Joystick.Left_Joystick_Y", timeout_sec, timeout_usec);
	std::cout << "TAG SIZE: " << tags.size() << std::endl;
	for(i = 0; i < tags.size(); i++)
	{
		m_tag * t = tags.at(i);
		m_num<int> *nt = dynamic_cast<m_num<int>*>(t);
		if(nt != NULL)
		{
			Left_Joystick_Y() = *nt;
		}						
	}
	if(tags.size() == 0)
	{
		Left_Joystick_Y() = 0;
		timeout_usec += 100000;
		if(timeout_usec >= 1000000)
		{
			timeout_usec = 0;
			timeout_sec++;
		}
	}
	else
	{
		timeout_usec -= 100000;
		if(timeout_usec <= 0 && timeout_sec > 0)
		{
			timeout_usec = 900000;
			timeout_sec--;
		}
		else if(timeout_usec < 100000)
		{
			timeout_usec = 100000;
		}
		if(timeout_sec < 0)
			timeout_sec = 0;
	}
	std::cout << "TSEC: " << timeout_sec << " TUSEC: " << timeout_usec << std::endl;
	tags = get_tag_broadcast("Joystick.Right_Joystick_Y", timeout_sec, timeout_usec);
	std::cout << "TAG SIZE: " << tags.size() << std::endl;
	for(i = 0; i < tags.size(); i++)
	{
		m_tag * t = tags.at(i);
		m_num<int> *nt = dynamic_cast<m_num<int>*>(t);
		if(nt != NULL)
		{
			Right_Joystick_Y() = *nt;
		}
	}
	
	if(tags.size() == 0)
	{
		Right_Joystick_Y() = 0;
		timeout_usec += 100000;
		if(timeout_usec >= 1000000)
		{
			timeout_usec = 0;
			timeout_sec++;
		}
	}
	else
	{
		timeout_usec -= 100000;
		if(timeout_usec <= 0 && timeout_sec > 0)
		{
			timeout_usec = 900000;
			timeout_sec--;
		}
		else if(timeout_usec < 100000)
		{
			timeout_usec = 100000;
		}
		if(timeout_sec < 0)
			timeout_sec = 0;
	}
	std::cout << "TSEC: " << timeout_sec << " TUSEC: " << timeout_usec << std::endl;
}