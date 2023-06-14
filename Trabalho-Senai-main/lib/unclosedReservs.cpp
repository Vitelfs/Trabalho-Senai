#include <iostream>
#include <fstream>
#include <conio.h>
#include "nlohmann/json.hpp"
#include "date/date.h"

void OpenReserveList() {
    std::ifstream fileRoom("lib/room.json");
    nlohmann::json jsonData;
    if (fileRoom.is_open()) {
        fileRoom >> jsonData;
        for (auto& category : jsonData["category"].items()) {
            for (auto& room : category.value().items()) {
                if (room.value()["occupied"]) {
                    std::cout << "Quarto: " << room.value()["number"] << std::endl;
                    std::cout << "Categoria: " << category.key() << std::endl;
                    std::cout << "Reservado por: " << room.value()["occupiedBy"] << std::endl;
                    std::cout << "Data de inicio: " << room.value()["start_date"] << std::endl;
                    std::cout << "Data de fim: " << room.value()["end_date"] << std::endl;
                    std::cout << "---------------------------" << std::endl;
                }
            }
        }
    }
    bool reservelist = true;
    std::cout <<"Sem Reservas" << std::endl;

    system("pause");
    system("cls");
}