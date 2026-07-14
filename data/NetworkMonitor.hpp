#pragma once
#include <QObject>

namespace rmol::data {

// Wraps NetworkManager DBus signals to expose connectivity state.
// Phase 3 will implement via QDBusConnection::systemBus() subscription
// to org.freedesktop.NetworkManager "StateChanged".
class NetworkMonitor : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool online READ isOnline NOTIFY onlineChanged)

public:
    explicit NetworkMonitor(QObject* parent = nullptr);
    bool isOnline() const { return m_online; }

signals:
    void onlineChanged(bool online);

private:
    bool m_online = false;
};

} // namespace rmol::data
