void ListRooms() {
    
    std::ifstream Room("lib/room.json");
    nlohmann::json Data;

    if (Room.is_open()) {
        Room >> Data;
        for (const auto& category : Data["category"].items()) {
            std::cout << "Categoria: " << category.key() << std::endl;
            std::cout << "--------------------------" << std::endl;
            for (const auto& room : category.value()) {
                std::cout << "Numero: " << room["number"] << std::endl;
                std::cout << "Estatus: " << room["occupied"] << std::endl;
                std::cout << "Preço: " << room["price"] << std::endl;
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "Falha ao abrir o arquivo" << std::endl;
    }
    system("pause");
    system("cls");
}

