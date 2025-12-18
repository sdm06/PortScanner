
```
### C-ThreadScan

A high-performance, multi-threaded TCP port scanner written in C. This project explores low-level networking, POSIX threads, and thread-safe console logging.

###  Features
- **Parallel Scanning:** Distributes port ranges across multiple threads using `pthread`.
- **Thread Safety:** Implements `pthread_mutex_t` to prevent race conditions during reporting.
- **Nix-Native:** Optimized for **NixOS** with a dedicated `shell.nix`.
- **Socket Programming:** Direct implementation of the TCP three-way handshake.



---

###  Installation & Building

### Option 1(Using NixOS): Enter the Nix Shell
Load the GCC compiler, GNUMake, and Netcat for testing:
```bash
nix-shell

```
### Option 2: Other Linux Distros (Ubuntu, Arch, Fedora, etc.)

Ensure you have gcc and make installed via your package manager (e.g., sudo apt install build-essential). Then, simply compile:
Bash
```bash
make
```
### 2. Compile

Use the provided `Makefile` to link the `pthread` library and build the binary:

```bash
make

```

---

##  Usage

The scanner requires four arguments: Target IP, Start Port, End Port, and Thread Count.

```bash
./scanner <IP> <StartPort> <EndPort> <Threads>

```

### Local Testing

To verify the scanner logic, open a listener in one terminal and scan it with another:

**Terminal 1 (Listener):**

```bash
\nc -l 777

```

**Terminal 2 (Scanner):**

```bash
./scanner 127.0.0.1 700 800 4

```

---

##  Technical Deep Dive

### Thread Management

The program utilizes the **Worker Pattern**. It calculates the range of ports each thread is responsible for to ensure no port is scanned twice and no CPU cycle is wasted.

### The Mutex Lock

To prevent "Interleaved Output" (where multiple threads print to the screen at the exact same time, garbling the text), we use a Mutual Exclusion object:

```c
pthread_mutex_lock(&log_mutex);
printf("[+] Port %d is OPEN\n", port);
pthread_mutex_unlock(&log_mutex);

```

---

##  Requirements

* **OS:** Linux (NixOS, Arch, Ubuntu, etc.)
* **Compiler:** GCC or Clang
* **Libraries:** `glibc` with `lpthread` support.

## ⚠️ Disclaimer

This tool is for educational and authorized testing purposes only. Do not use it on networks you do not own or have explicit permission to scan.

```

