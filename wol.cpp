#include <iostream>     // For input/output
#include <string>       // For handling strings
#include <vector>       // For storing bytes
#include <sys/socket.h> // For network sockets
#include <netinet/in.h> // For internet address structures
#include <arpa/inet.h>  // For converting IP addresses
#include <unistd.h>     // For close()
#include <cstring>      // For memset()

// Function to turn MAC address (like "00:11:22:33:44:55") into bytes
std::vector<unsigned char> parseMAC(const std::string& mac) {
    std::vector<unsigned char> bytes;
    size_t start = 0;
    size_t end = mac.find(':');
    int count = 0;

    // Split the string by ':' and convert each part to a byte
    while (end != std::string::npos && count < 5) {
        std::string byteStr = mac.substr(start, end - start);
        try {
            unsigned char byte = static_cast<unsigned char>(std::stoi(byteStr, nullptr, 16));
            bytes.push_back(byte);
        } catch (...) {
            return {}; // Return empty if conversion fails
        }
        start = end + 1;
        end = mac.find(':', start);
        count++;
    }

    // Check if we have exactly 5 colons
    if (count != 5) {
        return {};
    }

    // Get the last part
    std::string byteStr = mac.substr(start);
    try {
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteStr, nullptr, 16));
        bytes.push_back(byte);
    } catch (...) {
        return {};
    }

    // MAC address must be 6 bytes
    if (bytes.size() != 6) {
        return {};
    }

    return bytes;
}

// Function to build the magic packet
std::vector<unsigned char> createMagicPacket(const std::vector<unsigned char>& mac) {
    std::vector<unsigned char> packet;

    // Step 1: Add 6 bytes of FF (255 in hex)
    for (int i = 0; i < 6; i++) {
        packet.push_back(0xFF);
    }

    // Step 2: Add the MAC address 16 times
    for (int i = 0; i < 16; i++) {
        for (auto byte : mac) {
            packet.push_back(byte);
        }
    }

    return packet;
}

// Function to send the magic packet over the network
bool sendPacket(const std::vector<unsigned char>& packet) {
    // Create a UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cout << "Error: Could not create socket" << std::endl;
        return false;
    }

    // Allow the socket to send broadcast messages
    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        std::cout << "Error: Could not set broadcast option" << std::endl;
        close(sock);
        return false;
    }

    // Set up the destination (broadcast address: 255.255.255.255, port 9)
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9); // Port 9 is common for WOL
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    // Send the packet
    ssize_t sent = sendto(sock, packet.data(), packet.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (sent < 0) {
        std::cout << "Error: Failed to send packet" << std::endl;
        close(sock);
        return false;
    }

    // Clean up
    close(sock);
    return true;
}

int main() {
    std::string mac;

    // Ask user for the MAC address
    std::cout << "Enter MAC address (example: 00:11:22:33:44:55): ";
    std::cin >> mac;

    // Parse the MAC address into bytes
    auto macBytes = parseMAC(mac);
    if (macBytes.size() != 6) {
        std::cout << "Error: Invalid MAC address. Use format XX:XX:XX:XX:XX:XX" << std::endl;
        return 1;
    }

    // Create the magic packet
    auto packet = createMagicPacket(macBytes);

    // Send the packet and check for errors
    if (!sendPacket(packet)) {
        return 1; // Exit with error if sending fails
    }

    // Success!
    std::cout << "Magic packet sent successfully!" << std::endl;
    return 0;
}