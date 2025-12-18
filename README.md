C-ThreadScan

A high-performance, multi-threaded TCP port scanner written in C. This project explores low-level networking, POSIX threads, and thread-safe console logging.
Features

    Parallel Scanning: Distributes port ranges across multiple threads using pthread.

    Thread Safety: Implements pthread_mutex_t to prevent race conditions during reporting.

    Nix-Native: Optimized for NixOS with a dedicated shell.nix.

    Socket Programming: Direct implementation of the TCP three-way handshake.

Installation and Building
1. Environment Setup

Option A: NixOS (Recommended) Load the GCC compiler, GNUMake, and Netcat via the provided shell:
Bash

nix-shell

Option B: Other Linux Distros (Ubuntu, Arch, Fedora, etc.) Ensure you have gcc and make installed via your package manager:
Bash

# Example for Ubuntu/Debian
sudo apt install build-essential

2. Compilation

Once your environment is ready, use the Makefile to link the pthread library and build the binary:
Bash

make

Usage

The scanner requires four arguments: Target IP, Start Port, End Port, and Thread Count.
Bash

./scanner <IP> <StartPort> <EndPort> <Threads>

Local Testing

To verify the scanner logic, open a listener in one terminal and scan it with another.

Terminal 1 (Listener):
Bash

\nc -l 777

Terminal 2 (Scanner):
Bash

./scanner 127.0.0.1 700 800 4

Technical Deep Dive
Thread Management

The program utilizes the Worker Pattern. It calculates a specific range of ports for each thread to ensure no port is scanned twice and CPU cycles are used efficiently across all available cores.
The Mutex Lock

To prevent "Interleaved Output"—where multiple threads attempt to write to the console simultaneously—the program uses a Mutual Exclusion (Mutex) object. This ensures the output remains legible and synchronized.
C

pthread_mutex_lock(&log_mutex);
printf("[+] Port %d is OPEN\n", port);
pthread_mutex_unlock(&log_mutex);

Requirements

    OS: Linux (NixOS, Arch, Ubuntu, etc.)

    Compiler: GCC or Clang

    Libraries: glibc with lpthread support.

Disclaimer

This tool is for educational and authorized testing purposes only. Do not use it on networks you do not own or have explicit permission to scan.
