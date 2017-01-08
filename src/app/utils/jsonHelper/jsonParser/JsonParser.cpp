#include "JsonParser.h"

bool parseLightInteJson(const char* jsonString, LightIntensityInfo* info)
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
     * Parse Information of Sender
     */
    std::string ipStr = pTree.get<std::string>("Sender.IP");
    std::string portStr = pTree.get<std::string>("Sender.Port");

    /*!
     * Parse Light Intensity
     */
    std::string lightIntenStr = 
                        pTree.get<std::string>("data.LIGHT_INTENSITY_VALUE");

    info->data.lightIntensity = std::stol(lightIntenStr);
    info->sender.port = std::stol(portStr);
    strcpy(info->sender.ip, ipStr.c_str());
}