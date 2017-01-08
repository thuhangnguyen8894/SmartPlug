/*****************************************************************************/
/*!
 * @file MessageSender.h
 * @brief The blueprint of MessageSender
 *

 *
 * @detail The class uses UDP protocol and poco library. 
 *
 * Modified History
 * ----------------
 */
/*****************************************************************************/

#ifndef __MESSAGE_SENDER_H__
#define __MESSAGE_SENDER_H__

#include <iostream>
#include <string>

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"

#define PROCESSOR_PORT 6203

class MessageSender
{
public:
    MessageSender();
    bool sendMessageUDP(std::string data, std::string host, unsigned int port);
    bool sendMessageTCP(std::string data, std::string host, unsigned int port);

private:
    Poco::Net::DatagramSocket sender;
};

#endif
