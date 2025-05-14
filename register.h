// Copyright 2025 Sgly
#ifndef D__IM_CLIENT_IM_CLIENT_REGISTER_H
#define D__IM_CLIENT_IM_CLIENT_REGISTER_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class Register;
}

class Register : public QDialog {
    Q_OBJECT

 public:
    explicit Register(QDialog *parent = nullptr);
    ~Register();
 signals:
    void close_Register();
 public slots:
    // void back_login();
 private:
     Ui::Register *ui;
     void closeEvent(QCloseEvent* event) override;
};
#endif // D__IM_CLIENT_IM_CLIENT_REGISTER_H
