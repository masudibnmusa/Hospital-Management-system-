# Medicine & Equipment Feature

## Overview
A new "Medicine & Equipment" menu has been added to the Main Menu for managing hospital medicine inventory.

## Changes Made

### 1. New Structure Added
```c
typedef struct {
    int id;
    char name[100];
    char category[50];       // Tablet, Syrup, Injection, etc.
    char manufacturer[100];
    float price;
    int quantity;
    char expiry_date[20];    // DD/MM/YYYY
    char description[200];
} Medicine;
```

### 2. Global Variables
```c
Medicine medicines[500];     // Array to store up to 500 medicines
int medicine_count = 0;      // Current count of medicines
```

### 3. New Functions

#### `addMedicine()` - Add medicine to inventory
**Features:**
- Auto-generates unique Medicine ID (starting from 3001)
- Collects medicine information:
  - Name
  - Category (Tablet/Syrup/Injection/Capsule/etc.)
  - Manufacturer
  - Price per unit
  - Quantity in stock
  - Expiry date (validated DD/MM/YYYY format)
  - Description/usage
- Validates expiry date format
- Saves to `medicines.dat` file
- Shows success confirmation with all details

#### `saveMedicineData()` - Save medicine data
- Saves medicine records to `medicines.dat`
- Binary file format for data integrity

#### `loadMedicineData()` - Load medicine data
- Loads medicine records from `medicines.dat`
- Automatically called on program startup
- Includes capacity guards for safety

#### `getNewMedicineId()` - Generate new medicine ID
- Returns next available ID (starting from 3001)
- Prevents ID conflicts

#### `medicineManagementMenu()` - Medicine menu
- Access point for medicine operations
- Currently includes:
  1. Add Medicine
  2. Back to Main Menu

### 4. Main Menu Updated

**Before:**
```
10. Admin panel
11. Exit
```

**After:**
```
10. Medicine & Equipment
11. Admin panel
12. Exit
```

## How to Use

### Adding a Medicine

1. From Main Menu, select **"10. Medicine & Equipment"**
2. Select **"1. Add Medicine"**
3. Enter medicine details:
   - **Medicine name**: e.g., "Paracetamol 500mg"
   - **Category**: e.g., "Tablet"
   - **Manufacturer**: e.g., "PharmaCorp"
   - **Price per unit**: e.g., 2.50
   - **Quantity in stock**: e.g., 1000
   - **Expiry date**: Must be in DD/MM/YYYY format (e.g., 31/12/2025)
   - **Description/usage**: e.g., "For fever and pain relief"
4. Medicine is added and saved automatically
5. Unique Medicine ID is assigned

## File Structure

### New File
- **medicines.dat** - Binary file storing medicine inventory data

### Directory Structure
```
Hospital Management System/
├── hospital.exe
├── *.dat (database files)
│   ├── patients.dat
│   ├── doctors.dat
│   ├── appointments.dat
│   ├── bills.dat
│   ├── staff.dat
│   └── medicines.dat      ← NEW
├── backups/
├── exports/
└── docs/
```

## Data Validation

- **Expiry Date**: Must be in DD/MM/YYYY format
  - Valid: 31/12/2025
  - Invalid: 2025-12-31, 31-12-2025, 32/12/2025
- **Price**: Must be a positive float value
- **Quantity**: Must be a positive integer
- **Capacity**: Maximum 500 medicines in inventory

## Safety Features

- Unique ID generation prevents duplicates
- Date validation ensures correct format
- Capacity check (max 500 medicines)
- Auto-save after adding medicine
- Binary file storage for data integrity

## Future Enhancements (Possible)

The menu structure supports adding more options:
- View All Medicines
- Search Medicine
- Update Medicine Stock
- Remove Medicine
- Check Expiring Medicines
- Generate Inventory Report
- Medicine Usage History
- Low Stock Alerts

## Technical Details

### Medicine ID Range
- Starts from: 3001
- Increments automatically
- No ID conflicts with other entities:
  - Patients: 1001+
  - Doctors: 101+
  - Staff: 2001+
  - Bills: 10001+
  - Appointments: 5001+
  - **Medicines: 3001+**

### Storage
- File: medicines.dat
- Format: Binary
- Structure: Count (int) + Array of Medicine structs

### Compilation
Successfully compiles with no errors:
```bash
gcc hospital.c -o hospital.exe
```

## Code Statistics

**Lines Added:** ~145 lines
- Structure definition: 9 lines
- Function prototypes: 5 lines
- Functions: ~120 lines
- Menu update: ~11 lines

**Files Modified:**
- hospital.c (1 file)

**New Files Created:**
- medicines.dat (auto-generated)
- MEDICINE_FEATURE.md (documentation)

## Integration with Existing System

The medicine module is fully integrated:
- ✅ Loads on program startup
- ✅ Saves automatically after adding
- ✅ Accessible from Main Menu
- ✅ Uses existing color scheme
- ✅ Follows existing code patterns
- ✅ Compatible with database backup/restore

## Notes

- Medicine data is loaded automatically when the program starts
- All medicine operations are saved immediately
- The expiry date uses the same validation as other dates in the system
- Medicine IDs start from 3001 to avoid conflicts with other entities
- The system can store up to 500 different medicines
