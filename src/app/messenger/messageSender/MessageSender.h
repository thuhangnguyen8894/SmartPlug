/*****************************************************************************/
/*!
 * @file MessageSender.h
 * @brief The blueprint of MessageSender
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail The class uses UDP protocol and poco library. 
 *
 * Modified History
 * ----------------
 * 2016-Dec-08 Created Tien Nguyen Anh
 */
/*****************************************************************************/

#ifndef __MESSAGE_SENDER_H__
#define __MESSAGE_SENDER_H__

#include <iostream>
#include <string>

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"

class MessageSender
{
public:
    MessageSender();
    bool sendMessage(std::string data, std::string host, unsigned int port);

private:
    Poco::Net::DatagramSocket sender;
};

#endif
