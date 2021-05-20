// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//Jost test

#include <iostream>
#include "BasicClient.h"

using namespace std;
int main(int argc, char* argv[])
{
    // Define Server IP/PORT
    char serverAdresse[] = "127.0.0.1";
    char serverPort[] = "5000";
    //Client c(argv[1], argv[2]);
    BasicClient c(serverAdresse, serverPort);
    char req[1024];
    char ans[1024];
    char wahl;
    // Basic CMD Interface
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout <<      "Was wollen Sie tun: " << endl;
        cout <<      "----------------------------------------------------" << endl;
        cout <<      "Jede Beleuchtung im Gebaeude ausschalten \t(x)" << endl;
        cout <<      "Beleuchtungszustaende aktualisieren      \t(r)" << endl;
        cout <<      "Beenden                                  \t(e)" << endl;
        cout <<      "----------------------------------------------------" << endl;
        cout <<      "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 'x': // Turn off every Light
            strcpy_s(req, "LightOff\0");
            c.sendRequest(req, ans);
            cout << ans;
            break;
        case 'r': // Reload Light Information
            strcpy_s(req, "getLightInfo\0");
            c.sendRequest(req, ans);
            // Light Management
            cout << ans;
            break;
        default:;

        }
    } while (wahl != 'e');
}

