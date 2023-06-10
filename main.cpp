#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "lib/nlohmann/json.hpp"
#include "lib/date/date.h"

struct Information {
    int num;
    std::string category;
    int status;
    Information* next;
};
struct Client{
    std::string name;
    std::string cpf;
    std::string password;
};
typedef Information Status;

int InitializeList(Status* room) {
    room->next = nullptr;
    return 0;
}
void register_scrn() {
    system("cls");
    std::ifstream file("lib/clientData.json");
    nlohmann::json data;

    if (file.is_open()) {
        file >> data;
        file.close();
    }
    else {
        std::cout << "Flha ao abrir o arquivp\n";
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

    std::ofstream outputFile("lib/clientData.json");
    if (outputFile.is_open()) {
        outputFile << data.dump(4) << std::endl;
        outputFile.close();
        std::cout << "Registrado com sucesso\n";
    }
    else {
        std::cout << "Falha ao abrir o arquivo para armazenamento\n";
    }
}
void listAllClients(){
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
                std::cout << "Client "<< clientNum << ":" << client["name"] << std::endl;
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
void reservRoom() {
    std::fstream fileRoom("lib/room.json", std::ios::in | std::ios::out);
    nlohmann::json jsonData;

    if(fileRoom.is_open()){
        fileRoom >> jsonData;
        std::string category;
        std::string clientName;

        std::cout << "Qual categoria de quarto voce quer?" << std::endl;
        std::cout << "Basic: $50/dia | Lux: $100/dia | SuperLux: $150/dia" << std::endl;
        do{
            std::getline(std::cin >> std::ws,category);  
            for(int i = 0;i < category.size();i++){
                category[i] = tolower(category[i]);
            }
            if(category != "basic" && category != "lux" && category != "superlux"){
                std::cout << "Categoria invalida!" << std::endl;
            }
        }while(category != "basic" && category != "lux" && category != "superlux");

        std::cout << "Digite o nome do reservador:\n";
        std::getline(std::cin >> std::ws,clientName);
        
        std::cout << "Ponha uma data de inicio (Estrutura: dd/mm/aaaa): ";
        std::string startDateStr;
        std::getline(std::cin, startDateStr);
        std::istringstream startDateStream(startDateStr);
        date::sys_time<std::chrono::milliseconds> startDate;
        startDateStream >> date::parse("%d/%m/%Y", startDate);

        std::cout << "Quantos dias voce pretende ficar?" << std::endl;
        int days;
        std::cin >> days;

        auto endDate = startDate + date::days(days);
        nlohmann::json rooms = jsonData["category"][category];
        
        bool foundRoom = false;
        for (auto& room : rooms) {
            if (!room["occupied"]) {
                int roomPrice = room["price"].get<double>();
                int totalPrice = roomPrice * days;
                std::cout << "Seu quarto: " << room["number"] << std::endl;
                std::cout << "Preco total por " << days << " dias: $" << totalPrice << ",00" << std::endl;
                std::cout << "Data de inicio: " << date::format("%d/%m/%Y", startDate) << std::endl;
                std::cout << "Data de fim: " << date::format("%d/%m/%Y", endDate) << std::endl;
                foundRoom = true;
                room["occupied"] = true;
                room["start_date"] = date::format("%d/%m/%Y", startDate);
                room["end_date"] = date::format("%d/%m/%Y", endDate);
                room["occupiedBy"] = clientName;
                break;
            }
        }
        if (!foundRoom) {
            std::cout << "Nao temos quartos disponiveis nessa categoria." << std::endl;
            return;
        }
        
        jsonData["category"][category] = rooms;
        
        fileRoom.seekp(0);

        fileRoom << std::setw(4) << jsonData << std::endl;

        fileRoom.close();

        system("pause");
        system("cls");
    }
}
void listReservationPerPeriod(){

    std::ifstream listRoom("lib/room.json");

    if(listRoom.is_open()){
        nlohmann::json jsonData;
        listRoom >> jsonData;
        bool reservFind = false;

        std::cout << "Ponha a data de inicio (Estrutura: dd/mm/aaaa): ";
        std::string startDateStr;
        std::getline(std::cin >> std::ws, startDateStr);

        std::istringstream startDateStream(startDateStr);
        date::sys_time<std::chrono::milliseconds> startDate;
        startDateStream >> date::parse("%d/%m/%Y", startDate);

        std::cout << "Ponha a data de fim (Estrutura: dd/mm/aaaa): ";
        std::string endDateStr;
        std::getline(std::cin >> std::ws, endDateStr);
        
        std::istringstream endDateStream(endDateStr);
        date::sys_time<std::chrono::milliseconds> endDate;
        endDateStream >> date::parse("%d/%m/%Y", endDate);

        for (const auto& category : jsonData["category"].items()) {
            for (const auto& reservation : category.value()) {
                if (reservation.contains("start_date") && reservation.contains("end_date")){
                    std::string reservationStartDateStr = reservation["start_date"];
                    std::istringstream reservationStartDateStream(reservationStartDateStr);
                    date::sys_days reservationStartDate;
                    reservationStartDateStream >> date::parse("%d/%m/%Y", reservationStartDate);

                    std::string reservationEndDateStr = reservation["end_date"];
                    std::istringstream reservationEndDateStream(reservationEndDateStr);
                    date::sys_days reservationEndDate;
                    reservationEndDateStream >> date::parse("%d/%m/%Y", reservationEndDate);

                    if (reservationStartDate >= startDate && reservationEndDate <= endDate) {
                        std::cout << "Detalhes de reversa:" << std::endl;
                        std::cout << "Categoria: " << category.key() << std::endl;
                        std::cout << "Data de inicio: " << reservationStartDateStr << std::endl;
                        std::cout << "Data de fim: " << reservationEndDateStr << std::endl;
                        if (reservation.contains("occupiedBy")) {
                            std::cout << "Ocupada por: " << reservation["occupiedBy"] << std::endl;
                        }
                        std::cout << "Numero do quarto: " << reservation["number"] << std::endl;
                        std::cout << std::endl;
                        reservFind = true;
                    }
                }
            }
        }
        if(!reservFind){
            std::cout << "Nao tem reservas nesse periodo!\n";      
        }
    }
    system("pause");
    system("cls");  
}
void Register(Status* room) {

    char option;
    Status* aux;

    do {
        aux = new Status();
        std::cout << "Digite o numero do quarto: ";
        std::cin >> aux->num;
        std::cin.ignore();

        std::cout << "Digite a categoria do quarto: ";
        std::cin >> aux->category;
        std::cin.ignore();

        std::cout << "Quer cadastrar outro quarto (S/N) ";
        std::cin >> option;
        std::cin.ignore();

        aux->status = 1;

        aux->next = room->next;
        room->next = aux;

    } while (option == 'S');
}

void Print(Status* room) {

    Status* aux = room->next;
    if (aux == nullptr) {
        std::cout << "--> Quarto indisponível <--";
    }
    else {
        while (aux != nullptr) {
            std::cout << aux->num << " ";
            aux = aux->next;
        }
    }
}

void CreateFile(Status* room) {
    std::ofstream file("RegisteredRooms.txt");

    if (room == nullptr) {
        std::cout << "Nenhum quarto registrado";
        file.close();
        return;
    }

    while (room) {
        file << "Numero do quarto: " << room->num << std::endl;
        file << "Estado do quarto: " << room->status << std::endl;
        file << "Categoria: " << room->category << std::endl;
        room = room->next;
    }
    file.close();
}

void RoomStatus(Status* room, int RoomNumber) {

    Status* aux = room->next;

    while (room->next != nullptr) {

        if (RoomNumber == aux->num) {
            if (aux->status == 0) {
                std::cout << "Quarto " << aux->num << " está ocupado" << std::endl;
                std::cout << "categoria: " << aux->category << std::endl;
            }
            else {
                std::cout << "Quarto " << aux->num << " está disponível" << std::endl;
                aux->status = 0;
                std::cout << "Room type: " << aux->category << std::endl;
                CreateFile(aux);
            }
        }
        aux = aux->next;
    }
}

int main(){

    int decision;
    int RoomNumber;
    Status* room = new Status();
    InitializeList(room);
    do{
    std::cout << "1 Cadastrar clientes\n"
              << "2 Listar clientes\n"
              << "3 Cadastrar quartos\n"
              << "4 Listar quartos exibindo o status\n"
              << "5 listar apenas quartos disponíveis\n"
              << "6 Reservar quartos para os dias disponíveis\n"
              << "7 Listar todas as reversas em aberto - José Vitor\n"
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
                std::cout << "=== Registrar quarto ===" << std::endl;
                Register(room);

            break;
            case 4 :
                std::cout << "\n=== Quartos ===" << std::endl;
                Print(room);
                std::cout << "\nDigite o quarto desejado: ";
                std::cin >> RoomNumber;
                RoomStatus(room, RoomNumber);
            break;
            case 6:
                reservRoom();
            break;
            case 8:
                listReservationPerPeriod();
            break;
        }
    }while(decision != 9);

    return 0;
}
