/**
 * 
 * Spark SMS Library
 * 
 * SparkSMS.h
 * 
 * @author Harrison Jones <harrison@hhj.me>
 * @version 1.0 May 08, 2015
 * 
*/

#ifndef SPARKSMS_H
#define	SPARKSMS_H

#include <cstring>
#include <stdio.h>
#include "application.h"

class SparkSMS
{
    public:
        SparkSMS();                                             // Object constructor. Sets up the SparkSMS object
        bool sendSMS(char* number, char* message);               // Sends a SMS as a formatted Spark event
        bool handleIncSMS(const char *event, const char *data); // Handles an incoming SMS event. Parses it and stores the number and message 
        char* getNum();                                         // Gets the parsed SMS number
        char* getMessage();                                     // Gets the parsed SMS message
    private:
        char _buffNum[63];                                      // A string to hold the parsed SMS number
        char _buffMessage[63];                                  // A string to hold the parsed SMS message
};
#endif	/* SPARKSMS_H */

