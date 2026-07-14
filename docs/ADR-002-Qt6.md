# ADR-002: Qt6 au lieu de Qt5

**Statut**: Accepté (2026-07-14)

## Contexte
Phase 1 supposait Qt5 (base historique reMarkable 1/2). Le build réel sur
SDK `ferrari/5.7.119` échoue : `Qt5Config.cmake` absent. Inspection sysroot
confirme `libQt6Core.so.6.8.2` présent, aucune trace de Qt5.

## Décision
- Toutes les références Qt5 -> Qt6 (6.8.2) : `find_package(Qt6 ...)`,
  `Qt6::Core`/`Qt6::Quick`/etc en link.
- Imports QML : suppression des numéros de version (`import QtQuick 2.15`
  -> `import QtQuick`), forme dépréciée en Qt6.
- `QNetworkAccessManager`, `QAbstractListModel`, `QDBusConnection` : API
  inchangée entre Qt5/Qt6 pour les usages prévus, pas d'impact sur
  `domain/`/`data/` déjà écrits.

## Suivi
- Vérifier présence de `qt-cmake` (wrapper Qt6 qui pré-remplit
  `CMAKE_PREFIX_PATH`) sur le SDK — si absent, documenter le passage
  manuel de `Qt6_DIR`.
- Si `Qt6Config.cmake` reste introuvable malgré le runtime présent :
  SDK potentiellement livré sans dev-cmake-configs -> escalade vers
  support reMarkable developer (SDK incomplet).
