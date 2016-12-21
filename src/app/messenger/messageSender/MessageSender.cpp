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
 * ---------------
 * 2016-Dec-08 Created Tien Nguyen Anh
 */
/*****************************************************************************/

#include "MessageSender.h"

MessageSender::MessageSender()
{

}

bool MessageSender::sendMessageUDP(std::string data, std::string host,
									unsigned int port)
{

}

bool MessageSender::sendMessageTCP(std::string message, std::string host,
									unsigned int port)
{
    Poco::Net::SocketAddress socketAddress(host, port);
    this->sender.connect(socketAddress);

    int sizePackage = this->sender.sendBytes(message.data(), message.size());

    return sizePackage > 0;
}
