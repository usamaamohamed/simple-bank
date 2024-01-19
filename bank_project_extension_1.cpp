#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

int main();

const string ClientsFileName = "clients_data.txt";
const string ClientsFileSeperator = "----------------------------------------------------------------------";
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum en_operation { Show_Clients_List = 1, Add_New_Client = 2, Delete_Client = 3, Update_Client_info = 4, Find_Client = 5, Transactions = 6, Exit = 7 };

int main_menu_screen(string& user_operation, int& user_operation_number)
{
    cout << "==================================================================\n";
    cout << "                         main menu screen                         \n";
    cout << "==================================================================\n";
    cout << "       [1] Show Clients List.   \n";
    cout << "       [2] Add New Client.      \n";
    cout << "       [3] Delete CLient.       \n";
    cout << "       [4] Update Client Info.  \n";
    cout << "       [5] Find Client.         \n";
    cout << "       [6] Transactions.        \n";
    cout << "       [7] Exit.                \n";
    cout << "Your Operation: ";
    getline(cin >> ws, user_operation);
    while (user_operation != "1" && user_operation != "2" && user_operation != "3" && user_operation != "4" && user_operation != "5" && user_operation != "6" && user_operation != "7")
    {
        cout << "You Must Enter a Number from 1 to 7.\n";
        cin >> user_operation;
    }
    user_operation_number = stoi(user_operation);
    return user_operation_number;
}

enum en_transactions { Main_Menu = 0, Deposite = 1, Withdraw = 2, Total_Balances = 3 };

int Transactions_main_menu(string& User_Transaction, int& User_Transaction_Number)
{
    cout << "\n==================================================================\n";
    cout << "                      Transactions Menu Menu                      \n";
    cout << "==================================================================\n";
    cout << "       [1] Deposite.        \n";
    cout << "       [2] Withdraw.       \n";
    cout << "       [3] Total Balances. \n";
    cout << "       [0] Main Menu.      \n";
    cout << "Your Transaction: ";
    getline(cin >> ws, User_Transaction);
    while (User_Transaction != "1" && User_Transaction != "2" && User_Transaction != "3" && User_Transaction != "0")
    {
        cout << "You Must Enter a Number from 1 to 7.\n";
        cin >> User_Transaction;
    }
    User_Transaction_Number = stoi(User_Transaction);
    return User_Transaction_Number;
}

//Functions--------------------------------------------------------------------------------------------------
//operation-1-show clients list -----------------------------------------------------------------------------

string Split_Line_Words(string Line, string Delim, string& Line_data)
{
    short pos = Line.find(Delim);
    if (pos != std::string::npos)
    {
        Line_data = Line.substr(pos + 2, Line.length());
    }
    return Line;
}
sClient Load_words_to_struct(sClient& Client, vector <string>& Clients_data)
{

    Client.Name = Clients_data[0];
    Client.Phone = Clients_data[1];
    Client.AccountNumber = Clients_data[2];
    Client.AccountBalance = stod(Clients_data[3]);
    Client.PinCode = Clients_data[4];

    return Client;
}
vector <sClient> Convert_lines_to_record(string Line, vector <sClient>& V_Clients, vector <string>& Clients_data, sClient& Client)
{

    string Line_data = "";
    Split_Line_Words(Line, ":", Line_data);

    if (Line_data != "")
    {
        Clients_data.push_back(Line_data);
    }
    if (Line == ClientsFileSeperator)
    {
        Load_words_to_struct(Client, Clients_data);
        V_Clients.push_back(Client);
        Clients_data.clear();
    }

    return V_Clients;
}
void Load_Clients_Data_From_File_To_Vector(string ClientsFileName, vector <sClient>& V_Clients, vector <string>& Clients_data, sClient& Client)
{
    string Line = "";

    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in); //read Mode
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            Convert_lines_to_record(Line, V_Clients, Clients_data, Client);
        }
        MyFile.close();
    }

}
void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(16) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(16) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
}

//operation-2-add new client --------------------------------------------------------------------------------

void If_Account_Nnumber_Exist(vector <sClient>& V_Clients, sClient& new_client)
{
    for (int i = 0; i < size(V_Clients); i++)
    {
        if (V_Clients[i].AccountNumber == new_client.AccountNumber)
        {
            cout << "This Account Number Already Exits ,Please Enter Another Number:\n";
            system("color 4F"); //turn screen to red
            cout << "\a"; //make alert sound
            cin >> new_client.AccountNumber;
            i = -1; // you can use recusrion and make i = 0 
            //If_AccountNnumber_Exist(V_Clients , new_client); // recusrion line
        }

    }

}
sClient read_new_client(sClient& new_client, vector <sClient>& V_Clients, sClient& Client)
{
    cout << "" << "client's name: ";                       getline(cin >> ws, new_client.Name);  //ignore whiete spaces //cin >> client.Name;
    cout << new_client.Name << "'s phone: ";               cin >> new_client.Phone;
    cout << new_client.Name << "'s account number: ";      cin >> new_client.AccountNumber;
    If_Account_Nnumber_Exist(V_Clients, new_client);
    cout << new_client.Name << "'s account balance: ";     cin >> new_client.AccountBalance;
    while (cin.fail())
    {
        // user didn't input a number    
        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "Invalid input data type ,Enter a valid number:" << endl;
        cin >> new_client.AccountBalance;
    }
    cout << new_client.Name << "'s pincode: ";             cin >> new_client.PinCode;
    cout << "Client Added Successfully\n";
    system("color 2F"); //turn screen to green
    cout << "\a"; //make alert sound
    return new_client;
}
int read_how_many_clients(int& clients_iterator)
{
    string Line = "";
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in); // read mode
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            if (Line == ClientsFileSeperator)
            {
                clients_iterator++;
            }
        }
        MyFile.close();
    }
    return clients_iterator;
}
void add_record_to_file(string ClientsFileName, sClient client, int& clients_iterator)
{
    read_how_many_clients(clients_iterator);
    fstream myfile;
    myfile.open(ClientsFileName, ios::out | ios::app); // append mode
    if (myfile.is_open())
    {
        myfile << "client number " << clients_iterator << "\n";
        myfile << "name: " << client.Name << "\n";
        myfile << "phone: " << client.Phone << "\n";
        myfile << "account number: " << client.AccountNumber << "\n";
        myfile << "account balance: " << client.AccountBalance << "\n";
        myfile << "pincode: " << client.PinCode << "\n";
        myfile << ClientsFileSeperator << "\n";
        myfile.close();
    }

}

//operation-3-delete client ---------------------------------------------------------------------------------

bool Confirm_Deletion(vector <sClient>& vClients, sClient& Client, int i)
{
    char delete_ans = 'n';
    cout << "\ndo you want to delete this client? (y,n)";
    cin >> delete_ans;
    if (delete_ans == 'y' || delete_ans == 'Y')
    {
        cout << "\nClient Deleted Successfully.\n";
        system("color 2F"); //turn screen to green
        cout << "\a"; //make alert sound
        vClients[i].MarkForDelete = true;
        return true;
    }
    else
    {
        cout << "Operation Terminated.\n";
        system("color 4F"); //turn screen to red
        cout << "\a"; //make alert sound
        return false;
    }
    return false;
}
void Print_Client_Info_By_Account_Number(sClient& Client)
{
    cout << "\n\n-----------------------------------------------------";
    cout << "\n The following are the client details:\n";
    cout << "\n     Accout Number:   " << Client.AccountNumber;
    cout << "\n     Pin Code     :   " << Client.PinCode;
    cout << "\n     Name         :   " << Client.Name;
    cout << "\n     Phone        :   " << Client.Phone;
    cout << "\n     Account Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------------------------\n";
}
vector <sClient> Save_New_Vector_To_file(string ClientsFileName, vector <sClient>& V_Clients)
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
                MyFile << "Name: " << V_Clients[i].Name << "\n";
                MyFile << "Phone: " << V_Clients[i].Phone << "\n";
                MyFile << "Accout Number: " << V_Clients[i].AccountNumber << "\n";
                MyFile << "Account Balance: " << V_Clients[i].AccountBalance << "\n";
                MyFile << "Pin Code: " << V_Clients[i].PinCode << "\n";
                MyFile << ClientsFileSeperator << endl;
            }
        }
        MyFile.close();
    }
    return V_Clients;
}
char is_client_exist_to_delete(vector <sClient>& V_Clients, sClient& Client)
{
    string accout_number = "";
    cout << "please enter account number: ";
    cin >> accout_number;
    for (int i = 0; i < size(V_Clients); i++)
    {
        if (V_Clients[i].AccountNumber == accout_number)
        {
            Print_Client_Info_By_Account_Number(V_Clients[i]);
            Confirm_Deletion(V_Clients, Client, i);
            return true;
        }
    }
    cout << "client with account number " << accout_number << " is not found";
    system("color 4F"); //turn screen to red
    cout << "\a"; //make alert sound
    return false;
}

//operation-4 update client info ----------------------------------------------------------------------------

bool Confirm_Update(vector <sClient>& vClients, sClient& Client, int i)
{
    char update_ans = 'n';
    cout << "\nDo You Want To Update This Client? (y,n)";
    cin >> update_ans;
    if (update_ans == 'y' || update_ans == 'Y')
    {
        cout << "Enter Name: ";                 getline(cin >> ws, vClients[i].Name);
        cout << "Enter Account Balance: ";      cin >> vClients[i].AccountBalance;
        while (cin.fail())
        {
            // user didn't input a number    
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Invalid input data type ,Enter a valid number:" << endl;
            cin >> vClients[i].AccountBalance;
        }
        cout << "Enter Phone: ";                cin >> vClients[i].Phone;
        cout << "Enter Pin Code: ";             cin >> vClients[i].PinCode;
        cout << "\nClient Updated Successfully.\n";
        system("color 2F"); //turn screen to green
        cout << "\a"; //make alert sound
        return true;
    }
    else
    {
        cout << "Operation Terminated.\n";
        system("color 4F"); //turn screen to red
        cout << "\a"; //make alert sound
        return false;
    }
    return false;
}
vector <sClient> Save_Updated_Vector_To_file(string ClientsFileName, vector <sClient>& V_Clients)
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out); //overwrite
    if (MyFile.is_open())
    {
        for (int i = 0; i < size(V_Clients); i++)
        {
            MyFile << "client number " << i + 1 << "\n";
            MyFile << "Name: " << V_Clients[i].Name << "\n";
            MyFile << "Phone: " << V_Clients[i].Phone << "\n";
            MyFile << "Accout Number: " << V_Clients[i].AccountNumber << "\n";
            MyFile << "Account Balance: " << V_Clients[i].AccountBalance << "\n";
            MyFile << "Pin Code: " << V_Clients[i].PinCode << "\n";
            MyFile << ClientsFileSeperator << endl;
        }
        MyFile.close();
    }
    return V_Clients;
}
char Is_Client_Exist_To_Update(vector <sClient>& V_Clients, sClient& Client)
{
    string accout_number = "";
    cout << "please enter account number: ";
    cin >> accout_number;
    for (int i = 0; i < size(V_Clients); i++)
    {
        if (V_Clients[i].AccountNumber == accout_number)
        {
            Print_Client_Info_By_Account_Number(V_Clients[i]);
            Confirm_Update(V_Clients, Client, i);
            return true;
        }
    }
    cout << "client with account number " << accout_number << " is not found";
    system("color 4F"); //turn screen to red

    return false;
}

//operation-5 find client -----------------------------------------------------------------------------------

char is_client_exist_to_show_data(vector <sClient>& V_Clients, sClient& Client)
{
    string accout_number = "";
    cout << "please enter account number: ";
    cin >> accout_number;
    for (int i = 0; i < size(V_Clients); i++)
    {
        if (V_Clients[i].AccountNumber == accout_number)
        {
            Client = V_Clients[i];
            Print_Client_Info_By_Account_Number(V_Clients[i]);
            system("color 2F"); //turn screen to green
            cout << "\a"; //make alert sound
            return true;
        }
    }
    cout << "client with account number " << accout_number << " is not found";
    system("color 4F"); //turn screen to red
    cout << "\a"; //make alert sound
    return false;
}

//operation-6-Transactions-----------------------------------------------------------------------------------

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

//Operations-------------------------------------------------------------------------------------------------

//operation-1-Show_Clients_List_Operation--------------------------------------------------------------------
void Show_Clients_List_Operation()
{
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    PrintAllClientsData(V_Clients);

}

//operation-2-Add_New_Client---------------------------------------------------------------------------------
void Add_New_Client_Operation()
{
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    sClient new_client;
    int clients_iterator = 1;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    read_new_client(new_client, V_Clients, Client);
    add_record_to_file(ClientsFileName, new_client, clients_iterator);
}

//operation-3-Delete_Client----------------------------------------------------------------------------------
void Delete_Client_Operation()
{
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    is_client_exist_to_delete(V_Clients, Client);
    Save_New_Vector_To_file(ClientsFileName, V_Clients);
}

//operation-4-Update_Client_Info-----------------------------------------------------------------------------
void Update_Client_Info_Operation()
{
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    Is_Client_Exist_To_Update(V_Clients, Client);
    Save_Updated_Vector_To_file(ClientsFileName, V_Clients);
}

//operation-5-Find_Client------------------------------------------------------------------------------------
void Find_Client_Operation()
{
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    is_client_exist_to_show_data(V_Clients, Client);

}

//operation-6-Transactions-----------------------------------------------------------------------------------
void Deposite_Operation(sClient& Client)
{
    char insurance = 'n';
    double Deposite_Amount = 0;
    cout << "Please Enter Deposite Amount: ";
    cin >> Deposite_Amount;
    while (cin.fail())
    {
        // user didn't input a number    
        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "Invalid input data type ,Enter a valid number:" << endl;
        cin >> Deposite_Amount;
    }
    cout << "Are You Sure You Want To Deposite This Amount?\n";
    cin >> insurance;
    if (insurance == 'y' || insurance == 'Y')
    {
        Client.AccountBalance += Deposite_Amount;
        cout << "Successful Transaction. \n";
        cout << "\nNew Balance = " << Client.AccountBalance << "\n";
        system("color 2F"); //turn screen to green
    }
    else
    {
        cout << "\nTransaction Terminated.\n";
        system("color 4F"); //turn screen to red
    }

}
//-----------------------------------------------------------------------------------------------------------
void Withdraw_Operation(sClient& Client)
{
    char insurance = 'n';
    double Withdraw_Amount = 0;
    cout << "Please Enter Withdraw Amount: ";
    cin >> Withdraw_Amount;
    while (cin.fail())
    {
        // user didn't input a number    
        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "Invalid input data type ,Enter a valid number:" << endl;
        cin >> Withdraw_Amount;
    }

    while (Withdraw_Amount > Client.AccountBalance)
    {
        cout << "Withdraw Amount Exceds Your Balance. \n You Can Withdraw Up To = " << Client.AccountBalance << "\n Withdraw Amount:";
        cin >> Withdraw_Amount;
        cout << endl;
    }
    cout << "Are You Sure You Want To Withdraw This Amount?\n";
    cin >> insurance;
    if (insurance == 'y' || insurance == 'Y')
    {
        Client.AccountBalance -= Withdraw_Amount;
        cout << "Successful Transaction. \n";
        cout << "\nNew Balance = " << Client.AccountBalance << "\n";
        system("color 2F"); //turn screen to green
    }
    else
    {
        cout << "\nTransaction Terminated.\n";
        system("color 4F"); //turn screen to red
    }
}
//-----------------------------------------------------------------------------------------------------------
void Print_Balances_Clients_Record(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void Print_All_Clients_Balances(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        Print_Balances_Clients_Record(Client);
        cout << endl;
    }
    cout << "\n__________________________________________________________________";
    cout << "__________________________________________________\n" << endl;
}
//-----------------------------------------------------------------------------------------------------------
void User_Transactions_Navigator(string& User_Transaction, int& User_Transaction_Number, sClient& Client, vector <sClient>& V_Clients)
{
    switch (User_Transaction_Number)
    {
    case en_transactions::Deposite:
        system("cls");
        if (is_client_exist_to_show_data(V_Clients, Client))
        {
            Deposite_Operation(Client);
        }
        break;

    case en_transactions::Withdraw:
        system("cls");
        if (is_client_exist_to_show_data(V_Clients, Client))
        {
            Withdraw_Operation(Client);
        }
        break;

    case en_transactions::Total_Balances:
        system("cls");
        Print_All_Clients_Balances(V_Clients);
        break;

    case en_transactions::Main_Menu:
        system("cls");
        break;
    }
}
string User_Transaction = "7";
void Transactions_main()
{ 
    int User_Transaction_Number = 0;
    vector <sClient> V_Clients;
    vector <string> Clients_data;
    sClient Client;
    Load_Clients_Data_From_File_To_Vector(ClientsFileName, V_Clients, Clients_data, Client);
    Transactions_main_menu(User_Transaction, User_Transaction_Number);
    User_Transactions_Navigator(User_Transaction, User_Transaction_Number, Client, V_Clients);
    refresh_vector_after_transaction(V_Clients, Client);
    Save_New_Vector_To_file(ClientsFileName, V_Clients);

}

void user_operation_navigator(string& user_operation, int& user_operation_number)
{
    switch (user_operation_number)
    {
    case en_operation::Show_Clients_List:
        system("cls");
        Show_Clients_List_Operation();
        break;

    case en_operation::Add_New_Client:
        system("cls");
        Add_New_Client_Operation();
        break;

    case en_operation::Delete_Client:
        system("cls");
        Delete_Client_Operation();
        break;

    case en_operation::Update_Client_info:
        system("cls");
        Update_Client_Info_Operation();
        break;

    case en_operation::Find_Client:
        system("cls");
        Find_Client_Operation();
        break;

    case en_operation::Transactions:
        system("cls");
        Transactions_main();
        break;

    case en_operation::Exit:
        system("cls");
        cout << "\n     Thank You For Using Our Service.\n";
        break;
    }
}

int main()
{
    jump:
    string user_operation = "0";
    char answer = 'y';
    int user_operation_number = 0;
    while ((answer == 'y' || answer == 'Y') && user_operation != "7")
    {

        main_menu_screen(user_operation, user_operation_number);
        user_operation_navigator(user_operation, user_operation_number);
        if (user_operation_number == en_operation::Exit)
        {
            break;
        }
        else if (User_Transaction == "0")
        {
            goto jump;
        }
        else
        {
            cout << "\nDo You Want To Do Anything Else?\n";
            cin >> answer;
            system("color 0F");
            system("cls");
            cout << "\a"; //make alert sound
        }
        
    }
    cout << "\n     Program Closed.\n";
    return 0;
}
