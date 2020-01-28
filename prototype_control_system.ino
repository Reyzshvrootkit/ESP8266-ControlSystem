#include <ESP8266WiFi.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";

int Output1 = 5; //set your Pin
int Output2 = 4;
int Output3 = 12;
int Output4 = 13;

WiFiServer server(80);

void setup() {

  //pin mode
  pinMode(Output1,OUTPUT);
  digitalWrite(Output1,LOW);

  pinMode(Output2,OUTPUT);
  digitalWrite(Output2,LOW);

  pinMode(Output3,OUTPUT);
  digitalWrite(Output3,LOW);

  pinMode(Output4,OUTPUT);
  digitalWrite(Output4,LOW);
 
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED )
  {
    delay(1000);
  }

  Serial.println();
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  Serial.println("NodeMCU Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.begin();
  }

void loop() {

  //   Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("Hello New client");
  
   // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  int value = LOW;
  
  //Control
  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
  
  if (request.indexOf("/Output1=ON") != -1)  
  {
    digitalWrite(Output1, HIGH);
    value = HIGH;
  }
  
  if (request.indexOf("/Output1=OFF") != -1)  
  {
    digitalWrite(Output1, LOW);
    value = LOW;
  }
  
  if (request.indexOf("/Output2=ON") != -1)  
  {
    digitalWrite(Output2, HIGH);
    value = HIGH;
  }
  
  if (request.indexOf("/Output2=OFF") != -1)  
  {
    digitalWrite(Output2, LOW);
    value = LOW;
  }

  if (request.indexOf("/Output3=ON") != -1)  
  {
    digitalWrite(Output3, HIGH);
    value = HIGH;
  }
  
  if (request.indexOf("/Output3=OFF") != -1)  
  {
    digitalWrite(Output3, LOW);
    value = LOW;
  }

  if (request.indexOf("/Output4=ON") != -1)  
  {
    digitalWrite(Output4, HIGH);
    value = HIGH;
  }
  
  if (request.indexOf("/Output4=OFF") != -1)  
  {
    digitalWrite(Output4, LOW);
    value = LOW;
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Led pin is now: ");
 
  if(value == HIGH) 
  {
    client.print("On");
  } 
  else 
  {
    client.print("Off");
  }

  //HTTP User Interface
  client.println("<br><br>");
  client.println("<a href=\"/Output1=ON\"\"><button>Turn On 1</button></a>");
  client.println("<a href=\"/Output1=OFF\"\"><button>Turn Off 1</button></a><br />"); 
  client.println("<a href=\"/Output2=ON\"\"><button>Turn On 2</button></a>");
  client.println("<a href=\"/Output2=OFF\"\"><button>Turn Off 2</button></a><br />"); 
  client.println("<a href=\"/Output3=ON\"\"><button>Turn On 3</button></a>");
  client.println("<a href=\"/Output3=ON\"\"><button>Turn Off 4</button></a>");
  client.println("<a href=\"/Output4=ON\"\"><button>Turn On 4</button></a>");
  client.println("<a href=\"/Output4=ON\"\"><button>Turn Off 4</button></a>"); 
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  
}
