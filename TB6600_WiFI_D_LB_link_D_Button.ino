#include <ESP8266WiFi.h>
/*
  IOT Series 
  Code for Step Motor power,frequency and 
  direction control through TCP/IP protocol.
  Created by Diomar Sbardelotto, Jannuary 3, 2019.
  Released into the public domain.
  Clock/steps: GPIO05
  Enable/disable: GPIO04
  Direction: GPIO16
  Resistor: A0, Vcc e GND
  */
//Thankyou Manoj R. Thankur
//Reference: Zero to Hero ESP8266

const char* ssid="BL-MP01-A7BF48";
const char* password = "12345678";
int Period;
boolean ENABLE=4;
boolean DIR=16;
int STEP=5;
WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(15);

  pinMode(STEP, OUTPUT);
  digitalWrite(STEP, LOW);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, LOW);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, HIGH);
  Period=100000;
  /*Conectando com a rede WiFi*/
  /*WiFi connecting*/
  Serial.println();
  Serial.println();
  Serial.print("Obtendo rede de: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  /* Segue nesta condição até obter aconexão*/
  /*Wainting connection*/
  while (WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
    /*Isto irá imprimir pontos até estabelecera conexão*/
    /*Printing dots until connection ok*/
    
  }
Serial.println("");
Serial.println("Conectado!");
server.begin();
Serial.println("Servidor iniciado em: ");
//Os comandos abaixo irão imprimir o endereço IP conectado
//Will print WiFi Ip
Serial.print(WiFi.localIP());

}

void loop() {
  //STEP
  digitalWrite(STEP, HIGH);
  delayMicroseconds(Period);
  digitalWrite(STEP, LOW);
  delayMicroseconds(Period);

  // Verificando por cliente
  // Searching client
  WiFiClient client= server.available();
  if(!client){
    return;
  }
Serial.println("Cliente novo");
while(!client.available()){
  delay(1);
}


String request=client.readStringUntil('/r');
Serial.println(request);
client.flush();
//int value = LOW;
//if (request.indexOf("/LED=ON")!=-1){
//  digitalWrite(LEDPin, HIGH);
//  value = HIGH;


 //Variável ENABLE
if(request.indexOf("/ENABLE")!=-1 && digitalRead(ENABLE)==LOW)

  digitalWrite(ENABLE, HIGH);
  else if (request.indexOf("/ENABLE") != -1 && digitalRead(ENABLE)==HIGH)
  digitalWrite(ENABLE, LOW);
  
  //Variável DIR
  else if (request.indexOf("/DIR") != -1 && digitalRead(DIR)==LOW)
   digitalWrite(DIR, HIGH);
  else if (request.indexOf("/DIR") != -1 && digitalRead(DIR)==HIGH)
   digitalWrite(DIR, LOW);

    //Variável STEP DOWN
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==100000)
    Period=50000;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==50000)
    Period=25000;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==25000)
    Period=10000;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==10000)
    Period=1000;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==1000)
    Period=500;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==500)
    Period=300;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==300)
    Period=200;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==200)
    Period=100;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==100)
    Period=50;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==50)
    Period=25;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==25)
    Period=10;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==10)
    Period=5;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==5)
    Period=3;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==3)
    Period=2;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==2)
    Period=1;
  else if (request.indexOf("/STEP_DOWN") != -1&& Period==1)
    Period=100000;

      //Variável STEP UP
  else if (request.indexOf("/STEP_UP") != -1&& Period==1)
    Period=2;
  else if (request.indexOf("/STEP_UP") != -1&& Period==2)
    Period=3;
  else if (request.indexOf("/STEP_UP") != -1&& Period==3)
    Period=5;
  else if (request.indexOf("/STEP_UP") != -1&& Period==5)
    Period=10;
  else if (request.indexOf("/STEP_UP") != -1&& Period==10)
    Period=25;
  else if (request.indexOf("/STEP_UP") != -1&& Period==25)
    Period=50;
  else if (request.indexOf("/STEP_UP") != -1&& Period==50)
    Period=100;
  else if (request.indexOf("/STEP_UP") != -1&& Period==100)
    Period=200;
  else if (request.indexOf("/STEP_UP") != -1&& Period==200)
    Period=300;
  else if (request.indexOf("/STEP_UP") != -1&& Period==300)
    Period=500;
  else if (request.indexOf("/STEP_UP") != -1&& Period==500)
    Period=1000;
  else if (request.indexOf("/STEP_UP") != -1&& Period==1000)
    Period=10000;
  else if (request.indexOf("/STEP_UP") != -1&& Period==10000)
    Period=25000;
  else if (request.indexOf("/STEP_UP") != -1&& Period==25000)
    Period=50000;
  else if (request.indexOf("/STEP_UP") != -1&& Period==50000)
    Period=100000;
  else if (request.indexOf("/STEP_UP") != -1&& Period==100000)
    Period=1;
    

//Configurando LEDPin de acordo com sua seleção
//Retona a resposta
client.println("HTTP/1.1 200 OK");
client.println("Content-Type:text/html");
client.println(""); //não esqueça disto!
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print("Periodo: ");
client.print(Period);
client.println("<br><br>");
client.print("Direcao: ");
//if (DIR=LOW)
//{
//client.print("Horario");
//}
//if (DIR=HIGH)
//{
//client.print("Anti-horario");
//}
client.println("<br><br>");
client.println("<a href=\"/ENABLE\"\"><button>ENABLE</button></a><br/>");
client.println("<br><br>");
client.println("<a href=\"/DIR\"\"><button>DIR</button></a><br/>");
client.println("<br><br>");
client.println("<a href=\"/STEP_DOWN\"\"><button>STEP_DOWN</button></a><br/>");
client.println("<br><br>");
client.println("<a href=\"/STEP_UP\"\"><button>STEP_UP</button></a><br/>");
client.println("<br><br>");
client.println("</html>");
delay(1);
}


