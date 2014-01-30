/*

 */

#include "Arduino.h"
#include "lfrlib.h"

int sensorArray [] = {0,0,0,0,0,0,0,0,0};
byte maximum , maximumPosition , x , sum , average , threshold , difference[10] , line ;

lfrlib::lrflib(int enb1, int in1, int in2, int enb2, int in3,int in4)
{
	int _enb1 = enb1;
	int _enb2 = enb2;
	int _in1 = in1;
	int _in2 = in2;
	int _in3 = in3;
	int _in4 = in4;
	Serial.begin(9600); 
	pinMode(_in1, OUTPUT);
	pinMode(_in2, OUTPUT);
	pinMode(_in3, OUTPUT);
	pinMode(_in4, OUTPUT);
	pinMode(_enb1, OUTPUT);
	pinMode(_enb2, OUTPUT);
	pinMode(13, OUTPUT);



}

int lfrlib::lineDetect()
{
	int difference[8];  //intializing difference array
	difference[0] = abs(sensorArray[0]-sensorArray[7]); //sensorArray is the average of all readings
	difference[1] = abs(sensorArray[1]-sensorArray[7]); //difference [x] is the deviation of no. x sensor with the average sensor value
	difference[2] = abs(sensorArray[2]-sensorArray[7]); 
	difference[3] = abs(sensorArray[3]-sensorArray[7]); 
	difference[4] = abs(sensorArray[4]-sensorArray[7]); 
	difference[5] = abs(sensorArray[5]-sensorArray[7]);
	difference[6] = difference[1] + difference[2] + difference[3] + difference[4] + difference[5] + difference[0]; //sum of all difference
	difference[7] = difference[6]/6; //average of all the difference
	//========================
	boolean errorCheck = true;
	//========================
	maximum = difference[0];	
	maximumPosition = 0; 
	for (x = 1; x < 6; x++){ 
		if(difference[x]>maximum && difference[x] > difference[7])
		{ 
			maximum = difference[x]; 
			maximumPosition = x;
			//=================
			errorCheck = false;
			//=================
		} 
	}
	
	//=============================================================
	if (errorCheck && difference[0]<difference[7])
	{
		maximumPosition = -1; //negative number signifies an error
	}
	//=============================================================
	return maximumPosition; 
}

void lfrlib::ledDisplay(int y)
{
	ledReset(); 
	if( y == 0 ){ 
		digitalWrite(8, HIGH); 
	} 
	if( y == 1 ){ 
		digitalWrite(9, HIGH); 
	} 
	if( y == 2 ){ 
		digitalWrite(10, HIGH); 
	} 
	if( y == 3 ){ 
		digitalWrite(11, HIGH); 
	} 
	if( y == 4 ){ 
		digitalWrite(12, HIGH); 
	} 
	if( y == 5 ){ 
		digitalWrite(13, HIGH); 
	}
}

void lfrlib::followLine(int y){
	if( y == 0 ){ 
		fullLeft(); 
	} 
	if( y == 1 ){ 
		left(); 
	} 
	if( y == 2 ){ 
		forward(); 
	} 
	if( y == 3 ){ 
		forward(); 
	} 
	if( y == 4 ){ 
		right(); 
	} 
	if( y == 5 ){ 
		fullRight; 
	}
	if (y == -1)
	{
		backward();
	}
}


void lfrlib::lineSet()
{
	sum = sensorArray[0] + sensorArray[1] + sensorArray[3] + sensorArray[4] + sensorArray[5]; 
	average= (sum/5); 
	if (average > sensorArray[2])
	{
		threshold = 50; //(abs(average - sensorArray[2])/2); 
		line = 0; 
	} 
	else
	{
		threshold = 1000; 
		//(abs(sensorArray[2] - average)/2);
		line = 1; 
	}
	flickr();
} 


void lfrlib::flickr()
{
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(200); 
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(400); 
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(200); 
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(400); 
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(200); 
	digitalWrite(13, HIGH);  delay(200);  ledReset();  delay(400); 
}

void lfrlib::readAnalog(){ 
	sensorArray[0] = analogRead(A0); 
	sensorArray[1] = analogRead(A1); 
	sensorArray[2] = analogRead(A2); 
	sensorArray[3] = analogRead(A3); 
	sensorArray[4] = analogRead(A4); 
	sensorArray[5] = analogRead(A5); 
	sensorArray[6] = sensorArray[0] + sensorArray[1] + sensorArray[2] + sensorArray[3] + sensorArray[4] + sensorArray[5];
	sensorArray[7] = sensorArray[6]/6;
}


void lfrlib::printData()
{
	Serial.print(sensorArray[0]); 
	Serial.print(" "); 
	Serial.print(sensorArray[1]); 
	Serial.print(" "); 
	Serial.print(sensorArray[2]); 
	Serial.print(" "); 
	Serial.print(sensorArray[3]); 
	Serial.print(" "); 
	Serial.print(sensorArray[4]); 
	Serial.print(" "); 
	Serial.print(sensorArray[5]); 
	Serial.print(" "); 
	Serial.print(difference[0]); 
	Serial.print(" "); 
	Serial.print(difference[1]); 
	Serial.print(" "); 
	Serial.print(difference[2]); 
	Serial.print(" "); 
	Serial.print(difference[3]); 
	Serial.print(" "); 
	Serial.print(difference[4]); 
	Serial.print(" "); 
	Serial.print(difference[5]); 
	Serial.print(" "); 
	Serial.print(sensorArray[0]/average*100); 
	Serial.print(" "); 
	Serial.print(sensorArray[1]/average*100); 
	Serial.print(" "); 
	Serial.print(sensorArray[2]/average*100); 
	Serial.print(" "); 
	Serial.print(sensorArray[3]/average*100); 
	Serial.print(" "); 
	Serial.print(sensorArray[4]/average*100); 
	Serial.print(" "); 
	Serial.print(sensorArray[5]/average*100); 
	Serial.println(" ");
	delay(500); 
}

void lfrlib::ledChaser()
{
	pinMode(8,OUTPUT);  pinMode(9,OUTPUT);  pinMode(10,OUTPUT);
	pinMode(11,OUTPUT); pinMode(12,OUTPUT); pinMode(13,OUTPUT);
	ledReset();  digitalWrite(8, HIGH);  delay(1000); 
	ledReset();  digitalWrite(9, HIGH);  delay(1000); 
	ledReset();  digitalWrite(10, HIGH); delay(1000); 
	ledReset();  digitalWrite(11, HIGH); delay(1000); 
	ledReset();  digitalWrite(12, HIGH); delay(1000); 
	ledReset();  digitalWrite(13, HIGH); delay(1000); 
}


void lfrlib::ledReset()
{ 
	digitalWrite(8, LOW);   digitalWrite(9, LOW); 
	digitalWrite(10, LOW);  digitalWrite(11, LOW); 
	digitalWrite(12, LOW);  digitalWrite(13, LOW); 
}


void lfrlib::forward()
{ 
	digitalWrite(_in1,HIGH);  digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);  digitalWrite(_in4,LOW);
	analogWrite(_enb1, 255);  analogWrite(_enb2, 255);
	Serial.println(" ");  Serial.println(" Go Forward ");

}

void lfrlib::backward()
{ 
	digitalWrite(_in2,HIGH);  digitalWrite(_in1,LOW);
	digitalWrite(_in4,HIGH);  digitalWrite(_in3,LOW);
	analogWrite(_enb1, 255);  analogWrite(_enb2, 255);
	Serial.println(" ");  Serial.println(" Go Backward ");
}

void lfrlib::fullRight()
{ 
	digitalWrite(_in1,HIGH);  digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);  digitalWrite(_in4,LOW);
	analogWrite(_enb1, 255);  analogWrite(_enb2, 0);
	Serial.println(" ");  Serial.println(" Full Right ");
}

void lfrlib::fullLeft()
{ 
	digitalWrite(_in1,HIGH);  digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);  digitalWrite(_in4,LOW);
	analogWrite(_enb1, 0);    analogWrite(_enb2, 255);
	Serial.println(" ");  Serial.println(" Full Left ");
}

void lfrlib::right()
{ 
	digitalWrite(_in1,HIGH);  digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);  digitalWrite(_in4,LOW);
	analogWrite(_enb1, 255);  analogWrite(_enb2, 180);
	Serial.println(" ");  Serial.println(" Go Right ");
}

void lfrlib::left()
{ 
	digitalWrite(_in1,HIGH);  digitalWrite(_in2,LOW);
	digitalWrite(_in3,HIGH);  digitalWrite(_in4,LOW);
	analogWrite(_enb1, 180);  analogWrite(_enb2, 255);
	Serial.println(" ");  Serial.println(" Go Left ");


}

int lfrlib::derailSolver()
{


}
