/*****************************************************************************/
/*!
 * @file MessageReceiver.h 
 * @brief The declaration of MessageReceiver.
 *        The class has ability to receiver a message from a client.
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail The class is expected to receive a message from a Arduino client
 *             or another one. The class also be able to redirect the message
 *             to another component for the next process.
 *
 * Modified History
 * ----------------
 * 2016-Dec-08 Created Tien Nguyen Anh
 */
/*****************************************************************************/

#ifndef __MESSAGE_RECEIVER__
#define __MESSAGE_RECEIVER__

#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#include "zhelpers.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/DatagramSocket.h"
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
    Poco::Net::SocketAddress address() const;
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
