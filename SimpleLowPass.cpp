#include "SimpleLowPass.h"

SimpleLowPass::SimpleLowPass(float alpha, boolean burnIn){
  _alpha = alpha;
  _burnIn = burnIn;
  _lastOutput = 0.0F; 
}

float SimpleLowPass::updateF(int newVal){
  if(!_updated){
    _updated= true;
    if(_burnIn){
      _lastOutput = newVal;
    }
  }
  _lastOutput+= _alpha*(newVal-_lastOutput);
  return _lastOutput;
}
