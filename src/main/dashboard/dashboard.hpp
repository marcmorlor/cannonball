#ifndef _DASHBOARD_H_
#define _DASHBOARD_H_

#include <stdint.h>
#include <wiringSerial.h>

#include <iostream>
#include <sstream>

class Dashboard {
 public:
  static const uint8_t MAX_TACHO_REVS = 8;
  static const uint8_t MAX_FUEL_LEVEL = 5;

  Dashboard(void);
  ~Dashboard(void);

  bool init(char *device, int baud);
  void clearAll(void);

  void updateTacho(uint8_t revs);
  void clearTacho(void);

  void updateFuel(uint8_t level);
  void clearFuel(void);

  void updateTurbo(bool enabled);
  void clearTurbo(void);

  void updateSpeed(uint16_t speed);
  void clearSpeed(void);

 protected:
  int _fd;

  uint8_t _revs;
  uint8_t _fuel;
  bool _turbo;
  uint16_t _speed;
};

extern Dashboard dashboard;

#endif
