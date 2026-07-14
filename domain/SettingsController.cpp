#include "SettingsController.hpp"

namespace rmol::domain {

SettingsController::SettingsController(std::shared_ptr<ISettingsStore> store,
                                         std::shared_ptr<IAuthService> auth,
                                         QObject* parent)
    : QObject(parent), m_store(std::move(store)), m_auth(std::move(auth)) {
    m_settings = m_store->load();
    if (m_settings.username.isEmpty()) m_settings.username = "";
}

void SettingsController::setUsername(const QString& v) {
    if (m_settings.username == v) return;
    m_settings.username = v;
    persist();
    emit usernameChanged();
}

void SettingsController::setApiBaseUrl(const QString& v) {
    if (m_settings.apiBaseUrl == v) return;
    m_settings.apiBaseUrl = v;
    persist();
    emit apiBaseUrlChanged();
}

void SettingsController::setDestinationFolder(const QString& v) {
    if (m_settings.destinationFolder == v) return;
    m_settings.destinationFolder = v;
    persist();
    emit destinationFolderChanged();
}

void SettingsController::setCacheSizeMb(int v) {
    if (m_settings.cacheSizeMb == v) return;
    m_settings.cacheSizeMb = v;
    persist();
    emit cacheSizeMbChanged();
}

void SettingsController::login(const QString& password) {
    m_auth->login(m_settings.username, password, [this](AuthResult r) {
        switch (r) {
            case AuthResult::Success:
                emit loggedInChanged();
                break;
            case AuthResult::InvalidCredentials:
                emit loginFailed(tr("Identifiants invalides"));
                break;
            case AuthResult::NetworkUnavailable:
                emit loginFailed(tr("Hors ligne : réessaie une fois connecté"));
                break;
            case AuthResult::NotImplemented:
                emit loginFailed(tr("Authentification pas encore disponible (Phase 3)"));
                break;
        }
    });
}

void SettingsController::logout() {
    m_auth->logout();
    emit loggedInChanged();
}

void SettingsController::persist() {
    m_store->save(m_settings);
}

} // namespace rmol::domain
