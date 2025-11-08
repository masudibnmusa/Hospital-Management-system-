# 🏥 Hospital Management System

A comprehensive console-based Hospital Management System written in C, featuring patient management, staff administration, medicine inventory, billing, and advanced analytics.

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)](https://github.com)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

---

## 📋 Table of Contents

- [Features](#-features)
- [System Requirements](#-system-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Module Overview](#-module-overview)
- [File Structure](#-file-structure)
- [Admin Credentials](#-admin-credentials)
- [Screenshots](#-screenshots)
- [Documentation](#-documentation)
- [Contributing](#-contributing)
- [License](#-license)

---

## ✨ Features

### 👥 Patient Management
- ✅ Add new patients with complete medical history
- ✅ View all patients with detailed information
- ✅ Search patients by ID or name
- ✅ Track patient demographics and contact information

### 👨‍⚕️ Doctor Management
- ✅ Add and remove doctors
- ✅ Edit doctor information
- ✅ View doctor statistics and performance
- ✅ Track specializations and availability
- ✅ Doctor-appointment analytics

### 📅 Appointment System
- ✅ Schedule patient appointments
- ✅ View all appointments
- ✅ Date and time validation (12-hour format)
- ✅ Appointment status tracking
- ✅ Doctor-patient appointment linking

### 💰 Billing System
- ✅ Generate detailed patient bills
- ✅ Multiple charge categories (consultation, medicine, room, lab)
- ✅ Automatic total calculation
- ✅ Bill status tracking
- ✅ Export bills to text files

### 👔 Staff Management
- ✅ Add, edit, and delete staff members
- ✅ Track qualifications and departments
- ✅ Assign duty rosters (Morning/Evening/Night shifts)
- ✅ Search staff by ID, name, role, or department
- ✅ Salary and join date tracking

### 💊 Medicine & Equipment
- ✅ Add medicines to inventory
- ✅ View available medicine stock with color-coded status
- ✅ Update stock quantities (Add/Reduce/Set)
- ✅ Automatic expiry date checking
- ✅ Low stock alerts (< 50 units)
- ✅ Inventory value calculation
- ✅ Category-based organization

### 📊 Reports & Analytics
- ✅ Daily revenue reports
- ✅ Monthly revenue reports with breakdown
- ✅ Yearly revenue reports with statistics
- ✅ Unpaid bills tracking
- ✅ Department-wise revenue analysis
- ✅ Doctor performance statistics

### 💾 Database Management
- ✅ **Backup Database** - Timestamped backups
- ✅ **Restore Database** - From any backup
- ✅ **Export to CSV/Excel** - All data exportable
- ✅ **Delete All Data** - With double confirmation

### 🔐 Security
- ✅ Admin authentication system
- ✅ Password masking during login
- ✅ Multiple login attempts protection
- ✅ Role-based access control

### 🎨 User Interface
- ✅ Color-coded console output
- ✅ Professional menu layouts
- ✅ Clear error messages
- ✅ Progress indicators
- ✅ Intuitive navigation

---

## 💻 System Requirements

### Minimum Requirements
- **OS**: Windows 7/8/10/11 or Linux (Ubuntu, Debian, etc.)
- **Compiler**: GCC 4.8 or later
- **RAM**: 512 MB
- **Storage**: 50 MB free space
- **Terminal**: Console with ANSI color support

### Recommended
- **OS**: Windows 10/11 or Linux (Latest)
- **Compiler**: GCC 9.0 or later
- **RAM**: 1 GB or more
- **Storage**: 100 MB free space

---

## 🚀 Installation

### Windows

1. **Install GCC Compiler** (if not installed)
   ```bash
   # Download and install MinGW or TDM-GCC
   # Add to PATH environment variable
   ```

2. **Clone or Download the Repository**
   ```bash
   git clone <repository-url>
   cd "Hospital Management System"
   ```

3. **Compile the Program**
   ```bash
   gcc hospital.c -o hospital.exe
   ```

4. **Run the Program**
   ```bash
   hospital.exe
   ```

### Linux

1. **Install GCC** (if not installed)
   ```bash
   sudo apt update
   sudo apt install gcc
   ```

2. **Clone or Download the Repository**
   ```bash
   git clone <repository-url>
   cd "Hospital Management System"
   ```

3. **Compile the Program**
   ```bash
   gcc hospital.c -o hospital
   ```

4. **Run the Program**
   ```bash
   ./hospital
   ```

---

## 📖 Usage

### Starting the Program

Run the compiled executable:
- **Windows**: `hospital.exe`
- **Linux**: `./hospital`

### Main Menu Options

```
========================================
   HOSPITAL MANAGEMENT SYSTEM          
========================================

=== MAIN MENU ===
1. Add New Patient
2. View All Patients
3. Search Patient
4. View All Doctors
5. Search Doctor
6. Schedule Appointment
7. View Appointments
8. Generate Bill
9. View Bills
10. Medicine & Equipment
11. Admin panel
12. Exit
========================================
```

### Admin Panel Access

1. Select **"11. Admin panel"** from Main Menu
2. Enter credentials:
   - **Username**: `admin`
   - **Password**: `admin123`
3. Access admin features

---

## 🧩 Module Overview

### 1️⃣ Patient Management
**Purpose**: Manage patient records and information

**Features**:
- Patient registration with auto-generated ID
- Medical history tracking
- Contact information management
- Search by ID or name

**Data Stored**: ID, Name, Age, Gender, Contact, Address, Medical History

---

### 2️⃣ Doctor Management (Admin Only)
**Purpose**: Manage hospital doctors and their information

**Features**:
- Add/Remove doctors
- Edit doctor information
- View doctor statistics
- Track specializations
- Monitor appointment load

**Data Stored**: ID, Name, Specialization, Contact, Availability

---

### 3️⃣ Appointment System
**Purpose**: Schedule and track patient appointments

**Features**:
- Date validation (DD/MM/YYYY)
- Time validation (12-hour format with AM/PM)
- Patient-doctor linking
- Appointment status tracking

**Data Stored**: ID, Patient ID, Doctor ID, Date, Time, Purpose, Status

---

### 4️⃣ Billing System
**Purpose**: Generate and manage patient bills

**Features**:
- Multiple charge categories
- Automatic total calculation
- Bill export to text file
- Payment status tracking

**Data Stored**: Bill No, Patient ID, Consultation Fee, Medicine Charges, Room Charges, Lab Charges, Total Amount, Date, Status

---

### 5️⃣ Staff Management (Admin Only)
**Purpose**: Manage hospital staff and duty rosters

**Features**:
- Staff CRUD operations
- Duty roster assignment
- Department organization
- Salary tracking

**Data Stored**: ID, Name, Role, Department, Contact, Email, Address, Qualification, Salary, Join Date, Shift, Status

---

### 6️⃣ Medicine & Equipment
**Purpose**: Manage medicine inventory

**Features**:
- **Add Medicine**: Register new medicines
- **Available Medicine**: View stock with color-coding
  - 🟢 Green: Good stock (50+ units)
  - 🟡 Yellow: Low stock (< 50 units)
  - 🔴 Red: Out of stock or expired
- **Update Stock**: Three update methods
  - Add Stock (restocking)
  - Reduce Stock (dispensing)
  - Set New Stock (inventory count)
- Automatic expiry detection
- Inventory value calculation

**Data Stored**: ID, Name, Category, Manufacturer, Price, Quantity, Expiry Date, Description

---

### 7️⃣ Reports & Analytics (Admin Only)
**Purpose**: Generate business intelligence reports

**Available Reports**:
1. **Daily Revenue Report** - Today's earnings
2. **Monthly Revenue Report** - Month-wise breakdown
3. **Yearly Revenue Report** - Annual statistics
4. **Unpaid Bills Report** - Outstanding payments
5. **Department Revenue** - Performance by specialization

---

### 8️⃣ Database Management (Admin Only)
**Purpose**: Backup, restore, and maintain data

**Features**:
1. **Backup Database**
   - Creates timestamped backups
   - Stored in `backups/YYYYMMDD_HHMMSS/`
   - All .dat files included

2. **Restore Database**
   - Lists available backups
   - Select by timestamp
   - Confirmation required
   - Restart needed after restore

3. **Export to CSV/Excel**
   - Exports all data to CSV format
   - Stored in `exports/` directory
   - Compatible with Excel, Google Sheets
   - Timestamped filenames

4. **Delete All Data**
   - Removes all records
   - Double confirmation required
   - ⚠️ Cannot be undone

---

## 📁 File Structure

```
Hospital Management System/
│
├── hospital.c                          # Main source code
├── hospital.exe                        # Compiled executable (Windows)
├── README.md                           # This file
│
├── Data Files (.dat)
│   ├── patients.dat                    # Patient records
│   ├── doctors.dat                     # Doctor records
│   ├── appointments.dat                # Appointment records
│   ├── bills.dat                       # Billing records
│   ├── staff.dat                       # Staff records
│   └── medicines.dat                   # Medicine inventory
│
├── backups/                            # Database backups
│   ├── 20250108_105530/               # Backup folder (timestamp)
│   │   ├── patients.dat
│   │   ├── doctors.dat
│   │   ├── appointments.dat
│   │   ├── bills.dat
│   │   ├── staff.dat
│   │   └── medicines.dat
│   └── ...
│
├── exports/                            # CSV exports
│   ├── patients_20250108_105530.csv
│   ├── doctors_20250108_105530.csv
│   ├── appointments_20250108_105530.csv
│   ├── bills_20250108_105530.csv
│   ├── staff_20250108_105530.csv
│   └── medicines_20250108_105530.csv
│
└── Documentation/
    ├── DATABASE_MANAGEMENT_FEATURE.md
    ├── MEDICINE_FEATURE.md
    ├── AVAILABLE_MEDICINE_SUMMARY.txt
    ├── UPDATE_STOCK_FEATURE.txt
    ├── QUICK_REFERENCE.txt
    └── CHANGELOG.md
```

---

## 🔑 Admin Credentials

### Default Login
- **Username**: `admin`
- **Password**: `admin123`

### Security Notes
- Change default password in production
- Located in `adminLogin()` function (line ~1410)
- Maximum 3 login attempts
- Password is masked during input

### Changing Admin Password

Edit the source code:
```c
// Line ~1410 in hospital.c
if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
    // Change "admin123" to your new password
}
```

---

## 📸 Screenshots

### Main Menu
```
========================================
   HOSPITAL MANAGEMENT SYSTEM          
========================================

=== MAIN MENU ===
1. Add New Patient
2. View All Patients
...
```

### Medicine Stock View
```
========================================
        AVAILABLE MEDICINE              
========================================

Total Medicines in Stock: 5

ID   Medicine Name            Category      Qty   Price   Expiry
3001 Paracetamol 500mg       Tablet        500   $2.50   31/12/2025
3002 Amoxicillin 250mg       Capsule       30    $5.00   15/06/2024
...

=== INVENTORY SUMMARY ===
Total Medicines        : 5
Low Stock Items        : 2 (< 50 units)
Expired Items          : 1
Total Units in Stock   : 1575
Total Inventory Value  : $4,737.50
```

---

## 📚 Documentation

### Feature Documentation
- `DATABASE_MANAGEMENT_FEATURE.md` - Backup, restore, export, delete features
- `MEDICINE_FEATURE.md` - Medicine inventory management
- `AVAILABLE_MEDICINE_SUMMARY.txt` - Stock viewing feature
- `UPDATE_STOCK_FEATURE.txt` - Stock update operations
- `QUICK_REFERENCE.txt` - Quick user guide
- `CHANGELOG.md` - Version history

### Code Documentation
- **Lines of Code**: ~3,500+
- **Functions**: 50+
- **Data Structures**: 6 (Patient, Doctor, Appointment, Bill, Staff, Medicine)
- **Features**: 8 major modules

---

## 🎯 Key Highlights

### ID Ranges
- **Patients**: 1001+
- **Doctors**: 101+
- **Staff**: 2001+
- **Medicines**: 3001+
- **Appointments**: 5001+
- **Bills**: 10001+

### Date Format
- **Format**: DD/MM/YYYY
- **Validation**: Full calendar validation (leap years supported)
- **Example**: 31/12/2025

### Time Format
- **Format**: HH:MM AM/PM (12-hour)
- **Validation**: Valid hour (1-12) and minute (0-59)
- **Example**: 10:30 AM

### Color Coding
- 🟢 **GREEN**: Success, good stock
- 🟡 **YELLOW**: Warning, low stock
- 🔴 **RED**: Error, out of stock, expired
- 🔵 **BLUE**: Information, prompts
- 🟣 **MAGENTA**: Special options
- 🔷 **CYAN**: Headers, dividers

---

## 🔧 Troubleshooting

### Compilation Errors

**Problem**: Undefined reference errors
```bash
Solution: Ensure all functions are implemented
```

**Problem**: ANSI colors not working
```bash
Solution: Use terminal with ANSI support (Windows 10+, Linux terminal)
```

### Runtime Errors

**Problem**: Data not loading
```bash
Solution: Check if .dat files exist in the same directory
```

**Problem**: Backup/Restore not working
```bash
Solution: Ensure write permissions for backups/ directory
```

---

## 🚦 Getting Started Guide

### First Time Setup

1. **Compile the Program**
   ```bash
   gcc hospital.c -o hospital.exe
   ```

2. **Run the Program**
   ```bash
   hospital.exe
   ```

3. **Add Sample Data**
   - Add a doctor first
   - Add a patient
   - Add medicines to inventory
   - Schedule an appointment
   - Generate a bill

4. **Test Admin Features**
   - Login to admin panel
   - Try backup/restore
   - Export data to CSV
   - View reports

5. **Test Medicine Management**
   - Add medicines
   - View stock
   - Update quantities
   - Check expiry warnings

---

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Coding Standards
- Follow existing code style
- Add comments for complex logic
- Test before submitting
- Update documentation

---

## 📝 Future Enhancements

### Planned Features
- [ ] Patient appointment history
- [ ] Medicine prescription tracking
- [ ] Lab test management
- [ ] Room/bed allocation system
- [ ] Insurance claim processing
- [ ] SMS/Email notifications
- [ ] Web-based dashboard
- [ ] Mobile app integration
- [ ] Advanced analytics with charts
- [ ] Multi-user support with roles

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Hospital Management System**
- Version: 2.0
- Last Updated: January 2025

---

## 🙏 Acknowledgments

- Developed as a comprehensive console-based management system
- Built with C programming language
- Cross-platform compatibility (Windows/Linux)
- Designed for educational and practical use

---

## 📞 Support

For issues, questions, or suggestions:
1. Check the documentation in the `/Documentation` folder
2. Review the troubleshooting section
3. Open an issue on GitHub
4. Contact the development team

---

## ⚠️ Important Notes

1. **Backup Regularly**: Use the backup feature frequently
2. **Default Password**: Change admin password before production use
3. **Data Loss**: Delete All Data cannot be undone - backup first
4. **Restart Required**: After database restore, restart the application
5. **File Permissions**: Ensure write permissions for data files

---

## 🔗 Quick Links

- [Database Management Guide](DATABASE_MANAGEMENT_FEATURE.md)
- [Medicine Management Guide](MEDICINE_FEATURE.md)
- [Quick Reference](QUICK_REFERENCE.txt)
- [Update Stock Guide](UPDATE_STOCK_FEATURE.txt)
- [Changelog](CHANGELOG.md)

---

## 📊 Statistics

- **Total Functions**: 50+
- **Total Lines**: 3,500+
- **Data Files**: 6
- **Menu Options**: 12 (Main Menu)
- **Admin Features**: 4 major categories
- **Report Types**: 5
- **Compilation Time**: < 5 seconds
- **Runtime Memory**: < 10 MB

---

<div align="center">

**Made with ❤️ for Healthcare Management**

⭐ Star this repo if you find it useful!

[Report Bug](https://github.com/issues) · [Request Feature](https://github.com/issues)

</div>
