#include <sys/_stdint.h>
#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include "config.h"
#include <Arduino.h>
#include <U8g2lib.h>

//very important structure. Basically, together with MENU, it handles all menu navigation.
struct MENUITEM 
{
  String title;                // item title
  void (*action)(void * ptr);  // function to execute
  void *param;                // parameter for function to execute
  struct MENU *subMenu;       // submenu for this menu item to open
  const unsigned char *icon; //it is a pointer, so it can point to the array making it dynamic declaration ;)
  const uint8_t icon_size[2]; //dimensions of the icons
};

//very important structure. Basically, together with MENUITEM, it handles all menu navigation.
struct MENU
{
  String title;              // menu title
  std::vector<MENUITEM>* items;          // menu items
  int numItems;             // number of menu items
  struct MENU *parentMenu;  // parent menu of this menu
  uint8_t style;
};
//pointers to subMenu and parentMenu in those structs allow to navigate through menus without the need to track on which menu we are right now


//type for the int variables that will be needed to be changed later (ex. volume)
struct INT_VARIABLE{ 
  String name;
  int value;
  int min_value;
  int max_value;
  uint8_t step;
};

//struct made to make menaging wifi networks easier
struct WIFI_INFO{
  String SSID;
  String PASS;
  bool is_pass;
  int strength;
};


//class made to make managing many scrolling texts easier
class ScrollableText{
  public:
    ScrollableText(String text,uint8_t y, U8G2 &display, const uint8_t *font, uint8_t step = 5)
      : u8g2(display), text(text), y(y), step(step), font(font) // Initialize all the values here
    {
      this->SetText(text);
    }
    void process(){
      u8g2.setFont(font);
      if(scrolling){
        x+=step;
        if(x>x_diff)
          x = 0;
        u8g2.drawStr(-x,y,text.c_str());
      }
      else{
        uint8_t display_x = u8g2.getDisplayWidth();
        uint8_t str_x = u8g2.getStrWidth(text.c_str());
        u8g2.drawStr( (display_x-str_x)/2 , y, text.c_str() );
      }
    }
    void SetText(String NewText){
      u8g2.setFont(font);
      text = NewText;
      x = 0;
      x_diff = -min( (u8g2.getDisplayWidth() - u8g2.getStrWidth(text.c_str())) , 0);
      if(x_diff == 0){
        scrolling = false;
      }
      else{
        scrolling = true;
        text = "  " + text + "  ";
        x_diff += u8g2.getStrWidth("    ");
      }
    }


  private:
    bool scrolling;
    const uint8_t *font;
    U8G2 &u8g2;
    //how much px text is too long to fit
    uint x_diff = 0;

    //current scrolling position
    uint x = 0;

    uint8_t y = 0;

    //text to be showed
    String text = "";

    //how many pixels to move the text
    uint8_t step = 5;
  
};

//metadata storage (in char arrays)
struct {
  String Title;
  String Album;
  String Artist;
  bool changed;
}Meta;

#endif