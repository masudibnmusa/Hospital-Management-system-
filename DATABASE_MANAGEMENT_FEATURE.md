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
       └── 3. Back to Admin Menu
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

## Notes
- Backups are stored in the `backups/` directory with timestamp subdirectories
- After restoring, you must restart the application to load the restored data
- The restore function uses cross-platform directory listing (Windows/Linux)
