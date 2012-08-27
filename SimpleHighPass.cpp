#include "SimpleHighPass.h"

const float pi = 3.1415927;

SimpleHighPass::SimpleHighPass(float alpha, boolean burnIn){
  _alpha = alpha;
  _burnIn = burnIn;
  _lastOutput = 0.0F; 
}

float SimpleHighPass::calcAlpha(float fRatio){
  return fRatio/(2.0F*pi + fRatio); 
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

