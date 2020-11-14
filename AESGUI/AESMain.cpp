#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QFileDialog>


#include <string.h>
#include <stdio.h>
#include <iostream>


#include "AESMain.h"
#include "AlertDialog.h"
#include "AES.h"
#include "AESException.h"


using namespace std;


AESMain::AESMain(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->init();
	this->loading();
}

void AESMain::init() {
	this->initView();
	this->initInteraction();
}

void AESMain::initView() {
	this->setWindowFlags(Qt::CustomizeWindowHint);
	this->setWindowTitle(QString::fromLocal8Bit("AES加解密器"));
	this->setWindowIcon(QIcon(":/AESMain/images/svg/icon.svg"));
}

void AESMain::initInteraction() {
	connect(ui.close, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
	connect(ui.maximize, SIGNAL(clicked()), this, SLOT(onMaximizeClicked()));
	connect(ui.minimize, SIGNAL(clicked()), this, SLOT(onMinimizeClicked()));
	connect(ui.left, SIGNAL(clicked()), this, SLOT(onLeftClicked()));
	connect(ui.right, SIGNAL(clicked()), this, SLOT(onRightClicked()));
	connect(ui.strEncrypt, SIGNAL(clicked()), this, SLOT(onStrEncryptClicked()));
	connect(ui.strDecrypt, SIGNAL(clicked()), this, SLOT(onStrDecryptClicked()));
	connect(ui.fileEncrypt, SIGNAL(clicked()), this, SLOT(onFileEncryptClicked()));
	connect(ui.fileDecrypt, SIGNAL(clicked()), this, SLOT(onFileDecryptClicked()));
	connect(ui.pickFile, SIGNAL(clicked()), this, SLOT(onPickFileClicked()));
	connect(ui.pickPlace, SIGNAL(clicked()), this, SLOT(onPickPlaceClicked()));
}


void AESMain::loading() {
	this->loadingData();
}

void AESMain::loadingData() {
	ui.AESBits->addItem(QString("AES 128"));
	ui.AESBits->addItem(QString("AES 192"));
	ui.AESBits->addItem(QString("AES 256"));

	ui.AESMode->addItem(QString("ECB"));
	ui.AESMode->addItem(QString("CBC"));
	ui.AESMode->addItem(QString("OFB8"));
	ui.AESMode->addItem(QString("CFB8"));
	ui.AESMode->addItem(QString("CTR"));

	ui.AESPaddingMode->addItem(QString("No Padding"));
	ui.AESPaddingMode->addItem(QString("Zero Padding"));
	ui.AESPaddingMode->addItem(QString("PKCS#7 Padding"));


	ui.fileAESBits->addItem(QString("AES 128"));
	ui.fileAESBits->addItem(QString("AES 192"));
	ui.fileAESBits->addItem(QString("AES 256"));

	ui.fileAESMode->addItem(QString("ECB"));
	ui.fileAESMode->addItem(QString("CBC"));
	ui.fileAESMode->addItem(QString("OFB8"));
	ui.fileAESMode->addItem(QString("CFB8"));
	ui.fileAESMode->addItem(QString("CTR"));

	ui.fileAESPaddingMode->addItem(QString("No Padding"));
	ui.fileAESPaddingMode->addItem(QString("Zero Padding"));
	ui.fileAESPaddingMode->addItem(QString("PKCS#7 Padding"));
}








void AESMain::onCloseClicked() {
	this->close();
}

void AESMain::onMaximizeClicked() {
	if (this->isMaximized()) {
		this->showNormal();
	}
	else {
		this->showMaximized();
	}
}

void AESMain::onMinimizeClicked() {
	this->showMinimized();
}

void AESMain::onLeftClicked() {
	int index = ui.stackedWidget->currentIndex() - 1;

	if (index < 0 ) {
		index = 0;
	}


	ui.stackedWidget->setCurrentIndex(index);
}

void AESMain::onRightClicked() {
	int index = ui.stackedWidget->currentIndex() + 1;

	if (index > ui.stackedWidget->count() - 1) {
		index -= ui.stackedWidget->count()-1;
	}
	

	ui.stackedWidget->setCurrentIndex(index);
}


void AESMain::onPickFileClicked() {
	QString filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("選擇加解密檔案"), QString("/"));

	if (filePath != NULL) {
		ui.file->setText(filePath);
	}
}

void AESMain::onPickPlaceClicked(){
	QString placePath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("選擇保存路徑"), QString("/"));

	if (placePath != NULL) {
		ui.place->setText(placePath);
	}
}

void AESMain::onStrEncryptClicked() {

	// 取得文字資訊
	string plaintext = ui.plaintext->toPlainText().toStdString();
	string key1 = ui.AESKey1->text().toStdString();
	string key2 = ui.AESKey2->text().toStdString();
	string key3 = ui.AESKey3->text().toStdString();
	string iv = ui.AESIv->text().toStdString();

	char * c_plaintext = plaintext.size()!=0 ? new char[plaintext.size()+1] : new char[1];
	char * c_key1 = key1.size() != 0 ? new char[key1.size()+1] : new char[1];
	char * c_key2 = key2.size() != 0 ? new char[key2.size()+1] : new char[1];
	char * c_key3 = key3.size() != 0 ? new char[key3.size()+1] : new char[1];
	char * c_iv = iv.size() !=0 ? new char[iv.size()+1] : new char[1];

	if (plaintext.size() != 0) {
		strcpy(c_plaintext, plaintext.c_str());
	}
	else {
		c_plaintext[0] = '\0';
	}
	if (key1.size() != 0) {
		strcpy(c_key1, key1.c_str());
	}
	else {
		c_key1[0] = '\0';
	}
	if (key2.size() != 0) {
		strcpy(c_key2, key2.c_str());
	}
	else {
		c_key2[0] = '\0';
	}
	if (key3.size() != 0) {
		strcpy(c_key3, key3.c_str());
	}
	else {
		c_key3[0] = '\0';
	}
	if (iv.size() != 0) {
		strcpy(c_iv, iv.c_str());
	}
	else {
		c_iv[0] = '\0';
	}

	// 分配mode、paddingMode及aes位元
	int mode = this->mode2ClassMode(ui.AESMode->currentIndex());
	int paddingMode = this->paddingMode2ClassPaddingMode(ui.AESPaddingMode->currentIndex());
	int aes = this->aes2ClassAes(ui.AESBits->currentIndex());
	
	// 結果區
	unsigned char * encrypted = NULL;
	int encryptedSize = -1;

	// EDE模式
	if (key2.size() != 0 || key3.size() != 0) {
		unsigned char * stage1 = NULL;
		int stageSize1 = -1;

		char * stage2 = NULL;
		int stageSize2 = -1;


		try {
			AES * AESHelper1 = new AES(aes, mode, paddingMode);
			AES * AESHelper2 = new AES(aes, mode, paddingMode);
			AES * AESHelper3 = new AES(aes, mode, paddingMode);

			AESHelper1->init(c_key1, c_iv);
			AESHelper2->init(c_key2, c_iv);
			AESHelper3->init(c_key3, c_iv);

			AESHelper1->encrypt(c_plaintext, strlen(c_plaintext), &stage1, &stageSize1);
			AESHelper2->decrypt(stage1, stageSize1, &stage2, &stageSize2);
			AESHelper3->encrypt(stage2, stageSize2, &encrypted, &encryptedSize);

			delete AESHelper1, AESHelper2, AESHelper3;

		}
		catch (AESException * e) {
			if (e->getType() == AESException::INVILID_KEY_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現金鑰長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVILID_IV_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現初始向量長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現明文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現密文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
		}

		delete[] stage1, stage2;

	}
	// 普通模式
	else {
		try {
			AES * AESHelper = new AES(aes, mode, paddingMode);
			AESHelper->init(c_key1, c_iv);
			AESHelper->encrypt(c_plaintext, strlen(c_plaintext), &encrypted, &encryptedSize);
			delete AESHelper;
		}
		catch (AESException * e) {
			if (e->getType() == AESException::INVILID_KEY_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現金鑰長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVILID_IV_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現初始向量長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現明文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現密文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
		}


		
	}
	

	
	
	if (encrypted != NULL && encryptedSize != -1) {
		char * encryptedHex = new char[encryptedSize * 2 + 1];
		this->byte2HexChars(encrypted, encryptedSize, encryptedHex);
		ui.ciphertext->setText(QString::fromUtf8(encryptedHex));
		delete[] encryptedHex;
	}

	delete[] c_plaintext, c_key1, c_key2, c_key3, c_iv, encrypted;
}

void AESMain::onStrDecryptClicked() {
	// 取得文字資訊
	string ciphertext = ui.ciphertext->toPlainText().toStdString();
	string key1 = ui.AESKey1->text().toStdString();
	string key2 = ui.AESKey2->text().toStdString();
	string key3 = ui.AESKey3->text().toStdString();
	string iv = ui.AESIv->text().toStdString();

	char * c_ciphertext = ciphertext.size() != 0 ? new char[ciphertext.size() + 1] : new char[1];
	char * c_key1 = key1.size() != 0 ? new char[key1.size() + 1] : new char[1];
	char * c_key2 = key2.size() != 0 ? new char[key2.size() + 1] : new char[1];
	char * c_key3 = key3.size() != 0 ? new char[key3.size() + 1] : new char[1];
	char * c_iv = iv.size() != 0 ? new char[iv.size() + 1] : new char[1];

	if (ciphertext.size() != 0) {
		strcpy(c_ciphertext, ciphertext.c_str());
	}
	else {
		c_ciphertext[0] = '\0';
	}
	if (key1.size() != 0) {
		strcpy(c_key1, key1.c_str());
	}
	else {
		c_key1[0] = '\0';
	}
	if (key2.size() != 0) {
		strcpy(c_key2, key2.c_str());
	}
	else {
		c_key2[0] = '\0';
	}
	if (key3.size() != 0) {
		strcpy(c_key3, key3.c_str());
	}
	else {
		c_key3[0] = '\0';
	}
	if (iv.size() != 0) {
		strcpy(c_iv, iv.c_str());
	}
	else {
		c_iv[0] = '\0';
	}


	// 分配mode、paddingMode及aes位元
	int mode = this->mode2ClassMode(ui.AESMode->currentIndex());
	int paddingMode = this->paddingMode2ClassPaddingMode(ui.AESPaddingMode->currentIndex());
	int aes = this->aes2ClassAes(ui.AESBits->currentIndex());

	// 輸入字符串轉byte
	unsigned char * encrypted = new unsigned char[ciphertext.size() / 2];
	this->hexChars2Byte(c_ciphertext, ciphertext.size(), encrypted);
	

	// 結果區
	char * decrypted = NULL;
	int decryptedSize = -1;


	if (strlen(c_key2) != 0 || strlen(c_key3) != 0) {
		char * stage1 = NULL;
		int stageSize1 = -1;

		unsigned char * stage2 = NULL;
		int stageSize2 = -1;


		try {
			AES * AESHelper1 = new AES(aes, mode, paddingMode);
			AES * AESHelper2 = new AES(aes, mode, paddingMode);
			AES * AESHelper3 = new AES(aes, mode, paddingMode);

			AESHelper1->init(c_key1, c_iv);
			AESHelper2->init(c_key2, c_iv);
			AESHelper3->init(c_key3, c_iv);

			AESHelper3->decrypt(encrypted, ciphertext.size() / 2, &stage1, &stageSize1);
			AESHelper2->encrypt(stage1, stageSize1, &stage2, &stageSize2);
			AESHelper3->decrypt(stage2, stageSize2, &decrypted, &decryptedSize);

			delete AESHelper1, AESHelper2, AESHelper3;


		}
		catch (AESException * e) {
			if (e->getType() == AESException::INVILID_KEY_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現金鑰長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVILID_IV_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現初始向量長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現明文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現密文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
		}

		delete[] stage1, stage2;


	}
	else {
		try {
			AES * AESHelper = new AES(aes, mode, paddingMode);
			AESHelper->init(c_key1, c_iv);
			AESHelper->decrypt(encrypted, ciphertext.size() / 2, &decrypted, &decryptedSize);
			delete AESHelper;
		}
		catch (AESException * e) {
			if (e->getType() == AESException::INVILID_KEY_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現金鑰長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVILID_IV_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現初始向量長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現明文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
			else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
				AlertDialog * alertDialog = new AlertDialog();
				alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
				alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現密文長度異常，請檢查後重試"));
				alertDialog->exec();
			}
		}
	}


	if (decrypted != NULL && decryptedSize != -1) {
		ui.plaintext->setText(QString::fromUtf8(decrypted));
	}

	delete[] c_ciphertext, c_key1, c_key2, c_key3, c_iv, encrypted, decrypted;
}

void AESMain::onFileEncryptClicked() {
	// 取得文字資訊
	string key1 = ui.fileAESKey1->text().toStdString();
	string key2 = ui.fileAESKey2->text().toStdString();
	string key3 = ui.fileAESKey3->text().toStdString();
	string iv = ui.fileAESIv->text().toStdString();

	char * c_key1 = key1.size() != 0 ? new char[key1.size() + 1] : new char[1];
	char * c_key2 = key2.size() != 0 ? new char[key2.size() + 1] : new char[1];
	char * c_key3 = key3.size() != 0 ? new char[key3.size() + 1] : new char[1];
	char * c_iv = iv.size() != 0 ? new char[iv.size() + 1] : new char[1];

	if (key1.size() != 0) {
		strcpy(c_key1, key1.c_str());
	}
	else {
		c_key1[0] = '\0';
	}
	if (key2.size() != 0) {
		strcpy(c_key2, key2.c_str());
	}
	else {
		c_key2[0] = '\0';
	}
	if (key3.size() != 0) {
		strcpy(c_key3, key3.c_str());
	}
	else {
		c_key3[0] = '\0';
	}
	if (iv.size() != 0) {
		strcpy(c_iv, iv.c_str());
	}
	else {
		c_iv[0] = '\0';
	}

	// 分配mode、paddingMode及aes位元
	int mode = this->mode2ClassMode(ui.fileAESMode->currentIndex());
	int paddingMode = this->paddingMode2ClassPaddingMode(ui.fileAESPaddingMode->currentIndex());
	int aes = this->aes2ClassAes(ui.fileAESBits->currentIndex());



	// 開始獲取檔案
	string inputFilePath = ui.file->text().toLocal8Bit().data();
	char * c_inputFilePath = new char[inputFilePath.size() + 1];
	strcpy(c_inputFilePath, inputFilePath.c_str());

	string outputFilePath = ui.place->text().toLocal8Bit().data();
	char * c_outputFilePath = new char[outputFilePath.size() + 1];
	strcpy(c_outputFilePath, outputFilePath.c_str());

	FILE *inputFile = fopen(c_inputFilePath, "rb");
	FILE *outputFile = fopen(c_outputFilePath, "wb");
	

	if (inputFile && outputFile) {
		// 取得檔案大小
		fseek(inputFile, 0, SEEK_END);
		int inputFileSize = ftell(inputFile);
		fseek(inputFile, 0, SEEK_SET);

		// 取得檔案內容
		char * inputFileContent = new char[inputFileSize];
		fread(inputFileContent, 1, inputFileSize, inputFile);

		// 加密
		unsigned char * encrypted = NULL;
		int encryptedSize = -1;

		// EDE模式
		if (key2.size() != 0 || key3.size() != 0) {
			unsigned char * stage1 = NULL;
			int stageSize1 = -1;

			char * stage2 = NULL;
			int stageSize2 = -1;


			try {
				AES * AESHelper1 = new AES(aes, mode, paddingMode);
				AES * AESHelper2 = new AES(aes, mode, paddingMode);
				AES * AESHelper3 = new AES(aes, mode, paddingMode);

				AESHelper1->init(c_key1, c_iv);
				AESHelper2->init(c_key2, c_iv);
				AESHelper3->init(c_key3, c_iv);

				AESHelper1->encrypt(inputFileContent, inputFileSize, &stage1, &stageSize1);
				AESHelper2->decrypt(stage1, stageSize1, &stage2, &stageSize2);
				AESHelper3->encrypt(stage2, stageSize2, &encrypted, &encryptedSize);

				delete AESHelper1, AESHelper2, AESHelper3;

			}
			catch (AESException * e) {
				if (e->getType() == AESException::INVILID_KEY_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現金鑰長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVILID_IV_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現初始向量長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現明文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現密文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
			}

			delete[] stage1, stage2;

		}
		// 普通模式
		else {
			try {
				AES * AESHelper = new AES(aes, mode, paddingMode);
				AESHelper->init(c_key1, c_iv);
				AESHelper->encrypt(inputFileContent, inputFileSize, &encrypted, &encryptedSize);
				delete AESHelper;
			}
			catch (AESException * e) {
				if (e->getType() == AESException::INVILID_KEY_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現金鑰長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVILID_IV_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現初始向量長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現明文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現密文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
			}
		}
		


		
		if (encrypted != NULL && encryptedSize != -1) {
			fwrite(encrypted, 1, encryptedSize, outputFile);
		}
		



		fclose(inputFile);
		fclose(outputFile);
		delete[] inputFileContent, encrypted;

	} else {
		AlertDialog *alertDialog = new AlertDialog();
		alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
		alertDialog->setMessage(QString::fromLocal8Bit("無法開啟檔案，請確認加解密檔案路徑是否正確"));
		alertDialog->exec();
	}
	

	delete[] c_key1, c_key2, c_key3, c_iv, c_inputFilePath, c_outputFilePath;
}

void AESMain::onFileDecryptClicked() {
	// 取得文字資訊
	string key1 = ui.fileAESKey1->text().toStdString();
	string key2 = ui.fileAESKey2->text().toStdString();
	string key3 = ui.fileAESKey3->text().toStdString();
	string iv = ui.fileAESIv->text().toStdString();

	char * c_key1 = key1.size() != 0 ? new char[key1.size() + 1] : new char[1];
	char * c_key2 = key2.size() != 0 ? new char[key2.size() + 1] : new char[1];
	char * c_key3 = key3.size() != 0 ? new char[key3.size() + 1] : new char[1];
	char * c_iv = iv.size() != 0 ? new char[iv.size() + 1] : new char[1];

	if (key1.size() != 0) {
		strcpy(c_key1, key1.c_str());
	}
	else {
		c_key1[0] = '\0';
	}
	if (key2.size() != 0) {
		strcpy(c_key2, key2.c_str());
	}
	else {
		c_key2[0] = '\0';
	}
	if (key3.size() != 0) {
		strcpy(c_key3, key3.c_str());
	}
	else {
		c_key3[0] = '\0';
	}
	if (iv.size() != 0) {
		strcpy(c_iv, iv.c_str());
	}
	else {
		c_iv[0] = '\0';
	}

	// 分配mode、paddingMode及aes位元
	int mode = this->mode2ClassMode(ui.fileAESMode->currentIndex());
	int paddingMode = this->paddingMode2ClassPaddingMode(ui.fileAESPaddingMode->currentIndex());
	int aes = this->aes2ClassAes(ui.fileAESBits->currentIndex());

	// 開始獲取檔案
	string inputFilePath = ui.file->text().toLocal8Bit().data();
	char * c_inputFilePath = new char[inputFilePath.size() + 1];
	strcpy(c_inputFilePath, inputFilePath.c_str());

	string outputFilePath = ui.place->text().toLocal8Bit().data();
	char * c_outputFilePath = new char[outputFilePath.size() + 1];
	strcpy(c_outputFilePath, outputFilePath.c_str());

	FILE *inputFile = fopen(c_inputFilePath, "rb");
	FILE *outputFile = fopen(c_outputFilePath, "wb");

	if (inputFile && outputFile) {
		// 取得檔案大小
		fseek(inputFile, 0, SEEK_END);
		int inputFileSize = ftell(inputFile);
		fseek(inputFile, 0, SEEK_SET);

		// 取得檔案內容
		char * inputFileContent = new char[inputFileSize];
		fread(inputFileContent, 1, inputFileSize, inputFile);

		// 解密
		char * decrypted = NULL;
		int decryptedSize = -1;
		if (strlen(c_key2) != 0 || strlen(c_key3) != 0) {
			char * stage1 = NULL;
			int stageSize1 = -1;

			unsigned char * stage2 = NULL;
			int stageSize2 = -1;


			try {
				AES * AESHelper1 = new AES(aes, mode, paddingMode);
				AES * AESHelper2 = new AES(aes, mode, paddingMode);
				AES * AESHelper3 = new AES(aes, mode, paddingMode);

				AESHelper1->init(c_key1, c_iv);
				AESHelper2->init(c_key2, c_iv);
				AESHelper3->init(c_key3, c_iv);

				AESHelper3->decrypt((unsigned char *)inputFileContent, inputFileSize, &stage1, &stageSize1);
				AESHelper2->encrypt(stage1, stageSize1, &stage2, &stageSize2);
				AESHelper3->decrypt(stage2, stageSize2, &decrypted, &decryptedSize);

				delete AESHelper1, AESHelper2, AESHelper3;


			}
			catch (AESException * e) {
				if (e->getType() == AESException::INVILID_KEY_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現金鑰長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVILID_IV_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現初始向量長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現明文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("3AES(EDE)加解密過程發現密文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
			}

			delete[] stage1, stage2;


		}
		else {
			try {
				AES * AESHelper = new AES(aes, mode, paddingMode);
				AESHelper->init(c_key1, c_iv);
				AESHelper->decrypt((unsigned char *) inputFileContent, inputFileSize, &decrypted, &decryptedSize);
				delete AESHelper;
			}
			catch (AESException * e) {
				if (e->getType() == AESException::INVILID_KEY_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現金鑰長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVILID_IV_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現初始向量長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_PLAINTEXT_LENGHT) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現明文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
				else if (e->getType() == AESException::INVALID_CIPHERTEXT_LENGTH) {
					AlertDialog * alertDialog = new AlertDialog();
					alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
					alertDialog->setMessage(QString::fromLocal8Bit("加解密過程發現密文長度異常，請檢查後重試"));
					alertDialog->exec();
				}
			}
		}


		if (decrypted != NULL && decryptedSize != -1) {
			fwrite(decrypted, 1, decryptedSize, outputFile);
		}




		fclose(inputFile);
		fclose(outputFile);
		delete[] inputFileContent, decrypted;

	}
	else {
		AlertDialog *alertDialog = new AlertDialog();
		alertDialog->setTitle(QString::fromLocal8Bit("錯誤訊息"));
		alertDialog->setMessage(QString::fromLocal8Bit("無法開啟檔案，請確認加解密檔案路徑是否正確"));
		alertDialog->exec();
	}


	delete[] c_key1, c_key2, c_key3, c_iv, c_inputFilePath, c_outputFilePath;
}



int AESMain::aes2ClassAes(int index) {
	switch (index)
	{
	case 0:
		return AES::AES128;
	case 1:
		return AES::AES192;
	case 2:
		return AES::AES256;
	}

	return NULL;
}

int AESMain::mode2ClassMode(int index) {
	switch (index)
	{
	case 0:
		return AES::ECB;
		break;
	case 1:
		return AES::CBC;
		break;
	case 2:
		return AES::OFB8;
		break;
	case 3:
		return AES::CFB8;
		break;
	case 4:
		return AES::CTR;
		break;
	}

	return NULL;
}

int AESMain::paddingMode2ClassPaddingMode(int index) {
	switch (index)
	{
	case 0:
		return AES::NoPadding;
		break;
	case 1:
		return AES::ZeroPadding;
		break;
	case 2:
		return AES::PKCS7Padding;
		break;
	}

	return NULL;
}

int AESMain::char2int(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return NULL;
}

void AESMain::hexChars2Byte(char * ori, int oriSize, unsigned char * tar) {
	for (int i = 0; i < oriSize; i += 2) {
		int fir = this->char2int(ori[i]);
		int sec = this->char2int(ori[i + 1]);
		tar[i / 2] = fir * 16 + sec;
	}
}

void AESMain::byte2HexChars(unsigned char * ori, int oriSize, char * tar) {
	for (int i = 0; i < oriSize; i++) {
		sprintf(tar + i * 2, "%02x", ori[i]);
	}
	tar[oriSize * 2] = '\0';
}





void AESMain::mousePressEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton) {
		this->moveFlag = true;
		this->movePosition = event->globalPos() - this->pos();
		this->setCursor(QCursor(Qt::OpenHandCursor));
		event->accept();
	}
}

void AESMain::mouseMoveEvent(QMouseEvent *event) {
	if (this->moveFlag) {
		this->move(event->globalPos() - this->movePosition);
		event->accept();
	}
}

void AESMain::mouseReleaseEvent(QMouseEvent *event) {
	this->moveFlag = false;
	this->setCursor(QCursor(Qt::ArrowCursor));
	
}