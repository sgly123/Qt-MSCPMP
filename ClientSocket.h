// Copyright 2025 Sgly
#ifndef D__IM_CLIENT_IM_CLIENT_CLIENTSOCKET_H_
#define D__IM_CLIENT_IM_CLIENT_CLIENTSOCKET_H_

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include<QTimer>
#include"Agreement.h"
#include <QtNetwork/QAbstractSocket>

using SocketError = QAbstractSocket::SocketError;

enum class SocketErrors {
    NoError = 0,
    ConnectionClosed,
    ConnectionRefused,
    UnknownError
};

class ClientSocket : public QObject {
    Q_OBJECT
 public:
    explicit ClientSocket(QObject* parent = nullptr);
     ~ClientSocket();
    void initClientTcp();
    void sendMessage(QJsonDocument message, quint8 msgType);
    void processPayload(const QByteArray& data);

 signals:
     void dataReceived(const QJsonObject& data);
     void connectionError(QAbstractSocket::SocketError error);

 private slots:
    void onConnected();
    void onReadyread();
    void handleError(QAbstractSocket::SocketError socketError);
    void handleDisconnected();
    void onInitTimeout();

 private:
    std::unique_ptr<QTcpSocket> m_tcpSocket;
    QByteArray m_receiveBuffer;
    std::unique_ptr<QTimer> m_initTimer;
    QAbstractSocket::SocketError mapSocketError(SocketErrors error);
};

#endif  // D__IM_CLIENT_IM_CLIENT_CLIENTSOCKET_H_
