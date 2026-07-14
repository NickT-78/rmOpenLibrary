#pragma once
#include <QString>
#include <functional>

namespace rmol::domain {

enum class AuthResult { Success, InvalidCredentials, NetworkUnavailable, NotImplemented };

// Port: implemented by data/OpenLibraryAuthService (Phase 3 — needs
// OpenLibraryClient/NetworkMonitor). Phase 2a wires the UI contract only;
// data/NullAuthService below is the Phase-2 placeholder, explicit about
// what it doesn't do (no silent success).
class IAuthService {
public:
    virtual ~IAuthService() = default;
    virtual void login(const QString& username, const QString& password,
                        std::function<void(AuthResult)> onDone) = 0;
    virtual void logout() = 0;
    virtual bool isLoggedIn() const = 0;
};

} // namespace rmol::domain
