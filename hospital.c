#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Cross-platform screen clear function
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

// Structure definitions
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    char address[100];
    char medical_history[200];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
    char contact[15];
    char availability[50];
} Doctor;

typedef struct {
    int id;
    int patient_id;
    int doctor_id;
    char date[20];
    char time[10];
    char purpose[100];
    char status[20];
} Appointment;

typedef struct {
    int bill_no;
    int patient_id;
    float consultation_fee;
    float medicine_charges;
    float room_charges;
    float lab_charges;
    float total_amount;
    char date[20];
    char status[20];
} Bill;
typedef struct {
    int id;
    char name[50];
    char role[30];           // Nurse, Receptionist, Technician, etc.
    char department[50];
    char contact[15];
    char email[50];
    char address[100];
    char qualification[100];
    float salary;
    char join_date[20];
    char shift[20];          // Morning, Evening, Night
    char status[20];         // Active, Inactive
} Staff;

// Global arrays to store data
Patient patients[1000];
Doctor doctors[100];
Appointment appointments[500];
Bill bills[300];

int patient_count = 0;
int doctor_count = 0;
int appointment_count = 0;
int bill_count = 0;

Staff staff[200];
int staff_count = 0;

// Function prototypes
void clearScreen();
void pauseScreen();
void displayMenu();
void addPatient();
void addDoctor();
void viewPatients();
void searchPatient();
void viewDoctors();
void searchDoctor();
void scheduleAppointment();
void viewAppointments();
void generateBill();
void viewBills();
void staffManagementMenu();
void saveData();
void loadData();
int getNewPatientId();
int getNewDoctorId();
int getNewAppointmentId();
int getNewBillNo();
int adminLogin();
void adminMenu();
void removeDoctor();
void addStaff();
void viewStaff();
void editStaff();
void deleteStaff();
void assignDutyRoster();
void searchStaff();
int getNewStaffId();
void saveStaffData();
void loadStaffData();

// Utility function to clear screen
void clearScreen() {
    system(CLEAR_SCREEN);
}

// Utility function to pause screen
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

int main() {
    loadData();
    int choice;

    clearScreen();
    printf("========================================\n");
    printf("   HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("========================================\n");
    printf("\nPress Enter to continue...");
    getchar();

    do {
        clearScreen();
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1:
                addPatient();
                pauseScreen();
                break;
            case 2:
                viewPatients();
                pauseScreen();
                break;
            case 3:
                searchPatient();
                pauseScreen();
                break;
            case 4:
                viewDoctors();
                pauseScreen();
                break;
            case 5:
                searchDoctor();
                pauseScreen();
                break;
            case 6:
                scheduleAppointment();
                pauseScreen();
                break;
            case 7:
                viewAppointments();
                pauseScreen();
                break;
            case 8:
                generateBill();
                pauseScreen();
                break;
            case 9:
                viewBills();
                pauseScreen();
                break;
            case 10:
                if(adminLogin()) {
                    adminMenu();
                }
                pauseScreen();
                break;
            case 11:
                saveData();
                printf("========================================\n");
                printf("   Thank you for using Hospital        \n");
                printf("      Management System!               \n");
                printf("========================================\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                pauseScreen();
        }
    } while(choice != 11);

    return 0;
}

void displayMenu() {
    printf("========================================\n");
    printf("   HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("========================================\n");
    printf("\n=== MAIN MENU ===\n");
    printf("1. Add New Patient\n");
    printf("2. View All Patients\n");
    printf("3. Search Patient\n");
    printf("4. View All Doctors\n");
    printf("5. Search Doctor\n");
    printf("6. Schedule Appointment\n");
    printf("7. View Appointments\n");
    printf("8. Generate Bill\n");
    printf("9. View Bills\n");
    printf("10. Admin panel\n");
    printf("11. Exit\n");
    printf("========================================\n");
}

void addPatient() {
    if(patient_count >= 1000) {
        printf("Patient database full!\n");
        return;
    }

    Patient p;
    p.id = getNewPatientId();

    printf("========================================\n");
    printf("        ADD NEW PATIENT                \n");
    printf("========================================\n\n");

    printf("Enter patient name: ");
    getchar();
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter age: ");
    scanf("%d", &p.age);

    printf("Enter gender: ");
    scanf("%s", p.gender);

    printf("Enter contact number: ");
    scanf("%s", p.contact);

    printf("Enter address: ");
    getchar();
    fgets(p.address, 100, stdin);
    p.address[strcspn(p.address, "\n")] = 0;

    printf("Enter medical history: ");
    fgets(p.medical_history, 200, stdin);
    p.medical_history[strcspn(p.medical_history, "\n")] = 0;

    patients[patient_count++] = p;

    saveData();

    printf("\n========================================\n");
    printf("   PATIENT ADDED SUCCESSFULLY!         \n");
    printf("========================================\n");
    printf("Patient ID: %d\n", p.id);
    printf("Name: %s\n", p.name);
    printf("========================================\n");
}

void viewPatients() {
    printf("========================================\n");
    printf("        ALL PATIENTS                   \n");
    printf("========================================\n\n");

    if(patient_count == 0) {
        printf("No patients found!\n");
        return;
    }

    printf("ID\tName\t\t\tAge\tGender\tContact\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < patient_count; i++) {
        printf("%d\t%-20s\t%d\t%s\t%s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].contact);
    }
}

void searchPatient() {
    printf("========================================\n");
    printf("        SEARCH PATIENT                 \n");
    printf("========================================\n\n");

    if(patient_count == 0) {
        printf("No patients found!\n");
        return;
    }

    int choice;
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    clearScreen();

    if(choice == 1) {
        int id;
        printf("========================================\n");
        printf("      SEARCH PATIENT BY ID             \n");
        printf("========================================\n\n");
        printf("Enter patient ID: ");
        scanf("%d", &id);

        for(int i = 0; i < patient_count; i++) {
            if(patients[i].id == id) {
                printf("\n========================================\n");
                printf("        PATIENT FOUND                  \n");
                printf("========================================\n");
                printf("ID: %d\n", patients[i].id);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Gender: %s\n", patients[i].gender);
                printf("Contact: %s\n", patients[i].contact);
                printf("Address: %s\n", patients[i].address);
                printf("Medical History: %s\n", patients[i].medical_history);
                printf("========================================\n");
                return;
            }
        }
        printf("\nPatient not found!\n");
    }
    else if(choice == 2) {
        char name[50];
        printf("========================================\n");
        printf("      SEARCH PATIENT BY NAME           \n");
        printf("========================================\n\n");
        printf("Enter patient name: ");
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < patient_count; i++) {
            if(strstr(patients[i].name, name) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\t\tAge\tGender\tContact\n");
                    printf("------------------------------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%-20s\t%d\t%s\t%s\n",
                       patients[i].id, patients[i].name, patients[i].age,
                       patients[i].gender, patients[i].contact);
            }
        }
        if(!found) {
            printf("\nPatient not found!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}

void viewDoctors() {
    printf("========================================\n");
    printf("        ALL DOCTORS                    \n");
    printf("========================================\n\n");

    if(doctor_count == 0) {
        printf("No doctors found!\n");
        return;
    }

    printf("ID\tName\t\t\tSpecialization\t\tContact\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < doctor_count; i++) {
        printf("%d\t%-20s\t%-20s\t%s\n",
               doctors[i].id, doctors[i].name, doctors[i].specialization,
               doctors[i].contact);
    }
}

void searchDoctor() {
    printf("========================================\n");
    printf("        SEARCH DOCTOR                  \n");
    printf("========================================\n\n");

    if(doctor_count == 0) {
        printf("No doctors found!\n");
        return;
    }

    int choice;
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Specialization\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    clearScreen();

    if(choice == 1) {
        int id;
        printf("========================================\n");
        printf("      SEARCH DOCTOR BY ID              \n");
        printf("========================================\n\n");
        printf("Enter doctor ID: ");
        scanf("%d", &id);

        for(int i = 0; i < doctor_count; i++) {
            if(doctors[i].id == id) {
                printf("\n========================================\n");
                printf("        DOCTOR FOUND                   \n");
                printf("========================================\n");
                printf("ID: %d\n", doctors[i].id);
                printf("Name: %s\n", doctors[i].name);
                printf("Specialization: %s\n", doctors[i].specialization);
                printf("Contact: %s\n", doctors[i].contact);
                printf("Availability: %s\n", doctors[i].availability);
                printf("========================================\n");
                return;
            }
        }
        printf("\nDoctor not found!\n");
    }
    else if(choice == 2) {
        char name[50];
        printf("========================================\n");
        printf("      SEARCH DOCTOR BY NAME            \n");
        printf("========================================\n\n");
        printf("Enter doctor name: ");
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].name, name) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\t\tSpecialization\t\tContact\n");
                    printf("------------------------------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%-20s\t%-20s\t%s\n",
                       doctors[i].id, doctors[i].name, doctors[i].specialization,
                       doctors[i].contact);
            }
        }
        if(!found) {
            printf("\nDoctor not found!\n");
        }
    }
    else if(choice == 3) {
        char specialization[50];
        printf("========================================\n");
        printf("   SEARCH DOCTOR BY SPECIALIZATION     \n");
        printf("========================================\n\n");
        printf("Enter specialization: ");
        getchar();
        fgets(specialization, 50, stdin);
        specialization[strcspn(specialization, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].specialization, specialization) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\t\tSpecialization\t\tContact\n");
                    printf("------------------------------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%-20s\t%-20s\t%s\n",
                       doctors[i].id, doctors[i].name, doctors[i].specialization,
                       doctors[i].contact);
            }
        }
        if(!found) {
            printf("\nNo doctors found with this specialization!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}

void scheduleAppointment() {
    printf("========================================\n");
    printf("      SCHEDULE APPOINTMENT             \n");
    printf("========================================\n\n");

    if(appointment_count >= 500) {
        printf("Appointment database full!\n");
        return;
    }

    if(patient_count == 0 || doctor_count == 0) {
        printf("No patients or doctors available!\n");
        return;
    }

    Appointment a;
    a.id = getNewAppointmentId();

    printf("Available Patients:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewPatients();
    printf("\nEnter patient ID: ");
    scanf("%d", &a.patient_id);

    printf("\nAvailable Doctors:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewDoctors();
    printf("\nEnter doctor ID: ");
    scanf("%d", &a.doctor_id);

    printf("\nEnter date (DD/MM/YYYY): ");
    scanf("%s", a.date);

    printf("Enter time (HH:MM): ");
    scanf("%s", a.time);

    printf("Enter purpose: ");
    getchar();
    fgets(a.purpose, 100, stdin);
    a.purpose[strcspn(a.purpose, "\n")] = 0;

    strcpy(a.status, "Scheduled");

    appointments[appointment_count++] = a;

    saveData();

    printf("\n========================================\n");
    printf("  APPOINTMENT SCHEDULED SUCCESSFULLY!  \n");
    printf("========================================\n");
    printf("Appointment ID: %d\n", a.id);
    printf("Date: %s\n", a.date);
    printf("Time: %s\n", a.time);
    printf("========================================\n");
}

void viewAppointments() {
    printf("========================================\n");
    printf("        ALL APPOINTMENTS               \n");
    printf("========================================\n\n");

    if(appointment_count == 0) {
        printf("No appointments found!\n");
        return;
    }

    printf("ID\tPatient ID\tDoctor ID\tDate\t\tTime\tStatus\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < appointment_count; i++) {
        printf("%d\t%d\t\t%d\t\t%s\t%s\t%s\n",
               appointments[i].id, appointments[i].patient_id,
               appointments[i].doctor_id, appointments[i].date,
               appointments[i].time, appointments[i].status);
    }
}

void generateBill() {
    printf("========================================\n");
    printf("        GENERATE BILL                  \n");
    printf("========================================\n\n");

    if(bill_count >= 300) {
        printf("Bill database full!\n");
        return;
    }

    if(patient_count == 0) {
        printf("No patients available!\n");
        return;
    }

    Bill b;
    b.bill_no = getNewBillNo();

    printf("Available Patients:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewPatients();
    printf("\nEnter patient ID: ");
    scanf("%d", &b.patient_id);

    printf("\nEnter consultation fee: ");
    scanf("%f", &b.consultation_fee);

    printf("Enter medicine charges: ");
    scanf("%f", &b.medicine_charges);

    printf("Enter room charges: ");
    scanf("%f", &b.room_charges);

    printf("Enter lab charges: ");
    scanf("%f", &b.lab_charges);

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", b.date);

    b.total_amount = b.consultation_fee + b.medicine_charges +
                    b.room_charges + b.lab_charges;

    strcpy(b.status, "Generated");

    bills[bill_count++] = b;

    saveData();

    // Get patient name
    char patient_name[50] = "Unknown";
    for(int i = 0; i < patient_count; i++) {
        if(patients[i].id == b.patient_id) {
            strcpy(patient_name, patients[i].name);
            break;
        }
    }

    char filename[100];
    sprintf(filename, "Bill_%d.txt", b.bill_no);

    FILE *fp = fopen(filename, "w");
    if(fp != NULL) {
        // Header
        fprintf(fp, "===============================================\n");
        fprintf(fp, "          HOSPITAL MANAGEMENT SYSTEM          \n");
        fprintf(fp, "             PATIENT INVOICE/BILL             \n");
        fprintf(fp, "===============================================\n\n");

        // Bill details
        fprintf(fp, "Bill Number    : %d\n", b.bill_no);
        fprintf(fp, "Date           : %s\n", b.date);
        fprintf(fp, "Patient ID     : %d\n", b.patient_id);
        fprintf(fp, "Patient Name   : %s\n", patient_name);
        fprintf(fp, "Status         : %s\n\n", b.status);

        fprintf(fp, "-----------------------------------------------\n");
        fprintf(fp, "                CHARGES BREAKDOWN              \n");
        fprintf(fp, "-----------------------------------------------\n\n");

        // Charges breakdown
        fprintf(fp, "Consultation Fee      : $%.2f\n", b.consultation_fee);
        fprintf(fp, "Medicine Charges      : $%.2f\n", b.medicine_charges);
        fprintf(fp, "Room Charges          : $%.2f\n", b.room_charges);
        fprintf(fp, "Lab/Test Charges      : $%.2f\n", b.lab_charges);

        fprintf(fp, "\n-----------------------------------------------\n");
        fprintf(fp, "TOTAL AMOUNT          : $%.2f\n", b.total_amount);
        fprintf(fp, "-----------------------------------------------\n\n");

        // Footer
        fprintf(fp, "Payment Status: %s\n\n", b.status);
        fprintf(fp, "Thank you for choosing our hospital!\n");
        fprintf(fp, "For queries, contact: +123-456-7890\n");
        fprintf(fp, "===============================================\n");

        fclose(fp);
    }

    // Display on screen
    clearScreen();
    printf("\n===============================================\n");
    printf("          BILL GENERATED SUCCESSFULLY         \n");
    printf("===============================================\n\n");
    printf("Bill Number      : %d\n", b.bill_no);
    printf("Patient ID       : %d\n", b.patient_id);
    printf("Patient Name     : %s\n", patient_name);
    printf("Date             : %s\n\n", b.date);
    printf("-----------------------------------------------\n");
    printf("            CHARGES BREAKDOWN                  \n");
    printf("-----------------------------------------------\n");
    printf("Consultation Fee : $%.2f\n", b.consultation_fee);
    printf("Medicine Charges : $%.2f\n", b.medicine_charges);
    printf("Room Charges     : $%.2f\n", b.room_charges);
    printf("Lab Charges      : $%.2f\n", b.lab_charges);
    printf("-----------------------------------------------\n");
    printf("TOTAL AMOUNT     : $%.2f\n", b.total_amount);
    printf("-----------------------------------------------\n");
    printf("Status           : %s\n", b.status);
    printf("\nBill saved as    : %s\n", filename);
    printf("===============================================\n");
}

void viewBills() {
    printf("========================================\n");
    printf("        ALL BILLS                      \n");
    printf("========================================\n\n");

    if(bill_count == 0) {
        printf("No bills found!\n");
        return;
    }

    printf("Bill No\tPatient ID\tTotal Amount\tDate\t\tStatus\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < bill_count; i++) {
        printf("%d\t%d\t\t$%.2f\t\t%s\t%s\n",
               bills[i].bill_no, bills[i].patient_id,
               bills[i].total_amount, bills[i].date, bills[i].status);
    }
}

// Utility functions for generating IDs
int getNewPatientId() {
    int max_id = 1000;
    for(int i = 0; i < patient_count; i++) {
        if(patients[i].id > max_id) {
            max_id = patients[i].id;
        }
    }
    return max_id + 1;
}

int getNewDoctorId() {
    int max_id = 100;
    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id > max_id) {
            max_id = doctors[i].id;
        }
    }
    return max_id + 1;
}

int getNewAppointmentId() {
    int max_id = 5000;
    for(int i = 0; i < appointment_count; i++) {
        if(appointments[i].id > max_id) {
            max_id = appointments[i].id;
        }
    }
    return max_id + 1;
}

int getNewBillNo() {
    int max_bill = 10000;
    for(int i = 0; i < bill_count; i++) {
        if(bills[i].bill_no > max_bill) {
            max_bill = bills[i].bill_no;
        }
    }
    return max_bill + 1;
}
int getNewStaffId() {
    int max_id = 2000;
    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id > max_id) {
            max_id = staff[i].id;
        }
    }
    return max_id + 1;
}

// File handling functions

// Save staff data to file
void saveStaffData() {
    FILE *fp = fopen("staff.dat", "wb");
    if(fp != NULL) {
        fwrite(&staff_count, sizeof(int), 1, fp);
        fwrite(staff, sizeof(Staff), staff_count, fp);
        fclose(fp);
    }
}

// Load staff data from file
void loadStaffData() {
    FILE *fp = fopen("staff.dat", "rb");
    if(fp != NULL) {
        fread(&staff_count, sizeof(int), 1, fp);
        fread(staff, sizeof(Staff), staff_count, fp);
        fclose(fp);
    }
}

// Save all data to files

void saveData() {
    FILE *fp;

    // Save patients
    fp = fopen("patients.dat", "wb");
    if(fp != NULL) {
        fwrite(&patient_count, sizeof(int), 1, fp);
        fwrite(patients, sizeof(Patient), patient_count, fp);
        fclose(fp);
    }

    // Save doctors
    fp = fopen("doctors.dat", "wb");
    if(fp != NULL) {
        fwrite(&doctor_count, sizeof(int), 1, fp);
        fwrite(doctors, sizeof(Doctor), doctor_count, fp);
        fclose(fp);
    }

    // Save appointments
    fp = fopen("appointments.dat", "wb");
    if(fp != NULL) {
        fwrite(&appointment_count, sizeof(int), 1, fp);
        fwrite(appointments, sizeof(Appointment), appointment_count, fp);
        fclose(fp);
    }

    // Save bills
    fp = fopen("bills.dat", "wb");
    if(fp != NULL) {
        fwrite(&bill_count, sizeof(int), 1, fp);
        fwrite(bills, sizeof(Bill), bill_count, fp);
        fclose(fp);
    }
    // Save staff data
    saveStaffData();

}

void loadData() {
    FILE *fp;

    // Load patients
    fp = fopen("patients.dat", "rb");
    if(fp != NULL) {
        fread(&patient_count, sizeof(int), 1, fp);
        fread(patients, sizeof(Patient), patient_count, fp);
        fclose(fp);
    }

    // Load doctors
    fp = fopen("doctors.dat", "rb");
    if(fp != NULL) {
        fread(&doctor_count, sizeof(int), 1, fp);
        fread(doctors, sizeof(Doctor), doctor_count, fp);
        fclose(fp);
    }

    // Load appointments
    fp = fopen("appointments.dat", "rb");
    if(fp != NULL) {
        fread(&appointment_count, sizeof(int), 1, fp);
        fread(appointments, sizeof(Appointment), appointment_count, fp);
        fclose(fp);
    }

    // Load bills
    fp = fopen("bills.dat", "rb");
    if(fp != NULL) {
        fread(&bill_count, sizeof(int), 1, fp);
        fread(bills, sizeof(Bill), bill_count, fp);
        fclose(fp);
    }
    // Load staff data
     loadStaffData();
}


//  ADMIN PANEL FUNCTIONS

void getPasswordWithMask(char *password, int max_length) {
    int i = 0;
    char ch;

    printf("Password: ");

    while (1) {
        #ifdef _WIN32
            ch = _getch();  // Windows specific
        #else
            // Linux/Mac - disable echo
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            ch = getchar();

            // Restore terminal settings immediately
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        #endif

        // Check for Enter key (carriage return or newline)
        if (ch == '\r' || ch == '\n') {
            break;
        }
        // Check for Backspace
        else if (ch == 127 || ch == 8) { // 127=Linux/Mac, 8=Windows
            if (i > 0) {
                i--;
                printf("\b \b"); // Move back, space, move back again
            }
        }
        // Regular character input
        else if (i < max_length - 1) {
            password[i++] = ch;
            printf("*");
        }
    }

    password[i] = '\0'; // Null terminate the string
    printf("\n");
}
// Admin Login Function

int adminLogin() {
    char username[50];
    char password[50];
    int attempts = 0;

    printf("========================================\n");
    printf("          ADMIN LOGIN PANEL            \n");
    printf("========================================\n");

    while(attempts < 3) {
        printf("\nUsername: ");
        scanf("%s", username);

        // Use the password masking function
        getPasswordWithMask(password, 50);

        if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("\nLogin Successful! Welcome Admin!\n");
            return 1;
        } else {
            attempts++;
            printf("Invalid credentials! Attempts remaining: %d\n", 3 - attempts);
        }
    }

    printf("\nAccess Denied! Too many failed attempts.\n");
    return 0;
}

// Admin Menu
void adminMenu() {
    int choice;

    do {
        clearScreen();
        printf("========================================\n");
        printf("             ADMIN PANEL                \n");
        printf("========================================\n");
        printf("  1. Add New Doctor                    \n");
        printf("  2. Remove Doctor                     \n");
        printf("  3. View All Doctors                  \n");
        printf("  4. Search Doctor                     \n");
        printf("  5. Staff Management                  \n");
        printf("  6. Logout                            \n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1:
                addDoctor();
                pauseScreen();
                break;
            case 2:
                removeDoctor();
                pauseScreen();
                break;
            case 3:
                viewDoctors();
                pauseScreen();
                break;
            case 4:
                searchDoctor();
                pauseScreen();
                break;
            case 5:
                staffManagementMenu();
                pauseScreen();
                break;
            case 6:
                printf("========================================\n");
                printf("    Logged out successfully!           \n");
                printf("========================================\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                pauseScreen();
        }
    } while(choice != 6);
}

void staffManagementMenu() {
    int choice;
    do {
        clearScreen();
        printf("========================================\n");
        printf("           STAFF MANAGEMENT            \n");
        printf("========================================\n");
        printf("  1. Add New Staff                     \n");
        printf("  2. View All Staff                    \n");
        printf("  3. Edit Staff Information            \n");
        printf("  4. Delete Staff                      \n");
        printf("  5. Assign Duty Roster                \n");
        printf("  6. Search Staff                      \n");
        printf("  7. Back to Admin Menu                \n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1: addStaff();
            break;
            case 2: viewStaff();
            break;
            case 3: editStaff();
            break;
            case 4: deleteStaff();
            break;
            case 5: assignDutyRoster();
            break;
            case 6: searchStaff();
            break;
            case 7: printf("Returning to Admin Menu...\n"); break;
            default: printf("Invalid choice!\n");
        }
        if(choice != 7) pauseScreen();
    } while(choice != 7);
}

// Remove Doctor Function
void removeDoctor() {
    printf("========================================\n");
    printf("            REMOVE DOCTOR               \n");
    printf("========================================\n\n");

    if(doctor_count == 0) {
        printf("No doctors available to remove!\n");
        return;
    }

    int doctor_id;
    int found = 0;
    char confirm;

    // Show all doctors
    printf("Available Doctors:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewDoctors();

    printf("\nEnter Doctor ID to remove: ");
    scanf("%d", &doctor_id);

    // Search for the doctor
    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id == doctor_id) {
            found = 1;

            clearScreen();

            // Display doctor details
            printf("========================================\n");
            printf("           DOCTOR DETAILS               \n");
            printf("========================================\n");
            printf("ID             : %d\n", doctors[i].id);
            printf("Name           : %s\n", doctors[i].name);
            printf("Specialization : %s\n", doctors[i].specialization);
            printf("Contact        : %s\n", doctors[i].contact);
            printf("Availability   : %s\n", doctors[i].availability);
            printf("========================================\n");

            // Check if doctor has any appointments
            int appointment_exists = 0;
            for(int j = 0; j < appointment_count; j++) {
                if(appointments[j].doctor_id == doctor_id) {
                    appointment_exists = 1;
                    break;
                }
            }

            if(appointment_exists) {
                printf("\nWARNING: This doctor has existing appointments!\n");
            }

            // Confirmation
            printf("\n  Are you sure you want to remove this doctor? (y/n): ");
            scanf(" %c", &confirm);

            if(confirm == 'y' || confirm == 'Y') {
                // Shift all doctors after this position
                for(int j = i; j < doctor_count - 1; j++) {
                    doctors[j] = doctors[j + 1];
                }
                doctor_count--;

                saveData();  // Auto-save after deletion

                clearScreen();
                printf("========================================\n");
                printf("     DOCTOR REMOVED SUCCESSFULLY!     \n");
                printf("========================================\n");
                printf("Total doctors now: %d\n", doctor_count);
            } else {
                printf("\nOperation cancelled.\n");
            }

            return;
        }
    }

    if(!found) {
        printf("\nDoctor with ID %d not found!\n", doctor_id);
    }
}

// Modified addDoctor function (with better formatting)
void addDoctor() {
    printf("========================================\n");
    printf("           ADD NEW DOCTOR               \n");
    printf("========================================\n\n");

    if(doctor_count >= 100) {
        printf("Doctor database full! Cannot add more doctors.\n");
        return;
    }

    Doctor d;
    d.id = getNewDoctorId();

    printf("Enter doctor name: ");
    getchar();
    fgets(d.name, 50, stdin);
    d.name[strcspn(d.name, "\n")] = 0;

    printf("Enter specialization: ");
    fgets(d.specialization, 50, stdin);
    d.specialization[strcspn(d.specialization, "\n")] = 0;

    printf("Enter contact number: ");
    fgets(d.contact, 15, stdin);
    d.contact[strcspn(d.contact, "\n")] = 0;

    printf("Enter availability (e.g., Mon-Fri 9AM-5PM): ");
    fgets(d.availability, 50, stdin);
    d.availability[strcspn(d.availability, "\n")] = 0;

    doctors[doctor_count++] = d;

    saveData();  // Auto-save

    clearScreen();
    printf("========================================\n");
    printf("     DOCTOR ADDED SUCCESSFULLY!       \n");
    printf("========================================\n");
    printf("Doctor ID      : %d\n", d.id);
    printf("Name           : %s\n", d.name);
    printf("Specialization : %s\n", d.specialization);
    printf("Contact        : %s\n", d.contact);
    printf("Availability   : %s\n", d.availability);
    printf("========================================\n");
    printf("Total doctors: %d\n", doctor_count);

}

// Add new staff member
void addStaff() {
    printf("========================================\n");
    printf("           ADD NEW STAFF               \n");
    printf("========================================\n\n");

    if(staff_count >= 200) {
        printf("Staff database full! Cannot add more staff.\n");
        return;
    }

    Staff s;
    s.id = getNewStaffId();

    printf("Enter staff name: ");
    getchar();
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter role (Nurse/Receptionist/Technician/etc.): ");
    fgets(s.role, 30, stdin);
    s.role[strcspn(s.role, "\n")] = 0;

    printf("Enter department: ");
    fgets(s.department, 50, stdin);
    s.department[strcspn(s.department, "\n")] = 0;

    printf("Enter contact number: ");
    fgets(s.contact, 15, stdin);
    s.contact[strcspn(s.contact, "\n")] = 0;

    printf("Enter email: ");
    fgets(s.email, 50, stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    printf("Enter address: ");
    fgets(s.address, 100, stdin);
    s.address[strcspn(s.address, "\n")] = 0;

    printf("Enter qualification: ");
    fgets(s.qualification, 100, stdin);
    s.qualification[strcspn(s.qualification, "\n")] = 0;

    printf("Enter salary: ");
    scanf("%f", &s.salary);

    printf("Enter join date (DD/MM/YYYY): ");
    getchar();
    fgets(s.join_date, 20, stdin);
    s.join_date[strcspn(s.join_date, "\n")] = 0;

    printf("Enter default shift (Morning/Evening/Night): ");
    fgets(s.shift, 20, stdin);
    s.shift[strcspn(s.shift, "\n")] = 0;

    strcpy(s.status, "Active");

    staff[staff_count++] = s;
    saveStaffData();

    printf("\n========================================\n");
    printf("     STAFF ADDED SUCCESSFULLY!        \n");
    printf("========================================\n");
    printf("Staff ID     : %d\n", s.id);
    printf("Name         : %s\n", s.name);
    printf("Role         : %s\n", s.role);
    printf("Department   : %s\n", s.department);
    printf("Contact      : %s\n", s.contact);
    printf("========================================\n");
}

// View all staff members
void viewStaff() {
    printf("========================================\n");
    printf("            ALL STAFF MEMBERS          \n");
    printf("========================================\n\n");

    if(staff_count == 0) {
        printf("No staff members found!\n");
        return;
    }

    printf("ID\tName\t\t\tRole\t\tDepartment\t\tContact\n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < staff_count; i++) {
        printf("%d\t%-20s\t%-15s\t%-20s\t%s\n",
               staff[i].id, staff[i].name, staff[i].role,
               staff[i].department, staff[i].contact);
    }

    printf("\nTotal staff members: %d\n", staff_count);
}

// Edit staff information
void editStaff() {
    printf("========================================\n");
    printf("           EDIT STAFF INFORMATION      \n");
    printf("========================================\n\n");

    if(staff_count == 0) {
        printf("No staff members available!\n");
        return;
    }

    int staff_id;
    int found = 0;

    printf("Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewStaff();

    printf("\nEnter Staff ID to edit: ");
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf("\n========================================\n");
            printf("     EDITING STAFF ID: %d            \n", staff_id);
            printf("========================================\n");

            printf("Current Name (%s): ", staff[i].name);
            getchar();
            char temp[50];
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].name, temp);
            }

            printf("Current Role (%s): ", staff[i].role);
            fgets(temp, 30, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].role, temp);
            }

            printf("Current Department (%s): ", staff[i].department);
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].department, temp);
            }

            printf("Current Contact (%s): ", staff[i].contact);
            fgets(temp, 15, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].contact, temp);
            }

            printf("Current Email (%s): ", staff[i].email);
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].email, temp);
            }

            printf("Current Salary (%.2f): ", staff[i].salary);
            char salary_input[20];
            fgets(salary_input, 20, stdin);
            if(strlen(salary_input) > 1) {
                staff[i].salary = atof(salary_input);
            }

            printf("Current Shift (%s): ", staff[i].shift);
            fgets(temp, 20, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].shift, temp);
            }

            saveStaffData();

            printf("\n========================================\n");
            printf("   STAFF INFORMATION UPDATED!         \n");
            printf("========================================\n");
            break;
        }
    }

    if(!found) {
        printf("\nStaff with ID %d not found!\n", staff_id);
    }
}

// Delete staff member
void deleteStaff() {
    printf("========================================\n");
    printf("            DELETE STAFF               \n");
    printf("========================================\n\n");

    if(staff_count == 0) {
        printf("No staff members available to delete!\n");
        return;
    }

    int staff_id;
    int found = 0;
    char confirm;

    printf("Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewStaff();

    printf("\nEnter Staff ID to delete: ");
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf("\n========================================\n");
            printf("           STAFF DETAILS               \n");
            printf("========================================\n");
            printf("ID           : %d\n", staff[i].id);
            printf("Name         : %s\n", staff[i].name);
            printf("Role         : %s\n", staff[i].role);
            printf("Department   : %s\n", staff[i].department);
            printf("Contact      : %s\n", staff[i].contact);
            printf("========================================\n");

            printf("\nAre you sure you want to delete this staff member? (y/n): ");
            scanf(" %c", &confirm);

            if(confirm == 'y' || confirm == 'Y') {
                // Shift all staff after this position
                for(int j = i; j < staff_count - 1; j++) {
                    staff[j] = staff[j + 1];
                }
                staff_count--;

                saveStaffData();

                printf("\n========================================\n");
                printf("     STAFF DELETED SUCCESSFULLY!       \n");
                printf("========================================\n");
                printf("Total staff members now: %d\n", staff_count);
            } else {
                printf("\nOperation cancelled.\n");
            }
            break;
        }
    }

    if(!found) {
        printf("\nStaff with ID %d not found!\n", staff_id);
    }
}

// Assign duty roster
void assignDutyRoster() {
    printf("========================================\n");
    printf("           ASSIGN DUTY ROSTER          \n");
    printf("========================================\n\n");

    if(staff_count == 0) {
        printf("No staff members available!\n");
        return;
    }

    int staff_id;
    int found = 0;

    printf("Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n");
    viewStaff();

    printf("\nEnter Staff ID to assign duty: ");
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf("\n========================================\n");
            printf("   ASSIGNING DUTY FOR: %s            \n", staff[i].name);
            printf("========================================\n");
            printf("Current Shift: %s\n", staff[i].shift);

            printf("\nAvailable Shifts:\n");
            printf("1. Morning (7:00 AM - 3:00 PM)\n");
            printf("2. Evening (3:00 PM - 11:00 PM)\n");
            printf("3. Night (11:00 PM - 7:00 AM)\n");
            printf("4. Custom Shift\n");

            int choice;
            printf("\nEnter shift choice (1-4): ");
            scanf("%d", &choice);

            getchar(); // Clear buffer

            switch(choice) {
                case 1:
                    strcpy(staff[i].shift, "Morning (7AM-3PM)");
                    break;
                case 2:
                    strcpy(staff[i].shift, "Evening (3PM-11PM)");
                    break;
                case 3:
                    strcpy(staff[i].shift, "Night (11PM-7AM)");
                    break;
                case 4:
                    printf("Enter custom shift details: ");
                    fgets(staff[i].shift, 20, stdin);
                    staff[i].shift[strcspn(staff[i].shift, "\n")] = 0;
                    break;
                default:
                    printf("Invalid choice! Keeping current shift.\n");
            }

            saveStaffData();

            printf("\n========================================\n");
            printf("     DUTY ROSTER UPDATED!             \n");
            printf("========================================\n");
            printf("Staff Name: %s\n", staff[i].name);
            printf("New Shift : %s\n", staff[i].shift);
            break;
        }
    }

    if(!found) {
        printf("\nStaff with ID %d not found!\n", staff_id);
    }
}

// Search staff
void searchStaff() {
    printf("========================================\n");
    printf("            SEARCH STAFF               \n");
    printf("========================================\n\n");

    if(staff_count == 0) {
        printf("No staff members found!\n");
        return;
    }

    int choice;
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Role\n");
    printf("4. Search by Department\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    getchar(); // Clear buffer

    if(choice == 1) {
        int id;
        printf("Enter staff ID: ");
        scanf("%d", &id);

        for(int i = 0; i < staff_count; i++) {
            if(staff[i].id == id) {
                printf("\n========================================\n");
                printf("           STAFF FOUND                 \n");
                printf("========================================\n");
                printf("ID           : %d\n", staff[i].id);
                printf("Name         : %s\n", staff[i].name);
                printf("Role         : %s\n", staff[i].role);
                printf("Department   : %s\n", staff[i].department);
                printf("Contact      : %s\n", staff[i].contact);
                printf("Email        : %s\n", staff[i].email);
                printf("Address      : %s\n", staff[i].address);
                printf("Qualification: %s\n", staff[i].qualification);
                printf("Salary       : $%.2f\n", staff[i].salary);
                printf("Join Date    : %s\n", staff[i].join_date);
                printf("Shift        : %s\n", staff[i].shift);
                printf("Status       : %s\n", staff[i].status);
                printf("========================================\n");
                return;
            }
        }
        printf("\nStaff not found!\n");
    }
    else if(choice == 2 || choice == 3 || choice == 4) {
        char search_term[50];

        if(choice == 2) {
            printf("Enter staff name: ");
            fgets(search_term, 50, stdin);
        }
        else if(choice == 3) {
            printf("Enter role: ");
            fgets(search_term, 50, stdin);
        }
        else {
            printf("Enter department: ");
            fgets(search_term, 50, stdin);
        }

        search_term[strcspn(search_term, "\n")] = 0;

        int found = 0;
        printf("\nSearch Results:\n");
        printf("ID\tName\t\t\tRole\t\tDepartment\t\tContact\n");
        printf("--------------------------------------------------------------------------------\n");

        for(int i = 0; i < staff_count; i++) {
            if((choice == 2 && strstr(staff[i].name, search_term)) ||
               (choice == 3 && strstr(staff[i].role, search_term)) ||
               (choice == 4 && strstr(staff[i].department, search_term))) {
                printf("%d\t%-20s\t%-15s\t%-20s\t%s\n",
                       staff[i].id, staff[i].name, staff[i].role,
                       staff[i].department, staff[i].contact);
                found = 1;
            }
        }

        if(!found) {
            printf("No staff members found!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}
