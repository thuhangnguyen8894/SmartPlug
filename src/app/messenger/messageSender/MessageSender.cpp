/*****************************************************************************/
/*!
 * @file MessageSender.h
 * @brief The blueprint of MessageSender
 *
 *
 * @detail The class uses UDP protocol and poco library. 
 *
 * Modified History
 * ---------------
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
