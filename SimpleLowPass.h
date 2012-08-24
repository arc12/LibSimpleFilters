/* SimpleLowPass.h - Infinite Impulse Exponential Moving Average                               
 Copyright 2012, Adam Cooper
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * SimpleLowPass is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU Lesser General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Lesser General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Alternative licenses may be available. Please contact Adam Cooper if the  *
 * GNU LGPL is problematical for you.                                        *
 ****************************************************************************/
#ifndef SIMPLE_LOW_PASS_H
#define SIMPLE_LOW_PASS_H

#include "Arduino.h"

/*!  This filter calculates its output based on the previous output and the update value.
output[t] = alpha*input + (1-alpha)*output[t-1], where alpha is the smoothing factor and t is the time-step.
Small values of alpha (<<0.5) make for slow-moving output.
 To use: create an instance of the filter and submit new readings using update().
 Readings should be sampled at regular (i.e. equal) time intervals.
 This is a an infinite-impulse-response (IIR) single-pole lowpass filter, see http://en.wikipedia.org/wiki/Low-pass_filter
 @brief  An infinite length moving average with exponential weighting.
 @todo a version using fixed-point integer arithmetic. */
class SimpleLowPass{
public:
  /*! Create the filter with specified parameters.
  @param alpha The smoothing factor (range 0<=alpha<=1).
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  SimpleLowPass(float alpha, boolean burnIn);

  /** @name Active
   Methods to interact with an active filter. */
  //!@{
  /*! Submit a new measurement to the filter.
   @param newVal The new value.
   @returns The filter output. */
  float updateF(int newVal);
  //!@}  


private:
  //constructor parameters
  boolean _burnIn;
  float _alpha;
  
  boolean _updated;
  float _lastOutput;

};

#endif
