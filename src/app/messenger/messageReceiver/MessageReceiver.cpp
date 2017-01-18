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
    char* pBuffer = new char[this->bufferSize];

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5563");

    /*
    time
    */
    time_t now = time(0);
    tm *ltm = localtime(&now);

    while(!this->stop)
    {
        if (this->socket.poll(span, Poco::Net::Socket::SELECT_READ))
        {
            try
            {
                Poco::Net::SocketAddress sender;
                int n = this->socket.receiveFrom(pBuffer, this->bufferSize, sender);

                /*
                handle time
                */
                int year = YEAR + ltm->tm_year;
                std::cout<<"Year: "<<year<<std::endl;
                int month = MONTH + ltm->tm_month;
                std::cout<<"Month: "<<month<<std::endl;
                int day = ltm->tm_mday;
                std::cout<<"Day: "<<day<<std::endl;
                int hour = ltm->tm_hour;
                std::cout<<"Hour: "<<hour<<std::endl;
                int min = ltm->tm_min;
                std::cout<<"Min: "<<min<<std::endl;
                int sec = ltm->tm_sec;
                std::cout<<"Sec: "<<sec<<std::endl;

                std::string strYear = to_string(year);
                std::string strMonth = to_string(month);
                std::string strDay = to_string(day);
                std::string strHour = to_string(hour);
                std::string strMin = to_string(min);
                std::string strSec = to_string(sec);

                std::cout<<"String Year"<<strYear<<std::endl;
                std::cout<<"String Month"<<strMonth<<std::endl;
                std::cout<<"String Day"<<strDay<<std::endl;
                std::cout<<"String Hour"<<strHour<<std::endl;
                std::cout<<"String Min"<<strMin<<std::endl;
                std::cout<<"String Sec"<<strSec<<std::endl;


                std::string jsonString;

                /*!
                 * Appending IP of Sender to message
                 */
                strcat(pBuffer, SENSOR_MESSAGE_SPLITTER);
                strcat(pBuffer, sender.toString().c_str());
                strcat(pBuffer, SENSOR_MESSAGE_SPLITTER);
                strcat(pBuffer, strMonth.c_str());
                strcat(pBuffer, DATE_TIME_SLASH);
                strcat(pBuffer, strDay.c_str());
                strcat(pBuffer, DATE_TIME_SLASH);
                strcat(pBuffer, strYear.c_str());
                strcat(pBuffer, DATE_TIME_SPACE);
                strcat(pBuffer, strHour.c_str());
                strcat(pBuffer, IP_PORT_REGEX_SPLITTER);
                strcat(pBuffer, strMin.c_str());
                strcat(pBuffer, IP_PORT_REGEX_SPLITTER);
                strcat(pBuffer, strSec.c_str());

                //convert char to string
                std::string s_pBuffer(pBuffer); 

                if (isSensorMessage(s_pBuffer))
                {
                    if (!buildJson(s_pBuffer, jsonString))
                    {
                        continue;
                    }

                    MESSAGE_TYPE messageType = getJSONMessageType(s_pBuffer);
                    
                    std::string topic = convertMessageTypeToStr(messageType);
                    s_sendmore (publisher, (char*)topic.c_str());
                    s_send (publisher, (char*)jsonString.c_str());
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

