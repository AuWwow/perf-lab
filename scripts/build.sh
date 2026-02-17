#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
IMG_DIR="${PROJECT_ROOT}/img"
BUILD_TYPE="Debug"
CLEAN=0

usage() {
    cat <<USAGE
Usage: $(basename "$0") [options]

Options:
  --release        Build with CMAKE_BUILD_TYPE=Release
  --debug          Build with CMAKE_BUILD_TYPE=Debug (default)
  --clean          Remove build directory before configuring
  -j, --jobs N     Number of parallel build jobs
  -h, --help       Show this help
USAGE
}

JOBS=""
while [[ $# -gt 0 ]]; do
    case "$1" in
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
            if [[ $# -eq 0 || ! "$1" =~ ^[0-9]+$ ]]; then
                echo "Error: --jobs requires a numeric value." >&2
                exit 1
            fi
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

if ! command -v cmake >/dev/null 2>&1; then
    echo "Error: cmake is not installed or not in PATH." >&2
    exit 1
fi

if [[ $CLEAN -eq 1 ]]; then
    rm -rf "${BUILD_DIR}"
fi

cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"

if [[ -n "${JOBS}" ]]; then
    cmake --build "${BUILD_DIR}" -- -j"${JOBS}"
else
    cmake --build "${BUILD_DIR}"
fi

mkdir -p "${IMG_DIR}"
find "${IMG_DIR}" -maxdepth 1 -type f -name '*.bin' -delete

mapfile -t BIN_FILES < <(find "${BUILD_DIR}" -type f -name '*.bin' ! -path '*/CMakeFiles/*')

if [[ ${#BIN_FILES[@]} -eq 0 ]]; then
    echo "No project .bin files found in ${BUILD_DIR}" >&2
    exit 1
fi

for bin_file in "${BIN_FILES[@]}"; do
    cp -f "${bin_file}" "${IMG_DIR}/"
done

echo "Collected ${#BIN_FILES[@]} .bin file(s) to ${IMG_DIR}"
