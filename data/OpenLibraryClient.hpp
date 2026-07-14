#pragma once
#include <QNetworkAccessManager>
#include <QString>
#include <QElapsedTimer>
#include <QQueue>

namespace rmol::data {

// Enforces OpenLibrary usage guidelines:
// - User-Agent: "rmOpenLibrary/<version> (<contact-email>)"
// - Rate limit: 3 req/s max when identified (default assumption; verified
//   empirically in Phase 3 integration tests against sandbox).
// - No bulk requests: search.json batches, never per-item loops >N.
class OpenLibraryClient : public QObject {
    Q_OBJECT
public:
    explicit OpenLibraryClient(QString baseUrl, QString contactEmail,
                                QObject* parent = nullptr);

    void get(const QString& path,
              std::function<void(QByteArray)> onSuccess,
              std::function<void(QString)> onError);

private:
    void enqueue(std::function<void()> request);
    void drainQueue();

    QNetworkAccessManager m_nam;
    QString m_baseUrl;
    QString m_userAgent;
    QQueue<std::function<void()>> m_queue;
    QElapsedTimer m_rateTimer;
    static constexpr double kMaxRequestsPerSecond = 3.0;
};

} // namespace rmol::data
