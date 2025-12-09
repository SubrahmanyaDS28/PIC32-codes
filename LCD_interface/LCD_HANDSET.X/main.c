#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "uart2.h"
#include "pic32_config.h"
#include "initialize.h"
#include "rtcc.h"
#include "constants.h"
#include "extern.h"
#include "delay.h"
#include "lcd.h"

#define LED1 LATGbits.LATG12
#define LED2 LATGbits.LATG13
#define LED3 LATGbits.LATG14

uint8_t ReadButton(void);

char process_command(void);

FLAG COMMAND_RECEIVED;

unsigned char command[20];

unsigned int command_length = 0;


//unsigned int *load_buffer, *transfer_buffer;

unsigned int command_i;

typedef enum {
    STATE_HOME,       // Show current date/time
    STATE_MENU,       // Menu selection
} SystemState;

SystemState currentState = STATE_HOME;

int get_weekday(int d, int m, int y)
{
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int K = y % 100;
    int J = y / 100;
    int h = (d + (13*(m + 1))/5 + K + K/4 + J/4 + 5*J) % 7;
    // h = 0?Saturday, 1?Sunday, ..., 6?Friday
    int weekday = (h + 6) % 7; // Convert to 1=Monday ... 7=Sunday
    return weekday;
}

uint8_t exitMenu = 0;

// === LCD Functions (User Provided) ===
//void LCD_Init(void);
//void LCD_Command(unsigned char cmd);
//void LCD_Char(unsigned char data);
//void LCD_String(const char *str);
//void LCD_clear(void);
//void LCD_PrintInt(int num);
//void LCD_SetCursor(uint8_t row, uint8_t col);

// === Button Definitions ===
// 1=UP, 2=DOWN, 3=LEFT, 4=RIGHT, 5=ENTER, 6=BACK
uint8_t ReadButton(void);

// === Menu Structure ===
typedef struct Menu {
    const char *name;
    void (*action)(void);
    struct Menu *parent;
    struct Menu *children;
    uint8_t childCount;
} Menu;

#define MENU_SIZE(x) (sizeof(x) / sizeof(Menu))

// === Action Placeholders ===
void Action_Stars(void) {}
void Action_DeepSky(void) {}
void Action_Constellations(void) {}
void Action_NamedObj(void) {}
void Action_SolarEclipse(void) {}
void Action_LunarEclipse(void) {}
void Action_MeteorShowers(void) {}
void Action_WinterSolstice(void) {}
void Action_SummerSolstice(void) {}
void Action_SpringEquinox(void) {}
void Action_AutumnEquinox(void) {}
void Action_GuidedTour(void) {}
void Action_Glossary(void) {}
void Action_Align(void) {}

void Action_SetDate(void) {
    static char date[] = "27-10-25";
    uint8_t cursor = 0;
    uint8_t editing = 1;
    uint8_t btn;
    int day, month, year, weekday;
    char formatted[9];

    LCD_clear();
    LCD_SetCursor(0, 0);
    LCD_String("Set Date:");
    LCD_SetCursor(1, 0);
    LCD_String(date);
    LCD_Command(0x0F); // cursor blink

    while (editing) {
        btn = ReadButton();

        switch (btn) {
            case 1: // UP
                if (isdigit(date[cursor]))
                    date[cursor] = (date[cursor] == '9') ? '0' : date[cursor] + 1;
                break;

            case 2: // DOWN
                if (isdigit(date[cursor]))
                    date[cursor] = (date[cursor] == '0') ? '9' : date[cursor] - 1;
                break;

            case 3: // LEFT
                if (cursor > 0) {
                    cursor--;
                    if (date[cursor] == '-') cursor--;
                }
                break;

            case 4: // RIGHT
                if (cursor < 7) {
                    cursor++;
                    if (date[cursor] == '-') cursor++;
                }
                break;

            case 5: // ENTER ? Save
                day   = (date[0]-'0')*10 + (date[1]-'0');
                month = (date[3]-'0')*10 + (date[4]-'0');
                year  = (date[6]-'0')*10 + (date[7]-'0');

                weekday = get_weekday(day, month, 2000 + year); // optional

                sprintf(formatted, "%02d%02d%02d%02d", year, month, day, weekday);

                LCD_clear();
                LCD_SetCursor(0, 0);
                LCD_String("Date Saved:");
                LCD_SetCursor(1, 0);
                LCD_String(formatted);

                // Optional: send to RTCC
                set_date((uint32_t) strtoul(formatted, NULL, 16));

                delay_ms(1000);
                editing = 0;
                break;

            case 6: // BACK
                editing = 0;
                break;
        }

        // Update LCD
        LCD_SetCursor(1, 0);
        LCD_String(date);
        LCD_SetCursor(1, cursor);
        LCD_Command(0x0F);
    }
    LCD_Command(0x0C);
    // Return to menu
    LCD_clear();
    DisplayMenu();
}


void Action_SetTime(void) {
    static char time[] = "12:00:00";
    uint8_t cursor = 0;
    uint8_t editing = 1;
    uint8_t btn;
    int hour, min, sec;
    char formatted[9];

    LCD_clear();
    LCD_SetCursor(0, 0);
    LCD_String("Set Time:");
    LCD_SetCursor(1, 0);
    LCD_String(time);
    LCD_Command(0x0F); // cursor blink ON

    while (editing) {
        btn = ReadButton();

        switch (btn) {
            case 1: // UP
                if (isdigit(time[cursor]))
                    time[cursor] = (time[cursor] == '9') ? '0' : time[cursor] + 1;
                break;

            case 2: // DOWN
                if (isdigit(time[cursor]))
                    time[cursor] = (time[cursor] == '0') ? '9' : time[cursor] - 1;
                break;

            case 3: // LEFT
                if (cursor > 0) {
                    cursor--;
                    if (time[cursor] == ':') cursor--;
                }
                break;

            case 4: // RIGHT
                if (cursor < 7) {
                    cursor++;
                    if (time[cursor] == ':') cursor++;
                }
                break;

            case 5: // ENTER ? save time
                hour = (time[0]-'0')*10 + (time[1]-'0');
                min  = (time[3]-'0')*10 + (time[4]-'0');
                sec  = (time[6]-'0')*10 + (time[7]-'0');
                sprintf(formatted, "%02d%02d%02d00", hour, min, sec);

                LCD_clear();
                LCD_SetCursor(0, 0);
                LCD_String("Time Saved:");
                LCD_SetCursor(1, 0);
                LCD_String(formatted);

                // Optional: send to RTCC
                set_time((uint32_t) strtoul(formatted, NULL, 16));

                delay_ms(1000);
                editing = 0;
                break;

            case 6: // BACK
                editing = 0;
                break;
        }

        // Update LCD display
        LCD_SetCursor(1, 0);
        LCD_String(time);
        LCD_SetCursor(1, cursor);
        LCD_Command(0x0F);
    }
    LCD_Command(0x0C);
    // When finished ? return to menu
    LCD_clear();
    DisplayMenu();
}
void Action_SetSlewSpeed(void) {
    HandSetFreq = SLEW_FREQUENCY;
    currentState = STATE_HOME;
    exitMenu = 1;
}
void Action_SetSetSpeed(void) {
    HandSetFreq = SET_FREQUENCY;
    currentState = STATE_HOME;
    exitMenu = 1;
}
void Action_SetGuideSpeed(void) {
    HandSetFreq = GUIDE_FREQUENCY;
    currentState = STATE_HOME;
    exitMenu = 1;
}
void Action_SetFineSpeed(void) {
    HandSetFreq = FINE_GUIDE_FREQUENCY;
    currentState = STATE_HOME;
    exitMenu = 1;
}
void Action_SetLocation(void) {}
void Action_Sunrise(void) {}
void Action_Sunset(void) {}
void Action_Moonrise(void) {}
void Action_Moonset(void) {}
void Action_Planet_Mercury(void) {}
void Action_Planet_Venus(void) {}
void Action_Planet_Mars(void) {}
void Action_Planet_Jupiter(void) {}
void Action_Planet_Saturn(void) {}
void Action_Planet_Uranus(void) {}
void Action_Planet_Neptune(void) {}
void Action_Comet_Halley(void) {}

// === Menu Declarations ===
extern Menu mainMenu[];  // Forward declaration

// --- Submenus ---

Menu solarSystem[] = {
    {"Mercury", Action_Planet_Mercury, NULL, NULL, 0},
    {"Venus",   Action_Planet_Venus,   NULL, NULL, 0},
    {"Mars",    Action_Planet_Mars,    NULL, NULL, 0},
    {"Jupiter", Action_Planet_Jupiter, NULL, NULL, 0},
    {"Saturn",  Action_Planet_Saturn,  NULL, NULL, 0},
    {"Uranus",  Action_Planet_Uranus,  NULL, NULL, 0},
    {"Neptune", Action_Planet_Neptune, NULL, NULL, 0},
};
Menu speed[] = {
    {"1. Slew Speed", Action_SetSlewSpeed, NULL, NULL, 0},
    {"2. Set Speed", Action_SetSetSpeed, NULL, NULL, 0},
    {"3. Guide Speed", Action_SetGuideSpeed, NULL, NULL, 0},
    {"4. Fine G. Speed", Action_SetFineSpeed, NULL, NULL, 0},
};
Menu setup[] = {
    {"Align",    Action_Align,      NULL, NULL, 0},
    {"Date",     Action_SetDate,    NULL, NULL, 0},
    {"Time",     Action_SetTime,    NULL, NULL, 0},
    {"Motor Speed", NULL,           NULL, speed, MENU_SIZE(speed)},
    {"Location", Action_SetLocation,NULL, NULL, 0},
};
Menu utilities[] = {
    {"Timer", NULL, NULL, NULL, 0},
    {"Alarm", NULL, NULL, NULL, 0},
    {"Brightness", NULL, NULL, NULL, 0},
    {"Contrast", NULL, NULL, NULL, 0},
    {"Language", NULL, NULL, NULL, 0},
};
Menu solstices[] = {
    {"Winter Solstice", Action_WinterSolstice, NULL, NULL, 0},
    {"Summer Solstice", Action_SummerSolstice, NULL, NULL, 0},
    {"Spring Equinox",  Action_SpringEquinox,  NULL, NULL, 0},
    {"Autumn Equinox",  Action_AutumnEquinox,  NULL, NULL, 0},
};
Menu events[] = {
    {"Sunrise",  Action_Sunrise,  NULL, NULL, 0},
    {"Sunset",   Action_Sunset,   NULL, NULL, 0},
    {"Moonrise", Action_Moonrise, NULL, NULL, 0},
    {"Moonset",  Action_Moonset,  NULL, NULL, 0},
    {"Solar Eclipse",  Action_SolarEclipse, NULL, NULL, 0},
    {"Lunar Eclipse",  Action_LunarEclipse, NULL, NULL, 0},
    {"Meteor Showers", Action_MeteorShowers,NULL, NULL, 0},
};
Menu objects[] = {
    {"SolarSys",   NULL, NULL, solarSystem,MENU_SIZE(solarSystem)},
    {"Stars",          Action_Stars,          NULL, NULL, 0},
    {"Deep Sky",       Action_DeepSky,        NULL, NULL, 0},
    {"Constellations", Action_Constellations, NULL, NULL, 0},
    {"Named Objects",  Action_NamedObj,       NULL, NULL, 0},
};

// --- Main Menu ---
Menu mainMenu[] = {
    {"Object",     NULL, NULL, objects,    MENU_SIZE(objects)},
    {"Event",      NULL, NULL, events,     MENU_SIZE(events)},
    {"Setup", NULL, NULL, setup, MENU_SIZE(setup)},
    {"Utilities",  NULL, NULL, utilities, MENU_SIZE(utilities)},
    {"GuidedTour", Action_GuidedTour, NULL, NULL, 0},
    {"Glossary",   Action_Glossary,  NULL, NULL, 0},
};

// === Globals ===
Menu *currentMenu = mainMenu;
uint8_t currentIndex = 0;
uint8_t currentTop = 0; // For scrolling
uint8_t currentCount = MENU_SIZE(mainMenu);

// === Helper: Link Parents ===
void LinkParents(Menu *menu, uint8_t count, Menu *parent) {
    for (uint8_t i = 0; i < count; i++) {
        menu[i].parent = parent;
        if (menu[i].children != NULL)
            LinkParents(menu[i].children, menu[i].childCount, &menu[i]);
    }
}

// === Display ===
void DisplayMenu(void) {
    LCD_clear();
    uint8_t line = 0;

    for (uint8_t i = currentTop; i < currentCount && line < 2; i++, line++) {
        LCD_SetCursor(line, 0);
        if (i == currentIndex) LCD_String(">");
        else LCD_String(" ");

        LCD_String(currentMenu[i].name);
    }
}

// === Navigation ===
void Menu_Navigate(void)
{
    
    exitMenu = 0;
    LCD_clear();
    DisplayMenu();

    while (!exitMenu)
    {
        uint8_t btn = ReadButton();

        if (btn == 1 && currentIndex > 0) {                 // UP
            currentIndex--;
            if (currentIndex < currentTop) currentTop--;
        } 
        else if (btn == 2 && currentIndex < currentCount - 1) { // DOWN
            currentIndex++;
            if (currentIndex >= currentTop + 2) currentTop++;
        } 
        else if (btn == 5) { // ENTER
            if (currentMenu[currentIndex].children) {
                // Enter child menu
                currentMenu = currentMenu[currentIndex].children;
                currentCount = currentMenu[0].parent->childCount;
                currentIndex = 0;
                currentTop = 0;
            } 
            else if (currentMenu[currentIndex].action) {
                LCD_clear();
                LCD_SetCursor(0, 0);
                LCD_String("Running:");
                delay_ms(1000);
                LCD_SetCursor(1, 0);
                LCD_String(currentMenu[currentIndex].name);
                currentMenu[currentIndex].action();
            }
        } 
        else if (btn == 6) { // BACK
            if (currentMenu->parent) {
                // Go up one level
                currentMenu = currentMenu->parent->parent ? currentMenu->parent : mainMenu;
                currentCount = currentMenu->childCount ? currentMenu->childCount : MENU_SIZE(mainMenu);
                currentIndex = 0;
                currentTop = 0;
            } else {
                // Exit completely
                LCD_clear();
                LCD_SetCursor(0,0);
                LCD_String("Exiting Menu...");
                delay_ms(2000);
                LCD_clear();
                currentState = STATE_HOME;
                exitMenu = 1; // <-- exit condition
            }
        }

        DisplayMenu();
    }
}



// === Initialization ===
void Menu_Init(void) {
    LCD_Init();
    LinkParents(mainMenu, MENU_SIZE(mainMenu), NULL);
    DisplayMenu();
}






// === Main ===
void main(void) {
    
    Init_SYS(NULL);
    Menu_Init();

    LCD_clear();
    LCD_SetCursor(0,0);
    LCD_String("Welcome!");
    LCD_SetCursor(1,0);
    LCD_String("Starting...");
    delay_ms(3000);
    
    Action_SetTime();
    Action_SetDate();
    
    while (1) {
        
        uint8_t btn = ReadButton();
        
        switch (currentState)
        {
            case STATE_HOME:
                Read_RTCC_DateTime_LCD();
                direction_enabled = 1;
                
                if (btn == 5) currentState = STATE_MENU;
                delay_ms(100);
                
                break;
                
            case STATE_MENU:
                direction_enabled = 0;
                
                Menu_Navigate();
                delay_ms(100);
                
                break;
                
        }
    }
}

char process_command(void) {
    unsigned int i = 0;
    char temp;
    
      switch (command[0]) {
            
        case 'a':
            if (command_length != 2)
                return NAK;
            else {
                int value = 0;
                for (i = 1; command[i] != '\0'; i++) {
					temp = command[i] - '0';
                    value = (value  * 10) + temp;                     
                }
                
                set_alarm_time(value);
            }
            
            break;
            
          case 's':
              if (command_length != 9)
                return NAK;
            else {
                  
                char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t alarm_time;
                alarm_time = (uint32_t) strtoul(hex_str, NULL, 16);
                
                set_alarm_to_particular_time(alarm_time);
                
            }
            
            break;
            
          case 't':
              if (command_length != 9)
                return NAK;
              else{
                  char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t new_time;
                new_time = (uint32_t) strtoul(hex_str, NULL, 16);
                
                set_time(new_time);
              }
              break;
              
          case 'd':
              if (command_length != 9)
                return NAK;
              else{
                  char hex_str[9];  // 8 chars for 32-bit hex + null
                strncpy(hex_str, &command[1], 8); // skip '*' and 'a'
                hex_str[8] = '\0';                  // null-terminate
  
                uint32_t new_date;
                new_date = (uint32_t) strtoul(hex_str, NULL, 16);
                
                set_date(new_date);
              }
              break;
        }
      return ACK;
    }

//uint8_t ReadButton(void)
//{
//    if (!BTN_UP)    { delay_ms(150); while(!BTN_UP); return 1; }
//    if (!BTN_DOWN)  { delay_ms(150); while(!BTN_DOWN); return 2; }
//    if (!BTN_LEFT)  { delay_ms(150); while(!BTN_LEFT); return 3; }
//    if (!BTN_RIGHT) { delay_ms(150); while(!BTN_RIGHT); return 4; }
//    if (!BTN_ENTER) { delay_ms(150); while(!BTN_ENTER); return 5; }
//    if (!BTN_RESET) { delay_ms(150); while(!BTN_RESET); return 6; }
//    return 0; 
//}
uint8_t ReadButton(void)
{
    delay_ms(100);
    static uint8_t lastState = 0;
    uint8_t current = 0;

    if (!BTN_UP) current = 2;
    else if (!BTN_DOWN) current = 1;
    else if (!BTN_LEFT) current = 3;
    else if (!BTN_RIGHT) current = 4;
    else if (!BTN_ENTER) current = 5;
    else if (!BTN_RESET) current = 6;
    else current = 0;

    uint8_t result = 0;
    if (current != 0 && lastState == 0)
        result = current; // new press detected

    lastState = current;
    return result;
}