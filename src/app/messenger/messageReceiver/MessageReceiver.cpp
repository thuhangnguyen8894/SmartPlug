/*****************************************************************************/
/*!
 * @file MessageReceiver.cpp
 * @brief The implementation of MessageReceive class
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail Using Poco library to implement a UDP server.
 *         Using ZeroMQ to implement a publisher who
 *               publish the message to subscribers.
 *
 * Modified History
 * ---------------
 * 2016-Dec-08 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
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
    
    zmq_close(this->publisher);
    zmq_ctx_destroy(this->zmq_context);
}

Poco::UInt16 MessageReceiver::port() const
{
    return this->socket.address().port();
}

void MessageReceiver::run()
{
    this->ready.set();
    Poco::Timespan span(250000);
    

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PAIR);
    zmq_bind(publisher, "tcp://*:5563");

    while(!this->stop)
    {
        if (this->socket.poll(span, Poco::Net::Socket::SELECT_READ))
        {
            try
            {
                char* pBuffer = new char[this->bufferSize];
                Poco::Net::SocketAddress sender;
                int n = this->socket.receiveFrom(pBuffer, this->bufferSize, sender);

                std::string jsonString;

                char* datetime = timer();
                char* idTableTimerChar = idTableTimer();

                /*!
                 * Appending IP of Sender to message
                 * Appending datetime of DatetimeSP to message
                 */
                strcat(pBuffer, SEMICOLON_SPLITTER);
                strcat(pBuffer, sender.toString().c_str());
                strcat(pBuffer, SEMICOLON_SPLITTER);
                strcat(pBuffer, idTableTimerChar);
                strcat(pBuffer, UNDERSCORS_SPLITTER);
                strcat(pBuffer, datetime);

                std::cout<<pBuffer<<std::endl;

                /*convert char to string*/
                std::string s_pBuffer(pBuffer);

                if (isSensorMessage(s_pBuffer))
                {
                    if (!buildJson(s_pBuffer, jsonString))
                    {
                        std::cout << "buildJson ERROR" << std::endl;
                        continue;
                    }

                    MESSAGE_TYPE messageType = getJSONMessageType(s_pBuffer);
                    
                    std::string topic = convertMessageTypeToStr(messageType);
                    s_sendmore (publisher, (char*)topic.c_str());
                    s_send(publisher, (char*)jsonString.c_str());                    
                   
                    /*char* string = (char*)jsonString.c_str();
                    zmq_send (publisher, string, strlen (string), ZMQ_NOBLOCK);*/
                    
                    std::cout << "send SUCCESSFULL" << std::endl;
                    sleep (1);
                 }                
                 if (pBuffer != NULL)
                {                    
                    delete pBuffer;              
                }

            }
            catch(Poco::Exception& ex)
            {
                std::cout << "MessageReceiver: " << ex.displayText() << std::endl;
            }
        }
    }
}

Poco::Net::SocketAddress MessageReceiver::address() const
{
    return this->socket.address();
}