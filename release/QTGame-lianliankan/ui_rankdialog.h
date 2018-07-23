/********************************************************************************
** Form generated from reading UI file 'rankdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANKDIALOG_H
#define UI_RANKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_rankDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;

    void setupUi(QDialog *rankDialog)
    {
        if (rankDialog->objectName().isEmpty())
            rankDialog->setObjectName(QStringLiteral("rankDialog"));
        rankDialog->resize(861, 800);
        rankDialog->setStyleSheet(QStringLiteral("#rankDialog{border-image: url(:/images/background2.jpg);}"));
        gridLayout = new QGridLayout(rankDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 4, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(rankDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(25);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color:white;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableView = new QTableView(rankDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(16);
        tableView->setFont(font1);
        tableView->setStyleSheet(QLatin1String("background:transparent;color:black;\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"QHeaderView::section:vertical {\n"
"    background: transparent;\n"
"        width: 30px;\n"
"};\n"
"QHeaderView::section:horizontal {\n"
"     background: transparent;\n"
"        height: 30px;\n"
"}"));

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(180, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(rankDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(20);
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QLatin1String("#pushButton_2{color:black;\n"
"border-image: url(:/images/button2.png);}\n"
"#pushButton_2:hover{color:white;\n"
"border-image: url(:/images/button2.png);}\n"
"#pushButton_2:pressed{color:green;\n"
"border-image: url(:/images/button2.png);}"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(rankDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QLatin1String("#pushButton{color:black;\n"
"border-image: url(:/images/button2.png);}\n"
"#pushButton:hover{color:white;\n"
"border-image: url(:/images/button2.png);}\n"
"#pushButton:pressed{color:green;\n"
"border-image: url(:/images/button2.png);}"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(180, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 8);
        verticalLayout_2->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout_2, 1, 1, 2, 1);

        horizontalSpacer_4 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 1);

        label_2 = new QLabel(rankDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(12);
        label_2->setFont(font3);
        label_2->setStyleSheet(QStringLiteral("color:white;"));
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 3, 1, 1, 1);


        retranslateUi(rankDialog);

        QMetaObject::connectSlotsByName(rankDialog);
    } // setupUi

    void retranslateUi(QDialog *rankDialog)
    {
        rankDialog->setWindowTitle(QApplication::translate("rankDialog", "\346\216\222\350\241\214\346\246\234", Q_NULLPTR));
        label->setText(QApplication::translate("rankDialog", "\346\216\222\350\241\214\346\246\234", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("rankDialog", "\345\261\225\347\244\272", Q_NULLPTR));
        pushButton->setText(QApplication::translate("rankDialog", "\350\277\224\345\233\236", Q_NULLPTR));
        label_2->setText(QApplication::translate("rankDialog", "tips:1.\350\203\214\346\231\257\350\211\262\344\270\272\351\235\222\350\211\262\347\232\204\346\241\206\344\270\255\346\230\276\347\244\272\347\232\204\346\230\257\346\202\250\347\232\204\344\277\241\346\201\257\357\274\210\345\214\205\346\213\254\347\224\250\346\210\267\345\220\215\343\200\201\345\210\206\346\225\260\343\200\201\346\216\222\345\220\215\357\274\2112.\350\257\245\346\246\234\345\215\225\345\217\252\346\230\276\347\244\2721-10\345\220\215\357\274\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rankDialog: public Ui_rankDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANKDIALOG_H
