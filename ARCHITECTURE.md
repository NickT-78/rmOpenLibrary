# Architecture — rmOpenLibrary

Cible: reMarkable Paper Pro (`ferrari`), SDK `5.7.119`, sysroot
`cortexa53-crypto-remarkable-linux`, **Qt 6.8.2** (confirmé empiriquement,
cf ADR-002 — pas Qt5 comme supposé initialement en Phase 1).

## Couches (n-tiers)

```
ui/       QML (Qt Quick 6, imports non-versionnés) — Settings, Search, Result list. Aucune logique métier.
domain/   C++ — modèles (Book, SearchQuery, Session), services
          (SearchService, AuthService, CacheService), interfaces (ports).
data/     C++ — implémentations concrètes: HttpClient (curl/QNetworkAccessManager),
          SqliteCache, OpenLibraryRepository (impl. des ports domain/).
```

Règle de dépendance: `ui -> domain -> data` (jamais l'inverse).
`domain/` ne connaît QNetwork/Sqlite qu'via interfaces abstraites
(injection de dépendance au démarrage, `main.cpp`).

## Composants clés

| Composant | Rôle |
|---|---|
| `NetworkMonitor` | Détecte online/offline (DBus NetworkManager), émet signal Qt |
| `OpenLibraryClient` | Rate-limit (1-3 req/s), User-Agent+email obligatoire, retry/backoff |
| `SqliteCache` | Cache résultats recherche + covers, TTL configurable, éviction LRU |
| `AuthService` | Login cookie, stockage chiffré (cf ADR-001) |
| `SettingsController` | Persistance JSON paramètres (compte, URL, dossier, cache size) |
| `SearchResultModel` | QAbstractListModel exposé au QML, tri/filtre côté domain |

## Build

CMake + `qt-cmake` wrapper du SDK Yocto (préférer `qt-cmake` à un
`CMAKE_TOOLCHAIN_FILE` manuel : il fixe automatiquement `Qt6_DIR`,
`CMAKE_PREFIX_PATH` et le sysroot). Cross-compilation uniquement
(host x86_64 -> target aarch64).

## Conformité

- OpenLibrary: `User-Agent: rmOpenLibrary/<version> (<contact-email>)`,
  cache systématique, pas de scraping HTML, pas de bulk.
- reMarkable: pas de modification système hors dev mode, désinstallation propre,
  respect du guide UI Qt Quick e-paper (refresh rate, contraste, pas d'animations
  continues).
