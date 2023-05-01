#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>

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
        try{
            input_amount = std::stoi(input);
            break;
        }
        catch(const std::invalid_argument&){
            conslole_clear();
            std::cout << "Invalid input... Enter a number! \n";
        }
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

void deleteTransaction(transaction*& transactions_list,int list_size){

    getTransactionList(transactions_list,list_size);

    std::string input;
    std::cout << "Element number ('e' for exit): ";
    std::cin >> input;

    if (input== "e") {
        return; 
    }

    // while true()
    int index = std::stoi(input);
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
    printf_s("Action: \n");
    printf_s("1.Add Transaction \n");
    printf_s("2.Delete Transaction \n");
    printf_s("3.Get Transactions List\n");
    printf_s("4.Exit \n");
    
    while (true){
        std::cout << "Select action: ";
        std::getline(std::cin, input_str);
        try{
            action = std::stoi(input_str);
            break;
        } catch (const std::invalid_argument&){
            std::cout << "Invalid input.Please enter a number. \n";
        }
    }
    return action;
}


int main(){
    transaction *transactions_list = new transaction[4];
    int counter = 0;
    int size_list = 0;
    while (true){
        int action;
        action =  message_handler(transactions_list);
        conslole_clear();
        switch (action){
            case 1:{
                counter+=1;
                transaction* tr = new transaction;
                addTransaction(transactions_list,tr,counter,size_list);
                conslole_clear();
                size_list++;
                break;
            }
            case 2:{
                deleteTransaction(transactions_list,size_list);
                conslole_clear();
                size_list--;
                break;       
            }
            case 3:{
                getTransactionList(transactions_list,size_list);
                break;
                }

            case 4:{
                break;
            }
        }
        if (action==4){
            save_transactions_to_csv(transactions_list,size_list);
            std::cout << "Programm was closed... \n";
            break;
        }   
    }
    return 0;
}
