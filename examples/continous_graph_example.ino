/*-----------------------------------------------------------------------------
                                __  _                             
              _________  ____  / /_(_)___  __  ______  __  _______
             / ___/ __ \/ __ \/ __/ / __ \/ / / / __ \/ / / / ___/
            / /__/ /_/ / / / / /_/ / / / / /_/ / /_/ / /_/ (__  ) 
            \___/\____/_/ /_/\__/_/_/ /_/\__,_/\____/\__,_/____/  
                        ____ __________ _____  / /_               
                       / __ `/ ___/ __ `/ __ \/ __ \              
                      / /_/ / /  / /_/ / /_/ / / / /              
                      \__, /_/   \__,_/ .___/_/ /_/               
                     /____/          /_/              
            
--------------------------------------------------------------------------------
OVERVIEW
--------------------------------------------------------------------------------
  The purpose of this file is to provide a working example of an instance of
  the ContinuousGraph class.
--------------------------------------------------------------------------------
VERSION HISTORY
--------------------------------------------------------------------------------
  VERSION         DATE         AUTHOR                DESCRIPTION
  -------         ----         ------                -----------
  1.0             024/01/19     J. Ingram-Wright      Initial version
--------------------------------------------------------------------------------
EXTRA NOTES
--------------------------------------------------------------------------------
  N/A
------------------------------------------------------------------------------*/


#include <continuous_graph.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create an instance of a ContinuousGraph to be drawn on the display with the
// following properties:
//   - Width: 100px.
//   - Height: 50px.
//   - X-Position: 15.
//   - Y-Position: 57.
//   - Max Input Value: 100.
ContinuousGraph graph(&display, 100, 50, 14, 57, 100);

// For display update timing.
const int   kUpdateInterval = 20;
signed long previousmillis = 0;

// Value to be plotted.
int graphvalue = 0;
int incrementvalue = 1;

void setup()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (true); //Display not connected. Don't proceed, loop forever.
  }

  display.clearDisplay();
  display.display();
}

void updateGraphValue()
{
      if (graphvalue >= 100)
    {
      graphvalue = 0;

      if (incrementvalue >= 10)
      {
        incrementvalue = 1;
      }
      else
      {
        incrementvalue++;
      }
    }
    else
    {
      if ((graphvalue + incrementvalue) > 100)
      {
        graphvalue = 100;
      }
      else
      {
        graphvalue += incrementvalue;
      }
    }
}

void loop()
{
  unsigned long currentmillis = millis();

  if (currentmillis - previousmillis >= kUpdateInterval)
  {
    previousmillis = currentmillis;

    display.clearDisplay();
    graph.update(graphvalue);
    display.display();

    updateGraphValue();
  }
}