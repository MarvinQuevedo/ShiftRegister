/*
 	 ShiftRegister.cpp - This is for a easy IC 74HC595 pins control
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

#include "ShiftRegister.h"


ShiftRegister::ShiftRegister(int latchPin, int clockPin, int dataPin, int howIc)
{
	//Se establecen los pines de control del 74HC959
	this->_latchPin = latchPin;
	this->_clockPin = clockPin;
	this->_dataPin = dataPin;
	this->_pinSize = howIc * 8;//Se recibe la cantidad de IC a controlar, y se multiplica por 8
	this->_pinsStates = new byte[this->_pinSize]; // Se inicializa el array principal
	this->startPinsStates();
	//Se confiran los pines como salida
	pinMode(this->_latchPin, OUTPUT);
	pinMode(this->_dataPin, OUTPUT);
	pinMode(this->_clockPin, OUTPUT);
}
ShiftRegister::ShiftRegister()
{
	this->_clockPin = 2;
	this->_latchPin = 3;
	this->_dataPin = 4;
	this->_pinSize = 8;
	this->_pinsStates = new byte[8];
}
void ShiftRegister::startPinsStates()
{
	for(int i = 0;i<this->_pinSize;i++)
	{
		this->_pinsStates[i] = FALSE;
	}
}
void ShiftRegister::setClockPin(int clockPin)
{
	this->_clockPin = clockPin;
}
void ShiftRegister::setDataPin(int dataPin)
{
	this->_dataPin = dataPin;
}
void ShiftRegister::setLatchPin(int latchPin)
{
	this->_latchPin = latchPin;
}
void ShiftRegister::setIcSize(int icSize)
{
	this->_pinSize = icSize * 8;
	this->_pinsStates = new byte[this->_pinSize]; // Se inicializa el array principal
	this->startPinsStates();
}
int ShiftRegister::getClockPin()
{
	return this->_clockPin;
}
int ShiftRegister::getLatchPin()
{
	return this->_latchPin;
}
int ShiftRegister::getIcSize()
{
	return this->_pinSize/8;
}
byte* ShiftRegister::getPinsStates()
{
	return this->_pinsStates;
}
void ShiftRegister::changePinState(int pin, byte state, boolean autoLoad, boolean autoShow)
{

	if(pin>=0 && pin < this->_pinSize)
	{
		this->_pinsStates[pin] = state;
		if(autoLoad)
		{
			this->shiftOut(autoShow);
		}
	}

}
void ShiftRegister::dw(int pin, byte state, boolean autoLoad, boolean autoShow)
{
	this->changePinState(pin, state, autoLoad, autoShow);
}
void ShiftRegister::dw(int pin, byte state)
{
	this->dw(pin, state, true, true);
}
void ShiftRegister::high(int pin)
{
	this->changePinState(pin, TRUE, true, true);
}
void ShiftRegister::high(int pin, boolean autoLoad, boolean autoShow)
{
	this->changePinState(pin, TRUE, autoLoad, autoShow);
}
void ShiftRegister::low(int pin)
{
	this->changePinState(pin, FALSE, true, true);
}
void ShiftRegister::low(int pin, boolean autoLoad, boolean autoShow)
{
	this->changePinState(pin, FALSE, autoLoad, autoShow);
}

void ShiftRegister::shiftOut(boolean autoShow)
{

  int i=0;
  int pinState;
  digitalWrite(this->_dataPin, 0);
  digitalWrite(this->_clockPin, 0);
  digitalWrite(this->_latchPin, 0);
  for (i=this->_pinSize; i>=0; i--)
  {
    digitalWrite(this->_clockPin, 0);
    if (this->_pinsStates[i] == TRUE)
    {
      pinState = TRUE;
    }
    else
    {
      pinState = FALSE;
    }

    digitalWrite(this->_dataPin, pinState);

    digitalWrite(this->_clockPin, 1);

    digitalWrite(this->_dataPin, 0);
  }
  digitalWrite(this->_clockPin, 0);
  if(autoShow)
  {
	  //Show the changes
	  digitalWrite(this->_latchPin, 1);
  }

}
void ShiftRegister::showBytes()
{
	digitalWrite(this->_latchPin, 1);
}
void ShiftRegister::loadBinaries(byte *bytes,  int size)
{
	this->loadBinaries(bytes,size, 0, true, true);
}
void ShiftRegister::loadBinaries(byte *bytes,  int size, int from)
{
	this->loadBinaries(bytes,size, from, true, true);
}
void ShiftRegister::loadBinaries(byte *bytes, int size, int from, boolean autoLoad, boolean autoShow)
{
	int i = 0;
	if(from<0)
	{
		from = 0;
	}
	if((size + from) > this->_pinSize)
	{
		from = 0;
		size = this->_pinSize;
	}

	for(i = 0;i< size ;i++)
	{
		if(i<this->_pinSize){
			this->_pinsStates[i+from] = bytes[i];
		}
	}
	if(autoLoad)
	{
		this->shiftOut(autoShow);
	}

}
void ShiftRegister::test(int wait = 500)
{
	Serial.println("Starting test");

	int i;
	for(i = 0;i<this->_pinSize;i++)
	{
		this->high(i);
		delay(wait);

	}
	delay(wait*3);
	for(i = this->_pinSize;i>=0;i--)
		{
			this->low(i);
			delay(wait);
		}

	for(i = 0;i<this->_pinSize;i++)
			{
				if(i>0){
					this->low(i-1);
					//delay(wait);
				}
				this->high(i);
				delay(wait);

			}

	for(i = this->_pinSize;i>=0;i--)
		{
			this->high(i);
			delay(wait);

		}
		delay(wait*3);
	for(i = 0;i<this->_pinSize;i++)
		{
			this->low(i);
			delay(wait);
		}

	for(i = this->_pinSize;i>=0;i--)
			{
				if(i<this->_pinSize){
					this->low(i+1);

				}
				this->high(i);
				delay(wait);
			}

}
int ShiftRegister::getFreeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

int ShiftRegister::getPinSize()
{
	return this->_pinSize;
}

void ShiftRegister::reset(boolean autoLoad, boolean autoShow)
{
	int i = 0;
	for(i=0;i<this->_pinSize;i++)
	{
		this->_pinsStates[i] = 0;
	}
	if(autoLoad)
	{
		this->shiftOut(autoShow);
	}
}
void ShiftRegister::reset(boolean autoLoad)
{
	this->reset(autoLoad, true);
}
void ShiftRegister::invertBytes()
{
	for(int i= 0;i<this->_pinSize;i++)
	{
		if(this->_pinsStates[i] == TRUE){
			this->_pinsStates[i] = FALSE;
		}else{
			this->_pinsStates[i] = TRUE;
		}

	}
}
