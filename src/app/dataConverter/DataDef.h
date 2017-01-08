#ifndef __DATA_STRUCT_DEF_H__
#define __DATA_STRUCT_DEF_H__

struct Sender
{
    char ip[20];
    long port;
};

struct smartplug
{
    long smartplug;
};

struct smartplugInfo
{
    smartplug data;
    Sender sender;

};

#endif
