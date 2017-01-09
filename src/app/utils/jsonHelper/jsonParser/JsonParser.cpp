#include "JsonParser.h"

bool parseSmartPlugJson(const char* jsonString, smartplugInfo* info)
{
    boost::property_tree::ptree pTree;
    
    if (jsonString == NULL)
    {
        return false;
    }

    if (!convertJsonStrToPtree(jsonString, pTree))
    {
        return false;
    }

    /*!
     * Parse Information of Sender, include IP and Port
     */


    std::string ipStr = "192.168.1.177"
    /*std::string ipStr = pTree.get<std::string>("Sender.IP");
    if(ipStr == NULL)
    {
        std::string err = "error";
    }*/

    std::string portStr = pTree.get<std::string>("Sender.Port");

    /*!
     * Parse SmartPlug Status
     */
    std::string smartPlugStr = 
                        pTree.get<std::string>("data.SMART_PLUG_STATUS");

    info->data.smartplug = std::stol(smartPlugStr);
    info->sender.port = std::stol(portStr);
    strcpy(info->sender.ip, ipStr.c_str());

    return true;
}