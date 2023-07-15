// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>


#define MotorInterfaceType 4

// Define a stepper and the pins it will use
AccelStepper stepper(MotorInterfaceType, 4, 5, 6, 7); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
}

void loop()
{
    if (stepper.distanceToGo() == 0)
    {
	// Random change to speed, position and acceleration
	// Make sure we dont get 0 speed or accelerations
	delay(1000);
	stepper.move(2000);
	stepper.setMaxSpeed(500);
	stepper.setAcceleration(100);
    }
    stepper.run();
}
