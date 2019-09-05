//PROGRAMACIÓN PARA EL CONTROL DE UNA PANTALLA 7 SEGMENTOS MEDIANTE WIFI
//HECHO POR: IVAN VARGAS

#include <ESP8266WiFi.h>                  //librería ESP8266WiFi

int Seg [7] = { 2, 3, 4, 5, 6, 7, 8 };
int a;
int cont=0;
 
const char* ssid = "wifigratis";  //NOMBRE DEL WIFI A UTILIZAR PARA LA CONEXIÓN  
const char* password = "ivan3222";       //CONTRASEÑA DE NUESTRA RED WIFI
 
WiFiServer server(80);                    //PUERTO PARA LAS COMUNICACIONES

void setup() {
  Serial.begin(115200);
  
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

  // Declaración de pines de salida
  for(int i=2; i<=8; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  digitalWrite(8, LOW);

}

void loop() {

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

    if (peticion.indexOf("ROB=A") != -1) {
      cont=cont+1; //contador
      if(cont==10)
      {
        cont=0; //Si llega a ser 10 entonces vuelve a la posición inicial
        for(int i=2; i<=7; i++)
        {
          digitalWrite(i, HIGH);
         }
          digitalWrite(8, LOW);
      }
      }

     if (peticion.indexOf("ROB=B") != -1) {
      if(cont>0) //NUMERO (0) EN 7 SEGMENTOS
      {
        if(cont==1)  //NUMERO (1) EN 7 SEGMENTOS
        {  
          digitalWrite(2, LOW);
          for(int i=5; i<=8; i++)
          {
            digitalWrite(i, LOW);
          }
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
        }
        if(cont==2) //NUMERO (2) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
          {
            if(i==4)
            {
              digitalWrite(4, LOW);
            }
            else
            if(i==7)
            {
              digitalWrite(7, LOW);
            }
            else
            {
              digitalWrite(i, HIGH);
            }
        }
        }
        if(cont==3) //NUMERO (3) EN 7 SEGMENTOS
        {
          for( int i=2; i<=5; i++)
          {
            digitalWrite(i, HIGH);
          }
          digitalWrite(8, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
        }
        if(cont==4) //NUMERO (4) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
          {
            if(i==2)
            {
              digitalWrite(2, LOW);
            }
            else
            if(i==5)
            {
              digitalWrite(5, LOW);
            }
            else
            if(i==6)
            {
              digitalWrite(6, LOW);
            }
            else
            {
              digitalWrite(i, HIGH);
            }
          }
        }
        if(cont==5) //NUMERO (5) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
          {
            if(i==3)
            {
              digitalWrite(3, LOW);
            }
            else
            if( i==6)
            {
              digitalWrite(6, LOW);
            }
            else
            {
              digitalWrite(i, HIGH);
            }
          }
        }
        if(cont==6) //NUMERO (6) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
          {
            if(i==3)
            {
              digitalWrite(3, LOW);
            }
            else
            {
              digitalWrite(i, HIGH);
            }
          }
        }
        if(cont==7) //NUMERO (7) EN 7 SEGMENTOS
        {
          for(int i=2; i<=4; i++)
          {
            digitalWrite(i, HIGH);
          }
          for(int j=5; j<=8; j++)
          {
            digitalWrite(j, LOW);
          }
        }
        if(cont==8) //NUMERO (8) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
          {
              digitalWrite(i, HIGH);
          }
        }
        if(cont==9) //NUMERO (9) EN 7 SEGMENTOS
        {
          for(int i=2; i<=8; i++)
           {
            if(i==6)
            {
              digitalWrite(i, LOW);
            }
            else
            {
              digitalWrite(i, HIGH);
            }
          }
        }
      cont=0; // Se reinicia el contador
        }
      } 
      if (peticion.indexOf("ROB=C") != -1) {
        cont=0; //Vuelve a su valor inicial
        for(int i=2; i<=7; i++)
        {
          digitalWrite(i, HIGH);
         }
          digitalWrite(8, LOW);
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
          client.println("<h1>CONTROL PARA PANTALLA 7 SEGMENTOS</h1>"); //TITULO DE LA PAGINA
          client.println("</body>");

          //CONTROL DEL CARROTANQUE
          client.println("<button type='button' onClick=location.href='/ROB=A' style='margin:auto; background-color:blue; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> INICIAR </h2> </button>");
          client.println("<button type='button' onClick=location.href='/ROB=B' style='margin:auto; background-color:green; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> ADELANTE </h2> </button><br><br>");
          client.println("<button type='button' onClick=location.href='/ROB=C' style='margin:auto; background-color:red; color:#F6D8CE; padding:5px; border:2px solid black; width:200;'><h2> RESET </h2> </button>");
          client.println("</html>"); 
          delay(1);
          Serial.println("Petición finalizada");          // Se finaliza la petición al cliente. Se inicaliza la espera de una nueva petición.
 
          //Desconexión de los clientes
          //WiFi.softAPdisconnect();
        }
