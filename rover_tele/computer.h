#ifndef COMPUTER_H
#define COMPUTER_H

/*
 * Takes xbox controller and share it as input with a remote
 * rover
 */

#include <rtr.h>
#include <rt_input_user.h>

void configure(void) {}
void initialize(void) {}
void setup(void) {}
void start(void) {}

class computer : public m_device
{
	public:
		using m_device::m_device;
		XBOX_Joystick Joystick{"Joystick"};
		
		void start(void);
};


#endif