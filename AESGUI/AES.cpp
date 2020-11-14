#include "AES.h"
#include "AESException.h"

#include <string.h>
#include <algorithm>

using namespace std;

// 構造方法 
AES::AES(const int aes, const int mode, const int paddingMode) {
	this->keySize_bit = aes;
	this->keySize_byte = this->keySize_bit / 8;
	this->keySize_word = this->keySize_byte / 4;
	this->mode = mode;
	this->paddingMode = paddingMode;
}

// 初始化key iv (提供外部呼叫) 
void AES::init(const char * key, const char * iv) {
	this->initKey(key);
	this->initIv(iv);
	this->initRound();
	this->keyExpansion();
}

// 初始化key 
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
	// 初始化iv大小 
	this->ivSize_bit = 128;
	this->ivSize_byte = this->ivSize_bit / 8;
	this->ivSize_word = this->ivSize_byte / 4;

	// 取得傳入的iv大小 
	int ivSize_byte = strlen(iv);

	// 如果iv大小錯誤則拋出異常 
	if (this->mode != AES::ECB&&ivSize_byte != this->ivSize_byte) {
		throw new AESException(AESException::INVILID_IV_LENGTH);
	}

	// 動態配置iv記憶體 
	if (this->iv == NULL) {
		this->iv = new unsigned char[this->ivSize_byte];
	}
	else {
		delete[] this->iv;
		this->iv = NULL;
	}

	// 將iv複製進去 
	for (int i = 0; i < this->ivSize_byte; i++) {
		(this->iv)[i] = (unsigned char)iv[i];
	}
}
void AES::initRound() {
	// 確認要跑幾輪 
	this->round = 6 + max(4, this->keySize_word);
}

// AES函數 
void AES::keyExpansion() {
	// 初始化roundKey大小 
	this->roundKeyTotalSize_byte = (this->round + 1) * 16;
	this->roundKeyTotalSize_bit = this->roundKeyTotalSize_byte * 8;
	this->roundKeyTotalSize_word = this->roundKeyTotalSize_byte / 4;

	// 動態配置roundKey記憶體 
	if (this->roundKey == NULL) {
		this->roundKey = new unsigned char[this->roundKeyTotalSize_byte];
	}
	else {
		delete[] this->roundKey;
		this->roundKey = NULL;
	}

	// 初始化第一輪 
	for (int i = 0; i < this->keySize_byte; i += 4) {
		(this->roundKey)[i] = (this->key)[i];
		(this->roundKey)[i + 1] = (this->key)[i + 1];
		(this->roundKey)[i + 2] = (this->key)[i + 2];
		(this->roundKey)[i + 3] = (this->key)[i + 3];
	}

	// 循環產生其他回合
	for (int currentWord = this->keySize_word; currentWord < this->roundKeyTotalSize_word; currentWord++) {

		// 配置兩個暫時的變數 - operandFir = w[n-1]，operandSec = w[n-Nbk] 
		unsigned char * operandFir = new unsigned char[4];
		unsigned char * operandSec = new unsigned char[4];
		// 將值複製過來
		for (int i = 0; i < 4; i++) {
			operandFir[i] = roundKey[(currentWord - this->keySize_word) * 4 + i];
			operandSec[i] = roundKey[(currentWord - 1) * 4 + i];
		}

		// 根據不同AES塊長度進行不同的處理
		if (this->keySize_bit == AES::AES256) {
			if (currentWord%this->keySize_word == 0) {
				// 第一步: 向右循環一位
				unsigned char cycle = operandSec[0];
				for (int i = 0; i < 3; i++) {
					operandSec[i] = operandSec[i + 1];
				}
				operandSec[3] = cycle;

				// 第二步: S盒代換
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}

				// 第三步: 輪常量異或
				operandSec[0] = operandSec[0] ^ this->Rcon[currentWord / this->keySize_word];

				// 第四部: 儲存XOR結果 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}

			}
			else if (currentWord%this->keySize_word != 0 && currentWord % (this->keySize_word / 2) == 0) {
				// 第一步: S盒代換
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}
				// 第二步: 儲存XOR結果 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
			else if (currentWord%this->keySize_word != 0) {
				// 第一步: 儲存XOR結果 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
		}
		else if (this->keySize_bit == AES::AES128 || this->keySize_bit == AES::AES192) {
			if (currentWord%this->keySize_word == 0) {
				// 第一步: 向右循環一位
				unsigned char cycle = operandSec[0];
				for (int i = 0; i < 3; i++) {
					operandSec[i] = operandSec[i + 1];
				}
				operandSec[3] = cycle;

				// 第二步: S盒代換
				for (int i = 0; i < 4; i++) {
					operandSec[i] = (unsigned char)this->SBox[(int)operandSec[i]];
				}

				// 第三步: 輪常量異或
				operandSec[0] = operandSec[0] ^ this->Rcon[currentWord / this->keySize_word];

				// 第四部: 儲存XOR結果 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
			else {
				// 第一步: 儲存XOR結果 
				for (int i = 0; i < 4; i++) {
					roundKey[currentWord * 4 + i] = operandFir[i] ^ operandSec[i];
				}
			}
		}

		// 歸還兩個暫時值給OS
		delete[] operandFir;
		delete[] operandSec;
	}
}
void AES::addRoundKey(const int round) {
	// 將state中個每個值和該輪的key進行XOR運算 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (this->state)[i] ^ (this->roundKey)[16 * round + i];
	}
}

void AES::addInverseMixColumnRoundKey(const int round) {
	// 要求一個暫存Inverse Mix Column Round key的記憶體 
	unsigned char * tempRoundKey = new unsigned char[16];

	// 對Round key做inverse mix column
	for (int i = 0; i < 4; i++) {
		// 查表
		tempRoundKey[i * 4] = (this->GMul_0e)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 1] = (this->GMul_09)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 2] = (this->GMul_0d)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0b)[(this->roundKey)[16 * round + i * 4 + 3]];
		tempRoundKey[i * 4 + 3] = (this->GMul_0b)[(this->roundKey)[16 * round + i * 4]] ^ (this->GMul_0d)[(this->roundKey)[16 * round + i * 4 + 1]] ^ (this->GMul_09)[(this->roundKey)[16 * round + i * 4 + 2]] ^ (this->GMul_0e)[(this->roundKey)[16 * round + i * 4 + 3]];
	}

	// 將state中個每個值和該輪進行過inverse mix column的key進行XOR運算 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (this->state)[i] ^ tempRoundKey[i];
	}

	// 釋放記憶體
	delete[] tempRoundKey;
}

// AES加密函數 
void AES::SBoxSubstitution() {
	// 將state中的每個值進行SBox的查表對應 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (unsigned char)this->SBox[(int)(this->state)[i]];
	}
}
void AES::shiftRows() {
	unsigned char tempState; // 宣告一個暫存值

	//第一行不動
	//第二行向右循環一位
	tempState = (this->state)[1];
	(this->state)[1] = (this->state)[5];
	(this->state)[5] = (this->state)[9];
	(this->state)[9] = (this->state)[13];
	(this->state)[13] = tempState;

	//第三行向右循環兩位
	tempState = (this->state)[14];
	(this->state)[14] = (this->state)[6];
	(this->state)[6] = tempState;
	tempState = (this->state)[2];
	(this->state)[2] = (this->state)[10];
	(this->state)[10] = tempState;

	//第四行向右循環三位
	tempState = (this->state)[15];
	(this->state)[15] = (this->state)[11];
	(this->state)[11] = (this->state)[7];
	(this->state)[7] = (this->state)[3];
	(this->state)[3] = tempState;
}
void AES::mixColumn() {
	// 動態宣告四個暫存值記憶體 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		//計算方法 
		/*
		tempState[0] = this->GMul(0x02, (this->state)[i*4]) ^ this->GMul(0x03, (this->state)[i*4+1]) ^ (this->state)[i*4+2] ^ (this->state)[i*4+3];
		tempState[1] = (this->state)[i*4] ^ this->GMul(0x02, (this->state)[i*4+1]) ^ this->GMul(0x03, (this->state)[i*4+2]) ^ (this->state)[i*4+3];
		tempState[2] = (this->state)[i*4] ^ (this->state)[i*4+1] ^ this->GMul(0x02, (this->state)[i*4+2]) ^ this->GMul(0x03, (this->state)[i*4+3]);
		tempState[3] = this->GMul(0x03, (this->state)[i*4]) ^ (this->state)[i*4+1] ^ (this->state)[i*4+2] ^ this->GMul(0x02, (this->state)[i*4+3]);
		*/

		// 查表方法
		tempState[0] = (this->GMul_02)[(this->state)[i * 4]] ^ (this->GMul_03)[(this->state)[i * 4 + 1]] ^ (this->state)[i * 4 + 2] ^ (this->state)[i * 4 + 3];
		tempState[1] = (this->state)[i * 4] ^ (this->GMul_02)[(this->state)[i * 4 + 1]] ^ (this->GMul_03)[(this->state)[i * 4 + 2]] ^ (this->state)[i * 4 + 3];
		tempState[2] = (this->state)[i * 4] ^ (this->state)[i * 4 + 1] ^ (this->GMul_02)[(this->state)[i * 4 + 2]] ^ (this->GMul_03)[(this->state)[i * 4 + 3]];
		tempState[3] = (this->GMul_03)[(this->state)[i * 4]] ^ (this->state)[i * 4 + 1] ^ (this->state)[i * 4 + 2] ^ (this->GMul_02)[(this->state)[i * 4 + 3]];


		// 賦值 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// 釋放記憶體 
	delete[] tempState;
}
void AES::TBoxSubstitution() {

	// 動態宣告四個暫存值記憶體 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		// 查表
		tempState[0] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][0]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][0]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][0]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][0]));
		tempState[1] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][1]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][1]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][1]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][1]));
		tempState[2] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][2]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][2]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][2]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][2]));
		tempState[3] = (unsigned char)((this->Te_0[(int)(this->state[i * 4])][3]) ^ (this->Te_1[(int)(this->state[i * 4 + 1])][3]) ^ (this->Te_2[(int)(this->state[i * 4 + 2])][3]) ^ (this->Te_3[(int)(this->state[i * 4 + 3])][3]));

		// 賦值 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// 釋放記憶體 
	delete[] tempState;
}

// AES解密函數
void AES::inverseSBoxSubstitution() {
	// 將state中的每個值進行InverseSBox的查表對應 
	for (int i = 0; i < 16; i++) {
		(this->state)[i] = (unsigned char)this->InverseSBox[(int)(this->state)[i]];
	}
}
void AES::inverseShiftRows() {
	unsigned char tempState; // 宣告一個暫存值

	//第一行不動
	//第二行向左循環一位
	tempState = (this->state)[13];
	(this->state)[13] = (this->state)[9];
	(this->state)[9] = (this->state)[5];
	(this->state)[5] = (this->state)[1];
	(this->state)[1] = tempState;

	//第三行向左循環兩位
	tempState = (this->state)[6];
	(this->state)[6] = (this->state)[14];
	(this->state)[14] = tempState;
	tempState = (this->state)[10];
	(this->state)[10] = (this->state)[2];
	(this->state)[2] = tempState;

	//第四行向左循環三位
	tempState = (this->state)[3];
	(this->state)[3] = (this->state)[7];
	(this->state)[7] = (this->state)[11];
	(this->state)[11] = (this->state)[15];
	(this->state)[15] = tempState;
}
void AES::inverseMixColumn() {
	// 動態宣告四個暫存值記憶體 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		//計算方法 
		/*
		tempState[0] = this->GMul(0x0e, (this->state)[i*4]) ^ this->GMul(0x0b, (this->state)[i*4+1]) ^ this->GMul(0x0d, (this->state)[i*4+2]) ^ this->GMul(0x09, (this->state)[i*4+3]);
		tempState[1] = this->GMul(0x09, (this->state)[i*4]) ^ this->GMul(0x0e, (this->state)[i*4+1]) ^ this->GMul(0x0b, (this->state)[i*4+2]) ^ this->GMul(0x0d, (this->state)[i*4+3]);
		tempState[2] = this->GMul(0x0d, (this->state)[i*4]) ^ this->GMul(0x09, (this->state)[i*4+1]) ^ this->GMul(0x0e, (this->state)[i*4+2]) ^ this->GMul(0x0b, (this->state)[i*4+3]);
		tempState[3] = this->GMul(0x0b, (this->state)[i*4]) ^ this->GMul(0x0d, (this->state)[i*4+1]) ^ this->GMul(0x09, (this->state)[i*4+2]) ^ this->GMul(0x0e, (this->state)[i*4+3]);
		*/

		// 查表方法
		tempState[0] = (this->GMul_0e)[(this->state)[i * 4]] ^ (this->GMul_0b)[(this->state)[i * 4 + 1]] ^ (this->GMul_0d)[(this->state)[i * 4 + 2]] ^ (this->GMul_09)[(this->state)[i * 4 + 3]];
		tempState[1] = (this->GMul_09)[(this->state)[i * 4]] ^ (this->GMul_0e)[(this->state)[i * 4 + 1]] ^ (this->GMul_0b)[(this->state)[i * 4 + 2]] ^ (this->GMul_0d)[(this->state)[i * 4 + 3]];
		tempState[2] = (this->GMul_0d)[(this->state)[i * 4]] ^ (this->GMul_09)[(this->state)[i * 4 + 1]] ^ (this->GMul_0e)[(this->state)[i * 4 + 2]] ^ (this->GMul_0b)[(this->state)[i * 4 + 3]];
		tempState[3] = (this->GMul_0b)[(this->state)[i * 4]] ^ (this->GMul_0d)[(this->state)[i * 4 + 1]] ^ (this->GMul_09)[(this->state)[i * 4 + 2]] ^ (this->GMul_0e)[(this->state)[i * 4 + 3]];

		// 賦值 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// 釋放記憶體 
	delete[] tempState;
}

void AES::inverseTBoxSubstitution() {

	// 動態宣告四個暫存值記憶體 
	unsigned char * tempState = new unsigned char[4];

	for (int i = 0; i < 4; i++) {
		// 查表
		tempState[0] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][0]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][0]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][0]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][0]));
		tempState[1] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][1]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][1]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][1]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][1]));
		tempState[2] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][2]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][2]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][2]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][2]));
		tempState[3] = (unsigned char)((this->Td_0[(int)(this->state[i * 4])][3]) ^ (this->Td_1[(int)(this->state[i * 4 + 1])][3]) ^ (this->Td_2[(int)(this->state[i * 4 + 2])][3]) ^ (this->Td_3[(int)(this->state[i * 4 + 3])][3]));

		// 賦值 
		(this->state)[i * 4] = tempState[0];
		(this->state)[i * 4 + 1] = tempState[1];
		(this->state)[i * 4 + 2] = tempState[2];
		(this->state)[i * 4 + 3] = tempState[3];
	}

	// 釋放記憶體 
	delete[] tempState;
}


// 填充 
void AES::padding() {

	// 暫存原本明文大小 
	int plaintextSize_byte = this->plaintextSize_byte;
	// 配置原本明文記憶體空間
	unsigned char * plaintext = new unsigned char[plaintextSize_byte];
	// 複製原本明文
	for (int i = 0; i < plaintextSize_byte; i++) {
		plaintext[i] = this->plaintext[i];
	}

	if (this->paddingMode == AES::ZeroPadding) {

		// 取得應該填充多少大小 
		int fillSize_byte = (plaintextSize_byte % 16 == 0) ? 16 : (16 - plaintextSize_byte % 16);

		// 取得填充後plaintext大小
		int newPlaintextSize_byte = plaintextSize_byte + fillSize_byte;

		// 將填充後的明文放入類變數中
		// 配置明文記憶體空間 
		if (this->plaintext == NULL) {
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->plaintext;
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		// 配置密文記憶體空間
		if (this->ciphertext == NULL) {
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->ciphertext;
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}

		// 先複製原有的部分
		for (int i = 0; i < plaintextSize_byte; i++) {
			(this->plaintext)[i] = plaintext[i];
		}
		// 處理填充部分 - 填充0 
		for (int i = plaintextSize_byte; i < newPlaintextSize_byte; i++) {
			(this->plaintext)[i] = 0;
		}

		// 儲存明文大小
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
		// 儲存密文大小 - 根據AES的特徵加密前後的大小相同
		this->ciphertextSize_byte = this->plaintextSize_byte;
		this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
		this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	}
	else if (this->paddingMode == AES::PKCS7Padding) {

		// 取得應該填充多少大小 
		int fillSize_byte = (plaintextSize_byte % 16 == 0) ? 16 : (16 - plaintextSize_byte % 16);

		// 取得填充後plaintext大小
		int newPlaintextSize_byte = plaintextSize_byte + fillSize_byte;

		// 取得要填充哪個字
		unsigned char filler = (unsigned char)fillSize_byte;

		// 將填充後的明文放入類變數中
		// 配置明文記憶體空間 
		if (this->plaintext == NULL) {
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->plaintext;
			this->plaintext = new unsigned char[newPlaintextSize_byte];
		}
		// 配置密文記憶體空間
		if (this->ciphertext == NULL) {
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}
		else {
			delete[] this->ciphertext;
			this->ciphertext = new unsigned char[newPlaintextSize_byte];
		}

		// 先複製原有的部分
		for (int i = 0; i < plaintextSize_byte; i++) {
			(this->plaintext)[i] = plaintext[i];
		}
		// 處理填充部分 - 填充filler
		for (int i = plaintextSize_byte; i < newPlaintextSize_byte; i++) {
			(this->plaintext)[i] = filler;
		}

		// 儲存明文大小
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
		// 儲存密文大小 - 根據AES的特徵加密前後的大小相同
		this->ciphertextSize_byte = this->plaintextSize_byte;
		this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
		this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	}
	// NoPadding 不用處理 

	// 釋放原本明文記憶體空間 
	delete[] plaintext;
}
// 解填充 
void AES::unpadding() {

	// 配置原本明文記憶體空間
	unsigned char * plaintext = new unsigned char[plaintextSize_byte];
	// 複製原本明文
	for (int i = 0; i < plaintextSize_byte; i++) {
		plaintext[i] = this->plaintext[i];
	}


	if (this->paddingMode == AES::ZeroPadding) {

		// 暫存原本明文大小 
		int newPlaintextSize_byte = this->plaintextSize_byte;

		// 運算從前面保留多少字元 
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

		// 重新配置明文記憶體
		delete[] this->plaintext;
		this->plaintext = new unsigned char[newPlaintextSize_byte];

		// 複製內容
		for (int i = 0; i < newPlaintextSize_byte; i++) {
			this->plaintext[i] = plaintext[i];
		}

		// 更新明文大小紀錄
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;

	}
	else if (this->paddingMode == AES::PKCS7Padding) {
		int newPlaintextSize_byte = this->plaintextSize_byte - (int)this->plaintext[this->plaintextSize_byte - 1];

		// 重新配置明文記憶體
		delete[] this->plaintext;
		this->plaintext = new unsigned char[newPlaintextSize_byte];

		// 複製內容
		for (int i = 0; i < newPlaintextSize_byte; i++) {
			this->plaintext[i] = plaintext[i];
		}

		// 更新明文大小紀錄
		this->plaintextSize_byte = newPlaintextSize_byte;
		this->plaintextSize_bit = this->plaintextSize_byte * 8;
		this->plaintextSize_word = this->plaintextSize_byte / 4;
	}
	// NoPadding不用處理 

	// 釋放原本明文記憶體空間 
	delete[] plaintext;


}

// 加密器 - 將128bit的明文放置state後呼叫，加密完成後結果於state 
void AES::encryptor() {

	// 第一輪Add Round Key
	this->addRoundKey(0);

	// 循環完成剩下輪
	for (int i = 1; i <= this->round; i++) {
		// SBox替換 
		this->SBoxSubstitution();
		// 列移位 
		this->shiftRows();
		// 行混合(最後一次不做)
		if (i != this->round) {
			this->mixColumn();
		}
		// 輪密鑰加
		this->addRoundKey(i);
	}


}

void AES::quickEncryptor() {

	// 第一輪Add Round Key
	this->addRoundKey(0);

	// 循環完成剩下輪
	for (int i = 1; i <= this->round; i++) {
		// 列移位 
		this->shiftRows();

		// T盒查詢(最後一次只做S盒替換) 
		if (i == this->round) {
			this->SBoxSubstitution();
		}
		else {
			this->TBoxSubstitution();
		}

		// 輪密鑰加
		this->addRoundKey(i);
	}


}

void AES::ECBEncrypt() {
	// 循環分塊將明文加密 
	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// 放置128bit塊明文至state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->plaintext)[i + j];
			(this->state)[j + 1] = (this->plaintext)[i + j + 1];
			(this->state)[j + 2] = (this->plaintext)[i + j + 2];
			(this->state)[j + 3] = (this->plaintext)[i + j + 3];
		}

		// 呼叫加密器加密該塊
		this->quickEncryptor();

		// 從state取出加密後的結果
		for (int j = 0; j < 16; j++) {
			(this->ciphertext)[i + j] = (this->state)[j];
		}
	}
}
void AES::CBCEncrypt() {

	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// 明文前置處理 
		if (i == 0) {
			// 第一次明文和iv做XOR
			for (int j = 0; j < 16; j += 4) {
				(this->state)[j] = (this->plaintext)[j] ^ (this->iv)[j];
				(this->state)[j + 1] = (this->plaintext)[j + 1] ^ (this->iv)[j + 1];
				(this->state)[j + 2] = (this->plaintext)[j + 2] ^ (this->iv)[j + 2];
				(this->state)[j + 3] = (this->plaintext)[j + 3] ^ (this->iv)[j + 3];
			}
		}
		else {
			// 之後每一次明文和上一次產生的密文進行XOR
			for (int j = 0; j < 16; j += 4) {
				(this->state)[j] = (this->plaintext)[i + j] ^ (this->ciphertext)[i - 16 + j];
				(this->state)[j + 1] = (this->plaintext)[i + j + 1] ^ (this->ciphertext)[i - 16 + j + 1];
				(this->state)[j + 2] = (this->plaintext)[i + j + 2] ^ (this->ciphertext)[i - 16 + j + 2];
				(this->state)[j + 3] = (this->plaintext)[i + j + 3] ^ (this->ciphertext)[i - 16 + j + 3];
			}
		}

		// 加密 
		this->quickEncryptor();

		// 從state複製出結果至ciphertext
		for (int j = 0; j < 16; j++) {
			(this->ciphertext)[i + j] = (this->state)[j];
		}

	}
}
void AES::OFB8Encrypt() {
	// 建立一個暫存iv值及暫存加密iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i++) {

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 將結果從state複製出來
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// 取得密文一位 - 明文8個bit(1個byte)與加密IV的最高8個bit(1個byte)進行XOR
		(this->ciphertext)[i] = (this->plaintext)[i] ^ encryptedIv[0];

		// 暫存iv向左移8個bit(1個byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// 暫存iv的最後8個bit(1個byte)由剛剛取得的8個bit(1個byte)加密IV補上
		tempIv[15] = encryptedIv[0];
	}

	// 歸還暫存IV及暫存加密iv值的記憶體 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CFB8Encrypt() {

	// 建立一個暫存iv值及暫存加密iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i++) {

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 將結果從state複製出來
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// 取得密文一位 - 明文8個bit(1個byte)與加密IV的最高8個bit(1個byte)進行XOR
		(this->ciphertext)[i] = (this->plaintext)[i] ^ encryptedIv[0];

		// 暫存iv向左移8個bit(1個byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// 暫存iv的最後8個bit(1個byte)由剛剛取得的8個bit(1個byte)密文補上
		tempIv[15] = (this->ciphertext)[i];
	}

	// 歸還暫存IV及暫存加密iv值的記憶體 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CTREncrypt() {
	// 建立一個暫存iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->plaintextSize_byte; i += 16) {

		// 計數器向上加
		tempIv[15] += i / 16;

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 明文與加密iv左對齊做XOR
		for (int j = 0; j < 16; j++) {
			if (i + j == this->plaintextSize_byte) {
				break;
			}

			(this->ciphertext)[i + j] = (this->state)[j] ^ (this->plaintext)[i + j];
		}
	}

	// 歸還暫存IV的記憶體 
	delete[] tempIv;
}


// 解密器 - 將128bit明文放置於state後呼叫，解密完成後結果於state 
void AES::decryptor() {
	for (int i = this->round; i >= 1; i--) {
		//輪密鑰加
		this->addRoundKey(i);
		// 逆行混合(第一次不做)
		if (i != this->round) {
			this->inverseMixColumn();
		}
		// 逆行移位
		this->inverseShiftRows();
		// 逆SBox替換
		this->inverseSBoxSubstitution();
	}

	this->addRoundKey(0);
}

void AES::quickDecryptor() {


	this->addRoundKey(this->round);

	for (int i = this->round - 1; i >= 0; i--) {
		// 逆行移位
		this->inverseShiftRows();

		// 逆T盒代換(最後一次只做逆S盒代換) 
		if (i == 0) {
			this->inverseSBoxSubstitution();
		}
		else {
			this->inverseTBoxSubstitution();
		}

		// 最後一輪的key不用做inverse mix column 
		if (i == 0) {
			this->addRoundKey(i);
		}
		else {
			this->addInverseMixColumnRoundKey(i);
		}


	}


}

void AES::ECBDecrypt() {
	// 循環分塊將密文解密 
	for (int i = 0; i < this->ciphertextSize_byte; i += 16) {

		// 放置128bit塊密文至state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->ciphertext)[i + j];
			(this->state)[j + 1] = (this->ciphertext)[i + j + 1];
			(this->state)[j + 2] = (this->ciphertext)[i + j + 2];
			(this->state)[j + 3] = (this->ciphertext)[i + j + 3];
		}

		// 呼叫加密器加密該塊
		this->quickDecryptor();

		// 從state取出加密後的結果
		for (int j = 0; j < 16; j++) {
			(this->plaintext)[i + j] = (this->state)[j];
		}
	}
}
void AES::CBCDecrypt() {
	// 從最後一塊開始解密
	for (int i = this->ciphertextSize_byte - 16; i >= 0; i -= 16) {

		// 先做該塊密文解密 
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = (this->ciphertext)[i + j];
			(this->state)[j + 1] = (this->ciphertext)[i + j + 1];
			(this->state)[j + 2] = (this->ciphertext)[i + j + 2];
			(this->state)[j + 3] = (this->ciphertext)[i + j + 3];
		}

		// 呼叫解密器解密該塊
		this->quickDecryptor();

		if (i == 0) {
			// 最後一塊要跟IV做XOR取得明文 
			for (int j = 0; j < 16; j += 4) {
				(this->plaintext)[j] = (this->state)[j] ^ (this->iv)[j];
				(this->plaintext)[j + 1] = (this->state)[j + 1] ^ (this->iv)[j + 1];
				(this->plaintext)[j + 2] = (this->state)[j + 2] ^ (this->iv)[j + 2];
				(this->plaintext)[j + 3] = (this->state)[j + 3] ^ (this->iv)[j + 3];
			}
		}
		else {
			// 其他與下一階段要處理的密文做XOR 
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
	// OFB模式加密與解密相同

	// 建立一個暫存iv值及暫存加密iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i++) {

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 將結果從state複製出來
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// 取得密文一位 - 明文8個bit(1個byte)與加密IV的最高8個bit(1個byte)進行XOR
		(this->plaintext)[i] = (this->ciphertext)[i] ^ encryptedIv[0];

		// 暫存iv向左移8個bit(1個byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// 暫存iv的最後8個bit(1個byte)由剛剛取得的8個bit(1個byte)加密IV補上
		tempIv[15] = encryptedIv[0];
	}

	// 歸還暫存IV及暫存加密iv值的記憶體 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CFB8Decrypt() {

	// CFB模式加密與解密相同 

	// 建立一個暫存iv值及暫存加密iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];
	unsigned char * encryptedIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i++) {

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 將結果從state複製出來
		for (int j = 0; j < 16; j++) {
			encryptedIv[j] = (this->state)[j];
		}

		// 取得密文一位 - 明文8個bit(1個byte)與加密IV的最高8個bit(1個byte)進行XOR
		(this->plaintext)[i] = (this->ciphertext)[i] ^ encryptedIv[0];

		// 暫存iv向左移8個bit(1個byte)
		for (int j = 0; j < 15; j++) {
			tempIv[j] = tempIv[j + 1];
		}

		// 暫存iv的最後8個bit(1個byte)由剛剛取得的8個bit(1個byte)密文補上
		tempIv[15] = (this->ciphertext)[i];
	}

	// 歸還暫存IV及暫存加密iv值的記憶體 
	delete[] tempIv;
	delete[] encryptedIv;
}
void AES::CTRDecrypt() {
	// 建立一個暫存iv值並配置記憶體空間
	unsigned char * tempIv = new unsigned char[16];

	// 將原本iv複製進暫存iv
	for (int i = 0; i < 16; i++) {
		tempIv[i] = (this->iv)[i];
	}

	for (int i = 0; i < this->ciphertextSize_byte; i += 16) {

		// 計數器向上加
		tempIv[15] += i / 16;

		// 加密iv
		// 複製暫存iv進state
		for (int j = 0; j < 16; j++) {
			(this->state)[j] = tempIv[j];
			(this->state)[j + 1] = tempIv[j + 1];
			(this->state)[j + 2] = tempIv[j + 2];
			(this->state)[j + 3] = tempIv[j + 3];
		}
		// 執行加密器
		this->quickEncryptor();

		// 明文與加密iv左對齊做XOR
		for (int j = 0; j < 16; j++) {
			if (i + j == this->ciphertextSize_byte) {
				break;
			}

			(this->plaintext)[i + j] = (this->state)[j] ^ (this->ciphertext)[i + j];
		}
	}

	// 歸還暫存IV的記憶體 
	delete[] tempIv;
}



// 加密 (提供外部呼叫) 
void AES::encrypt(const char * plaintext, const int plaintextSize_byte, unsigned char ** result, int * resultSize_byte) {


	// 配置明文記憶體
	if (this->plaintext == NULL) {
		this->plaintext = new unsigned char[plaintextSize_byte];
	}
	else {
		delete[] this->plaintext;
		this->plaintext = new unsigned char[plaintextSize_byte];
	}

	// 配置密文記憶體
	if (this->ciphertext == NULL) {
		this->ciphertext = new unsigned char[plaintextSize_byte];
	}
	else {
		delete[] this->ciphertext;
		this->ciphertext = new unsigned char[plaintextSize_byte];
	}

	// 儲存明文大小
	this->plaintextSize_byte = plaintextSize_byte;
	this->plaintextSize_bit = this->plaintextSize_byte * 8;
	this->plaintextSize_word = this->plaintextSize_byte / 4;

	// 儲存密文大小
	this->ciphertextSize_byte = plaintextSize_byte;
	this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
	this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	// 複製明文進入類變數 
	for (int i = 0; i < plaintextSize_byte; i++) {
		this->plaintext[i] = plaintext[i];
	}

	// 配置state空間
	this->state = new unsigned char[16];


	// 呼叫padding
	this->padding();

	// 確定明文大小是否符合該模式要求 - ECB及CBC模式要求填充後的明文大小為128bit的倍數
	// 若不符合則拋出明文長度錯誤異常 
	if ((this->mode == AES::ECB || this->mode == AES::CBC) && this->plaintextSize_bit % 128 != 0) {
		throw new AESException(AESException::INVALID_PLAINTEXT_LENGHT);
	}

	// 根據要求模式進行加密
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

	// 放置結果
	// 放置結果大小
	*resultSize_byte = this->ciphertextSize_byte;
	// 配置結果記憶體 
	*result = new unsigned char[*resultSize_byte];
	// 放置結果
	for (int i = 0; i < *resultSize_byte; i++) {
		*(*result + i) = this->ciphertext[i];
	}


	// 歸還state空間
	delete[] this->state;
	this->state = NULL;

	// 歸還明文空間
	delete[] this->plaintext;
	this->plaintext = NULL;

	// 歸還密文空間
	delete[] this->ciphertext;
	this->ciphertext = NULL;

	// 清除明文空間大小紀錄
	this->plaintextSize_bit = -1;
	this->plaintextSize_byte = -1;
	this->plaintextSize_word = -1;

	// 清除密文空間大小紀錄
	this->ciphertextSize_bit = -1;
	this->ciphertextSize_byte = -1;
	this->ciphertextSize_word = -1;

}

// 解密 (提供外部呼叫) 
void AES::decrypt(const unsigned char * ciphertext, const int ciphertextSize_byte, char ** result, int * resultSize_byte) {

	// 配置明文記憶體
	if (this->plaintext == NULL) {
		this->plaintext = new unsigned char[ciphertextSize_byte];
	}
	else {
		delete[] this->plaintext;
		this->plaintext = new unsigned char[ciphertextSize_byte];
	}

	// 配置密文記憶體
	if (this->ciphertext == NULL) {
		this->ciphertext = new unsigned char[ciphertextSize_byte];
	}
	else {
		delete[] this->ciphertext;
		this->ciphertext = new unsigned char[ciphertextSize_byte];
	}

	// 儲存明文大小
	this->plaintextSize_byte = ciphertextSize_byte;
	this->plaintextSize_bit = this->plaintextSize_byte * 8;
	this->plaintextSize_word = this->plaintextSize_byte / 4;

	// 儲存密文大小
	this->ciphertextSize_byte = ciphertextSize_byte;
	this->ciphertextSize_bit = this->ciphertextSize_byte * 8;
	this->ciphertextSize_word = this->ciphertextSize_byte / 4;

	// 複製密文進去
	for (int i = 0; i < ciphertextSize_byte; i++) {
		this->ciphertext[i] = ciphertext[i];
	}

	// 配置state空間
	this->state = new unsigned char[16];

	// 確定密文大小是否符合該模式要求 - ECB及CBC模式要求密文大小為128bit的倍數
	// 若不符合則拋出密文長度錯誤異常 
	if ((this->mode == AES::ECB || this->mode == AES::CBC) && this->ciphertextSize_bit % 128 != 0) {
		throw new AESException(AESException::INVALID_CIPHERTEXT_LENGTH);
	}

	// 根據要求模式進行解密 
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

	// 解填充
	this->unpadding();

	// 放置結果
	// 放置結果大小
	*resultSize_byte = this->plaintextSize_byte;
	// 配置結果記憶體 
	*result = new char[*resultSize_byte+1];
	// 放置結果
	for (int i = 0; i < *resultSize_byte; i++) {
		*(*result + i) = this->plaintext[i];
	}
	*(*result + *resultSize_byte) = '\0';

	// 歸還state空間
	delete[] this->state;
	this->state = NULL;

	// 歸還明文空間
	delete[] this->plaintext;
	this->plaintext = NULL;

	// 歸還密文空間
	delete[] this->ciphertext;
	this->ciphertext = NULL;

	// 清除明文空間大小紀錄
	this->plaintextSize_bit = -1;
	this->plaintextSize_byte = -1;
	this->plaintextSize_word = -1;

	// 清除密文空間大小紀錄
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


