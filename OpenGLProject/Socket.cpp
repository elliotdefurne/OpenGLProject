#include "Socket.h"

bool Socket::connectToServer(const char* ip, int port) {
    printf("[Socket] Initialisation Winsock...\n");
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("[Socket] ERREUR: WSAStartup failed\n");
        return false;
    }

    printf("[Socket] Creation du socket...\n");
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("[Socket] ERREUR: creation du socket echouee\n");
        WSACleanup();
        return false;
    }

    printf("[Socket] Tentative de connexion a %s:%d...\n", ip, port);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    InetPtonA(AF_INET, ip, &addr.sin_addr);

    if (connect(m_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        switch (error) {
        case WSAETIMEDOUT:
            printf("  -> Le serveur n'a pas repondu (timeout)\n");
            printf("  -> Verifier que le serveur est demarre\n");
            break;
        case WSAECONNREFUSED:
            printf("  -> Connexion refusee, il y a-t-il déjà une autre connexion en cours ?\n");
            printf("  -> Le port est peut-etre ferme\n");
            break;
        case WSAEHOSTUNREACH:
            printf("  -> Hote injoignable\n");
            printf("  -> Vérifier l'adresse IP\n");
            break;
        default:
            printf("  -> Erreur inconnue\n");
        }

        closesocket(m_socket);
        WSACleanup();
        return false;
    }

    printf("[Socket] Connexion reussie!\n");

    u_long mode = 1;
    ioctlsocket(m_socket, FIONBIO, &mode);

    // Sauvegarder les informations du serveur
    m_serverIP = ip;
    m_serverPort = port;

    // Récupérer les informations locales (IP et port client)
    sockaddr_in localAddr;
    int addrLen = sizeof(localAddr);
    if (getsockname(m_socket, (sockaddr*)&localAddr, &addrLen) == 0) {
        char ipStr[INET_ADDRSTRLEN];
        InetNtopA(AF_INET, &localAddr.sin_addr, ipStr, sizeof(ipStr));
        m_localIP = ipStr;
        m_localPort = ntohs(localAddr.sin_port);
    }

    m_connected = true;
    m_running.store(true);
    m_netThread = std::thread(&Socket::networkLoop, this);
    return true;
}


void Socket::stop() {
    if (!m_running.load()) return;
    m_running.store(false);

    if (m_netThread.joinable()) m_netThread.join();

    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        WSACleanup();
    }
    m_connected = false; // Mettre à jour le statut
}

void Socket::sendPacket(const std::string& data) {
    std::lock_guard<std::mutex> lock(m_outMutex);
    m_outgoing.push(data);
}

bool Socket::pollEvent(std::string& out) {
    std::lock_guard<std::mutex> lock(m_inMutex);
    if (m_incoming.empty()) return false;
    out = m_incoming.front();
    m_incoming.pop();
    return true;
}


// Thread qui tourne en fond

void Socket::networkLoop() {
    char buffer[Constants::MAX_PACKET_SIZE];

    while (m_running.load()) {
        int n = recv(m_socket, buffer, sizeof(buffer), 0);
        if (n > 0) {
            std::lock_guard<std::mutex> lock(m_inMutex);
            m_incoming.push(std::string(buffer, n));
        }

        {
            std::lock_guard<std::mutex> lock(m_outMutex);
            while (!m_outgoing.empty()) {
                const std::string& msg = m_outgoing.front();
                send(m_socket, msg.data(), (int)msg.size(), 0);
                m_outgoing.pop();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}