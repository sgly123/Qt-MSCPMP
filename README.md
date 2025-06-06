# **SafeMediLink：基于 Qt 的医疗安全通讯与患者管理平台**  
**版本号**：MVP 1.1（集成 WebRTC 视频通话 + 子系统拆分）  
**编制日期**：2025 年 05 月 10 日  

---

## **1. 引言**  
### **1.1 项目背景**  
- **行业需求**：医疗行业对远程诊疗、患者信息管理及数据隐私保护的需求激增，需构建符合 HIPAA/GDPR 法规的数字化平台。  
- **技术驱动**：基于 Qt 框架的跨平台能力、图形界面优势及网络通信模块，开发高效、稳定的医疗管理系统。  

### **1.2 项目目标**  
- **核心目标**：  
  - 实现患者信息的安全管理、医疗数据的实时通讯及医患交互的规范化。  
  - **新增目标**：集成 WebRTC 实现安全的视频通话功能，支持医生与患者的远程诊疗。  
- **次要目标**：  
  - 提供直观的用户界面，符合 ISO 13485 医疗设备软件安全认证要求。  
  - 支持 DICOM 图像共享与隐私保护机制。  

### **1.3 文档范围**  
本需求分析书涵盖系统功能需求、非功能需求、技术实现方案及用户角色定义，新增 **WebRTC 视频通话模块** 的设计与实现，并明确 **子系统拆分方案**。  

---

## **2. 综合描述**  
### **2.1 系统概述**  
- **系统名称**：基于 Qt 的医疗安全通讯与患者管理平台  
- **核心功能**：  
  - **患者信息管理**（录入、查询、更新、删除）  
  - **安全通讯**（加密消息、远程诊断交互）  
  - **医疗记录管理**（DICOM/PDF 存档与共享）  
  - **多角色权限控制**（管理员、医生、患者）  
  - **视频通话模块**（通过 WebRTC 实现医患远程诊疗）  

### **2.2 用户角色与权限**  
| **角色**   | **权限与功能**                                               |
| ---------- | ------------------------------------------------------------ |
| **管理员** | 管理用户权限、系统配置、数据备份与恢复；监控视频通话状态（如强制挂断）。 |
| **医生**   | 查看患者病历、发送加密消息、上传诊断报告、发起/接听 WebRTC 视频通话。 |
| **患者**   | 查看自身病历、发送咨询消息、预约医生、下载检查报告、接收视频通话请求。 |

---

## **3. 功能需求分析**  
### **3.1 系统登录与权限验证**  
- **功能描述**：用户通过账号密码登录，支持多因素认证（如短信验证码），根据角色分配操作权限（管理员 > 医生 > 患者）。  
- **Qt 实现**：  
  - 使用 `QSignal/Slot` 机制实现登录验证逻辑。  
  - 集成 OpenSSL 实现密码加密传输（TLS 1.3）。  

### **3.2 患者信息管理模块**  
- **功能描述**：录入患者基本信息（姓名、性别、年龄、病史等），支持模糊搜索、导出为 PDF/Excel。  
- **Qt 实现**：  
  - 使用 `QTableView` 和 `QSqlTableModel` 绑定 SQLite/MySQL 数据库。  
  - QML 实现跨平台界面布局。  

### **3.3 安全通讯模块**  
- **功能描述**：医患双方通过加密消息实时通讯（支持文本、图片、文件），消息内容自动存档并支持审计日志。  
- **Qt 实现**：  
  - 使用 `QTcpSocket/QUdpSocket` 实现底层通信。  
  - 基于 OpenSSL 的 TLS/SSL 协议加密数据传输。  

### **3.4 医疗记录管理模块**  
- **功能描述**：医生上传诊断报告、影像资料（如 DICOM 图像），患者查看历史记录，支持权限分级（仅医生可编辑）。  
- **Qt 实现**：  
  - 集成 DCMTK 库处理医学影像。  
  - 使用 `QJsonDocument` 解析/生成 JSON 格式的诊断报告。  

### **3.5 系统维护与监控模块**  
- **功能描述**：管理员监控系统运行状态（CPU、内存占用），数据备份与恢复（支持自动定时备份）。  
- **Qt 实现**：  
  - 使用 `QProcess` 调用系统命令获取资源信息。  
  - `QSqlDatabase` 实现数据库备份接口。  

### **3.6 视频通话模块（新增）**  
- **功能描述**：  
  - **发起/接听视频通话**：医生主动发起，患者接收请求。  
  - **多角色支持**：管理员可监控通话状态（如录制权限、强制挂断）。  
  - **通话记录存档**：将通话元数据（时间、参与方、持续时间）存储到数据库。  
- **Qt 实现**：  
  - 使用 `QWebEngineView` 嵌入 WebRTC 客户端页面（HTML5 + JavaScript）。  
  - 信令服务器通过 WebSocket 实现 SDP/ICE 交换，与 Qt 后端集成。  

---

## **4. 非功能需求分析**  
### **4.1 系统性能**  
- **响应时间**：登录验证 ≤ 1 秒，消息发送延迟 ≤ 500ms，视频通话延迟 ≤ 200ms。  
- **吞吐量**：支持至少 1000 个并发用户。  

### **4.2 安全性需求**  
- **数据加密**：  
  - 传输层：TLS 1.3 + WebRTC SRTP 加密。  
  - 存储层：AES-256 加密敏感数据。  
- **权限控制**：RBAC（基于角色的访问控制），支持细粒度权限分配。  

### **4.3 可扩展性**  
- **模块化设计**：使用 Qt 插件机制（`QPluginLoader`）支持功能扩展。  
- **第三方对接**：支持对接 HIS/PACS 系统。  

### **4.4 易用性**  
- **界面设计**：支持多语言（中文、英文），触摸屏优化（按钮尺寸 ≥ 1cm²）。  
- **跨平台支持**：Windows/Linux/macOS 兼容性测试。  

---

## **5. 数据定义**  
### **5.1 数据格式**  
#### **患者信息表**  
```cpp
struct Patient {
    QString id;           // 患者ID（唯一）
    QString name;         // 姓名
    int age;              // 年龄
    QString gender;       // 性别
    QString medicalHistory; // 病史
};
```

#### **视频通话记录表**  
```sql
CREATE TABLE VideoCalls (
    CallID TEXT PRIMARY KEY,
    DoctorID TEXT NOT NULL,
    PatientID TEXT NOT NULL,
    StartTime DATETIME,
    EndTime DATETIME,
    Duration INTEGER,
    FOREIGN KEY(DoctorID) REFERENCES Users(ID),
    FOREIGN KEY(PatientID) REFERENCES Patients(ID)
);
```

---

## **6. 技术实现方案**  
### **6.1 Qt 框架选型**  
- **UI 层**：QWidget + C++ 后端，支持动态主题切换。  
- **网络通信**：`QTcpServer/QTcpSocket` + OpenSSL，WebRTC 通过 `QWebEngineView` 嵌入。  
- **数据持久化**：`QSqlDatabase` + SQLite/MySQL。  

### **6.2 子系统拆分方案**  
| **子系统名称**       | **功能描述**                                                 | **技术实现建议**                                             |
| -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **患者管理子系统**   | 管理患者基本信息、病历、检查记录等。                         | 使用 Qt + SQLite/MySQL，支持加密存储（AES-256）。            |
| **权限控制子系统**   | 实现 RBAC（基于角色的访问控制），管理医生、患者、管理员的权限。 | 集成 OpenSSL 实现 TLS/SSL 认证，与 Qt 登录模块联动。         |
| **安全通讯子系统**   | 加密消息传输、文件共享（支持 DICOM 图像）。                  | QTcpSocket + OpenSSL 加密，支持离线消息缓存。                |
| **视频通话子系统**   | 基于 WebRTC 的实时音视频交互，支持多角色权限控制。           | Qt WebEngine 嵌入 WebRTC 页面，信令服务器使用 WebSocket（WebSocketpp）。 |
| **数据存储子系统**   | 统一管理数据库（患者信息、通话记录、日志等），支持备份与恢复。 | Qt SQL 模块 + MySQL，定期自动备份（QTimer + QProcess）。     |
| **审计日志子系统**   | 记录所有操作日志（如登录、数据修改、通话记录），支持合规性审计。 | 使用 SQLite 存储日志，定期导出为 PDF/Excel。                 |
| **DICOM 共享子系统** | 支持医学影像的上传、解析与共享（与视频通话模块联动）。       | 集成 DCMTK 库，通过 WebRTC 数据通道传输 DICOM 文件。         |

---

## **7. 开发计划**  
| **阶段**           | **时间**   | **交付物**                                                   |
| ------------------ | ---------- | ------------------------------------------------------------ |
| **需求分析**       | 2025.05    | 补充 WebRTC 功能需求文档，定义视频通话场景（如预约、实时交互）。 |
| **技术调研**       | 2025.06    | 完成 WebRTC 集成方案设计（Qt WebEngine vs 原生 C++），选择信令服务器框架。 |
| **核心模块开发**   | 2025.07-08 | 实现 WebRTC 视频通话模块，完成与 Qt 登录、权限控制模块的集成。 |
| **测试与优化**     | 2025.09    | 测试跨平台兼容性（Windows/Linux/macOS），优化视频延迟和安全性。 |
| **文档与答辩准备** | 2025.10    | 编写毕业设计论文，制作实习作品集（GitHub 仓库、演示视频、技术博客）。 |

---

## **8. 项目亮点**  
1. **跨平台能力**：Qt 与 WebRTC 结合，支持 Windows/Linux/macOS。  
2. **安全性**：TLS/SSL + SRTP 加密，符合 HIPAA/GDPR 法规。  
3. **模块化设计**：WebRTC 模块与现有系统解耦，便于扩展。  
4. **医疗场景定制**：支持 DICOM 图像共享、低带宽自适应、隐私保护。  

---

## **9. 附录**  
### **术语表**  
- **DICOM**：医学数字成像与通信标准。  
- **RBAC**：基于角色的访问控制模型。  

### **参考文献**  
- [Qt 官方文档](https://doc.qt.io/)  
- [ISO 13485 医疗器械质量管理体系标准](https://www.iso.org/)  
- [WebRTC 官方文档](https://webrtc.org/)  

---

### **优化说明**  
1. **WebRTC 集成**：新增视频通话模块的功能描述、技术实现和数据定义。  
2. **子系统拆分**：明确划分子系统，突出模块化设计的优势。  
3. **实习申请亮点**：突出跨平台开发、安全性设计、医疗场景适配。  
4. **毕业设计创新点**：强调 DICOM 共享、隐私保护、模块化设计。  
5. **格式调整**：使用清晰的标题层级、代码块和表格，提升可读性。  

希望这份文档能帮助你更好地展示项目价值！如果需要进一步调整，请随时告知。
