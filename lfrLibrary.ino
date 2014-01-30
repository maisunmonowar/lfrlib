int in1 = 7; 
int in2 = 8;

int enb1 = 9; 
int enb2 = 10;

int in3 = 11; 
int in4 = 12;


int threshold,line,p,sum,average,minimum,minimumPosition,maximum,maximumPosition,x;

int sensorArray[8]; 
int difference[8];

void setup() { 
  line = 4; 
  threshold = 5000; 
  Serial.begin(9600); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enb1, OUTPUT); 
  pinMode(enb2, OUTPUT); 
  pinMode(13, OUTPUT);

}

void loop() 
{

  readAnalog(); 
  printData(); 
  p = lineDetect();   
  followLine(p); 
}


int lineDetect(){ 
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


void ledDisplay(int y){ 
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


void followLine(int y){ 
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


void lineSet(){ 
  sum = sensorArray[0] + sensorArray[1] + sensorArray[3] + sensorArray[4] + sensorArray[5]; 
  average= (sum/5); 
  if (average > sensorArray[2]) { 
    threshold = 50; //(abs(average - sensorArray[2])/2); 
    line = 0; 
  } 
  else { 
    threshold = 1000; 
    //(abs(sensorArray[2] - average)/2);

    line = 1; 

  }


  flickr();


} 

void flickr(){ 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(200); 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(400); 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(200); 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(400); 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(200); 
  digitalWrite(13, HIGH); 
  delay(200); 
  ledReset(); 
  delay(400); 
}



void readAnalog(){ 
  sensorArray[0] = analogRead(A0); 
  sensorArray[1] = analogRead(A1); 
  sensorArray[2] = analogRead(A2); 
  sensorArray[3] = analogRead(A3); 
  sensorArray[4] = analogRead(A4); 
  sensorArray[5] = analogRead(A5); 
  sensorArray[6] = sensorArray[0] + sensorArray[1] + sensorArray[2] + sensorArray[3] + sensorArray[4] + sensorArray[5]; 
  sensorArray[7] = sensorArray[6]/6;
}



void printData(){ /*Serial.print("Threshold "); Serial.print(threshold); Serial.print(" "); Serial.print("Line "); Serial.print(line); Serial.print(" "); Serial.print("p or position "); Serial.print(p); Serial.print(" "); */
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
  Serial.println(" "); /* Serial.print("Sum "); Serial.print(sum); Serial.print(" Average "); Serial.println(average);*/
  delay(500); 
}



void ledChaser(){ 
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  ledReset();
  digitalWrite(8, HIGH); 
  delay(1000); 
  ledReset(); 
  digitalWrite(9, HIGH); 
  delay(1000); 
  ledReset(); 
  digitalWrite(10, HIGH); 
  delay(1000); 
  ledReset(); 
  digitalWrite(11, HIGH); 
  delay(1000); 
  ledReset(); 
  digitalWrite(12, HIGH); 
  delay(1000); 
  ledReset(); 
  digitalWrite(13, HIGH); 
  delay(1000); 
}



void ledReset(){ 
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(11, LOW); 
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW); 
}

void forward(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  analogWrite(enb1, 255); 
  analogWrite(enb2, 255); 
  Serial.println(" ");
  Serial.println(" Go Forward ");

}

void backward(){ 
  digitalWrite(in2,HIGH); 
  digitalWrite(in1,LOW); 
  digitalWrite(in4,HIGH); 
  digitalWrite(in3,LOW); 
  analogWrite(enb1, 255); 
  analogWrite(enb2, 255); 
  Serial.println(" ");
  Serial.println(" Go Backward ");
}

void fullRight(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  analogWrite(enb1, 255); 
  analogWrite(enb2, 0); 
  Serial.println(" ");
  Serial.println(" Full Right ");
}

void fullLeft(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  analogWrite(enb1, 0); 
  analogWrite(enb2, 255); 
  Serial.println(" ");
  Serial.println(" Full Left ");
}

void right(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  analogWrite(enb1, 255); 
  analogWrite(enb2, 180); 
  Serial.println(" ");
  Serial.println(" Go Right ");
}

void left(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW); 
  analogWrite(enb1, 180); 
  analogWrite(enb2, 255); 
  Serial.println(" ");
  Serial.println(" Go Left ");


}


