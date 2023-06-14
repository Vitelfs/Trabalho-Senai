#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "nlohmann/json.hpp"
#include "date/date.h"
#include "RegisterRoom.cpp"

void listReservationPerPeriod(){ //victor

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
