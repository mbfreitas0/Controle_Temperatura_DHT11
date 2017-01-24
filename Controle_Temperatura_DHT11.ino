
////////////////////////////////////////////////////////////
//                                                        //
//        Controle de Temperatura  - Arduino              //
//                                                        //
//        Marcelo Barbosa de Freitas                      //
//                                                        //
//                                                        //
//                                                        //
//        Data: 23/01/2017                                //
//                                                        //
//                                                        //
////////////////////////////////////////////////////////////

  #include <dht11.h>
  #include <LiquidCrystal_I2C.h>
  #include <Wire.h>  
  #include "RTClib.h"
  
  RTC_DS1307 RTC;
  
  #define RELAY1 7 //Ligar o "IN1"do Rele no "pino 7" do Arduino
  
  dht11 DHT; // Cria um objeto que o sensor DHT11
    
  int posicao;// Variável responsável por pegar a posição do rele na A0
  String temper;// variável responsável por pegar a situação do Aquecedor: Ligado ou Desligado
  
  int dhtpin = A1; // Pino analógico em que o sensor DHT11 está conectado
  
  /***  Configuração do LCD   ***/
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
  //LiquidCrystal_I2C lcd(0x20,16,2);
  
  void setup() {
  
    /*** Configuração do Relógio ***/
    Wire.begin(); // Inicia a porta I2C
    RTC.begin(); // Inicia a comunicação com o módulo RTC
    RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
    
    Serial.begin(9600);
  
  /*** Configurando o "pino 7" do Arduino como Saída(OUTPUT) ***/
  pinMode(RELAY1, OUTPUT); 
  lcd.begin(16,2); // Define o display com 16 colunas e 2 linhas
  delay(2000);
  
  }
  
  void loop() {
  
    DateTime now = RTC.now(); // Obtem e fecha a hora do RTC
  
    
    posicao = analogRead(A0);
    
    DHT.read(dhtpin); //Lê as informações do sensor
  

  if (DHT.temperature <= 25){
      digitalWrite(RELAY1, LOW);
      temper = "Aquecedor Ligado";
    } 
    else {
          digitalWrite(RELAY1, HIGH);
          temper = "Aquecedor Deslig";
          
      }
    
      /*------------------ Impressões LCD --------------*/
  
      /*------------------WEBESTUFA - AJH5-------------*/
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("WEBESTUFA");
      lcd.setCursor(0,1);
      lcd.print("Estufa Agricola");
      delay(5000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Status :");
      lcd.setCursor(0,1);
      lcd.print(temper);
      delay(3000);      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Umidade: ");
      lcd.print(DHT.humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Temperatura: ");
      lcd.print(DHT.temperature);
      lcd.write(B11011111);
      delay(3000);
  }

