/* MedianFilter.h - Median Filter                               
 Copyright 2012, Adam Cooper
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * MedianFilter is free software: you can redistribute it and/or modify     *
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
#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include "Arduino.h"

#define MEDIAN_MAX_LEN 25 //!< Maximum number of samples, as specified by the length parameter in the constructor. Absolute max is 256.

/*!  This filter calculates the median of a set number of previous values.
This is able to suppress sudden impules/glitches while still allowing step changes to be preserved, although delayed.
Longer buffers will reject longer outlier signals.
See http://en.wikipedia.org/wiki/Median_filter (also http://medim.sth.kth.se/6l2872/F/F7-1.pdf)
 To use: create an instance of the filter and submit new readings using update().
 Readings should be sampled at regular (i.e. equal) time intervals.
 @brief  A finite length median filter. */
class MedianFilter{
public:
  /*! Create the filter with specified parameters.
   @param length The number of samples to take into account with a maximum specified by MEDIAN_MAX_LEN. This should be odd; even values will be siltently increased by 1.
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  MedianFilter(int length, boolean burnIn);

  /** @name Active
   Methods to interact with an active filter. */
  //!@{
  /*! Submit a new measurement to the filter.
   @param newVal The new value.
   @returns The filter output. */
  int update(int newVal);

  //!@}  

  /** @name Debugging
   Useful stuff for debugging etc */
  //!@{
  /*! Get the previously-submitted values.
  @param[out] A buffer of length specified by the length parameter in the constructor. */
  void getHistory(int* values[]);
  /*! What was the last index used in the returned buffer from getHistory()?
  @returns The index to the value submitted by the last update() */
  int getLastIndex();
  //!@}


private:
  //constructor parameters
  boolean _burnIn;
  int _length;

  boolean _updated;//has the filter received any data yet
  int _values[MEDIAN_MAX_LEN];
  byte _sortList[MEDIAN_MAX_LEN]; //sorted order of entries in _values
  int _index;// pointer into _values[]
  
  //common code used by both update() methods
  void accumulate(int newVal);

};

#endif

