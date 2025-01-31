#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const string ClientsFile = "Clients.txt";

enum enMainMenuChoice { mQuick_Withdraw = 1, mNormal_Withdraw, mDeposit, mCheck_Balance, mLogout };

enMainMenuChoice GetMainMenuChoice()
{
    short Choice;

    std::cout << "Choose What you want to do ? [1 to 5] : ";
    cin >> Choice;
    
    return enMainMenuChoice(Choice);
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

sClient CurrentClient;

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

void SaveClientsDataToFile(vector <sClient> &vClients)
{
    fstream MyFile;
    MyFile.open(ClientsFile, ios::out);

    string Line;

    if (MyFile.is_open())
    {
        for(sClient &Client : vClients)
        {
            if (Client.AccountNumber == CurrentClient.AccountNumber)
            {
                Line = ConvertRecordToLine(CurrentClient, "#//#");
            }
            else
            {
                Line = ConvertRecordToLine(Client, "#//#");
            }
            
            MyFile << Line << endl;

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

        while (std::getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line, "#//#");
            vClients.push_back(Client);
        }
        
        MyFile.close();
    }
    return vClients;
}

void GoBackToMainMenue();

void MainMenu();

void QuickWithdraw()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "        Quick Withdraw Screen      " << endl;
    cout << "___________________________________" << endl;
    cout << "\t [1] 20  " << "\t [2] 50  " << endl;
    cout << "\t [3] 100 " << "\t [4] 200 " << endl;
    cout << "\t [5] 400 " << "\t [6] 600 " << endl;
    cout << "\t [7] 800 " << "\t [8] 1000" << endl;
    cout << "\t [9] Exit" << endl;
    cout << "___________________________________" << endl;

    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;

    short choice;
    short MenuAmount[] = {20,50,100,200,400,600,800,1000};
    do
    {
        cout << "Choose What to Withdraw from [1] to [8] : ";
        cin >> choice;

        if (choice == 9)
        {
            return;
        }

        if ((choice > 0 && choice < 9) && (CurrentClient.AccountBalance > MenuAmount[choice-1]))
        {
            break;
        }
        
        
    } while (true);
    
    cout << "Are you sure you want to perform this Transaction? [Y/N] : ";
    char Answer;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        switch (choice)
        {
        case 1:
            CurrentClient.AccountBalance -= 20;
            break;

        case 2:
            CurrentClient.AccountBalance -= 50;
            break;

        case 3:
            CurrentClient.AccountBalance -= 100;
            break;

        case 4:
            CurrentClient.AccountBalance -= 200;
            break;

        case 5:
            CurrentClient.AccountBalance -= 400;
            break;

        case 6:
            CurrentClient.AccountBalance -= 600;
            break;

        case 7:
            CurrentClient.AccountBalance -= 800;
            break;

        case 8:
            CurrentClient.AccountBalance -= 1000;
            break;
        
        default:
            break;
        }

        cout << "\nDone Successfully, New Balance : " << CurrentClient.AccountBalance;
    }
}

void NormalWithdraw()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "       Normal Withdraw Screen      " << endl;
    cout << "___________________________________" << endl;

    int Amount;
    do
    {
        cout << "Enter an Amount multiple of 5 : ";
        cin >> Amount;

    } while ((Amount % 5 != 0) || (Amount > CurrentClient.AccountBalance));

    cout << "Are you sure you want to perform this Transaction? [Y/N] : ";
    char Answer;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        CurrentClient.AccountBalance -= Amount;
        cout << "\nDone Successfully, New Balance : " << CurrentClient.AccountBalance;
    }
}

void Deposit()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "            Deposit Screen         " << endl;
    cout << "___________________________________" << endl;

    int Amount;
    do
    {
        cout << "Enter positive deposit amount : ";
        cin >> Amount;

    } while (Amount < 0);
    
    cout << "Are you sure you want to perform this Transaction? [Y/N] : ";
    char Answer;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        CurrentClient.AccountBalance += Amount;
        cout << "\nDone Successfully, New Balance : " << CurrentClient.AccountBalance;
    }
}

void CheckBalance()
{
    system("cls");
    cout << "___________________________________" << endl;
    cout << "         Check Balance Screen      " << endl;
    cout << "___________________________________" << endl;

    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
}

void MainMenu()
{
    enMainMenuChoice Choice;
    vector <sClient> vClients;

    while (true)
    {
        system("cls");
        cout << "========================================\n";
        cout << "               Main Menu                \n";
        cout << "========================================\n";
        cout << "\t [1] Quick Withdraw. \n";
        cout << "\t [2] Normal Withdraw. \n";
        cout << "\t [3] Deposit. \n";
        cout << "\t [4] Check Balance. \n";
        cout << "\t [5] Logout. \n";
        cout << "========================================\n";

        Choice = GetMainMenuChoice();

        vClients = ReadClientsDataFromFile(ClientsFile);


        switch (Choice)
        {
            case enMainMenuChoice::mQuick_Withdraw:
                QuickWithdraw();
                GoBackToMainMenue();
                SaveClientsDataToFile(vClients);
                break;

            case enMainMenuChoice::mNormal_Withdraw:
                NormalWithdraw();
                GoBackToMainMenue();
                SaveClientsDataToFile(vClients);
                break;
            
            case enMainMenuChoice::mDeposit:
                Deposit();
                GoBackToMainMenue();
                SaveClientsDataToFile(vClients);
                break;

            case enMainMenuChoice::mCheck_Balance:
                CheckBalance();
                GoBackToMainMenue();
                break;

            case enMainMenuChoice::mLogout:
                return;
                break;

            default:
                break;
        }
    }
}

void Login()
{
    while (true)
    {
        system("cls");
        cout << "___________________________________" << endl;
        cout << "            Login Screen           " << endl;
        cout << "___________________________________" << endl;

        vector <sClient> vClients = ReadClientsDataFromFile(ClientsFile);

        sClient LoginClient;
        cout << "\nEnter Account Number : ";
        getline(cin >> ws, LoginClient.AccountNumber);
        cout << "\nEnter PinCode : ";
        getline(cin >> ws, LoginClient.PinCode);

        for(sClient &Client : vClients)
        {
            if ((Client.AccountNumber == LoginClient.AccountNumber) && (Client.PinCode == LoginClient.PinCode))
            {
                CurrentClient = Client;
                MainMenu();
                break; // when logging out from main menu, skip loop
            }
        }
    }
}

int main()
{
    Login();
}