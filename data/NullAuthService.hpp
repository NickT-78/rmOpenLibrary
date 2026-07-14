#pragma once
#include "../domain/IAuthService.hpp"

namespace rmol::data {

// Phase 2 placeholder. Real network login lands in Phase 3
// (OpenLibraryAuthService using OpenLibraryClient + encrypted cookie
// storage per ADR-001). Deliberately returns NotImplemented rather than
// faking success, so UI wiring is testable without lying about state.
class NullAuthService : public rmol::domain::IAuthService {
public:
    void login(const QString&, const QString&,
               std::function<void(rmol::domain::AuthResult)> onDone) override {
        onDone(rmol::domain::AuthResult::NotImplemented);
    }
    void logout() override { m_loggedIn = false; }
    bool isLoggedIn() const override { return m_loggedIn; }

private:
    bool m_loggedIn = false;
};

} // namespace rmol::data
