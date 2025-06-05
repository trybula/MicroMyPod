#ifndef CONFIG_H
  #define CONFIG_H

  //buttons
  #define NEXT_BTN 5
  #define PREV_BTN 7
  #define UP_BTN 4
  #define DOWN_BTN 6
  #define ENTER_BTN 9
  #define POWER_BTN 13
  #define WAKEUP_GPIO GPIO_NUM_13 //those two must match

  //wifi file
  #define WIFI_PASS_FILE "/wifi-conf.csv"
  #define WIFI_PASS_FILE_DELIMITER '\t'

  //display
  #define DISPLAY_SDA 37
  #define DISPLAY_SCL 38
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


  //sd
  #define SD_CS_PIN 41
  #define SPI_SPEED SD_SCK_MHZ(20)
  #define SD_MISO 42
  #define SD_SCK 1
  #define SD_MOSI 2

  //DAC
  #define DAC_LCK 35
  #define DAC_BCK 36
  #define DAC_DIN 34
  
  //pin to which is connected the mosfet to cutoff the power for any periphals
  #define POWER_PIN 8

  //display refresh interval (in playing mode)
  const unsigned long og_interval = 500;

  //-----------few functions -----------

  void DONOTSELECT(void *){};
  #define NUMELEMENTS(X) (sizeof(X) / sizeof(X[0]))

  //returns a voltage red from the Vsys pin
  float get_vsys_voltage(){
    float voltage = 3.3;
    return voltage;
  }

#endif