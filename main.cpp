#include <iostream>
#include <fstream>
#include <libpq-fe.h>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

// * Main schema of the User table
struct User
{
    int id;
    string name;
    int age;
    int salary;
    string nationality;
    string created_at;
    string updated_at;
};

// * Prototype of functions
void fetchUsers(PGconn *conn, User *&users, int &numUsers);
void getConnectionLink(string &connectionLink);

int main()
{
    string connectionLink;
    getConnectionLink(connectionLink);

    //* Connect to the database
    PGconn *conn = PQconnectdb(connectionLink.c_str());
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return 1;
    }
    else
    {
        cout << "Connection to database successful." << endl;
    }

    User *users = nullptr;
    int numUsers = 0;

    // * Fetch users from the database and saving in array to work with
    fetchUsers(conn, users, numUsers);

    for (int i = 0; i < numUsers; i++)
    {
        cout << "ID: " << users[i].id << ", Name: " << users[i].name << ", Age: " << users[i].age
             << ", Salary: " << users[i].salary << ", Nationality: " << users[i].nationality
             << ", Created: " << users[i].created_at << ", Updated: " << users[i].updated_at << endl;
    }

    // * (Ali Alshehri) now you can use the arrays of users and their data to do your work

    //* Clean allocated memory
    delete[] users;
    PQfinish(conn);

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
void fetchUsers(PGconn *conn, User *&users, int &numUsers)
{
    PGresult *res = PQexec(conn, "SELECT id, name, age, salary, nationality, created_at, updated_at FROM users");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        cerr << "Failed to fetch users: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        return;
    }

    numUsers = PQntuples(res);

    users = new User[numUsers];

    for (int i = 0; i < numUsers; i++)
    {
        users[i].id = atoi(PQgetvalue(res, i, 0));
        users[i].name = PQgetvalue(res, i, 1);
        users[i].age = atoi(PQgetvalue(res, i, 2));
        users[i].salary = atoi(PQgetvalue(res, i, 3));
        users[i].nationality = PQgetvalue(res, i, 4);
        users[i].created_at = PQgetvalue(res, i, 5);
        users[i].updated_at = PQgetvalue(res, i, 6);
    }

    PQclear(res);
}

// * (Ali Alshehri) put your functions below this line
