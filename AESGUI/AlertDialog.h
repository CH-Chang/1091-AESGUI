#pragma once

#include <QDialog>
#include <QCursor>
#include <QMouseEvent>

#include "ui_AlertDialog.h"

class AlertDialog : public QDialog
{
	Q_OBJECT

public:
	AlertDialog(QWidget *parent = Q_NULLPTR);
	~AlertDialog();

	void setTitle(QString);
	void setMessage(QString);

private:

	// �ܼ�
	int moveFlag = false;

	Ui::AlertDialog ui;

	QPoint movePosition;

	void init();
	void initView();
	void initInteraction();

protected:

	// ������k
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);

public slots:
	void onCloseClicked();
	void onMaximizeClicked();
	void onMinimizeClicked();
	void onComfirmClicked();
};
