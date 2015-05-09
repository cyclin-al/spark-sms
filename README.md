# About
A Spark library for sending and receiving SMS. Specially formatted Spark events, along with a webhook, are used to send and receive text messages in a way that is platform agnostic. As long as the webhook and backend service can be configured to correctly format and route incoming and outgoing text messages then this library will work. The firmware, along with examples, can be found in the firmware folder. Full tutorials, containing backend code and webhook defintions, can be found in the tutorial folder.

# Tutorials

Tutorials for using the following services have been written

| Backend Service   | SMS Send          | SMS Receive       | Server Required | Notes |
|-------------------|-------------------|-------------------|-----------------|-------|
| Tropo             | No  ($0.01+/sms)  | No  ($0.01/sms)   | No              | Development is free for send/receive. $3/mo for a number
| Twilio            | No  ($0.0075+/sms)| No ($0.0075/sms)  | YES (Receive)   | $1/mo for a number
| Google Voice      | No  (Free)        | No (Free)         | ?               | Not for production. Google's API is not stable

# Firmware Functions

## Sending SMS

1. **Call** `sendSMS(char* number, char* message)`

    - **Param** `number` a char pointer to a char array containing the number to send the message to
	- **Param** `message` a char point to a char array containing the message to send in the SMS

### Example

	/* Includes ------------------------------------------------------------------*/  
	#include "application.h"
	#include "SparkSMS.h"

	/* Defines -------------------------------------------------------------------*/
	// We need the core to be connected to the internet and the Spark cloud for the SparkSMS library to work
	SYSTEM_MODE(AUTOMATIC);

	/* Variables/Objects ---------------------------------------------------------*/ 
	// Instantiate a SparkSMS object
	SparkSMS sms;

	void setup()
	{
	    sms.sendSMS("4155550000", "Hello World!");
	}

	void loop()
	{
	}

## Receiving SMS

1. **Call** `Spark.subscribe("SMSINC",...)` to subscribe to the incoming sms event
2. **Call** `handleIncSMS(const char *event, const char *data)` inside your event callback/handler
    - **Param** `event` a char pointer to a char array containing the event name
	- **Param** `data` a char point to a char array containing the event data
2. **Call** `handleIncSMS(const char *event, const char *data)` inside your event callback/handler
    - **Param** `event` a char pointer to a char array containing the event name
	- **Param** `data` a char point to a char array containing the event data
3. **Call** `getNum()` and `getMessage()` to grab the incoming SMS's number and message and char arrays

### Example

	/* Includes ------------------------------------------------------------------*/  
	#include "application.h"
	#include "SparkSMS.h"
	
	/* Defines -------------------------------------------------------------------*/
	// We need the core to be connected to the internet and the Spark cloud for the SparkSMS library to work
	SYSTEM_MODE(AUTOMATIC);
	
	/* Variables/Objects ---------------------------------------------------------*/ 
	// Instantiate a SparkSMS object
	SparkSMS sms;
	
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
	
	void setup()
	{
	    Spark.subscribe("SMSINC", smsHandler, MY_DEVICES);
	}
	
	void loop()
	{
	}


# To Do / How Can You Help?

1. Write tutorials for Twilio, Google Voice, etc
2. Generate a sms.begin() function which automatically subscribes to the correct event and then takes a callback which is passed the number and message so the user doesn't have to interface with spark events at all.
3. Functions which allow for voice calls
4. Functions which allow for different sending numbers to be used. Ability to parse incoming number as well (what number was the text sent to?)