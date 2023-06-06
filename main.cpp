#include <iostream>
#include <fstream>
#include <string>

struct Information {
    int num;
    std::string category;
    int status;
    Information* next;
};

typedef Information Status;

int InitializeList(Status* room) {
    room->next = nullptr;
    return 0;
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
        }
    }while(decision != 9);

    return 0;
}