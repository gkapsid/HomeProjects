//tested 3/3/21 ok!
#include <HITIComm.h> //used for timer, can be replaced by Ticker or a similar library

HC_Timer timer;

bool flagButton = false; //αν έχει πατηθεί το κουμπί
bool alarm = false; // αν έχουν περάσει τα 12 sec

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT) ;
  pinMode(10, OUTPUT) ;
  pinMode(6, OUTPUT) ;
  pinMode(2, INPUT) ;
  pinMode(11, INPUT) ;

  // set Timer to manual reset mode
  timer.manualReset();
}

void loop()
{
  // αν δεν υπάρχει αυτοκίνητο - IR αισθητήρας LOW
  if (digitalRead(11) == LOW) {
    digitalWrite(10, LOW);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    digitalWrite(12, LOW);
    flagButton = false;
    alarm = false;
    timer.reset();

  }
  else { //αν υπάρχει αυτοκίνητο - IR αισθητήρας HIGH
    if ((flagButton == false) and (alarm == false) ) {
      timer.isStarting(); //ξεκινάει να μετράει 12 sec
      analogWrite(6, 255); // ανάβει πορτοκαλί φανάρι
      analogWrite(10, 128);
      analogWrite(9, 0);
    }
    else if (alarm == false) { //αν δεν περάσουν τα 12 sec και έχει πατηθεί το κουμπί
      analogWrite(6, 0);
      analogWrite(10, 255); //πράσινο φανάρι
      timer.reset();
    }

    if (digitalRead(2) == HIGH) { //αν αφού περάσουν τα 12 sec πατηθεί το κουμπί
      analogWrite(6, 0);
      analogWrite(10, 255);
      analogWrite(9, 0);
      digitalWrite(12, LOW);
      flagButton = true;
    }
    if (timer.delay(9000) and flagButton == false) //αν περάσουν τα 12 sec και δεν πατηθεί το κουμπί
    {
      digitalWrite(12, HIGH); //ηχεί σειρήνα
      analogWrite(6, 255); // ανάβει κόκκινο
      analogWrite(10, 0);
      alarm = true;
    }

  }

}
