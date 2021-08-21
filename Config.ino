// Configuracion

AnalogPin  		Selector_on    		(A4);
AnalogPin  		Selector_off		(A5);
DigitalPin 		Selector_timer		(6);
DigitalPin 		Selector_sensor		(7);
DigitalPin 		Sensor_PIR			(4);
Led 			Led_test			(13);
LedPWM 			Led_state_PWM		(11);
Led 			Led_state_Digital 	(11);
DigitalActuator Relay  				(2);

SerialConsole 	Msg;
AsyncDelay 		Timer;

unsigned long MaxTime = 30000;
unsigned long MinTime = 60000;