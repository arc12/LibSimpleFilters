/* SimpleHighPass.h - Discrete Time High Pass Filter                               
 Copyright 2012, Adam Cooper */
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * SimpleHighPass is free software: you can redistribute it and/or modify     *
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
#ifndef SIMPLE_HIGH_PASS_H
#define SIMPLE_HIGH_PASS_H

#include "Arduino.h"

/*!  This filter calculates its output based on the previous output, previous input and the update value.
output[t] = alpha*(input[t]-input[t-1]) + alpha*output[t-1], where alpha is the impulse factor and t is the time-step.
Small values of alpha (<<0.5) cause only high frequencies (rapid, large swings in input) to give an output far from 0.
Large values of alpha mean the output only settles to zero after a considerable number of unchanging samples.
 Readings should be sampled at regular (i.e. equal) time intervals.\n
 See http://en.wikipedia.org/wiki/High-pass_filter \n
 To use: create an instance of the filter and submit new readings using update().
 @brief  An infinite length moving average with exponential weighting.
 @todo a version using fixed-point integer arithmetic. */
class SimpleHighPass{
public:
  /*! Create the filter with specified parameters.
  @param alpha The impulse factor (range 0<=alpha<=1). See calcAlpha().
   @param burnIn Whether to initialise the filter on first reading such that the output = zero (as if input had been constant prior to this).
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  SimpleHighPass(float alpha, boolean burnIn);
  
  /*! Calculate the alpha value for a desired "corner" frequency.
   @param fRatio The ratio of the sampling frequency (each sample is submitted to update()) over the desired corner frequency.*/
  float calcAlpha(float fRatio);

  /*! Submit a new measurement to the filter.\n
  Readings should be sampled at regular (i.e. equal) time intervals.
   @param newVal The new value.
   @returns The filter output. */
  float updateF(int newVal);

private:
  //constructor parameters
  boolean _burnIn;
  float _alpha;
  
  boolean _updated;
  float _lastOutput;
  float _lastInput;

};

#endif
