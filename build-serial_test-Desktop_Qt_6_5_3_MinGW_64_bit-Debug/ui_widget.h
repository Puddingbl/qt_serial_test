/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_6;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextBrowser *text_rx;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QPushButton *btn_clear_rx;
    QPushButton *btn_open;
    QPushButton *btn_clear_tx;
    QPushButton *btn_send;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox_Port;
    QLabel *label;
    QComboBox *comboBox_Baud;
    QLabel *label_3;
    QComboBox *comboBox_Stop;
    QLabel *label_4;
    QComboBox *comboBox_DataBit;
    QLabel *label_5;
    QComboBox *comboBox_Varity;
    QTextEdit *text_tx;
    QWidget *tab_2;
    QLabel *label_6;
    QWidget *tab_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *widget_4;
    QWidget *widget_3;
    QLabel *label_7;
    QLineEdit *lineEditKey;
    QWidget *widget_2;
    QLabel *label_8;
    QLineEdit *lineEditIv;
    QLabel *label_9;
    QTextBrowser *textFileInfo;
    QPushButton *pushButton_6;
    QWidget *widget_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QComboBox *comboBox_Port_2;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit;
    QLabel *label_12;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_13;
    QPushButton *pushButton;
    QLabel *label_14;
    QLineEdit *lineEdit_4;
    QLabel *label_15;
    QLineEdit *lineEdit_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(510, 500);
        gridLayout_3 = new QGridLayout(Widget);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        widget_6 = new QWidget(Widget);
        widget_6->setObjectName("widget_6");
        gridLayout_4 = new QGridLayout(widget_6);
        gridLayout_4->setObjectName("gridLayout_4");
        tabWidget = new QTabWidget(widget_6);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setUsesScrollButtons(true);
        tab = new QWidget();
        tab->setObjectName("tab");
        text_rx = new QTextBrowser(tab);
        text_rx->setObjectName("text_rx");
        text_rx->setEnabled(true);
        text_rx->setGeometry(QRect(9, 9, 256, 192));
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(280, 230, 151, 72));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        btn_clear_rx = new QPushButton(widget);
        btn_clear_rx->setObjectName("btn_clear_rx");

        gridLayout_2->addWidget(btn_clear_rx, 0, 2, 1, 1);

        btn_open = new QPushButton(widget);
        btn_open->setObjectName("btn_open");

        gridLayout_2->addWidget(btn_open, 0, 1, 1, 1);

        btn_clear_tx = new QPushButton(widget);
        btn_clear_tx->setObjectName("btn_clear_tx");

        gridLayout_2->addWidget(btn_clear_tx, 2, 2, 1, 1);

        btn_send = new QPushButton(widget);
        btn_send->setObjectName("btn_send");

        gridLayout_2->addWidget(btn_send, 2, 1, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(280, 20, 143, 169));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        comboBox_Port = new QComboBox(groupBox);
        comboBox_Port->setObjectName("comboBox_Port");

        gridLayout->addWidget(comboBox_Port, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox_Baud = new QComboBox(groupBox);
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->addItem(QString());
        comboBox_Baud->setObjectName("comboBox_Baud");

        gridLayout->addWidget(comboBox_Baud, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboBox_Stop = new QComboBox(groupBox);
        comboBox_Stop->addItem(QString());
        comboBox_Stop->addItem(QString());
        comboBox_Stop->setObjectName("comboBox_Stop");

        gridLayout->addWidget(comboBox_Stop, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        comboBox_DataBit = new QComboBox(groupBox);
        comboBox_DataBit->addItem(QString());
        comboBox_DataBit->addItem(QString());
        comboBox_DataBit->addItem(QString());
        comboBox_DataBit->addItem(QString());
        comboBox_DataBit->setObjectName("comboBox_DataBit");

        gridLayout->addWidget(comboBox_DataBit, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        comboBox_Varity = new QComboBox(groupBox);
        comboBox_Varity->addItem(QString());
        comboBox_Varity->addItem(QString());
        comboBox_Varity->addItem(QString());
        comboBox_Varity->setObjectName("comboBox_Varity");

        gridLayout->addWidget(comboBox_Varity, 4, 1, 1, 1);

        text_tx = new QTextEdit(tab);
        text_tx->setObjectName("text_tx");
        text_tx->setGeometry(QRect(10, 240, 261, 61));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 10, 241, 141));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 10, 75, 23));
        pushButton_4 = new QPushButton(tab_3);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 70, 75, 41));
        pushButton_5 = new QPushButton(tab_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 40, 75, 23));
        widget_4 = new QWidget(tab_3);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(100, 10, 161, 101));
        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(0, 40, 161, 21));
        label_7 = new QLabel(widget_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 0, 21, 16));
        lineEditKey = new QLineEdit(widget_3);
        lineEditKey->setObjectName("lineEditKey");
        lineEditKey->setGeometry(QRect(40, 0, 113, 21));
        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 70, 161, 41));
        label_8 = new QLabel(widget_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 10, 16, 16));
        lineEditIv = new QLineEdit(widget_2);
        lineEditIv->setObjectName("lineEditIv");
        lineEditIv->setGeometry(QRect(40, 10, 113, 21));
        label_9 = new QLabel(widget_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 10, 53, 15));
        textFileInfo = new QTextBrowser(tab_3);
        textFileInfo->setObjectName("textFileInfo");
        textFileInfo->setGeometry(QRect(95, 130, 171, 71));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 120, 75, 23));
        tabWidget->addTab(tab_3, QString());
        widget_5 = new QWidget();
        widget_5->setObjectName("widget_5");
        pushButton_8 = new QPushButton(widget_5);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(20, 110, 75, 23));
        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(100, 110, 75, 23));
        comboBox_Port_2 = new QComboBox(widget_5);
        comboBox_Port_2->addItem(QString());
        comboBox_Port_2->addItem(QString());
        comboBox_Port_2->addItem(QString());
        comboBox_Port_2->addItem(QString());
        comboBox_Port_2->setObjectName("comboBox_Port_2");
        comboBox_Port_2->setGeometry(QRect(80, 10, 69, 21));
        label_10 = new QLabel(widget_5);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 10, 48, 21));
        label_11 = new QLabel(widget_5);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 40, 48, 21));
        lineEdit = new QLineEdit(widget_5);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(80, 40, 71, 21));
        label_12 = new QLabel(widget_5);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 70, 48, 21));
        lineEdit_2 = new QLineEdit(widget_5);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(80, 70, 71, 21));
        lineEdit_3 = new QLineEdit(widget_5);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(250, 10, 71, 21));
        label_13 = new QLabel(widget_5);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(190, 10, 31, 21));
        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(180, 110, 75, 23));
        label_14 = new QLabel(widget_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(190, 40, 41, 21));
        lineEdit_4 = new QLineEdit(widget_5);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(250, 40, 71, 21));
        label_15 = new QLabel(widget_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(190, 70, 51, 21));
        lineEdit_5 = new QLineEdit(widget_5);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(250, 70, 71, 21));
        tabWidget->addTab(widget_5, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget_6, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_2, 2, 1, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "PuttingblAide", nullptr));
        btn_clear_rx->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\346\216\245\346\224\266", nullptr));
        btn_open->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        btn_clear_tx->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\345\217\221\351\200\201", nullptr));
        btn_send->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\351\200\211\346\213\251", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_Baud->setItemText(0, QCoreApplication::translate("Widget", "9600", nullptr));
        comboBox_Baud->setItemText(1, QCoreApplication::translate("Widget", "115200", nullptr));
        comboBox_Baud->setItemText(2, QCoreApplication::translate("Widget", "256000", nullptr));
        comboBox_Baud->setItemText(3, QCoreApplication::translate("Widget", "460800", nullptr));
        comboBox_Baud->setItemText(4, QCoreApplication::translate("Widget", "921600", nullptr));
        comboBox_Baud->setItemText(5, QCoreApplication::translate("Widget", "2000000", nullptr));

        label_3->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215", nullptr));
        comboBox_Stop->setItemText(0, QCoreApplication::translate("Widget", "1", nullptr));
        comboBox_Stop->setItemText(1, QCoreApplication::translate("Widget", "2", nullptr));

        label_4->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215", nullptr));
        comboBox_DataBit->setItemText(0, QCoreApplication::translate("Widget", "8", nullptr));
        comboBox_DataBit->setItemText(1, QCoreApplication::translate("Widget", "7", nullptr));
        comboBox_DataBit->setItemText(2, QCoreApplication::translate("Widget", "6", nullptr));
        comboBox_DataBit->setItemText(3, QCoreApplication::translate("Widget", "5", nullptr));

        label_5->setText(QCoreApplication::translate("Widget", "\345\245\207\345\201\266\346\240\241\351\252\214", nullptr));
        comboBox_Varity->setItemText(0, QCoreApplication::translate("Widget", "\346\227\240", nullptr));
        comboBox_Varity->setItemText(1, QCoreApplication::translate("Widget", "\345\245\207", nullptr));
        comboBox_Varity->setItemText(2, QCoreApplication::translate("Widget", "\345\201\266", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Widget", "\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Widget", "\345\233\276\345\203\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\345\244\264\351\203\250\n"
"\344\277\241\346\201\257", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "aes\345\212\240\345\257\206", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "key", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "iv", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "AES \351\205\215\347\275\256", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\217\246\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\244\204\347\220\206", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\345\215\207\347\272\247", nullptr));
        comboBox_Port_2->setItemText(0, QCoreApplication::translate("Widget", "\344\270\262\345\217\243", nullptr));
        comboBox_Port_2->setItemText(1, QCoreApplication::translate("Widget", "\350\223\235\347\211\231", nullptr));
        comboBox_Port_2->setItemText(2, QCoreApplication::translate("Widget", "WiFi", nullptr));
        comboBox_Port_2->setItemText(3, QCoreApplication::translate("Widget", "USB-HID", nullptr));

        label_10->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245\346\226\271\345\274\217", nullptr));
        label_11->setText(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\345\220\215\347\247\260", nullptr));
        label_12->setText(QCoreApplication::translate("Widget", "\346\226\207\344\273\266\347\211\210\346\234\254", nullptr));
        label_13->setText(QCoreApplication::translate("Widget", "\345\215\217\350\256\256", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\345\244\215\344\275\215", nullptr));
        label_14->setText(QCoreApplication::translate("Widget", "\345\270\247\345\244\247\345\260\217", nullptr));
        label_15->setText(QCoreApplication::translate("Widget", "\346\240\241\351\252\214\346\226\271\345\274\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget_5), QCoreApplication::translate("Widget", "IAP\345\215\207\347\272\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
