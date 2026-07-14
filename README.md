# rmOpenLibrary

Client OpenLibrary natif pour reMarkable Paper Pro (`ferrari`). Recherche
de livres, tri/filtres, consultation hors-ligne via cache local.

- Licence: LGPL-3.0
- Cible: reMarkable Paper Pro (OS 4.0.813+, Qt Quick/QML, C++17)
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

```bash
source /path/to/sdk/environment-setup-cortexa53-crypto-remarkable-linux
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$OECORE_NATIVE_SYSROOT/usr/share/cmake/OEToolchainConfig.cmake ..
make -j$(nproc)
```

## Déploiement

```bash
./deploy/deploy.sh <device-ip>
```
