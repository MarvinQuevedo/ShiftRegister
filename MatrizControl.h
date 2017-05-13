/*
  	 MatrizControl.h - This is for handle a Led Matriz with ShiftRegister and/or 7417 Decade Counter
  Created on: 30 mar. 2017
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
 * */
#include "ShiftRegister.h"



#ifndef MATRIZCONTROL_H_
#define MATRIZCONTROL_H_
#define IC_74HC595 1
#define IC_4017 0


class MatrizControl {
private:
byte _matriz[16][32];//[Rows][Cols]
byte _icType;
int _rows = 8;
int _trueCols = 32;
int _cols = 16;
ShiftRegister *_shiftCols;
ShiftRegister *_shiftRows;
int _clockDc;
int _resetDc;
int _pinEnableDc = -1;
int _activeRow = -1;
int _cursor = 0;
long _timeChange = 25;
long _nextChange = this->_timeChange;
boolean _allowMove = true;

void pulseDc();
void resetDc();
void starup();
void addLetter(char l);
void move();


public:
	MatrizControl(ShiftRegister *shiftCols,  int clockCounter, int resetCounter);
	MatrizControl(ShiftRegister *shiftCols, ShiftRegister *shiftRows);
	void test();
	void paint();
	void addWords(char words[], int size);
	void setLetter(byte letter[8][6]);
	void setAllowMove(boolean allow);
	void setTimeChange(long time);

};



#endif /* MATRIZCONTROL_H_ */


