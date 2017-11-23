#include "nexstar.h"
#include "settings.h"
#include "TimeLib.h"
Nexstar::Nexstar(HardwareSerial &port) : Singleton<Nexstar>(this), _port(port)
{
}



void Nexstar::read_to(Stream &stream) {
  if(_port.available()) {
    stream.write(_port.read());
  }
}

void Nexstar::setup() {
  _port.begin(9600);
}

void Nexstar::set_gps_info(double latitude, double longitude) {
}

void Nexstar::set_time() {
  tmElements_t time;
  int32_t offset = static_cast<int32_t>(Settings::instance()->timezone() + Settings::instance()->daylight_saving()) * 60 * 60;
  breakTime(now() + offset, time);
  
  _port.write('H');
  _port.write(time.Hour);
  _port.write(time.Minute);
  _port.write(time.Second);
  _port.write(time.Month);
  _port.write(time.Day);
  _port.write(1970 + time.Year - 2000);
  _port.write(Settings::instance()->timezone() > 0 ? Settings::instance()->timezone() : (256 + Settings::instance()->timezone()));
  _port.write(Settings::instance()->daylight_saving());
}

