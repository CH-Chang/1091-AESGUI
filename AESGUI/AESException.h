#pragma once

#include <exception>

using namespace std;

class AESException : public exception {

public:

	// �c�y��k
	AESException(const int);

	// �R�A�ܼ�
	static const int INVILID_KEY_LENGTH = 0;
	static const int INVILID_IV_LENGTH = 1;
	static const int INVALID_PLAINTEXT_LENGHT = 2;
	static const int INVALID_CIPHERTEXT_LENGTH = 3;

	// �禡
	char * getDetail();

	int getType();


private:

	// �`�� 
	int type;
	char * detail;

	// �禡
	void init(const int);



};

