#include <TeensyThreads.h>
#include "Nextion.h"
#include <SPI.h>  
#include <SD.h>
#include <TimeLib.h>
#include <SparkFun_APDS9960_Wire0.h>
#include "SparkFun_APDS9960_Wire1.h"
SparkFun_APDS9960_Wire0 apds0 = SparkFun_APDS9960_Wire0();
SparkFun_APDS9960_Wire1 apds1 = SparkFun_APDS9960_Wire1();
 uint8_t proximity_data = 0;
 uint8_t proximity_data0 = 0;
 
#include "Filter.h"

long FilterWeight = 5;
ExponentialFilter<long> Filter1(5,0);

int dvolume=0;
int dbright=0;
int id1;
int id2;
int id3;
int id4;
int id5;
int id6;
int id7;
int checkingflag=0;
int analogInPin = 26;
int sensorValue = 0;
int limitCyclesQ=0;
int currentCyclesQ=0;
int UVOUT = 0;
int m0=0;
int s0=0;

volatile int s1;
volatile int s2;
volatile int s3;
volatile int laststatying=25;
volatile int statying=23;
volatile int killer=0;
volatile int killer2=0;
volatile int killer3=0;
volatile int killer4=0;
volatile int killer5=0;
volatile int killer6=0;
volatile int killer7=0;
volatile int temporaldbright=0;
volatile int temporaldvolume=0;
volatile int bright=0;
volatile int standbyb=0;
volatile int gorun=0;
volatile int chronostate=0;
volatile int isMainActivated=0;
volatile int currentled=0;
volatile int ledstatus=0;
volatile int isended=0;
volatile int chronotrigger=0;
volatile int setluxvalue=0;
volatile int lamp=0;
volatile int startb= 0;
volatile int msett = 0;
volatile int mhelp = 0;
volatile int sreset = 0;
volatile int shome = 0;
volatile int shelp = 0;
volatile int rstop = 0;
volatile int hhome = 0;
volatile int hsett = 0;
volatile int chome = 0;
volatile int csett = 0;
volatile int chelp = 0;
volatile int wback = 0;
volatile int wrun = 0;
volatile int whelp = 0;
volatile int dback = 0;
volatile int dhelp = 0;
volatile int eback = 0;
volatile int ehelp = 0;
volatile int esett = 0;
volatile int ynhome = 0;
volatile int ynhelp = 0;
volatile int ynyes = 0;
volatile int ynno = 0;
volatile int sthelp = 0;
volatile int stsett = 0;
volatile int rshome = 0;
volatile int rshelp = 0;
volatile int s2home=0;
volatile int s2help=0;
volatile int s2back=0;
volatile int down1=0;
volatile int down2=0;
volatile int down3=0;
volatile int up1=0;
volatile int up2=0;
volatile int up3=0;
volatile int nextarrow=0;


const int SD_CS = BUILTIN_SDCARD;
const int avgSamples = 10;

long setcurrentvalue=0;

float sensitivity = 500.0 / 500.0; 
float Vref = 1860; 


String myString="";
char datarcv;

String myString2="";
char datarcv2;

String myString3="";
char datarcv3;

String strings[6];

int tflag=0;
long standmillis=0;



int cuRead=1;
long varCurrent=0;


int Sensor0=41;


//int Buzzer=6;
int Buzzer=37;

//int lampy=9;
int lampy=39;

String CyclesQS="";
String  cCycleS="";
String limitCycS="";
String lcurrentRS="";
String uvReadingS="";
String st0,st1,st2,st3,st4,st5;


File myFile;
File myFile2;
File myFile3;

//////////////////////////////////////////////////////////////////////////////
//Timer Variables
/////////////////////////////////////////////////////////////////////////////
unsigned long Watch0, _micro0, time0 = micros();
unsigned int Clock0 = 0, R_clock0;
boolean Reset0 = false, Stop0 = false, Paused0 = false;
volatile boolean timeFlag0 = false;
int varS0=0;//Seconds turned on
int varM0=6;//Minutes turned on
/////////////////////////////////////////////////////////////////////////////
NexVariable storageset = NexVariable(10,7,"touchyStorage");

NexVariable voluming= NexVariable(11,15,"voluming");
NexVariable haloing= NexVariable(11,16,"haloing");

NexVariable varAttach= NexVariable(1,14,"va0");
NexVariable varLock= NexVariable(1,16,"va1");
NexVariable va2= NexVariable(1,3,"va2");
NexVariable varReady= NexVariable(1,18,"va3");

NexVariable Ready0 = NexVariable(0,6,"Ready0"); // Intro Screen States

NexTimer dReady = NexTimer(1,2,"tm0");//Advice
NexTimer timerP = NexTimer(1,13,"tm1");//Attach
NexTimer timerI = NexTimer(1,15,"tm2");//Secure


NexPicture pReady = NexPicture(1,1,"p0");//"System"
NexPicture mainPicture = NexPicture(1,7,"p1");//Main Picture
NexPicture pnotReady = NexPicture(1,8,"p2");//Message
NexPicture pReady2 = NexPicture(1,17,"p3");//"Ready"

NexPage introPage = NexPage(0,0,"Intro");
NexPage mainPage = NexPage(1,0,"Main");
NexPage settingsPage = NexPage(2,0,"Settings");
NexPage runningPage = NexPage(3,0,"Running");
NexPage helpPage = NexPage(4,0,"Help");
NexPage canceledPage = NexPage(5,0,"Canceled");
NexPage warningPage = NexPage(6,0,"Warning");
NexPage dangerPage = NexPage(7,0,"Danger");
NexPage endPage = NexPage(8,0,"End");
NexPage confirmationPage = NexPage(9,0,"AcceptDecline");
NexPage storagePage = NexPage(10,0,"Storage");
NexPage setting2Page = NexPage(11,0,"Settings2");
NexPage bootPage= NexPage(12,0,"Boot");
NexPage rSuccessPage= NexPage(13,0,"RSuccess");
NexPage standbyPage= NexPage(14,0,"Standby");
NexPage errorPage= NexPage(15,0,"ErrorSD");

////Running Variables
NexText timeText = NexText(3,1,"t0");  //Timestamp
////Settingas Variables

NexText dateText = NexText(2,8,"t4");  //dateStamp


NexText haloText = NexText(11,6,"haloText"); 
NexText audioText = NexText(11,7,"audioText"); 

NexText lampCyclesCurr = NexText(2,4,"t0");  //LampCycles Currently
NexText uvReading = NexText(2,5,"t1");   //Last UV Reading
NexText currentRead = NexText(2,6,"t2");   //Last Current Reading
NexText tCycles = NexText(2,7,"t3");   //Total Cycles



NexText redText = NexText(1,8,"redText"); 

int standstate=0;
NexButton b0 =NexButton(1,4,"b0");
NexButton msettb = NexButton(1,5,"msettb");
NexButton mhelpb = NexButton(1,6,"mhelpb");

NexButton sresetb =NexButton(2,1,"sresetb");
NexButton shomeb = NexButton(2,2,"shomeb");
NexButton shelpb = NexButton(2,3,"shelpb");


NexButton rstopb =NexButton(3,4,"rstopb");

NexButton hhomeb=NexButton(4,1,"hhomeb");
NexButton hsettb =NexButton(4,2,"hsettb");

NexButton chomeb = NexButton(5,1,"chomeb");
NexButton csettb =NexButton(5,3,"csettb");
NexButton chelpb = NexButton(5,4,"chelpb");

NexButton wbackb = NexButton(6,3,"wbackb");
NexButton wrunb =NexButton(6,5,"wrunb");
NexButton whelpb = NexButton(6,2,"whelpb");

NexButton dbackb = NexButton(7,3,"dbackb");
NexButton dhelpb = NexButton(7,2,"dhelpb");

NexButton ebackb = NexButton(8,1,"ebackb");
NexButton ehelpb = NexButton(8,2,"ehelpb");
NexButton esettb =NexButton(8,6,"esettb");

NexButton ynhomeb = NexButton(9,1,"ynhomeb");
NexButton ynhelpb = NexButton(9,2,"ynhelpb");
NexButton ynyesb = NexButton(9,3,"ynyesb");
NexButton ynnob = NexButton(9,4,"ynnob");

NexButton sthelpb = NexButton(10,2,"sthelpb");
NexButton stsettb = NexButton(10,3,"stsettb");

NexButton s2backb = NexButton(11,2,"s2backb");
NexButton s2homeb = NexButton(11,3,"s2homeb");
NexButton s2helpb = NexButton(11,4,"s2helpb");

NexButton down1b = NexButton(11,8,"down1");
NexButton down2b = NexButton(11,9,"down2");
NexButton down3b = NexButton(11,10,"down3");

NexButton up1b = NexButton(11,11,"up1");
NexButton up2b = NexButton(11,12,"up2");
NexButton up3b = NexButton(11,13,"up3");

NexButton nextarrowb = NexButton(2,12,"nextarrowb");



NexButton rshomeb = NexButton(13,2,"rshomeb");
NexButton rshelpb = NexButton(13,3,"rshelpb");





long smillis=0;


time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

#define TIME_HEADER  "T"   // Header tag for //SERIAl time sync message
unsigned long processSyncMessage()
{
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 13 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void nextarrowbPushCallback(void *ptr)
{
  nextarrow=1;
  isMainActivated=0;
}

void s2helpbPushCallback(void *ptr)
{
 s2help = 1;
 isMainActivated=0;

 
}

void s2homebPushCallback(void *ptr)
{
  laststatying=25;
statying=23;
  
 s2home = 1;
}


void s2backbPushCallback(void *ptr)
{
 s2back = 1;
 isMainActivated=0;
 
}

void buzz(int targetPin, long frequency, long length) 
{ 
 long delayValue = 1000000 / frequency / 2; 
 long numCycles = frequency * length / 1000;
 for (long i = 0; i < numCycles; i++) 
 { 
  double analoging = (double(dvolume)/100);
  analoging= analoging*255;
  analogWriteFrequency(targetPin,375000);
  analogWrite(targetPin,analoging);
  threads.delayMicroseconds(delayValue); 
  analogWrite(targetPin,0);
  threads.delayMicroseconds(delayValue); 
 }
}


void down1bPushCallback(void *ptr)
{
 down1 = 1;
 isMainActivated=0;
 buzz(Buzzer,400,100);
}

void down2bPushCallback(void *ptr)
{
 down2 = 1;
 isMainActivated=0;
 buzz(Buzzer,400,100);
}

void down3bPushCallback(void *ptr)
{
 down3 = 1;
 isMainActivated=0;
}
void up1bPushCallback(void *ptr)
{
 up1 = 1;
 isMainActivated=0;
 buzz(Buzzer,400,100);
}
void up2bPushCallback(void *ptr)
{
 up2 = 1;
 isMainActivated=0;
 buzz(Buzzer,400,100);
}

void up3bPushCallback(void *ptr)
{
 up3 = 1;
 isMainActivated=0;
}














void b0PushCallback(void *ptr)
{
 startb= 1; 
 if(chronotrigger==1)
 {
  if(currentCyclesQ<limitCyclesQ)
  {
   if(currentCyclesQ<(limitCyclesQ-50))
   {
    killer6=1;
    alloff();
    ////SERIAl.println("El asesino 6");
   } 
  
     else
    {
     warningPage.show();
     smillis=millis();
     ledstatus=6;
    }
   }
   else 
   {
    ledstatus=4;
    dangerPage.show();
    smillis=millis();
   }
  }
 }

void msettbPushCallback(void *ptr)
{
 ////SERIAl.println("Settings");
 msett = 1;
 isMainActivated=0;
 
}
void mhelpbPushCallback(void *ptr)
{
  mhelp = 1;
 isMainActivated=0;
}
void sresetbPushCallback(void *ptr)
{
 sreset = 1;
 isMainActivated=0;
}

void shomebPushCallback(void *ptr)
{
 shome = 1;
 isMainActivated=1;
}

void shelpbPushCallback(void *ptr)
{
 shelp = 1;
 isMainActivated=0;
}

void rstopbPushCallback(void *ptr)
{
 rstop = 1;
 isMainActivated=0;
}

void hhomebPushCallback(void *ptr)
{
 isMainActivated=1;
 hhome=1;
  laststatying=25;
  statying=23;
}

void hsettbPushCallback(void *ptr)
{
 hsett = 1;
 isMainActivated=0;
}

void chomebPushCallback(void *ptr)
{
  laststatying=25;
  statying=23;
  
 chome = 1;
}

void csettbPushCallback(void *ptr)
{
 csett = 1;
 isMainActivated=0;
}

void chelpbPushCallback(void *ptr)
{

 chelp = 1;
 isMainActivated=0;
}

void wbackbPushCallback(void *ptr)
{
 isMainActivated=1;
 wback = 1;
}

void wrunbPushCallback(void *ptr)
{
 
  ledstatus=1;

    SetTimer0(0, varM0, varS0);
    
    isMainActivated=0;
    
    runningPage.show();
    
    m0 = varM0;
    s0 = varS0;
    String m0S=String(m0);
    String s0S=String(s0);
    if (m0<10)
    {
     m0S="0"+m0S;
    }
    if (s0<10)
    {
     s0S="0"+s0S;
    }
    String taimu= m0S+":"+s0S;
    
    timeText.setText(taimu.c_str());//Start time printed on screen  
     
     
    StartTimer0();//Countdown timer will start
    
    checkingflag=0;

    pinMode(lampy,OUTPUT);
    digitalWrite(lampy,HIGH);//Lamp
    
    gorun=1;   
  
 wrun = 1;
 isMainActivated=0;
}

void whelpbPushCallback(void *ptr)
{
 whelp = 1;
 isMainActivated=0;
}

void dbackbPushCallback(void *ptr)
{
 isMainActivated=1;
 dback = 1;
}

void dhelpbPushCallback(void *ptr)
{
 dhelp = 1;
 isMainActivated=0;
}

void ebackbPushCallback(void *ptr)
{
 isMainActivated=1;
 eback = 1;
 
}

void ehelpbPushCallback(void *ptr)
{
 ehelp = 1;
 isMainActivated=0;
}

void esettbPushCallback(void *ptr)
{
 esett = 1;
 isMainActivated=0;
}

void ynhomebPushCallback(void *ptr)
{
   laststatying=25;
  statying=23;
 ynhome = 1;
 isMainActivated=1;
}

void ynhelpbPushCallback(void *ptr)
{
 ynhelp = 1;
 isMainActivated=0;
}

void ynyesbPushCallback(void *ptr)
{

 isMainActivated=0;
 ynyes = 1;
}

void ynnobPushCallback(void *ptr)
{
 ynno = 1;
 isMainActivated=0;
}

void sthelpbPushCallback(void *ptr)
{
  isMainActivated=0;
 sthelp = 1;
}

void stsettbPushCallback(void *ptr)
{
  isMainActivated=0;
 stsett = 1;
}

void rshomebPushCallback(void *ptr)
{
   laststatying=25;
  statying=23;
  isMainActivated=1;
 rshome = 1;
}

void rshelpbPushCallback(void *ptr)
{
  isMainActivated=0;
 rshelp = 1;
}

void standbyPagePushCallback(void *ptr)
{
  standbyb=1;
  isMainActivated=1;
}


NexTouch *nex_listen_list[] =
{
 &b0,
 &msettb,
 &mhelpb,
 &sresetb,
 &shomeb,
 &shelpb,
 &rstopb,
 &hhomeb,
 &hsettb,
 &chomeb,
 &csettb,
 &chelpb,
 &wbackb,
 &wrunb,
 &whelpb,
 &dbackb,
 &dhelpb,
 &ebackb,
 &ehelpb,
 &esettb,
 &ynhomeb,
 &ynhelpb,
 &ynyesb,
 &ynnob,
 &sthelpb,
 &stsettb,
 &rshomeb,
 &rshelpb,
 &standbyPage,
 &s2backb,
 &s2helpb,
 &s2homeb,
 &nextarrowb,
  &up1b,
 &down1b,
 &up2b,
 &down2b,
 &up3b,
 &down3b,
 NULL
};

NexVariable states0 = NexVariable(0,7,"States0"); // Intro Screen States
NexVariable states1 = NexVariable(1,12,"States1"); // Main Screen States
NexVariable states2 = NexVariable(2,10,"States2"); // Settings Screen States 
NexVariable states3 = NexVariable(3,5,"States3"); // Running Screen States
NexVariable states4 = NexVariable(4,4,"States4"); // Help Screen States
NexVariable states5 = NexVariable(5,2,"States5"); // Canceled Screen States
NexVariable states6 = NexVariable(6,1,"States6"); // Warning Screen States
NexVariable states7 = NexVariable(7,1,"States7"); // Danger Screen States
NexVariable states8 = NexVariable(8,4,"States8"); // End Screen States
NexVariable states9 = NexVariable(9,5,"States9"); // Confirmation Screen States
NexVariable states10 = NexVariable(10,4,"States10"); // Storage Screen States
NexVariable states11 = NexVariable(11,1,"States11"); //Unattached Screen States
NexVariable states12 = NexVariable(12,1,"States12"); // Boot Screen States
NexVariable states13 = NexVariable(13,1,"States13"); // Success States
NexVariable states14 = NexVariable(14,3,"States14"); // Standby States

void alloff()
{
digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
 
}

 void psensor0()
 {
  if ( !apds0.readProximity(proximity_data0) ) {
  //  //SERIAl.println("Error reading proximity value");
  }
  else {
    ////SERIAl.print("Proximity0: ");
   // //SERIAl.println(proximity_data0);
  }
 }

  void psensor1()
  {
   if ( !apds1.readProximity(proximity_data) ) 
   {
    ////SERIAl.println("Error reading proximity value");
   }
   else 
   {
    ////SERIAl.print("Proximity1: ");
    ////SERIAl.println(proximity_data);
  }
 }

void red()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);
      digitalWrite(2,HIGH);
   digitalWrite(23,LOW);
}

void green()
{
   digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
      digitalWrite(2,LOW);
   digitalWrite(23,HIGH);
}

void twenty()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,HIGH);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void nineteen()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,HIGH);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void eighteen()
{
  digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,HIGH);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void seventeen()
{
  digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,HIGH); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}


    
void sixteen()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,HIGH);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
} 



void fifteen()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,HIGH);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}



void fourteen()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,HIGH);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}
void thirteen()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,HIGH);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void twelve()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,HIGH);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}
void eleven()
{
digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,HIGH);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void ten()
{
digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,HIGH);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void nine()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,HIGH);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}
void eight()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,HIGH);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void seven()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,HIGH);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}
void six()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,HIGH);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}





void five()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,HIGH);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}



void four()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,HIGH);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void three()
{
 digitalWrite(32,LOW);
 digitalWrite(31,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void two()
{
 digitalWrite(32,LOW);
 digitalWrite(31,HIGH);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}

void one()
{
 digitalWrite(32,HIGH);
 digitalWrite(31,LOW);
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(14,LOW);
 digitalWrite(9,LOW);
 digitalWrite(8,LOW);
 digitalWrite(11,LOW);  
 digitalWrite(10,LOW);
 digitalWrite(15,LOW);
 digitalWrite(28,LOW);
 digitalWrite(29,LOW);
 digitalWrite(4,LOW);
 digitalWrite(7,LOW);   
 digitalWrite(6,LOW);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW); 
 digitalWrite(22,LOW);
 digitalWrite(1,LOW);
 digitalWrite(0,LOW);  
 digitalWrite(2,LOW);
 digitalWrite(23,LOW);
}
void (*ledfunctions[])(void) = {
one,
two,
three,
four,
five,
six,
seven,
eight,
nine,
ten,
eleven,
twelve,
thirteen,
fourteen,
fifteen,
sixteen,
seventeen,  
eighteen,
nineteen,
twenty,
};


  void startLedFunction()
  {
   for (int i=0; i<=19;i++) 
   {
    ledfunctions[i]();
    delay(35);
   } 
   for (int j=19; j>=0;j--)
   {
    ledfunctions[j]();
    delay(35);
   }
   alloff();
  }


bool blinking=false;

void runningLeds(int sm,int ss, int cm, int cs)
{
 int st=(sm*60)+ss;
 int ct=(cm*60)+cs;
 int tled=st-ct;
 float pled=float(tled)/float(st);
 int cled=int(pled*20);
 if(cled>19)
 {
  cled=19;
 }
 if(cled<0)
 {
  cled=0;
 }  
 if (currentled!=cled)
 {
  blinking=1;
  }
 currentled=cled;
 blinking=!blinking;  
}



void SetTimer0(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
 unsigned int _Sec = (seconds / 60), _M = (minutes / 60);
 if (_Sec) minutes += _Sec;
 if (_M) hours += _M;
 Clock0 = (hours * 3600) + (minutes * 60) + (seconds % 60);
 R_clock0 = Clock0;
 Stop0 = false;
}

void SetTimer0(unsigned int seconds)
{
 Clock0 = seconds;
 R_clock0 = Clock0;
 Stop0 = false;
}

int ShowHours0()
{
  return Clock0 / 3600;
}

int ShowMinutes0()
{
  return (Clock0 / 60) % 60;
}

int ShowSeconds0()
{
  return Clock0 % 60;
}

unsigned long ShowMilliSeconds0()
{
  return (_micro0 - Watch0) / 1000.0;
}

unsigned long ShowMicroSeconds0()
{
  return _micro0 - Watch0;
}

boolean TimeHasChanged0()
{
  return timeFlag0;
}

boolean CountDownTimer0()
{
 static unsigned long duration = 1000000;
 timeFlag0 = false;
 if (!Stop0 && !Paused0)
 {
  if ((_micro0 = micros()) - time0 > duration )
  {
   Clock0--;
   timeFlag0 = true;
   if (Clock0 == 0)
   Stop0 = true;
   _micro0 < time0 ? time0 = _micro0 : time0 += duration;
  }
 }
 return !Stop0; 
}

void StartTimer0()
{
 Watch0 = micros();
 time0 = micros();
 Stop0 = false;
 Paused0 = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readingSensor()
{
 lamp=analogRead(40);
 st4= String(lamp);
}


void readingcurrent()
{
 int lastSensorValue=0;
 for (int i = 0; i < avgSamples; i++)
 {
  lastSensorValue=analogRead(analogInPin);
  if(lastSensorValue>sensorValue)
  {
   sensorValue=lastSensorValue;
  } 
  threads.delay(2);
 }
 float voltage = 4.88 * sensorValue;
 float current = (voltage - Vref) * sensitivity;
 varCurrent=current;
 st3= String(varCurrent);
  sensorValue = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void listener()
{
 while(1)
 {
  nexLoop(nex_listen_list);
  threads.yield();
 }
}


int blinkeochingon=0;

void turningoff()
{
 while(1)
 {
  //if(digitalRead(Sensor0)==0||proximity_data<250||proximity_data0<250)
  //{
   //digitalWrite(lampy,LOW);
  //}
 //threads.yield();
 }  
}


int ledsflag=0;
int ledscounting=0;


void leds()
{
 while(1)
 {
  if(ledstatus==1)//blue
  {
        if(dbright==25)
    {
      bright=1000;
    }
    else if (dbright==50)
    {
      bright=500;
    }
     else if (dbright==75)
    {
      bright=100;
    }
     else if (dbright==100)
    {
      bright=1;
    }
    
   for (int i = 0; i<=19; i++)
   { 
    ledfunctions[i]();
    threads.delayMicroseconds(10);
   }
   alloff();
  
    threads.delayMicroseconds(bright);
   }
 

 else if(ledstatus==3)//Running
 {
  if (ledsflag==0)
  {
    ledsflag=1;
    ledscounting=0;
  }
  
  if(blinking)
  {
   for (int i=0;i<currentled+1;i++)
   {
    ledfunctions[i]();
    threads.delayMicroseconds(900);
   }   
  }
  else
  {
   int k=currentled-1;
   if(k<0)
   {
    alloff(); 
   }
   else
   { 
    for (int i=0;i<k+1;i++)
    {
     ledfunctions[i]();  
     threads.delayMicroseconds(900);
    }
   }  
  }
 
 }

  else if(ledstatus==4)//Red
 {
  if(dbright==25)
  {
   bright=150;
  }
  else if (dbright==50)
  {
   bright=100;
  }
  else if (dbright==75)
  {
   bright=50;
  }
  else if (dbright==100)
  {
      bright=1;
    }
    
  red();
   threads.delayMicroseconds(1);
   alloff();
   threads.delayMicroseconds(bright);
 }

 else if(ledstatus==5)
 {
  alloff();
 }

   else if(ledstatus==6)
 {
   if(dbright==25)
    {
      bright=1000;
    }
    else if (dbright==50)
    {
      bright=500;
    }
     else if (dbright==75)
    {
      bright=100;
    }
     else if (dbright==100)
    {
      bright=1;
    }
  yellow();
  }

  
  else if(ledstatus==8)//Green
 {
  green();
  /*if(dbright==25)
  {
   bright=150;
  }
  else if (dbright==50)
    {
      bright=100;
    }
     else if (dbright==75)
    {
      bright=60;
    }
     else if (dbright==100)
    {
      bright=1;
    }
    green();
   threads.delayMicroseconds(1);
   alloff();
   threads.delayMicroseconds(bright);*/
 }

  else if (ledstatus==9)//Orange
  {
   if(dbright==25)
   {
    bright=1000;
   }
   else if (dbright==50)
   {
    bright=500;
   }
   else if (dbright==75)
   {
    bright=100;
   }
   else if (dbright==100)
    {
      bright=1;
    }
    
    orange();
  }
   if (ledstatus!=3)
 {
  ledsflag=0;
  currentled=0;
  blinking=0;
 }

  
  threads.yield();
 }
}









void chronos()
{
  while(1)
  {
    
    switch(chronostate)
    {
      case 0:
      {
       chronostate=gorun;
      }
      break;

      case 1:
      {
        isMainActivated=0;

       if(chronotrigger==1) 
       {  
        ledstatus=3;
        CountDownTimer0();
        if (TimeHasChanged0())//If time has changed from the last loop, time text in screen will be refreshed 
        {
         m0 = int(ShowMinutes0());//get current running minutes 
         s0 = int(ShowSeconds0());//get current running seconds
      
         String m0S=String(m0,DEC);//As m0 is not a string, needs to be changed 
         String s0S=String(s0,DEC);//As s0 is not a string, needs to be changed
      
        if (m0<10)//Add a zero before minutes number if this is only one digit
        {
         m0S=String("0"+m0S);//Concatenate a 0 to minutes String variable
        }
      
        if (s0<10)//Add a zero before seconds number if this is only one digit
       {
        s0S=String("0"+s0S);//Concatenate a 0 to seconds String variable
        }
      
        String taimu= String(m0S+":"+s0S); //Concatenate minutes and seconds
       ////SERIAl.print("lamp");
       ////SERIAl.println(lamp);
         st4= String(lamp);
        readingcurrent();
      
   
      
      timeText.setText(taimu.c_str()); //Prints time on Nextion screen
         
       if (checkingflag==0)
       {
        if (s0<=50)
        {
         checkingflag=1;
        }
       }
       else  
      { 
        Serial.println(lamp);
        Serial.println(setluxvalue);
        Serial.println(varCurrent);
        Serial.println(setcurrentvalue);
       if (lamp>setluxvalue&&varCurrent>setcurrentvalue) 
       {
    
       }
       else 
       {  

        if(lamp<setluxvalue)
        {
          ////SERIAl.println("la luz");
          //
          ////SERIAl.print("valor de lectura");
          //SERIAl.println(lamp);
          //SERIAl.print("Valor seteado");
          //SERIAl.println(setluxvalue);
         }
        if(varCurrent<setcurrentvalue)
        {
          
        }
          
        ledstatus=4;
        digitalWrite(lampy,LOW);
        Stop0=true;
        gorun=0;
        chronotrigger=0;
       /* //SERIAl.println(setluxvalue);
        //SERIAl.print("Luz");
        //SERIAl.println(lamp);
        //SERIAl.println(setcurrentvalue);
        //SERIAl.print("Corriente");
        //SERIAl.println(varCurrent);
        //SERIAl.print("lo detuvo la lectura de los valores");*/
        chronostate=0;
        smillis=millis();
        dangerPage.show();
      } 
     }
        
     runningLeds(varM0,varS0,m0,s0);
       
     if (s0 == 0 && m0 == 0)//When time's up
     {
      alloff();
      killer3=1;
      break;
     }
    } 
   }
     
   else 
   {
  /*  //SERIAl.print("Chronotrigger ");
    //SERIAl.println(chronotrigger);
    //SERIAl.println("me detuve por el chronotrigger");*/
    digitalWrite(lampy,LOW);
    Stop0=true;
    ledstatus=4;
    gorun=0;
    chronotrigger=0;
    chronostate=0;
    isended=0; 
    smillis=millis();
    canceledPage.show();
    laststatying=25;
    statying=23;
    buzz(Buzzer,150,200);
    threads.delay(100);
    buzz(Buzzer,150,200); 
   }
  }
      
      
      
    }
    if(isended==1)
    {
      digitalWrite(lampy,LOW); 
      ledstatus=8;
    }
   threads.yield();     
  }
 }

volatile int blackstatus=0;
long cmillis=0; 


void blacking()
{
 while(1)
 {
  switch(blackstatus)
  {
   case 0:
   {
    cmillis=millis()-smillis;
    if(cmillis>=3000000&&gorun==0)
    {
     isMainActivated=0;
     blackstatus=1;
     standbyPage.show();  
    } 
   }
   break;
   
   case 1:
   {
    if(standbyb==1)
    {
     blackstatus=0;
     smillis=millis();
     mainPage.show();
     standbyb=0;
     isended=0;
     gorun=0; 
     ynhome=0;
     chome =0;
     hhome=0;
     shome=0;
     rshome=0;
     wback = 0;
     dback = 0;
     eback = 0;
    }
   }
   break;
  }
  threads.yield();
 }
} 

void threadsCreator()
{ 
 threads.setMicroTimer(1);
 id1 = threads.addThread(turningoff);
 id2 = threads.addThread(leds);
 id3 = threads.addThread(mainthread);
 id4 = threads.addThread(locking);
 id5 = threads.addThread(chronos);
 id6 = threads.addThread(listener);
 id7 = threads.addThread(blacking);
}


void yellow()
{
 red();
 threads.delayMicroseconds(65);
 green();
 threads.delayMicroseconds(35);
 alloff();
 threads.delayMicroseconds(bright);
}

void orange()
{

 red();
 threads.delayMicroseconds(50);
 green();
 threads.delayMicroseconds(1);  
 alloff();
 threads.delayMicroseconds(bright);
}










void locking()
{
 while(1)
 {

  psensor0();
  psensor1();
  
  s2=proximity_data;  
  s3=proximity_data0;
  pinMode(41,INPUT);
  
  lamp=analogRead(40);
  s1=digitalRead(41);
    /*  Serial.println(s2);
    Serial.println(s3);
    Serial.println(isMainActivated);*/
 
  if(isMainActivated==1)
  {

       
    if(s1==0&&s2>=255&&s3>=255)//Ready
    {
     statying=1;
     chronotrigger=1;
     //isMainActivated=1;
    }
    
    else if(s1==1&&s2>=255&&s3>=255)//Lock
    {
     digitalWrite(lampy,LOW);
     statying=2;
     ledstatus=9;
     chronotrigger=0;
     //isMainActivated=1;
    }
  
    else if((s1==1&&s2<255&&s3>=255)||(s1==1&&s2<255&&s3<255)||(s1==1&&s2>=255&&s3<255)||(s1==0&&s2<255&&s3<255)||(s1==0&&s2>=255&&s3<255)||(s1==0&&s2<255&&s3>=255))//Attach
    {
     ledstatus=9;
     digitalWrite(lampy,LOW);
     statying=3;
     chronotrigger=0;
    // isMainActivated=1;
    }
    
   if(laststatying!=statying)
   {
   // killer7=1;
    smillis=millis();

     switch(statying)
    {
     case 0:
    {
    
  }
  break;
   case 1:
  {
   ledstatus=1;
   timerI.disable();
   timerP.disable();
   dReady.enable();
   pReady2.setPic(109);
   pReady.setPic(110);
   mainPicture.setPic(39);
   b0.Set_background_image_pic(106);
   b0.Set_press_background_image_pic2(106);
   varAttach.setValue(33);
   varLock.setValue(41);
   isMainActivated=1;
  }
  break;
   case 2://Lock
  {
   ledstatus =9;
   pReady.setPic(119);//Picture Ready 
   pReady2.setPic(116);//Picture Ready
   varReady.setValue(106);//Variable Ready button play var3
   va2.setValue(111);//Variable Picture Ready va2         
   b0.Set_background_image_pic(104);
   b0.Set_press_background_image_pic2(104);
   dReady.disable();//Timer Ready
   timerP.disable();//Timer Unattached Reset
   timerI.enable();//Timer Unlocked 
   pnotReady.setPic(118);//
   varAttach.setValue(33);//va0
   isMainActivated=1;
  }
  break;
   case 3://attach
  {
   
   pReady.setPic(119);//Picture Ready 
   pReady2.setPic(116);//Picture Ready
   varReady.setValue(106);//Variable Ready button play var3
   va2.setValue(111);//Variable Picture Ready va2         
   b0.Set_background_image_pic(104);
   b0.Set_press_background_image_pic2(104);
   dReady.disable();//Timer Ready
   timerI.disable();//Secure Timer
   pnotReady.setPic(117);//Attach device Message
   varLock.setValue(41);//Locked Variable Reset
   timerP.enable();
   ledstatus=9;
   isMainActivated=1;
  }
  break;
 }
  laststatying=statying;
}


 
  
}
else 
{

  
  if(s1==0&&s2>=255&&s3>=255)
  {
    chronotrigger=1;
  }
  else
  {
  // digitalWrite(lampy,LOW);
   chronotrigger=0;
  }
    laststatying=25;
  
  statying=23;
  }
  threads.yield();
  }
}





void mainthread()
{

  while(1)
  {

    
  if(startb==1||wrun==1)//running page
  { 
   wrun=0;
   startb=0;
   
  }

else if(msett==1||hsett==1||csett==1||esett==1||stsett==1||ynno==1||s2back==1)//settings page
{
  
 if(s2back==1) 
 {
  killer4=1; 
 }
 else
 {
  smillis=millis();
  isended=0;
  gorun=0;
  ledstatus=1;
    
  laststatying=25;
  statying=23;
  settingsPage.show();
  ////SERIAl.println("Settings");
  tCycles.setText(st0.c_str());  
  lampCyclesCurr.setText((st1+"/"+st2).c_str());
  int currentint=0;
  float currentfloat=0;
  currentint= st3.toInt();
  currentfloat = float(currentint)/1000;
  st3=String(currentfloat);
  currentRead.setText(st3.c_str());
  uvReading.setText(st4.c_str());   
  dateText.setText(st5.c_str());   

  stsett=0;
  esett=0;
  csett=0;
  hsett=0;
  msett=0;
  ynno=0;
  s2back=0;
 }

 
}


 
else if (mhelp==1||shelp==1||chelp ==1||whelp==1||dhelp ==1||ehelp==1||sthelp==1||rshelp==1||ynhelp==1||s2help==1)//help Page
{
  
 if(s2help==1)
 {
  killer5=1;
 }
 else
 {
  smillis=millis();
 isended=0;
 ledstatus=1;
    
 gorun=0;
 
 ynhelp=0;
 rshelp=0;
 sthelp=0;
 ehelp=0;
 dhelp =0;
 whelp=0;
 chelp =0;
 shelp = 0;
 mhelp = 0;
 
 helpPage.show();
 s2help = 0;
 }
 
}

else if (shome==1||hhome==1||chome==1||ynhome==1||rshome==1||wback==1||dback==1||eback==1||s2home==1)//home page
{
 if(s2home==1)
 {
   killer2=1;
   laststatying=25;
   statying=23;
 }
 else 
 {
  laststatying=25;
  statying=23;
  isended=0;
  ledstatus=1;
   
  smillis=millis();
  gorun=0;
  ynhome=0;
  chome =0;
  hhome=0;
  shome=0;
  rshome=0;
  wback = 0;
  dback = 0;
  eback = 0;
  s2home = 0; 
  
  threads.delay(20);
  mainPage.show();  
  statying=23;
  isMainActivated=1;
  threads.kill(id4);
  id4 = threads.addThread(locking);
 }

}

else if (sreset==1)
{
 gorun=0;
 sreset=0;
 smillis=millis();
 confirmationPage.show();
}

else if(ynyes==1)
{

  killer=1;
 
}




else if(rstop==1)
{
 digitalWrite(lampy,LOW);
 smillis=millis();
 gorun=0;
 
 laststatying=25;
  statying=23;
 canceledPage.show();
 chronotrigger=0;
// //SERIAl.println("lo detuvo el boton de stop");
 chronostate=0;
 buzz(Buzzer,150,200);
 threads.delay(100);
 buzz(Buzzer,150,200); 
 ledstatus=4;
 Stop0=true;
 rstop=0;
}

  else if(nextarrow==1)
{
  setting2Page.show();
  haloing.setValue(dbright);
  voluming.setValue(dvolume);
  haloText.setText((String(dbright)+"%").c_str()); 
  audioText.setText((String(dvolume)+"%").c_str()); 
  temporaldbright=dbright;
  temporaldvolume=dvolume;
  nextarrow=0;
  smillis=millis();
}

  else if(down2==1)
  {
   int tempdbright=dbright;
   tempdbright=tempdbright-25;
   if(tempdbright<25)
   {
    dbright=25;
   }
   else 
   {
    dbright=tempdbright;
   }
   down2=0;
  }
  
  else if(up2==1)
  {

   int tempdbright=dbright;
   tempdbright=tempdbright+25;
   if(tempdbright>100)
   {
    dbright=100;
   }
   else 
   {
    dbright=tempdbright;
   }
   up2=0;
  }





  else if(down3==1)
  {
   int tempdvolume=dvolume;
   tempdvolume=tempdvolume-25;
   if(tempdvolume<25)
   {
    dvolume=25;
   }
   else 
   {
    dvolume=tempdvolume;
   }
   down3=0;
   buzz(Buzzer,2500,200);
   buzz(Buzzer,3000,200); 
  }
  
  else if(up3==1)
  {
   int tempdvolume=dvolume;
   tempdvolume=tempdvolume+25;
   if(tempdvolume>100)
   {
    dvolume=100;
   }
   else 
   {
    dvolume=tempdvolume;
   }
   up3=0;
   buzz(Buzzer,2500,200);
   buzz(Buzzer,3000,200); 
  }















threads.yield();
}
}


void loop()
{

 

 if (killer==1)
 {
  threads.kill(id1);
  threads.kill(id2);
  threads.kill(id3);
  threads.kill(id4);
  threads.kill(id5);
  threads.kill(id6);
  threads.kill(id7);
  
  smillis=millis();
  gorun=0;
  String myString = "";   
    ynyes=0;
  
  myFile = SD.open("CQTY.txt");
  
  if (myFile) 
  {
   while (myFile.available()) 
   {
    datarcv=myFile.read();
    myString.concat(datarcv);
   }
   for (int i = 0; i <=4 ; i++)
   {  
    strings[i]= myString.substring(0,myString.indexOf("|"));
    myString= myString.substring(myString.indexOf("|")+1);
   }
   strings[5]=myString.substring(0,myString.indexOf("|"));
       
    myFile.close();
    SD.remove("cqty.txt");
    myFile=SD.open("cqty.txt",FILE_WRITE);
    String dataString=strings[0]+"|"+String(0)+"|"+strings[2]+"|"+strings[3]+"|"+strings[4]+"|"+strings[5]+"|";
    myFile.println(dataString);
    myFile.close();
    currentCyclesQ=0;
   
    st0=strings[0];
    st1=String(0);
    st2=strings[2];
    st3=strings[3];
    st4=strings[4];
    st5= myString.substring(0,myString.indexOf("|"));
    rSuccessPage.show();
   }  
   else
   {
    ledstatus=4;
    errorPage.show();
    while(1)
    {
     }
   }
  killer=0; 
  id1 = threads.addThread(turningoff);
 id2 = threads.addThread(leds);
 id3 = threads.addThread(mainthread);
 id4 = threads.addThread(locking);
 id5 = threads.addThread(chronos);
 id6 = threads.addThread(listener);
 id7 = threads.addThread(blacking);
 }




 
 if(killer2==1)
 {
  threads.kill(id1);
  threads.kill(id2);
  threads.kill(id3 );
  threads.kill(id4);
  threads.kill(id5);
  threads.kill(id6);
  threads.kill(id7);
  
   if(s2home==1)
   {
    
   uint32_t haloshi=0;   
   haloing.getValue(&haloshi);
   ////SERIAl.println(haloshi);
   if(haloshi==temporaldbright)
   {
    dbright=temporaldbright;
  
   }
   else 
   {
   
    SD.remove("h.txt");
    myFile=SD.open("h.txt",FILE_WRITE);
    myFile.println(String(haloshi));
    myFile.close();
    dbright=(String(haloshi)).toInt();
   }



   
  uint32_t audioshi=0;   
  voluming.getValue(&audioshi);
  if(audioshi==temporaldvolume)
  {
    dvolume=temporaldvolume;
  }
  else 
  {
   SD.remove("v.txt");
   myFile2=SD.open("v.txt",FILE_WRITE);
   myFile2.println(String(audioshi));
   myFile2.close();
   dvolume=(String(audioshi)).toInt();
  }
 
   
 }
 
 killer2=0; 
 
 statying=25;
 laststatying=23;

 
  isended=0;
 ledstatus=1;
    
 smillis=millis();
 gorun=0;
 ynhome=0;
 chome =0;
 hhome=0;
 shome=0;
 rshome=0;
 wback = 0;
 dback = 0;
 eback = 0;
 s2home = 0; 
 isMainActivated=1;
 delay(20);
 mainPage.show(); 

 id1 = threads.addThread(turningoff);
 id2 = threads.addThread(leds);
 id3 = threads.addThread(mainthread);
 id4 = threads.addThread(locking);
 id5 = threads.addThread(chronos);
 id6 = threads.addThread(listener);
 id7 = threads.addThread(blacking);
 
 }


 if (killer3==1)
 {
  digitalWrite(lampy,LOW);
  ledstatus=8;
 
    green();
  threads.kill(id1);
  threads.kill(id2);
  threads.kill(id3 );
  threads.kill(id4);
  threads.kill(id5);
  threads.kill(id6);
  threads.kill(id7);
 
        
      smillis=millis();
      isended=1; 
      gorun=0;
      chronotrigger=0;    
      chronostate=0;
      
      endPage.show();
      buzz(Buzzer,450,500);
      threads.delay(100);
      buzz(Buzzer,450,500);
      threads.delay(100); 
      buzz(Buzzer,450,500);
      
      ledstatus=8;
    
      String myString = "";   
      myFile = SD.open("cqty.txt");
      if (myFile) 
      {
       while (myFile.available()) 
       {
        datarcv=myFile.read();
        myString.concat(datarcv);
       }
       for (int i = 0; i <=4 ; i++)
       {  
        strings[i]= myString.substring(0,myString.indexOf("|"));
        myString= myString.substring(myString.indexOf("|")+1);
       }

       myFile.close();
       SD.remove("cqty.txt");
       
       time_t t = processSyncMessage();
        if (t != 0)
        {
         Teensy3Clock.set(t); // set the RTC
         setTime(t);
        }
       String Month="";
       String Day="";   



      if(String(day())<10)
       {
        Day="0"+String(day());
       }
       else 
       {
        Day=String(day());
       }
            
       if(String(month())<10)
       {
        Month="0"+String(month());
       }
       else 
       {
        
        Month=String(month());
       }
           
       String dateS=Month+"/"+Day+"/"+String(year())+"    "+ String(hour())+":"+String(minute())+":"+String(second());

       
       myFile=SD.open("cqty.txt",FILE_WRITE);
       String dataString=String(strings[0].toInt()+1)+"|"+String(strings[1].toInt()+1)+"|"+strings[2]+"|"+String(varCurrent) +"|"+String(lamp)+"|"+dateS+"|";
       myFile.println(dataString);
       myFile.close();
       currentCyclesQ=strings[1].toInt()+1;

       st0= String(strings[0].toInt()+1);
       st1= String(currentCyclesQ);
       st2= strings[2];
       st3= String(varCurrent);
       st4= String(lamp);
       
       st5= dateS;
       gorun=0;
       smillis=millis();
      }
      else
      {
       ledstatus=4;
       errorPage.show();
       while(1)
       {
        red();
        digitalWrite(lampy,LOW);
       }  
      } 
      
      smillis=millis();

 id1 = threads.addThread(turningoff);
 id2 = threads.addThread(leds);
 id3 = threads.addThread(mainthread);
 id4 = threads.addThread(locking);
 id5 = threads.addThread(chronos);
 id6 = threads.addThread(listener);
 id7 = threads.addThread(blacking);
ledstatus=8;
  killer3=0;
  
  }

  if(killer4==1)
  {
   threads.kill(id1);
   threads.kill(id2);
   threads.kill(id3 );
   threads.kill(id4);
   threads.kill(id5);
   threads.kill(id6);
   threads.kill(id7);
   uint32_t haloshi=0;   
   haloing.getValue(&haloshi);
 
   if(haloshi==temporaldbright)
   {
    dbright=temporaldbright;
   }
   else 
   {
    SD.remove("h.txt");
    myFile=SD.open("h.txt",FILE_WRITE);
    myFile.println(String(haloshi));
    myFile.close();
    dbright=(String(haloshi)).toInt();
   }


  uint32_t audioshi=0;   
  voluming.getValue(&audioshi);
  if(audioshi==temporaldvolume)
  {
    
  }
  else 
  {
   SD.remove("v.txt");
   myFile=SD.open("v.txt",FILE_WRITE);
   myFile.println(String(audioshi));
   myFile.close();
   dvolume=(String(audioshi)).toInt();
  }


   smillis=millis();
  isended=0;
  gorun=0;
  ledstatus=1;
    

   laststatying=25;
 statying=23;
 settingsPage.show();
 
 tCycles.setText(st0.c_str());  
 lampCyclesCurr.setText((st1+"/"+st2).c_str());

 int currentint=0;
 float currentfloat=0;
 currentint= st3.toInt();
 currentfloat = float(currentint)/1000;
 st3=String(currentfloat);
 
 currentRead.setText(st3.c_str());
 uvReading.setText(st4.c_str());   
 dateText.setText(st5.c_str());   

 stsett=0;
 esett=0;
 csett=0;
 hsett=0;
 msett=0;
 ynno=0;
 s2back=0;
   id1 = threads.addThread(turningoff);
   id2 = threads.addThread(leds);
   id3 = threads.addThread(mainthread);
   id4 = threads.addThread(locking);
   id5 = threads.addThread(chronos);
   id6 = threads.addThread(listener);
   id7 = threads.addThread(blacking);

   killer4=0;
  }

  if(killer5==1)
  {
   killer5=0;
   threads.kill(id1);
   threads.kill(id2);
   threads.kill(id3 );
   threads.kill(id4);
   threads.kill(id5);
   threads.kill(id6);
   threads.kill(id7);
   
   uint32_t haloshi=0;   
   haloing.getValue(&haloshi);
   if(haloshi==temporaldbright)
   {
    dbright=temporaldbright;
   }
   else 
   {
     
    SD.remove("h.txt");
    myFile=SD.open("h.txt",FILE_WRITE);
    myFile.println(String(haloshi));
    myFile.close();
    dbright=(String(haloshi)).toInt();
 }

 
 uint32_t audioshi=0;   
 voluming.getValue(&audioshi);
 if(audioshi==temporaldvolume)
  {
    
  }
  else 
  {
   SD.remove("v.txt");
   myFile=SD.open("v.txt",FILE_WRITE);
   myFile.println(String(audioshi));
   myFile.close();
   dvolume=(String(audioshi)).toInt();
 }


 
     smillis=millis();
 isended=0;
 ledstatus=1;
    
 gorun=0;
 
 ynhelp=0;
 rshelp=0;
 sthelp=0;
 ehelp=0;
 dhelp =0;
 whelp=0;
 chelp =0;
 shelp = 0;
 mhelp = 0;
 
 helpPage.show();
 s2help = 0;
   id1 = threads.addThread(turningoff);
   id2 = threads.addThread(leds);
   id3 = threads.addThread(mainthread);
   id4 = threads.addThread(locking);
   id5 = threads.addThread(chronos);
   id6 = threads.addThread(listener);
   id7 = threads.addThread(blacking);
  }

  if(killer6==1)
  {
   killer6=0;
   
   threads.kill(id1);
   threads.kill(id2);
   threads.kill(id3 );
   threads.kill(id4);
   threads.kill(id5);
   threads.kill(id6);
   threads.kill(id7);
    
    SetTimer0(0, varM0, varS0);
    
    isMainActivated=0;
    

 runningPage.show();
    
    m0 = varM0;
    s0 = varS0;
    String m0S=String(m0);
    String s0S=String(s0);
    if (m0<10)
    {
     m0S="0"+m0S;
    }
    if (s0<10)
    {
     s0S="0"+s0S;
    }
    String taimu= m0S+":"+s0S;
    
    timeText.setText(taimu.c_str());//Start time printed on screen  
     
     
    StartTimer0();//Countdown timer will start
    
    checkingflag=0;


  //readingsensor();
   
   readingcurrent();
  
   setcurrentvalue=varCurrent;
   varCurrent=0;

   
   
   int runninglux=0;
   
   for (int i = 0; i < 25; i++)
   {//
    runninglux=analogRead(40);
    if(runninglux>setluxvalue)
    {
     setluxvalue=runninglux;
    }     
    threads.delay(2);
   }
    
    digitalWrite(lampy,HIGH);//Lamp
    
    gorun=1;   
      id1 = threads.addThread(turningoff);
   id2 = threads.addThread(leds);
   id3 = threads.addThread(mainthread);
   id4 = threads.addThread(locking);
   id5 = threads.addThread(chronos);
   id6 = threads.addThread(listener);
   id7 = threads.addThread(blacking);
   digitalWrite(lampy,HIGH);
   }


   

 


 
}
 
 






void setup() 
{
 pinMode(analogInPin,INPUT);
 pinMode(20,INPUT);
 pinMode(21,INPUT);
 pinMode(40,INPUT);
  pinMode(0,OUTPUT);
 pinMode(1,OUTPUT);
  pinMode(23,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(29,OUTPUT);
 pinMode(28,OUTPUT);
 pinMode(2,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
    pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
 
 pinMode(23,OUTPUT);
 pinMode(2,OUTPUT);
  
  
  


  nexInit();
  if(apds0.init())
  {
    
  } else
  {
    
  }

  // Start running the apds1-9960 proximity sensor (no interrupts)
  // Settings to defaults
  if ( apds0.enableProximitySensor(false) ) {
    ////SERIAl.println(F("Proximity sensor is now running"));
  } else {
    ////SERIAl.println(F("Something went wrong during sensor init!"));
  }

  // Adjust the Proximity sensor gain
  if ( !apds0.setProximityGain(0) ) {
    ////SERIAl.println(F("Something went wrong trying to set PGAIN"));
  } 

  
 if ( apds1.init() ) {
    ////SERIAl.println(F("apds1-9960 initialization complete"));
  } else {
    ////SERIAl.println(F("Something went wrong during apds1-9960 init!"));
  }

  // Start running the apds1-9960 proximity sensor (no interrupts)
  // Settings to defaults
  if ( apds1.enableProximitySensor(false) ) {
    ////SERIAl.println(F("Proximity sensor is now running"));
  } else {
    ////SERIAl.println(F("Something went wrong during sensor init!"));
  }

  // Adjust the Proximity sensor gain
  if ( !apds1.setProximityGain(0) ) {
    ////SERIAl.println(F("Something went wrong trying to set PGAIN"));
  } 
 
 
   setSyncProvider(getTeensy3Time);
   if (timeStatus()!= timeSet)
   {
    // //SERIAl.println("time not set");
   }
    else 
    {
      ////SERIAl.println("time set");
    }
      if (timeStatus()!= timeSet) {
    ////SERIAl.println("Unable to sync with the RTC");
  } else {
    ////SERIAl.println("RTC has set the system time");
  }
    
 s2helpb.attachPush(s2helpbPushCallback,&s2helpb);
 s2homeb.attachPush(s2homebPushCallback,&s2homeb);
 s2backb.attachPush(s2backbPushCallback,&s2backb);
 
 down1b.attachPush(down1bPushCallback,&down1b);
 down2b.attachPush(down2bPushCallback,&down2b);
 down3b.attachPush(down3bPushCallback,&down3b);
 
 up1b.attachPush(up1bPushCallback,&up1b);
 up2b.attachPush(up2bPushCallback,&up2b);
 up3b.attachPush(up3bPushCallback,&up3b);
 
 nextarrowb.attachPush(nextarrowbPushCallback,&nextarrowb);
 
 b0.attachPush(b0PushCallback,&b0);
 msettb.attachPush(msettbPushCallback,&msettb);
 mhelpb.attachPush(mhelpbPushCallback,&mhelpb);
 sresetb.attachPush(sresetbPushCallback,&sresetb);
 shomeb.attachPush(shomebPushCallback,&shomeb);
 shelpb.attachPush(shelpbPushCallback,&shelpb);
 rstopb.attachPush(rstopbPushCallback,&rstopb);
 hhomeb.attachPush(hhomebPushCallback,&hhomeb);
 hsettb.attachPush(hsettbPushCallback,&hsettb);
 chomeb.attachPush(chomebPushCallback,&chomeb);
 csettb.attachPush(csettbPushCallback,&csettb);
 chelpb.attachPush(chelpbPushCallback,&chelpb);
 wbackb.attachPush(wbackbPushCallback,&wbackb);
 wrunb.attachPush(wrunbPushCallback,&wrunb);
 whelpb.attachPush(whelpbPushCallback,&whelpb);
 dbackb.attachPush(dbackbPushCallback,&dbackb);
 dhelpb.attachPush(dhelpbPushCallback,&dhelpb);
 ebackb.attachPush(ebackbPushCallback,&ebackb);
 ehelpb.attachPush(ehelpbPushCallback,&ehelpb);
 esettb.attachPush(esettbPushCallback,&esettb);
 ynhomeb.attachPush(ynhomebPushCallback,&ynhomeb);
 ynhelpb.attachPush(ynhelpbPushCallback,&ynhelpb);
 ynyesb.attachPush(ynyesbPushCallback,&ynyesb);
 ynnob.attachPush(ynnobPushCallback,&ynnob);
 sthelpb.attachPush(sthelpbPushCallback,&sthelpb);
 stsettb.attachPush(stsettbPushCallback,&stsettb);
 rshomeb.attachPush(rshomebPushCallback,&rshomeb);
 rshelpb.attachPush(rshelpbPushCallback,&rshelpb); 
 standbyPage.attachPush(standbyPagePushCallback,&standbyPage);


 if (!SD.begin(SD_CS)) 
 {
  delay(50);
  if(!SD.begin(SD_CS))
  {
    delay(50);
    if(!SD.begin(SD_CS))
    {
     ledstatus=4;
     errorPage.show();
     while(1)
     {
      
     }
   }
  }  
 }

 
 SPI.setClockDivider(SPI_CLOCK_DIV2); 
 
 String myString = "";  
  

 myFile = SD.open("CQTY.txt");
 if (myFile) 
 {
  ////SERIAl.println("File exist");
  while (myFile.available()) 
  {
   datarcv=myFile.read();
   myString.concat(datarcv);
  }
   
  for (int i=0;i<=4;i++)
  {  
   strings[i]= myString.substring(0,myString.indexOf("|"));
   
   myString= myString.substring(myString.indexOf("|")+1);
  }
  myFile.close();
 }
 else
 {
  
  ledstatus=4;
  errorPage.show();
   myFile.close();
  while(1)
  {
      
  }
 }


 st0=strings[0];
 st1=strings[1];
 st2=strings[2];
 st3=strings[3];
 st4=strings[4];
 strings[5]= myString.substring(0,myString.indexOf("|"));
 st5=strings[5];
 ////SERIAl.println(st5);
 currentCyclesQ=strings[1].toInt();
 limitCyclesQ=strings[2].toInt();

 myFile2 = SD.open("h.txt");
 if (myFile2) 
 {
  while (myFile2.available()) 
  {
   datarcv2=myFile2.read();
   myString2.concat(datarcv2);
  }
 }
 myFile2.close();
 
 dbright=myString2.toInt();
 
 myFile3 = SD.open("v.txt");
 if (myFile3) 
 {
  while (myFile3.available()) 
  {
   datarcv3=myFile3.read();
   myString3.concat(datarcv3);
  }
 }
 myFile3.close();
 dvolume=myString3.toInt();
 
 pinMode(Buzzer,OUTPUT);
 
 buzz(Buzzer,2500,200);
 buzz(Buzzer,3000,200); 
 buzz(Buzzer,3500,200);
 buzz(Buzzer,4000,200);
 ////SERIAl.print(dvolume);
 startLedFunction();
 
 
 pinMode(Sensor0,INPUT);
 pinMode(lampy,OUTPUT);
 pinMode(UVOUT, INPUT);
 pinMode(cuRead,INPUT);
 digitalWrite(lampy,LOW);
 digitalWrite(Buzzer,LOW); 


  uint32_t introReady=0;
    
  while(introReady==0)
  {
   Ready0.getValue(&introReady);  
  } 

  mainPage.show();
  smillis=millis();   
  threadsCreator();
  isMainActivated=1;
 pinMode(0,OUTPUT);
 pinMode(1,OUTPUT);
}
