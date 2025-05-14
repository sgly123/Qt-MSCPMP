// Copyright 2025 Sgly
#include "Login.h"
#include "./ui_Login.h"
#include"ClientSocket.h"

Login::Login(QDialog *parent)
    : QDialog(parent)
    , client_socket(new ClientSocket(this))
    , ui(new Ui::Login)
    , register_window(new Register()){
    ui->setupUi(this);
    connect(ui->to_Register,
            &QPushButton::clicked,
            this,
            &Login::goRegister);
    connect(ui->pushButton,
            &QPushButton::clicked,
            this,
            &Login::sendMessage);
}
Login::~Login() {
    if(register_window){
        delete register_window;
    }
    delete ui;
}

void Login::sendMessage() {
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QJsonObject obj;
    obj["username"] = username;
    obj["password"] = password;
    obj["operator"] = "Login";
    QJsonDocument doc(obj);
    client_socket->sendMessage(doc, 0);
}

void Login::goRegister() {
    this->hide();
    register_window->show();
    connect(register_window,
            &Register::close_Register,
            this,
            &Login::show);
}
