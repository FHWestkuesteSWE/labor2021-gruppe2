// main.cpp : Diese Datei enth�lt die Funktion "main". Hier beginnt und endet die Ausf�hrung des Programms.
//Jost test

#include <iostream>
#include "BasicClient.h"

using namespace std;
int main(int argc, char* argv[])
{
    char serverAdresse[] = "127.0.0.1";
    char serverPort[] = "5000";
    //Client c(argv[1], argv[2]);
    BasicClient c(serverAdresse, serverPort);
    char req[1024];
    char ans[1024];
    char wahl;
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout << "Was wollen Sie tun: " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Jede Beleuchtung im Gebaeude ausschalten \t(x)" << endl;
        cout << "Beenden \t\t\t\t(e)" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 'x': // req zusammenbauen
            strcpy_s(req, "LightOff\0");
            c.sendRequest(req, ans);
            cout << ans;
            break;
        default:;

        }
    } while (wahl != 'e');
}

