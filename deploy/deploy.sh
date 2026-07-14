#!/usr/bin/env bash
# Phase 4 deployment protocol — reMarkable Paper Pro (ferrari), dev mode required.
set -euo pipefail

DEVICE_IP="${1:-10.11.99.1}"
BINARY="build/ui/rmOpenLibrary"
REMOTE_DIR="/home/root/rmOpenLibrary"

echo "[1/4] Checking device reachability..."
ssh "root@${DEVICE_IP}" "mkdir -p ${REMOTE_DIR}"

echo "[2/4] Copying binary + QML resources..."
scp "${BINARY}" "root@${DEVICE_IP}:${REMOTE_DIR}/"
scp -r ui/*.qml "root@${DEVICE_IP}:${REMOTE_DIR}/qml/"

echo "[3/4] Registering systemd unit (optional, if launcher integration needed)..."
# scp deploy/rmopenlibrary.service root@${DEVICE_IP}:/etc/systemd/system/

echo "[4/4] Smoke test..."
ssh "root@${DEVICE_IP}" "${REMOTE_DIR}/rmOpenLibrary --version"

echo "Deployed. Rollback: ssh root@${DEVICE_IP} rm -rf ${REMOTE_DIR}"
