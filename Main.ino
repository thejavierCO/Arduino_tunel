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
  Timer.set(1000,AsyncDelay::MILLIS);
}

void loop() {
  while(Selector_timer.If(true)&&Selector_sensor.If(false)){
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(true)){
  }
  while(Selector_timer.If(false)&&Selector_sensor.If(false)){
    Led_state.to(30,5,0);
    Serial.println(Sensor_PIR.Read());
    Led_state.to(30,0,5);
  }
  Led_state.Set(0);
}