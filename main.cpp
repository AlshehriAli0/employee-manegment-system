#include <iostream>
#include <fstream>
// #include <libpq-fe.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// !! (Ali Alshehri) I have commented out the PostgreSQL library and its functions dont remove them!

// * Main schema of the User table
struct User
{
    int id;
    int nationalId;
    string password;
    bool admin;
    string name;
    int age;
    int salary;
    string nationality;
    string created_at;
    string updated_at;
};

vector<User> Users; // * Dynamic Array
int nextID = 1;     // * Assign users with unique ID's

// * Prototype of functions

int findUserByNationalID(int nationalID, vector<User> Users);

// PGconn *connectToDatabase(const string &connectionLink);

// void fetchUsers(PGconn *conn, vector<User> &users);

void typeWriterEffect(const string &text, int delay);

void getConnectionLink(string &connectionLink);

void addUser();

void displayUsers();

void updateUser(int id);

void deleteUser(int ID);

int isValid(int &option);

string readSecretKey(const string &filename);

string vigenereCipherEncrypt(const string &plaintext, const string &keyword);

int main()
{
    string connectionLink;
    getConnectionLink(connectionLink);

    string key = readSecretKey("env.txt");

    //* Connect to the database
    // PGconn *conn = connectToDatabase(connectionLink);
    // if (!conn)
    // {
    //     return 1;
    // }
    cout << endl;

    // * Welcoming message

    string welcomeMessage = "Welcome to the \033[1;31mEmployee Management System\033[0m\n";
    typeWriterEffect(welcomeMessage, 80);

    // * Fetch users from the database and saving in array to work with
    // fetchUsers(conn, Users);

    //* Dummy user data
    User users[] = {
        {1, 123456789, "0608Sbh", false, "John Doe", 30, 50000, "American", "2022-01-01", "2022-01-01"},    //* Decrypted password: 1234abc
        {2, 987654321, ")795Ubf", true, "Jane Doe", 28, 60000, "American", "2022-01-02", "2022-01-02"},     //* Decrypted password: 4321cba
        {3, 112233445, "0608Sbh", false, "Alice Smith", 35, 70000, "Canadian", "2022-01-03", "2022-01-03"}, //* Decrypted password: 1234abc
        {4, 998877665, ")795Ubf", true, "Bob Johnson", 40, 80000, "British", "2022-01-04", "2022-01-04"}    //* Decrypted password: 4321cba
    };

    // * Adding dummy data to the vector of Users
    Users.insert(Users.end(), begin(users), end(users));

    // * (Ali Alshehri) now you can use the arrays of users and their data to do your work as
    // * users.[attribute]

    //* Clean allocated memory and kill db connection
    // delete[] users;
    // PQfinish(conn);

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
            cout << endl;

            // * Admin Authentication
            cout << "Enter National ID: ";
            int nationalID;
            cin >> nationalID;

            int userIndex = findUserByNationalID(nationalID, Users);

            if (userIndex == -1)
            {
                cout << "User not found\n";
                continue;
            }

            cout << "Enter Password: ";
            string password;
            cin >> password;
            
            // * Encrypting the password to compare with the stored encrypted password
            string encryptedPassword = vigenereCipherEncrypt(password, key);
            cout << encryptedPassword << endl;

            if (encryptedPassword == Users[userIndex].password && Users[userIndex].admin == true)
            {
                cout << endl;
                cout << "Authentication successful. Entering admin menu.\n";
                cout << "Welcome " << Users[userIndex].name << endl;
            }
            else
            {
                cout << endl;
                Users[userIndex].admin == false ? cout << "Authentication failed. You are not an admin. Exiting.\n" : cout << "Authentication failed. Wrong credentials.\n";

                continue;
            }

            // * Admin Submenu
            bool exitMenu = false;
            while (!exitMenu)
            {
                int option;
                int userID;

                cout << "\nOptions:\n";
                cout << "1. Display records\n";
                cout << "2. Add record\n";
                cout << "3. Delete a record\n";
                cout << "4. Update a record\n";
                cout << "5. Exit\n";
                cout << ">> ";

                // * Wait for valid input
                isValid(option);

                switch (option)
                {
                case 1:
                    // * Read Records
                    displayUsers();
                    break;

                case 2:
                    //* Create Record
                    addUser();
                    break;
                case 3:
                    //* Delete Record
                    cout << "User ID:\n>> ";
                    isValid(userID);
                    deleteUser(userID);
                    break;

                case 4:
                    //* Update Record
                    cout << "User ID:\n>> ";
                    isValid(userID);
                    updateUser(userID);
                    break;

                case 5:
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
            int nationalID;
            cin >> nationalID;

            int userIndex = findUserByNationalID(nationalID, Users);

            if (userIndex == -1)
            {
                cout << "User not found\n";
                continue;
            }

            cout << "Enter Password: ";
            string password;
            cin >> password;

            // * Encrypting the password to compare with the stored encrypted password
            string encryptedPassword = vigenereCipherEncrypt(password, key);
            cout << encryptedPassword << endl;

            if (encryptedPassword == Users[userIndex].password && Users[userIndex].admin == false)
            {
                cout << endl;
                cout << "Authentication successful. Entering employee menu.\n";
                cout << "Welcome " << Users[userIndex].name << endl;
            }
            else
            {
                cout << endl;
                Users[userIndex].admin == true ? cout << "Authentication failed. Use the admin login instead. Exiting.\n" : cout << "Authentication failed. Wrong credentials.\n";

                continue;
            }

            // TODO: Employee Submenu options
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

//* Function to read connection string for PostgreSQL from file
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
// void fetchUsers(PGconn *conn, vector<User> &users)
// {
//     users.clear();

//     PGresult *res = PQexec(conn, "SELECT id, national_id, password, admin, name, age, salary, nationality, created_at, updated_at FROM users");

//     if (PQresultStatus(res) != PGRES_TUPLES_OK)
//     {
//         cerr << "Failed to fetch users: " << PQerrorMessage(conn) << endl;
//         PQclear(res);
//         return;
//     }

//     int numRows = PQntuples(res);

//     for (int i = 0; i < numRows; i++)
//     {
//         User newUser;
//         newUser.id = atoi(PQgetvalue(res, i, 0));
//         newUser.nationalId = atoi(PQgetvalue(res, i, 1));
//         newUser.password = atoi(PQgetvalue(res, i, 2));
//         newUser.admin = (PQgetvalue(res, i, 3)[0] == 't');
//         newUser.name = PQgetvalue(res, i, 4);
//         newUser.age = atoi(PQgetvalue(res, i, 5));
//         newUser.salary = atoi(PQgetvalue(res, i, 6));
//         newUser.nationality = PQgetvalue(res, i, 7);
//         newUser.created_at = PQgetvalue(res, i, 8);
//         newUser.updated_at = PQgetvalue(res, i, 9);

//         users.push_back(newUser);
//     }

//     PQclear(res);
// }

// * (Ali Alshehri) put your functions below this line

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

void addUser()
{
    User newUser;
    newUser.id = nextID++; // * Modifies global variable of nextID to assign unique ID to users
    cout << "Name: ";
    cin.ignore();
    getline(cin, newUser.name);
    cout << "Age: ";
    isValid(newUser.age);
    cout << "Salary: ";
    isValid(newUser.salary);
    cout << "Nationality: ";
    cin >> newUser.nationality;

    // * Current Day-Date-Time
    time_t currentTime = time(nullptr);
    newUser.created_at = asctime(localtime(&currentTime));
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

void updateUser(int id)
{
    for (auto &user : Users)
    {
        if (user.id == id)
        {
            int option;
            bool updated;
            do
            {
                cout << "\nOptions:\n";
                cout << "1. Update Name\n";
                cout << "2. Update Age\n";
                cout << "3. Update Salary\n";
                cout << "4. Update Nationality\n";
                cout << "5. Exit\n";
                cout << ">> ";
                cin >> option;

                switch (option)
                {
                case 1:
                    cout << "Name: ";
                    cin.ignore();
                    getline(cin, user.name);
                    updated = true;
                    break;
                case 2:
                    cout << "Age: ";
                    cin >> user.age;
                    updated = true;
                    break;
                case 3:
                    cout << "Salary: ";
                    cin >> user.salary;
                    updated = true;
                    break;
                case 4:
                    cout << "Nationality: ";
                    cin >> user.nationality;
                    updated = true;
                    break;
                case 5:
                    cout << endl;
                    break;
                default:
                    cout << "\nInvalid prompt\n";
                    break;
                }
            } while (option != 5);

            // * Check if user updated to display message after exiting
            if (updated)
            {
                // * Saves at 'updated_at' when the specified user info was last updated
                time_t currentTime = time(nullptr);
                user.updated_at = asctime(localtime(&currentTime));
                cout << "\nUpdated Successfully\n";
            }
        }
    }
}

void deleteUser(int ID)
{
    bool found = false;

    //* Iterate through the vector of users
    for (auto currentUserIterator = Users.begin(); currentUserIterator != Users.end(); ++currentUserIterator)
    {
        //* Check if the current iterator's ID matches the specified ID
        if ((*currentUserIterator).id == ID)
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
int findUserByNationalID(int nationalID, vector<User> Users)
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

// TODO: Function to save users to the database

// * Connect to Db
// PGconn *connectToDatabase(const string &connectionLink)
// {
//     PGconn *conn = PQconnectdb(connectionLink.c_str());
//     if (PQstatus(conn) == CONNECTION_BAD)
//     {
//         cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
//         PQfinish(conn);
//         return nullptr;
//     }
//     else
//     {
//         return conn;
//     }
// }

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
