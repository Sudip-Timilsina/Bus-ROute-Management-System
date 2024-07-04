# Bus Route Management System

## Overview

The Bus Route Management System is a console-based application designed to manage bus routes, including adding, displaying, and deleting routes. The system includes functionalities for both admin and user interactions. Users can register and log in to view available routes, while admins have additional privileges to manage the bus routes.

## Features

### Admin Features
- **Admin Login**: Secure login for admin with predefined credentials.
- **Add Route**: Allows the admin to add new bus routes.
- **Delete Route**: Allows the admin to delete existing bus routes by specifying the source and destination.
- **Display All Routes**: Admin can view all available bus routes.
- **Display User Logins**: Admin can view all registered user login information.

### User Features
- **User Registration**: New users can register by providing a unique username and a password.
- **User Login**: Registered users can log in to the system.
- **Display Routes by Choice**: Users can filter and view bus routes based on source and destination.
- **Display All Routes**: Users can view all available bus routes.

## Files

- `bus_routes.txt`: Stores the bus routes information.
- `user_data.txt`: Stores the registered user login information.



### Prerequisites

- A C compiler (e.g., GCC)
- A Windows environment for `conio.h` and `windows.h` functionalities.

### Compilation

To compile the program, use the following command:

```bash
gcc -o bus_route_management bus_route_management.c
