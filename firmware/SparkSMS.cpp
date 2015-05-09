/**
 * 
 * Spark SMS Library
 * 
 * SparkSMS.cpp
 * 
 * @author Harrison Jones <harrison@hhj.me>
 * @version 1.0 May 08, 2015
 * 
*/

/* Includes ------------------------------------------------------------------*/ 
#include "SparkSMS.h"

/**
 * 
 * SparkSMS Constructor
 * 
 * Sets the internal number and message buffers to '0\'
 * 
*/
SparkSMS::SparkSMS()
{
    this->_buffNum[0] = '\0';
    this->_buffMessage[0] = '\0';
}

/**
 * 
 * sendSMS
 * 
 * Formats a SMS number and message into a json string and publishes it. Truncates the message if it is too long (max 37 characters)
 * 
 * @param number the number to send the message to
 * @param message the message to send
 * @return a boolean, true if the string was send to be published, false otherwise
 * 
*/
bool SparkSMS::sendSMS(char* number, char* message)          
{
    // Define a temporary buffer for both the string to be published and the message to be truncated.
    char buffPublish[63];
    char buffMessage[63];

    // If the number is longer than 47 characters then the publish string will exceed the 63 byte maximum.
    if(strlen(number) > 47)
        return false;
    
    // Calculate the maximum message length given the 63 byte publish limit
    unsigned int maxMessageLength = 63-strlen(number)-16;

    // Copy the given message string to the buffer, truncate if necessary
    strncpy(buffMessage,message,maxMessageLength);
    // Null terminate the string to ensure that there are no overflows
    buffMessage[maxMessageLength] = '\0';

    // Formatting the string to be published. Formatting string matches '{"n":"12345678901","m":"hello world"}'
    sprintf (buffPublish, "{\"n\":\"%s\",\"m\":\"%s\"}", number, buffMessage);
    // Null terminate the formatted string to ensure that there are no overflows
    buffPublish[62] = '\0';

    // Send the formatted string
    Spark.publish("SMSSEND",buffPublish, 60, PRIVATE);
    
    return true;
}

/**
 * 
 * handleIncSMS
 * 
 * Handles incoming SMS events and parses them to retrieve the number and message
 * 
 * @param event the event name. Not currently used
 * @param data the data to parse
 * @return a boolean, true if the number and message was successfully parsed, false otherwise
 * 
*/
bool SparkSMS::handleIncSMS(const char *event, const char *data) // The subscribe callback
{
    // Find the first command, which deliminates the number from the message. Correctly formatted incoming SMS event's follow this format: number,message
    char * pch = strchr(data, ',');
    
    // If a comma was not found return false
    if(pch == NULL)
        return false;
    
    // Find the position of the comma
    unsigned char cmaPos = (pch - data);
    
    // Copy all the characters up till the comma to a buffer and null terminate it. This string is the incoming number (the sender)
    strncpy(this->_buffNum, data, cmaPos);
    this->_buffNum[cmaPos] = '\0';
    
    // Copy all the characters after the comma to a buffer and null terminate it. This string is the incoming message 
    strncpy(this->_buffMessage, data+cmaPos+1, strlen(data)-cmaPos);
    this->_buffMessage[strlen(data)-cmaPos] = '\0';
    
    return true;
}

/**
 * 
 * getNum
 * 
 * Returns the latest number parsed from an incoming SMS event. 
 * 
 * @return a character array, NULL if no number has been parsed. 
 * 
*/
char* SparkSMS::getNum()
{
    return this->_buffNum;
}

/**
 * 
 * getMessage
 * 
 * Returns the latest message parsed from an incoming SMS event. 
 * 
 * @return a character array, NULL if no message has been parsed. 
 * 
*/
char* SparkSMS::getMessage()
{
    return this->_buffMessage;
}