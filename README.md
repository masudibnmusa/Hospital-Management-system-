Hospital Management System
A comprehensive C-based Hospital Management System that provides efficient management of patients, doctors, staff, appointments, and billing operations with a user-friendly console interface.

🏥 Features
Core Functionalities
Patient Management: Add, view, and search patient records

Doctor Management: Comprehensive doctor information and scheduling

Appointment System: Schedule and manage patient-doctor appointments

Billing System: Generate detailed bills and invoices

Staff Management: Complete staff roster and duty management

User Roles
General Users: Access basic patient and doctor information

Administrators: Full system access with advanced management capabilities

🚀 Installation
Prerequisites
GCC Compiler

Any C-compatible IDE or terminal

Windows/Linux/macOS operating system

Compilation
bash
gcc -o hospital_management hospital_management.c
Running the Application
bash
./hospital_management
📋 System Modules
1. Patient Management
Add new patients with complete medical history

View all patient records

Search patients by ID or name

Store contact information and addresses

2. Doctor Management
Add and remove doctors

View doctor schedules and specializations

Search doctors by ID, name, or specialization

Edit doctor information

View doctor statistics and performance

3. Appointment System
Schedule patient-doctor appointments

View all scheduled appointments

Track appointment status

Manage time slots and availability

4. Billing System
Generate detailed patient bills

Calculate consultation fees, medicine charges, room charges, and lab fees

Save bills as text files

View billing history

5. Staff Management
Add and manage hospital staff (nurses, receptionists, technicians)

Assign duty rosters and shifts

Track staff qualifications and contact information

Manage staff salaries and departments

6. Administrative Features
Secure admin login with password protection

Comprehensive system management

Data backup and restoration

System statistics and reporting

🔐 Admin Access
Default Admin Credentials:

Username: admin

Password: admin123

Note: Change these credentials in the source code for production use.

💾 Data Storage
The system automatically saves data to multiple binary files:

patients.dat - Patient records

doctors.dat - Doctor information

appointments.dat - Appointment schedules

bills.dat - Billing information

staff.dat - Staff records

🎨 User Interface Features
Color-coded console output for better readability

Cross-platform compatibility (Windows/Linux/macOS)

Password masking for secure login

Formatted displays with clear sections

Interactive menus with navigation options

📊 System Statistics
Doctor performance reports

Appointment analytics

Specialization distribution

Staff management metrics

Billing summaries

🔧 Technical Features
Modular Design: Separate functions for each module

Error Handling: Comprehensive input validation

Data Persistence: Automatic save/load functionality

Memory Management: Efficient array-based storage

Cross-platform: Compatible with major operating systems

📝 Usage Guide
Start the application and navigate through the main menu

Add patients and doctors to populate the system

Schedule appointments between patients and doctors

Generate bills for services rendered

Use admin panel for advanced management tasks

Save data regularly or use auto-save feature

🛠️ Customization
The system can be easily customized by modifying:

Color schemes in the #define sections

Array sizes for scaling the system

Admin credentials in the adminLogin() function

Charge structures in the billing module

⚠️ Limitations
Console-based interface (no GUI)

Fixed array sizes (modifiable in source code)

Basic file-based storage (no database)

Single admin account system

🔄 Future Enhancements
Potential improvements include:

Database integration

Graphical user interface

Multi-user support with roles

Email/SMS notifications

Advanced reporting and analytics

Web-based interface

📞 Support
For issues or modifications, contact with me .
