# Employee Management System 💻

## TODO

- [x] Connect to db
- [] Main Menu
  - [] Employee Submenu
    - [] Login Authentication
      - [] Display Information
      - ...
      - [] Logout
  - [] Admin SubMenu
    - [] Login Authentication
      - [] CRUD Operations
        - [] Create an Employee's Record (including user & password for employee submenu login. # not sure if it's worth the hassle but encrypting the password column somehow would be a nice feature to implement and mention during presentation)
        - [] Read/Display ^ Record
        - [] Update/Edit ^ Record
          - [] Salary, Performance evaluation, ...
        - [] Delete ^ Record
     - [] Logout

# Functions
- [] main followed by sub menus to start the program
- [] User Creation fun
- [] User Deletion fun
- [] user inquiry fun
- [] Sort fun
- [] user editing fun
- [] Fun to save chosen data in a .txt

# User object scheema
```c++
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
```