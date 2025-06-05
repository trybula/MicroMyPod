#include <sys/_stdint.h>
#ifndef DISPLAY_FUNC_H
  #define DISPLAY_FUNC_H

  #include "structs.h"
  #include "config.h"
  #include <vector>
  #include <U8g2lib.h>
  #define ICON_OFFSET 5 //offset of an icon relative to the text in menu


  extern uint8_t element_index;
  extern MENU * current_menu;
  extern MENU DirSelect;
  //extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
  extern std::vector<MENUITEM> Mp3MenuItems;

  uint STRING_WIDTH(String S){
    return u8g2.getStrWidth(S.c_str());
  } 

  //draws a string centered on the screen
  void draw_centered_string(uint y, const char* S){
    uint x = u8g2.getStrWidth(S);
    uint display_x = u8g2.getDisplayWidth();
    if(x>display_x)
      u8g2.drawStr(0,y,S);
    else
      u8g2.drawStr( (display_x-x)/2 , y, S );
  }

  void draw_reduced_string(uint x, uint y, String S, uint maxchar){
    if(current_menu == &DirSelect){
      if(S == "/")
        S = "root";
      else if(S == Mp3MenuItems[2].title)
        S = "Play this album";
    }
    if(S.length()<=maxchar)
      u8g2.drawStr(x, y, S.c_str());
    else{
      String reduced =  S.substring(S.length()-maxchar);
      reduced[0] = '.';
      reduced[2] = '.';
      reduced[1] = '.';
      u8g2.drawStr(x, y, reduced.c_str());
    }
  }



  void display_current_menu(){ 
    static const unsigned char image_WARNING_bits[] = {0xff,0xff,0xff,0x07,0x1f,0x00,0x00,0x07,0xef,0xff,0xff,0x06,0xef,0xfb,0xfb,0x06,0xe3,0xf7,0xfd,0x06,0xfd,0xef,0xfe,0x06,0xfd,0x5f,0xff,0x06,0xfd,0xbf,0xff,0x06,0xfd,0x5f,0xff,0x06,0xfd,0xef,0xfe,0x06,0xe3,0xf7,0xfd,0x06,0xef,0xfb,0xfb,0x06,0xef,0xff,0xff,0x06,0x1f,0x00,0x00,0x07,0xff,0xff,0xff,0x07};
    
    uint8_t style = current_menu->style;
    

    switch (style){
      default:
        {
          static const unsigned char image_arrow_curved_left_up_bits[] U8X8_PROGMEM = {0x04,0x0e,0x1f,0x04,0x0c,0x08,0x10};
          static const unsigned char image_arrow_curved_left_down_bits[] U8X8_PROGMEM = {0x10,0x08,0x0c,0x04,0x1f,0x0e,0x04};
          static const unsigned char image_music_radio_bits[] U8X8_PROGMEM = {0x00,0x18,0x00,0x06,0x80,0x01,0x60,0x00,0x18,0x00,0x06,0x00,0xfe,0x7f,0x39,0x80,0x55,0xbe,0x83,0xa2,0xd7,0xbe,0x83,0x80,0x55,0xaa,0x39,0x80,0xfe,0x7f,0x00,0x00};
          static const unsigned char image_Ok_btn_bits[] U8X8_PROGMEM = {0x7c,0x00,0x82,0x00,0x39,0x01,0x7d,0x01,0x7d,0x01,0x7d,0x01,0x39,0x01,0x82,0x00,0x7c,0x00};
          static const unsigned char image_cross_small_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x86,0x01,0xcc,0x00,0x78,0x00,0x30,0x00,0x78,0x00,0xcc,0x00,0x86,0x01,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00};
          u8g2.clearBuffer();
          u8g2.setFontMode(1);
          u8g2.setBitmapMode(1);

          u8g2.drawRFrame(3, 2, 122, 60, 9);//FRAME AROUND

          //-----------upper select
          u8g2.setDrawColor(1);
          if(element_index != 0){
            u8g2.drawXBMP(12, 8, 5, 7, image_arrow_curved_left_up_bits);
            u8g2.setFont(u8g2_font_5x8_tr);
            u8g2.drawStr(21, 15, ((*current_menu->items)[element_index-1].title).c_str());
          }
          //else
            //u8g2.drawXBMP(11, 3, 10, 16, image_cross_small_bits);

          //--------------currently selected
          u8g2.setDrawColor(1);
          u8g2.drawBox(3, 20, 122, 24);
          u8g2.setDrawColor(2);
          u8g2.setFont(u8g2_font_t0_17_tr);
          u8g2.drawStr(30, 38,  ((*current_menu->items)[element_index].title).c_str());
          uint8_t strwidth = STRING_WIDTH( (*current_menu->items)[element_index].title);
          u8g2.drawXBMP(30+strwidth+ICON_OFFSET, 23,  (*current_menu->items)[element_index].icon_size[0], (*current_menu->items)[element_index].icon_size[1], (*current_menu->items)[element_index].icon);
          u8g2.drawXBMP(12, 28, 9, 9, image_Ok_btn_bits);

          //----------------lower select
          u8g2.setDrawColor(1);
          if(element_index != current_menu->numItems -1){
            u8g2.setFont(u8g2_font_5x8_tr);
            u8g2.drawXBMP(12, 49, 5, 7, image_arrow_curved_left_down_bits);
            u8g2.drawStr(21, 56,  ((*current_menu->items)[element_index+1].title).c_str());
          }
          //else
            //u8g2.drawXBMP(11, 44, 10, 16, image_cross_small_bits);

        }
      break;
      case 0:
      {
          static const unsigned char Dot_empty[] U8X8_PROGMEM = {0x06,0x09,0x09,0x06};
          static const unsigned char Dot_full[] U8X8_PROGMEM = {0x06,0x0f,0x0f,0x06};
          u8g2.clearBuffer();
          u8g2.setFontMode(1);
          u8g2.setBitmapMode(1);

          // Frame
          u8g2.drawRFrame(2, 2, 124, 60, 9);

          // Title
          u8g2.setFont(u8g2_font_t0_15b_tr);
          uint8_t str_x = (u8g2.getDisplayWidth() - STRING_WIDTH((*current_menu->items)[element_index].title) )/2; 
          u8g2.drawStr(str_x, 52, ((*current_menu->items)[element_index].title).c_str());

          // Page status bar
          
          uint8_t ball_x = (u8g2.getDisplayWidth() - current_menu->numItems * 8)/2;
          uint8_t ball_y = 55;
          for(uint8_t i=0;i<current_menu->numItems;i++){
            if(i == element_index){
              u8g2.drawXBMP(ball_x, ball_y, 4, 4, Dot_full);
            }
            else{
              u8g2.drawXBMP(ball_x, ball_y, 4, 4, Dot_empty);
            }
            ball_x +=8;
          }

          // Radio_icon
          uint8_t bmp_y = (37 - (*current_menu->items)[element_index].icon_size[1])/2 + 3;
          uint8_t bmp_x = (u8g2.getDisplayWidth() - (*current_menu->items)[element_index].icon_size[0])/2;
          u8g2.drawXBMP(bmp_x, bmp_y, (*current_menu->items)[element_index].icon_size[0], (*current_menu->items)[element_index].icon_size[1], (*current_menu->items)[element_index].icon);

      }
      break;
      case 2:
      {
        uint8_t local_el_index = element_index % 5; //"local" one is always equal global element_index, unless global one is bigger than 4, and all elements wont fit on the screen. then it is used to show correct elements on screen.
        uint8_t local_page_index = element_index / 5;

        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);

        // header
        u8g2.setFont(u8g2_font_6x10_tr);
        if( //if text would overlap the header,  header is hidden
          (current_menu->numItems>=1 + local_page_index*5) //there need to be any item to show
          && 
          (STRING_WIDTH((*current_menu->items)[0+local_page_index*5].title) <=  u8g2.getDisplayWidth() - STRING_WIDTH(" "+(current_menu->title)+" ")-9)//comparing strings sizes
          ){ 
          u8g2.drawLine(u8g2.getDisplayWidth() - STRING_WIDTH(" "+(current_menu->title)+" "), 9, u8g2.getDisplayWidth(), 9);
          u8g2.drawLine(u8g2.getDisplayWidth() - STRING_WIDTH(" "+(current_menu->title)+" "), 9, u8g2.getDisplayWidth() - STRING_WIDTH(" "+(current_menu->title)+" ")-9, 0);
          u8g2.drawStr(u8g2.getDisplayWidth() - STRING_WIDTH(" "+(current_menu->title)+" "), 8, (" "+(current_menu->title)+" ").c_str());
        }

        // texts
        for(uint8_t i=1;i<=5;i++){
          if(current_menu->numItems>=i + local_page_index*5)
            draw_reduced_string(8, i*13-3, ((*current_menu->items)[i-1+local_page_index*5].title),18);
        }


        // Selected
        if((*current_menu->items)[element_index].action != &DONOTSELECT){
          u8g2.setDrawColor(2);
          u8g2.drawBox(3, 2+local_el_index*13, STRING_WIDTH(" "+ (*current_menu->items)[element_index].title + " "), 10);
        }
        



      }
      break;

    }
    float vol = get_vsys_voltage();
    if(vol <=3.4){
      u8g2.setFontMode(0);
      u8g2.setBitmapMode(1);
      u8g2.setDrawColor(1);
      u8g2.drawXBM(101, 0, 27, 15, image_WARNING_bits);
    }
    u8g2.sendBuffer();
    
  }


  void thinking_rn(void) {
    static const unsigned char image_hour_glass_75_bits[] = {0xff,0x07,0x02,0x02,0x02,0x02,0x8a,0x02,0xfa,0x02,0x74,0x01,0xa8,0x00,0x50,0x00,0x50,0x00,0x88,0x00,0x24,0x01,0x22,0x02,0x72,0x02,0xfa,0x02,0xfe,0x03,0xff,0x07};
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawXBM(59, 24, 11, 16, image_hour_glass_75_bits);

    u8g2.setFont(u8g2_font_t0_11_tr);
    u8g2.drawStr(37, 56, "RIGHT NOW");

    u8g2.drawStr(40, 16, "THINKING");

    u8g2.sendBuffer();
  }

  void draw_value_with_bar(String name, float value, float max_value,String unit){
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.drawFrame(23, 31, 82, 12);

    u8g2.setFont(u8g2_font_t0_11_tr);
    draw_centered_string(24, name.c_str());
    //u8g2.drawStr(46, 24, name.c_str());

    u8g2.drawBox(25, 33, round(78*value/max_value), 8);

    u8g2.setFont(u8g2_font_4x6_tr);
    draw_centered_string(52, ((String(value)) + unit).c_str());

    u8g2.sendBuffer();
  }

  

#endif