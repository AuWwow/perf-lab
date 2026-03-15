#!/usr/bin/env bash
set -euo pipefail

# ──────────────────────────────────────────────────────────────────────────────
# perf-lab build helper
# Supports: host-sim (POSIX FreeRTOS), rp2040-pico, renode-stm32f4, ...
# Usage examples:
#   ./scripts/build.sh host --release -j8 --clean
#   ./scripts/build.sh pico --release
#   ./scripts/build.sh renode --debug
# ──────────────────────────────────────────────────────────────────────────────

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

BUILD_DIR_BASE="${PROJECT_ROOT}/build"
IMG_DIR="${PROJECT_ROOT}/img"

TARGET="host"           # default
BUILD_TYPE="Debug"
CLEAN=0
JOBS=""

usage() {
    cat <<USAGE
Usage: $(basename "$0") <target> [options]

Targets:
  host       POSIX FreeRTOS simulator (default)
  pico       Raspberry Pi Pico / Pico 2 (RP2040/RP2350)
  renode     Renode + STM32F4 emulation
  my-rtos    Custom RTOS implementation

Options:
  --release        CMAKE_BUILD_TYPE=Release
  --debug          CMAKE_BUILD_TYPE=Debug (default)
  --clean          Remove build directory before configuring
  -j N / --jobs N  Number of parallel jobs
  -h / --help      Show this help
USAGE
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        host|pico|renode|my-rtos)
            TARGET="$1"
            ;;
        --release)
            BUILD_TYPE="Release"
            ;;
        --debug)
            BUILD_TYPE="Debug"
            ;;
        --clean)
            CLEAN=1
            ;;
        -j|--jobs)
            shift
            [[ $# -eq 0 || ! "$1" =~ ^[0-9]+$ ]] && { echo "Error: --jobs requires number" >&2; exit 1; }
            JOBS="$1"
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown argument: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
    shift
done

# ──────────────────────────────────────────────────────────────────────────────
# Prepare build directory per target + config
# ──────────────────────────────────────────────────────────────────────────────

BUILD_SUBDIR="${TARGET}-${BUILD_TYPE,,}"
BUILD_DIR="${BUILD_DIR_BASE}/${BUILD_SUBDIR}"

echo "→ Target       : ${TARGET}"
echo "→ Build type   : ${BUILD_TYPE}"
echo "→ Build dir    : ${BUILD_DIR}"
echo "→ Jobs         : ${JOBS:-$(nproc)}"

if [[ ${CLEAN} -eq 1 ]]; then
    echo "→ Cleaning ${BUILD_DIR}"
    rm -rf "${BUILD_DIR}"
fi

mkdir -p "${BUILD_DIR}"

# Common CMake arguments
CMAKE_ARGS=(
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
    -DTARGET="${TARGET}"
)

case "${TARGET}" in
    pico)
        [[ -d "${PROJECT_ROOT}/external/pico-sdk" ]] || {
            echo "Error: pico-sdk not found in external/pico-sdk" >&2
            echo "→ git submodule update --init --recursive" >&2
            exit 1
        }
        CMAKE_ARGS+=(
            -DPICO_SDK_PATH="${PROJECT_ROOT}/external/pico-sdk"
            -DPICO_TOOLCHAIN_PATH="${PROJECT_ROOT}/external/pico-sdk/toolchain"  # optional
        )
        ;;
    renode)
        # Можно добавить путь к Renode toolchain / STM32 HAL если нужно
        ;;
    host)
        # Для host можно включить санитайзеры, тесты и т.д.
        CMAKE_ARGS+=(-DENABLE_SANITIZERS=ON -DBUILD_TESTS=ON)
        ;;
esac

# Configure
echo "→ cmake configure ..."
cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" "${CMAKE_ARGS[@]}"

# Build
echo "→ Building ..."
if [[ -n "${JOBS}" ]]; then
    cmake --build "${BUILD_DIR}" -j"${JOBS}"
else
    cmake --build "${BUILD_DIR}"
fi

# Collect artifacts
mkdir -p "${IMG_DIR}"
find "${IMG_DIR}" -maxdepth 1 -type f -name '*.bin' -delete
find "${IMG_DIR}" -maxdepth 1 -type f -name '*.uf2' -delete  # для pico

mapfile -t BIN_FILES < <(find "${BUILD_DIR}" -type f \( -name '*.bin' -o -name '*.uf2' \) ! -path '*/CMakeFiles/*')

if [[ ${#BIN_FILES[@]} -eq 0 ]]; then
    echo "Warning: no .bin / .uf2 files found in build directory" >&2
else
    for f in "${BIN_FILES[@]}"; do
        cp -f -v "${f}" "${IMG_DIR}/"
    done
    echo "→ Copied ${#BIN_FILES[@]} artifact(s) to ${IMG_DIR}"
fi

echo "Done."
echo "  Artifacts → ${IMG_DIR}"
