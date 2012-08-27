/* ButterworthLowPass2.h - Butterworth Second Order Low Pass Filter                               
 Copyright 2012, Adam Cooper
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * ButterworthLowPass2 is free software: you can redistribute it and/or modify     *
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
#ifndef BUTTERWORTH_LOW_PASS2_H
#define BUTTERWORTH_LOW_PASS2_H

#include "Arduino.h"

/*! A Second Order Butterworth Filter, which may be used to produce any even-order filter by cascading a
  series of second order filters (see the constructors).\n
  Butterworth Filters are principally-defined by a cut-off frequency at which attenuation is around -3dB and after which
 signal attenuation is 20N dB/decade (N=2 for second order). They use a recursive equation which takes account of all past values
 (i.e. infinite impulse response) and have a phase shift that varies with frequency (hence there is some distortion).
  They have a maximally flat response in the pass-band, a better pulse response than Chebyshev filters
  and a better rate of attenuation than Bessel filters. Large transients are not filtered, though.
  The flat response means that signals in the pass band do not recieve frequency-dependent attenuation.\n
  See http://en.wikipedia.org/wiki/Butterworth_filter \n
 To use: create an instance of the filter and submit new readings using update().
 Readings should be sampled at regular (i.e. equal) time intervals.
 @brief Second Order Butterworth Filter */
class ButterworthLowPass2{
public:
  /*! Create the filter with specified parameters. This constructor is for the construction of a stand-alone
  second order filter. See alternatives for use in creating any even-order filter.
  This calculates the coefficients to be used, which are accessible using getCoefficients().
   @param fRatio The ratio of the sampling frequency (each sample is submitted to update()) over the desired cut-off frequency.
   fRatio must be greater than 2, typically much greater
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings.
   Burn-in is probably better than a zero initialisation but may be worse than initialisation using getState() and setState().
   Since the effect of initialisation is present in the output for some time afterwards, a period of stablisation is useful.
   See http://www.kwon3d.com/theory/filtering/init.html */
  ButterworthLowPass2(float fRatio, boolean burnIn);
  
  /*! Create a second order filter for chaining in order to create an even-order filter.
  Otherwise than this, behaviour is exactly as the plain 2nd order filter.
  Chain filters together with all values of k from 0 to (N/2 - 1), where N is the overall order.
  @param fRatio The ratio of the sampling frequency over the desired cut-off frequency.
  @param k The elementary filter number (i.e. which second-order sub-component of the overall filter this is), a value from from 0 to (N/2 - 1)
  @param N The overall order of the filter of which this is an element
  @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading. */  
  ButterworthLowPass2(float fRatio, int k, int N, boolean burnIn);

  /*! Submit a new measurement to the filter.\n
  Readings should be sampled at regular (i.e. equal) time intervals.
   @param newVal The new value.
   @returns The filter output. */
  float updateF(int newVal);

/* Get the coefficients for the Butterworth Filter in use.
The equation is out[i] = a0*in[i] + a1*in[i-1] + a2*in[i-2] - b1*out[i-1] - b2*out[i-2]
where in[1] = gain * sample value (newVal as submitted to updateF()
@param[out] coefficients An array where the elements are (in order) gain, a0, a1, a2, b1, b2 */
  void getCoefficients(float coefficients[]);
  
  /* Print a formatted version of the coefficients to Serial */
  void printCoefficients();
 
 /* Get the current state of the filter, determined by the input/output history used in the recursive equation.
 Use this with setState() to initialise the filter in a more realistic way than achieved using burnin=true in the constructor.
 Typical use: run the system and filter for a period of time to establish a stable and realistic baseline state; use setState() to
 initialise the filter at subsequent start-ups.
@param[out] state an array containing in[i-1], in[i-2], out[i-1], out[i-2], where "i" is the next sample/frame */
  void getState(float state[]); 
  
  /* Set the filter state, as defined by historical input/output vales used in the recursive equation.
  See getState().
  @param state an array obtained by getState(). */
  void setState(float state[]);
  

private:
  //constructor parameters
  boolean _burnIn;
  float _gain;
  float _a0, _a1, _a2, _b1, _b2;
  boolean _updated;//has the filter received any data yet
  int _in1, _in2;//_in2 is input for i-2
  float _out1, _out2;//_out2 is output for i-2
  
  void calculateCoefficients(float fRatio, int k, int N);//sets the member variables gain, a0,a1,a2,b1,b2. Used by both constructors
};

#endif

