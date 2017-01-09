/*****************************************************************************/
/*!
 * @file MessageReceiver.h 
 * @brief The declaration of MessageReceiver.
 *        The class has ability to receiver a message from a client.
 *
 * @detail The class is expected to receive a message from a Arduino client
 *             or another one. The class also be able to redirect the message
 *             to another component for the next process.
 *
 * Modified History
 * ----------------
 */
/*****************************************************************************/

#ifndef __MESSAGE_RECEIVER__
#define __MESSAGE_RECEIVER__

#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#include "zhelpers.h"
#include "Poco/Net/Socket.h"            //Socket is the common base class for StreamSocket, ServerSocket, DatagramSocket and other socket classes. It provides operations common to all socket types.
#include "Poco/Net/DatagramSocket.h"    //This class provides an interface to an UDP stream socket.
#include "Poco/Thread.h"
#include "Poco/Event.h"
#include "Poco/Timespan.h"

#include "JsonCommon.h"
#include "JsonBuilder.h"

#define PUBLISHER_PORT_OPT 5600

class MessageReceiver: public Poco::Runnable
{
public:
    MessageReceiver(int bufferSize = 256);
    MessageReceiver(const Poco::Net::SocketAddress& sa, int bufferSize = 256);
    ~MessageReceiver();
    Poco::UInt16 port() const;
    Poco::Net::SocketAddress address() const;   //Returns the IP address and port number of the socket.

    void run();

private:
    Poco::Net::DatagramSocket socket;
    Poco::Thread thread;
    Poco::Event ready;
    bool stop;
    int bufferSize;
    void* zmq_context = NULL;
    void* publisher = NULL;
};

#endif
