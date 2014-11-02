/* SimpleLowPass.h - Infinite Impulse Exponential Moving Average                               
 Copyright 2012, Adam Cooper */
 
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
output[i] = alpha*input[i] + (1-alpha)*output[i-1], where alpha is the smoothing factor and i is the sample/frame (i-1 = previous).
Small values of alpha (<<0.5) make for slow-moving output. 
The time constant, "RC" = sample period * ((1-alpha)/alpha)
RC = time for a step change to reach 63.2% of asymptotic value.
Cutoff frequency = 1/(2*pi*RC), hence
f_sampling/f_cutoff = 2*pi*(1-alpha)/alpha
So a "cutoff frequency" of 1/10th the sample rate requires alpha=0.385\n
 This is a an infinite-impulse-response (IIR) single-pole lowpass filter, see http://en.wikipedia.org/wiki/Low-pass_filter 
 and also http://helpful.knobs-dials.com/index.php/Low-pass_filter for more introductory comments. \n
 To use: create an instance of the filter and submit new readings using update().
 @brief  An infinite length moving average with exponential weighting.
 @todo a version using fixed-point integer arithmetic. */
class SimpleLowPass{
public:
  /*! Create the filter with specified parameters.
  @param alpha The smoothing factor (range 0<=alpha<=1). See calcAlpha(). NB this is different to ButterworthLowPass2, which uses the fRatio directly.
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  SimpleLowPass(float alpha, boolean burnIn);
  
  /*! Calculate the alpha value for a desired "cutoff" frequency.
  See the constructor.
   @param fRatio The ratio of the sampling frequency (each sample is submitted to update()) over the desired cut-off frequency.*/
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

};

#endif
