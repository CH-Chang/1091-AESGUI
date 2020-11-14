#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>

#include "ui_AESMain.h"

class AESMain : public QMainWindow
{
    Q_OBJECT

public:
    AESMain(QWidget *parent = Q_NULLPTR);

private:

	// 變數
	int moveFlag = false;

    Ui::AESMainClass ui;
	
	QPoint movePosition;

	// 方法
	void init();
	void initView();
	void initInteraction();

	void loading();
	void loadingData();

	int mode2ClassMode(int);
	int paddingMode2ClassPaddingMode(int);
	int aes2ClassAes(int);
	int char2int(char);

	void hexChars2Byte(char *, int, unsigned char *);
	void byte2HexChars(unsigned char *, int, char *);

	
	

protected:

	// 重載方法
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);

public slots:
	void onCloseClicked();
	void onMaximizeClicked();
	void onMinimizeClicked();
	void onLeftClicked();
	void onRightClicked();
	void onStrEncryptClicked();
	void onStrDecryptClicked();
	void onPickFileClicked();
	void onPickPlaceClicked();
	void onFileEncryptClicked();
	void onFileDecryptClicked();


	
};


	
