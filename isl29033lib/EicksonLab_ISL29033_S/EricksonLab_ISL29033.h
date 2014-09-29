/******************************************************************************
 *  ISL29033 Hardware i2c Driver for Arduino
 *
 *  Copyright Erickson Lab, Cornell University
 *  
 *  Iain Derrington (http://www.kandi-electronics.co.uk)
*******************************************************************************/
#ifndef EricksonLab_ISL29033_h
#define EricksonLab_ISL29033_h

class EricksonLab_ISL29033 {
public:  
  EricksonLab_ISL29033();
  EricksonLab_ISL29033(unsigned char);

  int init(int);
  int init();         // initialises the device
  float read();        // read light value
private:
  unsigned char dev_address;
};

#endif
