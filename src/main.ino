#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#define PIN 11
#define ledsN 120
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledsN, PIN, NEO_GRB + NEO_KHZ800);

char incoming_command;
boolean animate = true;
unsigned long loop_start;
unsigned long animation_change_timeout;
int storeLastAnimation = 0;
int    storeBrightness = 1;
int storeBrightnessLev = 2;
int    storeRedLevDIY1 = 3;
int  storeGreenLevDIY1 = 4;
int   storeBlueLevDIY1 = 5;
int    storeRedLevDIY2 = 6;
int  storeGreenLevDIY2 = 7;
int   storeBlueLevDIY2 = 8;
int    storeRedLevDIY3 = 9;
int  storeGreenLevDIY3 = 10;
int   storeBlueLevDIY3 = 11;
int    storeRedLevDIY4 = 12;
int  storeGreenLevDIY4 = 13;
int   storeBlueLevDIY4 = 14;
int    storeRedLevDIY5 = 15;
int  storeGreenLevDIY5 = 16;
int   storeBlueLevDIY5 = 17;
int    storeRedLevDIY6 = 18;
int  storeGreenLevDIY6 = 19;
int   storeBlueLevDIY6 = 20;
int brightness;
int brightnesslev;
int redlev = 0;
int greenlev = 0;
int bluelev = 0;
int DIYslot = 0;
int onoff = 1;
boolean offlightlev = true;

void setup() {
	Serial.begin(9600);
	pinMode(3, OUTPUT); //Wyjście dla diody 1
	pinMode(5, OUTPUT); //Wyjście dla diody 2
	pinMode(6, OUTPUT); //Wyjście dla diody 3
	pinMode(9, OUTPUT); //Wyjście dla diody 4
	pinMode(10, OUTPUT); //Wyjście dla diody 5
	pinMode(13, OUTPUT); // dioda 13
	strip.begin();
	//EEPROM.write(storeBrightness, 255);
	strip.setBrightness(brightness = EEPROM.read(storeBrightness));
	strip.show();
	//EEPROM.write(storeLastAnimation, 'H');
	incoming_command = EEPROM.read(storeLastAnimation);
	//incoming_command = '~'; // for TEST color
	//EEPROM.write(storeBrightnessLev, 0);
	brightnesslev = EEPROM.read(storeBrightnessLev);
}

void loop() {
	if (incoming_command != 'B' && incoming_command != 'C' && incoming_command != 'D' && incoming_command != 'A') lightlev();
	switch (incoming_command) {
	case '~': //TEST
		colorWipe(0, 0xd0, 0xff, 0);
		break;
	case 'A': //ONOFF
		if (onoff == 0) {
			onoff = 1;
			setAllDIY(0, 0, 0);
			//colorWipe(0, 0, 0, 0);
		}
		else {
			onoff = 0;
			incoming_command = EEPROM.read(storeLastAnimation);
		}
		break;
	case 'D': //BRIGHT_UP
		brightness_up();
		break;
	case 'C': //BRIGHT_DOWN
		brightness_down();
		break;
	case 'B': //BRIGHT_JUMP
		brightness_jump();
		break;
	case '1': //RED_UP
		redlev += 5;
		if (redlev > 255) redlev = 0;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '2': //RED_DOWN
		redlev -= 5;
		if (redlev < 0) redlev = 255;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '3': //GREEN_UP
		greenlev += 5;
		if (greenlev > 255) greenlev = 0;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '4': //GREEN_DOWN
		greenlev -= 5;
		if (greenlev < 0) greenlev = 255;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '5': //BLUE_UP
		bluelev += 5;
		if (bluelev > 255) bluelev = 0;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '6': //BLUE_DOWN
		bluelev -= 5;
		if (bluelev < 0) bluelev = 255;
		onoff = 0;
		setAllDIY(redlev, greenlev, bluelev);
		break;
	case '%': //FLASH
		if (DIYslot == 0) {
			digitalWrite(13, HIGH);
			DIYslot = 1;
		}
		else {
			digitalWrite(13, LOW);
			DIYslot = 0;
		}
		check_for_inputLoop();
		break;
	case '$': //AUTO
		if (DIYslot == 0) {
			redlev = random(255);
			greenlev = random(255);
			bluelev = random(255);
			setAllDIY(redlev, greenlev, bluelev);
		}
		else {
			redlev = 0;
			greenlev = 0;
			bluelev = 0;
			setAllDIY(redlev, greenlev, bluelev);
		}
		break;
	case '7': //DIY1
		EEPROM.write(storeLastAnimation, '7');
		onoff = 0;
		DIYsaving();
		break;
	case '8': //DIY2
		EEPROM.write(storeLastAnimation, '8');
		onoff = 0;
		DIYsaving();
		break;
	case '9': //DIY3
		EEPROM.write(storeLastAnimation, '9');
		onoff = 0;
		DIYsaving();
		break;
	case '!': //DIY4
		EEPROM.write(storeLastAnimation, '!');
		onoff = 0;
		DIYsaving();
		break;
	case '@': //DIY5
		EEPROM.write(storeLastAnimation, '@');
		onoff = 0;
		DIYsaving();
		break;
	case '#': //DIY6
		EEPROM.write(storeLastAnimation, '#');
		onoff = 0;
		DIYsaving();
		break;
	case 'E': //R1
		EEPROM.write(storeLastAnimation, 'E');
		onoff = 0;
		colorWipe(0xff, 0, 0, 0);
		break;
	case 'F': //G1
		EEPROM.write(storeLastAnimation, 'F');
		onoff = 0;
		colorWipe(0, 0xff, 0, 0);
		break;
	case 'G': //B1
		EEPROM.write(storeLastAnimation, 'G');
		onoff = 0;
		colorWipe(0, 0, 0xff, 0);
		break;
	case 'L': //R2
		EEPROM.write(storeLastAnimation, 'L');
		onoff = 0;
		colorWipe(0xff, 0x19, 0, 0);
		break;
	case 'M': //R3
		EEPROM.write(storeLastAnimation, 'M');
		onoff = 0;
		colorWipe(0xff, 0x26, 0, 0);
		break;
	case 'T': //R4
		EEPROM.write(storeLastAnimation, 'T');
		onoff = 0;
		colorWipe(0xff, 0x6a, 0, 0);
		break;
	case 'U': //R5
		EEPROM.write(storeLastAnimation, 'U');
		onoff = 0;
		colorWipe(0xff, 0xff, 0, 0);
		break;
	case 'K': //G2
		EEPROM.write(storeLastAnimation, 'K');
		onoff = 0;
		colorWipe(0, 0xff, 0x60, 0);
		break;
	case 'N': //G3
		EEPROM.write(storeLastAnimation, 'N');
		onoff = 0;
		colorWipe(0, 0xff, 0xae, 0);
		break;
	case 'S': //G4
		EEPROM.write(storeLastAnimation, 'S');
		onoff = 0;
		colorWipe(0x34, 0x82, 0x28, 0);
		break;
	case 'V': //G5
		EEPROM.write(storeLastAnimation, 'V');
		onoff = 0;
		colorWipe(0x00, 0x63, 0x43, 0);
		break;
	case 'J': //B2
		EEPROM.write(storeLastAnimation, 'J');
		onoff = 0;
		colorWipe(0, 0x26, 0xff, 0);
		break;
	case 'O': //B3
		EEPROM.write(storeLastAnimation, 'O');
		onoff = 0;
		colorWipe(0, 0, 0, 0);
		break;
	case 'R': //B4
		EEPROM.write(storeLastAnimation, 'R');
		onoff = 0;
		colorWipe(0x90, 0, 0xff, 0);
		break;
	case 'W': //B5
		EEPROM.write(storeLastAnimation, 'W');
		onoff = 0;
		colorWipe(0xff, 0, 0xff, 0);
		break;
	case 'I': //W2
		EEPROM.write(storeLastAnimation, 'I');
		onoff = 0;
		colorWipe(0xf8, 0x7c, 0xff, 0);
		break;
	case 'P': //W3
		EEPROM.write(storeLastAnimation, 'P');
		onoff = 0;
		colorWipe(0xf8, 0x7c, 0xff, 0);
		break;
	case 'Q': //W4
		EEPROM.write(storeLastAnimation, 'Q');
		onoff = 0;
		colorWipe(0, 0xd0, 0xff, 0);
		break;
	case 'X': //W5
		EEPROM.write(storeLastAnimation, 'X');
		onoff = 0;
		colorWipe(0, 0xd0, 0xff, 0);
		break;
	case 'Y': //FADE3
		EEPROM.write(storeLastAnimation, 'Y');
		onoff = 0;
		rainbow(20);
		break;
	case 'Z': //FADE7
		EEPROM.write(storeLastAnimation, 'Z');
		onoff = 0;
		rainbowCycle(20);
		break;
	case '&': //FADE/JUMP7
		EEPROM.write(storeLastAnimation, '&');
		onoff = 0;
		fade(100);
		break;
	case 'H': //W1
		EEPROM.write(storeLastAnimation, 'H');
		onoff = 0;
		colorWipe(0xff, 0xff, 0xff, 0);
		break;
	}
	animation_change_timeout = 0;
	animate = true;
}

//--------------------------------------------------------------------------------------------------//
//ANIMATIONS                                                                                        //
//--------------------------------------------------------------------------------------------------//
void colorWipe(byte red, byte green, byte blue, unsigned long speedDelay) {
	loop_start = millis() - 150;
	for (int i = 0; i < ledsN; i++) {
		strip.setPixelColor(i, strip.Color(red, green, blue));
		strip.show();
		mdelay(speedDelay);
		if (!animate) break;
	}
	check_for_inputLoop();
}

void fade(unsigned long speedDelay) {
	loop_start = millis();
	while (animate) {
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < ledsN; j++) {
				strip.setPixelColor(j, Wheel(i));
			}
			strip.show();
			mdelay(speedDelay);
			if (!animate) break;
		}
		check_for_input();
	}
}

void rainbow(unsigned long speedDelay) {
	loop_start = millis();
	while (animate) {
		for (int j = 0; j < 256; j++) {
			for (int i = 0; i < ledsN; i++) {
				strip.setPixelColor(i, Wheel((i + j) & 255));
			}
			strip.show();
			mdelay(speedDelay);
			if (!animate) break;
		}
		check_for_input();
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(unsigned long speedDelay) {
	loop_start = millis();
	while (animate) {
		for (int j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
			for (int i = 0; i < ledsN; i++) {
				strip.setPixelColor(i, Wheel(((i * 256 / ledsN) + j) & 255));
			}
			strip.show();
			mdelay(speedDelay);
			if (!animate) break;
		}
		check_for_input();
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//--------------------------------------------------------------------------------------------------//
//HARDWARE FUNCTIONS                                                                                //
//--------------------------------------------------------------------------------------------------//
void mdelay(unsigned long milli) {
	unsigned long endTime = millis() + milli;
	if (millis() == endTime) {
		check_for_input();
	}
	else {
		while (millis() < endTime) {
			check_for_input();
			if (!animate) break;
		}
	}
}

void check_for_inputLoop() {
	while (animate) {
		check_for_input();
	}
}

void check_for_input() {
	animation_change_timeout = millis() - loop_start;
	if (animation_change_timeout > 250) {
		if (offlightlev) lightlevoff();
		if (Serial.available() > 0) {
			incoming_command = Serial.read();
			Serial.print("I received: ");
			Serial.println(incoming_command);
			animate = false;
		}
	}
}

void brightness_up() {
	strip.setBrightness(brightness += 10);
	if (brightness > 254) brightness = 255;
	if (brightness >= 5) brightnesslev = 2;
	if (brightness >= 45) brightnesslev = 3;
	if (brightness >= 95) brightnesslev = 4;
	if (brightness >= 145) brightnesslev = 5;
	if (brightness >= 195) brightnesslev = 0;
	if (brightness >= 255) brightnesslev = 1;
	EEPROM.write(storeBrightness, brightness);
	EEPROM.write(storeBrightnessLev, brightnesslev);
	strip.setBrightness(brightness);
	strip.show();
	lightlev();
	incoming_command = EEPROM.read(storeLastAnimation);
}

void brightness_down() {
	strip.setBrightness(brightness -= 10);
	if (brightness < 5) brightness = 5;
	if (brightness >= 5) brightnesslev = 2;
	if (brightness >= 45) brightnesslev = 3;
	if (brightness >= 95) brightnesslev = 4;
	if (brightness >= 145) brightnesslev = 5;
	if (brightness >= 195) brightnesslev = 0;
	if (brightness >= 255) brightnesslev = 1;
	EEPROM.write(storeBrightness, brightness);
	EEPROM.write(storeBrightnessLev, brightnesslev);
	strip.setBrightness(brightness);
	strip.show();
	lightlev();
	incoming_command = EEPROM.read(storeLastAnimation);
}

void brightness_jump() {
	if (brightnesslev == 0) {
		strip.setBrightness(brightness = 255);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 1;
	}
	else if (brightnesslev == 1) {
		strip.setBrightness(brightness = 5);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 2;
	}
	else if (brightnesslev == 2) {
		strip.setBrightness(brightness = 45);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 3;
	}
	else if (brightnesslev == 3) {
		strip.setBrightness(brightness = 95);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 4;
	}
	else if (brightnesslev == 4) {
		strip.setBrightness(brightness = 145);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 5;
	}
	else if (brightnesslev == 5) {
		strip.setBrightness(brightness = 195);
		EEPROM.write(storeBrightness, brightness);
		strip.show();
		brightnesslev = 0;
	}
	EEPROM.write(storeBrightnessLev, brightnesslev);
	lightlev();
	incoming_command = EEPROM.read(storeLastAnimation);
}

void DIYsaving() {
	int redlevS;
	int greenlevS;
	int bluelevS;
	if (incoming_command == '7') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY1);
			greenlevS = EEPROM.read(storeGreenLevDIY1);
			bluelevS = EEPROM.read(storeBlueLevDIY1);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY1, redlev);
			EEPROM.write(storeGreenLevDIY1, greenlev);
			EEPROM.write(storeBlueLevDIY1, bluelev);
		}
	}
	else if (incoming_command == '8') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY2);
			greenlevS = EEPROM.read(storeGreenLevDIY2);
			bluelevS = EEPROM.read(storeBlueLevDIY2);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY2, redlev);
			EEPROM.write(storeGreenLevDIY2, greenlev);
			EEPROM.write(storeBlueLevDIY2, bluelev);
		}
	}
	else if (incoming_command == '9') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY3);
			greenlevS = EEPROM.read(storeGreenLevDIY3);
			bluelevS = EEPROM.read(storeBlueLevDIY3);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY3, redlev);
			EEPROM.write(storeGreenLevDIY3, greenlev);
			EEPROM.write(storeBlueLevDIY3, bluelev);
		}
	}
	else if (incoming_command == '!') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY4);
			greenlevS = EEPROM.read(storeGreenLevDIY4);
			bluelevS = EEPROM.read(storeBlueLevDIY4);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY4, redlev);
			EEPROM.write(storeGreenLevDIY4, greenlev);
			EEPROM.write(storeBlueLevDIY4, bluelev);
		}
	}
	else if (incoming_command == '@') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY5);
			greenlevS = EEPROM.read(storeGreenLevDIY5);
			bluelevS = EEPROM.read(storeBlueLevDIY5);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY5, redlev);
			EEPROM.write(storeGreenLevDIY5, greenlev);
			EEPROM.write(storeBlueLevDIY5, bluelev);
		}
	}
	else if (incoming_command == '#') {
		if (DIYslot == 0) {
			redlevS = EEPROM.read(storeRedLevDIY6);
			greenlevS = EEPROM.read(storeGreenLevDIY6);
			bluelevS = EEPROM.read(storeBlueLevDIY6);
			colorWipe(redlevS, greenlevS, bluelevS, 0);
		}
		else {
			EEPROM.write(storeRedLevDIY6, redlev);
			EEPROM.write(storeGreenLevDIY6, greenlev);
			EEPROM.write(storeBlueLevDIY6, bluelev);
		}
	}
	check_for_inputLoop();
}

void lightlev() {
	offlightlev = true;
	if (brightness >= 5) {
		if (brightness >= 45) analogWrite(3, map(5, 1, 5, 16, 255));
		else if (brightness == 35) analogWrite(3, map(4, 1, 4, 16, 128));
		else if (brightness == 25) analogWrite(3, map(3, 1, 4, 16, 128));
		else if (brightness == 15) analogWrite(3, map(2, 1, 4, 16, 128));
		else if (brightness == 5)  analogWrite(3, map(1, 1, 4, 16, 128));
	}
	else analogWrite(3, 0);
	if (brightness > 45) {
		if (brightness >= 95) analogWrite(5, map(5, 1, 5, 16, 255));
		else if (brightness == 85) analogWrite(5, map(4, 1, 4, 16, 128));
		else if (brightness == 75) analogWrite(5, map(3, 1, 4, 16, 128));
		else if (brightness == 65) analogWrite(5, map(2, 1, 4, 16, 128));
		else if (brightness == 55) analogWrite(5, map(1, 1, 4, 16, 128));
	}
	else analogWrite(5, 0);
	if (brightness > 95) {
		if (brightness >= 145) analogWrite(6, map(5, 1, 5, 16, 255));
		else if (brightness == 135) analogWrite(6, map(4, 1, 4, 16, 128));
		else if (brightness == 125) analogWrite(6, map(3, 1, 4, 16, 128));
		else if (brightness == 115) analogWrite(6, map(2, 1, 4, 16, 128));
		else if (brightness == 105) analogWrite(6, map(1, 1, 4, 16, 128));
	}
	else analogWrite(6, 0);
	if (brightness > 145) {
		if (brightness >= 195) analogWrite(9, map(5, 1, 5, 16, 255));
		else if (brightness == 185) analogWrite(9, map(4, 1, 4, 16, 128));
		else if (brightness == 175) analogWrite(9, map(3, 1, 4, 16, 128));
		else if (brightness == 165) analogWrite(9, map(2, 1, 4, 16, 128));
		else if (brightness == 155) analogWrite(9, map(1, 1, 4, 16, 128));
	}
	else analogWrite(9, 0);
	if (brightness > 195) {
		if (brightness == 255) analogWrite(10, map(6, 1, 6, 16, 255));
		else if (brightness == 245) analogWrite(10, map(5, 1, 5, 16, 128));
		else if (brightness == 235) analogWrite(10, map(4, 1, 5, 16, 128));
		else if (brightness == 225) analogWrite(10, map(3, 1, 5, 16, 128));
		else if (brightness == 215) analogWrite(10, map(2, 1, 5, 16, 128));
		else if (brightness == 205) analogWrite(10, map(1, 1, 5, 16, 128));
	}
	else analogWrite(10, 0);
}

void lightlevoff() {
	offlightlev = false;
	analogWrite(3, 0);
	analogWrite(5, 0);
	analogWrite(6, 0);
	analogWrite(9, 0);
	analogWrite(10, 0);
}

void setAllDIY(byte red, byte green, byte blue) {
	setAll(red, green, blue);
	loop_start = millis();
	check_for_inputLoop();
}

void setAll(byte red, byte green, byte blue) {
	for (int i = 0; i < ledsN; i++) {
		strip.setPixelColor(i, strip.Color(red, green, blue));
	}
	strip.show();
}