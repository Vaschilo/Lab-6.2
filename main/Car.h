#pragma once

#include <iostream>
using namespace std;

class Auto
{
private:
	string name;
	int speed;
	int price;
public:
	Auto() {}
	Auto(string name, int speed, int price) 
	{
		this->name = name;
		this->speed = speed;
		this->price = price;
	}

	string GetName() { return this->name; }
	int GetSpeed() { return this->speed; }
	int GetPrice() { return this->price; }

	void SetName(string name) { this->name = name; }
	void SetSpeed(int speed) { this->speed = speed; }
	void SetPrice(int price) { this->price = price; }

	void print()
	{
		cout << this->name << " " << this->speed << " " << this->price;
	}
};