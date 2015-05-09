/**
 * 
 * Spark SMS Library
 * 
 * examples/receiveSMS.cpp
 * 
 * @author Harrison Jones <harrison@hhj.me>
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
 * smsHandler
 * 
 * Callback function for handling incoming SMS events. Simply echos the message sent to it back to the sender
 * 
 * @param event the event name. Not currently used
 * @param data the SMS data to pass to the parser
 * 
*/
void smsHandler(const char *event, const char *data)
{
    if(sms.handleIncSMS(event,data))
    {
        sms.sendSMS(sms.getNum(), sms.getMessage());
    }
    else
    {
        Spark.publish("SMSFAIL","Failed to parse incoming sms");
    }
}

/**
 * 
 * setup
 * 
 * The main setup function. Runs once
 * 
*/
void setup()
{
    Spark.subscribe("SMSINC", smsHandler, MY_DEVICES);
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