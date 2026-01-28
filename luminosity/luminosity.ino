// #define LED 8
// #define SENSOR A0

// void setup(){
// pinMode(LED, OUTPUT);
// Serial.begin(115200);
// }

// void loop(){
//   int light = analogRead(SENSOR);
//   if(light < 300){
//     digitalWrite(LED, HIGH);
//   }
//   else{
//     digitalWrite(LED, LOW);
//   }
// delay(1000);
// }



#define SENSOR A0
#define SAMPLE_SIZE 100
int lum_arr[SAMPLE_SIZE] = {0};
int index_counter = 0;
unsigned long lumLastRead = millis();
unsigned long lumDelay = 50;


int averageLum(){
long sum = 0;

for(int i = 0; i < SAMPLE_SIZE; i++){
sum += lum_arr[i];
}
return sum/SAMPLE_SIZE;
}

void printAverageLum(){
  {
  int average = averageLum();
Serial.println("");
Serial.print("Average luminosity for ");
Serial.print(SAMPLE_SIZE);
Serial.print(" samples, taken every ");
Serial.print(lumDelay);
Serial.print(" ms is:");
Serial.println(average);
Serial.println("____");
}
}


void setup(){
Serial.begin(115200);
}


void loop(){
unsigned long timeNow = millis();
if(timeNow - lumLastRead > lumDelay){
  lumLastRead += lumDelay;
  lum_arr[index_counter] = analogRead(SENSOR);
  index_counter++;
  if(index_counter == SAMPLE_SIZE){
    index_counter = 0;
printAverageLum();
  }
  Serial.print(">");
  }
  averageLum();
}


