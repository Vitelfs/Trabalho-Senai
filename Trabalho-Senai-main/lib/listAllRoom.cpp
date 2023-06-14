#include <iostream>
#include <fstream>
#include <conio.h>
#include "nlohmann/json.hpp"


void listAllRooms() {
    std::ifstream fileRoom("lib/room.json");
    nlohmann::json jsonData;
    if (fileRoom.is_open()) {
        fileRoom >> jsonData;
        for (const auto& category : jsonData["category"].items()) {
            std::cout << "Categorias: " << category.key() << std::endl;
            std::cout << "--------------------------" << std::endl;
            for (const auto& room : category.value()) {
                std::cout << "Numero do quarto: " << room["number"] << std::endl;
                std::cout << "Quarto ocupado: " << room["occupied"] << std::endl;
                std::cout << "Preco: " << room["price"] << std::endl;
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "Failed to open room.json" << std::endl;
    }
    system("pause");
    system("cls");
}