#include <QCursor>
#include <QMouseEvent>


#include "AlertDialog.h"

AlertDialog::AlertDialog(QWidget *parent)
	: QDialog(parent)
{
	this->init();
}

AlertDialog::~AlertDialog()
{
}

void AlertDialog::init() {
	this->initView();
	this->initInteraction();
}

void AlertDialog::initView() {
	ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint);
	this->setWindowIcon(QIcon(":/AlertDialog/images/svg/icon.svg"));
}

void AlertDialog::initInteraction() {
	connect(ui.close, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
	connect(ui.maximize, SIGNAL(clicked()), this, SLOT(onMaximizeClicked()));
	connect(ui.minimize, SIGNAL(clicked()), this, SLOT(onMinimizeClicked()));
	connect(ui.comfirm, SIGNAL(clicked()), this, SLOT(onComfirmClicked()));
}

void AlertDialog::setTitle(QString s) {
	ui.title->setText(s);
	this->setWindowTitle(s);
}

void AlertDialog::setMessage(QString s) {
	ui.message->setText(s);
	
}


void AlertDialog::onCloseClicked() {
	this->reject();
}
void AlertDialog::onMaximizeClicked() {
	if (this->isMaximized()) {
		this->showNormal();
	}
	else {
		this->showMaximized();
	}
	
}
void AlertDialog::onMinimizeClicked() {
	this->showMinimized();
}
void AlertDialog::onComfirmClicked() {
	this->accept();
}



void AlertDialog::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		this->moveFlag = true;
		this->movePosition = event->globalPos() - this->pos();
		this->setCursor(QCursor(Qt::OpenHandCursor));
		event->accept();
	}
}

void AlertDialog::mouseMoveEvent(QMouseEvent *event) {
	if (this->moveFlag) {
		this->move(event->globalPos() - this->movePosition);
		event->accept();
	}
}

void AlertDialog::mouseReleaseEvent(QMouseEvent *event) {
	this->moveFlag = false;
	this->setCursor(QCursor(Qt::ArrowCursor));

}