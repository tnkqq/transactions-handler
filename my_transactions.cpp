#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include<cstdio>
#include<stdio.h>
#include <tchar.h>
using namespace std;

struct transaction{
    std :: string description;
    int amount;
    int id;
    std :: string dt;
};

void conslole_clear(){
    #if defined _WIN32
    system("cls");

    #else
    system("clear");

    #endif
}

bool isNumeric(std :: string const &input){
    auto it = input.begin();
    while (it != input.end() && std::isdigit(*it)) {
        it++;
    }
    return !input.empty() && it == input.end();
}

void getTransactionList(transaction* transactions_list,int list_size){
    // cout << "LIST : SIZE : " << list_size << "\n";
    for (int i=0;i<list_size;i++){
        cout <<i+1<<". "<<"id: "<< transactions_list[i].id<<" | Description: "<< transactions_list[i].description << " |" << " Amount:" << transactions_list[i].amount << " |" << " Date:" << transactions_list[i].dt << endl;
    }
}

void addTransaction(transaction *transactions_list,transaction* tr,int id,int size_list){
    // gmttime 
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    
    std::string input_desc;
    std::cout << "Input description:";
    std::getline(std::cin,input_desc);
    (*tr).description = input_desc;
    
    int input_amount;
    std::string input;
    while(true){
        std::cout << "Input amount:";
        std::getline(std::cin,input);
        if (isNumeric(input)){
            input_amount = std::stoi(input); 
            break;
        }
        std::cout << "Invalid input... Enter a number! \n";
    }
    (*tr).amount = input_amount;
    (*tr).dt = dt;
    (*tr).id = id;
    if (size_list < 1){
        transactions_list[0] = *tr;
    }
    else{
        transactions_list[size_list] = *tr;
    }
    
}

bool deleteTransaction(transaction*& transactions_list,int list_size){


    getTransactionList(transactions_list,list_size);
    int index;
    std::string input;
    while(true){
        std::cout << "Transaction number ('e' for exit): ";
        std::getline(std::cin , input);
        if (input== "e") {
            return false; 
        }
        if(isNumeric(input)){
            index = std::stoi(input);
            if (1<=index && index<=list_size){
                break;
            };
        }
        conslole_clear();
        getTransactionList(transactions_list,list_size);
        std::cout << "Invalid index! \n";
    }
    
    index--;
    transaction* temp = new transaction[list_size-1]; 

    for (int i = 0;i<index;i++){
        temp [i] = transactions_list[i];
    }

    for (int i = index+1;i<list_size;i++){
        temp [i-1] = transactions_list[i];
    }
    delete[] transactions_list;
    transactions_list = temp;

    return true;
    
}


void save_transactions_to_csv(transaction* transactions_list,int list_size){
    
    std::ofstream file("transactions.csv", std::ios::app);

    // if transactions.csv already created
    if (file.is_open()){
    
        for (int i = 0;i < list_size;i++){
        file << transactions_list[i].id << "," 
            <<transactions_list[i].description << "," 
            <<transactions_list[i].amount << ","
            <<transactions_list[i].dt << std::endl;
        }

    }
    else{
        std::ofstream file("transactions.csv");

        file << "id, Description, Amount, Date \n"<< std::endl;

        for (int i = 0;i < list_size;i++){
        file << transactions_list[i].id << "," 
            <<transactions_list[i].description << "," 
            <<transactions_list[i].amount << ","
            <<transactions_list[i].dt << std::endl;
        }
    }
}

int message_handler(transaction *transactions_list){
    int short action;
    std::string input_str;
    while (true){
    printf("Action: \n");
    printf("1.Add Transaction \n");
    printf("2.Delete Transaction \n");
    printf("3.Get Transactions List\n");
    printf("4.Exit \n");
        std::cout << "Select action: ";
        std::getline(std::cin, input_str);
        if (isNumeric(input_str)){
            action = std::stoi(input_str);
            if (1<= action && action <= 4){
                break;
            }    
        }
        conslole_clear();
        std::cout << "Invalid input.Select action again. \n \n";
    }
    return action;
}

void arrayExtension(transaction*& transactions_list,int const max_size,int const size_list){
    transaction* temp = new transaction [max_size];
    for (int i = 0 ; i < size_list;i++){
        temp[i] = transactions_list[i];
    }
    delete[] transactions_list;
    transactions_list = temp;
}




int main(){
    transaction *transactions_list = new transaction[2];
    int counter = 0;
    int size_list = 0;
    int max_size = 2;
    while (true){
        
        back_handler:
        int action;
        action =  message_handler(transactions_list);
        conslole_clear();
        
        switch (action){
            case 1:{counter+=1;
                transaction* tr = new transaction;
                addTransaction(transactions_list,tr,counter,size_list);
                conslole_clear();
                size_list++;
                if (size_list == max_size){
                    max_size *= 2;
                    arrayExtension(transactions_list,max_size,size_list);}
                break;}

            case 2:{
                if (deleteTransaction(transactions_list,size_list)){size_list--;}
                conslole_clear();
                break;}

            case 3:{getTransactionList(transactions_list,size_list);
                break;}

            case 4:{
                break;}
        }
        
        if (action==4){
            std::string input0;
            int input;
            conslole_clear();
            std :: cout << "Are you sure you want to close the program? \n 1 - Close \n 2 - back \n Select action: ";
            reinput:
            std::getline(std::cin, input0);
            if (isNumeric(input0)){
                input = std::stoi(input0);
            }else{goto default_reinput;}

            switch(input){
                case 1:{
                    save_transactions_to_csv(transactions_list,size_list);
                    std::cout << "Programm was closed... \n";
                    goto exit_handler;}
                case 2:{conslole_clear();
                    goto back_handler;}

                default:{default_reinput:
                    conslole_clear();
                    std::cout << "Choose '1' for exit or '0' for back to menu :";
                    goto reinput;}
            }
        }
    }
    
    exit_handler:
    return 0;
}
//reinit repositorie git

