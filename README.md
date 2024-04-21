## Employee Management System 💻

### App Flow

- [x] Connect to db
- [x] Main Menu
  - [] Employee Submenu
    - [x] Login Authentication
      - [] Display Information
      - [] Save any wanted personal data
      - [] Logout
  - [x] Admin SubMenu
    - [x] Login Authentication
      - [] CRUD Operations
        - [x] Create an Employee's Record (including user & password for employee submenu login. # not sure if it's worth the hassle but encrypting the password column somehow would be a nice feature to implement and mention during presentation)
        - [x] Read/Display ^ Record
        - [x] Update/Edit ^ Record
        - [x] Delete ^ Record
    - [] Logout

### TODO

- [x] main followed by sub menus to start the program
- [x] User Creation function
- [x] User Deletion function
- [] user inquiry function
- [] Sort function
- [] Encryption function
- [x] user editing function
- [] Function to save chosen data in a .txt
- [] Function to search by any chosen field

### User Structure

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

### Team Notes

#### - Ali Alshehri

- Try to make any function accept an array and return the new array updated so i can use the function and just save
