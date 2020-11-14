#pragma once

#include <exception>

using namespace std;

class AESException : public exception {

public:

	// 構造方法
	AESException(const int);

	// 靜態變數
	static const int INVILID_KEY_LENGTH = 0;
	static const int INVILID_IV_LENGTH = 1;
	static const int INVALID_PLAINTEXT_LENGHT = 2;
	static const int INVALID_CIPHERTEXT_LENGTH = 3;

	// 函式
	char * getDetail();

	int getType();


private:

	// 常數 
	int type;
	char * detail;

	// 函式
	void init(const int);



};

