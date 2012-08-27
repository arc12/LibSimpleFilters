#include "MedianFilter.h"

MedianFilter::MedianFilter(int length, boolean burnIn){
  //make sure the buffer length is within the allocated space
  if(length>MEDIAN_MAX_LEN){
    _length = MEDIAN_MAX_LEN;
  }
  else{  
    _length = length;
  }
  //use an odd number for median so the middle value can be found.
  if(_length%2 == 0){
    if(length==MEDIAN_MAX_LEN){
      _length--;
    }
    else{
      _length++;
    }
  }
  _burnIn = burnIn;
  _index = 0;
  _updated=false;
}

int MedianFilter::update(int newVal){
  int median;
  //This section is so that the history of samples is initialised on first use.
  if(!_updated){
    _updated= true;
    if(_burnIn){
      //fill _values with newVal rather than zeros such that the moving average return value starts as newVal
      for(int i=0; i<_length; i++){
        _values[i]=newVal;
      }
      median = newVal;//the output
    }
    else{
      //fill with zero
      for(int i=0; i<_length; i++){
        _values[i]=0;
      }
      median = 0;//the output
    }
    //all values are the same so the sort order is arbitrary but it does need initialising
    for(int i=0; i<_length; i++){
      _sortList[i] = i;
    }
  }
  else{
    //Find the median!

    //update the buffer of values
    _values[_index] = newVal;
    //find the item in the sort list that points to the replaced value
    for(int si = 0; si<_length;si++){
      if(_sortList[si] == _index){
        //found the replaced item. Now push it up or down the list until it is properly re-sorted again
        boolean sorted = false;        
        if(si>0){
          //we are not at the bottom. Look beneath for a larger number to see if newVal should go down.
          for(int sd=si-1; sd>=0; sd--){
            if(newVal<_values[_sortList[sd]]){
              _sortList[sd+1]=_sortList[sd];
              _sortList[sd]=_index;
              sorted=true;
            }
            else{
              break;//there wasn't a larger number so stop looking
            }
          }
        }
        if(!sorted){
          if(si<_length-1){
            //we are not at the top. Look above for a smaller number to see if newVal should go up.
            for(int su=si+1; su<_length; su++){
              if(newVal>_values[_sortList[su]]){
                _sortList[su-1]=_sortList[su];
                _sortList[su]=_index;
              }
              else{
                break;//there wasn't a smaller number so stop looking
              }
            }
          }

        }
        break; //from si loop since if we got here we found the replaced item in the sort list
      }
    }//si loop
    //and the median is just... the middle entry in the sort list, so find the associated value
    median = _values[_sortList[_length/2]];

    //increment the pointer, bringing back to 0 as required
    _index++;
    _index = _index%_length;

  }
  return median;
}


// debugging
void MedianFilter::getHistory(int values[]){
  for(int i = 0; i<_length; i++){
    values[i] = _values[i];
  }  
}

int MedianFilter::getLastIndex(){
  int lastIndex = _index-1;
  if(lastIndex<0){
    lastIndex = _length-1;
  }
  return lastIndex;
}




