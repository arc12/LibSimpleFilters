/* Xxx.h - XXXXXX                               
 Copyright 2012, Adam Cooper
 
/* ***************************** LICENCE ************************************
 *  This file is part of LibSimpleFilters Arduino library.                   *
 *    (each component of the library is licenced separately)                 *
 *                                                                           *
 * Xxx is free software: you can redistribute it and/or modify     *
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
#ifndef XXX_H
#define XXX_H


#include "Arduino.h"

//#defines visible to Doxygen but ungrouped
#define XXX_MAX_LEN 25 //!< Maximum number of samples, as specified by the length parameter in the constructor

/** @name GROUP_NAME
 * Group description
 */
//!@{
//#defines visible to Doxygen and grouped under a name and description
//!@}

/// \cond HIDDEN_GROUP_NAME
//#defines grouped and hidden from Doxygen unless explicitly selected by name
/// \endcond

/*! Class description, incl references to datasheet, theory etc.
 To use: create an instance of the filter and submit new readings using update().
 Readings should be sampled at regular (i.e. equal) time intervals.
 @brief Class brief description
 @todo unfinished jobs! */
class Xxx{
public:
  /*! Create the filter with specified parameters.
   @param length The number of samples to take into account with a maximum specified by MOVING_AVERAGE_MAX_LEN
   @param alpha The smoothing factor  (range 0<=alpha<=1)
   @param burnIn Whether to initialise the filter on first reading such that the output = the input after that reading.
   Otherwise the output is as if the input had just been turned on with previous zero readings. */
  Xxx(int length, float alpha, boolean burnIn);

  /** @name Active
   Methods to interact with an active filter. */
  //!@{
  /*! Submit a new measurement to the filter.
   @param newVal The new value.
   @returns The filter output. */
  int update(int newVal);
  /*! Same as the integer version except that the average is computed using 4 byte floating point arithmetic. */
  float updateF(int newVal);
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
  float _alpha;
  int _length;

  boolean _updated;//has the filter received any data yet
  int _values[XXX_MAX_LEN];
  int _index;// pointer into _values[]

};

#endif

