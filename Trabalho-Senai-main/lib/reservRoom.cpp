#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "nlohmann/json.hpp"
#include "date/date.h"


void reservRoom() { //victor
    std::fstream fileRoom("room.json", std::ios::in | std::ios::out);
    nlohmann::json jsonData;

    if(fileRoom.is_open()){
        fileRoom >> jsonData;
        std::string category;
        std::string clientName;

        std::cout << "Qual categoria de quarto voce quer?" << std::endl;
        std::cout << "Basic: R$50/dia | Lux: R$100/dia | SuperLux: R$150/dia" << std::endl;
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