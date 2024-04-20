#include <iostream>
#include <fstream>
// #include <libpq-fe.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>

using namespace std;

// !! (Ali Alshehri) I have commented out the PostgreSQL library and its functions dont remove them!

// * Main schema of the User table
struct User
{
    int id;
    int nationalId;
    int password;
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
// void fetchUsers(PGconn *conn, User *&users, int &numUsers);

void getConnectionLink(string &connectionLink);

void addUser();

void displayUsers();

void updateUser(int id);

void deleteUser(int ID);

int isValid(int &option);

int main()
{
    string connectionLink;
    // getConnectionLink(connectionLink);

    //* Connect to the database
    // PGconn *conn = PQconnectdb(connectionLink.c_str());
    // if (PQstatus(conn) == CONNECTION_BAD)
    // {
    //     cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
    //     PQfinish(conn);
    //     return 1;
    // }
    // else
    // {
    //     cout << "Connection to database successful." << endl;
    // }

    // User *users = nullptr;
    int numUsers = 3;

    // * Fetch users from the database and saving in array to work with
    // fetchUsers(conn, users, numUsers);

    //* Dummy user data
    User users[] = {
        {1, 123456789, 1234, false, "John Doe", 30, 50000, "American", "2022-01-01", "2022-01-01"},
        {2, 987654321, 4321, true, "Jane Doe", 28, 60000, "American", "2022-01-02", "2022-01-02"},
        {3, 112233445, 5678, false, "Alice Smith", 35, 70000, "Canadian", "2022-01-03", "2022-01-03"},
        {4, 998877665, 8765, true, "Bob Johnson", 40, 80000, "British", "2022-01-04", "2022-01-04"}};

    // for (int i = 0; i < numUsers; i++)
    // {
    //     cout << "ID: " << users[i].id << ", Name: " << users[i].name << ", Age: " << users[i].age
    //          << ", Salary: " << users[i].salary << ", Nationality: " << users[i].nationality
    //          << ", Created: " << users[i].created_at << ", Updated: " << users[i].updated_at << endl;
    // }

    // * (Ali Alshehri) now you can use the arrays of users and their data to do your work as
    // * users.[attribute]

    //* Clean allocated memory
    // delete[] users;
    // PQfinish(conn);

    int option;
    while (true)
    {
        cout << "\nOptions:\n";
        cout << "1. Admin Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Exit\n";
        cout << ">> ";

        // * Wait for valid input
        isValid(option);

        if (option == 1)
        {
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
// void fetchUsers(PGconn *conn, User *&users, int &numUsers)
// {
//     PGresult *res = PQexec(conn, "SELECT id, name, age, salary, nationality, created_at, updated_at FROM users");

//     if (PQresultStatus(res) != PGRES_TUPLES_OK)
//     {
//         cerr << "Failed to fetch users: " << PQerrorMessage(conn) << endl;
//         PQclear(res);
//         return;
//     }

//     numUsers = PQntuples(res);

//     users = new User[numUsers];

//     for (int i = 0; i < numUsers; i++)
//     {
//         users[i].id = atoi(PQgetvalue(res, i, 0));
//         users[i].name = PQgetvalue(res, i, 1);
//         users[i].age = atoi(PQgetvalue(res, i, 2));
//         users[i].salary = atoi(PQgetvalue(res, i, 3));
//         users[i].nationality = PQgetvalue(res, i, 4);
//         users[i].created_at = PQgetvalue(res, i, 5);
//         users[i].updated_at = PQgetvalue(res, i, 6);
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