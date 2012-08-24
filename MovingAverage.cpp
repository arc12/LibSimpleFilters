#include "MovingAverage.h"

MovingAverage::MovingAverage(int length, boolean burnIn){
  //make sure the buffer length is within the allocated space
  if(length>MOVING_AVERAGE_MAX_LEN){
    _length = MOVING_AVERAGE_MAX_LEN;
  }
  else{  
    _length = length;
  }
  _correction = _length/2;
  _burnIn = burnIn;
  _index = 0;
}

int MovingAverage::update(int newVal){
  accumulate(newVal);
  return (_sum+_correction)/_length;
}

float MovingAverage::updateF(int newVal){
  accumulate(newVal);
  return float(_sum)/float(_length);
}

// debugging
void MovingAverage::getHistory(int* values[]){
  *values = _values;  
}

int MovingAverage::getLastIndex(){
  int lastIndex = _index-1;
  if(lastIndex<0){
    lastIndex = _length-1;
  }
  return lastIndex;
}

//
// private
//
void MovingAverage::accumulate(int newVal){
  //This section is so that the history of samples is initialised on first use.
  if(!_updated){
    _updated= true;
    if(_burnIn){
      //fill _values with newVal rather than zeros such that the moving average return value starts as newVal
      for(int i=1; i<_length; i++){
        _values[i]=newVal;
      }
      _sum = newVal*(_length-1); 
    }
    else{
      for(int i=0; i<_length; i++){
        _values[i]=0;
      }
      _sum = 0;
    }
  }

  //This is where accumulation happens
  //update the total
  _sum-=_values[_index];
  _sum+=newVal;
  //store the new value
  _values[_index] = newVal;
  //increment the pointer, bringing back to 0 as required
  _index++;
  _index = _index%_length;
}






