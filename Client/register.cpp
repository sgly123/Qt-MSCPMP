// Copyright 2025 Sgly
#include "register.h"
#include "ui_register.h"
#include "Login.h"
Register::Register(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Register) {
    ui->setupUi(this);
    //  connect(this, &Register::close_Register, this, &Register::back_login);
}

Register::~Register() {
    delete ui;
}

void Register::closeEvent(QCloseEvent *event)
{
    emit close_Register();
    event->accept();
}

//  void Register::back_login() {
//     Login* login_window = new Login();
//     login_window->show();
//  }
