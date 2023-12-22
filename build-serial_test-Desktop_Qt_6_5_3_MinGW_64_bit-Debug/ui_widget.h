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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *text_tx;
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
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QPushButton *btn_clear_rx;
    QPushButton *btn_open;
    QPushButton *btn_clear_tx;
    QPushButton *btn_send;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTextBrowser *text_rx;
    QWidget *tab_2;
    QLabel *label_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(440, 550);
        text_tx = new QTextEdit(Widget);
        text_tx->setObjectName("text_tx");
        text_tx->setGeometry(QRect(10, 200, 261, 71));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(280, 0, 143, 169));
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

        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(270, 200, 174, 72));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        btn_clear_rx = new QPushButton(widget);
        btn_clear_rx->setObjectName("btn_clear_rx");

        gridLayout_2->addWidget(btn_clear_rx, 0, 0, 1, 1);

        btn_open = new QPushButton(widget);
        btn_open->setObjectName("btn_open");

        gridLayout_2->addWidget(btn_open, 0, 1, 1, 1);

        btn_clear_tx = new QPushButton(widget);
        btn_clear_tx->setObjectName("btn_clear_tx");

        gridLayout_2->addWidget(btn_clear_tx, 1, 0, 1, 1);

        btn_send = new QPushButton(widget);
        btn_send->setObjectName("btn_send");

        gridLayout_2->addWidget(btn_send, 1, 1, 1, 1);

        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 280, 191));
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName("verticalLayout");
        text_rx = new QTextBrowser(tab);
        text_rx->setObjectName("text_rx");

        verticalLayout->addWidget(text_rx);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 10, 241, 141));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
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

        btn_clear_rx->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\346\216\245\346\224\266", nullptr));
        btn_open->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        btn_clear_tx->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\345\217\221\351\200\201", nullptr));
        btn_send->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Widget", "\346\225\260\346\215\256", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Widget", "\345\233\276\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
