#include <WiFi.h>
#include <WebServer.h>
#include "config.h"

#define TRIG_PIN    5
#define ECHO_PIN   18
#define LED_GREEN  25
#define LED_YELLOW 26
#define LED_RED    27
#define BUZZER_PIN 32

#define NORMAL_CM    30
#define WARNING_CM   15

float samples[10];
int   sampleIdx = 0;
bool  sampleFull = false;

float getAverage() {

  int n = sampleFull ? 10 : sampleIdx;
  if (n == 0) return 0;
  float sum = 0;
  for (int i = 0; i < n; i++) sum += samples[i];
  return sum / n;

}

float readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return (duration * 0.0343) / 2.0;

}

WebServer server(80);

float  currentDistance = 0;
String currentLevel    = "NORMAL";
String historyData     = "";
int    histCount       = 0;

const char* HTML_PAGE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitor Dashboard</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: Arial; background: #1a1a2e; color: white; text-align: center; }
    h1   { color: #e94560; }
    .level { font-size: 2em; padding: 10px; border-radius: 8px; margin: 20px auto; width: 300px; }
    .NORMAL   { background: #27ae60; }
    .WARNING  { background: #f39c12; }
    .CRITICAL { background: #c0392b; animation: blink 0.5s infinite; }
    @keyframes blink { 0%,100%{opacity:1} 50%{opacity:0.3} }
  </style>
</head>
<body>
  <h1>River Water Level Monitor</h1>
  <p>Distance from sensor to water surface: <strong id="dist">--</strong> cm</p>
  <div class="level NORMAL" id="level">Loading...</div>
  <canvas id="chart" width="600" height="300" style="max-width:100%;margin:auto;display:block;"></canvas>
  <script>
    const ctx = document.getElementById('chart').getContext('2d');
    let chart = new Chart(ctx, {

      type: 'line',
      data: {

        labels: [], datasets: [{

          label: 'Distance (cm)',
          data: [], borderColor: '#e94560', fill: false, tension: 0.3
        }]
      },
      options: { animation: false, scales: { y: { reverse: true, title: { display: true, text: 'Distance cm (lower = more water)' } } } }
    });

    async function update() {

      const r = await fetch('/data');
      const d = await r.json();
      document.getElementById('dist').textContent  = d.distance.toFixed(1);
      document.getElementById('level').textContent = d.level;
      document.getElementById('level').className   = 'level ' + d.level;

      if (chart.data.labels.length > 20) {

        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();

      }
      chart.data.labels.push(new Date().toLocaleTimeString());
      chart.data.datasets[0].data.push(d.distance);
      chart.update();

    }
    setInterval(update, 2000);
    update();
  </script>
</body>
</html>
)rawliteral";

void handleRoot() { server.send(200, "text/html", HTML_PAGE); }

void handleData() {

  String json = "{\"distance\":" + String(currentDistance, 1)
              + ",\"level\":\"" + currentLevel + "\"}";
  server.send(200, "application/json", json);

}

unsigned long lastBuzz = 0;
bool buzzState = false;

void setAlert(int level) {

  digitalWrite(LED_GREEN,  level == 0 ? HIGH : LOW);
  digitalWrite(LED_YELLOW, level == 1 ? HIGH : LOW);
  digitalWrite(LED_RED,    level == 2 ? HIGH : LOW);

  unsigned long now = millis();
  if (level == 0) { digitalWrite(BUZZER_PIN, LOW); }
  else if (level == 1) {

    if (now - lastBuzz >= 2000) { lastBuzz = now; buzzState = !buzzState; digitalWrite(BUZZER_PIN, buzzState); }
  } else {

    if (now - lastBuzz >= 300)  { lastBuzz = now; buzzState = !buzzState; digitalWrite(BUZZER_PIN, buzzState); }

  }

}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN,   OUTPUT);
  pinMode(ECHO_PIN,   INPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nConnected! Dashboard: http://" + WiFi.localIP().toString());

  server.on("/",     handleRoot);
  server.on("/data", handleData);
  server.begin();

}

unsigned long lastRead = 0;

void loop() {

  server.handleClient();

  if (millis() - lastRead >= 500) {

    lastRead = millis();

    float dist = readDistance();
    if (dist < 0) { Serial.println("[ERROR] Sensor timeout"); return; }

    samples[sampleIdx] = dist;
    sampleIdx = (sampleIdx + 1) % 10;
    if (sampleIdx == 0) sampleFull = true;

    currentDistance = getAverage();

    int level;
    if (currentDistance > NORMAL_CM) {

      currentLevel = "NORMAL";  level = 0;
    } else if (currentDistance > WARNING_CM) {

      currentLevel = "WARNING"; level = 1;
    } else {

      currentLevel = "CRITICAL"; level = 2;

    }

    Serial.printf("[FLOOD] Distance: %.1f cm (avg) | Level: %s\n",
                  currentDistance, currentLevel.c_str());

    setAlert(level);

  }

}
