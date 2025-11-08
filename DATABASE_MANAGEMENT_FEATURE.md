# Database Management Feature

## Overview
A new "Database Management" menu has been added to the Admin Panel with backup and restore functionality.

## Changes Made

### 1. Function Prototypes Added (Line 152-154)
```c
void backupData();
void restoreData();            // NEW - Restore from backup
void databaseManagementMenu(); // NEW - Database management menu
```

### 2. Admin Menu Updated (Line 383-384)
Changed from directly calling `backupData()` to calling the new `databaseManagementMenu()`:
```c
case 4:
    databaseManagementMenu();
    break;
```

### 3. New Functions Added

#### `restoreData()` Function (Lines 2402-2498)
- Lists available backups from the `backups/` directory
- Prompts user to enter backup folder name (timestamp format: YYYYMMDD_HHMMSS)
- Verifies backup exists
- Shows warning about overwriting current data
- Asks for confirmation (y/n)
- Restores all .dat files from the selected backup:
  - patients.dat
  - doctors.dat
  - appointments.dat
  - bills.dat
  - staff.dat
- Displays restore progress and results
- Notifies user to restart application to load restored data

#### `databaseManagementMenu()` Function (Lines 2500-2535)
A new submenu with three options:
1. **Backup Database** - Creates timestamped backup of all data files
2. **Restore Database** - Restores data from a previous backup
3. **Back to Admin Menu** - Returns to admin panel

## Menu Structure
```
Admin Panel
  └── 4. Database Management
       ├── 1. Backup Database (existing backupData() function)
       ├── 2. Restore Database (new restoreData() function)
       ├── 3. Export to CSV/Excel (new exportToCSV() function)
       ├── 4. Delete All Data (new deleteAllData() function)
       └── 5. Back to Admin Menu
```

## How to Use

### Creating a Backup
1. Login to Admin Panel (username: admin, password: admin123)
2. Select option 4: Database Management
3. Select option 1: Backup Database
4. Backup will be created in `backups/YYYYMMDD_HHMMSS/` folder

### Restoring from Backup
1. Login to Admin Panel
2. Select option 4: Database Management
3. Select option 2: Restore Database
4. View list of available backups
5. Enter the backup folder name (e.g., 20250108_105530)
6. Confirm the restore operation (y/n)
7. Restart the application after successful restore

## Safety Features
- Backup creates timestamped folders to avoid overwriting
- Restore shows warning before overwriting current data
- Restore requires explicit confirmation (y/n)
- Both functions display detailed progress information
- Files are copied using binary mode to preserve data integrity

## Compilation
The program compiles successfully with no errors or warnings:
```bash
gcc hospital.c -o hospital.exe
```

### Exporting to CSV/Excel
1. Login to Admin Panel
2. Select option 4: Database Management
3. Select option 3: Export to CSV/Excel
4. Data will be exported to `exports/` directory with timestamped filenames
5. Open CSV files in Excel, Google Sheets, or any spreadsheet application

### Deleting All Data
1. Login to Admin Panel
2. Select option 4: Database Management
3. Select option 4: Delete All Data
4. Read the warning carefully - it shows how many records will be deleted
5. Confirm TWICE (y/n) to proceed with deletion
6. All data files and memory will be cleared

## Detailed Function Descriptions

### 3. `exportToCSV()` Function
**Purpose**: Export all database records to CSV files for Excel/spreadsheet analysis

**Features**:
- Creates timestamped CSV files in `exports/` directory
- Exports 5 separate files:
  - `patients_YYYYMMDD_HHMMSS.csv` - Patient records
  - `doctors_YYYYMMDD_HHMMSS.csv` - Doctor records
  - `appointments_YYYYMMDD_HHMMSS.csv` - Appointment records
  - `bills_YYYYMMDD_HHMMSS.csv` - Billing records
  - `staff_YYYYMMDD_HHMMSS.csv` - Staff records
- Includes column headers for easy reading
- Properly quotes text fields to handle commas in data
- Skips empty datasets (no records to export)
- Shows progress and count of exported records

**Use Cases**:
- Data analysis in Excel/Google Sheets
- Creating reports and presentations
- Sharing data with other systems
- Archiving data in readable format
- Importing into other database systems

### 4. `deleteAllData()` Function
**Purpose**: Permanently delete all database records and files

**Features**:
- Shows detailed warning with record counts for each data type
- Requires TWO confirmations to prevent accidental deletion
- Clears all memory arrays (resets counts to 0)
- Deletes all .dat files from disk
- Provides feedback on deletion progress
- Cannot be undone (emphasizes backup importance)

**Safety Measures**:
- Double confirmation required (y/n twice)
- Shows exact number of records that will be deleted
- Warns user to create backup first
- Clear visual warnings with RED text
- Displays success/failure for each file deletion

**Use Cases**:
- Starting fresh with new data
- Testing the system
- Removing demo/test data
- System maintenance
- Privacy compliance (data deletion requests)

## Notes
- Backups are stored in the `backups/` directory with timestamp subdirectories
- After restoring, you must restart the application to load the restored data
- The restore function uses cross-platform directory listing (Windows/Linux)
- CSV exports are saved in the `exports/` directory
- All exported CSV files are compatible with Microsoft Excel, Google Sheets, LibreOffice Calc
- Delete All Data cannot be undone - always backup before using this feature
- Timestamps in filenames use format: YYYYMMDD_HHMMSS (e.g., 20250108_110530)
