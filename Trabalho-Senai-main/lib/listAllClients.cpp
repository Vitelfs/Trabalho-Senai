#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

void listAllClients(){ //victor
    std::fstream clientsData("lib/clientData.json");
    nlohmann::json jsonData;
    int clientNum = 1;
    if(clientsData.is_open()){
        clientsData >> jsonData;

        if (jsonData.empty()) {
        std::cout << "A lista de clientes esta vazia!" << std::endl;
        system("pause");
        system("cls");
        return;
        }
        else{
            for(const auto& client : jsonData){
                std::cout << "Cliente "<< clientNum << ":" << client["name"] << std::endl;
                clientNum++;
                std::cout << std::endl;
            }
            clientsData.close();
        }
    } 
    else {
        std::cout << "Falha ao abrir o arquivo de Data dos clientes\n" << std::endl;
    }

    system("pause");
    system("cls");
}
