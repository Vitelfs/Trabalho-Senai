#include <iostream>
#include <fstream>
#include "lib/nlohmann/json.hpp"
#include "lib/date/date.h"
#include "functions.h"


int main(){

    int decision;
    int RoomNumber;
    do{
    std::cout << "1 Cadastrar clientes\n"
              << "2 Listar clientes\n"
              << "3 Cadastrar quartos\n"
              << "4 Listar quartos exibindo o status\n"
              << "5 listar apenas quartos disponíveis\n"
              << "6 Reservar quartos para os dias disponíveis\n"
              << "7 Listar todas as reversas em aberto\n"
              << "8 Listar todas as reversas por período\n"
              << "9 Sair\n";

        std::cin >> decision;
        switch(decision){
            case 1:
                register_scrn();
                break;
            case 2:
                listAllClients();
                break;
            case 3 :
                Register();
            break;
            case 4 :
                ListRooms();
            break;
            case 5:
                listAllRooms();
            break;
            case 6:
                reservRoom();
            break;
            case 7:
                OpenReserveList();
            break;
            case 8:
                listReservationPerPeriod();
            break;
        }
    }while(decision != 9);

    return 0;
}
