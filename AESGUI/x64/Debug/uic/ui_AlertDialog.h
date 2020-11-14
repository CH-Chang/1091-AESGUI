/********************************************************************************
** Form generated from reading UI file 'AlertDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTDIALOG_H
#define UI_ALERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AlertDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *navigationBar;
    QLabel *title;
    QPushButton *minimize;
    QPushButton *maximize;
    QPushButton *close;
    QLabel *message;
    QHBoxLayout *checkArea;
    QPushButton *comfirm;

    void setupUi(QDialog *AlertDialog)
    {
        if (AlertDialog->objectName().isEmpty())
            AlertDialog->setObjectName(QString::fromUtf8("AlertDialog"));
        AlertDialog->resize(467, 300);
        AlertDialog->setStyleSheet(QString::fromUtf8("#AlertDialog{\n"
"	background-color: white;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(AlertDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        navigationBar = new QHBoxLayout();
        navigationBar->setSpacing(6);
        navigationBar->setObjectName(QString::fromUtf8("navigationBar"));
        title = new QLabel(AlertDialog);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);

        navigationBar->addWidget(title, 0, Qt::AlignLeft|Qt::AlignVCenter);

        minimize = new QPushButton(AlertDialog);
        minimize->setObjectName(QString::fromUtf8("minimize"));
        minimize->setCursor(QCursor(Qt::PointingHandCursor));
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
        icon.addFile(QString::fromUtf8(":/AlertDialog/images/svg/minimize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        minimize->setIcon(icon);
        minimize->setIconSize(QSize(12, 12));

        navigationBar->addWidget(minimize, 0, Qt::AlignRight|Qt::AlignTop);

        maximize = new QPushButton(AlertDialog);
        maximize->setObjectName(QString::fromUtf8("maximize"));
        maximize->setCursor(QCursor(Qt::PointingHandCursor));
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
        icon1.addFile(QString::fromUtf8(":/AlertDialog/images/svg/maximize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        maximize->setIcon(icon1);
        maximize->setIconSize(QSize(12, 12));

        navigationBar->addWidget(maximize, 0, Qt::AlignRight|Qt::AlignTop);

        close = new QPushButton(AlertDialog);
        close->setObjectName(QString::fromUtf8("close"));
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
        icon2.addFile(QString::fromUtf8(":/AlertDialog/images/svg/close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon2);
        close->setIconSize(QSize(12, 12));

        navigationBar->addWidget(close, 0, Qt::AlignRight|Qt::AlignTop);

        navigationBar->setStretch(0, 1);

        verticalLayout->addLayout(navigationBar);

        message = new QLabel(AlertDialog);
        message->setObjectName(QString::fromUtf8("message"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font1.setPointSize(10);
        message->setFont(font1);
        message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(message);

        checkArea = new QHBoxLayout();
        checkArea->setSpacing(6);
        checkArea->setObjectName(QString::fromUtf8("checkArea"));
        comfirm = new QPushButton(AlertDialog);
        comfirm->setObjectName(QString::fromUtf8("comfirm"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comfirm->sizePolicy().hasHeightForWidth());
        comfirm->setSizePolicy(sizePolicy);
        comfirm->setFont(font1);
        comfirm->setCursor(QCursor(Qt::PointingHandCursor));
        comfirm->setStyleSheet(QString::fromUtf8("#comfirm{\n"
"	background-color: white;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 20px 4px 20px;\n"
"\n"
"	color: #00327F;\n"
"}\n"
"\n"
"#comfirm:hover{\n"
"	background-color: #00327F;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding: 4px 20px 4px 20px;\n"
"\n"
"	color: white;\n"
"}\n"
"\n"
"#comfirm:pressed{\n"
"	background-color: #00304A;\n"
"	border: 1px;\n"
"	border-style: solid;\n"
"	border-color: #00327F;\n"
"	border-radius: 5px;\n"
"\n"
"	padding:4px 20px 4px 20px;\n"
"\n"
"	color: white;\n"
"}"));

        checkArea->addWidget(comfirm, 0, Qt::AlignRight|Qt::AlignVCenter);


        verticalLayout->addLayout(checkArea);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);
        verticalLayout->setStretch(2, 1);

        retranslateUi(AlertDialog);

        QMetaObject::connectSlotsByName(AlertDialog);
    } // setupUi

    void retranslateUi(QDialog *AlertDialog)
    {
        AlertDialog->setWindowTitle(QCoreApplication::translate("AlertDialog", "AlertDialog", nullptr));
        title->setText(QString());
#if QT_CONFIG(tooltip)
        minimize->setToolTip(QCoreApplication::translate("AlertDialog", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        minimize->setText(QString());
#if QT_CONFIG(tooltip)
        maximize->setToolTip(QCoreApplication::translate("AlertDialog", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        maximize->setText(QString());
#if QT_CONFIG(tooltip)
        close->setToolTip(QCoreApplication::translate("AlertDialog", "\351\227\234\351\226\211", nullptr));
#endif // QT_CONFIG(tooltip)
        close->setText(QString());
        message->setText(QString());
        comfirm->setText(QCoreApplication::translate("AlertDialog", "\347\242\272\350\252\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlertDialog: public Ui_AlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTDIALOG_H
