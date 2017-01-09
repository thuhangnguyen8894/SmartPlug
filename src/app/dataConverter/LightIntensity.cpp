#include "LightIntensity.h"

LightIntensity::LightIntensity()
{
    this->moment = 0;
    this->lightIntensity = 0;
}

LightIntensity::LightIntensity(double moment, double lightIntensity)
{
    this->moment = moment;
    this->lightIntensity = lightIntensity;
}

void LightIntensity::setMoment(double moment)
{
    this->moment = moment;
}

void LightIntensity::setLightIntensity(double lightIntensity)
{
    this->lightIntensity = lightIntensity;
}

double LightIntensity::getMoment()
{
    return this->moment;
}

double LightIntensity::getLightIntensity()
{
    return this->lightIntensity;
}
