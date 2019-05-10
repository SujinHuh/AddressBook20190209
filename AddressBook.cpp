#include "AddressBook.h"

//생성자
AddressBook::AddressBook(Long capacity)
	:personals(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

AddressBook::AddressBook(const AddressBook& source)
	:personals(source.personals)
{
	this->capacity = source.capacity;
	this->length = source.length;
}
AddressBook::~AddressBook() {
}
Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress) {
	Long index;

	Personal personal(name, address, telephoneNumber, emailAddress);
	if (this->length < this->capacity) {
		index = this->personals.Store(this->length, personal);
	}
	else {
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;
	return index;
}

void AddressBook::Find(string name, Long *(*indexes), Long *count) {
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareNames);
}

Long AddressBook::Erase(Long index) {
	index = this->personals.Delete(index);
	this->capacity--;
	this->length--;
	return index;
}

Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress) {

	Personal personal = this->personals.GetAt(index);
	personal = Personal(personal.GetName(), address, telephoneNumber, emailAddress);
	index = this->personals.Modify(index, personal);
	return index;
}

void AddressBook::Arrange() {
	this->personals.SelectionSort(ComparePersonals);
}

Personal& AddressBook::GetAt(Long index) {
	return this->personals.GetAt(index);
}

AddressBook& AddressBook::operator=(const AddressBook& source) {
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

Personal* AddressBook::operator+(Long index) {
	return this->personals + index;
}

Personal& AddressBook::operator[](Long index) {
	return this->personals[index];
}

#include<string>
#include<iostream>
using namespace std;

int main(int argc, char *argv[]) {

	AddressBook addressBook(3);
	Personal personal;
	Long index;
	Long(*indexes);
	Long count;
	Long i;

	index = addressBook.Record("홍길동", "서울마포구", "021111111", "hong@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;

	index = addressBook.Record("이길동", "경기시흥", "0311231233", "Lee@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;

	index = addressBook.Record("홍길동", "서울송파구", "023333333", "hong2@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;

	index = addressBook.Record("고길동", "부산시남구", "0519999999", "go@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;


	addressBook.Find("홍길동", &indexes, &count);
	i = 0;
	cout << "홍길동찾기" << endl;
	while (i < count) {
		personal = addressBook.GetAt(indexes[i]);
		cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		i++;
	}

	cout << "수정하기" << endl;
	index = addressBook.Correct(indexes[1], "제주공항동", "0501231233", "hong@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;

	//삭제
	index = addressBook.Erase(2);
	if (index == -1) {
		cout << "지워졌습니다" << endl;
	}
	i = 0;
	while (i < addressBook.GetLength()) {
		personal = addressBook.GetAt(i);
		cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		i++;
	}

	cout << "정리하기" << endl;
	addressBook.Arrange();
	i = 0;
	while (i < addressBook.GetLength()) {
		personal = addressBook.GetAt(i);
		cout << personal.GetName() << "-" << personal.GetAddress() << "-" << personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[]indexes;
	}
	return 0;
}
int CompareNames(void *one, void *other) {
	Personal* one_ = static_cast<Personal*>(one);
	string* other_ = static_cast<string*>(other);

	return one_->GetName().compare(*other_);
}
int ComparePersonals(void *one, void *other) {
	Personal* one_ = static_cast<Personal*>(one);
	Personal* other_ = static_cast<Personal*>(other);

	return one_->GetName().compare(other_->GetName());
}