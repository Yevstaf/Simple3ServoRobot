#include <Servo.h> 
#include <math.h>
Servo servo1; // servo controls:
Servo servo2;
Servo platform;

  double a = 13.5;// robot's linear size
  double b = 12;
  double k = 11;
  
  int x = 0;// basic coordinates
  int y = 1;
  int z = 2;
  double platformCord[] = {0,a+b,11};
  double baseCord[] = {0,0,0};
    void setup(){
      platform.attach(9);// 
      servo1.attach(10); //
      servo2.attach(5); // 

      servo1.write(180); //    |
      servo2.write(5); //  |>set up basic servos position
      platform.write(180);// |       
  }

  void loop(){ ///<<<<<<--------Start loop------------------
paint();

  }

//Service methods 
  double getPlatformAngle(double incomeCord[]){
    double e;
    e = sqrt(pow(platformCord[x] - incomeCord[x],2) + pow(platformCord[y] - incomeCord[y],2));
    double f;
    f = sqrt(pow(baseCord[x] - incomeCord[x],2) + pow(baseCord[y] - incomeCord[y],2));
    double g ;
     g = a + b;    
      return   180 -(acos((e*e + g*g - f*f)/(2*e*g))/3.14)*180.0;
    }
    
  double getFirstServoAngle(double incomeCord[]){ 
    double c;
    c = sqrt(pow(platformCord[x] - incomeCord[x],2) + pow(platformCord[z]+ k - incomeCord[z],2));
    double n;
    n = sqrt(pow(baseCord[y] - incomeCord[y],2) + pow(baseCord[z] - incomeCord[z],2));
    return  180 - abs(((acos((c*c + k*k - n*n)/(2*c*k))/3.14)*180.0 + (acos((b*b + c*c - a*a)/(2*b*c))/3.14)*180.0));
  }
  
    double getSecondServoAngle(double incomeCord[]){
      double cc;
      cc = sqrt(pow(platformCord[x] - incomeCord[x],2) + pow(platformCord[z]  - incomeCord[z],2));
      return   abs(((acos((a*a + b*b - cc*cc)/(2*a*b)))/3.14)*180.0);
      }
      
//Action methods
  void moveServo(Servo serv,int degree, double sp){
      if(degree >= 0 && degree <= 180 ){
      int prev = serv.read();
  
        if(degree > prev){
            for(int i = prev; i < degree; i++){
              serv.write(i);
                delay((1000.0/sp)/180.0);
         }//end FOR
        }else{
            for(int i = prev; i > degree; i--){
              serv.write(i);
                delay((1000.0/sp)/180.0);
            }//end FOR
        }//enf IF/ELSE
      }
     }//end moveServ

void smoothMove(Servo sv1,double dSv1,Servo  sv2, double dSv2, Servo sv3, double dSv3,float sp){
          double prev1 = sv1.read();
          double prev2 = sv2.read();
          double prev3 = sv3.read();
          
          double first = abs(prev1 - dSv1);
          double sec = abs(prev2 - dSv2);
          double third = abs (prev3 - dSv2);

          double biggest =  first > sec ? first : sec > third ? sec : third;
          first = first/biggest;
          sec = sec/biggest;
          third = third/biggest;
          
            for(int i = biggest; i > 0; i--){
              if(dSv1 > prev1){
                sv1.write(prev1);
                prev1 +=first;
                   }else{
                 sv1.write( prev1); 
               prev1-= first;
            }//enf IF/ELSE

            if(dSv2 > prev2){
               sv2.write(prev2);
               prev2 +=sec;
                   }else{
                 sv2.write( prev2); 
               prev2-= sec;
            }//enf IF/ELSE

           if(dSv3 > prev3){
               sv3.write(prev3);
               prev3 +=third;
                   }else{
                 sv3.write( prev3); 
               prev3-= third;
          }//enf IF/ELSE
            delay((1000/sp)/180);
            
          }

  }

  void additionalLinearMove(Servo sv1,double dSv1,Servo  sv2, double dSv2, Servo sv3, double dSv3,double sp){
      double first = sv1.read() + dSv1;
      double sec = sv2.read() + dSv2;
      double third = sv3.read() + dSv3;
      double res =  dSv1 > dSv2 ? dSv1 : dSv2 > dSv3 ? dSv2 : dSv3; //find the heighest walue
      double prev1 = sv1.read(); 
      double prev2 = sv2.read();
      double prev3 = sv3.read();

        for(int del = res; del > 0; del--){ //main delay block
            // first servo position code start:
              if(first > prev1){
               sv1.write(prev1++); 
             }else if (first < prev1){
               sv1.write(prev1--);
             }else{}
            // first servo position code end
          
          //second start:
            if(sec > prev2){
              sv2.write(prev2++); 
            }else if (sec < prev2){
              sv2.write(prev2--);
            }else{}
              //second end
              
              //third start:
            if(sec > prev3){
                sv3.write(prev3++); 
            }else if (sec < prev3){
                sv3.write(prev3--);
            }else{}
             delay((1000.0/sp)/180.0);
       }//end of FOR
  }//end of additionalMove

  void linearMove(Servo sv1,double dSv1,Servo  sv2, double dSv2, Servo sv3, double dSv3,double sp){
          double prev1 = sv1.read();
          double prev2 = sv2.read();
          double prev3 = sv3.read();
          
          double first = abs(prev1 - dSv1);
          double sec = abs(prev2 - dSv2);
          double third = abs (prev3 - dSv2);
          
          double biggest = first > sec ? first : sec > third ? sec : third;
          
            for(int i = biggest; i > 0; i--){
          
                 if(dSv1 > prev1){
                   sv1.write(prev1++);
                  }else{
                   sv1.write(prev1--);          
                }//enf IF/ELSE
  
                if(dSv2 > prev2){
                 sv2.write(prev2++);
                   }else{
                 sv2.write(prev2--);          
                }//enf IF/ELSE  
        
                 if(dSv3 > prev3){
                   sv3.write(prev3++);
                  }else{
                   sv3.write(prev3--);          
                 }//enf IF/ELSE
             delay((1000.0/sp)/180.0);
            }   
      }//end of linearMove
      
      void accelMove(double cords[],float startSpeed, float accel, float maxSpeed){
          double prev1 = platform.read();
          double prev2 = servo1.read();
          double prev3 = servo2.read();
          double sp = startSpeed;
          
          double first = abs(platform.read() - getPlatformAngle(cords));
          double sec = abs(servo1.read() - getFirstServoAngle(cords));
          double third = abs (servo2.read() - getSecondServoAngle(cords));
      
          double smallest =  first < sec ? first : sec < third ? sec : third;
          double stepOne = (getPlatformAngle(cords) - prev1)/smallest;
          double stepTwo = (getFirstServoAngle(cords) - prev2)/smallest;
          double stepThree = (getSecondServoAngle(cords) - prev3)/smallest;

            for(int i = smallest; i > 0; i--){
              linearMove(platform,prev1,servo1,prev2,servo2,prev3,sp);

              prev1 += stepOne;
              prev2 += stepTwo;
              prev3 += stepThree;

              if((sp + accel) < maxSpeed){
                sp += accel;
                }
              }
           stepOne = 0;
           stepTwo = 0;
           stepThree = 0;
  }

  
  void linearCordsMove(double cords[],double sp){
    int platformAngle = getPlatformAngle(cords);
    int firstAngle = getFirstServoAngle(cords);
    int secondAngle = getSecondServoAngle(cords);
    linearMove(platform,platformAngle,servo1,firstAngle,servo2,secondAngle,0.2);
    
  
  }
  
  void smoothCordsMove(double cords[],double sp){
    int platformAngle = getPlatformAngle(cords);
    int firstAngle = getFirstServoAngle(cords);
    int secondAngle = getSecondServoAngle(cords);  
    smoothMove(platform,platformAngle,servo1, firstAngle, servo2, secondAngle,sp);
   }


    void paint(){ //primitive program for servos test
  delay(100);
  smoothMove(platform,135,servo1, 90, servo2, 70,0.1);
  delay(200);
  moveServo(servo2,100,0.1);
  delay(200);
  moveServo(servo2,85,0.1);
  delay(200);
  moveServo(platform,120,0.1);
  delay(200);
  moveServo(servo2,70,0.1);
  delay(200);
  moveServo(servo2,100,0.1);
  delay(200);
  
  moveServo(servo1,110,0.1);
  delay(200);
    moveServo(platform,110,0.1);
    moveServo(servo2,70,0.1);
    moveServo(servo1,90,0.1);
  delay(200);
    moveServo(servo2,85,0.1);
  delay(200);
   moveServo(platform,95,0.1);
  delay(200);
  moveServo(servo2,70,0.1);
  delay(200);
  moveServo(servo2,100,0.1);
  delay(200);
    moveServo(platform,105,0.1);
  delay(200);
  
  moveServo(servo1,110,0.1);
  delay(200);
   moveServo(platform,85,0.1);
   moveServo(servo1,90,0.1);
   moveServo(platform,80,0.1);
  delay(200);   
   moveServo(servo2,70,0.1);
  moveServo(platform,70,0.1);
 delay(200); 
moveServo(servo2,100,0.1);

delay(200); 
moveServo(servo1,110,0.1);
moveServo(platform,60,0.1);
delay(200); 
moveServo(servo1,90,0.1);
moveServo(servo2,70,0.1);
moveServo(platform,50,0.1);
moveServo(servo2,100,0.1);
  delay(200); 
   
   
   moveServo(servo1,100,0.1);
   moveServo(platform,135,0.1);
   moveServo(servo2,70,0.1);
   delay(200);
   
  }
