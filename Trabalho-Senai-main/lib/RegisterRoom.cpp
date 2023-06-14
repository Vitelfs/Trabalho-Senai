#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

void Register() {

    int option, price;
	nlohmann::json Data;
	std:: string category, num;
	std::fstream Room("lib/room.json");
	
	if(Room.is_open()){
	    Room >> Data;
	    std::cout << "Digite o numero do quarto: ";
	    std:: cin >> num;

	    std:: cout << "Digite a categoria:";
	    std:: cout << "\n1- Superlux";
	    std:: cout << "\n2- lux";
	    std:: cout << "\n3- Basic\nR:";
	    std:: cin >> option;
	    
	    switch(option){
	        case 1:
	        category = "superlux";
	        price = 150;
	        break;
	        case 2:
	        category = "lux";
	        price= 100;
	        break;
	        case 3:
	        category = "basic";
	        price = 50;
	        break;
	    }
	    
	    nlohmann::json Room_Json;

	    Room_Json ["number"] = num;
        Room_Json ["occupied"] = false;
	    Room_Json ["price"] = price;
	    
	    Data["category"][category].push_back(Room_Json);

            Room.seekp(0);
    
            Room << std::setw(4) << Data << std::endl;
    
            Room.close();
        
	}else{
        std:: cout << "Arquivo não aberto\n";
    }
    
}
