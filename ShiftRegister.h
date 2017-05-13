/*
 	 ShiftRegister.h - This is for a easy IC 74HC595 pins control
  Created on: 25 mar. 2017
  Copyright (c) 2006 M. Osiel Quevedo.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_
#define TRUE 1
#define FALSE 0
#define WAIT_TIME 100
#include <Arduino.h>

class ShiftRegister {
public:
	ShiftRegister(int latchPin, int clockPin, int dataPin, int howIc);
	ShiftRegister();
	//Put to HIGH one pin
	void high(int p);
	void high(int p,  boolean autoLoad, boolean autoShow);
	//Put to LOW one pin
	void low(int p);
	void low(int p, boolean autoLoad, boolean autoShow);
	/*
	 * Equivalent to digitalWrite(), but have two params more,
	 * "autoLoad" define if the bytes will to send now = true, later = false
	 * "autoShow" depends of the "autoLoad* and allow the ShiftRegister show the new bytes
	 * The previous declaration if for all that have this params*/
	void dw(int pin, byte state, boolean autoLoad, boolean autoShow);
	void dw(int pin, byte state);
	/*
	 * This allow change many pins a only invoke
	 * */
	void loadBinaries(byte *bytes, int size, int from, boolean autoLoad, boolean autoShow);
	void loadBinaries(byte *bytes, int size, int from);
	void loadBinaries(byte *bytes, int size);
	int getPinSize();
	void test(int wait = 500);
	/*Show the last change in the IC pins*/
	void showBytes();
	/*Return the free Ram of the Microcontroler*/
	int getFreeRam();
	/*Set all pins to low*/
	void reset(boolean autoLoad, boolean autoShow);
	void reset(boolean autoLoad);

	/*Send the bytes to the ShiftRegister IC 74HC959*/
	void shiftOut(boolean autoShow);
	/*Change the controls pins for a new position*/
	void setLatchPin(int latchPin);
	void setClockPin(int clockPin);
	void setDataPin(int dataPin);
	void setIcSize(int icSize);
	/*Return the information required*/
	int getLatchPin();
	int getClockPin();
	int getIcSize();
	byte* getPinsStates();
	//Invert all the pins if =0 then set 1, and if 1 then set 0
	void invertBytes();

private:

	byte* _pinsStates;
	int _latchPin;
	int _clockPin;
	int _dataPin;
	int _pinSize;


	void changePinState(int pin, byte state, boolean autoLoad, boolean autoShow);
	void startPinsStates();//Initializing the pins stares array

};

#endif /* SHIFTREGISTER_H_ */
