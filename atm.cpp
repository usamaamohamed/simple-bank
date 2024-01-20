#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>

using namespace std;

struct sClient
{
    string name;
    string AccountNumber;
    string PinCode;
    double Balance;
    string Phone;
    bool MarkForDelete = false;
};

enum EN_ATM_Operations  { Quick_Withdraw = 1 , Normal_Withdraw = 2 , Deposit = 3 , Check_Balance = 4 , Logout = 5 };

const string ClientsFileName = "clients_data.txt";
const string ClientsFileSeperator = "----------------------------------------------------------------------";

int client_number = 0;
sClient Current_Client;
vector <sClient> V_Clients;

string split_line_words(string line , string delim = ":" )
{
    string line_info;
    int delim_pos = line.find(delim);
    if (delim_pos != std::string::npos)
    {
        line_info = line.substr(delim_pos +2 , line.length());
    }
    return line_info;
}
sClient load_info_to_client_struct(sClient & Client ,vector <string>  info_string )
{
    Client.name = info_string[0];
    Client.Phone = info_string[1];
    Client.AccountNumber = info_string[2];
    Client.PinCode = info_string[4];
    Client.Balance = stod(info_string[3]);
    return Client;
}
vector <sClient> convert_words_to_client_data(string line ,vector <string> & info_string ,sClient & Client)
{
    string line_info  = split_line_words(line);

    if (line_info != "")
    {
        info_string.push_back(line_info);
    }
    if (line == ClientsFileSeperator)
    {
        load_info_to_client_struct(Client , info_string);
        V_Clients.push_back(Client);
        info_string.clear();
    }
    return V_Clients;
}
vector <sClient> load_clients_from_file_to_vector()
{
    sClient Client;
    vector <string> info_string;
    string line = "";
    fstream MyFile;
    MyFile.open(ClientsFileName , ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile , line))
        {
            convert_words_to_client_data(line , info_string , Client);
        }
        MyFile.close();
    }
    return V_Clients;
}

void refresh_vector_after_transaction(vector <sClient>& V_Clients, sClient& Client)
{
    for (int i = 0; i < size(V_Clients); i++)
    {
        if (V_Clients[i].AccountNumber == Client.AccountNumber)
        {
            V_Clients[i] = Client;
        }
    }
}

vector <sClient> Save_New_Vector_To_file( vector <sClient>& V_Clients)
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out); //overwrite
    if (MyFile.is_open())
    {
        for (int i = 0; i < size(V_Clients); i++)
        {
            if (V_Clients[i].MarkForDelete == false)
            {
                MyFile << "client number " << i + 1 << "\n";
                MyFile << "Name: " << V_Clients[i].name << "\n";
                MyFile << "Phone: " << V_Clients[i].Phone << "\n";
                MyFile << "Accout Number: " << V_Clients[i].AccountNumber << "\n";
                MyFile << "Account Balance: " << V_Clients[i].Balance << "\n";
                MyFile << "Pin Code: " << V_Clients[i].PinCode << "\n";
                MyFile << ClientsFileSeperator << endl;
            }
        }
        MyFile.close();
    }
    return V_Clients;
}

bool check_account_number()
{
    for (client_number; client_number < size(V_Clients) ; client_number++)
    {
        if (Current_Client.AccountNumber == V_Clients[client_number].AccountNumber)
        {
            return true;
        }
    }
    return false;
}

bool check_password()
{
    if (Current_Client.PinCode == V_Clients[client_number].PinCode)
    {
        return true;
    }
    return false;
}

bool login()
{
    V_Clients = load_clients_from_file_to_vector();
    cout << "\n==================================================================\n";
    cout << "                      Login Menu Menu                             \n";
    cout << "==================================================================\n";
    cout << "Enter Account Number: ";
    cin >> Current_Client.AccountNumber;

    while (!check_account_number())
    {
        if (client_number >= 2)
        {
            cout << "Operation Terminated.\n";
            cout << "Please Contact Bank Customer Service.\n";
            Current_Client.AccountNumber = "*****"; 
            Current_Client.name = "*****";
            Current_Client.PinCode = "*****";  
            Current_Client.Balance = 0; 
            return false;
        }
        
        cout << "Invalid Account Number , Try Again\n";
        cin >> Current_Client.AccountNumber;
        client_number++;
    }    
    
    cout << "Enter PinCode: ";
    cin >> Current_Client.PinCode;

    int password_iterator = 0;
    while (!check_password())
    {
        if (password_iterator >= 2)
        {
            cout << "Your Card Is Locked.\n";
            cout << "Please Contact Bank Customer Service.\n";
            Current_Client.AccountNumber = "*****"; 
            Current_Client.name = "*****";
            Current_Client.PinCode = "*****";  
            Current_Client.Balance = 0; 
            return false;
        }
        
        cout << "Invalid Pincode , Try Again\n";
        cin >> Current_Client.PinCode;
        password_iterator++;
    }
    Current_Client = V_Clients[client_number];
    return true;
}
//-----------------------------------------------------------------------------------------------------------
int transfer_quick_draw_amount_of_money(short Withdraw_amount_money)
{
    switch ( Withdraw_amount_money)
    {
    case 1:
        return 50;
    
    case 2:
        return 100;

    case 3:
        return 200;

    case 4:
        return 300;

    case 5:
        return 400;  

    case 6:
        return 500;
    
    case 7:
        return 1000;

    case 8:
        return 2000;

    case 9:
        return 3000;

    case 0:
        return 0;
    default:
        break;
    }
    return Withdraw_amount_money;
}

int show_quick_withdraw_main_menu_screen()
{
    string Withdraw_amount = "";
    //system("cls");
    cout << "\n==================================================================\n";
    cout << "                       Quick Withdraw Menu.                       \n";
    cout << "==================================================================\n";
    cout << "Choose Amount You Want To Withdraw?\n";
    cout << "       [1] 50                [2] 100                   \n";
    cout << "       [3] 200               [4] 300                   \n";
    cout << "       [5] 400               [6] 500                   \n";
    cout << "       [7] 1000              [8] 2000                  \n";
    cout << "       [9] 3000                                        \n";
    cout << "                   [0] Exit                            \n";
    cout << "Amount Of Money: ";
    cin >> Withdraw_amount;
    while (Withdraw_amount != "0" &&  Withdraw_amount != "1" && Withdraw_amount != "2" &&  Withdraw_amount != "3" &&  
           Withdraw_amount != "4" &&  Withdraw_amount != "5" && Withdraw_amount != "6" &&  Withdraw_amount != "7" && 
           Withdraw_amount != "8" &&  Withdraw_amount != "9")
    {
        cout << "enter again.\n";
        cin >> Withdraw_amount;
    }
    short Withdraw_amount_money = stoi(Withdraw_amount);
    Withdraw_amount_money = transfer_quick_draw_amount_of_money(Withdraw_amount_money);
    return Withdraw_amount_money;
}


void Quick_Withdraw_Operation()
{
    char insurance = 'n';
    short Withdraw_Amount = show_quick_withdraw_main_menu_screen();
    while (Withdraw_Amount > Current_Client.Balance)
    {
        cout << "Withdraw Amount Exceds Your Balance. \n You Can Withdraw Up To = " << Current_Client.Balance << "\n Withdraw Amount:" ;
        Withdraw_Amount = show_quick_withdraw_main_menu_screen();
        cout << endl;
    }
    
    cout << "Are You Sure You Want To Withdraw This Amount?\n";
    cin >> insurance;
    if (insurance == 'y' || insurance == 'Y')
    {
        Current_Client.Balance -= Withdraw_Amount;
        cout << "Successful Transaction. \n";
        cout << "\nNew Balance = " << Current_Client.Balance << "\n";
        //system("color 2F"); //turn screen to green
    }
    else
    {
        cout << "\nTransaction Terminated.\n";
        //system("color 4F"); //turn screen to red
    }
}

//-----------------------------------------------------------------------------------------------------------
void Normal_Withdraw_Operation()
{
    char insurance = 'n';
    double Withdraw_Amount = 0;
    cout << "Please Enter Withdraw Amount: ";
    cin >> Withdraw_Amount;
    while (cin.fail())     
    { 
        // user didn't input a number    
        cin.clear();      
        cin.ignore( std::numeric_limits < std::streamsize > ::max(), '\n');          
        cout << "Invalid input data type ,Enter a valid number:" << endl;         
        cin >> Withdraw_Amount;     
    }

    while (Withdraw_Amount > Current_Client.Balance)
    {
        cout << "Withdraw Amount Exceds Your Balance. \n You Can Withdraw Up To = " << Current_Client.Balance << "\n Withdraw Amount:" ;
        cin >> Withdraw_Amount;
        cout << endl;
    }
    
    cout << "Are You Sure You Want To Withdraw This Amount?\n";
    cin >> insurance;
    if (insurance == 'y' || insurance == 'Y')
    {
        Current_Client.Balance -= Withdraw_Amount;
        cout << "Successful Transaction. \n";
        cout << "\nNew Balance = " << Current_Client.Balance << "\n";
        //system("color 2F"); //turn screen to green
    }
    else
    {
        cout << "\nTransaction Terminated.\n";
        //system("color 4F"); //turn screen to red
    }
}
//-----------------------------------------------------------------------------------------------------------
void Deposit_Operation()
{
    char insurance = 'n';
    double Deposite_Amount = 0;
    cout << "Please Enter Deposite Amount: ";
    cin >> Deposite_Amount;
    while (cin.fail())     
    { 
        // user didn't input a number    
        cin.clear();      
        cin.ignore( std::numeric_limits < std::streamsize > ::max(), '\n');          
        cout << "Invalid input data type ,Enter a valid number:" << endl;         
        cin >> Deposite_Amount;     
    }
    cout << "Are You Sure You Want To Deposite This Amount?\n";
    cin >> insurance;
    if (insurance == 'y' || insurance == 'Y')
    {
        Current_Client.Balance += Deposite_Amount;
        cout << "Successful Transaction. \n";
        cout << "\nNew Balance = " << Current_Client.Balance << "\n";
        //system("color 2F"); //turn screen to green
    }
    else
    {
        cout << "\nTransaction Terminated.\n";
        //system("color 4F"); //turn screen to red
    }

}
//-----------------------------------------------------------------------------------------------------------
void Show_Balance()
{
    cout << "Your Balance = " << Current_Client.Balance << endl;
}
//-----------------------------------------------------------------------------------------------------------
void operation_navigator(short operation)
{
    switch (operation)
    {
    case EN_ATM_Operations::Quick_Withdraw:
        Quick_Withdraw_Operation();
        break;
    
    case EN_ATM_Operations::Normal_Withdraw:
        Normal_Withdraw_Operation();
        break;

    case EN_ATM_Operations::Deposit:
        Deposit_Operation();
        break;

    case EN_ATM_Operations::Check_Balance:
        Show_Balance();
        break;

    case EN_ATM_Operations::Logout:
        
        break;
    }
    refresh_vector_after_transaction(V_Clients , Current_Client);
    Save_New_Vector_To_file(V_Clients);
}

//-----------------------------------------------------------------------------------------------------------
short show_atm_menu()
{   
    string user_operation = "";
    short user_operation_number = 0;

    cout << "==================================================================\n";
    cout << "                         ATM Menu Screen                          \n";
    cout << "==================================================================\n";
    cout << "       [1] Quick Withdraw.   \n";
    cout << "       [2] Normal Withdraw.  \n";
    cout << "       [3] Deposit.          \n";
    cout << "       [4] Check Balance.    \n";
    cout << "       [5] LogOut.           \n";
    cout << "Your Operation: ";
    getline(cin >> ws, user_operation);
    while (user_operation != "1" && user_operation != "2" && user_operation != "3" && user_operation != "4" && user_operation != "5")
    {
        cout << "You Must Enter a Number from 1 to 5.\n";
        cin >> user_operation;
    }
    user_operation_number = stoi(user_operation);

    return user_operation_number;
}

int main()
{
    char ans = 'y';
    if (login())
    {
        while (ans != 'n')
        {
            short operation = show_atm_menu();
            if (operation == EN_ATM_Operations::Logout)
            {
                break;
            }
            
            operation_navigator(operation);
            cout << "Do You Want To Do Any Thing Else? (y/n).\n";
            cin >> ans;
        }
    }

    cout << "\n             Thank You For Using Our Service.\n";
    cout << "                       Program CLosed.\n";

    return 0;
}