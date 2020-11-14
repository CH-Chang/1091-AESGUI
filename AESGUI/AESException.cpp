#include "AESException.h"

#include <exception>

using namespace std;

AESException::AESException(const int type) {
	this->init(type);
}


void AESException::init(const int type) {
	switch (type) {
	case AESException::INVILID_KEY_LENGTH:
		this->detail = "Invalid Key Length.";
		this->type = type;
		break;
	case AESException::INVILID_IV_LENGTH:
		this->detail = "Invalid IV Length.";
		this->type = type;
		break;
	case AESException::INVALID_PLAINTEXT_LENGHT:
		this->detail = "Invalid Plaintext Length.";
		this->type = type;
		break;
	case AESException::INVALID_CIPHERTEXT_LENGTH:
		this->detail = "Invalid Ciphertext Length.";
		this->type = type;
		break;
	default:
		this->detail = "Unknown Error";
		this->type = type;
		break;

	}
}

char * AESException::getDetail() {
	return this->detail;
}

int AESException::getType() {
	return this->type;
}