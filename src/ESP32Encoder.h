#pragma once
#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/pcnt.h>
#define MAX_ESP32_ENCODERS PCNT_UNIT_MAX
#define 	_INT16_MAX 32766
#define  	_INT16_MIN -32766

enum encType {
single,
half,
full
};
enum puType {
UP,
DOWN,
NONE
};
class ESP32Encoder {
public:
	ESP32Encoder(bool always_interrupt=false);
	~ESP32Encoder();
	void attachHalfQuad(int aPintNumber, int bPinNumber);
	void attachFullQuad(int aPintNumber, int bPinNumber);
	void attachSingleEdge(int aPintNumber, int bPinNumber);
	int64_t getCount();
	int64_t clearCount();
	int64_t pauseCount();
	int64_t resumeCount();
	void detatch();
	boolean isAttached(){return attached;}
	void setCount(int64_t value);
	void setFilter(uint16_t value);
	static ESP32Encoder *encoders[MAX_ESP32_ENCODERS];
	bool always_interrupt;
	gpio_num_t aPinNumber;
	gpio_num_t bPinNumber;
	pcnt_unit_t unit;
	bool fullQuad=false;
	int countsMode = 2;
	volatile int64_t count=0;
	pcnt_config_t r_enc_config;
	static enum puType useInternalWeakPullResistors;

private:
	static  pcnt_isr_handle_t user_isr_handle;
	static bool attachedInterrupt;
	void attach(int aPintNumber, int bPinNumber, enum encType et);
	int64_t getCountRaw();
	bool attached;
  bool direction;
  bool working;
};

//Added by Sloeber 
#pragma once

