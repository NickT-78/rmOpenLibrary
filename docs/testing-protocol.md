# Protocole de tests — cross-compilation aarch64

Les binaires produits (`test_searchquery`, `test_settingscontroller`,
`rmOpenLibrary`) sont compilés pour `aarch64` (cible reMarkable). Ils ne
s'exécutent pas nativement sur un host x86_64.

## Option A — qemu-user (rapide, dev loop)

```bash
find $OECORE_NATIVE_SYSROOT -iname "qemu-aarch64*"
# si présent:
qemu-aarch64 -L $OECORE_TARGET_SYSROOT build/tests/test_settingscontroller
```
`ctest` peut être configuré pour utiliser ce wrapper via
`CMAKE_CROSSCOMPILING_EMULATOR` :
```bash
cmake -DCMAKE_CROSSCOMPILING_EMULATOR="qemu-aarch64;-L;$OECORE_TARGET_SYSROOT" ...
ctest --output-on-failure
```

## Option B — exécution on-device (fidélité maximale, Phase 4)

```bash
scp build/tests/test_settingscontroller root@10.11.99.1:/tmp/
ssh root@10.11.99.1 /tmp/test_settingscontroller
```
Requis pour valider tout ce qui touche DBus NetworkManager réel (Phase 3
`test_offline_fallback`), impossible à émuler fidèlement sous qemu-user.

## CI

GitHub Actions n'a pas le SDK Yocto reMarkable en runner standard —
Option A (qemu-user) est la seule viable en CI. Option B reste manuelle
avant chaque merge vers `main` (checklist Phase 4).
