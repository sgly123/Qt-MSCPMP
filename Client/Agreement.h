// Copyright 2025 Sgly

#ifndef D__IM_CLIENT_IM_CLIENT_AGREEMENT_H_
#define D__IM_CLIENT_IM_CLIENT_AGREEMENT_H_

#include <QString>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

struct ProtocolHeader {
    uint32_t magic;    // 4字节
    uint8_t type;      // 1字节
    uint8_t version;   // 1字节
    uint32_t length;   // 4字节（网络字节序）
}__attribute__((packed));

#endif  // D__IM_CLIENT_IM_CLIENT_AGREEMENT_H_
