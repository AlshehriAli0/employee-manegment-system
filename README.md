# Employee Management System 👥✨

##### The Employee Management System is a comprehensive application designed to streamline the management of employee records and related operations. This README provides an overview of the app's functionality and how to use it effectively.

<br/><br/>

## App Functionality 🚀

The Employee Management System offers two main submenus: Employee Submenu and Admin Submenu.


### Employee Submenu 👤

#### The Employee Submenu allows individual employees to perform the following tasks:

- Login Authentication 🔐: Employees can securely log in using their credentials to access their personal information.
- Display Information 👀: Once logged in, employees can view their personal details, such as name, contact information, and employment details.
- Save Personal Data 💾: Employees have the option to save any desired personal data for future reference.
- Logout 🚪: Employees can log out of the system after completing their tasks.

---

### Admin Submenu 👑

##### The Admin Submenu provides administrators with powerful tools to manage employee records efficiently:

- Login Authentication 🔒: Administrators can log in using their credentials to access the admin panel.
### CRUD Operations ⚙️:

- Create an Employee's Record 📝: Administrators can create new employee records, including setting up user accounts and passwords for the Employee Submenu.
- Read/Display Record 📖: Administrators can view and display existing employee records.
- Update/Edit Record ✏️: Administrators can update and modify employee records as needed.
- Delete Record ❌: Administrators can remove employee records from the system.

- Logout 🚪: Administrators can log out of the system after completing their tasks.

<br/><br/>


## Setup 🔧

### To set up the Employee Management System, follow these steps:

- Create an env.txt file in the same directory as the application.
  In the env.txt file, add the following lines:
  - Line 1: Your PostgreSQL database connection string.
  - Line 2: The encryption secret key for data security.
- Install the [libpq](https://www.postgresql.org/docs/9.5/libpq.html) library and set up all the library and headers configurations.🔌

- Compile the program using:
```zsh
  g++ -I"C:\Program Files\PostgreSQL\16\include" -L"C:\Program Files\PostgreSQL\16\lib" -o main.exe main.cpp -lpq
```
- Start the main.exe, and now you're up and running. 🏡


<br/><br/>


## Speed and Performance ⚡️

#### One of the key features we take pride in is the exceptional speed and performance of the Employee Management System. Thanks to our optimized algorithms and efficient data handling, you'll experience lightning-fast response times, ensuring a smooth and seamless user experience.

<br/><br/>


## Feature Plans 🚀

### In addition to the current functionality, we have exciting plans to enhance the Employee Management System with the following features:

- Employee Daily Performance/Attendance Tracking: We aim to introduce a feature that allows administrators to track and record daily performance and attendance for each employee.
- Automated Weekly Reports with AI: Leveraging the power of AI, we will implement an automated weekly report generation system. These reports will be sent to administrators via email, providing comprehensive insights and analysis on employee performance and attendance.

<br/><br/>


## Contributors 🌟

- [Ali Alshehri](https://github.com/AlshehriAli0)
- [Abdullah Alhamly](https://github.com/173p)
