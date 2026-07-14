# rmOpenLibrary

Client OpenLibrary natif pour reMarkable Paper Pro (`ferrari`). Recherche
de livres, tri/filtres, consultation hors-ligne via cache local.

- Licence: LGPL-3.0
- Cible: reMarkable Paper Pro (SDK ferrari 5.7.119, Qt 6.8.2 Quick/QML, C++17)
- Statut: Phase 1 — scaffolding

## Limitations connues

- Authentification OpenLibrary via cookie de session (pas d'OAuth public,
  voir `docs/ADR-001-auth.md`). L'endpoint de login n'est pas versionné
  officiellement : un changement côté OpenLibrary peut casser l'auth.
- Aucune action de téléchargement/emprunt côté client : l'app est un outil
  de recherche/consultation de métadonnées, conformément aux guidelines
  OpenLibrary (pas de backend bulk).

## Conformité

- OpenLibrary Usage Guidelines: `User-Agent` identifié + email de contact,
  cache systématique, rate-limit respecté (3 req/s max), pas de scraping.
- reMarkable: build via SDK Yocto officiel, nécessite Developer Mode,
  désinstallation propre, pas de modification système persistante.

## Structure

Voir `ARCHITECTURE.md`.

## Build

Cible: Qt 6.8.2 (SDK `ferrari/5.7.119`). Qt5 n'existe pas sur ce SDK.

```bash
source /opt/codex/ferrari/5.7.119/environment-setup-cortexa53-crypto-remarkable-linux
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake \
      -DCMAKE_PREFIX_PATH=$OECORE_TARGET_SYSROOT/usr/lib/cmake \
      -DQt6_DIR=$OECORE_TARGET_SYSROOT/usr/lib/cmake/Qt6 \
      ..
make -j$(nproc)
```

Si `Qt6Config.cmake` reste introuvable malgré `libQt6Core.so` présent : le SDK
ne fournit que le runtime, pas les dev-cmake-configs. Vérifier
`find $OECORE_TARGET_SYSROOT -iname "qt-cmake*"` — s'il existe, l'utiliser
directement en remplacement de `cmake` (il pré-configure `CMAKE_PREFIX_PATH`).

## Déploiement

```bash
./deploy/deploy.sh <device-ip>
```
