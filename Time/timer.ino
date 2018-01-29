#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "ssid";
const char* password = "password";

//configure TimeZone
int timezone = 6 * 3600;
int dst = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }
  
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");   
}

void loop() {
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  String day = String(p_tm->tm_mday);
  String mon = String(p_tm->tm_mon+1);
  String year = String(p_tm->tm_year + 1900);
  String hour = String(p_tm->tm_hour);
  String mint = String(p_tm->tm_min);
  String sec = String(p_tm->tm_sec);
  String curTime = hour+":"+mint+":"+sec;
  String daymon = day+"/"+mon+"/"+year+"  "+curTime;
  Serial.print(daymon);

  /*
  Serial.print(".....");
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  
  Serial.print(" ");
  
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.println(p_tm->tm_sec);
  */
  
  delay(1000);
  Serial.flush();

}
