/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *gram3;
    QPlainTextEdit *gram3in;
    QLabel *cpp;
    QPlainTextEdit *cppin;
    QPlainTextEdit *tokenout;
    QLabel *token;
    QPushButton *start;
    QLabel *gram2;
    QLabel *trans;
    QPlainTextEdit *gram2in;
    QPlainTextEdit *transout;
    QPushButton *close;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gram3 = new QLabel(centralWidget);
        gram3->setObjectName(QStringLiteral("gram3"));
        gram3->setGeometry(QRect(80, 50, 111, 16));
        gram3in = new QPlainTextEdit(centralWidget);
        gram3in->setObjectName(QStringLiteral("gram3in"));
        gram3in->setGeometry(QRect(80, 70, 301, 111));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        gram3in->setFont(font);
        cpp = new QLabel(centralWidget);
        cpp->setObjectName(QStringLiteral("cpp"));
        cpp->setGeometry(QRect(80, 370, 111, 16));
        cppin = new QPlainTextEdit(centralWidget);
        cppin->setObjectName(QStringLiteral("cppin"));
        cppin->setGeometry(QRect(80, 390, 301, 111));
        cppin->setFont(font);
        tokenout = new QPlainTextEdit(centralWidget);
        tokenout->setObjectName(QStringLiteral("tokenout"));
        tokenout->setGeometry(QRect(420, 70, 301, 191));
        tokenout->setFont(font);
        token = new QLabel(centralWidget);
        token->setObjectName(QStringLiteral("token"));
        token->setGeometry(QRect(420, 50, 111, 16));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(190, 520, 80, 41));
        gram2 = new QLabel(centralWidget);
        gram2->setObjectName(QStringLiteral("gram2"));
        gram2->setGeometry(QRect(80, 210, 111, 16));
        trans = new QLabel(centralWidget);
        trans->setObjectName(QStringLiteral("trans"));
        trans->setGeometry(QRect(420, 290, 111, 16));
        gram2in = new QPlainTextEdit(centralWidget);
        gram2in->setObjectName(QStringLiteral("gram2in"));
        gram2in->setGeometry(QRect(80, 230, 301, 111));
        gram2in->setFont(font);
        transout = new QPlainTextEdit(centralWidget);
        transout->setObjectName(QStringLiteral("transout"));
        transout->setGeometry(QRect(420, 310, 301, 191));
        transout->setFont(font);
        close = new QPushButton(centralWidget);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(530, 520, 80, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(close, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\256\200\346\230\223\347\274\226\350\257\221\345\231\250", nullptr));
        gram3->setText(QApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220\346\255\243\350\247\204\346\226\207\346\263\225", nullptr));
        cpp->setText(QApplication::translate("MainWindow", "\345\210\206\346\236\220\346\272\220\347\240\201", nullptr));
        token->setText(QApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
        start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\210\206\346\236\220", nullptr));
        gram2->setText(QApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220\344\272\214\345\236\213\346\226\207\346\263\225", nullptr));
        trans->setText(QApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
        close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\347\252\227\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
