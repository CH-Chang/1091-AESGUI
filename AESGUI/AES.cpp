#include "AES.h"
#include "AESException.h"

#include <string.h>
#include <algorithm>

using namespace std;

// �c�y��k 
AES::AES(const int aes, const int mode, const int paddingMode) {
	this->keySize_bit = aes;
	this->keySize_byte = this->keySize_bit / 8;
	this->keySize_word = this->keySize_byte / 4;
	this->mode = mode;
	this->paddingMode = paddingMode;
}

// ��l��key iv (���ѥ~���I�s) 
void AES::init(const char * key, const char * iv) {
	this->initKey(key);
	this->initIv(iv);
	this->initRound();
	this->keyExpansion();
}

// ��l��key 
void AES::initKey(const char * key) {
	int keySize_byte = strlen(key);

	if (keySize_byte != this->keySize_byte) {
		throw new AESException(AESException::INVILID_KEY_LENGTH);
	}

	if (this->key == NULL) {
		this->key = new unsigned char[this->keySize_byte];
	}
	else {
		delete[] this->key;
		this->key = NULL;
	}

	for (int i = 0; i < this->keySize_byte; i++) {
		(this->key)[i] = (unsigned char)key[i];
	}
}
void AES::initIv(const char * iv) {
	// ��l��iv�j�p 
	this->ivSize_bit = 128;
	this->ivSize_byte = this->ivSize_bit / 8;
	this->ivSize_word = this->ivSize_byte / 4;

	// ���o�ǤJ��iv�j�p 
	int ivSize_byte = strlen(iv);

	// �p�Giv�j�p���~�h�ߥX���` 
	if (this->mode != AES::ECB&&ivSize_byte != this->ivSize_byte) {
		throw new AESException(AESException::INVILID_IV_LENGTH);
	}

	// �ʺA�t�miv�O���� 
	if (this->iv == NULL) {
		this->iv = new unsigned char[this->ivSize_byte];
	}
	else {
		delete[] this->iv;
		this->iv = NULL;
	}

	// �Niv�ƻs�i�h 
	for (int i = 0; i < this->ivSize_byte; i++) {
		(this->iv)[i] = (unsigned char)iv[i];
	}
}
void AES::initRound() {
	// �T�{�n�]�X�� 
	this->round = 6 + max(4, this->keySize_word);
}

// AES��� 
void AES::keyExpansion() {
	// ��l��roundKey�j�p 
	this->roundKeyTotalSize_byte = (this->round + 1) * 16;
	this->roundKeyTotalSize_bit = this->roundKeyTotalSize_byte * 8;
	this->roundKeyTotalSize_word = this->roundKeyTotalSize_byte / 4;

	// �ʺA�t�mroundKey�O���� 
	if (this->roundKey == NULL) {
		this->roundKey = new unsigned char[this->roundKeyTotalSize_byte];
	}
	else {
		delete[] this->roundKey;
		this->roundKey = NULL;
	}

	// ��l�ƲĤ@�� 
	for (int i = 0; i < this->keySize_byte; i += 4) {
		(this->roundKey)[i] = (this->key)[i];
		(this->roundKey)[i + 1] = (this->key)[i + 1];
		(this->roundKey)[i + 2] = (this->key)[i + 2];
		(this->roundKey)[i + 3] = (this->key)[i + 3];
	}

	// �`�����ͨ�L�^�X
	for (int currentWord = this->keySize_word; currentWord < this->roundKeyTotalSize_word; currentWord++) {

		// �t�m��ӼȮɪ��ܼ� - operandFir = w[n-1]�AoperandSec = w[n-Nbk] 
		unsigned char * operandFir = new unsigned char[4];
		unsigned char * operandSec = new unsigned char[4];
		// �N�Ƚƻs�L��
		for (int i = 0; i < 4; i++) {
			operandFir[i] = roundKey[(currentWord - this->keySize_word) * 4 + i];
			operandSec[i] = roundKey[(currentWord - 1) * 4 + i];
		}

		// �ھڤ��PAES�����׶i�椣�P���B�z
		if (this->keySize_bit == AES::AES256) {
			if (currentWord%this->keySize_word == 0) {
				// �Ĥ@�B: �V�k�`���@��
				unsigned char cycle = operandSec[0];
				for (int i = 0; i < 3; i++) {
					operandSec[i] = operandSec[i + 1];
				}
				operandSec[3] = cycle;

				// �ĤG�B: S���N��
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}

				// �ĤT�B: ���`�q����
				operandSec[0] = operandSec[0] ^ this->Rcon[currentWord / this->keySize_word];

				// �ĥ|��: �x�sXOR���G 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}

			}
			else if (currentWord%this->keySize_word != 0 && currentWord % (this->keySize_word / 2) == 0) {
				// �Ĥ@�B: S���N��
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}
				// �ĤG�B: �x�sXOR���G 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
			else if (currentWord%this->keySize_word != 0) {
				// �Ĥ@�B: �x�sXOR���G 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
		}
		else if (this->keySize_bit == AES::AES128 || this->keySize_bit == AES::AES192) {
			if (currentWord%this->keySize_word == 0) {
				// �Ĥ@�B: �V�k�`���@��
				unsigned char cycle = operandSec[0];
				for (int i = 0; i < 3; i++) {
					operandSec[i] = operandSec[i + 1];
				}
				operandSec[3] = cycle;

				// �ĤG�B: S���N��
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}

				// �ĤT�B: ���`�q����
				operandSec[0] = operandSec[0] ^ this->Rcon[currentWord / this->keySize_word];

				// �ĥ|��: �x�sXOR���G 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
			else {
				// �Ĥ@�B: �x�sXOR���G 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
		}

		// �k�٨�ӼȮɭȵ�OS
		delete[] operandFir;
		delete[] operandSec;
	}
}
void AES::addRoundKey(const int round) {
	// �Nstate���ӨC�ӭȩM�ӽ���key�i��XOR�B�� 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (this->state)[i] ^ (this->roundKey)[16 * round + i];
	}
}

void AES::addInverseMixColumnRoundKey(const int round) {
	// �n�D�@�ӼȦsInverse Mix Column Round key���O���� 
	unsigned char * tempRoundKey = new unsigned char[16];

	// ��Round key��inverse mix column
	for (int i = 0; i < 4; i++) {
		// �d��
		tempRoundKey[i * 4] = (this->GMul_0e)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 1] = (this->GMul_09)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 2] = (this->GMul_0d)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 3] = (this->GMul_0b)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 3]];
	}

	// �Nstate���ӨC�ӭȩM�ӽ��i��Linverse mix column��key�i��XOR�B�� 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (this->state)[i] ^ tempRoundKey[i];
	}

	// ����O����
	delete[] tempRoundKey;
}

// AES�[�K��� 
void AES::SBoxSubstitution() {
	// �Nstate�����C�ӭȶi��SBox���d����� 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (unsigned char)this->SBox[(int)(this->state)[i]];
	}
}
void AES::shiftRows() {
	unsigned char tempState; // �ŧi�@�ӼȦs��

	//�Ĥ@�椣��
	//�ĤG��V�k�`���@��
	tempState = (this->state)[1];
	(this->state)[1] = (this->state)[5];
	(this->state)[5] = (this->state)[9];
	(this->state)[9] = (this->state)[13];
	(this->state)[13] = tempState;

	//�ĤT��V�k�`�����
	tempState = (this->state)[14];
	(this->state)[14] = (this->state)[6];
	(this->state)[6] = tempState;
	tempState = (this->state)[2];
	(this->state)[2] = (this->state)[10];
	(this->state)[10] = tempState;

	//�ĥ|��V�k�`���T��
	tempState = (this->state)[15];
	(this->state)[15] = (this->state)[11];
	(this->state)[11] = (this->state)[7];
	(this->state)[7] = (this->state)[3];
	(this->state)[3] = tempState;
}
void AES::mixColumn() {
	// �ʺA�ŧi�|�ӼȦs�ȰO���� 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		//�p���k 
		/*
		tempState[0] = this->GMul(0x02, (this->state)[i*4]) ^ this->GMul(0x03, (this->state)[i*4+1]) ^ (this->state)[i*4+2] ^ (this->state)[i*4+3];
		tempState[1] = (this->state)[i*4] ^ this->GMul(0x02, (this->state)[i*4+1]) ^ this->GMul(0x03, (this->state)[i*4+2]) ^ (this->state)[i*4+3];
		tempState[2] = (this->state)[i*4] ^ (this->state)[i*4+1] ^ this->GMul(0x02, (this->state)[i*4+2]) ^ this->GMul(0x03, (this->state)[i*4+3]);
		tempState[3] = this->GMul(0x03, (this->state)[i*4]) ^ (this->state)[i*4+1] ^ (this->state)[i*4+2] ^ this->GMul(0x02, (this->state)[i*4+3]);
		*/

		// �d���k
		tempState[0] = (this->GMul_02)[(this->state)[i * 4]] ^ (this->GMul_03)[(this->state)[i * 4 + 1]] ^ (this->state)[i * 4 + 2] ^ (this->state)[i * 4 + 3];
		tempState[1] = (this->state)[i * 4] ^ (this->GMul_02)[(this->state)[i * 4 + 1]] ^ (this->GMul_03)[(this->state)[i * 4 + 2]] ^ (this->state)[i * 4 + 3];
		tempState[2] = (this->state)[i * 4] ^ (this->state)[i * 4 + 1] ^ (this->GMul_02)[(this->state)[i * 4 + 2]] ^ (this->GMul_03)[(this->state)[i * 4 + 3]];
		tempState[3] = (this->GMul_03)[(this->state)[i * 4]] ^ (this->state)[i * 4 + 1] ^ (this->state)[i * 4 + 2] ^ (this->GMul_02)[(this->state)[i * 4 + 3]];


		// ��� 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// ����O���� 
	delete[] tempState;
}
void AES::TBoxSubstitution() {

	// �ʺA�ŧi�|�ӼȦs�ȰO���� 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		// �d��
		tempState[0] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][0]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][0]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][0]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][0]));
		tempState[1] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][1]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][1]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][1]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][1]));
		tempState[2] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][2]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][2]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][2]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][2]));
		tempState[3] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][3]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][3]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][3]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][3]));

		// ��� 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// ����O���� 
	delete[] tempState;
}

// AES�ѱK���
void AES::inverseSBoxSubstitution() {
	// �Nstate�����C�ӭȶi��InverseSBox���d����� 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (unsigned char)this->InverseSBox[(int)(this->state)[i]];
	}
}
void AES::inverseShiftRows() {
	unsigned char tempState; // �ŧi�@�ӼȦs��

	//�Ĥ@�椣��
	//�ĤG��V���`���@��
	tempState = (this->state)[13];
	(this->state)[13] = (this->state)[9];
	(this->state)[9] = (this->state)[5];
	(this->state)[5] = (this->state)[1];
	(this->state)[1] = tempState;

	//�ĤT��V���`�����
	tempState = (this->state)[6];
	(this->state)[6] = (this->state)[14];
	(this->state)[14] = tempState;
	tempState = (this->state)[10];
	(this->state)[10] = (this->state)[2];
	(this->state)[2] = tempState;

	//�ĥ|��V���`���T��
	tempState = (this->state)[3];
	(this->state)[3] = (this->state)[7];
	(this->state)[7] = (this->state)[11];
	(this->state)[11] = (this->state)[15];
	(this->state)[15] = tempState;
}
void AES::inverseMixColumn() {
	// �ʺA�ŧi�|�ӼȦs�ȰO���� 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		//�p���k 
		/*
		tempState[0] = this->GMul(0x0e, (this->state)[i*4]) ^ this->GMul(0x0b, (this->state)[i*4+1]) ^ this->GMul(0x0d, (this->state)[i*4+2]) ^ this->GMul(0x09, (this->state)[i*4+3]);
		tempState[1] = this->GMul(0x09, (this->state)[i*4]) ^ this->GMul(0x0e, (this->state)[i*4+1]) ^ this->GMul(0x0b, (this->state)[i*4+2]) ^ this->GMul(0x0d, (this->state)[i*4+3]);
		tempState[2] = this->GMul(0x0d, (this->state)[i*4]) ^ this->GMul(0x09, (this->state)[i*4+1]) ^ this->GMul(0x0e, (this->state)[i*4+2]) ^ this->GMul(0x0b, (this->state)[i*4+3]);
		tempState[3] = this->GMul(0x0b, (this->state)[i*4]) ^ this->GMul(0x0d, (this->state)[i*4+1]) ^ this->GMul(0x09, (this->state)[i*4+2]) ^ this->GMul(0x0e, (this->state)[i*4+3]);
		*/

		// �d���k
		tempState[0] = (this->GMul_0e)[(this->state)[i * 4]] ^ (this->GMul_0b)[(this->state)[i * 4 + 1]] ^ (this->GMul_0d)[(this->state)[i * 4 + 2]] ^ (this->GMul_09)[(this->state)[i * 4 + 3]];
		tempState[1] = (this->GMul_09)[(this->state)[i * 4]] ^ (this->GMul_0e)[(this->state)[i * 4 + 1]] ^ (this->GMul_0b)[(this->state)[i * 4 + 2]] ^ (this->GMul_0d)[(this->state)[i * 4 + 3]];
		tempState[2] = (this->GMul_0d)[(this->state)[i * 4]] ^ (this->GMul_09)[(this->state)[i * 4 + 1]] ^ (this->GMul_0e)[(this->state)[i * 4 + 2]] ^ (this->GMul_0b)[(this->state)[i * 4 + 3]];
		tempState[3] = (this->GMul_0b)[(this->state)[i * 4]] ^ (this->GMul_0d)[(this->state)[i * 4 + 1]] ^ (this->GMul_09)[(this->state)[i * 4 + 2]] ^ (this->GMul_0e)[(this->state)[i * 4 + 3]];

		// ��� 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// ����O���� 
	delete[] tempState;
}

void AES::inverseTBoxSubstitution() {

	// �ʺA�ŧi�|�ӼȦs�ȰO���� 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		// �d��
		tempState[0] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][0]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][0]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][0]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][0]));
		tempState[1] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][1]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][1]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][1]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][1]));
		tempState[2] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][2]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][2]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][2]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][2]));
		tempState[3] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][3]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][3]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][3]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][3]));

		// ��� 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// ����O���� 
	delete[] tempState;
}


// ��R 
void AES::padding() {

	// �Ȧs�쥻����j�p 
	int plaintextSize_byte = this->plaintextSize_byte;
	// �t�m�쥻����O����Ŷ�
	unsigned char * plaintext = new unsigned char[plaintextSize_byte];
	// �ƻs�쥻����
	for (int i = 0; i < plaintextSize_byte; i++) {
		plaintext[i] = this->plaintext[i];
	}

	if (this->paddingMode == AES::ZeroPadding) {

		// ���o���Ӷ�R�h�֤j�p 
		int fillSize_byte = (plaintextSize_byte % 16 == 0) ? 16 : (16 - plaintextSize_byte % 16);

		// ���o��R��plaintext�j�p
		int newPlaintextSize_byte = plaintextSize_byte + fillSize_byte;

		// �N��R�᪺�����J���ܼƤ�
		// �t�m����O����Ŷ� 
		if (this->plaintext == NULL) {
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->plaintext;
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		// �t�m�K��O����Ŷ�
		if (this->ciphertext == NULL) {
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->ciphertext;
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}

		// ���ƻs�즳������
		for (int i = 0; i < plaintextSize_byte; i++) {
			(this->plaintext)[i] = plaintext[i];
		}
		// �B�z��R���� - ��R0 
		for (int i = plaintextSize_byte; i < newPlaintextSize_byte; i++) {
			(this->plaintext)[i] = 0;
		}

		// �x�s����j�p
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
		// �x�s�K��j�p - �ھ�AES���S�x�[�K�e�᪺�j�p�ۦP
		this->ciphertextSize_byte = this->plaintextSize_byte;
		this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
		this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	}
	else if (this->paddingMode == AES::PKCS7Padding) {

		// ���o���Ӷ�R�h�֤j�p 
		int fillSize_byte = (plaintextSize_byte % 16 == 0) ? 16 : (16 - plaintextSize_byte % 16);

		// ���o��R��plaintext�j�p
		int newPlaintextSize_byte = plaintextSize_byte + fillSize_byte;

		// ���o�n��R���Ӧr
		unsigned char filler = (unsigned char)fillSize_byte;

		// �N��R�᪺�����J���ܼƤ�
		// �t�m����O����Ŷ� 
		if (this->plaintext == NULL) {
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->plaintext;
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		// �t�m�K��O����Ŷ�
		if (this->ciphertext == NULL) {
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->ciphertext;
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}

		// ���ƻs�즳������
		for (int i = 0; i < plaintextSize_byte; i++) {
			(this->plaintext)[i] = plaintext[i];
		}
		// �B�z��R���� - ��Rfiller
		for (int i = plaintextSize_byte; i < newPlaintextSize_byte; i++) {
			(this->plaintext)[i] = filler;
		}

		// �x�s����j�p
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
		// �x�s�K��j�p - �ھ�AES���S�x�[�K�e�᪺�j�p�ۦP
		this->ciphertextSize_byte = this->plaintextSize_byte;
		this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
		this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	}
	// NoPadding ���γB�z 

	// ����쥻����O����Ŷ� 
	delete[] plaintext;
}
// �Ѷ�R 
void AES::unpadding() {

	// �t�m�쥻����O����Ŷ�
	unsigned char * plaintext = new unsigned char[plaintextSize_byte];
	// �ƻs�쥻����
	for (int i = 0; i < plaintextSize_byte; i++) {
		plaintext[i] = this->plaintext[i];
	}


	if (this->paddingMode == AES::ZeroPadding) {

		// �Ȧs�쥻����j�p 
		int newPlaintextSize_byte = this->plaintextSize_byte;

		// �B��q�e���O�d�h�֦r�� 
		for (int i = this->plaintextSize_byte - 1; i >= 0; i--) {
			if (this->plaintext[i] == 0x00) {
				newPlaintextSize_byte--;
			}

			if (i != 0) {
				if (this->plaintext[i - 1] != 0x00) {
					break;
				}
			}
		}

		// ���s�t�m����O����
		delete[] this->plaintext;
		this->plaintext = new unsigned char[newPlaintextSize_byte];

		// �ƻs���e
		for (int i = 0; i < newPlaintextSize_byte; i++) {
			this->plaintext[i] = plaintext[i];
		}

		// ��s����j�p����
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;

	}
	else if (this->paddingMode == AES::PKCS7Padding) {
		int newPlaintextSize_byte = this->plaintextSize_byte - (int)this->plaintext[this->plaintextSize_byte - 1];

		// ���s�t�m����O����
		delete[] this->plaintext;
		this->plaintext = new unsigned char[newPlaintextSize_byte];

		// �ƻs���e
		for (int i = 0; i < newPlaintextSize_byte; i++) {
			this->plaintext[i] = plaintext[i];
		}

		// ��s����j�p����
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
	}
	// NoPadding���γB�z 

	// ����쥻����O����Ŷ� 
	delete[] plaintext;


}

// �[�K�� - �N128bit�������mstate��I�s�A�[�K�����ᵲ�G��state 
void AES::encryptor() {

	// �Ĥ@��Add Round Key
	this->addRoundKey(0);

	// �`�������ѤU��
	for (int i = 1; i <= this->round; i++) {
		// SBox���� 
		this->SBoxSubstitution();
		// �C���� 
		this->shiftRows();
		// ��V�X(�̫�@������)
		if (i != this->round) {
			this->mixColumn();
		}
		// ���K�_�[
		this->addRoundKey(i);
	}


}

void AES::quickEncryptor() {

	// �Ĥ@��Add Round Key
	this->addRoundKey(0);

	// �`�������ѤU��
	for (int i = 1; i <= this->round; i++) {
		// �C���� 
		this->shiftRows();

		// T���d��(�̫�@���u��S������) 
		if (i == this->round) {
			this->SBoxSubstitution();
		}
		else {
			this->TBoxSubstitution();
		}

		// ���K�_�[
		this->addRoundKey(i);
	}


}

void AES::ECBEncrypt() {
	// �`�������N����[�K 
	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// ��m128bit�������state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->plaintext)[i + j];
			(this->state)[j + 1] = (this->plaintext)[i + j + 1];
			(this->state)[j + 2] = (this->plaintext)[i + j + 2];
			(this->state)[j + 3] = (this->plaintext)[i + j + 3];
		}

		// �I�s�[�K���[�K�Ӷ�
		this->quickEncryptor();

		// �qstate���X�[�K�᪺���G
		for (int j = 0; j < 16; j++) {
			(this->ciphertext)[i + j] = (this->state)[j];
		}
	}
}
void AES::CBCEncrypt() {

	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// ����e�m�B�z 
		if (i == 0) {
			// �Ĥ@������Miv��XOR
			for (int j = 0; j < 16; j += 4) {
				(this->state)[j] = (this->plaintext)[j] ^ (this->iv)[j];
				(this->state)[j + 1] = (this->plaintext)[j + 1] ^ (this->iv)[j + 1];
				(this->state)[j + 2] = (this->plaintext)[j + 2] ^ (this->iv)[j + 2];
				(this->state)[j + 3] = (this->plaintext)[j + 3] ^ (this->iv)[j + 3];
			}
		}
		else {
			// ����C�@������M�W�@�����ͪ��K��i��XOR
			for (int j = 0; j < 16; j += 4) {
				(this->state)[j] = (this->plaintext)[i + j] ^ (this->ciphertext)[i - 16 + j];
				(this->state)[j + 1] = (this->plaintext)[i + j + 1] ^ (this->ciphertext)[i - 16 + j + 1];
				(this->state)[j + 2] = (this->plaintext)[i + j + 2] ^ (this->ciphertext)[i - 16 + j + 2];
				(this->state)[j + 3] = (this->plaintext)[i + j + 3] ^ (this->ciphertext)[i - 16 + j + 3];
			}
		}

		// �[�K 
		this->quickEncryptor();

		// �qstate�ƻs�X���G��ciphertext
		for (int j = 0; j < 16; j++) {
			(this->ciphertext)[i + j] = (this->state)[j];
		}

	}
}
void AES::OFB8Encrypt() {
	// �إߤ@�ӼȦsiv�ȤμȦs�[�Kiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i++) {

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// �N���G�qstate�ƻs�X��
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// ���o�K��@�� - ����8��bit(1��byte)�P�[�KIV���̰�8��bit(1��byte)�i��XOR
		(this->ciphertext)[i] = (this->plaintext)[i] ^ encryptedIv[0];

		// �Ȧsiv�V����8��bit(1��byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// �Ȧsiv���̫�8��bit(1��byte)�ѭ����o��8��bit(1��byte)�[�KIV�ɤW
		tempIv[15] = encryptedIv[0];
	}

	// �k�ټȦsIV�μȦs�[�Kiv�Ȫ��O���� 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CFB8Encrypt() {

	// �إߤ@�ӼȦsiv�ȤμȦs�[�Kiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i++) {

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// �N���G�qstate�ƻs�X��
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// ���o�K��@�� - ����8��bit(1��byte)�P�[�KIV���̰�8��bit(1��byte)�i��XOR
		(this->ciphertext)[i] = (this->plaintext)[i] ^ encryptedIv[0];

		// �Ȧsiv�V����8��bit(1��byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// �Ȧsiv���̫�8��bit(1��byte)�ѭ����o��8��bit(1��byte)�K��ɤW
		tempIv[15] = (this->ciphertext)[i];
	}

	// �k�ټȦsIV�μȦs�[�Kiv�Ȫ��O���� 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CTREncrypt() {
	// �إߤ@�ӼȦsiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// �p�ƾ��V�W�[
		tempIv[15] += i / 16;

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// ����P�[�Kiv�������XOR
		for (int j = 0; j < 16; j++) {
			if (i + j == this->plaintextSize_byte) {
				break;
			}

			(this->ciphertext)[i + j] = (this->state)[j] ^ (this->plaintext)[i + j];
		}
	}

	// �k�ټȦsIV���O���� 
	delete[] tempIv;
}


// �ѱK�� - �N128bit�����m��state��I�s�A�ѱK�����ᵲ�G��state 
void AES::decryptor() {
	for (int i = this->round; i >= 1; i--) {
		//���K�_�[
		this->addRoundKey(i);
		// �f��V�X(�Ĥ@������)
		if (i != this->round) {
			this->inverseMixColumn();
		}
		// �f�沾��
		this->inverseShiftRows();
		// �fSBox����
		this->inverseSBoxSubstitution();
	}

	this->addRoundKey(0);
}

void AES::quickDecryptor() {


	this->addRoundKey(this->round);

	for (int i = this->round - 1; i >= 0; i--) {
		// �f�沾��
		this->inverseShiftRows();

		// �fT���N��(�̫�@���u���fS���N��) 
		if (i == 0) {
			this->inverseSBoxSubstitution();
		}
		else {
			this->inverseTBoxSubstitution();
		}

		// �̫�@����key���ΰ�inverse mix column 
		if (i == 0) {
			this->addRoundKey(i);
		}
		else {
			this->addInverseMixColumnRoundKey(i);
		}


	}


}

void AES::ECBDecrypt() {
	// �`�������N�K��ѱK 
	for (int i = 0; i < this->ciphertextSize_byte; i += 16) {

		// ��m128bit���K���state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->ciphertext)[i + j];
			(this->state)[j + 1] = (this->ciphertext)[i + j + 1];
			(this->state)[j + 2] = (this->ciphertext)[i + j + 2];
			(this->state)[j + 3] = (this->ciphertext)[i + j + 3];
		}

		// �I�s�[�K���[�K�Ӷ�
		this->quickDecryptor();

		// �qstate���X�[�K�᪺���G
		for (int j = 0; j < 16; j++) {
			(this->plaintext)[i + j] = (this->state)[j];
		}
	}
}
void AES::CBCDecrypt() {
	// �q�̫�@���}�l�ѱK
	for (int i = this->ciphertextSize_byte - 16; i >= 0; i -= 16) {

		// �����Ӷ��K��ѱK 
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->ciphertext)[i + j];
			(this->state)[j + 1] = (this->ciphertext)[i + j + 1];
			(this->state)[j + 2] = (this->ciphertext)[i + j + 2];
			(this->state)[j + 3] = (this->ciphertext)[i + j + 3];
		}

		// �I�s�ѱK���ѱK�Ӷ�
		this->quickDecryptor();

		if (i == 0) {
			// �̫�@���n��IV��XOR���o���� 
			for (int j = 0; j < 16; j += 4) {
				(this->plaintext)[j] = (this->state)[j] ^ (this->iv)[j];
				(this->plaintext)[j + 1] = (this->state)[j + 1] ^ (this->iv)[j + 1];
				(this->plaintext)[j + 2] = (this->state)[j + 2] ^ (this->iv)[j + 2];
				(this->plaintext)[j + 3] = (this->state)[j + 3] ^ (this->iv)[j + 3];
			}
		}
		else {
			// ��L�P�U�@���q�n�B�z���K�尵XOR 
			for (int j = 0; j < 16; j += 4) {
				(this->plaintext)[i + j] = (this->state)[j] ^ (this->ciphertext)[i - 16 + j];
				(this->plaintext)[i + j + 1] = (this->state)[j + 1] ^ (this->ciphertext)[i - 16 + j + 1];
				(this->plaintext)[i + j + 2] = (this->state)[j + 2] ^ (this->ciphertext)[i - 16 + j + 2];
				(this->plaintext)[i + j + 3] = (this->state)[j + 3] ^ (this->ciphertext)[i - 16 + j + 3];
			}
		}
	}
}
void AES::OFB8Decrypt() {
	// OFB�Ҧ��[�K�P�ѱK�ۦP

	// �إߤ@�ӼȦsiv�ȤμȦs�[�Kiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i++) {

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// �N���G�qstate�ƻs�X��
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// ���o�K��@�� - ����8��bit(1��byte)�P�[�KIV���̰�8��bit(1��byte)�i��XOR
		(this->plaintext)[i] = (this->ciphertext)[i] ^ encryptedIv[0];

		// �Ȧsiv�V����8��bit(1��byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// �Ȧsiv���̫�8��bit(1��byte)�ѭ����o��8��bit(1��byte)�[�KIV�ɤW
		tempIv[15] = encryptedIv[0];
	}

	// �k�ټȦsIV�μȦs�[�Kiv�Ȫ��O���� 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CFB8Decrypt() {

	// CFB�Ҧ��[�K�P�ѱK�ۦP 

	// �إߤ@�ӼȦsiv�ȤμȦs�[�Kiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i++) {

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// �N���G�qstate�ƻs�X��
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// ���o�K��@�� - ����8��bit(1��byte)�P�[�KIV���̰�8��bit(1��byte)�i��XOR
		(this->plaintext)[i] = (this->ciphertext)[i] ^ encryptedIv[0];

		// �Ȧsiv�V����8��bit(1��byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// �Ȧsiv���̫�8��bit(1��byte)�ѭ����o��8��bit(1��byte)�K��ɤW
		tempIv[15] = (this->ciphertext)[i];
	}

	// �k�ټȦsIV�μȦs�[�Kiv�Ȫ��O���� 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CTRDecrypt() {
	// �إߤ@�ӼȦsiv�Ȩðt�m�O����Ŷ�
	unsigned char * tempIv = new unsigned char[16];

	// �N�쥻iv�ƻs�i�Ȧsiv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i += 16) {

		// �p�ƾ��V�W�[
		tempIv[15] += i / 16;

		// �[�Kiv
		// �ƻs�Ȧsiv�istate
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// ����[�K��
		this->quickEncryptor();

		// ����P�[�Kiv�������XOR
		for (int j = 0; j < 16; j++) {
			if (i + j == this->ciphertextSize_byte) {
				break;
			}

			(this->plaintext)[i + j] = (this->state)[j] ^ (this->ciphertext)[i + j];
		}
	}

	// �k�ټȦsIV���O���� 
	delete[] tempIv;
}



// �[�K (���ѥ~���I�s) 
void AES::encrypt(const char * plaintext, const int plaintextSize_byte, unsigned char ** result, int * resultSize_byte) {


	// �t�m����O����
	if (this->plaintext == NULL) {
		this->plaintext = new unsigned char[plaintextSize_byte];
	}
	else {
		delete[] this->plaintext;
		this->plaintext = new unsigned char[plaintextSize_byte];
	}

	// �t�m�K��O����
	if (this->ciphertext == NULL) {
		this->ciphertext = new unsigned char[plaintextSize_byte];
	}
	else {
		delete[] this->ciphertext;
		this->ciphertext = new unsigned char[plaintextSize_byte];
	}

	// �x�s����j�p
	this->plaintextSize_byte = plaintextSize_byte;
	this->plaintextSize_bit = this->plaintextSize_byte * 8;
	this->plaintextSize_word = this->plaintextSize_byte / 4;

	// �x�s�K��j�p
	this->ciphertextSize_byte = plaintextSize_byte;
	this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
	this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	// �ƻs����i�J���ܼ� 
	for (int i = 0; i < plaintextSize_byte; i++) {
		this->plaintext[i] = plaintext[i];
	}

	// �t�mstate�Ŷ�
	this->state = new unsigned char[16];


	// �I�spadding
	this->padding();

	// �T�w����j�p�O�_�ŦX�ӼҦ��n�D - ECB��CBC�Ҧ��n�D��R�᪺����j�p��128bit������
	// �Y���ŦX�h�ߥX������׿��~���` 
	if ((this->mode == AES::ECB || this->mode == AES::CBC) && this->plaintextSize_bit % 128 != 0) {
		throw new AESException(AESException::INVALID_PLAINTEXT_LENGHT);
	}

	// �ھڭn�D�Ҧ��i��[�K
	if (this->mode == AES::ECB) {
		this->ECBEncrypt();
	}
	else if (this->mode == AES::CBC) {
		this->CBCEncrypt();
	}
	else if (this->mode == AES::OFB8) {
		this->OFB8Encrypt();
	}
	else if (this->mode == AES::CFB8) {
		this->CFB8Encrypt();
	}
	else if (this->mode == AES::CTR) {
		this->CTREncrypt();
	}

	// ��m���G
	// ��m���G�j�p
	*resultSize_byte = this->ciphertextSize_byte;
	// �t�m���G�O���� 
	*result = new unsigned char[*resultSize_byte];
	// ��m���G
	for (int i = 0; i < *resultSize_byte; i++) {
		*(*result + i) = this->ciphertext[i];
	}


	// �k��state�Ŷ�
	delete[] this->state;
	this->state = NULL;

	// �k�٩���Ŷ�
	delete[] this->plaintext;
	this->plaintext = NULL;

	// �k�ٱK��Ŷ�
	delete[] this->ciphertext;
	this->ciphertext = NULL;

	// �M������Ŷ��j�p����
	this->plaintextSize_bit = -1;
	this->plaintextSize_byte = -1;
	this->plaintextSize_word = -1;

	// �M���K��Ŷ��j�p����
	this->ciphertextSize_bit = -1;
	this->ciphertextSize_byte = -1;
	this->ciphertextSize_word = -1;

}

// �ѱK (���ѥ~���I�s) 
void AES::decrypt(const unsigned char * ciphertext, const int ciphertextSize_byte, char ** result, int * resultSize_byte) {

	// �t�m����O����
	if (this->plaintext == NULL) {
		this->plaintext = new unsigned char[ciphertextSize_byte];
	}
	else {
		delete[] this->plaintext;
		this->plaintext = new unsigned char[ciphertextSize_byte];
	}

	// �t�m�K��O����
	if (this->ciphertext == NULL) {
		this->ciphertext = new unsigned char[ciphertextSize_byte];
	}
	else {
		delete[] this->ciphertext;
		this->ciphertext = new unsigned char[ciphertextSize_byte];
	}

	// �x�s����j�p
	this->plaintextSize_byte = ciphertextSize_byte;
	this->plaintextSize_bit = this->plaintextSize_byte * 8;
	this->plaintextSize_word = this->plaintextSize_byte / 4;

	// �x�s�K��j�p
	this->ciphertextSize_byte = ciphertextSize_byte;
	this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
	this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	// �ƻs�K��i�h
	for (int i = 0; i < ciphertextSize_byte; i++) {
		this->ciphertext[i] = ciphertext[i];
	}

	// �t�mstate�Ŷ�
	this->state = new unsigned char[16];

	// �T�w�K��j�p�O�_�ŦX�ӼҦ��n�D - ECB��CBC�Ҧ��n�D�K��j�p��128bit������
	// �Y���ŦX�h�ߥX�K����׿��~���` 
	if ((this->mode == AES::ECB || this->mode == AES::CBC) && this->ciphertextSize_bit % 128 != 0) {
		throw new AESException(AESException::INVALID_CIPHERTEXT_LENGTH);
	}

	// �ھڭn�D�Ҧ��i��ѱK 
	if (this->mode == AES::ECB) {
		this->ECBDecrypt();
	}
	else if (this->mode == AES::CBC) {
		this->CBCDecrypt();
	}
	else if (this->mode == AES::OFB8) {
		this->OFB8Decrypt();
	}
	else if (this->mode == AES::CFB8) {
		this->CFB8Decrypt();
	}
	else if (this->mode == AES::CTR) {
		this->CTRDecrypt();
	}

	// �Ѷ�R
	this->unpadding();

	// ��m���G
	// ��m���G�j�p
	*resultSize_byte = this->plaintextSize_byte;
	// �t�m���G�O���� 
	*result = new char[*resultSize_byte+1];
	// ��m���G
	for (int i = 0; i < *resultSize_byte; i++) {
		*(*result + i) = this->plaintext[i];
	}
	*(*result + *resultSize_byte) = '\0';

	// �k��state�Ŷ�
	delete[] this->state;
	this->state = NULL;

	// �k�٩���Ŷ�
	delete[] this->plaintext;
	this->plaintext = NULL;

	// �k�ٱK��Ŷ�
	delete[] this->ciphertext;
	this->ciphertext = NULL;

	// �M������Ŷ��j�p����
	this->plaintextSize_bit = -1;
	this->plaintextSize_byte = -1;
	this->plaintextSize_word = -1;

	// �M���K��Ŷ��j�p����
	this->ciphertextSize_bit = -1;
	this->ciphertextSize_byte = -1;
	this->ciphertextSize_word = -1;

}





int AES::GMul(int u, int v) {
	int p = 0;
	for (int i = 0; i < 8; ++i) {
		if (u & 0x01) {
			p ^= v;
		}

		int flag = (v & 0x80);
		v <<= 1;
		if (flag) {
			v ^= 0x1B;  /* P(x) = x^8 + x^4 + x^3 + x + 1 */
		}

		u >>= 1;
	}
	return p;
}


