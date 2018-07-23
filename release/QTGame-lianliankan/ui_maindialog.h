/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QStringLiteral("MainDialog"));
        MainDialog->resize(603, 503);
        MainDialog->setStyleSheet(QLatin1String("#MainDialog{border-image: url(:/images/background5.jpg);}\n"
""));
        gridLayout = new QGridLayout(MainDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(MainDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font.setPointSize(25);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(MainDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200"));
        font1.setPointSize(25);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QLatin1String("#pushButton{color:black;border-image: url(:/images/button1_after.png);}\n"
"#pushButton:hover{color:blue;border-image: url(:/images/button1_after.png);}\n"
"#pushButton:pressed{color:white;border-image: url(:/images/button1_after.png);}\n"
""));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(MainDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QLatin1String("#pushButton_2{color:black;border-image: url(:/images/button2.png);}\n"
"#pushButton_2:hover{color:blue;border-image: url(:/images/button2.png);}\n"
"#pushButton_2:pressed{color:white;border-image: url(:/images/button2.png);}\n"
""));

        verticalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(MainDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QLatin1String("#pushButton_4{color:black;border-image: url(:/images/button3.png);}\n"
"#pushButton_4:hover{color:blue;border-image: url(:/images/button3.png);}\n"
"#pushButton_4:pressed{color:white;border-image: url(:/images/button3.png);}\n"
""));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(MainDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QLatin1String("#pushButton_3{color:black;border-image: url(:/images/button3.png);}\n"
"#pushButton_3:hover{color:blue;border-image: url(:/images/button3.png);}\n"
"#pushButton_3:pressed{color:white;border-image: url(:/images/button3.png);}\n"
""));

        verticalLayout->addWidget(pushButton_3);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);

        gridLayout->addLayout(verticalLayout_2, 1, 1, 2, 1);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);


        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "\344\270\273\350\217\234\345\215\225", Q_NULLPTR));
        label->setText(QApplication::translate("MainDialog", "\350\217\234\345\215\225", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainDialog", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainDialog", "\346\216\222\350\241\214\346\246\234", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainDialog", "\350\277\224\345\233\236\350\207\263\347\231\273\345\275\225\347\252\227\345\217\243", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainDialog", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
