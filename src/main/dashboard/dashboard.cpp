#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringSerial.h>

#include <iostream>
#include <sstream>	
#include <iomanip>

#include "dashboard.hpp"

Dashboard dashboard;

/* Constructor */
Dashboard::Dashboard(void) {
}

Dashboard::~Dashboard(void) {
}

bool Dashboard::init(char *device, int baud) {

  _fd = serialOpen (device, baud);

  _speed = 0;
  _turbo = false;
  _revs = 0;
  _fuel = MAX_FUEL_LEVEL;

  _lastMsg = 

  return true;
}

void Dashboard::clear_all(void) {
  clear_tacho();
  clear_fuel();
  clear_turbo();
  clear_speed();
  return;
}

void Dashboard::update_tacho(uint8_t revs) {
  if (revs < 0) revs = 0;
  if (revs > MAX_TACHO_REVS) revs = MAX_TACHO_REVS;
  _revs = revs;
  // update_dashboard();
  return;
}

void Dashboard::clear_tacho(void) {
  update_tacho(0);
  return;
}

void Dashboard::update_fuel(uint8_t level) {
  if (level < 0) level = 0;
  if (level > MAX_FUEL_LEVEL) level = MAX_FUEL_LEVEL;
  _fuel = level;
  // update_dashboard();
  return;
}

void Dashboard::clear_fuel(void) {
  update_fuel(0);
  return;
}

void Dashboard::update_turbo(bool enabled) {
  _turbo = enabled;
  // update_dashboard();
  return;
}

void Dashboard::clear_turbo(void) {
  update_turbo(false);
  return;
}

void Dashboard::update_speed(uint16_t speed) {
  if (speed < 0) speed = 0;
  if (speed > 255) speed = 255;
  _speed = speed;
  // update_dashboard();
  return;
}

void Dashboard::clear_speed(void) {
  update_speed(0);
  return;
}

void Dashboard::update_dashboard(void) {
  uint16_t t1 = _fuel;

  if (_turbo) {
    t1 += 100;
  }

  if (_revs > 0){
    t1 += (_revs * 8);
  }

  std::ostringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << (t + r + f);
  ss << std::setfill('0') << std::setw(2) << std::hex << s;
  ss << '\n';
  std::string msg = ss.str();

  if (_lastMsg.compare(msg) != 0) {
    _lastMsg = msg;
    serialPuts (_fd, msg.c_str());
  }

  return;
}

/*************/

