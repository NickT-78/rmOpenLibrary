#pragma once
#include <QObject>
#include <memory>
#include "ISettingsStore.hpp"
#include "IAuthService.hpp"

namespace rmol::domain {

class SettingsController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString apiBaseUrl READ apiBaseUrl WRITE setApiBaseUrl NOTIFY apiBaseUrlChanged)
    Q_PROPERTY(QString destinationFolder READ destinationFolder WRITE setDestinationFolder NOTIFY destinationFolderChanged)
    Q_PROPERTY(int cacheSizeMb READ cacheSizeMb WRITE setCacheSizeMb NOTIFY cacheSizeMbChanged)
    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged)

public:
    explicit SettingsController(std::shared_ptr<ISettingsStore> store,
                                  std::shared_ptr<IAuthService> auth,
                                  QObject* parent = nullptr);

    QString username() const { return m_settings.username; }
    void setUsername(const QString& v);

    QString apiBaseUrl() const { return m_settings.apiBaseUrl; }
    void setApiBaseUrl(const QString& v);

    QString destinationFolder() const { return m_settings.destinationFolder; }
    void setDestinationFolder(const QString& v);

    int cacheSizeMb() const { return m_settings.cacheSizeMb; }
    void setCacheSizeMb(int v);

    bool loggedIn() const { return m_auth->isLoggedIn(); }

    // Password never exposed as a Q_PROPERTY (avoid QML binding leaking
    // it into logs/inspectors). Invokable only, called from a dedicated
    // login dialog that discards the value immediately after the call.
    Q_INVOKABLE void login(const QString& password);
    Q_INVOKABLE void logout();

signals:
    void usernameChanged();
    void apiBaseUrlChanged();
    void destinationFolderChanged();
    void cacheSizeMbChanged();
    void loggedInChanged();
    void loginFailed(const QString& reason);

private:
    void persist();

    std::shared_ptr<ISettingsStore> m_store;
    std::shared_ptr<IAuthService> m_auth;
    AppSettings m_settings;
};

} // namespace rmol::domain
