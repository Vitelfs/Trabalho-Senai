#include <iostream>

int main(){

    int decision;

    std::cout << "1 Cadastrar clientes\n"
              << "2 Listar clientes\n"
              << "3 Cadastrar quartos\n"
              << "4 Listar quartos exibindo o status\n"
              << "5 listar apenas quartos disponíveis\n"
              << "6 Reservar quartos para os dias disponíveis\n"
              << "7 Listar todas as reversas em aberto - José Vitor\n"
              << "8 Listar todas as reversas por período\n";
    do{
        std::cin >> decision;
    }while(decision < 1 && decision > 8);

    return 0;
}