#include <HardwareSerial.h>

int count = 1;
int av = 0;
HardwareSerial MySerial(1);

char charset[256];

void loadChars()
{
  for(int i = 0; i < 256; i++)
  {
    charset[i] = ' ';
  }

  //numbers
  charset[157] = '0';
  charset[155] = '1';
  charset[153] = '2';
  charset[151] = '3';
  charset[149] = '4';
  charset[147] = '5';
  charset[145] = '6';
  charset[143] = '7';
  charset[141] = '8';
  charset[139] = '9';

  //upper case alphabet
  charset[125] = 'A';
  charset[123] = 'B';
  charset[121] = 'C';
  charset[119] = 'D';
  charset[117] = 'E';
  charset[115] = 'F';
  charset[113] = 'G';
  charset[111] = 'H';
  charset[109] = 'I';
  charset[107] = 'J';
  charset[105] = 'K';
  charset[103] = 'L';
  charset[101] = 'M';
  charset[99] = 'N';
  charset[97] = 'O';
  charset[95] = 'P';
  charset[93] = 'Q';
  charset[91] = 'R';
  charset[89] = 'S';
  charset[87] = 'T';
  charset[85] = 'U';
  charset[83] = 'V';
  charset[81] = 'W';
  charset[79] = 'X';
  charset[77] = 'Y';
  charset[75] = 'Z';

  //lower case alphabet
  charset[61] = 'a';
  charset[59] = 'b';
  charset[57] = 'c';
  charset[55] = 'd';
  charset[53] = 'e';
  charset[51] = 'f';
  charset[49] = 'g';
  charset[48] = 'h';
  charset[47] = 'i';
  charset[45] = 'j';
  charset[43] = 'k';
  charset[41] = 'l';
  charset[39] = 'm';
  charset[37] = 'n';
  charset[35] = 'o';
  charset[33] = 'p';
  charset[31] = 'q';
  charset[29] = 'r';
  charset[27] = 's';
  charset[25] = 't';
  charset[23] = 'u';
  charset[21] = 'v';
  charset[19] = 'w';
  charset[17] = 'x';
  charset[15] = 'y';
  charset[13] = 'z';
}

void setup() {
    loadChars();
    
    MySerial.setRxBufferSize(2);
    MySerial.setTxBufferSize(2);
    MySerial.begin(9600, SERIAL_8N1, 4, 5);
    Serial.begin(115200);
    MySerial.setPins(4, 5, 16, 17);
    MySerial.setHwFlowCtrlMode(HW_FLOWCTRL_CTS_RTS, 1);
}
bool first = true;
bool finished = false;
bool done = false;
uint8_t buff[150];

char* getCommand()
{
  char comm[count - 1];

  for(int i = 0; i < count - 1; i++)
  {
      uint8_t val = buff[i];
      comm[i] = charset[val];
  }

  return comm;
}

// modes
// 0 = Awaiting Command
int mode = 0;
int oldmode = 0;

void loop() {
  if(oldmode != mode)
  {
    if(oldmode == 0)
    {
      finished = false;
      done = false;
    }
  }

  if(mode == 0)
  {
    if(!finished)
    {
      doCommandRead(); 
    }

    if(finished && !done)
    {
      //At this point we have the command
      char* command = getCommand();

      //do something based on command...

      //currently echoes
      for(int i = 0; i < count - 1; i++)
      {
        MySerial.write(buff[i]);
        delay(100);
      }

      done = true;
    }
  }
}

void doCommandRead()
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
