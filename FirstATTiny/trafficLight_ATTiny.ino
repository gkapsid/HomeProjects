// C++ code
//
// Car and pedestrian

# define RED_C 0
# define YELLOW_C 1
# define GREEN_C 2
# define RED_P 3
# define GREEN_P 4

void setup()
{
  pinMode(RED_C, OUTPUT);
  pinMode(YELLOW_C, OUTPUT);
  pinMode(GREEN_C, OUTPUT);
  pinMode(RED_P, OUTPUT);
  pinMode(GREEN_P, OUTPUT);
}

void loop()
{
  digitalWrite(RED_P, HIGH);
  digitalWrite(GREEN_P, LOW);
  delay(3000); // Wait for 1000 millisecond(s)
  digitalWrite(GREEN_C, HIGH);
  digitalWrite(YELLOW_C, LOW);
  digitalWrite(RED_C, LOW);
  delay(30000); // Wait for 3000 millisecond(s)
  digitalWrite(GREEN_C, LOW);
  digitalWrite(YELLOW_C, HIGH);
  digitalWrite(RED_C, LOW);
  delay(10000); // Wait for 1000 millisecond(s)
  digitalWrite(GREEN_C, LOW);
  digitalWrite(YELLOW_C, LOW);
  digitalWrite(RED_C, HIGH);
  delay(3000); // Wait for 1000 millisecond(s)
  digitalWrite(RED_P, LOW);
  digitalWrite(GREEN_P, HIGH);
  delay(30000); // Wait for 3000 millisecond(s)
}
