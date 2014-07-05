#include <LIS331.h>
byte state;
LIS331 lis;

lis.i2caddress=LR_SA0_LOW;
state=lis.getPowerStatus();
if (state==LR_POWER_OFF){
    lis.setPowerStatus(LR_POWER_NORM);
}
if (!lis.getXEnable()){
    lis.setXEnable(true);
}
while (!lis.statusHasXDataAvailable())
{
delay(1);
}

int16_t val;
lis.getXValue(&val);
Serial.print("X Axis Value: ");
Serial.println(val,DEC);
