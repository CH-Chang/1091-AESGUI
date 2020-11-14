/********************************************************************************
** Form generated from reading UI file 'AESMain.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AESMAIN_H
#define UI_AESMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AESMainClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *navigationBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *minimize;
    QPushButton *maximize;
    QPushButton *close;
    QWidget *contentArea;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *left;
    QStackedWidget *stackedWidget;
    QWidget *stringPage;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *form;
    QLabel *AESModeLabel;
    QLabel *AESKey1Label;
    QPushButton *strDecrypt;
    QLabel *AESBitsLabel;
    QLabel *AESKey3Label;
    QPushButton *strEncrypt;
    QLabel *AESKey2Label;
    QLabel *AESIvLabel;
    QLabel *AESPaddingModeLabel;
    QComboBox *AESBits;
    QComboBox *AESMode;
    QComboBox *AESPaddingMode;
    QLineEdit *AESKey1;
    QLineEdit *AESKey2;
    QLineEdit *AESKey3;
    QLineEdit *AESIv;
    QVBoxLayout *plaintextArea;
    QLabel *plaintextLabel;
    QTextEdit *plaintext;
    QVBoxLayout *ciphertextArea;
    QLabel *ciphertextLabel;
    QTextEdit *ciphertext;
    QWidget *filePage;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *fileForm;
    QLabel *fileAESModeLabel;
    QLineEdit *fileAESIv;
    QLabel *fileAESKey2Label;
    QLineEdit *fileAESKey1;
    QLabel *fileAESKey3Label;
    QLabel *fileAESIvLabel;
    QLabel *fileAESBitsLabel;
    QComboBox *fileAESPaddingMode;
    QLineEdit *fileAESKey2;
    QLabel *filePaddingModeLabel;
    QComboBox *fileAESBits;
    QLabel *fileAESKey1Label;
    QComboBox *fileAESMode;
    QLineEdit *fileAESKey3;
    QGridLayout *fileControl;
    QLineEdit *file;
    QPushButton *fileEncrypt;
    QPushButton *pickFile;
    QLabel *fileLabel;
    QLineEdit *place;
    QLabel *placeLabel;
    QPushButton *pickPlace;
    QPushButton *fileDecrypt;
    QPushButton *right;
    QVBoxLayout *copyrightArea;
    QLabel *copyright;

    void setupUi(QMainWindow *AESMainClass)
    {
        if (AESMainClass->objectName().isEmpty())
            AESMainClass->setObjectName(QString::fromUtf8("AESMainClass"));
        AESMainClass->resize(800, 850);
        centralWidget = new QWidget(AESMainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("#centralWidget{\n"
"	background-color: white;\n"
"}"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 5, -1, 5);
        navigationBar = new QWidget(centralWidget);
        navigationBar->setObjectName(QString::fromUtf8("navigationBar"));
        horizontalLayout = new QHBoxLayout(navigationBar);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        minimize = new QPushButton(navigationBar);
        minimize->setObjectName(QString::fromUtf8("minimize"));
        minimize->setStyleSheet(QString::fromUtf8("#minimize{\n"
"	background-color: transparent;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#minimize:hover{\n"
"	background-color: #eeeeee;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#minimize:pressed{\n"
"	background-color: #999999;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/AESMain/images/svg/minimize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        minimize->setIcon(icon);
        minimize->setIconSize(QSize(12, 12));

        horizontalLayout->addWidget(minimize);

        maximize = new QPushButton(navigationBar);
        maximize->setObjectName(QString::fromUtf8("maximize"));
        maximize->setStyleSheet(QString::fromUtf8("#maximize{\n"
"	background-color: transparent;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#maximize:hover{\n"
"	background-color: #eeeeee;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#maximize:pressed{\n"
"	background-color: #999999;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/AESMain/images/svg/maximize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        maximize->setIcon(icon1);
        maximize->setIconSize(QSize(12, 12));

        horizontalLayout->addWidget(maximize);

        close = new QPushButton(navigationBar);
        close->setObjectName(QString::fromUtf8("close"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        close->setFont(font);
        close->setCursor(QCursor(Qt::PointingHandCursor));
        close->setStyleSheet(QString::fromUtf8("#close{\n"
"	background-color: transparent;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#close:hover{\n"
"	background-color: #eeeeee;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}\n"
"\n"
"#close:pressed{\n"
"	background-color: #999999;\n"
"	border: 0;\n"
"	border-style:none;\n"
"	border-radius:5px;\n"
"	padding: 3px 3px 3px 3px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/AESMain/images/svg/close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon2);
        close->setIconSize(QSize(12, 12));

        horizontalLayout->addWidget(close);


        verticalLayout->addWidget(navigationBar, 0, Qt::AlignRight|Qt::AlignTop);

        contentArea = new QWidget(centralWidget);
        contentArea->setObjectName(QString::fromUtf8("contentArea"));
        horizontalLayout_2 = new QHBoxLayout(contentArea);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        left = new QPushButton(contentArea);
        left->setObjectName(QString::fromUtf8("left"));
        left->setCursor(QCursor(Qt::PointingHandCursor));
        left->setStyleSheet(QString::fromUtf8("#left{\n"
"	background-color: transparent;\n"
"	border: 0;\n"
"	border-style: none;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/AESMain/images/svg/left.svg"), QSize(), QIcon::Normal, QIcon::Off);
        left->setIcon(icon3);
        left->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(left);

        stackedWidget = new QStackedWidget(contentArea);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        stringPage = new QWidget();
        stringPage->setObjectName(QString::fromUtf8("stringPage"));
        verticalLayout_2 = new QVBoxLayout(stringPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        form = new QGridLayout();
        form->setSpacing(6);
        form->setObjectName(QString::fromUtf8("form"));
        AESModeLabel = new QLabel(stringPage);
        AESModeLabel->setObjectName(QString::fromUtf8("AESModeLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font1.setPointSize(10);
        AESModeLabel->setFont(font1);
        AESModeLabel->setAlignment(Qt::AlignCenter);

        form->addWidget(AESModeLabel, 3, 0, 1, 1);

        AESKey1Label = new QLabel(stringPage);
        AESKey1Label->setObjectName(QString::fromUtf8("AESKey1Label"));
        AESKey1Label->setFont(font1);
        AESKey1Label->setAlignment(Qt::AlignCenter);

        form->addWidget(AESKey1Label, 5, 0, 1, 1);

        strDecrypt = new QPushButton(stringPage);
        strDecrypt->setObjectName(QString::fromUtf8("strDecrypt"));
        strDecrypt->setFont(font1);
        strDecrypt->setCursor(QCursor(Qt::PointingHandCursor));
        strDecrypt->setStyleSheet(QString::fromUtf8("#strDecrypt{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#strDecrypt:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#strDecrypt:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        form->addWidget(strDecrypt, 9, 4, 1, 1);

        AESBitsLabel = new QLabel(stringPage);
        AESBitsLabel->setObjectName(QString::fromUtf8("AESBitsLabel"));
        AESBitsLabel->setFont(font1);
        AESBitsLabel->setLayoutDirection(Qt::LeftToRight);
        AESBitsLabel->setTextFormat(Qt::PlainText);
        AESBitsLabel->setAlignment(Qt::AlignCenter);
        AESBitsLabel->setWordWrap(false);

        form->addWidget(AESBitsLabel, 0, 0, 1, 1);

        AESKey3Label = new QLabel(stringPage);
        AESKey3Label->setObjectName(QString::fromUtf8("AESKey3Label"));
        AESKey3Label->setFont(font1);
        AESKey3Label->setAlignment(Qt::AlignCenter);

        form->addWidget(AESKey3Label, 7, 0, 1, 1);

        strEncrypt = new QPushButton(stringPage);
        strEncrypt->setObjectName(QString::fromUtf8("strEncrypt"));
        strEncrypt->setFont(font1);
        strEncrypt->setCursor(QCursor(Qt::PointingHandCursor));
        strEncrypt->setStyleSheet(QString::fromUtf8("#strEncrypt{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#strEncrypt:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#strEncrypt:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        form->addWidget(strEncrypt, 9, 3, 1, 1);

        AESKey2Label = new QLabel(stringPage);
        AESKey2Label->setObjectName(QString::fromUtf8("AESKey2Label"));
        AESKey2Label->setFont(font1);
        AESKey2Label->setAlignment(Qt::AlignCenter);

        form->addWidget(AESKey2Label, 6, 0, 1, 1);

        AESIvLabel = new QLabel(stringPage);
        AESIvLabel->setObjectName(QString::fromUtf8("AESIvLabel"));
        AESIvLabel->setFont(font1);
        AESIvLabel->setAlignment(Qt::AlignCenter);

        form->addWidget(AESIvLabel, 8, 0, 1, 1);

        AESPaddingModeLabel = new QLabel(stringPage);
        AESPaddingModeLabel->setObjectName(QString::fromUtf8("AESPaddingModeLabel"));
        AESPaddingModeLabel->setFont(font1);
        AESPaddingModeLabel->setAlignment(Qt::AlignCenter);

        form->addWidget(AESPaddingModeLabel, 4, 0, 1, 1);

        AESBits = new QComboBox(stringPage);
        AESBits->setObjectName(QString::fromUtf8("AESBits"));
        AESBits->setFont(font1);
        AESBits->setCursor(QCursor(Qt::PointingHandCursor));
        AESBits->setStyleSheet(QString::fromUtf8("#AESBits{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESBits:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESBits:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESBits::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#AESBits::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        form->addWidget(AESBits, 0, 1, 1, 4);

        AESMode = new QComboBox(stringPage);
        AESMode->setObjectName(QString::fromUtf8("AESMode"));
        AESMode->setFont(font1);
        AESMode->setCursor(QCursor(Qt::PointingHandCursor));
        AESMode->setStyleSheet(QString::fromUtf8("#AESMode{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESMode:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"	\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESMode:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESMode::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#AESMode::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        form->addWidget(AESMode, 3, 1, 1, 4);

        AESPaddingMode = new QComboBox(stringPage);
        AESPaddingMode->setObjectName(QString::fromUtf8("AESPaddingMode"));
        AESPaddingMode->setFont(font1);
        AESPaddingMode->setCursor(QCursor(Qt::PointingHandCursor));
        AESPaddingMode->setStyleSheet(QString::fromUtf8("#AESPaddingMode{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESPaddingMode:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESPaddingMode:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#AESPaddingMode::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#AESPaddingMode::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        form->addWidget(AESPaddingMode, 4, 1, 1, 4);

        AESKey1 = new QLineEdit(stringPage);
        AESKey1->setObjectName(QString::fromUtf8("AESKey1"));
        AESKey1->setFont(font1);
        AESKey1->setCursor(QCursor(Qt::IBeamCursor));
        AESKey1->setStyleSheet(QString::fromUtf8("#AESKey1{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey1:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey1:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        form->addWidget(AESKey1, 5, 1, 1, 4);

        AESKey2 = new QLineEdit(stringPage);
        AESKey2->setObjectName(QString::fromUtf8("AESKey2"));
        AESKey2->setFont(font1);
        AESKey2->setStyleSheet(QString::fromUtf8("#AESKey2{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey2:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey2:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        form->addWidget(AESKey2, 6, 1, 1, 4);

        AESKey3 = new QLineEdit(stringPage);
        AESKey3->setObjectName(QString::fromUtf8("AESKey3"));
        AESKey3->setFont(font1);
        AESKey3->setStyleSheet(QString::fromUtf8("#AESKey3{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey3:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESKey3:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        form->addWidget(AESKey3, 7, 1, 1, 4);

        AESIv = new QLineEdit(stringPage);
        AESIv->setObjectName(QString::fromUtf8("AESIv"));
        AESIv->setFont(font1);
        AESIv->setStyleSheet(QString::fromUtf8("#AESIv{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESIv:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#AESIv:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        form->addWidget(AESIv, 8, 1, 1, 4);


        verticalLayout_2->addLayout(form);

        plaintextArea = new QVBoxLayout();
        plaintextArea->setSpacing(6);
        plaintextArea->setObjectName(QString::fromUtf8("plaintextArea"));
        plaintextLabel = new QLabel(stringPage);
        plaintextLabel->setObjectName(QString::fromUtf8("plaintextLabel"));
        plaintextLabel->setFont(font1);

        plaintextArea->addWidget(plaintextLabel);

        plaintext = new QTextEdit(stringPage);
        plaintext->setObjectName(QString::fromUtf8("plaintext"));
        plaintext->setFont(font1);
        plaintext->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        plaintext->setStyleSheet(QString::fromUtf8("#plaintext{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #ddd;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}\n"
"\n"
"#plaintext:hover{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #00327F;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}\n"
"\n"
"#plaintext:focus{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #00327F;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}"));

        plaintextArea->addWidget(plaintext);


        verticalLayout_2->addLayout(plaintextArea);

        ciphertextArea = new QVBoxLayout();
        ciphertextArea->setSpacing(6);
        ciphertextArea->setObjectName(QString::fromUtf8("ciphertextArea"));
        ciphertextLabel = new QLabel(stringPage);
        ciphertextLabel->setObjectName(QString::fromUtf8("ciphertextLabel"));
        ciphertextLabel->setFont(font1);
        ciphertextLabel->setCursor(QCursor(Qt::PointingHandCursor));

        ciphertextArea->addWidget(ciphertextLabel);

        ciphertext = new QTextEdit(stringPage);
        ciphertext->setObjectName(QString::fromUtf8("ciphertext"));
        ciphertext->setFont(font1);
        ciphertext->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        ciphertext->setStyleSheet(QString::fromUtf8("#ciphertext{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #ddd;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}\n"
"\n"
"#ciphertext:hover{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #00327F;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}\n"
"\n"
"#ciphertext:focus{\n"
"	background-color: white;\n"
"	\n"
"	border: 1px solid #00327F;\n"
"	border-radius: 10px;\n"
"\n"
"	padding: 10px 10px 10px 10px;\n"
"}"));

        ciphertextArea->addWidget(ciphertext);


        verticalLayout_2->addLayout(ciphertextArea);

        stackedWidget->addWidget(stringPage);
        filePage = new QWidget();
        filePage->setObjectName(QString::fromUtf8("filePage"));
        verticalLayout_3 = new QVBoxLayout(filePage);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        fileForm = new QGridLayout();
        fileForm->setSpacing(6);
        fileForm->setObjectName(QString::fromUtf8("fileForm"));
        fileForm->setVerticalSpacing(15);
        fileAESModeLabel = new QLabel(filePage);
        fileAESModeLabel->setObjectName(QString::fromUtf8("fileAESModeLabel"));
        fileAESModeLabel->setFont(font1);
        fileAESModeLabel->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESModeLabel, 1, 0, 1, 1);

        fileAESIv = new QLineEdit(filePage);
        fileAESIv->setObjectName(QString::fromUtf8("fileAESIv"));
        fileAESIv->setFont(font1);
        fileAESIv->setStyleSheet(QString::fromUtf8("#fileAESIv{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESIv:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESIv:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileForm->addWidget(fileAESIv, 6, 1, 1, 1);

        fileAESKey2Label = new QLabel(filePage);
        fileAESKey2Label->setObjectName(QString::fromUtf8("fileAESKey2Label"));
        fileAESKey2Label->setFont(font1);
        fileAESKey2Label->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESKey2Label, 4, 0, 1, 1);

        fileAESKey1 = new QLineEdit(filePage);
        fileAESKey1->setObjectName(QString::fromUtf8("fileAESKey1"));
        fileAESKey1->setFont(font1);
        fileAESKey1->setStyleSheet(QString::fromUtf8("#fileAESKey1{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey1:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey1:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileForm->addWidget(fileAESKey1, 3, 1, 1, 1);

        fileAESKey3Label = new QLabel(filePage);
        fileAESKey3Label->setObjectName(QString::fromUtf8("fileAESKey3Label"));
        fileAESKey3Label->setFont(font1);
        fileAESKey3Label->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESKey3Label, 5, 0, 1, 1);

        fileAESIvLabel = new QLabel(filePage);
        fileAESIvLabel->setObjectName(QString::fromUtf8("fileAESIvLabel"));
        fileAESIvLabel->setFont(font1);
        fileAESIvLabel->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESIvLabel, 6, 0, 1, 1);

        fileAESBitsLabel = new QLabel(filePage);
        fileAESBitsLabel->setObjectName(QString::fromUtf8("fileAESBitsLabel"));
        fileAESBitsLabel->setFont(font1);
        fileAESBitsLabel->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESBitsLabel, 0, 0, 1, 1);

        fileAESPaddingMode = new QComboBox(filePage);
        fileAESPaddingMode->setObjectName(QString::fromUtf8("fileAESPaddingMode"));
        fileAESPaddingMode->setFont(font1);
        fileAESPaddingMode->setStyleSheet(QString::fromUtf8("#fileAESPaddingMode{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESPaddingMode:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESPaddingMode:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESPaddingMode::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#fileAESPaddingMode::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        fileForm->addWidget(fileAESPaddingMode, 2, 1, 1, 1);

        fileAESKey2 = new QLineEdit(filePage);
        fileAESKey2->setObjectName(QString::fromUtf8("fileAESKey2"));
        fileAESKey2->setFont(font1);
        fileAESKey2->setStyleSheet(QString::fromUtf8("#fileAESKey2{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey2:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey2:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileForm->addWidget(fileAESKey2, 4, 1, 1, 1);

        filePaddingModeLabel = new QLabel(filePage);
        filePaddingModeLabel->setObjectName(QString::fromUtf8("filePaddingModeLabel"));
        filePaddingModeLabel->setFont(font1);
        filePaddingModeLabel->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(filePaddingModeLabel, 2, 0, 1, 1);

        fileAESBits = new QComboBox(filePage);
        fileAESBits->setObjectName(QString::fromUtf8("fileAESBits"));
        fileAESBits->setFont(font1);
        fileAESBits->setStyleSheet(QString::fromUtf8("#fileAESBits{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESBits:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESBits:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESBits::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#fileAESBits::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        fileForm->addWidget(fileAESBits, 0, 1, 1, 1);

        fileAESKey1Label = new QLabel(filePage);
        fileAESKey1Label->setObjectName(QString::fromUtf8("fileAESKey1Label"));
        fileAESKey1Label->setFont(font1);
        fileAESKey1Label->setAlignment(Qt::AlignCenter);

        fileForm->addWidget(fileAESKey1Label, 3, 0, 1, 1);

        fileAESMode = new QComboBox(filePage);
        fileAESMode->setObjectName(QString::fromUtf8("fileAESMode"));
        fileAESMode->setFont(font1);
        fileAESMode->setStyleSheet(QString::fromUtf8("#fileAESMode{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESMode:hover{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESMode:focus{\n"
"	border: 0;\n"
"	border-style: none;\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileAESMode::drop-down {\n"
"   	border: 0px;\n"
"	background-color: white;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"}\n"
"\n"
"#fileAESMode::down-arrow {\n"
"    image: url(:/AESMain/images/svg/down.svg);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}"));

        fileForm->addWidget(fileAESMode, 1, 1, 1, 1);

        fileAESKey3 = new QLineEdit(filePage);
        fileAESKey3->setObjectName(QString::fromUtf8("fileAESKey3"));
        fileAESKey3->setFont(font1);
        fileAESKey3->setStyleSheet(QString::fromUtf8("#fileAESKey3{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey3:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#fileAESKey3:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileForm->addWidget(fileAESKey3, 5, 1, 1, 1);

        fileForm->setColumnStretch(0, 1);
        fileForm->setColumnStretch(1, 5);

        verticalLayout_3->addLayout(fileForm);

        fileControl = new QGridLayout();
        fileControl->setSpacing(6);
        fileControl->setObjectName(QString::fromUtf8("fileControl"));
        fileControl->setVerticalSpacing(15);
        file = new QLineEdit(filePage);
        file->setObjectName(QString::fromUtf8("file"));
        file->setFont(font1);
        file->setStyleSheet(QString::fromUtf8("#file{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#file:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#file:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileControl->addWidget(file, 0, 1, 1, 2);

        fileEncrypt = new QPushButton(filePage);
        fileEncrypt->setObjectName(QString::fromUtf8("fileEncrypt"));
        fileEncrypt->setFont(font1);
        fileEncrypt->setCursor(QCursor(Qt::PointingHandCursor));
        fileEncrypt->setStyleSheet(QString::fromUtf8("#fileEncrypt{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileEncrypt:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#fileEncrypt:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        fileControl->addWidget(fileEncrypt, 2, 2, 1, 1);

        pickFile = new QPushButton(filePage);
        pickFile->setObjectName(QString::fromUtf8("pickFile"));
        pickFile->setFont(font1);
        pickFile->setCursor(QCursor(Qt::PointingHandCursor));
        pickFile->setStyleSheet(QString::fromUtf8("#pickFile{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#pickFile:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#pickFile:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        fileControl->addWidget(pickFile, 0, 3, 1, 1);

        fileLabel = new QLabel(filePage);
        fileLabel->setObjectName(QString::fromUtf8("fileLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fileLabel->sizePolicy().hasHeightForWidth());
        fileLabel->setSizePolicy(sizePolicy);
        fileLabel->setFont(font1);
        fileLabel->setScaledContents(false);
        fileLabel->setAlignment(Qt::AlignCenter);
        fileLabel->setWordWrap(true);

        fileControl->addWidget(fileLabel, 0, 0, 1, 1);

        place = new QLineEdit(filePage);
        place->setObjectName(QString::fromUtf8("place"));
        place->setFont(font1);
        place->setStyleSheet(QString::fromUtf8("#place{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #ddd;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#place:hover{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}\n"
"\n"
"#place:focus{\n"
"	background-color: white;\n"
"	border: 0;\n"
"	border-style: none;\n"
"\n"
"	border-bottom: 2px solid #00327F;\n"
"\n"
"	padding: 2px 3px 2px 3px;\n"
"}"));

        fileControl->addWidget(place, 1, 1, 1, 2);

        placeLabel = new QLabel(filePage);
        placeLabel->setObjectName(QString::fromUtf8("placeLabel"));
        placeLabel->setFont(font1);
        placeLabel->setAlignment(Qt::AlignCenter);

        fileControl->addWidget(placeLabel, 1, 0, 1, 1);

        pickPlace = new QPushButton(filePage);
        pickPlace->setObjectName(QString::fromUtf8("pickPlace"));
        pickPlace->setFont(font1);
        pickPlace->setCursor(QCursor(Qt::PointingHandCursor));
        pickPlace->setStyleSheet(QString::fromUtf8("#pickPlace{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#pickPlace:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#pickPlace:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        fileControl->addWidget(pickPlace, 1, 3, 1, 1);

        fileDecrypt = new QPushButton(filePage);
        fileDecrypt->setObjectName(QString::fromUtf8("fileDecrypt"));
        fileDecrypt->setFont(font1);
        fileDecrypt->setCursor(QCursor(Qt::PointingHandCursor));
        fileDecrypt->setStyleSheet(QString::fromUtf8("#fileDecrypt{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 2px 4px 2px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#fileDecrypt:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#fileDecrypt:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 2px 2px 2px 2px;\n"
"\n"
"	color: white;\n"
"}"));

        fileControl->addWidget(fileDecrypt, 2, 3, 1, 1);

        fileControl->setColumnStretch(0, 1);
        fileControl->setColumnStretch(1, 3);
        fileControl->setColumnStretch(2, 1);
        fileControl->setColumnStretch(3, 1);

        verticalLayout_3->addLayout(fileControl);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        stackedWidget->addWidget(filePage);

        horizontalLayout_2->addWidget(stackedWidget);

        right = new QPushButton(contentArea);
        right->setObjectName(QString::fromUtf8("right"));
        right->setCursor(QCursor(Qt::PointingHandCursor));
        right->setStyleSheet(QString::fromUtf8("#right{\n"
"	background-color: transparent;\n"
"	border: 0;\n"
"	border-style: none;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/AESMain/images/svg/right.svg"), QSize(), QIcon::Normal, QIcon::Off);
        right->setIcon(icon4);
        right->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(right);


        verticalLayout->addWidget(contentArea);

        copyrightArea = new QVBoxLayout();
        copyrightArea->setSpacing(6);
        copyrightArea->setObjectName(QString::fromUtf8("copyrightArea"));
        copyright = new QLabel(centralWidget);
        copyright->setObjectName(QString::fromUtf8("copyright"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font2.setPointSize(8);
        copyright->setFont(font2);
        copyright->setStyleSheet(QString::fromUtf8("#copyright{\n"
"	padding-top: 5px;\n"
"	padding-bottom: 5px;\n"
"}"));
        copyright->setAlignment(Qt::AlignCenter);

        copyrightArea->addWidget(copyright);


        verticalLayout->addLayout(copyrightArea);

        AESMainClass->setCentralWidget(centralWidget);

        retranslateUi(AESMainClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AESMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *AESMainClass)
    {
        AESMainClass->setWindowTitle(QCoreApplication::translate("AESMainClass", "AESMain", nullptr));
        minimize->setText(QString());
        maximize->setText(QString());
#if QT_CONFIG(tooltip)
        close->setToolTip(QCoreApplication::translate("AESMainClass", "\351\227\234\351\226\211", nullptr));
#endif // QT_CONFIG(tooltip)
        close->setText(QString());
        left->setText(QString());
        AESModeLabel->setText(QCoreApplication::translate("AESMainClass", "AES\346\250\241\345\274\217", nullptr));
        AESKey1Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\270\200", nullptr));
        strDecrypt->setText(QCoreApplication::translate("AESMainClass", "\350\247\243\345\257\206", nullptr));
        AESBitsLabel->setText(QCoreApplication::translate("AESMainClass", "AES\344\275\215\345\205\203", nullptr));
        AESKey3Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\270\211", nullptr));
        strEncrypt->setText(QCoreApplication::translate("AESMainClass", "\345\212\240\345\257\206", nullptr));
        AESKey2Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\272\214", nullptr));
        AESIvLabel->setText(QCoreApplication::translate("AESMainClass", "\345\210\235\345\247\213\345\220\221\351\207\217", nullptr));
        AESPaddingModeLabel->setText(QCoreApplication::translate("AESMainClass", "\345\241\253\345\205\205\346\250\241\345\274\217", nullptr));
#if QT_CONFIG(tooltip)
        AESBits->setToolTip(QCoreApplication::translate("AESMainClass", "\350\253\213\351\201\270\346\223\207AES\345\212\240\345\257\206\344\275\215\345\205\203", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        AESKey1->setToolTip(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\245\347\233\270\345\260\215\346\207\211\344\275\215\345\205\203\347\232\204\351\207\221\351\221\260", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        AESKey1->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        AESKey1->setPlaceholderText(QString());
#if QT_CONFIG(tooltip)
        AESKey2->setToolTip(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\245\347\233\270\345\260\215\346\207\211\344\275\215\345\205\203\347\232\204\351\207\221\351\221\260 \357\274\210\351\235\236EDE\346\250\241\345\274\217\345\205\215\345\241\253\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        AESKey2->setPlaceholderText(QString());
#if QT_CONFIG(tooltip)
        AESKey3->setToolTip(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\245\347\233\270\345\260\215\346\207\211\344\275\215\345\205\203\347\232\204\351\207\221\351\221\260 \357\274\210\351\235\236EDE\346\250\241\345\274\217\345\205\215\345\241\253\357\274\211", nullptr));
#endif // QT_CONFIG(tooltip)
        AESKey3->setPlaceholderText(QString());
#if QT_CONFIG(tooltip)
        AESIv->setToolTip(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\24516\345\200\213\345\255\227\345\205\203\347\232\204\345\210\235\345\247\213\345\220\221\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        AESIv->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        AESIv->setPlaceholderText(QString());
        plaintextLabel->setText(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\245\345\212\240\345\257\206\345\205\247\345\256\271\357\274\232", nullptr));
        ciphertextLabel->setText(QCoreApplication::translate("AESMainClass", "\350\253\213\350\274\270\345\205\245\350\247\243\345\257\206\345\205\247\345\256\271\357\274\232", nullptr));
        fileAESModeLabel->setText(QCoreApplication::translate("AESMainClass", "AES\346\250\241\345\274\217", nullptr));
        fileAESKey2Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\272\214", nullptr));
        fileAESKey3Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\270\211", nullptr));
        fileAESIvLabel->setText(QCoreApplication::translate("AESMainClass", "\345\210\235\345\247\213\345\220\221\351\207\217", nullptr));
        fileAESBitsLabel->setText(QCoreApplication::translate("AESMainClass", "AES\344\275\215\345\205\203", nullptr));
        filePaddingModeLabel->setText(QCoreApplication::translate("AESMainClass", "\345\241\253\345\205\205\346\250\241\345\274\217", nullptr));
        fileAESKey1Label->setText(QCoreApplication::translate("AESMainClass", "\351\207\221\351\221\260\344\270\200", nullptr));
        fileEncrypt->setText(QCoreApplication::translate("AESMainClass", "\345\212\240\345\257\206", nullptr));
        pickFile->setText(QCoreApplication::translate("AESMainClass", "\351\201\270\346\223\207\346\252\224\346\241\210", nullptr));
        fileLabel->setText(QCoreApplication::translate("AESMainClass", "\345\212\240\350\247\243\345\257\206\346\252\224\346\241\210", nullptr));
        placeLabel->setText(QCoreApplication::translate("AESMainClass", "\344\277\235\345\255\230\350\263\207\346\226\231\345\244\276", nullptr));
        pickPlace->setText(QCoreApplication::translate("AESMainClass", "\351\201\270\346\223\207\350\263\207\346\226\231\345\244\276", nullptr));
        fileDecrypt->setText(QCoreApplication::translate("AESMainClass", "\350\247\243\345\257\206", nullptr));
        right->setText(QString());
        copyright->setText(QCoreApplication::translate("AESMainClass", "Copyright \302\251 2020 CHANG CHIH HSIANG. All rights reserved.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AESMainClass: public Ui_AESMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AESMAIN_H
