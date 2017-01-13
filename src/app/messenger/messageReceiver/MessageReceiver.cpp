/*****************************************************************************/
/*!
 * @file MessageReceiver.cpp
 * @brief The implementation of MessageReceive class
 *
 *
 * @detail Using Poco library to implement a UDP server.
 *         Using ZeroMQ to implement a publisher who
 *               publish the message to subscribers.
 *
 * Modified History
 * 2016-Dec-08 Created tien.nguyenanh94@gmail.com
                Modified thuhang.nguyen8894@gmail.com
*/

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
    this->socket.bind(sa, true); //Poco::Net::DatagramSocket socket;
    this->thread.start(*this);   //Poco::Thread thread;
    this->ready.wait();          //Poco::Event ready;
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
    char* pBuffer = new char[this->bufferSize];

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5563");

    while(!this->stop)
    {
        if (this->socket.poll(span, Poco::Net::Socket::SELECT_READ))
        {
            try
            {
                Poco::Net::SocketAddress sender;
                int n = this->socket.receiveFrom(pBuffer, this->bufferSize, sender);

                char* jsonString = NULL;

                /*!
                 * Appending IP of Sender to message
                 */
                strcat(pBuffer, SENSOR_MESSAGE_SPLITTER); 
                strcat(pBuffer, sender.toString().c_str());

                if (isSensorMessage(pBuffer))
                {
                    if (!buildJson(pBuffer, &jsonString))
                    {
                        continue;
                    }

                    MESSAGE_TYPE messageType = getJSONMessageType(pBuffer);
                    
                    std::string topic = convertMessageTypeToStr(messageType);
                    s_sendmore (publisher, (char*)topic.c_str());
                    s_send (publisher, jsonString);
                    sleep (1);
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

