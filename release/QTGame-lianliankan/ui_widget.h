/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QLCDNumber *lcdNumber;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLCDNumber *lcdNumber_2;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(880, 870);
        Widget->setAutoFillBackground(false);
        Widget->setStyleSheet(QStringLiteral("#Widget{background-image: url(:/images/background2.jpg);}"));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        progressBar->setFont(font);
        progressBar->setStyleSheet(QLatin1String("QProgressBar#progressBar:chunk\n"
"{\n"
"background-color:red;\n"
"}\n"
"QProgressBar#progressBar\n"
"{\n"
"color:green;\n"
"}"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(progressBar);

        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setStyleSheet(QLatin1String("background-color:#FFF;\n"
"color:red;"));

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(12);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton#pushButton{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:white;}\n"
"QPushButton#pushButton:hover{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:blue;}\n"
"QPushButton#pushButton:pressed{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:yellow;}\n"
"QPushButton#pushButton:checked{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:yellow;\n"
"}"));
        pushButton->setCheckable(true);
        pushButton->setChecked(false);

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_3{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:white;}\n"
"QPushButton#pushButton_3:hover{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:blue;}\n"
"QPushButton#pushButton_3:pressed{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:yellow;}"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton#pushButton_2{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:white;}\n"
"QPushButton#pushButton_2:hover{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:blue;}\n"
"QPushButton#pushButton_2:pressed{border-image: url(:/images/\346\214\211\351\222\256.PNG);\n"
"color:yellow;}"));

        verticalLayout->addWidget(pushButton_2);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 8);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalSpacer_2 = new QSpacerItem(20, 738, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color:white;"));

        verticalLayout_3->addWidget(label);

        lcdNumber_2 = new QLCDNumber(Widget);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lcdNumber_2->sizePolicy().hasHeightForWidth());
        lcdNumber_2->setSizePolicy(sizePolicy2);
        lcdNumber_2->setMinimumSize(QSize(0, 30));
        QFont font2;
        font2.setPointSize(9);
        lcdNumber_2->setFont(font2);
        lcdNumber_2->setStyleSheet(QLatin1String("background-color:#FFF;\n"
"color:red;"));

        verticalLayout_3->addWidget(lcdNumber_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color:white;"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font3;
        font3.setPointSize(20);
        label_3->setFont(font3);
        label_3->setStyleSheet(QStringLiteral("color:white;background-color:skyblue;"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout_3);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Gaming", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "playing", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Widget", "To Menu", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "music", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "score:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "level:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "Easy", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
