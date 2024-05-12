#include <iostream>
#include <fstream>
#include <libpq-fe.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// * Main schema of the User table
struct User
{
    int id;
    long nationalId;
    string password;
    bool admin;
    string name;
    int age;
    int salary;
    string nationality;
    string performance;
    string created_at;
    string updated_at;
};

vector<User> Users;    // * Dynamic Array
int nextID = 1;        // * Assign users with unique ID's
long nationalID;       //* Initialized as global to use in functions without passing it as a parameter
string connectionLink; // * Connection string to the database

// * Prototype of functions

void saveUsers(const vector<User> &users);

int isValidLong(long &option);

int findUserByNationalID(vector<User> Users);

void fetchUsers(vector<User> &users);

void typeWriterEffect(const string &text, int delay);

void dataToFile(int userID, vector<User> &users);

void getConnectionLink(string &connectionLink);

void deleteUserFromDB(int ID);

void addUser();

void displayUsers();

void updateUserInDB(int userID);

void displayUser(int id);

void displayByField();

void updateUser(int id);

void deleteUser(int ID);

void viewPerformance(int ID);

void evaluateUser(int ID);

int isValid(int &option);

string getCurrentDateTime();

char *getPassword();

void searchByNationalID(vector<User> &users);

int returnNewID();

void searchByName(vector<User> &users);

void searchByAge(vector<User> &users);

void searchBySalary(vector<User> &users);

bool compareById(const User &u1, const User &u2);

bool compareByName(const User &u1, const User &u2);

bool compareByAge(const User &u1, const User &u2);

bool compareBySalary(const User &u1, const User &u2);

bool compareByCreatedAt(const User &u1, const User &u2);

bool compareByUpdatedAt(const User &u1, const User &u2);

void sortById(vector<User> &users);

void sortByName(vector<User> &users);

void sortByAge(vector<User> &users);

void sortBySalary(vector<User> &users);

void sortByCreatedAt(vector<User> &users);

void sortByUpdatedAt(vector<User> &users);

string readSecretKey(const string &filename);

// * Encryption Key
const string key = readSecretKey("env.txt");

string vigenereCipherEncrypt(const string &plaintext, const string &keyword);

// * Get connection string from file

int main()
{
    getConnectionLink(connectionLink);

    // * Welcoming message

    string welcomeMessage = "Welcome to the \033[1;31mEmployee Management System\033[0m\n";
    typeWriterEffect(welcomeMessage, 40);

    // * Fetch users from the database and saving in array to work with
    // fetchUsers(Users);

    // * Dummy user data
    // User users[] = {
    //     {1, 123456789, "0608Sbh", false, "John Doe", 37, 50800, "American", "", "2022-01-01 12:19:45", "2022-01-01"},  //* Decrypted password: 1234abc
    //     {2, 987654321, ")795Ubf", true, "John Doe", 35, 6000, "American", "", "2025-01-02 1:19:45", "2022-01-02"},     //* Decrypted password: 4321cba
    //     {3, 112233445, "0608Sbh", false, "Alice Smith", 67, 7000, "Canadian", "", "2020-01-03 4:19:45", "2022-01-03"}, //* Decrypted password: 1234abc
    //     {4, 998877665, ")795Ubf", true, "Bob Johnson", 40, 80000, "British", "", "2021-01-04 7:19:45", "2022-01-04"}   //* Decrypted password: 4321cba
    // };

    // * Adding dummy data to the vector of Users
    Users.insert(Users.end(), begin(users), end(users));

    // * (Ali Alshehri) now you can use the arrays of users and their data to do your work as
    // * users.[attribute].

    //* Clean allocated memory and kill db connection
    // delete[] users;

    int option;

    while (true)
    {
        // * Displaying the main menu
        cout << endl;
        cout << "\033[1;1mOptions:\033[0m\n";
        cout << "\033[1;31m1.\033[0m Admin Login\n";
        cout << "\033[1;32m2.\033[0m Employee Login\n";
        cout << "\033[1;34m3.\033[0m Exit\n";
        cout << ">> ";

        // * Wait for valid input
        isValid(option);

        if (option == 1)
        {
            // * Admin Submenu
            cout << endl;

            // * Admin Authentication
            cout << "Enter National ID: ";
            cin >> nationalID;

            int userIndex = findUserByNationalID(Users);

            if (userIndex == -1)
            {
                cout << "User not found\n";
                continue;
            }

            cout << "Enter Password: ";
            string password;
            password = getPassword();

            // * Encrypting the password to compare with the stored encrypted password
            string encryptedPassword = vigenereCipherEncrypt(password, key);

            if (encryptedPassword == Users[userIndex].password && Users[userIndex].admin == true)
            {
                cout << endl;
                cout << "\nAuthentication successful. Entering admin menu.\n";
                cout << "Welcome " << Users[userIndex].name << endl;
            }
            else
            {
                cout << endl;
                Users[userIndex].admin == false ? cout << "Authentication failed. You are not an admin. Exiting.\n" : cout << "Authentication failed. Wrong credentials.\n";

                continue;
            }

            bool exitMenu = false;
            while (!exitMenu)
            {
                int option;
                int subMenuOption;
                bool subExitMenu = false;
                int userID;

                cout << "\nOptions:\n";
                cout << "1. Display records\n";
                cout << "2. Add record\n";
                cout << "3. Delete a record\n";
                cout << "4. Update a record\n";
                cout << "5. Sort records\n";
                cout << "6. Evaluate an Employee's Performance\n";
                cout << "7. Exit\n";
                cout << ">> ";

                // * Wait for valid input
                isValid(option);

                switch (option)
                {
                case 1:
                    do
                    {
                        cout << "\nOptions:\n";
                        cout << "1. Display all records\n";
                        cout << "2. Display by field\n";
                        cout << "3. Search for a record\n";
                        cout << "4. Exit\n";
                        cout << ">> ";
                        isValid(subMenuOption);
                        switch (subMenuOption)
                        {
                        case 1:
                            displayUsers();
                            break;
                        case 2:
                            displayByField();
                            break;
                        case 3:
                            cout << "\nSearch by:\n";
                            cout << "1. National ID\n";
                            cout << "2. Name\n";
                            cout << "3. Age\n";
                            cout << "4. Salary\n";
                            cout << "5. Exit\n";
                            cout << ">> ";
                            isValid(option);
                            cout << endl;

                            switch (option)
                            {
                            case 1:
                                cout << "User ID:\n>> ";
                                searchByNationalID(Users);

                                break;
                            case 2:
                                cout << "Name:\n>> ";
                                searchByName(Users);

                                break;
                            case 3:
                                cout << "Age:\n>> ";
                                searchByAge(Users);
                                break;
                            case 4:
                                cout << "Salary:\n>> ";
                                searchBySalary(Users);

                                break;
                            case 5:
                                break;
                            default:
                                cout << "\nInvalid prompt\n";
                            }

                            break;

                        case 4:
                            subExitMenu = true;
                            break;

                        default:
                            cout << "\nInvalid prompt\n";
                        }
                    } while (!subExitMenu);
                    break;

                case 2:
                    //* Create Record
                    addUser();
                    // saveUsers(Users);
                    // fetchUsers(Users);

                    break;
                case 3:
                    //* Delete Record
                    cout << "User ID:\n>> ";
                    isValid(userID);
                    deleteUser(userID);
                    // deleteUserFromDB(userID);
                    break;

                case 4:
                    //* Update Record
                    cout << "User ID:\n>> ";
                    isValid(userID);
                    updateUser(userID);
                    // updateUserInDB(userID);
                    break;

                case 5:
                    // * Sort records
                    cout << "\nSort by: \n";
                    cout << "1. User ID\n";
                    cout << "2. Name\n";
                    cout << "3. Age\n";
                    cout << "4. Salary\n";
                    cout << "5. Created At\n";
                    cout << "6. Updated At\n";
                    cout << "7. Exit\n";
                    cout << ">> ";
                    isValid(option);
                    cout << endl;

                    switch (option)
                    {
                    case 1:
                        sortById(Users);

                        break;
                    case 2:
                        sortByName(Users);

                        break;
                    case 3:
                        sortByAge(Users);
                        break;
                    case 4:
                        sortBySalary(Users);

                        break;
                    case 5:
                        sortByCreatedAt(Users);

                        break;
                    case 6:
                        sortByUpdatedAt(Users);

                        break;
                    case 7:
                        break;
                    default:
                        cout << "\nInvalid prompt\n";
                    }
                    break;

                case 6:
                    // * Employee evaluation
                    cout << "User ID:\n>> ";
                    isValid(userID);
                    evaluateUser(userID);
                    break;

                case 7:
                    // * Exit Admin Submenu
                    exitMenu = true;
                    break;
                default:
                    cout << "\nInvalid prompt\n";
                }
            }
        }
        else if (option == 2)
        {
            // * Employee Submenu
            cout << endl;

            // * Employee Authentication
            cout << "Enter National ID: ";
            cin >> nationalID;

            int userIndex = findUserByNationalID(Users);

            if (userIndex == -1)
            {
                cout << "User not found\n";
                continue;
            }

            cout << "Enter Password: ";
            string password;
            password = getPassword();

            // * Encrypting the password to compare with the stored encrypted password
            string encryptedPassword = vigenereCipherEncrypt(password, key);

            if (encryptedPassword == Users[userIndex].password)
            {
                cout << endl;
                cout << "Authentication successful. Entering employee menu.\n";
                cout << "Welcome " << Users[userIndex].name << endl;
                // * Employee Submenu
                bool exitMenu = false;
                while (!exitMenu)
                {
                    int option;
                    int userID = Users[userIndex].id;

                    cout << "\nOptions:\n";
                    cout << "1. Display Information\n";
                    cout << "2. Save personal data in a .txt\n";
                    cout << "3. View Performance Evaluation\n";
                    cout << "4. Exit\n";
                    cout << ">> ";

                    // * Wait for valid input
                    isValid(option);

                    switch (option)
                    {
                    case 1:
                        // * Display Employee Information
                        displayUser(userID);
                        break;
                    case 2:
                        dataToFile(userID, Users);

                        break;

                    case 3:
                        viewPerformance(userID);
                        break;
                    case 4:
                        // * Exit Employee Submenu
                        exitMenu = true;
                        break;

                    default:
                        cout << "\nInvalid prompt\n";
                    }
                }
            }
            else
            {
                cout << endl;
                cout << "Authentication failed. Wrong credentials.\n";

                continue;
            }
        }
        else if (option == 3)
        {
            exit(0);
        }
        else
        {
            cout << "\n Invalid prompt\n";
        }
    }
    return 0;
}

// * Function to read connection string for PostgreSQL from file
void getConnectionLink(string &connectionLink)
{
    ifstream file("env.txt");
    if (file.is_open())
    {
        getline(file, connectionLink);
        file.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
}

// * Function to fetch users from the database
void fetchUsers(vector<User> &users)
{
    PGconn *conn = PQconnectdb(connectionLink.c_str());
    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Failed to connect to the database: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return;
    }

    users.clear();

    PGresult *res = PQexec(conn, "SELECT id, national_id, password, admin, name, age, salary, nationality, created_at, updated_at FROM users ORDER BY id ASC");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        cerr << "Failed to fetch users: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int numRows = PQntuples(res);
    for (int i = 0; i < numRows; i++)
    {
        User newUser;
        newUser.id = atoi(PQgetvalue(res, i, 0));
        newUser.nationalId = atoi(PQgetvalue(res, i, 1));
        newUser.password = PQgetvalue(res, i, 2);
        newUser.admin = (PQgetvalue(res, i, 3)[0] == 't');
        newUser.name = PQgetvalue(res, i, 4);
        newUser.age = atoi(PQgetvalue(res, i, 5));
        newUser.salary = atoi(PQgetvalue(res, i, 6));
        newUser.nationality = PQgetvalue(res, i, 7);
        newUser.created_at = PQgetvalue(res, i, 8);
        newUser.updated_at = PQgetvalue(res, i, 9);
        users.push_back(newUser);
    }

    PQclear(res);
    PQfinish(conn);
}

// * Prevents program from crashing when user enters non-numeric as input
int isValid(int &option)
{
    while (!(cin >> option))
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">> ";
    }
    return option;
}

// * Adds a new user to the array of 'Users'
void addUser()
{
    User newUser;

    newUser.id = returnNewID(); // * Modifies global variable of nextID to assign unique ID to users

    cout << "Name: ";
    cin.ignore();
    getline(cin, newUser.name);
    cout
        << "Password: ";
    newUser.password = getPassword();
    cout << endl;
    // * Encryption Process
    newUser.password = vigenereCipherEncrypt(newUser.password, key);
    cout << "National ID: ";
    isValidLong(newUser.nationalId);
    cout << "Age: ";
    isValid(newUser.age);
    cout << "Employee (0) | Admin (1): ";
    while (!(cin >> newUser.admin))
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">> ";
    }
    cout << "Salary: ";
    isValid(newUser.salary);
    cout << "Nationality: ";
    cin >> newUser.nationality;

    newUser.created_at = getCurrentDateTime();
    newUser.updated_at = "";

    // * Adds user to the array of 'Users'
    Users.push_back(newUser);
    cout << "Employee added successfully!\n";
}

// * Loops through every struct object stored in 'Users' dynamic array
void displayUsers()
{
    if (Users.empty())
    {
        cout << "\nNo Record Found\n";
    }
    else
    {
        cout << "Employees:" << endl;
        for (const auto &user : Users)
        {
            cout << "ID: " << user.id << " | Name: " << user.name << " | Age: " << user.age
                 << " | Salary: " << user.salary << " | Nationality: " << user.nationality
                 << " | Created: " << user.created_at << " | Updated: " << user.updated_at << endl;
        }
    }
}

// * Search for a user by ID and display their information
void displayUser(int id)
{
    bool found = false;
    for (int i = 0; i < Users.size(); i++)
    {
        if (Users[i].id == id)
        {
            cout << "ID: " << Users[i].id << " | Name: " << Users[i].name << " | Age: " << Users[i].age
                 << " | Salary: " << Users[i].salary << " | Nationality: " << Users[i].nationality
                 << " | Created: " << Users[i].created_at << " | Updated: " << Users[i].updated_at << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Record does not exist" << endl;
    }
}

// * Display users by field
void displayByField()
{
    int option;
    if (Users.empty())
    {
        cout << "\nNo Record Found\n";
    }
    else
    {
        cout << "\nOptions:\n";
        cout << "1. Display Names\n";
        cout << "2. Display Ages\n";
        cout << "3. Display Salaries\n";
        cout << "4. Display Nationalities\n";
        cout << "5. Exit\n";
        cout << ">> ";
        isValid(option);

        switch (option)
        {
        case 1:
            for (const auto &user : Users)
            {
                cout << "ID: " << user.id << " | Name: " << user.name << endl;
            }
            break;
        case 2:
            for (const auto &user : Users)
            {
                cout << "ID: " << user.id << " | Age: " << user.age << endl;
            }
            break;
        case 3:
            for (const auto &user : Users)
            {
                cout << "ID: " << user.id << " | Salary: " << user.salary << endl;
            }
            break;
        case 4:
            for (const auto &user : Users)
            {
                cout << "ID: " << user.id << " | Nationality: " << user.nationality << endl;
            }
            break;
        default:
            cout << "\nInvalid prompt\n";
        }
    }
}

// * Update user information
void updateUser(int id)
{
    bool found = false;
    for (auto &user : Users)
    {
        if (user.id == id)
        {
            found = true;
            int option;
            bool updated;
            do
            {
                cout << "\nOptions:\n";
                cout << "1. Update Name\n";
                cout << "2. Update Password\n";
                cout << "3. Update Age\n";
                cout << "4. Update Salary\n";
                cout << "5. Update Nationality\n";
                cout << "6. Exit\n";
                cout << ">> ";
                isValid(option);

                switch (option)
                {
                case 1:
                    cout << "New Name: ";
                    cin.ignore();
                    getline(cin, user.name);
                    updated = true;
                    break;
                case 2:
                    cout << "New Password: ";
                    user.password = getPassword();
                    cout << endl;
                    user.password = vigenereCipherEncrypt(user.password, key);
                    updated = true;
                    break;
                case 3:
                    cout << "New Age: ";
                    cin >> user.age;
                    updated = true;
                    break;
                case 4:
                    cout << "New Salary: ";
                    cin >> user.salary;
                    updated = true;
                    break;
                case 5:
                    cout << "New Nationality: ";
                    cin >> user.nationality;
                    updated = true;
                    break;
                case 6:
                    cout << endl;
                    break;
                default:
                    cout << "\nInvalid prompt\n";
                    break;
                }
            } while (option != 6);

            // * Check if user updated to display message after exiting
            if (updated)
            {
                // * Saves when the specified user info was last updated in 'updated_at'
                user.updated_at = getCurrentDateTime();

                cout << "\nUpdated Successfully\n";
            }
        }
    }
    if (!found)
        cout << "User not found" << endl;
}

// * Delete user by ID
void deleteUser(int ID)
{
    bool found = false;

    //* Iterate through the vector of users
    for (auto currentUserIterator = Users.begin(); currentUserIterator != Users.end(); ++currentUserIterator)
    {
        //* Check if the current iterator's ID matches the specified ID
        if ((*currentUserIterator).id == ID && (*currentUserIterator).admin == false)
        {
            //* Remove user from array
            currentUserIterator = Users.erase(currentUserIterator);
            cout << "\nRecord Successfully Deleted\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nNot Found\n";
    }
}

// * Function to search for a user by ID
int findUserByNationalID(vector<User> Users)
{
    for (int i = 0; i < Users.size(); i++)
    {
        if (Users[i].nationalId == nationalID)
        {
            return i;
        }
    }
    return -1;
}

// * Print with typewriter effect
void typeWriterEffect(const string &text, int delay)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// * Read encryption key from file which
string readSecretKey(const string &filename)
{
    ifstream file(filename);
    string key;
    string temp;

    getline(file, temp);

    getline(file, key);

    return key;
}

// * Encrypt and decrypt password
string vigenereCipherEncrypt(const string &plaintext, const string &keyword)
{
    string ciphertext;
    int keyLength = keyword.length();
    int textLength = plaintext.length();

    for (int i = 0, j = 0; i < textLength; ++i)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            ciphertext += ((c - base + keyword[j % keyLength] - 'a') % 26) + base;
            ++j;
        }
        else if (isdigit(c))
        {
            ciphertext += ((c - '0' + keyword[j % keyLength] - 'a') % 10) + '0';
            ++j;
        }
        else
        {
            ciphertext += c;
        }
    }

    return ciphertext;
}

// * Getting sensitive input from the user with maximum length of 30 characters
char *getPassword()
{
    static char s[30] = {0};
    int i = 0;
    while (true)
    {
        char c = _getch();
        if (c == 13)
            break;
        else if (c == 8)
        {
            if (i > 0)
            {
                s[--i] = '\0';
                cout << "\b \b";
            }
        }
        else if (i < 29)
        {
            s[i++] = c;
            _putch('*');
        }
    }
    s[i] = '\0';
    return s;
}

string getCurrentDateTime()
{
    time_t currentTime = time(nullptr);
    char formattedTime[20];
    // * Format current time to (Year-Month-Day currentTime)
    strftime(formattedTime, 20, "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    return formattedTime;
}

void searchByNationalID(vector<User> &users)
{
    int userID;
    bool found = false;
    cin >> userID;

    int numOfUsers = 0;

    for (const auto &user : users)
    {
        if (user.nationalId == userID)
        {
            numOfUsers++;
        }
    }
    if (numOfUsers)
    {
        cout << endl;
        cout << numOfUsers << " users found: " << endl;
        cout << endl;
    }

    for (const auto &user : users)
    {
        if (user.nationalId == userID)
        {
            found = true;
            cout << "ID: " << user.id << " | Name: " << user.name << " | Age: " << user.age
                 << " | Salary: " << user.salary << " | Nationality: " << user.nationality
                 << " | Created: " << user.created_at << " | Updated: " << user.updated_at << endl;
        }
    }
    if (!found)
    {
        cout << "User not found" << endl;
    }
}

void searchByName(vector<User> &users)
{
    string name;
    bool found = false;
    cin.ignore();
    getline(cin, name);

    int numOfUsers = 0;

    for (const auto &user : users)
    {
        if (user.name == name)
        {
            numOfUsers++;
        }
    }
    if (numOfUsers)
    {
        cout << endl;
        cout << numOfUsers << " users found: " << endl;
        cout << endl;
    }

    for (const auto &user : users)
    {
        // * Check if length of User name and User input are equal to begin matching case-sensitivity
        if (user.name.length() == name.length())
        {
            // * Iterate over each letter of the user's name and convert the corresponding letter in the input to match the case-sensitivity of the user
            for (int i = 0; i < user.name.length(); i++)
                (user.name[i] != toupper(name[i])) ? name[i] = tolower(name[i]) : name[i] = toupper(name[i]);

            // * Check after conversion if names are indeed matching
            if (user.name == name)
            {
                found = true;
                cout << "ID: " << user.id << " | Name: " << user.name << " | Age: " << user.age
                     << " | Salary: " << user.salary << " | Nationality: " << user.nationality
                     << " | Created: " << user.created_at << " | Updated: " << user.updated_at << endl;
            }
        }
    }
    if (!found)
    {
        cout << "User not found" << endl;
    }
}

void searchByAge(vector<User> &users)
{
    int age;
    bool found = false;
    cin >> age;

    int numOfUsers = 0;

    for (const auto &user : users)
    {
        if (user.age == age)
        {
            numOfUsers++;
        }
    }
    if (numOfUsers)
    {
        cout << endl;
        cout << numOfUsers << " users found: " << endl;
        cout << endl;
    }

    for (const auto &user : users)
    {
        if (user.age == age)
        {
            found = true;
            cout << "ID: " << user.id << " | Name: " << user.name << " | Age: " << user.age
                 << " | Salary: " << user.salary << " | Nationality: " << user.nationality
                 << " | Created: " << user.created_at << " | Updated: " << user.updated_at << endl;
        }
    }
    if (!found)
    {
        cout << "User not found" << endl;
    }
}

void searchBySalary(vector<User> &users)
{
    int salary;
    bool found = false;
    cin >> salary;

    int numOfUsers = 0;

    for (const auto &user : users)
    {
        if (user.salary == salary)
        {
            numOfUsers++;
        }
    }
    if (numOfUsers)
    {
        cout << endl;
        cout << numOfUsers << " users found: " << endl;
        cout << endl;
    }

    for (const auto &user : users)
    {
        if (user.salary == salary)
        {
            found = true;
            cout << "ID: " << user.id << " | Name: " << user.name << " | Age: " << user.age
                 << " | Salary: " << user.salary << " | Nationality: " << user.nationality
                 << " | Created: " << user.created_at << " | Updated: " << user.updated_at << endl;
        }
    }
    if (!found)
    {
        cout << "User not found" << endl;
    }
}

// * Function to save to the db
void saveUsers(const vector<User> &users)
{
    PGconn *conn = PQconnectdb(connectionLink.c_str());
    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Failed to connect to the database: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return;
    }

    if (!users.empty())
    {
        const User &user = users.back();

        const char *paramValues[10];
        string query = "INSERT INTO users (id, national_id, password, admin, name, age, salary, nationality, created_at, updated_at) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10)";

        paramValues[0] = to_string(user.id).c_str();
        paramValues[1] = to_string(user.nationalId).c_str();
        paramValues[2] = user.password.c_str();
        paramValues[3] = user.admin ? "true" : "false";
        paramValues[4] = user.name.c_str();
        paramValues[5] = to_string(user.age).c_str();
        paramValues[6] = to_string(user.salary).c_str();
        paramValues[7] = user.nationality.c_str();
        paramValues[8] = !user.created_at.empty() ? user.created_at.c_str() : "now()";
        paramValues[9] = !user.updated_at.empty() ? user.updated_at.c_str() : "now()";

        int paramLengths[10];
        int paramFormats[10];

        for (int i = 0; i < 10; ++i)
        {
            paramLengths[i] = -1;
            paramFormats[i] = 0;
        }

        PGresult *res = PQexecParams(conn, query.c_str(), 10, nullptr, paramValues, paramLengths, paramFormats, 0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            cerr << "Failed to save user: " << PQerrorMessage(conn) << endl;
        }

        PQclear(res);
    }

    PQfinish(conn);
}

// * Delete user from the database
void deleteUserFromDB(int ID)
{
    bool found = false;
    bool isAdmin = false;
    for (const auto &user : Users)
    {
        if (user.id == ID)
        {
            found = true;
            isAdmin = user.admin;
            break;
        }
    }

    // * Check if the user is an admin and if so, don't delete it
    if (!found || isAdmin)
    {
        if (isAdmin)
        {
            cout << "Cannot delete an admin user.\n"
                 << endl;
        }
        return;
    }

    PGconn *conn = PQconnectdb(connectionLink.c_str());
    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Failed to connect to the database: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return;
    }

    string query = "DELETE FROM users WHERE id = $1";
    const char *paramValues[1] = {to_string(ID).c_str()};
    int paramLengths[1] = {-1};
    int paramFormats[1] = {0};

    PGresult *res = PQexecParams(conn, query.c_str(), 1, nullptr, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to delete user: " << PQerrorMessage(conn) << endl;
    }
    else
    {
        cout << "User with ID " << ID << " deleted from the database." << endl;
    }

    PQclear(res);
    PQfinish(conn);
}

// * Function to save update to the db
void updateUserInDB(int userID)
{
    User updatedUser;
    bool found = false;
    for (const auto &user : Users)
    {
        if (user.id == userID)
        {
            updatedUser = user;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return;
    }

    PGconn *conn = PQconnectdb(connectionLink.c_str());
    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Failed to connect to the database: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return;
    }

    string query = "UPDATE users SET name = $1, password = $2, age = $3, salary = $4, nationality = $5, updated_at = now() WHERE id = $6";
    const char *paramValues[6] = {
        updatedUser.name.c_str(),
        updatedUser.password.c_str(),
        to_string(updatedUser.age).c_str(),
        to_string(updatedUser.salary).c_str(),
        updatedUser.nationality.c_str(),
        to_string(userID).c_str()};
    int paramLengths[6] = {-1, -1, -1, -1, -1, -1};
    int paramFormats[6] = {0, 0, 0, 0, 0, 0};

    PGresult *res = PQexecParams(conn, query.c_str(), 6, nullptr, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        cerr << "Failed to update user in the database: " << PQerrorMessage(conn) << endl;
    }
    else
    {
        cout << "User with ID " << userID << " updated in the database." << endl;
    }

    PQclear(res);
    PQfinish(conn);
}

// * comparison criteria
bool compareById(const User &u1, const User &u2)
{
    return u1.id < u2.id;
}

bool compareByName(const User &u1, const User &u2)
{
    return u1.name < u2.name;
}

bool compareByAge(const User &u1, const User &u2)
{
    return u1.age < u2.age;
}

bool compareBySalary(const User &u1, const User &u2)
{
    return u1.salary < u2.salary;
}

bool compareByCreatedAt(const User &u1, const User &u2)
{
    return u1.created_at < u2.created_at;
}

bool compareByUpdatedAt(const User &u1, const User &u2)
{
    return u1.updated_at < u2.updated_at;
}

//* Sorting functions
void sortById(vector<User> &users)
{
    sort(users.begin(), users.end(), compareById);
}

void sortByName(vector<User> &users)
{
    sort(users.begin(), users.end(), compareByName);
}

void sortByAge(vector<User> &users)
{
    sort(users.begin(), users.end(), compareByAge);
}

void sortBySalary(vector<User> &users)
{
    sort(users.begin(), users.end(), compareBySalary);
}

void sortByCreatedAt(vector<User> &users)
{
    sort(users.begin(), users.end(), compareByCreatedAt);
}

void sortByUpdatedAt(vector<User> &users)
{
    sort(users.begin(), users.end(), compareByUpdatedAt);
}

int returnNewID()
{
    int maxID = 0;
    for (const auto &user : Users)
    {
        if (user.id > maxID)
        {
            maxID = user.id;
        }
    } // * Finding the maximum ID in the array

    nextID = maxID + 1; // * Assigning next ID to the global variable
    return nextID++;
}

int isValidLong(long &option)
{
    while (!(cin >> option))
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">> ";
    }
    return option;
}

void dataToFile(int userID, vector<User> &users)
{
    for (auto &user : users)
    {
        if (user.id == userID)
        {
            string fileName = "recognition-of-" + user.name + ".txt";
            ofstream file(fileName);
            if (file.is_open())
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);

                file << "On the request of the employee, this recognition certificate is created on "
                     << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday
                     << " " << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec
                     << ".\nOur company recognizes our employee " << user.name
                     << " with ID number " << user.nationalId
                     << " for his work time for us since " << user.created_at
                     << " with a salary of " << user.salary << ".\n"
                     << endl;

                file.close();
                break;
            }
            else
            {
                cerr << "Unable to open file for " << user.name << endl;
            }
        }
    }
}

void viewPerformance(int ID)
{
    ID -= 1; // * Starting Index 0
    if (Users[ID].performance == "")
    {
        cout << "\nN/A\n";
    }
    else
    {
        cout << "Your Evaluation: " << Users[ID].performance << endl;
    }
}

void evaluateUser(int ID)
{
    bool found = false;
    for (int i = 0; i < Users.size(); i++)
    {
        if (Users[i].id == ID)
        {
            cout << "Report: ";
            cin.ignore();
            getline(cin, Users[i].performance);
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNot Found\n";
    }
}