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
  1.0             04/01/19     J. Ingram-Wright      Initial version
--------------------------------------------------------------------------------
EXTRA NOTES
--------------------------------------------------------------------------------
  Installation of the Adafruit_SSD1306 and Adafruit_GFX is necessary.
------------------------------------------------------------------------------*/

#include "continuous_graph.h"

ContinuousGraph::ContinuousGraph(Adafruit_SSD1306 * display, 
                                 const int kXAxisSize, const int kYAxisSize, 
                                 const int kXAxisPosition,
                                 const int kYAxisPosition,
                                 const int kValueMaximum)
  : display_(display),
    kXAxisRange_(kXAxisSize),
    kYAxisRange_(kYAxisSize),
    kXAxisPosition_(kXAxisPosition),
    kYAxisPosition_(kYAxisPosition),
    kXAxisNumberOfIntervals_(kXAxisSize),
    kYAxisNumberOfIntervals_(kYAxisSize),
    kXAxisIntervalSize_(kXAxisSize / kXAxisNumberOfIntervals_),
    kYAxisIntervalSize_(kYAxisSize / kYAxisNumberOfIntervals_),
    kValueMaximum_(kValueMaximum),
    kAdditionalMapToXAxisNecessary_(false),
    kAdditionalMapToYAxisNecessary_(false),
    firstUpdate_(true)
{
  // Initialize values_ and set all indexes to the graph baseline.
  values_ = new int[kXAxisNumberOfIntervals_];
  for (int i = 0; i < kXAxisNumberOfIntervals_; i++)
  {
    values_[i] = kYAxisPosition_ - 1;
  }
}

void ContinuousGraph::update(const int value)
{
  if (firstUpdate_)
  {
    for (int i = 0; i < kXAxisNumberOfIntervals_; i++)
    {
      updateValues(value);
    }
      
    firstUpdate_ = false;
  }
  else
  {
    updateValues(value);
  }
    
  drawGraph();
}

void ContinuousGraph::shiftValues()
{
  for (int i = 1; i < kXAxisNumberOfIntervals_; i++)
  {
      values_[i - 1] = values_[i];
  }
}

void ContinuousGraph::updateValues(const int value)
{
  shiftValues();
  values_[kXAxisNumberOfIntervals_ - 1] = map(value, 0, kValueMaximum_, 
                                              (kYAxisPosition_ - 1),
                                              (kYAxisPosition_ - kYAxisRange_));
}

void ContinuousGraph::drawGraph()
{
  // Draw Y Axis.
  display_->drawFastVLine(kXAxisPosition_, (kYAxisPosition_ - kYAxisRange_), 
                          kYAxisRange_, WHITE);
  
  // Draw Line Graph.
  for (int i = 0; i < kXAxisNumberOfIntervals_; i++)
  {
    // Set based upon whether the current index of the loop is not the last 
    // in order to draw a line joining values_[i] and the next valid index.
    int indextobechecked = (i != kXAxisNumberOfIntervals_ - 1) ? (i + 1) : i;

    // If the difference between the current values_ index and the next is 
    // larger than 1 then a line must be drawn to join the points.
    if (abs(values_[i] - values_[indextobechecked]) > 1)
    {
      // In order to avoid overlap on the line and ensure smooth curve 
      // representation a compensation value is calculated.
      int overlapcompensation = (values_[i] - values_[indextobechecked]) > 0 ? 1 : -1;

      display_->drawLine((i + kXAxisPosition_), (values_[i]),
                         (i + kXAxisPosition_),
                         ((values_[indextobechecked]) + overlapcompensation), 
                         WHITE);
    }
    else
    {
      display_->drawPixel((i + kXAxisPosition_), values_[i], WHITE);
    }
  }
}
