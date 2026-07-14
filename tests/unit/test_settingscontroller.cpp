#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <memory>
#include "domain/SettingsController.hpp"
#include "data/JsonSettingsStore.hpp"
#include "data/NullAuthService.hpp"

using namespace rmol;

class TestSettingsController : public QObject {
    Q_OBJECT
private slots:
    void persistsUsernameAcrossReload() {
        QTemporaryDir dir;
        const QString path = dir.filePath("settings.json");

        {
            auto store = std::make_shared<data::JsonSettingsStore>(path);
            auto auth = std::make_shared<data::NullAuthService>();
            domain::SettingsController ctrl(store, auth);
            ctrl.setUsername("alice");
            ctrl.setCacheSizeMb(256);
        }
        {
            auto store = std::make_shared<data::JsonSettingsStore>(path);
            auto auth = std::make_shared<data::NullAuthService>();
            domain::SettingsController ctrl(store, auth);
            QCOMPARE(ctrl.username(), QString("alice"));
            QCOMPARE(ctrl.cacheSizeMb(), 256);
        }
    }

    void loginWithoutRealAuthServiceReportsNotImplemented() {
        QTemporaryDir dir;
        auto store = std::make_shared<data::JsonSettingsStore>(dir.filePath("s.json"));
        auto auth = std::make_shared<data::NullAuthService>();
        domain::SettingsController ctrl(store, auth);

        QSignalSpy failedSpy(&ctrl, &domain::SettingsController::loginFailed);
        ctrl.login("whatever");
        QCOMPARE(failedSpy.count(), 1);
        QVERIFY(!ctrl.loggedIn());
    }

    void defaultApiBaseUrlIsOpenLibrary() {
        QTemporaryDir dir;
        auto store = std::make_shared<data::JsonSettingsStore>(dir.filePath("s2.json"));
        auto auth = std::make_shared<data::NullAuthService>();
        domain::SettingsController ctrl(store, auth);
        QCOMPARE(ctrl.apiBaseUrl(), QString("https://openlibrary.org"));
    }
};

QTEST_MAIN(TestSettingsController)
#include "test_settingscontroller.moc"
