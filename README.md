## Employee Management System 💻

### App Flow

- [x] Connect to db
- [x] Main Menu
  - [] Employee Submenu
    - [] Login Authentication
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
- [x] User Creation fun
- [x] User Deletion fun
- [] user inquiry fun
- [] Sort fun
- [x] user editing fun
- [] Fun to save chosen data in a .txt
- [] Fun to search by any chosen field

### User Structer

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
