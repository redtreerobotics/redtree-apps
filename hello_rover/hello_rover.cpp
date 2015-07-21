#include "hello_rover.h"
#include <iostream>

/*
 * Basic code that makes a driveable rover with
 * a controller
 * 
 * Jason Ernst, 2015
 * Redtree Robotics
 */

redtree_rover rover{"rover"};

void redtree_rover::configure(void)
{
	Control_Routine.run_every_when(100000, Joystick.Started);
}

void redtree_rover::start(void)
{
	Joystick.StartCommand();
}

void redtree_rover::control(void)
{
	if(m_fpga::isFound())
	{
		m_fpga::write(0xC00,1500 + (int32_t)scale_deadband(0.01, 3200, Joystick.Left_Joystick_Y()));
		m_fpga::write(0x800, 1500 + (int32_t)scale_deadband(0.01, 3200, -1*Joystick.Right_Joystick_Y()));
	}
	else
		std::cout << "NO FPGA FOUND" << std::endl;
}
