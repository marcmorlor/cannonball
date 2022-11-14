#include <stdint.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include <iostream>
#include <sstream>

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

  return true;
}

void Dashboard::clearAll(void) {
  clearTacho();
  clearFuel();
  clearTurbo();
  clearSpeed();
  return;
}

void Dashboard::updateTacho(uint8_t revs) {
  if (revs < 0) revs = 0;
  if (revs > MAX_TACHO_REVS) revs = MAX_TACHO_REVS;
  _revs = revs;
  updateDashboard();
  return;
}

void Dashboard::clearTacho(void) {
  updateTacho(0);
  return;
}

void Dashboard::updateFuel(uint8_t level) {
  if (level < 0) level = 0;
  if (level > MAX_FUEL_LEVEL) level = MAX_FUEL_LEVEL;
  _fuel = level;
  updateDashboard();
  return;
}

void Dashboard::clearFuel(void) {
  updateFuel(0);
  return;
}

void Dashboard::updateTurbo(bool enabled) {
  _turbo = enabled;
  updateDashboard();
  return;
}

void Dashboard::clearTurbo(void) {
  updateTurbo(false);
  return;
}

void Dashboard::updateSpeed(uint16_t speed) {
  if (speed < 0) speed = 0;
  if (speed > 255) speed = 255;
  _speed = speed;
  updateDashboard();
  return;
}

void Dashboard::clearSpeed(void) {
  updateSpeed(0);
  return;
}

/*************/

void Dashboard::updateDashboard(void) {
  uint16_t t1 = _fuel;

  if (_turbo) {
    t1 += 100;
  }

  if (_revs > 0){
    t1 += (_revs * 8);
  }

  std::ostringstream ss;
  ss << std::hex << t1;
  ss << std::hex << _speed;
  std::string msg = ss.str();

  serialPuts (_fd, msg.c_str());

  return;
}

