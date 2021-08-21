void setup() {
  Selector_on.Out();
  Selector_off.Out();
  Selector_timer.Out();
  Selector_sensor.Out();

  Sensor_PIR.In();
  Led_test.Out();
  Led_state.Out();
  Relay.Out();

  Msg.init();
}

void loop() {
  while(Selector_timer.If(true)&&Selector_sensor.If(false)){
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(true)){
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(false)){
    Led_state.blink(2000,255,Selector_timer.If(false)&&Selector_sensor.If(false)?false:true);
  }
  Led_state.Set(0);
}