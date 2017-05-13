/*
  	 SevenSegmentsDisplay.h - This is for handle 7 Segments Display with ShiftRegister
  Created on: 10 abr. 2017
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

#ifndef SEVENSEGMENTSDISPLAY_H_
#define SEVENSEGMENTSDISPLAY_H_
#include "ShiftRegister.h"

#define UNIT_TO_START_COUNTER 0
#define UNIT_TO_END_COUNTER  1

#define CATODE_COMMUN  0
#define ANODE_COMMUN 1

class SevenSegmentsDisplay {
private:
	ShiftRegister _register;//Is for the 74HC959 pins control
	int* _counters;
	boolean* _pointState;
	int* _displaysMode;
	int _counter = 0;
	int _counterMode = UNIT_TO_END_COUNTER;
	//int _displayMode = CATODE_COMMUN;
	int _counterMax = 9999;
	boolean _autoReset = false;
	boolean _autoShow = false;
	void startCounter();
	void paint(int displayId, boolean all);
	void paint(int displayId);

	void nextDisplay(int &last);


public:
	SevenSegmentsDisplay(int latchPin, int clockPin, int dataPin, int icSize);
	boolean setDisplayValue(int displayId, int value);
	boolean setDisplayValue(int value);
	boolean lessValue(int displayId, int value);
	boolean plusValue(int displayId, int value);
	boolean resetValue(int displayId);
	boolean lowDisplay(int displayId);


	boolean plusCounter(int value);
	boolean lessCounter(int value);
	boolean resetCounter();
	boolean lowCounter();
	boolean setCounterValue(int value);
	boolean setCounterValue(double value);



	boolean existDisplay(int displayId);
	boolean setPointState(int displayId,boolean state);

	boolean setPointState(boolean state);
	void setAutoReset(boolean autoReset);
	boolean isAutoReset();

	int getFreeRam();
	void showChange();


	boolean isAutoShow();
	void setAutoShow(boolean autoShow = false);

	int getCounterMax();

	void setCounterMax(int counterMax);
	int getDisplayMode(int displayId);
	void setDisplayMode(int displayId, int mode);
	void setDisplayMode(int mode);

};

#endif /* SEVENSEGMENTSDISPLAY_H_ */
