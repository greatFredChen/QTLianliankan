/********************************************************************************
** Form generated from reading UI file 'sounddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDDIALOG_H
#define UI_SOUNDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_sounddialog
{
public:
    QSlider *horizontalSlider;
    QLCDNumber *lcdNumber;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *sounddialog)
    {
        if (sounddialog->objectName().isEmpty())
            sounddialog->setObjectName(QStringLiteral("sounddialog"));
        sounddialog->resize(512, 126);
        sounddialog->setStyleSheet(QStringLiteral("background-color:#87CEFA;"));
        horizontalSlider = new QSlider(sounddialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 20, 251, 22));
        horizontalSlider->setStyleSheet(QLatin1String("\n"
"QSlider::groove:horizontal {\n"
"border: 1px solid #4A708B;\n"
"background: #C0C0C0;\n"
"height: 5px;\n"
"border-radius: 1px;\n"
"padding-left:-1px;\n"
"padding-right:-1px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);\n"
"border: 1px solid #4A708B;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"background: #575757;\n"
"border: 0px solid #777;\n"
"height: 10px;\n"
"border-radius: 2px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal \n"
"{\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \n"
"    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:hover {\n"
"    bac"
                        "kground: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA, \n"
"    stop:0.778409 rgba(255, 255, 255, 255));\n"
" \n"
"    width: 11px;\n"
"    margin-top: -3px;\n"
"    margin-bottom: -3px;\n"
"    border-radius: 5px;\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #00009C;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
" \n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}"));
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);
        lcdNumber = new QLCDNumber(sounddialog);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(420, 20, 71, 31));
        lcdNumber->setDigitCount(4);
        lcdNumber->setProperty("intValue", QVariant(50));
        pushButton = new QPushButton(sounddialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 50, 71, 71));
        pushButton->setStyleSheet(QLatin1String("#pushButton{border-image: url(:/images/musicbutton2.png);}\n"
"#pushButton:checked{border-image: url(:/images/musicbutton.png);}\n"
"\n"
""));
        pushButton->setCheckable(true);
        label_2 = new QLabel(sounddialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 10, 41, 41));
        label_2->setStyleSheet(QStringLiteral("border-image: url(:/images/halfsound.png);"));
        label = new QLabel(sounddialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 10, 41, 41));
        label->setStyleSheet(QStringLiteral("border-image: url(:/images/fullsound.png);"));

        retranslateUi(sounddialog);

        QMetaObject::connectSlotsByName(sounddialog);
    } // setupUi

    void retranslateUi(QDialog *sounddialog)
    {
        sounddialog->setWindowTitle(QApplication::translate("sounddialog", "\351\237\263\351\207\217", Q_NULLPTR));
        pushButton->setText(QString());
        label_2->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sounddialog: public Ui_sounddialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDDIALOG_H
