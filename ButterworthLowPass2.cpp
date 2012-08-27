#include "ButterworthLowPass2.h"

const float pi = 3.1415927;

ButterworthLowPass2::ButterworthLowPass2(float fRatio, boolean burnIn){
  _burnIn = burnIn;
  _updated=false;
  //calc the coeffs for a stand-alone 2nd order filter
  calculateCoefficients(fRatio,0,2);
}

ButterworthLowPass2::ButterworthLowPass2(float fRatio, int k, int N, boolean burnIn){
  _burnIn = burnIn;
  _updated=false;
  //calc the coeffs for a component/elementary 2nd order filter
  calculateCoefficients(fRatio,k,N);
}

float ButterworthLowPass2::updateF(int newVal){
  //apply the gain
  float in0 = float(newVal)*_gain;
  float out0;

  //This section is so that the history of samples is initialised on first use.
  if(!_updated){
    _updated= true;
    if(_burnIn){
      //fill with first reading
      _in1 = in0;
      _out1 = in0;
      out0 = in0;//the output
    }
    else{
      //fill with zero
      _in1 = 0;
      _out1 = 0.0F;
      out0 = 0.0F;//the output
    }
  } 
  else{
    //apply the filter
    out0 = _a0*in0 + _a1*_in1 + _a2*_in2 - _b1*_out1 - _b2*_out2;
  }
  //shuffle current to previous ready for next step
  _in2 = _in1;
  _in1 = in0;
  _out2 = _out1;
  _out1 = out0;
  return out0;       
}


void ButterworthLowPass2::getCoefficients(float coefficients[]){
  coefficients[0] = _gain;
  coefficients[1] = _a0;
  coefficients[2] = _a1;
  coefficients[3] = _a2;
  coefficients[4] = _b1;
  coefficients[5] = _b2;
}

void ButterworthLowPass2::printCoefficients(){
  Serial.println("Butterworth 2nd Order Coefficients");
  Serial.print("Gain=");
  Serial.println(_gain,4);
  Serial.print("a0=");
  Serial.println(_a0,3);
  Serial.print("a1=");
  Serial.println(_a1,3);
  Serial.print("a2=");
  Serial.println(_a2,3);
  Serial.print("b1=");
  Serial.println(_b1,3);
  Serial.print("b2=");
  Serial.println(_b2,3);
  Serial.println("-------------");
}

void ButterworthLowPass2::getState(float state[]){
  state[0]=float(_in1);
  state[1]=float(_in2);
  state[2]= _out1;
  state[3]=_out2;
}

void ButterworthLowPass2::setState(float state[]){
  _in1 = int(state[0]);
  _in2 = int(state[1]);
  _out1 = state[2];
  _out2 = state[3];
  _updated = true;//otherwise the state may get over-written in cases where a new object is created and state loaded in
}

//
// Private
//  
void ButterworthLowPass2::calculateCoefficients(float fRatio, int k, int N){
  //see http://www.kwon3d.com/theory/filtering/fil.html
  //check with http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.html
  float omegaC = tan(pi/fRatio);
  float omegaC2 = pow(omegaC,2);
  float ckn = 2.0F*cos(float(2*k+1)*pi/float(2*N))*omegaC;
  float c_k = 1.0F + ckn + omegaC2;
  _gain = omegaC2/c_k;
  _a0=1.0F;
  _a2=1.0F;
  _a1=2.0F;
  _b1=2.0F*(omegaC2-1.0F)/c_k;
  _b2=(1.0F - ckn + omegaC2)/c_k;
}



