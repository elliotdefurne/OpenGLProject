#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <atomic>
#include <queue>
#include <string>
#include <mutex>

#include "constants.h"

#pragma comment(lib, "ws2_32.lib")

class Socket {
public:
    Socket() : m_running(false), m_socket(INVALID_SOCKET) {}

    /**
     * @brief Établit une connexion TCP au serveur spécifié
     *
     * Initialise Winsock, crée un socket TCP, se connecte au serveur,
     * passe le socket en mode non-bloquant et démarre le thread réseau.
     *
     * @param ip Adresse IP du serveur (format string, ex: "127.0.0.1")
     * @param port Numéro de port du serveur
     * @return true si la connexion est établie avec succès
     * @return false en cas d'erreur (échec Winsock, socket, ou connexion)
     */
    bool connectToServer(const char* ip, int port);

    /**
     * @brief Arrête proprement la connexion réseau
     *
     * Signale au thread réseau de s'arrêter, attend sa terminaison,
     * ferme le socket et nettoie Winsock. Thread-safe et peut être
     * appelée plusieurs fois sans effet secondaire.
     */
    void stop();

    /**
     * @brief Envoie un paquet de données au serveur de manière asynchrone
     *
     * Ajoute les données à la queue d'envoi. L'envoi réel sera effectué
     * par le thread réseau. Thread-safe grâce au mutex.
     *
     * @param data Chaîne de caractères contenant les données à envoyer
     */
    void sendPacket(const std::string& data);

    /**
     * @brief Récupère le prochain paquet reçu depuis le serveur
     *
     * Vérifie s'il y a des données reçues dans la queue d'entrée.
     * Si oui, récupère le premier paquet et le retire de la queue.
     * Thread-safe grâce au mutex.
     *
     * @param[out] out Référence où sera stocké le paquet reçu
     * @return true si un paquet a été récupéré
     * @return false si la queue d'entrée est vide
     */
    bool pollEvent(std::string& out);

    // Getters

    inline std::string getServerIP() { return m_serverIP; };
    inline int getServerPort() { return m_serverPort; };
    inline std::string getLocalIP() { return m_localIP; };
    inline int getLocalPort() { return m_localPort; };
    inline bool getIsConnected() { return m_connected; };

private:
    /**
     * @brief Boucle principale du thread réseau (réception/envoi)
     *
     * Tourne en continu tant que running est vrai :
     * - Reçoit les données du serveur et les ajoute à la queue d'entrée
     * - Envoie tous les paquets en attente dans la queue de sortie
     * - Pause de 1ms entre chaque itération pour réduire la charge CPU
     *
     * @note Cette fonction s'exécute dans un thread séparé
     * @note Utilise des mutex pour protéger l'accès aux queues
     */
    void networkLoop();

    std::atomic<bool> m_running;
    SOCKET m_socket;

    std::thread m_netThread;

    std::queue<std::string> m_incoming;
    std::mutex m_inMutex;

    std::queue<std::string> m_outgoing;
    std::mutex m_outMutex;

    // Informations de connexion
    std::string m_serverIP;
    int m_serverPort = 0;
    std::string m_localIP;
    int m_localPort = 0;
    bool m_connected = false;
};