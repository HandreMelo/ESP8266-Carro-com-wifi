#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <String.h>

//motor A
#define pinMotorAdir D3 //direção A-
#define pinMotorAvelo D1 //velocidade A+
//motor B
#define pinMotorBdir D4 //B-
#define pinMotorBvelo D2 //B+
int numL = 0;
int numR = 0;;

//define as credenciais do WIFI (do ESP)
const char* ssid = "NomeQualquer";
const char* password = "senhaQualquer";

//cria o servidor
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
 
void setup(void){
//define os pinos do motor como saída
  pinMode(pinMotorAdir, OUTPUT);
  pinMode(pinMotorAvelo, OUTPUT);
  pinMode(pinMotorBdir, OUTPUT);
  pinMode(pinMotorBvelo, OUTPUT);
//inicializa os motores
  digitalWrite(pinMotorAdir,0);
  digitalWrite(pinMotorAvelo,0);
  digitalWrite(pinMotorBdir,0);
  digitalWrite(pinMotorBvelo,0);
 delay(1000);

 Serial.begin(115200);
//define o ESP como ponto de acesso com as credenciais definidas anteriormente
 WiFi.softAP(ssid, password); 
delay(2000);
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());

//inicia o servidor
 server.begin();
 webSocket.begin();
/*em caso de receber alguns sinal de quem estiver conectado, chama a função webSockerEvent e analisa que tipo de dado é*/
 webSocket.onEvent(webSocketEvent);
 
 Serial.println("Web server started!");
}
 
void loop(void){
//mantém o servidor ativo 
  webSocket.loop();
  server.handleClient();
  if (Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    webSocket.broadcastTXT(c, sizeof(c));
  }
            analogWrite(pinMotorAvelo, numL);
      analogWrite(pinMotorBvelo, numR);
}
 //função que lida com os dados recebidos
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
//se for texto
  if (type == WStype_TEXT){

    String msg = "";
    String L,R;

for(int i = 0; i < length; i++) msg += (char) payload[i]; 

     unsigned int a = msg.indexOf(";");
    unsigned int b = msg.length();

 //copia os dados recebidos como char (um a um) em uma string
                                                       

  //trabalha com a string para usar seu número para os motores
// sendo de 0 à 255 , velocidade e + ou -, direção.
// os valores da string são relacionados aos motores A e B respectivamente

    L = msg.substring(0,a);
    R = msg.substring(a+1);

    numL = L.toInt();
    numR = R.toInt();
    
          if ( L.toInt() < 0) {
            numL = numL*(-1);
            digitalWrite(pinMotorAdir, LOW);
          }
          if(L.toInt() >=0) digitalWrite(pinMotorAdir, HIGH);
          
          if ( R.toInt() < 0) {
            numR = numR*(-1);
            digitalWrite(pinMotorBdir, LOW);
          }
          if(R.toInt() >=0)
          digitalWrite(pinMotorBdir, HIGH);

         //define a velocidade do motor com os valores recebidos     
      
      Serial.println(msg);
      Serial.println(numL);
      Serial.println(numR);

      }//final SE TEXTO

    }

