#pragma once
#include <QString>
#include "../domain/ISettingsStore.hpp"

namespace rmol::data {

// Persists to $XDG_DATA_HOME/rmOpenLibrary/settings.json (fallback
// ~/.local/share/rmOpenLibrary/settings.json). No secrets stored here —
// credentials handled separately by AuthService (ADR-001, encrypted).
class JsonSettingsStore : public rmol::domain::ISettingsStore {
public:
    explicit JsonSettingsStore(QString path = {});

    rmol::domain::AppSettings load() override;
    void save(const rmol::domain::AppSettings&) override;

private:
    QString resolvePath() const;
    QString m_path;
};

} // namespace rmol::data
