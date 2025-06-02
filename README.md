# WakeOnLAN

WakeOnLAN is a C++ tool to remotely power on a PC using the Wake-on-LAN (WOL) protocol. It sends a magic packet with the target PC’s MAC address over UDP, with error handling for invalid inputs or network issues. Built for beginners, it supports both Windows and Linux, demonstrating cross-platform network programming. The target PC must have WOL enabled in its BIOS and network settings.

## Features
- Sends WOL magic packet to wake a PC
- Validates MAC address input
- Provides clear error messages
- Cross-platform: Windows and Linux

## Requirements
- **Windows**: C++ compiler (e.g., MinGW, Visual Studio), Winsock library
- **Linux**: C++ compiler (e.g., g++)
- **Target PC**: WOL enabled, same local network

## Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/AsifMinar/WakeOnLAN.git
   ```
2. Ensure `wol.cpp` is in the project directory.

## Compilation
- **Windows** (MinGW):
  ```bash
  g++ -o wol wol.cpp -lws2_32
  ```
- **Linux**:
  ```bash
  g++ -o wol wol.cpp
  ```

## Usage
- **Windows**:
  ```bash
  wol.exe
  ```
  Run as Administrator if permission denied.
- **Linux**:
  ```bash
  sudo ./wol
  ```
Enter the target PC’s MAC address (e.g., `00:11:22:33:44:55`).

Example:
```
Enter MAC address (example: 00:11:22:33:44:55): 00:11:22:33:44:55
Magic packet sent successfully!
```

## Testing
- Ensure the target PC has WOL enabled.
- Run on the same network as the target PC.
- Enter a valid MAC address and verify the PC powers on.
- Test invalid MAC addresses for error handling.

## Limitations
- Uses IPv4 broadcast (`255.255.255.255`) on port 9.
- Linux may require `sudo`; Windows may need admin rights.
- Supports MAC format `XX:XX:XX:XX:XX:XX` only.