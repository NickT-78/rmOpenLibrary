import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Phase 2a target. Bound to SettingsController (C++) via context property
// `settingsController`. No animations (e-paper refresh cost).
Page {
    id: root
    title: qsTr("Paramètres")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        GroupBox {
            title: qsTr("Compte OpenLibrary")
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                TextField {
                    placeholderText: qsTr("Nom d'utilisateur")
                    text: settingsController.username
                    onEditingFinished: settingsController.username = text
                }
                Button {
                    text: settingsController.loggedIn ? qsTr("Déconnexion") : qsTr("Connexion")
                    onClicked: settingsController.loggedIn
                        ? settingsController.logout()
                        : settingsController.login()
                }
            }
        }

        GroupBox {
            title: qsTr("Connexion API")
            Layout.fillWidth: true
            TextField {
                Layout.fillWidth: true
                placeholderText: qsTr("URL de base (défaut: openlibrary.org)")
                text: settingsController.apiBaseUrl
                onEditingFinished: settingsController.apiBaseUrl = text
            }
        }

        GroupBox {
            title: qsTr("Stockage")
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                TextField {
                    Layout.fillWidth: true
                    placeholderText: qsTr("Dossier de destination")
                    text: settingsController.destinationFolder
                    onEditingFinished: settingsController.destinationFolder = text
                }
                RowLayout {
                    Label { text: qsTr("Taille du cache (MB)") }
                    Slider {
                        from: 32; to: 1024; stepSize: 32
                        value: settingsController.cacheSizeMb
                        onValueChanged: settingsController.cacheSizeMb = value
                    }
                    Label { text: settingsController.cacheSizeMb.toFixed(0) }
                }
            }
        }
    }
}
