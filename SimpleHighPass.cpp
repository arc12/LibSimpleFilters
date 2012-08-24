#include "SimpleHighPass.h"

SimpleHighPass::SimpleHighPass(float alpha, boolean burnIn){
  _alpha = alpha;
  _burnIn = burnIn;
  _lastOutput = 0.0F; 
}

float SimpleHighPass::updateF(int newVal){
  if(!_updated){
    _updated= true;
    if(_burnIn){
      _lastOutput = 0;
      _lastInput = newVal;
    }
  }
  _lastOutput= _alpha*(_lastOutput+newVal-_lastInput);
  _lastInput = newVal;
  return _lastOutput;
}
