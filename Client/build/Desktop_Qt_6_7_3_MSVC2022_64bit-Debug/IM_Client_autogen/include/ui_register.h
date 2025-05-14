/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *username_label;
    QLabel *password_label;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *submit;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(800, 600);
        username_label = new QLabel(Register);
        username_label->setObjectName("username_label");
        username_label->setGeometry(QRect(180, 160, 69, 19));
        username_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        password_label = new QLabel(Register);
        password_label->setObjectName("password_label");
        password_label->setGeometry(QRect(180, 220, 69, 19));
        password_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        username = new QLineEdit(Register);
        username->setObjectName("username");
        username->setGeometry(QRect(280, 150, 241, 41));
        password = new QLineEdit(Register);
        password->setObjectName("password");
        password->setGeometry(QRect(280, 210, 241, 41));
        submit = new QPushButton(Register);
        submit->setObjectName("submit");
        submit->setGeometry(QRect(330, 300, 92, 28));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        username_label->setText(QCoreApplication::translate("Register", "\347\224\250\346\210\267\345\220\215", nullptr));
        password_label->setText(QCoreApplication::translate("Register", "\345\257\206\347\240\201", nullptr));
        submit->setText(QCoreApplication::translate("Register", "submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
