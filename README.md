# perf-lab

Low-latency performance playground for embedded-oriented C experiments.

This repository currently focuses on allocator prototypes and benchmark-style test binaries, while keeping a full roadmap toward a Cortex-M + FreeRTOS event pipeline.

## Table of Contents

1. [Project Vision](#project-vision)
2. [Repository Structure](#repository-structure)
3. [Current Repository State](#current-repository-state)
4. [Quick Start](#quick-start)
5. [Build Output](#build-output)
6. [Target Architecture (Roadmap)](#target-architecture-roadmap)
7. [Full Technical Specification (Semantic Part)](#full-technical-specification-semantic-part)
8. [Acceptance Criteria](#acceptance-criteria)
9. [Extensions](#extensions)

## Project Vision

Build a demonstration prototype of a deterministic real-time event engine for resource-constrained embedded systems (ARM Cortex-M + FreeRTOS), with strict latency goals:

- Lock-free critical path
- Tail latency target: `p99 < 10 us`
- No runtime `malloc` in production data path
- Optional telemetry export over UART / UDP

## Repository Structure

```
perf-lab/
├── cmake/                          # Reusable CMake modules
│   ├── TargetHostSim.cmake         # Host simulation target config
│   ├── TargetRP2040.cmake          # Raspberry Pi Pico target config
│   ├── TargetRenodeSTM32.cmake     # Renode STM32F4 target config
│   ├── TargetMyRTOS.cmake          # Custom RTOS target config
│   ├── FreeRTOSHelpers.cmake       # FreeRTOS integration helpers
│   ├── Sanitizers.cmake            # Sanitizer configuration
│   └── CompilerWarnings.cmake      # Warning flags
├── docs/                           # Documentation
│   ├── architecture.txt            # Project architecture overview
│   └── my-rtos.md                  # Custom RTOS documentation
├── external/                       # Git submodules (FreeRTOS, pico-sdk, lwip)
├── img/                            # Build artifacts (.bin, .uf2, .elf files)
├── scripts/                        # Build and utility scripts
│   ├── build.sh                    # Main build script
│   ├── clean.sh                    # Clean build artifacts
│   ├── sim-posix.sh                # POSIX simulator runner
│   ├── renode-run.sh               # Renode emulator runner
│   ├── pico-flash.sh               # Pico flashing script
│   └── plot-latency.py             # Latency plotting utility
├── src/                            # Source code
│   ├── app/                        # Application entry points
│   ├── drivers/                    # Hardware drivers
│   ├── middleware/                 # Middleware components
│   └── shared/                     # Shared libraries and utilities
│       ├── include/                # Public headers
│       └── libs/                   # Library implementations
├── targets/                        # Target-specific configurations
│   ├── host-sim/                   # POSIX FreeRTOS simulation
│   ├── rp2040-pico/                # Raspberry Pi Pico
│   ├── renode-stm32f4/             # Renode STM32F4 emulation
│   └── my-rtos/                    # Custom RTOS implementation
├── tests/                          # Unit and integration tests
│   ├── cash_bench/                 # Benchmark tests
│   └── sandbox/                    # Development sandbox
├── CMakeLists.txt                  # Root CMake configuration
├── .clang-format                   # Code formatting rules
├── .gitignore                      # Git ignore patterns
└── README.md                       # This file
```

## Current Repository State

What exists now:

- Multi-target CMake-based C project (`C11`) supporting host, embedded, and simulation platforms
- Modular architecture with reusable CMake modules
- `perf-lab-lib` static library with shared utilities
- Allocator experiments in `src/shared/libs/allocator/`:
  - Fixed-size allocator
  - Variable-size allocator (in progress)
  - Buddy allocator skeleton
- Target-specific configurations in `targets/`:
  - Host POSIX simulation
  - Raspberry Pi Pico (RP2040)
  - Renode STM32F4 emulation
  - Custom RTOS implementation
- Test binaries in `tests/`:
  - `cash_bench/` - Performance benchmarks
  - `sandbox/` - Development experiments
- Build system: `scripts/build.sh` with multi-target support

Current code is a development sandbox and does not yet implement the full event-aggregator architecture described below.

## Quick Start

### Prerequisites

- CMake `>= 3.16`
- A C toolchain compatible with C11
- Bash (for build script)

### Build (recommended)

Build for host simulation (default):

```bash
./scripts/build.sh host --debug
```

Build for Raspberry Pi Pico:

```bash
./scripts/build.sh pico --debug
```

Build for Renode STM32F4 emulation:

```bash
./scripts/build.sh renode --debug
```

Build for custom RTOS:

```bash
./scripts/build.sh my-rtos --debug
```

Release build:

```bash
./scripts/build.sh host --release
```

Clean rebuild with custom parallelism:

```bash
./scripts/build.sh host --clean --release -j 8
```

### Supported Targets

- `host` - POSIX FreeRTOS simulator (default)
- `pico` - Raspberry Pi Pico / Pico 2 (RP2040/RP2350)
- `renode` - Renode + STM32F4 emulation
- `my-rtos` - Custom RTOS implementation

### Build (manual CMake)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DTARGET=host
cmake --build build
```

## Build Output

After `scripts/build.sh`, project executables are built in `build/bin/` and artifacts are copied to `img/`:

- `img/cash-bench.bin` - Benchmark test binary
- `img/sandbox.bin` - Development sandbox binary
- `img/perf-lab` - Host simulation executable
- `img/perf-lab.uf2` - Pico UF2 firmware (when building for pico)
- `img/perf-lab.elf` - STM32F4 ELF binary (when building for renode)

Executables can be run directly from `build/bin/` for host targets.

## Target Architecture (Roadmap)

### 1) Event Producers

- Hardware sources: timer ISR, GPIO interrupts
- Software sources: FreeRTOS periodic tasks
- Each event carries compact payload + `source_id`

### 2) Lock-Free Ring Buffer

- Static fixed-size buffer
- Atomic head/tail updates
- No mutex on critical path
- Initial model: `SPSC`, then optional `MPMC`

### 3) Consumer / Aggregator Task

- Dequeues events in FreeRTOS task context
- Aggregates counters and simple rolling stats
- Exposes data via UART and optional UDP

### 4) Measurement Module

- Hardware: GPIO toggle + oscilloscope pulse width
- Software: `DWT->CYCCNT` sample collection
- Report: min / avg / max / p99 latency

### 5) Optional Networking

- `lwIP` RAW API for minimal overhead
- Command-triggered UDP snapshots

## Full Technical Specification (Semantic Part)

### Technical Specification (TOR)

**Project Name:** Low-Latency Event Aggregator for Embedded Systems Based on ARM Cortex-M and FreeRTOS

## 1. Project Goal

Develop a demonstration prototype of a real-time event collection, processing, and transmission engine for a resource-constrained embedded platform.

### Key Requirements

- Deterministic processing of events from multiple sources (sensors/interrupts)
- Lock-free design in the critical path
- Tail-latency minimization (**p99 < 10 us**)
- No dynamic memory allocation (`malloc`) during runtime
- Multitasking support via **FreeRTOS**
- Ability to transmit aggregated data over a network (UDP/TCP) for real-world demonstration

## 2. Platform and Toolchain

### Hardware

- **Microcontroller:** Any board based on ARM Cortex-M4 or M7  
  Examples:
  - STM32F407 Discovery
  - STM32F746G Discovery
- Minimum requirements:
  - >= 168 MHz CPU frequency
  - >= 128 KB RAM

### Peripherals

- GPIO (test signal generation)
- I2C/SPI (optional real sensors)
- UART (debugging and statistics output)
- Ethernet (optional, if available)

### Software

- IDE: STM32CubeIDE, System Workbench, or any GCC-based environment
- RTOS: **FreeRTOS** (latest stable version)
- Network stack (optional): **lwIP**
- Debugging: GDB + OpenOCD
- Static analysis: cppcheck

### Measurement Tools

- Oscilloscope or logic analyzer
- UART logging
- Internal timers (e.g., DWT cycle counter)

## 3. Architecture Overview

The system consists of the following components.

### 3.1 Event Generators (Producers)

**Hardware sources:**

- Timer interrupt (e.g., 10 kHz)
- External buttons (discrete event simulation)

**Software sources:**

- FreeRTOS tasks periodically generating test events

Each producer:

- Has a unique `source_id`
- Generates small payloads (8-16 bytes)

### 3.2 Lock-Free Ring Buffer

- Fixed-size array in static memory
- Atomic updates of read/write indices
- No mutexes or critical sections
- Initially supports **Single-Producer / Single-Consumer (SPSC)**
- Cache-line aligned to prevent false sharing (32/64 bytes)

### 3.3 Event Consumer

A FreeRTOS task that:

- Waits for new data (interrupt notification or polling)
- Performs lightweight aggregation:
  - Event counters per type
  - Moving averages
- Outputs results:
  - UART (debugging)
  - UDP packets (optional Ethernet)

### 3.4 Measurement Module

Latency measurement is performed as follows:

- GPIO pin toggled at:
  - Start of processing
  - End of processing
- Oscilloscope measures pulse width (processing latency)

Software measurement:

- Use DWT cycle counter (`DWT->CYCCNT`)
- Store samples
- Compute min / max / avg / p99
- Output statistics via UART

### 3.5 Optional Network Interface

If Ethernet is available:

- Implement a UDP server
- On command, transmit aggregated data to a specified IP
- Use **lwIP** RAW API (no sockets) to minimize overhead

## 4. Detailed Implementation

### 4.1 Data Structures

```c
// Ring buffer element
typedef struct {
    uint32_t timestamp;   // event timestamp (timer ticks)
    uint16_t source_id;   // event source
    uint16_t value;       // payload (e.g., ADC value)
} event_t;

#define BUFFER_SIZE 1024  // must be power of two

typedef struct {
    event_t data[BUFFER_SIZE];

    // Cache-line aligned pointers
    _Alignas(32) volatile uint32_t head;
    _Alignas(32) volatile uint32_t tail;
} lockfree_ring_t;
```

### 4.2 Atomic Operations (ARM Cortex-M)

```c
uint32_t read_head(void) {
    return __atomic_load_n(&ring.head, __ATOMIC_ACQUIRE);
}

void write_tail(uint32_t val) {
    __atomic_store_n(&ring.tail, val, __ATOMIC_RELEASE);
}

bool compare_exchange_head(uint32_t expected, uint32_t desired) {
    return __atomic_compare_exchange_n(
        &ring.head, &expected, desired,
        false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE
    );
}
```

### 4.3 Interrupts and Tasks

**Timer ISR:**

- Capture timestamp (DWT or TIM)
- Populate `event_t`
- Attempt non-blocking `enqueue()`
- If full, increment drop counter

**Consumer Task:**

- Priority slightly below interrupt
- Calls `dequeue()`
- Uses `xTaskNotifyFromISR()` to minimize latency

Example:

```c
void consumer_task(void *arg) {
    for (;;) {
        GPIOB->BSRR = LED_PIN;     // processing start

        event_t ev = dequeue();
        process_event(&ev);

        GPIOB->BRR = LED_PIN;      // processing end
    }
}
```

### 4.4 Latency Measurement

Two approaches:

**Hardware:**

- Measure GPIO pulse width via oscilloscope

**Software:**

- Read `DWT->CYCCNT`
- Store samples in static buffer
- Compute statistics on request

## 5. Topics to Study

### 5.1 Lock-Free Data Structures

- ABA problem
- CAS (Compare-And-Swap)
- Memory ordering (relaxed / acquire / release / seq_cst)
- SPSC vs MPMC ring buffers

### 5.2 ARM Cortex-M Architecture

- LDREX / STREX instructions
- NVIC interrupt priorities
- DWT cycle counter
- Cache alignment and false sharing

### 5.3 Latency and Profiling

- Embedded timing measurement techniques
- Tail latency (p99, p999)
- Impact of RTOS scheduler and interrupts on determinism

### 5.4 FreeRTOS

- `xTaskNotifyFromISR`
- Priority tuning
- Static memory allocation for:
  - Tasks
  - Queues
  - Stacks

### 5.5 Embedded Networking (Optional)

- **lwIP** RAW API
- RTOS integration
- UDP for low-latency transmission

### 5.6 Debugging Tools

- Logic analyzer (e.g., Saleae)
- GDB + OpenOCD
- Static code analysis

## Acceptance Criteria

- [ ] Lock-free ring buffer implemented and stress-tested
- [ ] Event generation rate >= 100,000 events/sec
- [ ] No event loss under normal load
- [ ] Aggregated statistics available via UART
- [ ] Measured latency:
  - [ ] Average < 5 us
  - [ ] p99 < 10 us
- [ ] README includes:
  - [ ] Architecture description
  - [ ] Measurement methodology
  - [ ] Latency graphs
  - [ ] Reproduction instructions

## Extensions

- Multi-producer support (CAS-based head updates)
- Compile-time configurable buffer size
- Real sensor integration (e.g., MPU6050 via I2C)
- Real-time Ethernet streaming
- Linux comparison implementation (sockets + pthread)
