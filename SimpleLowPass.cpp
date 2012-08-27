#include "SimpleLowPass.h"

const float pi = 3.1415927;

SimpleLowPass::SimpleLowPass(float alpha, boolean burnIn){
  _alpha = alpha;
  _burnIn = burnIn;
  _lastOutput = 0.0F; 
}
  float SimpleLowPass::calcAlpha(float fRatio){
    return 2.0F*pi/(fRatio + 2.0F*pi);
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
