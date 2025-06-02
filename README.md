# WakeOnLAN

WakeOnLAN is a C++ tool to remotely power on a PC using the Wake-on-LAN (WOL) protocol. It sends a magic packet containing the target PC’s MAC address over UDP, with error handling for invalid inputs or network issues. Built for beginners, it demonstrates network programming and basic C++ concepts. The target PC must have WOL enabled in its BIOS and network settings.

## Features
- Sends WOL magic packet to wake a PC
- Validates MAC address input
- Provides clear error messages
- Uses UDP for network communication

## Requirements
- C++ compiler (e.g., g++)
- Linux/Unix-based system (for socket programming)

## Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/AsifMinar/WakeOnLAN.git
   ```
2. Ensure `wol.cpp` is in the project directory.
3. Compile the program:
   ```bash
   g++ -o wol wol.cpp
   ```

## Usage
Run the program (may require sudo for network permissions):
```bash
sudo ./wol
```
Enter the target PC’s MAC address (e.g., `00:11:22:33:44:55`) when prompted.

Example:
```
Enter MAC address (example: 00:11:22:33:44:55): 00:11:22:33:44:55
Magic packet sent successfully!
```

## Testing
- Ensure the target PC has WOL enabled.
- Run the program on the same network as the target PC.
- Enter a valid MAC address and check if the PC powers on.
- Test with invalid MAC addresses to see error handling.

## Limitations
- Supports IPv4 broadcast (`255.255.255.255`) on port 9.
- Requires root privileges on some systems for broadcasting.
- Assumes ASCII input for MAC addresses.