#include <rtr.h>
#include "computer.h"
#include <iostream>

computer tele{"tele"};

void computer::start(void)
{
	Joystick.StartCommand();
}