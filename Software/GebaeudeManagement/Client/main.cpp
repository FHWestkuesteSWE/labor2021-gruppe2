// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Client.h"

using namespace std;
int main(int argc, char* argv[])
{
    Client c(argv[1], argv[2]);
    char req[1024];
    char ans[1024];
    char wahl;
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout << "Was wollen Sie tun: " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Aktuelle Raumtemperatur ueberpruefen \t(t)" << endl;
        cout << "Aussentueren oeffnen / schliessen \t(a)" << endl;
        cout << "..." << endl;
        cout << "Beenden \t\t\t\t(e)" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 't': // req zusammenbauen
            c.sendRequest(req, ans);
            cout << ans;
            break;
        default:;

        }
    } while (wahl != 'e');
}

