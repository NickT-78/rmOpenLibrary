import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 1620   // Paper Pro portrait resolution
    height: 2160
    title: qsTr("rmOpenLibrary")

    // E-Ink: no continuous animations, no transition easing curves.
    StackView {
        id: stack
        anchors.fill: parent
        initialItem: settingsPageComponent
        popEnter: Transition {}
        popExit: Transition {}
        pushEnter: Transition {}
        pushExit: Transition {}
    }

    Component {
        id: settingsPageComponent
        SettingsPage {}
    }
}
