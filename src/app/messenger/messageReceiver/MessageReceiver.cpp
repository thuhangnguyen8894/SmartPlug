/*****************************************************************************/
/*!
 * @file MessageReceiver.cpp
 * @brief The implementation of MessageReceive class
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail Using Poco library to implement a UDP server
 *
 * Modified History
 * ---------------
 * 2016-Dec-08 Created Tien Anh Nguyen 
 */
/*****************************************************************************/

#include "MessageReceiver.h"


MessageReceiver::MessageReceiver(int bufferSize):
    thread("MessageReceiver"),
    stop(false),
    bufferSize(bufferSize)
{
    this->socket.bind(Poco::Net::SocketAddress(), true);
    this->thread.start(*this);
    this->ready.wait();
}

MessageReceiver::MessageReceiver(const Poco::Net::SocketAddress& sa, int bufferSize):
    thread("MessageReceiver"),
    stop(false),
    bufferSize(bufferSize)
{
    this->socket.bind(sa, true);
    this->thread.start(*this);
    this->ready.wait();
}

MessageReceiver::~MessageReceiver()
{
    this->stop = true;
    this->thread.join();
}

Poco::UInt16 MessageReceiver::port() const
{
    return this->socket.address().port();
}

void MessageReceiver::run()
{
    std::cout << "Starting here!!!" << std::endl;
    this->ready.set();
    Poco::Timespan span(250000);
    char* pBuffer = new char[this->bufferSize];
    while(!this->stop)
    {
        if (this->socket.poll(span, Poco::Net::Socket::SELECT_READ))
        {
            try
            {
                Poco::Net::SocketAddress sender;
                int n = this->socket.receiveFrom(pBuffer, this->bufferSize, sender);
                std::cout << "Message is: " << pBuffer << std::endl;

                if (strlen(pBuffer) > 0 && strlen(pBuffer) < 4)
                {
                    char typeOfMessage = pBuffer[0];
                    char LSB = pBuffer[1];
                    char MSB = pBuffer[2];

                    uint16_t lightIntensity = LSB | uint16_t(MSB) << 8;

                    std::cout << "Light Intensity is: " << lightIntensity << std::endl;
                }

            }
            catch(Poco::Exception& ex)
            {
                std::cout << "MessageReceiver: " << ex.displayText() << std::endl;
            }
        }
    }

    if (pBuffer != NULL)
    {
        delete pBuffer;
    }
}

Poco::Net::SocketAddress MessageReceiver::address() const
{
    return this->socket.address();
}

