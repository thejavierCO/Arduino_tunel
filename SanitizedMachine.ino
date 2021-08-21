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
  public:
    AnalogActuator(int pin):AnalogPin(pin){}
    void Set(int number){
      this->Write(number);
    }
    void Switch(int rangeOn, int rangeOff){
      if(this->If(rangeOn))this->Set(rangeOff);
      else if(this->If(rangeOff))this->Set(rangeOn);
    }
};

class SerialConsole{
  private:
    int _baud = 9600;
  public:
    SerialConsole(int baud){
      if(baud==0)this->_baud = 9600;
      else this->_baud = baud;
    }
    void init(){
      Serial.begin(this->_baud);
    }
    void Text(char a[]){
      Serial.println(a);
    }
    void Bool(bool a){
      Serial.println(a);
    }
};