// Copyright 2025 Sgly
#include "ClientSocket.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QMessageBox>
ClientSocket::ClientSocket(QObject* parent)
    : QObject(parent), m_tcpSocket(std::make_unique<QTcpSocket>(this))
    , m_initTimer(std::make_unique<QTimer>(this)) {
    initClientTcp();
}

ClientSocket::~ClientSocket()
{
    m_tcpSocket.get()->close();
}

void ClientSocket::initClientTcp() {
    // m_TcpSocket = new QTcpSocket(this);
    // m_initTimer = new QTimer(this);
    m_initTimer->setInterval(5000);
    m_initTimer->start();
    connect(m_initTimer.get(),
            &QTimer::timeout,
            this,
            &ClientSocket::onInitTimeout);
    connect(m_tcpSocket.get(),
            &QTcpSocket::connected,
            this,
            &ClientSocket::onConnected);
    connect(m_tcpSocket.get(),
            &QTcpSocket::readyRead,
            this,
            &ClientSocket::onReadyread);
    connect(m_tcpSocket.get(),
            &QTcpSocket::errorOccurred,
            this,
            &ClientSocket::handleError);
    connect(m_tcpSocket.get(),
            &QTcpSocket::disconnected,
            this,
            &ClientSocket::handleDisconnected);
    m_tcpSocket->connectToHost("192.168.88.133", 8888);
}

void ClientSocket::sendMessage(const QJsonDocument message, quint8 msgType) {
    if (!m_tcpSocket || !m_tcpSocket->isOpen()) {
        qWarning() << "Socket not connected!";
        return;
    }

    QByteArray data = message.toJson(QJsonDocument::Compact);
    const int32_t dataLength = data.size();

    ProtocolHeader header{};
    header.magic = qToBigEndian<uint32_t>(0xDEADBEEF);
    header.type = msgType;
    header.version = 1;
    header.length = qToBigEndian<uint32_t>(dataLength);

    // 直接拼接 header 和 data，避免 QDataStream 对齐问题
    QByteArray packet(reinterpret_cast<char*>(&header), sizeof(header));
    packet.append(data);

    qint64 bytesWritten = m_tcpSocket->write(packet);
    if (bytesWritten != packet.size()) {
        qCritical() << "Failed to send packet:" << m_tcpSocket->errorString();
    }
}
void ClientSocket::onConnected() {
    m_initTimer->stop();
    QJsonObject obj;
    obj["operator"] = "Login"; // test Login
    obj["username"] = "admin"; // add account
    obj["password"] = "123456"; // add password
    QJsonDocument doc(obj);
    sendMessage(doc, 0);
}

void ClientSocket::onReadyread() {
    m_receiveBuffer.append(m_tcpSocket->readAll());

    while (m_receiveBuffer.size() >= sizeof(ProtocolHeader)) {
        // int32_t networkLength;
        ProtocolHeader header;
        std::memcpy(&header, m_receiveBuffer.constData(), sizeof(ProtocolHeader));
        quint32 expectedLength  = qToBigEndian(header.length);
        if (m_receiveBuffer.size() < sizeof(ProtocolHeader) + expectedLength) {
            break;
        }
        QByteArray payload = m_receiveBuffer.mid(sizeof(ProtocolHeader), expectedLength);
        processPayload(payload);
        m_receiveBuffer.remove(0, sizeof(ProtocolHeader) + expectedLength);

    }
}

void ClientSocket::handleError(QAbstractSocket::SocketError socketError) {
    SocketErrors appError = SocketErrors::UnknownError;

    switch(socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        appError = SocketErrors::ConnectionClosed;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        appError = SocketErrors::ConnectionRefused;
        break;
    case QAbstractSocket::NetworkError:  // 处理其他可能错误
    case QAbstractSocket::UnknownSocketError:
    default:
        appError = SocketErrors::UnknownError;
    }

    emit connectionError(mapSocketError(appError));
}
// 错误类型映射
QAbstractSocket::SocketError ClientSocket::mapSocketError(SocketErrors error) {
    switch(error) {
    case SocketErrors::ConnectionClosed:
        return QAbstractSocket::RemoteHostClosedError;
    case SocketErrors::ConnectionRefused:
        return QAbstractSocket::ConnectionRefusedError;
    default:
        return QAbstractSocket::UnknownSocketError;
    }
}


void ClientSocket::processPayload(const QByteArray& data) {
    QJsonParseError parseError;
    QJsonDocument response = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        emit dataReceived({}); // 发送空对象表示错误
        return;
    }

    if (!response.isObject()) {
        qWarning() << "Invalid JSON format: expected object";
        emit dataReceived({});
        return;
    }
    qDebug()<<response;
    emit dataReceived(response.object());
}
void ClientSocket::handleDisconnected() {
    m_initTimer->stop();
    qDebug() << "Server disconnected!";
}

void ClientSocket::onInitTimeout() {
    QMessageBox::information(nullptr, "提示", "服务器连接超时");
    // m_TcpSocket->abort();
}



