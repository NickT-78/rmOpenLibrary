# ADR-001: Authentification OpenLibrary

**Statut**: Accepté (2026-07-14)

## Contexte
OpenLibrary n'expose pas d'API OAuth/token publique. Seul un mécanisme
de login web basé sur cookie de session existe (`POST /account/login`,
domaine `openlibrary.org` / `archive.org` SSO partagé).

## Décision
- Auth = session cookie obtenue via `POST /account/login` (form-encoded:
  `username`, `password`, `redirect`).
- Cookie stocké chiffré (libsodium secretbox) dans
  `~/.local/share/rmOpenLibrary/session.enc`, clé dérivée du device ID RM.
- Aucune donnée de mot de passe persistée en clair, jamais loggée.
- Fonctionnalités nécessitant l'auth (listes de lecture, `mybooks` API) :
  dégradées gracieusement en mode "invité" si session absente/expirée.
- Renouvellement : re-login silencieux si cookie expiré et credentials
  en cache ; sinon reprompt UI.

## Conséquences
- Pas de refresh token standard -> gestion d'expiration ad hoc (session
  cookie TTL non documenté, à mesurer empiriquement en Phase 3).
- Dépendance à la stabilité du endpoint `/account/login` (non versionné
  officiellement) -> tests d'intégration doivent détecter un changement
  de comportement (breaking change monitoring).
- Documenté comme limitation connue dans README (transparence utilisateur
  open source).
