#ifndef __LIGHT_INTENSITY__
#define __LIGHT_INTENSITY__

class LightIntensity
{
public:
    LightIntensity();
    LightIntensity(double moment, double lightIntensity);
    void setMoment(double moment);
    void setLightIntensity(double lightIntensity);
    double getMoment();
    double getLightIntensity();

private:
    double moment;
    double lightIntensity;
};
#endif
