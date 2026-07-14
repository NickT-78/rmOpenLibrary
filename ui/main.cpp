#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

#include "domain/SettingsController.hpp"
#include "data/JsonSettingsStore.hpp"
#include "data/NullAuthService.hpp"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName("rmOpenLibrary");
    app.setApplicationVersion("0.1.0");

    // DI wiring — data/ implementations injected behind domain/ ports.
    auto settingsStore = std::make_shared<rmol::data::JsonSettingsStore>();
    auto authService = std::make_shared<rmol::data::NullAuthService>();
    auto settingsController = std::make_shared<rmol::domain::SettingsController>(
        settingsStore, authService);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("settingsController", settingsController.get());

    const QUrl url(u"qrc:/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                      &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
