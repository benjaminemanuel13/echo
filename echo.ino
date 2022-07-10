#include <HardwareSerial.h>

int count = 1;
int av = 0;
HardwareSerial MySerial(1);

void setup() {
    MySerial.setRxBufferSize(2);
    MySerial.setTxBufferSize(2);
    MySerial.begin(9600, SERIAL_8N1, 4, 5);
    Serial.begin(115200);
    MySerial.setPins(4, 5, 16, 17);
    MySerial.setHwFlowCtrlMode(HW_FLOWCTRL_CTS_RTS, 1);
    
    Serial.println("Started");
}
bool first = true;
bool finished = false;
bool done = false;
uint8_t buff[150];

void loop() {
  if(!finished)
  {
    doRead(); 
  }

  if(finished && !done)
  {
    Serial.print("Inside:");
    Serial.println(count);
//    buff[0] = 'a';
//    buff[1] = 'b';
//    buff[2] = 'c';
//    buff[3] = 'd';
//    buff[4] = 'e';
//    buff[5] = 'f';
//    buff[6] = 'g';
//    buff[7] = 'h';
//    buff[8] = 'i';
//    buff[9] = 'j';
//    buff[10] = 'k';
//    buff[11] = 'l';
    
    for(int i = 0; i < count - 1; i++)
    {
      MySerial.write(buff[i]);
      delay(100);
    }

    done = true;
  }
}

void doRead()
{
  uint8_t byteFromSerial = 0;
  
  while(MySerial.available() !=0 && byteFromSerial != 185)
  {  
    byteFromSerial = MySerial.read();
    delay(10);
    
    if(byteFromSerial > 0)
    {
      Serial.print(count);
      Serial.print(":");
      Serial.println(byteFromSerial);

      if(count < 150)
      {
        buff[count] = byteFromSerial;
      }

      if(byteFromSerial == 185)
      {
        finished = true;
      }

      count++;
    }
  }  
}
