#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup() {
  // Initialiser kommunikation
  Serial.begin(9600);
  

  CARRIER_CASE = false;
  carrier.begin();
  carrier.display.fillScreen(ST77XX_BLACK); // Start med en ren skærm
}

void loop() {
carrier.Buttons.update();
  // check if a color reading is available
  
  while (! carrier.Light.colorAvailable()) {
    delay(5);

  }
  
  int r, g, b;

if (carrier.Buttons.onTouchDown(TOUCH0)) {
    carrier.Light.readColor(r, g, b); // Læs data fra RGB-sensoren
  uint32_t myCustomColor = carrier.leds.Color(r,g,b);

    carrier.display.fillScreen(ST77XX_WHITE);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.setTextSize(2);

   carrier.leds.fill(myCustomColor, 0, 5);
     carrier.leds.show();


    carrier.display.setCursor(30, 110);
    carrier.display.print("RGB: ");
    carrier.display.setCursor(30, 125);
    carrier.display.print(r);
    carrier.display.setCursor(30, 140);
    carrier.display.print(g);
    carrier.display.setCursor(30, 155);
    carrier.display.print(b);

delay(200);
}

}