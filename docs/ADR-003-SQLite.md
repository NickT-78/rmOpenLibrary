# ADR-003: SqliteCache via libsqlite3 direct, pas QtSql

**Statut**: Proposé (2026-07-14) — à confirmer une fois `libsqlite3`/`sqlite3.h`
vérifiés présents sur le sysroot `ferrari/5.7.119`.

## Contexte
`find_package(Qt6 ... Sql)` échoue : `Qt6SqlConfig.cmake` absent du SDK,
bien que `Qt6Config.cmake` racine soit trouvé. L'image reMarkable minimale
n'embarque probablement pas le module QtSql (non utilisé par le launcher
système Codex/ferrari).

## Décision
- `data/SqliteCache` implémenté via l'API C `sqlite3.h` / `libsqlite3`
  directement (pas de wrapper Qt).
- Retrait de `Qt6::Sql` de `find_package`/`target_link_libraries`.
- Gain secondaire : moins d'allocations/couches d'abstraction pour un
  cache simple clé-valeur (TTL+LRU), conforme à l'objectif basse
  consommation du projet.

## Risque
- Si `libsqlite3.so`/`sqlite3.h` sont eux aussi absents du sysroot dev
  (à vérifier), fallback : embarquer sqlite3 en amalgamation source
  (`sqlite3.c` vendored, ~250KB compilé statiquement) — solution robuste
  indépendante du SDK.

## Suivi
- Confirmer présence `libsqlite3*`/`sqlite3.h` (résultat en attente).
- Si absent -> vendored sqlite3 amalgamation, mise à jour CMakeLists.
