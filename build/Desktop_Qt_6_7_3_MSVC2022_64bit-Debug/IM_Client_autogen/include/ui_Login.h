/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *to_Register;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(800, 600);
        pushButton = new QPushButton(Login);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(360, 350, 92, 28));
        label = new QLabel(Login);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 180, 69, 19));
        label_2 = new QLabel(Login);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 270, 69, 19));
        lineEdit = new QLineEdit(Login);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(280, 170, 271, 41));
        lineEdit_2 = new QLineEdit(Login);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(280, 250, 271, 41));
        to_Register = new QPushButton(Login);
        to_Register->setObjectName("to_Register");
        to_Register->setGeometry(QRect(210, 350, 92, 28));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Login", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("Login", "username", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "password", nullptr));
        to_Register->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
