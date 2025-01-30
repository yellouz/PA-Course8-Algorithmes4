#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const string ClientsFile = "Clients.txt";
const string UsersFile = "Users.txt";

enum enMainMenuChoice { Show_Client_List = 1, Add_New_Client, Delete_Client, Update_Client_Info, Find_Client, Transactions, Manage_Users, Logout };
enum enTransactionsMenuChoice { Deposit = 1, Withdraw, Total_Balances, Main_Menu };
enum enUsersMenuChoice { List_Users = 1, Add_New_User, Delete_User, Update_User, Find_User, Main_Menu_Again };

enMainMenuChoice GetMainMenuChoice()
{
    int Choice;

    cout << "Choose What you want to do ? [1 to 6] : ";
    cin >> Choice;
    
    return enMainMenuChoice(Choice);
}

enTransactionsMenuChoice GetTransactionsMenuChoice()
{
    int Choice;

    cout << "Choose What you want to do ? [1 to 4] : ";
    cin >> Choice;
    
    return enTransactionsMenuChoice(Choice);
}

enUsersMenuChoice GetUsersMenuChoice()
{
    int Choice;

    cout << "Choose What you want to do ? [1 to 6] : ";
    cin >> Choice;
    
    return enUsersMenuChoice(Choice);
}

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool ToDelete = false;
};

sClient GetClientInfos()
{
    sClient Client;
    cout << "\nPlease Enter Client's Data : \n";

    cout << "Account Number : ";
    getline(cin >> ws, Client.AccountNumber);

    cout << "Pin Code : ";
    getline(cin >> ws, Client.PinCode);

    cout << "Name : ";
    getline(cin >> ws, Client.Name);

    cout << "Phone Number : ";
    getline(cin >> ws, Client.Phone);

    cout << "Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

struct sUser
{
    string Name;
    string Password;
    int Permissions = 0;
    bool ToDelete = false;
};

sUser GetUserInfos()
{
    sUser User;
    cout << "\nPlease Enter User's Data : \n";

    cout << "Username : ";
    getline(cin >> ws, User.Name);

    cout << "Password : ";
    getline(cin >> ws, User.Password);

    return User;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

sClient ConvertLinetoRecord(string Line, string Seperator)
{
    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); //cast string to double

    return Client;
}

void SaveClientsDataToFile(vector<sClient> &vClients)
{
    fstream MyFile;
    MyFile.open(ClientsFile, ios::out);

    string Line;

    if (MyFile.is_open())
    {
        for(sClient &Client : vClients)
        {
            if (Client.ToDelete == false)
            {
                Line = ConvertRecordToLine(Client, "#//#");
                MyFile << Line << endl;
            }
        }
        
    }

    MyFile.close();
}

vector<sClient> ReadClientsDataFromFile(string ClientsFile)
{
    fstream MyFile;
    MyFile.open(ClientsFile, ios::in);

    vector <sClient> vClients;

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line, "#//#");
            vClients.push_back(Client);
        }
        
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecord(sClient Client)
{
    cout << "\n\nThe following are the client details:";
    cout << "\n___________________________________";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n___________________________________" << endl;
}

bool isAccountNumberAlreadyExists(vector <sClient> &vClients, sClient Client)
{
    for(sClient &C : vClients)
    {
        if (C.AccountNumber == Client.AccountNumber)
        {
            return true;
        }
    }
    return false;
}

void GoBackToMainMenue(vector<sClient> &vClients, int UserPermissions);

void MainMenu(int UserPermissions);

void GoBackToTransactionsMenu(vector<sClient> &vClients, int UserPermissions);

void TransactionsMenu(vector <sClient> &vClients, int UserPermissions);

void GoBackToUsersMenu(vector <sUser> &vClients, int UserPermissions);

void UsersMenu(int UserPermissions);

void Login();

void CheckUserPermissions(int UserPermissions, enMainMenuChoice Choice);

void ShowClientList(vector <sClient> &vClients, int UserPermissions)
{
    CheckUserPermissions(UserPermissions, enMainMenuChoice::Show_Client_List);

    system("cls");
    cout << "\t\t\t\t\t\t Client List (" << vClients.size() << ") Client(s). \n";
    cout << "________________________________________________________________________________________________________________________\n";
    cout << setw(20) << left << "| Account Number";
    cout << setw(20) << left << "| Pin Code";
    cout << setw(50) << left << "| Client Name";
    cout << setw(20) << left << "| Phone";
    cout << setw(20) << left << "| Balance";
    cout << endl;
    cout << "________________________________________________________________________________________________________________________\n";
    
    for(sClient &Client : vClients)
    {
        cout << setw(20) << left << Client.AccountNumber;
        cout << setw(20) << left << Client.PinCode;
        cout << setw(50) << left << Client.Name;
        cout << setw(20) << left << Client.Phone;
        cout << setw(20) << left << Client.AccountBalance;
        cout << endl;
    }

    cout << "________________________________________________________________________________________________________________________\n";

    GoBackToMainMenue(vClients, UserPermissions);
}

void AddNewClient(vector <sClient> &vClients, int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Add_New_Client);

    system("cls");

    cout << "___________________________________" << endl;
    cout << "         Add New Client Screen     " << endl;
    cout << "___________________________________" << endl;
    cout << "Adding New Client : " << endl;

    sClient Client;

    cout << "\nAccount Number : ";
    getline(cin >> ws, Client.AccountNumber);

    while (isAccountNumberAlreadyExists(vClients, Client))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exists, enter another Account Number : ";
        getline(cin >> ws, Client.AccountNumber);   
    }
    
    cout << "Pin Code : ";
    getline(cin >> ws, Client.PinCode);

    cout << "Name : ";
    getline(cin >> ws, Client.Name);

    cout << "Phone Number : ";
    getline(cin >> ws, Client.Phone);

    cout << "Account Balance : ";
    cin >> Client.AccountBalance;

    vClients.push_back(Client);
    //SaveDataToFile(Client);

    cout << "\nClient Added Successfully, Do You want to add more clients? [Y/N] ";
    char Answer;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        AddNewClient(vClients, UserPermissions);
    }
    else
    {
        GoBackToMainMenue(vClients, UserPermissions);
    }
}

void DeleteClient(vector <sClient> &vClients, int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Delete_Client);

    system("cls");

    cout << "___________________________________" << endl;
    cout << "         Delete Client Screen      " << endl;
    cout << "___________________________________" << endl;

    string AccountNumberToDelete;
    cout << "Please Enter the Account Number you want to Delete : ";
    getline(cin >> ws, AccountNumberToDelete);

    for(sClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumberToDelete)
        {
            PrintClientRecord(Client);
            cout << "\nAre you sure you want to delete this client ? [Y/N] ";
            char Answer;
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {                
                Client.ToDelete = true;
                cout << "\nClient Deleted Successfully.";

                GoBackToMainMenue(vClients, UserPermissions);
            }
            else
            {
                GoBackToMainMenue(vClients, UserPermissions);
            }
        }
    }
    
    cout << "Account Number Not Found ! \n";

    GoBackToMainMenue(vClients, UserPermissions);
}

void UpdateClientInfo(vector <sClient> &vClients, int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Update_Client_Info);

    system("cls");

    cout << "___________________________________" << endl;
    cout << "     Update Client Info Screen     " << endl;
    cout << "___________________________________" << endl;

    string AccountNumberToUpdate;
    cout << "Please Enter the Account Number you want to Update : ";
    getline(cin >> ws, AccountNumberToUpdate);

    for(sClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumberToUpdate)
        {
            PrintClientRecord(Client);
            cout << "\nAre you sure you want to update this client ? [Y/N] ";
            char Answer;
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {             
                cout << "Pin Code : ";
                getline(cin >> ws, Client.PinCode);

                cout << "Name : ";
                getline(cin >> ws, Client.Name);

                cout << "Phone Number : ";
                getline(cin >> ws, Client.Phone);

                cout << "Account Balance : ";
                cin >> Client.AccountBalance;

                cout << "\nClient Updated Successfully.";

                GoBackToMainMenue(vClients, UserPermissions);
            }
            else
            {
                GoBackToMainMenue(vClients, UserPermissions);
            }
        }
    }
    
    cout << "Account Number Not Found ! \n";

    GoBackToMainMenue(vClients, UserPermissions);
}

void FindClient(vector <sClient> &vClients, int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Find_Client);

    system("cls");

    cout << "___________________________________" << endl;
    cout << "        Find Client Screen         " << endl;
    cout << "___________________________________" << endl;

    string AccountNumberToLookFor;
    cout << "Please Enter the Account Number you want to Look for : ";
    getline(cin >> ws, AccountNumberToLookFor);

    for(sClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumberToLookFor)
        {
            PrintClientRecord(C);
            GoBackToMainMenue(vClients, UserPermissions);
        }
    }
    
    cout << "Account Number Not Found ! \n";

    GoBackToMainMenue(vClients, UserPermissions);
}

void GoBackToMainMenue(vector<sClient> &vClients, int UserPermissions)
{
    SaveClientsDataToFile(vClients);

    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    MainMenu(UserPermissions);
}

void ShowPermissionsErrorMsg()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "Access Denied," << endl;
    cout << "You Don't Have Permissions to do this," << endl;
    cout << "Please Contact Your Admin." << endl;
    cout << "___________________________________" << endl;

    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
}

void CheckUserPermissions(int UserPermissions, enMainMenuChoice Choice)
{
    if (UserPermissions == -1)
    {
        return;
    }
   
    switch (Choice)
    {
    case enMainMenuChoice::Show_Client_List:
        if (UserPermissions & 1)
        {
            return;
        }
        
        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;
    
    case enMainMenuChoice::Add_New_Client:
        if (UserPermissions & (1 << 1))
        {
            return;
        }
        
        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;

    case enMainMenuChoice::Delete_Client:
        if (UserPermissions & (1 << 2))
        {
            return;
        }
        
        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;

    case enMainMenuChoice::Update_Client_Info:
        if (UserPermissions & (1 << 3))
        {
            return;
        }

        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;

    case enMainMenuChoice::Find_Client:
        if (UserPermissions & (1 << 4))
        {
            return;
        }

        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;

    case enMainMenuChoice::Transactions:
        if (UserPermissions & (1 << 5))
        {
            return;
        }

        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
        break;
        
    case enMainMenuChoice::Manage_Users:
        if (UserPermissions & (1 << 6))
        {
            return;
        }

        ShowPermissionsErrorMsg();
        MainMenu(UserPermissions);
    
    default:
        MainMenu(UserPermissions);
        break;
    }
}

void MainMenu(int UserPermissions)
{
    system("cls");
    cout << "========================================\n";
    cout << "               Main Menu                \n";
    cout << "========================================\n";
    cout << "\t [1] Show Client List. \n";
    cout << "\t [2] Add New Client. \n";
    cout << "\t [3] Delete Client. \n";
    cout << "\t [4] Update Client Info. \n";
    cout << "\t [5] Find Client. \n";
    cout << "\t [6] Transactions. \n";
    cout << "\t [7] Manage Users. \n";
    cout << "\t [8] Logout. \n";
    cout << "========================================\n";
    enMainMenuChoice Choice = GetMainMenuChoice();

    vector <sClient> vClients = ReadClientsDataFromFile(ClientsFile);

    switch (Choice)
    {
        case enMainMenuChoice::Show_Client_List:
            ShowClientList(vClients, UserPermissions);
            break;
            
        case enMainMenuChoice::Add_New_Client:
            AddNewClient(vClients, UserPermissions);
            break;

        case enMainMenuChoice::Delete_Client:
            DeleteClient(vClients, UserPermissions);
            break;

        case enMainMenuChoice::Update_Client_Info:
            UpdateClientInfo(vClients, UserPermissions);
            break;

        case enMainMenuChoice::Find_Client:
            FindClient(vClients, UserPermissions);
            break;

        case enMainMenuChoice::Transactions:
            TransactionsMenu(vClients, UserPermissions);
            break;

        case enMainMenuChoice::Manage_Users:
            UsersMenu(UserPermissions);

        case enMainMenuChoice::Logout:
            Login();

        /*
            system("cls");
            cout << "_________________________________" << endl;
            cout << "       Program Ends :-)          " << endl;
            cout << "_________________________________" << endl;
            system("pause>0");
            exit(0);
            break;
        */

        default:
            MainMenu(UserPermissions);
            break;
    }
}

void TransactionsDeposit(vector<sClient> &vClients, int UserPermissions)
{
    system("cls");

    cout << "___________________________________" << endl;
    cout << "          Deposit Screen           " << endl;
    cout << "___________________________________" << endl;

    string AccountNumberToLookFor;
    cout << "Please Enter the Account Number : ";
    getline(cin >> ws, AccountNumberToLookFor);

    for(sClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumberToLookFor)
        {
            PrintClientRecord(Client);
            
            cout << "Enter Deposit Amount : ";
            double DepositAmount;
            cin >> DepositAmount;

            cout << "\nAre you sure you want to Perform this transaction ? [Y/N] ";
            char Answer;
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                Client.AccountBalance += DepositAmount;
                cout << "\nDone Successfully.. New Balance : " << Client.AccountBalance;
                GoBackToTransactionsMenu(vClients, UserPermissions);
            }
            else
                GoBackToTransactionsMenu(vClients, UserPermissions);
        }
    }
    
    cout << "Account Number Not Found ! \n";

    TransactionsDeposit(vClients, UserPermissions);

}

void TransactionsWithdraw(vector <sClient> &vClients, int UserPermissions)
{
    system("cls");

    cout << "___________________________________" << endl;
    cout << "         Withdraw Screen           " << endl;
    cout << "___________________________________" << endl;

    string AccountNumberToLookFor;
    cout << "Please Enter the Account Number : ";
    getline(cin >> ws, AccountNumberToLookFor);

    for(sClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumberToLookFor)
        {
            PrintClientRecord(Client);
            
            cout << "Enter Withdraw Amount : ";
            double WithdrawAmount;
            cin >> WithdrawAmount;

            cout << "\nAre you sure you want to Perform this transaction ? [Y/N] ";
            char Answer;
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                Client.AccountBalance -= WithdrawAmount;
                cout << "\nDone Successfully.. New Balance : " << Client.AccountBalance;
                GoBackToTransactionsMenu(vClients, UserPermissions);
            }
            else
                GoBackToTransactionsMenu(vClients, UserPermissions);
        }
    }
    
    cout << "Account Number Not Found ! \n";

    TransactionsWithdraw(vClients, UserPermissions);
}

void TrasactionsTotalBalances(vector <sClient> &vClients, int UserPermissions)
{
    system("cls");
    cout << "\t\t\t\t\t\t Balance List (" << vClients.size() << ") Client(s). \n";
    cout << "________________________________________________________________________________________________________________________\n";
    cout << setw(30) << left << "| Account Number";
    cout << setw(50) << left << "| Client Name";
    cout << setw(30) << left << "| Balance";
    cout << endl;
    cout << "________________________________________________________________________________________________________________________\n";
    
    double TotalBalances = 0;

    for(sClient &Client : vClients)
    {
        cout << setw(20) << left << Client.AccountNumber;
        cout << setw(50) << left << Client.Name;
        cout << setw(20) << left << Client.AccountBalance;
        cout << endl;

        TotalBalances += Client.AccountBalance;
    }

    cout << "________________________________________________________________________________________________________________________\n";

    cout << "\t\t\t\t\t\t Total Balances = " << TotalBalances << endl;

    GoBackToTransactionsMenu(vClients, UserPermissions);
}

void GoBackToTransactionsMenu(vector<sClient> &vClients, int UserPermissions)
{
    SaveClientsDataToFile(vClients);

    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");

    TransactionsMenu(vClients, UserPermissions);
}

void TransactionsMenu(vector <sClient> &vClients, int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Transactions);

    system("cls");
    cout << "========================================\n";
    cout << "         Transactions Main Menu         \n";
    cout << "========================================\n";
    cout << "\t [1] Deposit. \n";
    cout << "\t [2] Withdraw. \n";
    cout << "\t [3] Total Balances. \n";
    cout << "\t [4] Main Menu. \n";
    cout << "========================================\n";

    enTransactionsMenuChoice Choice = GetTransactionsMenuChoice();

    switch (Choice)
    {
        case enTransactionsMenuChoice::Deposit:
            TransactionsDeposit(vClients, UserPermissions);
            break;
        
        case enTransactionsMenuChoice::Withdraw:
            TransactionsWithdraw(vClients, UserPermissions);
            break;

        case enTransactionsMenuChoice::Total_Balances:
            TrasactionsTotalBalances(vClients, UserPermissions);
            break;

        case enTransactionsMenuChoice::Main_Menu:
            MainMenu(UserPermissions);
            break;

        default:
            TransactionsMenu(vClients, UserPermissions);
            break;
    }
}

bool isUserNameAlreadyExists(vector <sUser> &vUsers, sUser User)
{
    for(sUser &U : vUsers)
    {
        if (U.Name == User.Name)
        {
            return true;
        }
    }
    return false;
}

void PrintUserRecord(sUser User)
{
    cout << "\n\nThe following are the User details:";
    cout << "\n___________________________________";
    cout << "\nUsername: " << User.Name;
    cout << "\nPassword : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n___________________________________" << endl;
}

string ConvertRecordToLine(sUser User, string Seperator = "#//#")
{
    string stUserRecord = "";
    stUserRecord += User.Name + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permissions);

    return stUserRecord;
}

sUser ConvertLinetoRecord(string Line)
{
    string Seperator = "#//#";

    sUser User;
    vector <string> vUsersData;

    vUsersData = SplitString(Line, Seperator);

    User.Name = vUsersData[0];
    User.Password = vUsersData[1];
    User.Permissions = stoi(vUsersData[2]);

    return User;
}

void SaveUsersDataToFile(vector <sUser> &vUsers)
{
    fstream MyFile;
    MyFile.open(UsersFile, ios::out);

    string Line;

    if (MyFile.is_open())
    {
        for(sUser &User : vUsers)
        {
            if (User.ToDelete == false)
            {
                Line = ConvertRecordToLine(User, "#//#");
                MyFile << Line << endl;
            }
        }
        
    }

    MyFile.close();
}

vector <sUser> ReadUsersDataFromFile(string UsersFile)
{
    fstream MyFile;
    MyFile.open(UsersFile, ios::in);

    vector <sUser> vUsers;

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLinetoRecord(Line);
            vUsers.push_back(User);
        }
        
        MyFile.close();
    }
    return vUsers;
}

void ListUsers(vector <sUser> &vUsers, int UserPermissions)
{
    system("cls");
    cout << "\t\t\t\t\t\t Users List (" << vUsers.size() << ") Users(s). \n";
    cout << "________________________________________________________________________________________________________________________\n";
    cout << setw(30) << left << "| UserName";
    cout << setw(50) << left << "| Password";
    cout << setw(30) << left << "| Permissions";
    cout << endl;
    cout << "________________________________________________________________________________________________________________________\n";

    for(sUser &User : vUsers)
    {
        cout << setw(20) << left << User.Name;
        cout << setw(50) << left << User.Password;
        cout << setw(20) << left << User.Permissions;
        cout << endl;
    }

    cout << "________________________________________________________________________________________________________________________\n";

    GoBackToUsersMenu(vUsers, UserPermissions);
}

void AddNewUser(vector <sUser> &vUsers, int UserPermissions)
{
    system("cls");

    cout << "___________________________________" << endl;
    cout << "         Add New User Screen       " << endl;
    cout << "___________________________________" << endl;
    cout << "Adding New User : " << endl;

    sUser User;

    cout << "\nUserName : ";
    getline(cin >> ws, User.Name);

    while (isUserNameAlreadyExists(vUsers, User))
    {
        cout << "User with [" << User.Name << "] already exists, enter another UserName : ";
        getline(cin >> ws, User.Name);   
    }
    
    cout << "Password : ";
    getline(cin >> ws, User.Password);

    cout << "\nDo You Want To Give Full Access? [Y/N] ";
    char Answer;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        User.Permissions = -1;
    }
    else
    {
        cout << "\nDo You Want To Give Access To : \n";

        cout << "\nShow Client List? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 1;
        }

        cout << "\nAdd New Client? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 2;
        }

        cout << "\nDelete Client? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 4;
        }

        cout << "\nUpdate Client? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 8;
        }

        cout << "\nFind Client? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 16;
        }

        cout << "\nTransactions? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 32;
        }

        cout << "\nManage Users? [Y/N] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            User.Permissions += 64;
        }
    }

    vUsers.push_back(User);

    cout << "\nUser Added Successfully, Do You want to add more Users? [Y/N] ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        AddNewUser(vUsers, UserPermissions);
    }
    else
    {
        GoBackToUsersMenu(vUsers, UserPermissions);
    }
}

void DeleteUser(vector <sUser> &vUsers, int UserPermissions)
{
    system("cls");

    cout << "___________________________________" << endl;
    cout << "         Delete User Screen        " << endl;
    cout << "___________________________________" << endl;

    string UsernameToDelete;
    cout << "Please Enter the Username you want to Delete : ";
    getline(cin >> ws, UsernameToDelete);

    if (UsernameToDelete == "Admin")
    {
        cout << "This User can't Be Deleted!";
        GoBackToUsersMenu(vUsers, UserPermissions);
    }
    else
    {
        for(sUser &User : vUsers)
        {
            if (User.Name == UsernameToDelete)
            {
                PrintUserRecord(User);
                cout << "\nAre you sure you want to delete this user ? [Y/N] ";
                char Answer;
                cin >> Answer;

                if (Answer == 'y' || Answer == 'Y')
                {                
                    User.ToDelete = true;
                    cout << "\nUser Deleted Successfully.";
                }

                GoBackToUsersMenu(vUsers, UserPermissions);
            }
        }
    
    cout << "Username Not Found ! \n";
    GoBackToUsersMenu(vUsers, UserPermissions);

    }
}

void UpdateUser(vector <sUser> &vUsers, int UserPermissions)
{
    system("cls");

    cout << "___________________________________" << endl;
    cout << "     Update User Info Screen       " << endl;
    cout << "___________________________________" << endl;

    string UsernameToUpdate;
    cout << "Please Enter the Username you want to Update : ";
    getline(cin >> ws, UsernameToUpdate);

    for(sUser &User : vUsers)
    {
        if (User.Name == UsernameToUpdate)
        {
            PrintUserRecord(User);
            cout << "\nAre you sure you want to update this User ? [Y/N] ";
            char Answer;
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {             
                User.Permissions = 0;

                cout << "\nPassword : ";
                getline(cin >> ws, User.Password);

                cout << "\nDo You Want To Give Full Access? [Y/N] ";
                char Answer;
                cin >> Answer;

                if (Answer == 'y' || Answer == 'Y')
                {
                    User.Permissions = -1;
                }
                else
                {
                    cout << "\nDo You Want To Give Access To : \n";

                    cout << "\nShow Client List? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 1;
                    }

                    cout << "\nAdd New Client? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 2;
                    }

                    cout << "\nDelete Client? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 4;
                    }

                    cout << "\nUpdate Client? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 8;
                    }

                    cout << "\nFind Client? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 16;
                    }

                    cout << "\nTransactions? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 32;
                    }

                    cout << "\nManage Users? [Y/N] ";
                    cin >> Answer;
                    if (Answer == 'y' || Answer == 'Y')
                    {
                        User.Permissions += 64;
                    }
                }
            }

            GoBackToUsersMenu(vUsers, UserPermissions);
        }
    }
    
    cout << "Username Not Found ! \n";

    GoBackToUsersMenu(vUsers, UserPermissions);
}

void FindUser(vector <sUser> &vUsers, int UserPermissions)
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "         Find User Screen          " << endl;
    cout << "___________________________________" << endl;

    string UsernameToLookFor;
    cout << "Please Enter the Username you want to Look for : ";
    getline(cin >> ws, UsernameToLookFor);

    for(sUser &User : vUsers)
    {
        if (User.Name == UsernameToLookFor)
        {
            PrintUserRecord(User);
            GoBackToUsersMenu(vUsers, UserPermissions);
        }
    }

    cout << "Username Not Found ! \n";
    GoBackToUsersMenu(vUsers, UserPermissions); 
}

void GoBackToUsersMenu(vector <sUser> &vUsers, int UserPermissions)
{
    SaveUsersDataToFile(vUsers);

    cout << "\n\nPress any key to go back to Users Menue...";
    system("pause>0");

    UsersMenu(UserPermissions);
}

void UsersMenu(int UserPermissions)
{

    CheckUserPermissions(UserPermissions, enMainMenuChoice::Manage_Users);

    system("cls");
    cout << "========================================\n";
    cout << "            Users Main Menu             \n";
    cout << "========================================\n";
    cout << "\t [1] List Users. \n";
    cout << "\t [2] Add New User. \n";
    cout << "\t [3] Delete User. \n";
    cout << "\t [4] Update User. \n";
    cout << "\t [5] Find User. \n";
    cout << "\t [6] Main Menu. \n";
    cout << "========================================\n";

    enUsersMenuChoice Choice = GetUsersMenuChoice();

    vector <sUser> vUsers = ReadUsersDataFromFile(UsersFile);

    switch (Choice)
    {
        case enUsersMenuChoice::List_Users:
            ListUsers(vUsers, UserPermissions);
            break;
        
        case enUsersMenuChoice::Add_New_User:
            AddNewUser(vUsers, UserPermissions);
            break;

        case enUsersMenuChoice::Delete_User:
            DeleteUser(vUsers, UserPermissions);
            break;

        case enUsersMenuChoice::Update_User:
            UpdateUser(vUsers, UserPermissions);
            break;

        case enUsersMenuChoice::Find_User:
            FindUser(vUsers, UserPermissions);
            break;

        case enUsersMenuChoice::Main_Menu_Again:
            MainMenu(UserPermissions);
            break;

        default:
            UsersMenu(UserPermissions);
            break;
    }
}

void Login()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "            Login Screen           " << endl;
    cout << "___________________________________" << endl;


    vector <sUser> vUsers = ReadUsersDataFromFile(UsersFile);
    sUser LoginUser = GetUserInfos();
    
    for(sUser &User : vUsers)
    {
        if ((User.Name == LoginUser.Name) && (User.Password == LoginUser.Password))
        {
            MainMenu(User.Permissions);
        }
    }

    Login();
}

int main()
{
    Login();
}