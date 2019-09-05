//PROGRAMACIÓN PARA EL CONTROL DE UN CARRO TANQUE POR WIFI
//HECHO POR: IVAN VARGAS

#include <ESP8266WiFi.h>                  //librería ESP8266WiFi
#include <Servo.h>
 
const char* ssid = "wifigratis";  //NOMBRE DEL WIFI A UTILIZAR PARA LA CONEXIÓN  
const char* password = "ivan3222";       //CONTRASEÑA DE NUESTRA RED WIFI
 
WiFiServer server(80);                    //PUERTO PARA LAS COMUNICACIONES

Servo servo1;
 
void setup() {
  Serial.begin(115200);
  servo1.write(1);
 //DECLARACION DE PINES A UTILIZAR
 servo1.attach(9);
  
  server.begin();                         //inicializamos el servidor
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);            //Red con clave, en el canal 1 y visible
  //WiFi.softAP(ssid, password,3,1);      //Red con clave, en el canal 3 y visible 
  //WiFi.softAP(ssid);                    //Red abierta
 
  Serial.println();
 
  Serial.print("Direccion IP Access Point - por defecto: ");      //Imprime la dirección IP
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");                   //Imprime la dirección MAC
  Serial.println(WiFi.softAPmacAddress()); 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  // Comprueba si el cliente ha conectado
  WiFiClient client = server.available();  
  if (!client) {
    return;
  }
 
  // Espera hasta que el cliente envía alguna petición
  Serial.println("nuevo cliente");
  while(!client.available()){
    delay(1);
  }
 
  // Imprime el número de clientes conectados
  Serial.printf("Clientes conectados al Access Point: %dn", WiFi.softAPgetStationNum()); 
 
  // Lee la petición
  String peticion = client.readStringUntil('r');
  Serial.println(peticion);
  client.flush();
 
  // Comprueba la petición
  
  if (peticion.indexOf("ROB=ADELANTE") != -1) {
    
  } 
  //////////////////////////////////////////////////////
  if (peticion.indexOf("ROB=ATRAS") != -1){
    
  }
  ///////////////////////////////////////////////////
  if (peticion.indexOf("ROB=SERVOI") != -1){
    
    servo1.write(i);
    delay(40);
    i=i+1;
    if(i==180)
    {
      servo1.write(180);
    }
  }
    if (peticion.indexOf("ROB=SERVOD") != -1){
   servo1.write(i);
    delay(40);
    i=i-1;
    if(i==0)
    {
      servo1.write(0);
    }
  }

// CREACIÓN DE LA PAGINA WEB PARA CONTROLAR LA PANTALLA 7 SEGMENTOS
  client.println("HTTP/1.1 200 OK");
  client.println("");                                   //LINEA DE SEPARACIÓN
  client.println("<!DOCTYPE HTML>");
  client.println("<meta charset='UTF-8'>");
  client.println("<html>");

  client.println("<head>");
  client.println("<title>IVAN VARGAS</title>");  //NOMBRE DE LA PAGINA
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>CONTROL PARA CARROTANQUE DE GUERRA</h1>"); //TITULO DE LA PAGINA
  client.println("</body>");

  //CONTROL DEL CARROTANQUE
  client.println("<button type='button' onClick=location.href='/ROB=ADELANTE' style='margin:auto; background-color:blue; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> ADELANTE</h2> </button>");
  client.println("<button type='button' onClick=location.href='/ROB=ATRAS' style='margin:auto; background-color:green; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> ATRAS</h2> </button><br><br>");
  client.println("<button type='button' onClick=location.href='/ROB=SERVOI' style='margin:auto; background-color:red; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> GIRAR CAÑON IZQUIERDA </h2> </button>");
  client.println("<button type='button' onClick=location.href='/ROB=SERVOD' style='margin:auto; background-color:yellow; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> GIRAR CAÑON DERECHA </h2> </button>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Petición finalizada");          // Se finaliza la petición al cliente. Se inicaliza la espera de una nueva petición.
 
  //Desconexión de los clientes
  //WiFi.softAPdisconnect();
}
