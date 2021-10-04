#include <AsyncDelay.h>

//-------------------------------------
/*
    Basic Class
*/
//-------------------------------------
class Pin{
  private:
    int _pin = 0;
  public:
    Pin(int pin){
      this->_pin = pin;
    }
    int getPin(){
      return this->_pin;
    }
    void Out(){
      pinMode(this->_pin,OUTPUT);
    }
    void In(){
      pinMode(this->_pin,INPUT);
    }
};

class DigitalPin: public Pin {
  public:
    DigitalPin(int pin):Pin(pin){};
    bool Read(){
      return digitalRead(this->getPin());
    }
    void Write(bool state){
      digitalWrite(this->getPin(),state);
    }
    bool If(bool value){
      return this->Read()==value;
    }
};

class AnalogPin: public Pin {
  public:
    AnalogPin(int pin):Pin(pin){};
    int Read(){
      return analogRead(this->getPin());
    }
    void Write(int state){
      analogWrite(this->getPin(),state);
    }
    bool If(int value){
      return this->Read()==value;
    }
};

//-------------------------------------
/*
    Tools
*/
//-------------------------------------

class DigitalActuator: public DigitalPin{
  public:
    DigitalActuator(int pin):DigitalPin(pin){}
    void On(){
      this->Write(true);
    }
    void Off(){
      this->Write(false);
    }
    void Switch(){
      if(this->If(true))this->Off();
      else if(this->If(false))this->On();
    }
};

class AnalogActuator: public AnalogPin{
    private:
        bool _state = false;
  public:
    AnalogActuator(int pin):AnalogPin(pin){}
    void Set(int number){
      this->Write(number);
    }
    bool If(int value){
        return this->_state==value;
    }
    void Switch(int rangeOn, int rangeOff){
      if(this->If(false))this->Set(rangeOn);
      else if(this->If(true))this->Set(rangeOff);
    }
};

class Led: public DigitalActuator{
  private:
    AsyncDelay TimerLed;
  public:
    Led(int pin):DigitalActuator(pin){}
    void useTimeBlink(unsigned long time){
      this->TimerLed.start(time, AsyncDelay::MILLIS);
    }
    void blink(){
      if(this->TimerLed.isExpired()){
        this->Switch();
        this->TimerLed.repeat();
      }
    }
};

class LedPWM:public AnalogActuator{
  private:
    AsyncDelay TimerLed;
  public:
    LedPWM(int pin):AnalogActuator(pin){}
    void to(int time, int start = 0,int end = 0){
      if(start==0&&end==0)Serial.println("test");
      else{
        unsigned long TimeDelay;
        TimeDelay = time/end;
        this->TimerLed.start(TimeDelay,AsyncDelay::MILLIS);
        while(start<end){
          if(this->TimerLed.isExpired()){
            this->Set(start);
            start++;
            this->TimerLed.repeat();
          }
        }
        TimeDelay = time/start;
        this->TimerLed.start(TimeDelay,AsyncDelay::MILLIS);
        while(start>end){
          if(this->TimerLed.isExpired()){
            this->Set(start);
            start--;
            this->TimerLed.repeat();
          }
        }
        this->TimerLed.restart();
      }
    }
    void blink(int time, int max = 255){
      this->to(time/2,0,max); 
      this->to(time/2,max,0);
    }
};

//-------------------------------------
/*
    Debug
*/
//-------------------------------------

class SerialConsole{
  private:
    int _baud = 9600;
  public:
    SerialConsole(){}
    SerialConsole(int baud){
      if(baud==0)this->_baud = 9600;
      else this->_baud = baud;
    }
    void init(){
      Serial.begin(this->_baud);
    }
    void ReadDigital(DigitalActuator obj){
      Serial.println(obj.Read());
    }
    void ReadAnalog(AnalogActuator obj){
      Serial.println(obj.Read());
    }
};
