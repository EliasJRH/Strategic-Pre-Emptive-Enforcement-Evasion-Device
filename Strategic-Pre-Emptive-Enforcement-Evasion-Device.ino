#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <binary.h>

static const int RXPin = 16, TXPin = 14;
static const uint32_t GPSBaud = 9600;
const int PiezoPin = 9;
const int LEDPin = 6;
const int alertDist = 200;
const int alertTone = 12;
bool buzzed = false;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

typedef struct {
  double latitude;
  double longitude;
} coordPair;

coordPair coords[] = {
  {45.28146886, -75.74392084},
  {45.46935075, -75.45873444},
  {45.40021726, -75.63620026},
  {45.43924462, -75.59942769},
  {45.34462751, -75.74999215},
  {45.47888292, -75.47825523},
  {45.35109943, -75.80631488},
  {45.30821623, -75.89970065},
  {45.43322705, -75.5654689554},
  {45.3762722479, -75.660905566},
  {45.3340869419, -75.7838346302},
  {45.2652023749, -75.9099980496},
  {45.4384310938, -75.6453343887},
  {45.4717851882, -75.4944270367},
  {45.364651381, -75.7124151448},
  {45.3230004136, -75.924709162},
  {45.2949096036, -75.8813335527},
  {45.2785866571, -75.8569792798},
  {45.2777213039, -75.7793625171},
  {45.272065083, -75.724560914},
  {45.2852002063, -75.7095993577},
  {45.2624552977, -75.7416666407},
  {45.273377392, -75.9307772822},
  {45.3645359225, -75.7701692356},
  {45.3742208049, -75.773043905},
  {45.254533189, -75.7326814156},
  {45.4015010387, -75.6962570401},
  {45.4576945841, -75.4659423485},
  {45.3659607245, -75.6890686036},
  {45.279552655, -75.738320142},
  {45.3174384885, -75.6020732936},
  {45.2816928193, -75.6864424388},
  {45.2840564801, -75.8458194355},
  {45.3611477547, -75.6285653299},
  {45.3864254402, -75.6237983},
  {45.3883969422, -75.6926336623},
  {45.446483, -75.596159},
  {45.3794690898, -75.654934766},
  {45.4782729275, -75.540446514},
  {45.4338303582, -75.6900702041},
  {45.3265193065, -75.8079304761},
  {45.3737706134, -75.6550544},
  {45.3599059802, -75.6999508132},
  {45.3042480616, -75.8957381499},
  {45.4107477572, -75.6791235456},
  {45.3278664331, -75.7676975637},
  {45.1855972222, -75.8264130936},
  {45.2888548066, -75.7176619303},
  {45.4387795704, -75.6786160171},
  {45.4688572975, -75.4737434457},
  {45.2727214523, -75.7375774126},
  {45.3683972856, -75.6556107143},
  {45.3227529491, -75.7174008334},
  {45.4250254351, -75.6555102065},
  {45.454336379, -75.5980269984},
  {45.2641669344, -75.9276239242},
  {45.320561839, -75.8264788793},
  {45.4221778042, -75.4170741213},
  {45.2294525958, -75.6823655337},
  {45.3396748612, -75.9398458559},
  {45.39294866, -75.60758145},
  {45.41183341, -75.63045981},
  {45.32259424, -75.8871873},
  {45.40878852, -75.69378269},
  {45.36528328, -75.73082093},
  {45.35363104, -75.64733066},
  {45.41059369, -75.68946437},
  {45.41629602, -75.71467416},
  {45.47732608, -75.4974114},
  {45.38882841, -75.67723452},
  {45.38919155, -75.72662713},
  {45.43246674, -75.68908746},
  {45.41572863, -75.70823681},
  {45.41291758, -75.71265182},
  {45.37857171, -75.66755153},
  {45.41648492, -75.60244499},
  {45.47762664, -75.51259116},
  {45.2749753, -75.74900599},
  {45.38857382, -75.72576713},
  {45.36947236, -75.62207744},
  {45.42798671, -75.62701694},
  {45.41131111, -75.68406267},
  {45.36263085, -75.71144959},
  {45.40054791, -75.63148873},
  {45.43336965, -75.60745592},
  {45.41902653, -75.70240246},
  {45.43379539, -75.68991198},
  {45.35090342, -75.73351715},
  {45.37677184, -75.69148988},
  {45.36078523, -75.79226646},
  {45.40100097, -75.69965431},
  {45.4242409, -75.63736161},
  {45.30407235, -75.87677745},
  {45.2749753, -75.74900599},
  {45.48460028, -75.49810341},
  {45.40878852, -75.69378269},
  {45.38802034, -75.67623737},
  {45.38163119, -75.73846511},
  {45.40529157, -75.70973672},
  {45.41687927, -75.70547366},
  {45.40243467, -75.70051327},
  {45.42190879, -75.69381322},
  {45.40941288, -75.69427205},
  {45.44366406, -75.63909822},
  {45.36839102, -75.70119678},
  {45.4286548, -75.69605817},
  {45.27866592, -75.7799176},
  {45.44450342, -75.53280378},
  {45.36973398, -75.66494736},
  {45.48355406, -75.50105058},
  {45.3784036, -75.66945865},
  {45.45833915, -75.48637951},
  {45.34061302, -75.57823933},
  {45.417535, -75.703944},
  {45.3822204, -75.63422114},
  {45.35363104, -75.64733066},
  {45.41059366, -75.68946433},
  {45.37182033, -75.76700336},
  {45.42809335, -75.68529062},
  {45.39990521, -75.62158646},
  {45.44266084, -75.64210469},
  {45.34747262, -75.66147357},
  {45.38020918, -75.6443775},
  {45.33454599, -76.02328249},
  {45.48423559, -75.52036864},
  {45.28243692, -75.86494308},
  {45.38930031, -75.72674059},
  {45.26870306, -75.75116853},
  {45.28650966, -75.60392333},
  {45.38882841, -75.67723452},
  {45.35756736, -75.63707326},
  {45.38666703, -75.73257414},
  {45.37087356, -75.76881154},
  {45.37008858, -75.77058769},
  {45.29317806, -75.97205827},
  {45.37336061, -75.62420532},
  {45.36947236, -75.62207744},
  {45.40034514, -75.63441699},
  {45.34938793, -75.81807293},
  {45.47233893, -75.54795751},
  {45.29260541, -75.89451488},
  {45.42262016, -75.6613151},
  {45.42190879, -75.69381322},
  {45.41935066, -75.70759843},
  {45.43032102, -75.51571663},
  {45.36426544, -75.7477951}
};

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(PiezoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
}

float lastClosestDist = 999999999;
void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      float closestDist = -1;
      coordPair closestPair;
      for (int x = 0; x < 141; ++x){
        float dist = gps.distanceBetween(gps.location.lat(), gps.location.lng(), coords[x].latitude, coords[x].longitude);
        if (closestDist == -1 || dist < closestDist){
          closestDist = dist;
          closestPair = coords[x];
        } 
      }
      Serial.print('\r');
      Serial.print("Closest camera: ");
      Serial.print(closestPair.latitude, 10);
      Serial.print(", ");
      Serial.print(closestPair.longitude, 10);
      Serial.print(": ");
      Serial.println(closestDist, 10);

      if (closestDist <= alertDist){
        if (!buzzed){
          buzzed = true;
          digitalWrite(LEDPin, HIGH);
          analogWrite(PiezoPin, alertTone);
          delay(200);
          noTone(PiezoPin);
          delay(100);
          analogWrite(PiezoPin, alertTone);
          delay(200);
        } else{
          noTone(PiezoPin);
        }
      }else{
        buzzed = false;
      }
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 10);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 10);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(" Speed: ");
  if (gps.speed.isValid())
  {
    Serial.print(gps.speed.kmph());
    Serial.print(" km/h");
  }
  else
  {
    Serial.print("INVALID");
  }
  float bronson_lat = 45.3174384885;
  float bronson_lng = -75.6020732936;
  float dist_to_bronson = gps.distanceBetween(gps.location.lat(), gps.location.lng(), bronson_lat, bronson_lng);
  Serial.print(" Distance from Kelly Farm speed cam: ");
  Serial.print(dist_to_bronson);
  Serial.print(" m ");
  double course = gps.courseTo(gps.location.lat(), gps.location.lng(), bronson_lat, bronson_lng);
  char* dir = gps.cardinal(course);
  Serial.print(" Heading to Kelly Farm speed cam: ");
  Serial.print(course);
  Serial.print(" (");
  Serial.print(dir);
  Serial.print(") ");
  Serial.println();
}
