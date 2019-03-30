#include <IRremote.h>
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
char command;
boolean understood = false;
long lastButton;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.print("0x");
    //Serial.println(results.value, HEX);

    if (results.value == 0xFFFFFFFF) {
      results.value = lastButton;
    } else {
      lastButton = results.value;
    }

    understood = true;
    switch (results.value) {
      case 0xFF02FD: //ONOFF
        command = 'A';
        break;
      case 0xFF827D: //SKIP
        command = 'B';
        break;
      case 0xFF3AC5: //BRIGHT_UP
        command = 'D';
        break;
      case 0xFFBA45: //BRIGHT_DOWN
        command = 'C';
        break;
      case 0xFF1AE5: //R1
        command = 'E';
        break;
      case 0xFF9A65: //G1
        command = 'F';
        break;
      case 0xFFA25D: //B1
        command = 'G';
        break;
      case 0xFF22DD: //W1
        command = 'H';
        break;
      case 0xFF12ED: //W2
        command = 'I';
        break;
      case 0xFF926D: //B2
        command = 'J';
        break;
      case 0xFFAA55: //G2
        command = 'K';
        break;
      case 0xFF2AD5: //R2
        command = 'L';
        break;
      case 0xFF0AF5: //R3
        command = 'M';
        break;
      case 0xFF8A75: //G3
        command = 'N';
        break;
      case 0xFFB24D: //B3
        command = 'O';
        break;
      case 0xFF32CD: //W3
        command = 'P';
        break;
      case 0xFFF807: //W4
        command = 'Q';
        break;
      case 0xFF7887: //B4
        command = 'R';
        break;
      case 0xFFB847: //G4
        command = 'S';
        break;
      case 0xFF38C7: //R4
        command = 'T';
        break;
      case 0xFF18E7: //R5
        command = 'U';
        break;
      case 0xFF9867: //G5
        command = 'V';
        break;
      case 0xFF58A7: //B5
        command = 'W';
        break;
      case 0xFFD827: //W5
        command = 'X';
        break;
      case 0xFF609F: //FADE3
        command = 'Y';
        break;
      case 0xFFE01F: //FADE7
        command = 'Z';
        break;
      case 0xFF28D7: //RED_UP
        command = '1';
        break;
      case 0xFF08F7: //RED_DOWN
        command = '2';
        break;
      case 0xFFA857: //GREEN_UP
        command = '3';
        break;
      case 0xFF8877: //GREEN_DOWN
        command = '4';
        break;
      case 0xFF6897: //BLUE_UP
        command = '5';
        break;
      case 0xFF48B7: //BLUE_DOWN
        command = '6';
        break;
      case 0xFF30CF: //DIY1
        command = '7';
        break;
      case 0xFFB04F: //DIY2
        command = '8';
        break;
      case 0xFF708F: //DIY3
        command = '9';
        break;
      case 0xFF10EF: //DIY4
        command = '!';
        break;
      case 0xFF906F: //DIY5
        command = '@';
        break;
      case 0xFF50AF: //DIY6
        command = '#';
        break;
      case 0xFFF00F: //AUTO
        command = '$';
        break;
      case 0xFFD02F: //FLASH
        command = '%';
        break;
      case 0xFF20DF: //JUMP3
        command = '^';
        break;
      case 0xFFA05F: //JUMP7
        command = '&';
        break;
      case 0xFFE817: //QUICK
        command = '*';
        break;
      case 0xFFC837: //SLOW
        command = '(';
        break;
      default:
        understood = false;
    }
    if (understood) Serial.write(command);
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    irrecv.resume(); // Receive the next value
  }
}
