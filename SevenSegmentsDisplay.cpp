/*
 * SevenSegmentsDisplay.cpp
 *
 *  Created on: 10 abr. 2017
 *      Author: Osiel Quevedo
 */

#include "SevenSegmentsDisplay.h"
byte zero[] = {1,1,1,1,1,1,0,0};
byte one[] = {0,1,1,0,0,0,0,0};
byte two[] = {1,1,0,1,1,0,1,0};
byte three[] = {1,1,1,1,0,0,1,0};
byte four[] = {0,1,1,0,0,1,1,0};
byte five[] = {1,0,1,1,0,1,1,0};
byte six[] = {1,0,1,1,1,1,1,0};
byte seven[] = {1,1,1,0,0,1,0,0};
byte eight[] = {1,1,1,1,1,1,1,0};
byte nine[] = {1,1,1,0,0,1,1,0};


SevenSegmentsDisplay::SevenSegmentsDisplay(int latchPin, int clockPin, int dataPin, int icSize)
{
	ShiftRegister reg(latchPin, clockPin, dataPin, icSize);

	this->_register = reg;

	this->_register.setLatchPin(latchPin);
	this->_register.setClockPin(clockPin);
	this->_register.setDataPin(dataPin);
	this->_register.setIcSize(icSize);
	this->_counters = new int(this->_register.getIcSize());
	this->_pointState = new boolean(this->_register.getIcSize());
	this->_displaysMode = new int(this->_register.getIcSize());

	for(int i = 0;i<this->_register.getIcSize();i++){
		this->_counters[i] = -1;
		this->_pointState[i] = 0;
		this->_displaysMode[i] = CATODE_COMMUN;
	}



}
boolean SevenSegmentsDisplay::existDisplay(int displayId)
{
	if(displayId < this->_register.getIcSize() && displayId >= 0)
	{
		return true;
	}else
	{
		return false;
	}
}
void SevenSegmentsDisplay::paint(int displayId, boolean all)
{

	int i;
	byte p = FALSE;
	int t = 0;
	int f = 0;

	for(i = 0;i < this->_register.getIcSize();i++)
	{
		f = (8 * i);

		p = this->_pointState[i];

		if(displayId == i || all)
		{

			t = this->_counters[i];
			switch(t)
					{
					case 0:
						zero[7]= p;
						this->_register.loadBinaries(zero,8,f, false, false);
						break;
					case 1:
						one[7]= p;
						this->_register.loadBinaries(one,8,f, false, false);
						break;
					case 2:
						two[7] = p;
						this->_register.loadBinaries(two,8,f, false, false);
						break;
					case 3:
						three[7] = p;
						this->_register.loadBinaries(three,8,f, false, false);
						break;
					case 4:
						four[7] = p;
						this->_register.loadBinaries(four,8,f, false, false);
						break;
					case 5:
						five[7] = p;
						this->_register.loadBinaries(five,8,f, false, false);
						break;
					case 6:
						six[7] = p;
						this->_register.loadBinaries(six,8,f, false, false);
						break;
					case 7:
						seven[7] = p;
						this->_register.loadBinaries(seven,8,f, false, false);
						break;
					case 8:
						eight[7] = p;
						this->_register.loadBinaries(eight,8,f, false, false);
						break;
					case 9:
						nine[7] = p;
						this->_register.loadBinaries(nine,8,f, false, false);
						break;
					default:
						byte bytes[] = {0,0,0,0,0,0,0,0};
						this->_register.loadBinaries(bytes,0,f, false, false);
						break;
					}
			if(this->_displaysMode[i] == ANODE_COMMUN)
			{
				this->_register.invertBytes();
			}

		}

	}

	if(this->_autoShow){
		this->showChange();
	}

}

void SevenSegmentsDisplay::paint(int displayId)
{
	 this->paint(displayId, false);
}

boolean SevenSegmentsDisplay::setDisplayValue(int displayId, int value)
{

	if(value<0 || value>9)
	{
		if(this->_autoReset){
			value = 0;
		}
	}
	if(this->existDisplay(displayId))
		{
			this->_counters[displayId] = value;
			this->paint(displayId);
			return true;
		}

	return false;
}

boolean SevenSegmentsDisplay::setDisplayValue(int value)
{
	return this->setDisplayValue(0, value);
}

boolean SevenSegmentsDisplay::lessValue(int displayId, int value)
{
	if(this->existDisplay(displayId))
		{
			return this->setDisplayValue(displayId, this->_counters[displayId] - value);
		}
	return false;
}
boolean SevenSegmentsDisplay::plusValue(int displayId, int value)
{
	if(this->existDisplay(displayId))
		{
			return this->setDisplayValue(displayId, this->_counters[displayId] + value);
		}
		return false;
}
boolean SevenSegmentsDisplay::resetValue(int displayId){
	if(this->existDisplay(displayId))
	{
		this->setDisplayValue(displayId, 0);
		return true;
	}
	return false;
}
void SevenSegmentsDisplay::nextDisplay(int &last)
{
	if(this->_counterMode == UNIT_TO_END_COUNTER)
	{
		last --;
	}else if(this->_counterMode == UNIT_TO_START_COUNTER)
	{
		last ++;
	}
}

boolean SevenSegmentsDisplay::setCounterValue(int value)
{
	int i = 0;
	if(value>this->_counterMax || value <0)
	{
		value = 0;
		this->resetCounter();

	}
	String string = String(value);

	int size = string.length();
	int ics = this->_register.getIcSize()-1;
	int c = (this->_counterMode == UNIT_TO_END_COUNTER)?ics:0;

	for(i = size-1;i>=0;i--)
	{
		this->setDisplayValue(c, string.substring(i, i+1).toInt());
		this->nextDisplay(c);
	}
	this->_counter = value;

	return true;
}
boolean SevenSegmentsDisplay::setCounterValue(double value)
{
	String str = String(value);
	int point = str.indexOf(".");

	String string = "";
	for(int i = 0;i<str.length();i++)
	{
		if(i != point)
		{
			string.concat(str.substring(i,i+1));
		}
	}
	int size = string.length();
	int ics = this->_register.getIcSize()-1;
	int c = (this->_counterMode == UNIT_TO_END_COUNTER)?ics:0;

	for(int i = size-1;i>=0;i--)
	{
		if(string.substring(i, i+1).toInt() != 0 && i != size)
		{
			this->setDisplayValue(c, string.substring(i, i+1).toInt());
			this->nextDisplay(c);
		}else{
			if(string.substring(i, i+1) == "."){
				this->_pointState[c] = true;
			}
		}

	}


	return true;
}
boolean SevenSegmentsDisplay::resetCounter()
{
	int i = 0;
	for(i = 0;i<this->_register.getIcSize();i++){
		//this->resetValue(i);
		this->lowDisplay(i);
	}
	this->_counter = 0;
//	this->showChange()
	return true;
}
boolean SevenSegmentsDisplay::plusCounter(int value)
{
	return this->setCounterValue(this->_counter + value);
}
boolean SevenSegmentsDisplay::lowCounter()
{
	return false;
}
boolean SevenSegmentsDisplay::lessCounter(int value)
{
	return this->setCounterValue(this->_counter - value);
}

boolean SevenSegmentsDisplay::lowDisplay(int displayId)
{
	if(this->existDisplay(displayId))
		{
			this->setDisplayValue(displayId, -1);
			return true;
		}
		return false;
}

boolean SevenSegmentsDisplay::setPointState(int displayId, boolean state)
{
	if(this->existDisplay(displayId)){
		this->_pointState[displayId] = state;
		return true;
	}
	return false;
}
boolean SevenSegmentsDisplay::setPointState(boolean state)
{
	return this->setPointState(0, state);
}
void SevenSegmentsDisplay::setAutoReset(boolean autoReset)
{
	this->_autoReset = autoReset;
}
boolean SevenSegmentsDisplay::isAutoReset()
{
	return this->_autoReset;
}
int SevenSegmentsDisplay::getFreeRam(){
	return this->_register.getFreeRam();
}
void SevenSegmentsDisplay::showChange(){
	this->_register.shiftOut(false);
	this->_register.showBytes();
}
void SevenSegmentsDisplay::setAutoShow(boolean autoShow){
	this->_autoShow = autoShow;
}
boolean SevenSegmentsDisplay::isAutoShow(){
	return this->_autoShow;
}
int SevenSegmentsDisplay::getCounterMax(){
		return _counterMax;
	}

void SevenSegmentsDisplay::setCounterMax(int counterMax) {
	_counterMax = counterMax;
}
void SevenSegmentsDisplay::setDisplayMode(int displayId, int mode)
{
	this->_displaysMode[displayId] = mode;
}
void SevenSegmentsDisplay::setDisplayMode(int mode){
	for(int i = 0;i<this->_register.getIcSize();i++)
	{
		this->setDisplayMode(i, mode);
	}
}
int SevenSegmentsDisplay::getDisplayMode(int displayId)
{
	return this->_displaysMode[displayId];
}
