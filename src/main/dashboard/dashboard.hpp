#ifndef _DASHBOARD_H_
#define _DASHBOARD_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringSerial.h>

#include <iostream>
#include <sstream>	
#include <iomanip>

class Dashboard {
 public:
  static const uint8_t MAX_TACHO_REVS = 8;
  static const uint8_t MAX_FUEL_LEVEL = 5;

  Dashboard(void);
  ~Dashboard(void);

  bool init(char *device, int baud);
  void clear_all(void);

  void update_tacho(uint8_t revs);
  void clear_tacho(void);

  void update_fuel(uint8_t level);
  void clear_fuel(void);

  void update_turbo(bool enabled);
  void clear_turbo(void);

  void update_speed(uint16_t speed);
  void clear_speed(void);

  void update_dashboard(void);

 protected:
  int _fd;

  uint8_t _revs;
  uint8_t _fuel;
  bool _turbo;
  uint16_t _speed;

  std::string _lastMsg;
};

extern Dashboard dashboard;

#endif
