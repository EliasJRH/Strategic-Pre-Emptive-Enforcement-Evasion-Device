#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <binary.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 16, TXPin = 14;
static const uint32_t GPSBaud = 9600;
const int PiezoPin = 8;
const int LEDPin = 6;

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
  {45.41901397705078, -75.70237731933594},
  {45.353759765625, -75.64704132080078},
  {45.388816833496094, -75.6772689819336},
  {45.365272521972656, -75.73085021972656},
  {45.416263580322266, -75.71468353271484},
  {45.401100158691406, -75.69973754882812},
  {45.360713958740234, -75.79228973388672},
  {45.38939666748047, -75.7265396118164},
  {45.41070556640625, -75.68955993652344},
  {45.47734832763672, -75.49738311767578},
  {45.424217224121094, -75.63732147216797},
  {45.30404281616211, -75.87680053710938},
  {45.376827239990234, -75.69149780273438},
  {45.32253646850586, -75.88713836669922},
  {45.350894927978516, -75.7335433959961},
  {45.41182327270508, -75.63044738769531},
  {45.392852783203125, -75.60758209228516},
  {45.43253707885742, -75.6889877319336},
  {45.415714263916016, -75.70818328857422},
  {45.41290283203125, -75.712646484375},
  {45.378578186035156, -75.66753387451172},
  {45.41648483276367, -75.60243225097656},
  {45.4776611328125, -75.51260375976562},
  {45.27493667602539, -75.74898529052734},
  {45.38854217529297, -75.72576141357422},
  {45.369510650634766, -75.62220001220703},
  {45.4279670715332, -75.62702941894531},
  {45.41132736206055, -75.68406677246094},
  {45.36264419555664, -75.71141052246094},
  {45.4005241394043, -75.63148498535156},
  {45.2686882019043, -75.75109100341797},
  {45.43335723876953, -75.6074447631836},
  {45.43381881713867, -75.6900405883789},
  {45.48457717895508, -75.49810028076172},
  {45.388023376464844, -75.67626953125},
  {45.408721923828125, -75.69376373291016},
  {45.40886306762695, -75.69366455078125},
  {45.36838912963867, -75.70120239257812},
  {45.381622314453125, -75.73844146728516},
  {45.27865982055664, -75.77987670898438},
  {45.34062194824219, -75.57823944091797},
  {45.45835876464844, -75.48637390136719},
  {45.36974334716797, -75.6649398803711},
  {45.37840270996094, -75.66947174072266},
  {45.443660736083984, -75.63910675048828},
  {45.40529251098633, -75.709716796875},
  {45.40243911743164, -75.70050811767578},
  {45.409446716308594, -75.69427490234375},
  {45.416900634765625, -75.70549011230469},
  {45.41756057739258, -75.70393371582031},
  {45.44445037841797, -75.53278350830078},
  {45.48356246948242, -75.50102996826172},
  {45.422027587890625, -75.6937255859375},
  {45.42867660522461, -75.696044921875},
  {45.371761322021484, -75.76700592041016},
  {45.42809295654297, -75.68524932861328},
  {45.399906158447266, -75.62158966064453},
  {45.382205963134766, -75.63419342041016},
  {45.33456802368164, -76.02326965332031},
  {45.34748458862305, -75.66152954101562},
  {45.28244400024414, -75.86495971679688},
  {45.44266891479492, -75.64208984375},
  {45.38019943237305, -75.6443099975586},
  {45.48420333862305, -75.52039337158203},
  {45.37336730957031, -75.62421417236328},
  {45.36941146850586, -75.62208557128906},
  {45.35757827758789, -75.63707733154297},
  {45.386749267578125, -75.73265075683594},
  {45.293182373046875, -75.97206115722656},
  {45.40034866333008, -75.6344223022461},
  {45.349464416503906, -75.818115234375},
  {45.370155334472656, -75.77063751220703},
  {45.422645568847656, -75.66105651855469},
  {45.43032455444336, -75.51571655273438},
  {45.29255676269531, -75.89459991455078},
  {45.370872497558594, -75.76881408691406},
  {45.28651809692383, -75.60391998291016},
  {45.419349670410156, -75.70759582519531},
  {45.38922119140625, -75.7267837524414},
  {45.353553771972656, -75.6473617553711},
  {45.41065216064453, -75.6893539428711},
  {45.36426544189453, -75.74779510498047}
};

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(PiezoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

float lastClosestDist = 999999999;
void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      // displayInfo();
      float closestDist = -1;
      coordPair closestPair;
      for (int x = 0; x < 141; ++x){
        Serial.print("Distance to ");
        Serial.print(coords[x].latitude, 10);
        Serial.print(", ");
        Serial.print(coords[x].longitude, 10);
        Serial.print(": ");
        float dist = gps.distanceBetween(gps.location.lat(), gps.location.lng(), coords[x].latitude, coords[x].longitude);
        Serial.println(dist);
        if (closestDist == -1 || dist < closestDist){
          closestDist = dist;
          closestPair = coords[x];
        } 
      }
      Serial.print("Closest camera: ");
      Serial.print(closestPair.latitude, 10);
      Serial.print(", ");
      Serial.print(closestPair.longitude, 10);
      Serial.print(": ");
      Serial.println(closestDist, 10);
      Serial.println("//////////");
      if (closestDist <= 300){
        if (closestDist <= lastClosestDist){
          lastClosestDist = closestDist;
          digitalWrite(LEDPin, HIGH);
          tone(PiezoPin, 2000, 1000);
        }else {
          lastClosestDist = 999999999999;
          digitalWrite(LEDPin, LOW);
          noTone(PiezoPin);
        }
      } else {
        digitalWrite(LEDPin, LOW);
        noTone(PiezoPin);
      }
      delay(1000);
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
