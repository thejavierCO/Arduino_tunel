void setup() {
  Selector_on.Out();
  Selector_off.Out();
  Selector_timer.Out();
  Selector_sensor.Out();

  Sensor_PIR.In();
  Led_test.Out();
  Led_state_PWM.Out();
  Led_state_Digital.Out();
  Relay.Out();
  Msg.init();

  Led_state_Digital.useTimeBlink(1000);
}

void TimerLoop(unsigned long MinValue,unsigned long MaxValue,unsigned long MinTime,unsigned long MaxTime){
  Timer.start(map(Selector_on.Read(),0,600,MinTime,MaxTime),AsyncDelay::MILLIS);
  while(!Timer.isExpired()){
    Led_state_PWM.blink(1000,100);
    Relay.On();
  }
  Timer.start(map(Selector_off.Read(),0,600,MinTime,MaxTime),AsyncDelay::MILLIS);
  while(!Timer.isExpired()){
    Led_state_Digital.Off();
    Relay.Off();
  }
}

void loop() {
  while(Selector_timer.If(true)&&Selector_sensor.If(false))TimerLoop(0,600,MinTime,MaxTime);
  while(Selector_timer.If(false)&&Selector_sensor.If(true))if(Sensor_PIR.Read()==true)TimerLoop(0,600,MinTime,MaxTime);
  while(Selector_timer.If(false)&&Selector_sensor.If(false))if(Sensor_PIR.If(true))Led_state_Digital.On();else Led_state_Digital.Off();
  Led_state_Digital.Off();
}