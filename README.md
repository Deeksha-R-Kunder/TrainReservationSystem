# Train Reservation System

A command-line-based Train Reservation System for passengers to book train tickets and for administrators to manage train details.

## Features

- **Admin Menu**:

  - Add train details
  - View all trains
  - Protected with a hardcoded admin password

- **Passenger Features**:

  - Sign up with a unique username and password
  - Log in to access passenger-specific options
  - Book tickets for available trains
  - View ticket details
  - Change password

## How to Use

1. **Admin Access**:

   - Select the "Admin Login" option.
   - Enter the admin password (default: `PASSWORD`).
   - Manage train details through the admin menu.

2. **Passenger Access**:

   - Sign up using a unique username and password.
   - Log in to book tickets, view reservations, or change the password.

3. **Ticket Booking**:

   - Enter the train number to book a ticket.
   - Provide passenger details and class type.
   - Reservation number is generated automatically.

## File Storage

- **`trains.dat`**: Stores train details.
- **`tickets.dat`**: Stores ticket reservations.
- **`users.dat`**: Stores user credentials.

## Prerequisites

- C++ compiler (e.g., GCC)
- Basic knowledge of command-line operations

## Compilation and Execution

1. Compile the program:
   ```sh
   g++ -o TrainReservationSystem main.cpp
   ```
2. Run the program:
   ```sh
   ./TrainReservationSystem
   ```

## Notes

- Hardcoded admin password: `PASSWORD` (can be modified in the source code).
- Train and ticket data are stored in binary files for persistence.
- For input validation and a smooth user experience, ensure correct data entry.

## Limitations

- No GUI; this is a command-line application.
- Train and ticket records are not encrypted.
- Limited input validation.

## Future Enhancements

- Add encryption for stored data.
- Implement dynamic admin password management.
- Include a graphical user interface (GUI).
- Expand features for advanced ticket management.

