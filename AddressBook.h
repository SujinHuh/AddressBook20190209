#pragma once
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H

#include"Array.h"
#include"Personal.h"
#include<string>
typedef signed long int Long;
using namespace std;

class AddressBook {
public:
	AddressBook(Long capacity = 125);
	AddressBook(const AddressBook& source);
	~AddressBook();
	Long Record(string name, string address, string telephoneNumber, string emailAddress);
	void Find(string name, Long *(*indexes), Long *count);
	Long Correct(Long index, string address, string telephoneNumber, string emailAddress);
	Long Erase(Long index);
	void Arrange();
	AddressBook& operator=(const AddressBook& source);
	Personal* operator+(Long index);
	Personal& operator[](Long index);
	Long GetCapacity() const;
	Long GetLength() const;
	Personal& GetAt(Long index);
private:
	Array<Personal> personals;
	Long capacity;
	Long length;
};
inline Long AddressBook::GetCapacity()const {
	return this->capacity;
}
inline Long AddressBook::GetLength()const {
	return this->length;
}
int CompareNames(void *one, void *other);
int ComparePersonals(void *one, void *other);

#endif // _ADDRESSBOOK_H