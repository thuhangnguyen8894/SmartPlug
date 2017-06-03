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

#include <regex>
#include <cwctype>
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

bool isArduinoMessage(const std::string& message)
{
    try
    {
        std::regex pattern("(.*);(.*):(.*):(.*):(.*):(.*)");
        std::smatch match;
        return (std::regex_search(message, match, pattern) && match.size() > 1);
    }catch(std::regex_error& e)
    {
        /*!
         * @todo handle error.
         */
    }

}

void removeInvalidCharacter(std::string& jsonMessage)
{
    for (int i = 0; i < jsonMessage.length(); i++)
    {
        if (((int)jsonMessage[i]) < 32 || ((int)jsonMessage[i]) > 125)
        {
            jsonMessage.pop_back();
            break;
        }
    }
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

                if (isArduinoMessage(pBuffer))
                {
                    char* datetime = timer();

                    /*char* idTableTimerChar = idTableTimer();*/
                    char* idTableTimerChar = idTimer();

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
                    
                    std::string s_pBuffer(pBuffer);

                    if (!buildJson(s_pBuffer, jsonString))
                    {
                        std::cout << "buildJson ERROR" << std::endl;
                        continue;
                    }
                    /*
                    ----------------------------------------------------
                     */

                    MESSAGE_TYPE messageType = getJSONMessageType(s_pBuffer);

                    std::string topic = convertMessageTypeToStr(messageType);
                    s_sendmore (publisher, (char*)topic.c_str());
                    s_send(publisher, (char*)jsonString.c_str());

                    std::cout << "send SUCCESSFULL string" << std::endl;

                    sleep (1);
                }
                else
                {
                    /*!
                     * the message is json message.
                     */
                    std::string jsonMessage(pBuffer);
                    removeInvalidCharacter(jsonMessage);
                    std::string topicDjango;
                    if(parseJsonToTopic(jsonMessage, topicDjango))
                    {
                        std::cout << "topicDjango: " << topicDjango << std::endl;
                        s_sendmore (publisher, (char*)topicDjango.c_str());
                        s_send(publisher, (char*)jsonMessage.c_str());

                        std::cout << "send SUCCESSFULL json" << std::endl;

                        sleep (1);
                    }
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