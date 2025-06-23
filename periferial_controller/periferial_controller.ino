#include <EEPROM.h>
#include <SoftwareSerial.h>

#define ERROR_LED_PIN 3
//for extension class
class extension{
  struct ext_conf {
    bool is_using_pins = false;
    int (*out_data[3])(void); 
  };
  public:
    ext_conf Config;
};

//extension class end
bool isConfigured = false;
String input; 
SoftwareSerial module (10,11);
extension Extension;
String raspberryInput; 

void setup() {
  // put your setup code here, to run once:
  module.begin(115200);//extension
  Serial.begin(115200);//debug
  Serial3.begin(115200);//raspberry
  chechRaspConnection();

  
}

void loop() {
  if(module.available() > 0){
      input = module.readString();
      if(input.startsWith("$c ")){
        configure_ext(input.substring(3));

      }
  } 
}
void configure_ext(String args){
  args.trim();
  int input_length = args.length();
  bool failed = false;
  if(args[4] == '1'){
    Extension.Config.is_using_pins = true;
  }
  else if (args[4] == '0') {
    Extension.Config.is_using_pins = false;
  }else{
    failed = true;
  }
  if(args.indexOf("gyro") != -1){
    Extension.Config.out_data[0] = gyro;
  }
  if(args.indexOf("distance") != -1){
    Extension.Config.out_data[0] = distance;
  }





  if(failed){
    digitalWrite(ERROR_LED_PIN, 1);
    Serial.print("err");
    module.print("err");
  }
}
//placeholder
int gyro(){

}
//placeholder
int distance(){

}
void error(){
  while(1){
    digitalWrite(ERROR_LED_PIN, 1);
    delay(100);
    digitalWrite(ERROR_LED_PIN, 0);
    delay(100);
  }

}
void chechRaspConnection(){
  while(1){//waits for raspberry to respond
    Serial3.print("rr");
    if(Serial3.available()){
      raspberryInput = Serial3.readString();
      if(raspberryInput = "ar"){
        break;
      }
      else{
        error();
      }

    }
    
  }
  
}
