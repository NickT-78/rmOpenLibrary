#pragma once
#include <QString>

namespace rmol::domain {

struct AppSettings {
    QString username;
    QString apiBaseUrl = "https://openlibrary.org";
    QString destinationFolder;
    int cacheSizeMb = 128;
};

// Port: implemented by data/JsonSettingsStore.
class ISettingsStore {
public:
    virtual ~ISettingsStore() = default;
    virtual AppSettings load() = 0;
    virtual void save(const AppSettings&) = 0;
};

} // namespace rmol::domain
