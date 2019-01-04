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
  The aim of this class is to provide simple continuous graphing functionality 
  for OLED screens compatible with Arduino and the Adafruit_SSD1306 library.
--------------------------------------------------------------------------------
VERSION HISTORY
--------------------------------------------------------------------------------
  VERSION         DATE         AUTHOR                DESCRIPTION
  -------         ----         ------                -----------
  1.0             02/01/19     J. Ingram-Wright      Initial version
--------------------------------------------------------------------------------
EXTRA NOTES
--------------------------------------------------------------------------------
  Installation of the Adafruit_SSD1306 and Adafruit_GFX is necessary.
------------------------------------------------------------------------------*/


#ifndef _CONTINUOUS_GRAPH_h
#define _CONTINUOUS_GRAPH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class ContinuousGraph
{
  // Functions.
  public:
    explicit ContinuousGraph(Adafruit_SSD1306 * display, 
                             const int kXAxisSize, const int kYAxisSize, 
                             const int kXAxisPosition, 
                             const int kYAxisPosition, 
                             const int kValueMaximum);

    void update(const int value);

  // Functions.
  private:
    void shiftValues();

    void updateValues(const int value);

    void drawGraph();


  // Variables and Constants.
  private:
    // Pointer to Display Instance.
    Adafruit_SSD1306 * display_;

    // Axis Properties.
    const int kXAxisRange_,             kYAxisRange_;
    const int kXAxisPosition_,          kYAxisPosition_;
    const int kXAxisNumberOfIntervals_, kYAxisNumberOfIntervals_;
    const int kXAxisIntervalSize_,      kYAxisIntervalSize_;

    // Value Properties.
    const int kValueMaximum_;

    // Mapping Flags.
    const bool kAdditionalMapToXAxisNecessary_, 
               kAdditionalMapToYAxisNecessary_;

    bool firstUpdate_;

    // Values to Display Array.
    int * values_;
};


#endif