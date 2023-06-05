#include <LiquidCrystal.h>
#include <Servo.h> 
LiquidCrystal LCD(9, 8, 13, 12, 11, 10);

//Aumentar e diminuir temp/light
Servo servo1;
Servo servo2;
Servo servo3;

int count = 0;

int pinoA4 = 4;
int pinoA5 = 5;

double lightBUT = 0;//inicia lightbut
double tempBUT = 0;//inicia tempbut
int umityBUT = 1000;

// time
int startTime;

// display
String ML = "Ambiente a meia luz";
String MC = "Ambiente muito claro";

// temp
int t = 1;
float temp_READ;

// moist
int moist_READ;
int moist = 2;
int mr = 0;

// light
int Ph = A0;
int Ph_READ;
int delight = 0;

void setup() {
  // counter
  Serial.begin(9600);
  while (!Serial);
  startTime = millis(); // Set the start time

  // display
  LCD.begin(16, 2);
  
  //buttons
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);

  //servos
  servo1.attach(5);//temp
  servo2.attach(6);//light
  servo3.attach(7);//umity
}

void display1(int x) {
  LCD.clear();
  LCD.setCursor(0, 0);

  if (x == 0) {
    LCD.print(ML.substring(0, 16)); // 1st 16 letters on the 1st line
    LCD.setCursor(0, 1);
    LCD.print(ML.substring(16)); // print the rest
  }
  else if (x == 1) {
    LCD.print(MC.substring(0, 16)); // 1st 16 letters on the 1st line
    LCD.setCursor(0, 1);
    LCD.print(MC.substring(16)); // print the rest
  }

  delay(1500);
}

void display2(int x, float tt) {
  LCD.clear();
  LCD.setCursor(0, 0);

  if (x == 0) {
    LCD.print("Temp: Baixa");
  }
  else if (x == 1) {
    LCD.print("Temp: OK");
  }
  else if (x == 2) {
    LCD.print("Temp: Alta");
  }

  LCD.setCursor(0, 1);
  LCD.print("Temp: ");
  LCD.print(tt);
  LCD.print("C");

  delay(1500);
}

void display3(int x, int tt) {
  LCD.clear();
  LCD.setCursor(0, 0);

  if (x == 0) {
    LCD.print("Umidade ALTA");
  }
  else if (x == 1) {
    LCD.print("Umidade OK");
  }
  else if (x == 2) {
    LCD.print("Umidade BAIXA");
  }

  LCD.setCursor(0, 1);
  LCD.print("Umidade: ");
  LCD.print(tt); // convert to the correct percentage
  LCD.print("%");

  delay(1500);
}

void display4(int umity){
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Despejear agua");
  LCD.setCursor(0, 1);
  LCD.print("cada ");
  LCD.print(umity);
  LCD.print(" horas");
}

void loop() {
  // TIME
  unsigned long milisec = millis() - startTime;
  unsigned long sec = milisec / 1000;
  unsigned long hour = sec / 3600;    
  
    //ACTION
  if((hour - startTime >= umityBUT)&&(count == 1)){//abre torneira a cada hora determinada
    startTime = sec;
    
    servo3.write(179);
    delay(60000);
  }
  servo1.write(tempBUT);
  servo2.write(lightBUT);
  servo3.write(0);
  
  // READS + OPS
  Ph_READ = analogRead(Ph);
  Ph_READ = map(Ph_READ, 0, 675, 0, 1023);
  delight = Ph_READ * 0.0645; // 0 - 99.999999

  temp_READ = analogRead(t);
  temp_READ = temp_READ * 0.0752;

  moist_READ = analogRead(moist);
  moist_READ = map(moist_READ, 0, 675, 0, 1023);
  mr = moist_READ * 0.0645;
  
  //DIALS p2
  if(digitalRead(2) == LOW){
    
    LCD.clear();
  	LCD.setCursor(0, 0);
  	LCD.print("Soltar Botão");
    delay(2000);
    
    LCD.clear();
    LCD.setCursor(0, 0);
  	LCD.print("Apertar dnv");
    LCD.setCursor(0, 1);
  	LCD.print("para confirmar");
    delay(2000);
    
    umityBUT=0;
    
    while(digitalRead(2) == HIGH){
      //leitura condicional 
      lightBUT = analogRead(pinoA4);//um valor analógico do potenciometro de  0 a 255
  	  lightBUT = map(lightBUT, 0, 1023, 0, 179);//valor lido entre 0 a 1023 para uma valor ente 0 e 180
  
  	  tempBUT = analogRead(pinoA5);
  	  tempBUT = map(tempBUT, 0, 1023, 0, 179);
      
      //alteração de timing da agua
      if (digitalRead(4) == LOW) {
        umityBUT++;
        display4(umityBUT);
      }
      if (digitalRead(3) == LOW && umityBUT > 0) {
        umityBUT--;
        display4(umityBUT);
      }
      count = 1;
      startTime = 0;
      delay(200);
    }
  }


  // MOISTURE
  if (0 == (sec % 2)) {
    if (70 < mr) {
      display3(0, mr);
    }
    else if (50 > mr) {
      display3(2, mr);
    }
    else {
      display3(1, mr);
    }
  }

  // LIGHT
  if (0 == (sec % 3)) {
    if (delight > 66) {
      display1(0);
    }
    else if (delight < 33) { // 41 = 1/3
      display1(1);
    }
    else {
      // Display light value
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Light: ");
      LCD.print(delight);
      LCD.print("%");
      delay(1500);
    }
  }

  // TEMPERATURE
  if (0 == (sec % 5)) {
    if (temp_READ < 10) {
      display2(0, temp_READ);
    }
    else if ((temp_READ <= 15) && (temp_READ >= 10)) {
      display2(1, temp_READ);
    }
    else if (temp_READ > 15) {
      display2(2, temp_READ);
    }
  }
  
}