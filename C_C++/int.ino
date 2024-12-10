#define INPUT_PORT 2

#define OK_LED 3
#define PANIC_LED1 4
#define PANIC_LED2 5

int switchState = 0;

void boot() {
	const int BOOT_TIME = 3000;
	const int UNIT = 250;

	digitalWrite(OK_LED, LOW);

	for (int i = 0; i < BOOT_TIME; i++) {
		digitalWrite(PANIC_LED1, HIGH);
		digitalWrite(PANIC_LED2, LOW);
		delay(UNIT);
		i += UNIT;

		digitalWrite(PANIC_LED1, LOW);
		digitalWrite(PANIC_LED2, HIGH);
		delay(UNIT);
		i += UNIT;
	}
}

void setup() {
	pinMode(INPUT_PORT,INPUT);

 	pinMode(OK_LED, OUTPUT);
	pinMode(PANIC_LED1, OUTPUT);
	pinMode(PANIC_LED2, OUTPUT);

	boot();
}

void loop() {
 	switchState = digitalRead(INPUT_PORT);
	
	if (switchState == LOW) {
		// the button is not pressed
		digitalWrite(OK_LED, HIGH);
		digitalWrite(PANIC_LED1, LOW);
		digitalWrite(PANIC_LED2, LOW);
 	} else { // the button is pressed
		digitalWrite(OK_LED, LOW);
		digitalWrite(PANIC_LED1, LOW);
		digitalWrite(PANIC_LED2, HIGH);
		delay(250);
		
		// toggle the LEDs
		digitalWrite(PANIC_LED1, HIGH);
		digitalWrite(PANIC_LED2, LOW);
		delay(250);
	}
}
