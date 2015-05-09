/**
 * 
 * Spark SMS Library
 * 
 * examples/sendSMS.cpp
 * 
 * @author Harrison Jones
 * @version 1.0 May 08, 2015
 * 
*/

/* Includes ------------------------------------------------------------------*/  
#include "application.h"
#include "SparkSMS.h"

/* Defines -------------------------------------------------------------------*/
// We need the core to be connected to the internet and the Spark cloud for the SparkSMS library to work
SYSTEM_MODE(AUTOMATIC);

/* Variables/Objects ---------------------------------------------------------*/ 
// Instantiate a SparkSMS object
SparkSMS sms;

/**
 * 
 * setup
 * 
 * The main setup function. Runs once
 * 
*/
void setup()
{
    sms.sendSMS("4155550000", "Hello World!");
}

/**
 * 
 * loop
 * 
 * The main loop function. Runs indefinitely
 * 
*/
void loop()
{
}