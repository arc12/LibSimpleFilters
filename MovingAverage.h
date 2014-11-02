/* MovingAverage.h - Moving Average Smoothing                               
 Copyright 2012, Adam Cooper */
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * MovingAverage is free software: you can redistribute it and/or modify     *
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
 ****************************************************************************/
#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H


#include "Arduino.h"

#define MOVING_AVERAGE_MAX_LEN 25 //!< Maximum number of samples, as specified by the length parameter in the constructor

/*!  This filter calculates the average of a set number of previous values.
This has a very slow-moving output if a long length is specified.
 To use: create an instance of the filter and submit new readings using update().
 Readings should be sampled at regular (i.e. equal) time intervals.
 @brief  A finite length moving average without weighting. */
class MovingAverage{
public:
  /*! Create the filter with specified parameters.
   @param length The number of samples to take into account with a maximum specified by MOVING_AVERAGE_MAX_LEN.
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  MovingAverage(int length, boolean burnIn);

  /*! Submit a new measurement to the filter.\n
  Readings should be sampled at regular (i.e. equal) time intervals.
   @param newVal The new value.
   @returns The filter output. */
  int update(int newVal);

  /*! Same as the integer version except that the average is computed using 4 byte floating point arithmetic. */
  float updateF(int newVal);

  /*! Get the previously-submitted values.
  @param[out] values A buffer of length specified by the length parameter in the constructor. */
  void getHistory(int values[]);
  /*! What was the last index used in the returned buffer from getHistory()?
  @returns The index to the value submitted by the last update() */
  int getLastIndex();

private:
  //constructor parameters
  boolean _burnIn;
  int _length;

  boolean _updated;//has the filter received any data yet
  int _values[MOVING_AVERAGE_MAX_LEN];
  int _index;// pointer into _values[]
  long _sum;//sum of values[]
  int _correction;// _length/2, gets added in to compensate for integer division
  
  //common code used by both update() methods
  void accumulate(int newVal);

};

#endif

