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
  Led_state.useTimeBlink(1000);
}

void loop() {
  Led_state.blink();
}