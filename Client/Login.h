// Copyright 2025 Sgly
#ifndef D__IM_CLIENT_IM_CLIENT_DIALOG_H_
#define D__IM_CLIENT_IM_CLIENT_DIALOG_H_
#include"register.h"
#include <QDialog>
#include"ClientSocket.h"
#include<QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QDialog {
    Q_OBJECT

 public:
    explicit Login(QDialog *parent = nullptr);
    ~Login();
 public slots:
    void sendMessage();
    void goRegister();
 private:
     Ui::Login* ui;
     ClientSocket* client_socket;
     Register* register_window;
};
#endif  //  D__IM_CLIENT_IM_CLIENT_DIALOG_H_
