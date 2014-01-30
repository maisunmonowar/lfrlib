/*
  Written by maisunmonwar@gmail.com
  Released into the public domain.
*/

#ifndef lfrlib_h
#define lrflib_h

#include "Arduino.h"

class lfrlib
{
  public:
    lfrlib(int enb1,int in1,int in2,int enb2, int in3 , int in4);
    void left();
    void right();
    void forward();
    void backward();
    void fullLeft();
    void fullRight();    
    void ledDisplay(int y);
    void followLine(int y);
    void lineSet();
    void flickr();
    void readAnalog();
    void printData();
    void ledChaser();
    void ledReset();
    int lineDetect(); 
    int derailSolver();

    private:
    int _enb1;
    int _enb2;
    int _in1;
    int _in2;
    int _in3;
    int _in4;

};

#endif

