#include "JsonSettingsStore.hpp"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace rmol::data {

using rmol::domain::AppSettings;

JsonSettingsStore::JsonSettingsStore(QString path) : m_path(std::move(path)) {
    if (m_path.isEmpty()) m_path = resolvePath();
}

QString JsonSettingsStore::resolvePath() const {
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/settings.json";
}

AppSettings JsonSettingsStore::load() {
    AppSettings s; // defaults from struct
    QFile f(m_path);
    if (!f.open(QIODevice::ReadOnly)) return s;

    const auto doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isObject()) return s;
    const auto obj = doc.object();

    if (obj.contains("username")) s.username = obj["username"].toString();
    if (obj.contains("apiBaseUrl")) s.apiBaseUrl = obj["apiBaseUrl"].toString();
    if (obj.contains("destinationFolder")) s.destinationFolder = obj["destinationFolder"].toString();
    if (obj.contains("cacheSizeMb")) s.cacheSizeMb = obj["cacheSizeMb"].toInt();
    return s;
}

void JsonSettingsStore::save(const AppSettings& s) {
    QJsonObject obj;
    obj["username"] = s.username;
    obj["apiBaseUrl"] = s.apiBaseUrl;
    obj["destinationFolder"] = s.destinationFolder;
    obj["cacheSizeMb"] = s.cacheSizeMb;

    QFile f(m_path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    f.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

} // namespace rmol::data
