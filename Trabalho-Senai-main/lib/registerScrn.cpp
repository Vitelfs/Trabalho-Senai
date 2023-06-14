#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

struct Client{ //victor
    std::string name;
    std::string cpf;
    std::string password;
};
void register_scrn() { //victor
    system("cls");
    std::ifstream file("lib/clientData.json");
    nlohmann::json data;

    if (file.is_open()) {
        file >> data;
        file.close();
    }
    else {
        std::cout << "Falha ao abrir o arquivp\n";
        return;
    }

    Client clientRegistrationData;

    std::cout << "#######################\n";
    std::cout << "##  Tela de registro  ##\n";
    std::cout << "#######################\n";

    std::cout << "Ponha o seu nome completo:\n";
    std::getline(std::cin >> std::ws, clientRegistrationData.name);

    for(int i = 0;i < clientRegistrationData.name.size();i++){
        clientRegistrationData.name[i] = tolower(clientRegistrationData.name[i]);
    }

    std::cout << "Ponha o seu cpf(Apenas numeros): ";
    std::cin >> clientRegistrationData.cpf;
    std::cout << "Ponha a sua senha:\n";
    std::cin >> clientRegistrationData.password;

    
    nlohmann::json clientData;
    clientData["name"] = clientRegistrationData.name;
    clientData["cpf"] = clientRegistrationData.cpf;
    clientData["password"] = clientRegistrationData.password;

    data.push_back(clientData);

    std::ofstream outputFile("clientData.json");
    if (outputFile.is_open()) {
        outputFile << data.dump(4) << std::endl;
        outputFile.close();
        std::cout << "Registrado com sucesso\n";
    }
    else {
        std::cout << "Falha ao abrir o arquivo para armazenamento\n";
    }
}
