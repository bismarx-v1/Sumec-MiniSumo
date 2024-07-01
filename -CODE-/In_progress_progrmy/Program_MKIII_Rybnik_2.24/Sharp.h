#include <SharpIR.h>

class Sharp_sensor
{
  public:
    Sharp_sensor(uint8_t pin);
    int get();

  private:
    uint8_t pin;
    int mode = 0;
    int dis; 
    SharpIR test;
};
