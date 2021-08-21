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
    // Led_test.Set(0);
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(true)){
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(false)){
      Led_state.blink(1000,10);
      Led_state.blink(1000,100);
      Led_state.blink(1000,200);
  }
  Led_state.Set(0);
}