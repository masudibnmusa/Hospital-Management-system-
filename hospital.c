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

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

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
void doctorManagementMenu();
void editDoctor();
void viewDoctorStatistics();
void viewDoctorDetails(int doctor_id);
void reportsAndAnalyticsMenu();
void dailyRevenueReport();
void monthlyRevenueReport();
void yearlyRevenueReport();
void unpaidBillsReport();
void departmentRevenue();

// Utility function to safely clear input buffer
void clearInputBuffer() {
    int c;
    // Read and discard characters until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        // Continue clearing
    }
    // If we hit EOF, clear the error state
    if (c == EOF) {
        clearerr(stdin);
    }
}

// Utility function to clear screen
void clearScreen() {
    system(CLEAR_SCREEN);
}

// Utility function to pause screen
void pauseScreen() {
    printf("\nPress Enter to continue...");

    // Clear any pending input first
    clearInputBuffer();

    // Wait for Enter key
    int c = getchar();

    // Handle EOF or error conditions
    if (c == EOF) {
        clearerr(stdin);
    }
}

int main() {
    loadData();
    int choice;

    clearScreen();
    printf(CYAN "========================================\n");
    printf(BOLD "   HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("========================================\n" RESET);
    printf(GREEN "\nPress Enter to continue..." RESET);
    getchar();

    do {
        clearScreen();
        displayMenu();
        printf(BLUE "Enter your choice: " RESET);
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
                printf(CYAN "========================================\n");
                printf(GREEN "   Thank you for using Hospital        \n");
                printf("      Management System!               \n");
                printf("========================================\n" RESET);
                break;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                pauseScreen();
        }
    } while(choice != 11);

    return 0;
}

void displayMenu() {
    printf(CYAN "========================================\n");
    printf(BOLD "   HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("========================================\n" RESET);
    printf(YELLOW "\n=== MAIN MENU ===\n" RESET);
    printf(GREEN "1. Add New Patient\n");
    printf("2. View All Patients\n");
    printf("3. Search Patient\n");
    printf("4. View All Doctors\n");
    printf("5. Search Doctor\n");
    printf("6. Schedule Appointment\n");
    printf("7. View Appointments\n");
    printf("8. Generate Bill\n");
    printf("9. View Bills\n");
    printf(YELLOW "10. Admin panel\n" RESET);
    printf(RED "11. Exit\n" RESET);
    printf(CYAN "========================================\n" RESET);
}

// Admin Menu
void adminMenu() {
    int choice;

    do {
        clearScreen();
        printf(CYAN "========================================\n");
        printf(BOLD "             ADMIN PANEL                \n");
        printf("========================================\n" RESET);
        printf(GREEN "  1. Doctor Management                 \n" RESET);
        printf(YELLOW "  2. Staff Management                  \n" RESET);
        printf(MAGENTA "  3. Reports & Analytics               \n" RESET);
        printf(RED "  4. Logout                            \n" RESET);
        printf(CYAN "========================================\n" RESET);
        printf(BLUE "Enter your choice: " RESET);
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1:
                doctorManagementMenu();
                break;
            case 2:
                staffManagementMenu();
                break;
            case 3:
                reportsAndAnalyticsMenu();
                break;
            case 4:
                printf(GREEN "========================================\n");
                printf("    Logged out successfully!           \n");
                printf("========================================\n" RESET);
                break;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                pauseScreen();
        }
    } while(choice != 4);
}

// Doctor Management Menu
void doctorManagementMenu() {
    int choice;

    do {
        clearScreen();
        printf(CYAN "========================================\n");
        printf(BOLD "         DOCTOR MANAGEMENT             \n");
        printf("========================================\n" RESET);
        printf(GREEN "  1. Add New Doctor                    \n");
        printf("  2. Remove Doctor                     \n");
        printf("  3. View All Doctors                  \n");
        printf("  4. Search Doctor                     \n");
        printf(YELLOW "  5. Edit Doctor Information           \n");
        printf("  6. View Doctor Statistics            \n" RESET);
        printf("  7. View Doctor Details               \n" RESET);
        printf(RED "  8. Back to Admin Menu                \n" RESET);
        printf(CYAN "========================================\n" RESET);
        printf(BLUE "Enter your choice: " RESET);
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
                editDoctor();
                pauseScreen();
                break;
            case 6:
                viewDoctorStatistics();
                pauseScreen();
                break;
            case 7:
                {
                    int doctor_id;
                    printf("Enter Doctor ID: ");
                    scanf("%d", &doctor_id);
                    viewDoctorDetails(doctor_id);
                    pauseScreen();
                }
                break;
            case 8:
                printf(GREEN "Returning to Admin Menu...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                pauseScreen();
        }
    } while(choice != 8);
}

// Staff Management Menu]
void staffManagementMenu() {
    int choice;
    do {
        clearScreen();
        printf(CYAN "========================================\n");
        printf(BOLD "           STAFF MANAGEMENT            \n");
        printf("========================================\n" RESET);
        printf(GREEN "  1. Add New Staff                     \n");
        printf("  2. View All Staff                    \n");
        printf("  3. Edit Staff Information            \n");
        printf("  4. Delete Staff                      \n");
        printf(YELLOW "  5. Assign Duty Roster                \n");
        printf("  6. Search Staff                      \n" RESET);
        printf(RED "  7. Back to Admin Menu                \n" RESET);
        printf(CYAN "========================================\n" RESET);
        printf(BLUE "Enter your choice: " RESET);
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1:
                addStaff();
                break;
            case 2:
                viewStaff();
                break;
            case 3:
                editStaff();
                break;
            case 4:
                deleteStaff();
                break;
            case 5:
                assignDutyRoster();
                break;
            case 6:
                searchStaff();
                break;
            case 7:
                printf(GREEN "Returning to Admin Menu...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice!\n" RESET);
        }
        if(choice != 7) pauseScreen();
    } while(choice != 7);
}

// Reports & Analytics Menu
void reportsAndAnalyticsMenu() {
    int choice;

    do {
        clearScreen();
        printf(CYAN "========================================\n");
        printf(BOLD "         REPORTS & ANALYTICS           \n");
        printf("========================================\n" RESET);
        printf(GREEN "  1. Daily Revenue Report              \n");
        printf("  2. Monthly Revenue Report            \n");
        printf("  3. Yearly Revenue Report             \n");
        printf(YELLOW "  4. Unpaid Bills Report               \n");
        printf("  5. Department Revenue Report         \n" RESET);
        printf(RED "  6. Back to Admin Menu                \n" RESET);
        printf(CYAN "========================================\n" RESET);
        printf(BLUE "Enter your choice: " RESET);
        scanf("%d", &choice);

        clearScreen();

        switch(choice) {
            case 1:
                dailyRevenueReport();
                pauseScreen();
                break;
                break;
            case 2:
                monthlyRevenueReport();
                pauseScreen();
                break;
            case 3:
                printf(GREEN "Returning to Admin Menu...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                pauseScreen();
        }
    } while(choice != 3);
}

// Patient Management Functions
void addPatient() {
    if(patient_count >= 1000) {
        printf(RED "Patient database full!\n" RESET);
        return;
    }

    Patient p;
    p.id = getNewPatientId();

    printf(CYAN "========================================\n");
    printf(BOLD "        ADD NEW PATIENT                \n");
    printf("========================================\n\n" RESET);

    printf(BLUE "Enter patient name: " RESET);
    getchar();
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf(BLUE "Enter age: " RESET);
    scanf("%d", &p.age);

    printf(BLUE "Enter gender: " RESET);
    scanf("%s", p.gender);

    printf(BLUE "Enter contact number: " RESET);
    scanf("%s", p.contact);

    printf(BLUE "Enter address: " RESET);
    getchar();
    fgets(p.address, 100, stdin);
    p.address[strcspn(p.address, "\n")] = 0;

    printf(BLUE "Enter medical history: " RESET);
    fgets(p.medical_history, 200, stdin);
    p.medical_history[strcspn(p.medical_history, "\n")] = 0;

    patients[patient_count++] = p;

    saveData();

    printf(GREEN "\n========================================\n");
    printf("   PATIENT ADDED SUCCESSFULLY!         \n");
    printf("========================================\n" RESET);
    printf("Patient ID: " YELLOW "%d\n" RESET, p.id);
    printf("Name: " YELLOW "%s\n" RESET, p.name);
    printf(CYAN "========================================\n" RESET);
}

void viewPatients() {
    printf(CYAN "========================================\n");
    printf(BOLD "        ALL PATIENTS                   \n");
    printf("========================================\n\n" RESET);

    if(patient_count == 0) {
        printf(RED "No patients found!\n" RESET);
        return;
    }

    printf(YELLOW "ID\tName\t\t\tAge\tGender\tContact\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < patient_count; i++) {
        printf(GREEN "%d\t" RESET, patients[i].id);
        printf(CYAN "%-20s\t" RESET, patients[i].name);
        printf("%d\t" RESET, patients[i].age);
        printf(MAGENTA "%s\t" RESET, patients[i].gender);
        printf(BLUE "%s\n" RESET, patients[i].contact);
    }
}

void searchPatient() {
    printf(CYAN "========================================\n");
    printf(BOLD "        SEARCH PATIENT                 \n");
    printf("========================================\n\n" RESET);

    if(patient_count == 0) {
        printf(RED "No patients found!\n" RESET);
        return;
    }

    int choice;
    printf(YELLOW "1. Search by ID\n");
    printf("2. Search by Name\n");
    printf(BLUE "Enter choice: " RESET);
    scanf("%d", &choice);

    clearScreen();

    if(choice == 1) {
        int id;
        printf(CYAN "========================================\n");
        printf(BOLD "      SEARCH PATIENT BY ID             \n");
        printf("========================================\n\n" RESET);
        printf(BLUE "Enter patient ID: " RESET);
        scanf("%d", &id);

        for(int i = 0; i < patient_count; i++) {
            if(patients[i].id == id) {
                printf(GREEN "\n========================================\n");
                printf("        PATIENT FOUND                  \n");
                printf("========================================\n" RESET);
                printf("ID: " YELLOW "%d\n" RESET, patients[i].id);
                printf("Name: " YELLOW "%s\n" RESET, patients[i].name);
                printf("Age: " YELLOW "%d\n" RESET, patients[i].age);
                printf("Gender: " YELLOW "%s\n" RESET, patients[i].gender);
                printf("Contact: " YELLOW "%s\n" RESET, patients[i].contact);
                printf("Address: " YELLOW "%s\n" RESET, patients[i].address);
                printf("Medical History: " YELLOW "%s\n" RESET, patients[i].medical_history);
                printf(CYAN "========================================\n" RESET);
                return;
            }
        }
        printf(RED "\nPatient not found!\n" RESET);
    }
    else if(choice == 2) {
        char name[50];
        printf(CYAN "========================================\n");
        printf(BOLD "      SEARCH PATIENT BY NAME           \n");
        printf("========================================\n\n" RESET);
        printf(BLUE "Enter patient name: " RESET);
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < patient_count; i++) {
            if(strstr(patients[i].name, name) != NULL) {
                if(!found) {
                    printf(YELLOW "\nSearch Results:\n");
                    printf("ID\tName\t\t\tAge\tGender\tContact\n");
                    printf("------------------------------------------------------------------------\n" RESET);
                    found = 1;
                }
                printf(GREEN "%d\t" RESET, patients[i].id);
                printf(CYAN "%-20s\t" RESET, patients[i].name);
                printf("%d\t" RESET, patients[i].age);
                printf(MAGENTA "%s\t" RESET, patients[i].gender);
                printf(BLUE "%s\n" RESET, patients[i].contact);
            }
        }
        if(!found) {
            printf(RED "\nPatient not found!\n" RESET);
        }
    }
    else {
        printf(RED "Invalid choice!\n" RESET);
    }
}

void viewDoctors() {
    printf(CYAN "========================================\n");
    printf(BOLD "        ALL DOCTORS                    \n");
    printf("========================================\n\n" RESET);

    if(doctor_count == 0) {
        printf(RED "No doctors found!\n" RESET);
        return;
    }

    printf(YELLOW "ID\tName\t\t\tSpecialization\t\tContact\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < doctor_count; i++) {
        printf(GREEN "%d\t" RESET, doctors[i].id);
        printf(CYAN "%-20s\t" RESET, doctors[i].name);
        printf(MAGENTA "%-20s\t" RESET, doctors[i].specialization);
        printf(BLUE "%s\n" RESET, doctors[i].contact);
    }
}

void searchDoctor() {
    printf(CYAN "========================================\n");
    printf(BOLD "        SEARCH DOCTOR                  \n");
    printf("========================================\n\n" RESET);

    if(doctor_count == 0) {
        printf(RED "No doctors found!\n" RESET);
        return;
    }

    int choice;
    printf(YELLOW "1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Specialization\n");
    printf(BLUE "Enter choice: " RESET);
    scanf("%d", &choice);

    clearScreen();

    if(choice == 1) {
        int id;
        printf(CYAN "========================================\n");
        printf(BOLD "      SEARCH DOCTOR BY ID              \n");
        printf("========================================\n\n" RESET);
        printf(BLUE "Enter doctor ID: " RESET);
        scanf("%d", &id);

        for(int i = 0; i < doctor_count; i++) {
            if(doctors[i].id == id) {
                printf(GREEN "\n========================================\n");
                printf("        DOCTOR FOUND                   \n");
                printf("========================================\n" RESET);
                printf("ID: " YELLOW "%d\n" RESET, doctors[i].id);
                printf("Name: " YELLOW "%s\n" RESET, doctors[i].name);
                printf("Specialization: " YELLOW "%s\n" RESET, doctors[i].specialization);
                printf("Contact: " YELLOW "%s\n" RESET, doctors[i].contact);
                printf("Availability: " YELLOW "%s\n" RESET, doctors[i].availability);
                printf(CYAN "========================================\n" RESET);
                return;
            }
        }
        printf(RED "\nDoctor not found!\n" RESET);
    }
    else if(choice == 2) {
        char name[50];
        printf(CYAN "========================================\n");
        printf(BOLD "      SEARCH DOCTOR BY NAME            \n");
        printf("========================================\n\n" RESET);
        printf(BLUE "Enter doctor name: " RESET);
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].name, name) != NULL) {
                if(!found) {
                    printf(YELLOW "\nSearch Results:\n");
                    printf("ID\tName\t\t\tSpecialization\t\tContact\n");
                    printf("------------------------------------------------------------------------\n" RESET);
                    found = 1;
                }
                printf(GREEN "%d\t" RESET, doctors[i].id);
                printf(CYAN "%-20s\t" RESET, doctors[i].name);
                printf(MAGENTA "%-20s\t" RESET, doctors[i].specialization);
                printf(BLUE "%s\n" RESET, doctors[i].contact);
            }
        }
        if(!found) {
            printf(RED "\nDoctor not found!\n" RESET);
        }
    }
    else if(choice == 3) {
        char specialization[50];
        printf(CYAN "========================================\n");
        printf(BOLD "   SEARCH DOCTOR BY SPECIALIZATION     \n");
        printf("========================================\n\n" RESET);
        printf(BLUE "Enter specialization: " RESET);
        getchar();
        fgets(specialization, 50, stdin);
        specialization[strcspn(specialization, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].specialization, specialization) != NULL) {
                if(!found) {
                    printf(YELLOW "\nSearch Results:\n");
                    printf("ID\tName\t\t\tSpecialization\t\tContact\n");
                    printf("------------------------------------------------------------------------\n" RESET);
                    found = 1;
                }
                printf(GREEN "%d\t" RESET, doctors[i].id);
                printf(CYAN "%-20s\t" RESET, doctors[i].name);
                printf(MAGENTA "%-20s\t" RESET, doctors[i].specialization);
                printf(BLUE "%s\n" RESET, doctors[i].contact);
            }
        }
        if(!found) {
            printf(RED "\nNo doctors found with this specialization!\n" RESET);
        }
    }
    else {
        printf(RED "Invalid choice!\n" RESET);
    }
}

void scheduleAppointment() {
    printf(CYAN "========================================\n");
    printf(BOLD "      SCHEDULE APPOINTMENT             \n");
    printf("========================================\n\n" RESET);

    if(appointment_count >= 500) {
        printf(RED "Appointment database full!\n" RESET);
        return;
    }

    if(patient_count == 0 || doctor_count == 0) {
        printf(RED "No patients or doctors available!\n" RESET);
        return;
    }

    Appointment a;
    a.id = getNewAppointmentId();

    printf(YELLOW "Available Patients:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewPatients();
    printf(BLUE "\nEnter patient ID: " RESET);
    scanf("%d", &a.patient_id);

    printf(YELLOW "\nAvailable Doctors:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewDoctors();
    printf(BLUE "\nEnter doctor ID: " RESET);
    scanf("%d", &a.doctor_id);

    printf(BLUE "\nEnter date (DD/MM/YYYY): " RESET);
    scanf("%s", a.date);

    printf(BLUE "Enter time (HH:MM): " RESET);
    scanf("%s", a.time);

    printf(BLUE "Enter purpose: " RESET);
    getchar();
    fgets(a.purpose, 100, stdin);
    a.purpose[strcspn(a.purpose, "\n")] = 0;

    strcpy(a.status, "Scheduled");

    appointments[appointment_count++] = a;

    saveData();

    printf(GREEN "\n========================================\n");
    printf("  APPOINTMENT SCHEDULED SUCCESSFULLY!  \n");
    printf("========================================\n" RESET);
    printf("Appointment ID: " YELLOW "%d\n" RESET, a.id);
    printf("Date: " YELLOW "%s\n" RESET, a.date);
    printf("Time: " YELLOW "%s\n" RESET, a.time);
    printf(CYAN "========================================\n" RESET);
}

void viewAppointments() {
    printf(CYAN "========================================\n");
    printf(BOLD "        ALL APPOINTMENTS               \n");
    printf("========================================\n\n" RESET);

    if(appointment_count == 0) {
        printf(RED "No appointments found!\n" RESET);
        return;
    }

    printf(YELLOW "ID\tPatient ID\tDoctor ID\tDate\t\tTime\tStatus\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < appointment_count; i++) {
        printf(GREEN "%d\t" RESET, appointments[i].id);
        printf("%d\t\t" RESET, appointments[i].patient_id);
        printf("%d\t\t" RESET, appointments[i].doctor_id);
        printf(CYAN "%s\t" RESET, appointments[i].date);
        printf(MAGENTA "%s\t" RESET, appointments[i].time);
        printf(BLUE "%s\n" RESET, appointments[i].status);
    }
}

void generateBill() {
    printf(CYAN "========================================\n");
    printf(BOLD "        GENERATE BILL                  \n");
    printf("========================================\n\n" RESET);

    if(bill_count >= 300) {
        printf(RED "Bill database full!\n" RESET);
        return;
    }

    if(patient_count == 0) {
        printf(RED "No patients available!\n" RESET);
        return;
    }

    Bill b;
    b.bill_no = getNewBillNo();

    printf(YELLOW "Available Patients:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewPatients();
    printf(BLUE "\nEnter patient ID: " RESET);
    scanf("%d", &b.patient_id);

    printf(BLUE "\nEnter consultation fee: " RESET);
    scanf("%f", &b.consultation_fee);

    printf(BLUE "Enter medicine charges: " RESET);
    scanf("%f", &b.medicine_charges);

    printf(BLUE "Enter room charges: " RESET);
    scanf("%f", &b.room_charges);

    printf(BLUE "Enter lab charges: " RESET);
    scanf("%f", &b.lab_charges);

    printf(BLUE "Enter date (DD/MM/YYYY): " RESET);
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
    printf(GREEN "\n===============================================\n");
    printf("          BILL GENERATED SUCCESSFULLY         \n");
    printf("===============================================\n\n" RESET);
    printf("Bill Number      : " YELLOW "%d\n" RESET, b.bill_no);
    printf("Patient ID       : " YELLOW "%d\n" RESET, b.patient_id);
    printf("Patient Name     : " YELLOW "%s\n" RESET, patient_name);
    printf("Date             : " YELLOW "%s\n\n" RESET, b.date);
    printf(CYAN "-----------------------------------------------\n");
    printf("            CHARGES BREAKDOWN                  \n");
    printf("-----------------------------------------------\n" RESET);
    printf("Consultation Fee : " GREEN "$%.2f\n" RESET, b.consultation_fee);
    printf("Medicine Charges : " GREEN "$%.2f\n" RESET, b.medicine_charges);
    printf("Room Charges     : " GREEN "$%.2f\n" RESET, b.room_charges);
    printf("Lab Charges      : " GREEN "$%.2f\n" RESET, b.lab_charges);
    printf(YELLOW "-----------------------------------------------\n");
    printf("TOTAL AMOUNT     : $%.2f\n", b.total_amount);
    printf("-----------------------------------------------\n" RESET);
    printf("Status           : " BLUE "%s\n" RESET, b.status);
    printf("\nBill saved as    : " CYAN "%s\n" RESET, filename);
    printf(CYAN "===============================================\n" RESET);
}

void viewBills() {
    printf(CYAN "========================================\n");
    printf(BOLD "        ALL BILLS                      \n");
    printf("========================================\n\n" RESET);

    if(bill_count == 0) {
        printf(RED "No bills found!\n" RESET);
        return;
    }

    printf(YELLOW "Bill No\tPatient ID\tTotal Amount\tDate\t\tStatus\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < bill_count; i++) {
        printf(GREEN "%d\t" RESET, bills[i].bill_no);
        printf("%d\t\t" RESET, bills[i].patient_id);
        printf(YELLOW "$%.2f\t\t" RESET, bills[i].total_amount);
        printf(CYAN "%s\t" RESET, bills[i].date);
        printf(BLUE "%s\n" RESET, bills[i].status);
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

    printf(BLUE "Password: " RESET);

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
            printf(YELLOW "*" RESET);
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

    printf(CYAN "========================================\n");
    printf(BOLD "          ADMIN LOGIN PANEL            \n");
    printf("========================================\n" RESET);

    while(attempts < 3) {
        printf(BLUE "\nUsername: " RESET);
        scanf("%s", username);

        // Use the password masking function
        getPasswordWithMask(password, 50);

        if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf(GREEN "\nLogin Successful! Welcome Admin!\n" RESET);
            return 1;
        } else {
            attempts++;
            printf(RED "Invalid credentials! Attempts remaining: %d\n" RESET, 3 - attempts);
        }
    }

    printf(RED "\nAccess Denied! Too many failed attempts.\n" RESET);
    return 0;
}

// Remove Doctor Function
void removeDoctor() {
    printf(CYAN "========================================\n");
    printf(BOLD "            REMOVE DOCTOR               \n");
    printf("========================================\n\n" RESET);

    if(doctor_count == 0) {
        printf(RED "No doctors available to remove!\n" RESET);
        return;
    }

    int doctor_id;
    int found = 0;
    char confirm;

    // Show all doctors
    printf(YELLOW "Available Doctors:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewDoctors();

    printf(BLUE "\nEnter Doctor ID to remove: " RESET);
    scanf("%d", &doctor_id);

    // Search for the doctor
    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id == doctor_id) {
            found = 1;

            clearScreen();

            // Display doctor details
            printf(CYAN "========================================\n");
            printf(BOLD "           DOCTOR DETAILS               \n");
            printf("========================================\n" RESET);
            printf("ID             : " YELLOW "%d\n" RESET, doctors[i].id);
            printf("Name           : " YELLOW "%s\n" RESET, doctors[i].name);
            printf("Specialization : " YELLOW "%s\n" RESET, doctors[i].specialization);
            printf("Contact        : " YELLOW "%s\n" RESET, doctors[i].contact);
            printf("Availability   : " YELLOW "%s\n" RESET, doctors[i].availability);
            printf(CYAN "========================================\n" RESET);

            // Check if doctor has any appointments
            int appointment_exists = 0;
            for(int j = 0; j < appointment_count; j++) {
                if(appointments[j].doctor_id == doctor_id) {
                    appointment_exists = 1;
                    break;
                }
            }

            if(appointment_exists) {
                printf(RED "\nWARNING: This doctor has existing appointments!\n" RESET);
            }

            // Confirmation
            printf(YELLOW "\n  Are you sure you want to remove this doctor? (y/n): " RESET);
            scanf(" %c", &confirm);

            if(confirm == 'y' || confirm == 'Y') {
                // Shift all doctors after this position
                for(int j = i; j < doctor_count - 1; j++) {
                    doctors[j] = doctors[j + 1];
                }
                doctor_count--;

                saveData();  // Auto-save after deletion

                clearScreen();
                printf(GREEN "========================================\n");
                printf("     DOCTOR REMOVED SUCCESSFULLY!     \n");
                printf("========================================\n" RESET);
                printf("Total doctors now: " YELLOW "%d\n" RESET, doctor_count);
            } else {
                printf(YELLOW "\nOperation cancelled.\n" RESET);
            }

            return;
        }
    }

    if(!found) {
        printf(RED "\nDoctor with ID %d not found!\n" RESET, doctor_id);
    }
}

// Add new doctor
void addDoctor() {
    printf(CYAN "========================================\n");
    printf(BOLD "           ADD NEW DOCTOR               \n");
    printf("========================================\n\n" RESET);

    if(doctor_count >= 100) {
        printf(RED "Doctor database full! Cannot add more doctors.\n" RESET);
        return;
    }

    Doctor d;
    d.id = getNewDoctorId();

    printf(BLUE "Enter doctor name: " RESET);
    getchar();
    fgets(d.name, 50, stdin);
    d.name[strcspn(d.name, "\n")] = 0;

    printf(BLUE "Enter specialization: " RESET);
    fgets(d.specialization, 50, stdin);
    d.specialization[strcspn(d.specialization, "\n")] = 0;

    printf(BLUE "Enter contact number: " RESET);
    fgets(d.contact, 15, stdin);
    d.contact[strcspn(d.contact, "\n")] = 0;

    printf(BLUE "Enter availability (e.g., Mon-Fri 9AM-5PM): " RESET);
    fgets(d.availability, 50, stdin);
    d.availability[strcspn(d.availability, "\n")] = 0;

    doctors[doctor_count++] = d;

    saveData();  // Auto-save

    clearScreen();
    printf(GREEN "========================================\n");
    printf("     DOCTOR ADDED SUCCESSFULLY!       \n");
    printf("========================================\n" RESET);
    printf("Doctor ID      : " YELLOW "%d\n" RESET, d.id);
    printf("Name           : " YELLOW "%s\n" RESET, d.name);
    printf("Specialization : " YELLOW "%s\n" RESET, d.specialization);
    printf("Contact        : " YELLOW "%s\n" RESET, d.contact);
    printf("Availability   : " YELLOW "%s\n" RESET, d.availability);
    printf(CYAN "========================================\n" RESET);
    printf("Total doctors: " YELLOW "%d\n" RESET, doctor_count);

}

// Add new staff member
void addStaff() {
    printf(CYAN "========================================\n");
    printf(BOLD "           ADD NEW STAFF               \n");
    printf("========================================\n\n" RESET);

    if(staff_count >= 200) {
        printf(RED "Staff database full! Cannot add more staff.\n" RESET);
        return;
    }

    Staff s;
    s.id = getNewStaffId();

    printf(BLUE "Enter staff name: " RESET);
    getchar();
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf(BLUE "Enter role (Nurse/Receptionist/Technician/etc.): " RESET);
    fgets(s.role, 30, stdin);
    s.role[strcspn(s.role, "\n")] = 0;

    printf(BLUE "Enter department: " RESET);
    fgets(s.department, 50, stdin);
    s.department[strcspn(s.department, "\n")] = 0;

    printf(BLUE "Enter contact number: " RESET);
    fgets(s.contact, 15, stdin);
    s.contact[strcspn(s.contact, "\n")] = 0;

    printf(BLUE "Enter email: " RESET);
    fgets(s.email, 50, stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    printf(BLUE "Enter address: " RESET);
    fgets(s.address, 100, stdin);
    s.address[strcspn(s.address, "\n")] = 0;

    printf(BLUE "Enter qualification: " RESET);
    fgets(s.qualification, 100, stdin);
    s.qualification[strcspn(s.qualification, "\n")] = 0;

    printf(BLUE "Enter salary: " RESET);
    scanf("%f", &s.salary);

    printf(BLUE "Enter join date (DD/MM/YYYY): " RESET);
    getchar();
    fgets(s.join_date, 20, stdin);
    s.join_date[strcspn(s.join_date, "\n")] = 0;

    printf(BLUE "Enter default shift (Morning/Evening/Night): " RESET);
    fgets(s.shift, 20, stdin);
    s.shift[strcspn(s.shift, "\n")] = 0;

    strcpy(s.status, "Active");

    staff[staff_count++] = s;
    saveStaffData();

    printf(GREEN "\n========================================\n");
    printf("     STAFF ADDED SUCCESSFULLY!        \n");
    printf("========================================\n" RESET);
    printf("Staff ID     : " YELLOW "%d\n" RESET, s.id);
    printf("Name         : " YELLOW "%s\n" RESET, s.name);
    printf("Role         : " YELLOW "%s\n" RESET, s.role);
    printf("Department   : " YELLOW "%s\n" RESET, s.department);
    printf("Contact      : " YELLOW "%s\n" RESET, s.contact);
    printf(CYAN "========================================\n" RESET);
}

// View all staff members
void viewStaff() {
    printf(CYAN "========================================\n");
    printf(BOLD "            ALL STAFF MEMBERS          \n");
    printf("========================================\n\n" RESET);

    if(staff_count == 0) {
        printf(RED "No staff members found!\n" RESET);
        return;
    }

    printf(YELLOW "ID\tName\t\t\tRole\t\tDepartment\t\tContact\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < staff_count; i++) {
        printf(GREEN "%d\t" RESET, staff[i].id);
        printf(CYAN "%-20s\t" RESET, staff[i].name);
        printf(MAGENTA "%-15s\t" RESET, staff[i].role);
        printf(BLUE "%-20s\t" RESET, staff[i].department);
        printf(YELLOW "%s\n" RESET, staff[i].contact);
    }

    printf("\nTotal staff members: " YELLOW "%d\n" RESET, staff_count);
}

// Edit staff information
void editStaff() {
    printf(CYAN "========================================\n");
    printf(BOLD "           EDIT STAFF INFORMATION      \n");
    printf("========================================\n\n" RESET);

    if(staff_count == 0) {
        printf(RED "No staff members available!\n" RESET);
        return;
    }

    int staff_id;
    int found = 0;

    printf(YELLOW "Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewStaff();

    printf(BLUE "\nEnter Staff ID to edit: " RESET);
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf(CYAN "\n========================================\n");
            printf(BOLD "     EDITING STAFF ID: %d            \n", staff_id);
            printf("========================================\n" RESET);

            printf("Current Name (" YELLOW "%s" RESET "): ", staff[i].name);
            getchar();
            char temp[50];
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].name, temp);
            }

            printf("Current Role (" YELLOW "%s" RESET "): ", staff[i].role);
            fgets(temp, 30, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].role, temp);
            }

            printf("Current Department (" YELLOW "%s" RESET "): ", staff[i].department);
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].department, temp);
            }

            printf("Current Contact (" YELLOW "%s" RESET "): ", staff[i].contact);
            fgets(temp, 15, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].contact, temp);
            }

            printf("Current Email (" YELLOW "%s" RESET "): ", staff[i].email);
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].email, temp);
            }

            printf("Current Salary (" YELLOW "%.2f" RESET "): ", staff[i].salary);
            char salary_input[20];
            fgets(salary_input, 20, stdin);
            if(strlen(salary_input) > 1) {
                staff[i].salary = atof(salary_input);
            }

            printf("Current Shift (" YELLOW "%s" RESET "): ", staff[i].shift);
            fgets(temp, 20, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(staff[i].shift, temp);
            }

            saveStaffData();

            printf(GREEN "\n========================================\n");
            printf("   STAFF INFORMATION UPDATED!         \n");
            printf("========================================\n" RESET);
            break;
        }
    }

    if(!found) {
        printf(RED "\nStaff with ID %d not found!\n" RESET, staff_id);
    }
}

// Delete staff member
void deleteStaff() {
    printf(CYAN "========================================\n");
    printf(BOLD "            DELETE STAFF               \n");
    printf("========================================\n\n" RESET);

    if(staff_count == 0) {
        printf(RED "No staff members available to delete!\n" RESET);
        return;
    }

    int staff_id;
    int found = 0;
    char confirm;

    printf(YELLOW "Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewStaff();

    printf(BLUE "\nEnter Staff ID to delete: " RESET);
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf(CYAN "\n========================================\n");
            printf(BOLD "           STAFF DETAILS               \n");
            printf("========================================\n" RESET);
            printf("ID           : " YELLOW "%d\n" RESET, staff[i].id);
            printf("Name         : " YELLOW "%s\n" RESET, staff[i].name);
            printf("Role         : " YELLOW "%s\n" RESET, staff[i].role);
            printf("Department   : " YELLOW "%s\n" RESET, staff[i].department);
            printf("Contact      : " YELLOW "%s\n" RESET, staff[i].contact);
            printf(CYAN "========================================\n" RESET);

            printf(YELLOW "\nAre you sure you want to delete this staff member? (y/n): " RESET);
            scanf(" %c", &confirm);

            if(confirm == 'y' || confirm == 'Y') {
                // Shift all staff after this position
                for(int j = i; j < staff_count - 1; j++) {
                    staff[j] = staff[j + 1];
                }
                staff_count--;

                saveStaffData();

                printf(GREEN "\n========================================\n");
                printf("     STAFF DELETED SUCCESSFULLY!       \n");
                printf("========================================\n" RESET);
                printf("Total staff members now: " YELLOW "%d\n" RESET, staff_count);
            } else {
                printf(YELLOW "\nOperation cancelled.\n" RESET);
            }
            break;
        }
    }

    if(!found) {
        printf(RED "\nStaff with ID %d not found!\n" RESET, staff_id);
    }
}

// Assign duty roster
void assignDutyRoster() {
    printf(CYAN "========================================\n");
    printf(BOLD "           ASSIGN DUTY ROSTER          \n");
    printf("========================================\n\n" RESET);

    if(staff_count == 0) {
        printf(RED "No staff members available!\n" RESET);
        return;
    }

    int staff_id;
    int found = 0;

    printf(YELLOW "Available Staff:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewStaff();

    printf(BLUE "\nEnter Staff ID to assign duty: " RESET);
    scanf("%d", &staff_id);

    for(int i = 0; i < staff_count; i++) {
        if(staff[i].id == staff_id) {
            found = 1;

            printf(CYAN "\n========================================\n");
            printf(BOLD "   ASSIGNING DUTY FOR: %s            \n", staff[i].name);
            printf("========================================\n" RESET);
            printf("Current Shift: " YELLOW "%s\n" RESET, staff[i].shift);

            printf(YELLOW "\nAvailable Shifts:\n");
            printf("1. Morning (7:00 AM - 3:00 PM)\n");
            printf("2. Evening (3:00 PM - 11:00 PM)\n");
            printf("3. Night (11:00 PM - 7:00 AM)\n");
            printf("4. Custom Shift\n" RESET);

            int choice;
            printf(BLUE "\nEnter shift choice (1-4): " RESET);
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
                    printf(BLUE "Enter custom shift details: " RESET);
                    fgets(staff[i].shift, 20, stdin);
                    staff[i].shift[strcspn(staff[i].shift, "\n")] = 0;
                    break;
                default:
                    printf(RED "Invalid choice! Keeping current shift.\n" RESET);
            }

            saveStaffData();

            printf(GREEN "\n========================================\n");
            printf("     DUTY ROSTER UPDATED!             \n");
            printf("========================================\n" RESET);
            printf("Staff Name: " YELLOW "%s\n" RESET, staff[i].name);
            printf("New Shift : " YELLOW "%s\n" RESET, staff[i].shift);
            break;
        }
    }

    if(!found) {
        printf(RED "\nStaff with ID %d not found!\n" RESET, staff_id);
    }
}

// Search staff
void searchStaff() {
    printf(CYAN "========================================\n");
    printf(BOLD "            SEARCH STAFF               \n");
    printf("========================================\n\n" RESET);

    if(staff_count == 0) {
        printf(RED "No staff members found!\n" RESET);
        return;
    }

    int choice;
    printf(YELLOW "1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Role\n");
    printf("4. Search by Department\n");
    printf(BLUE "Enter choice: " RESET);
    scanf("%d", &choice);

    getchar(); // Clear buffer

    if(choice == 1) {
        int id;
        printf(BLUE "Enter staff ID: " RESET);
        scanf("%d", &id);

        for(int i = 0; i < staff_count; i++) {
            if(staff[i].id == id) {
                printf(GREEN "\n========================================\n");
                printf("           STAFF FOUND                 \n");
                printf("========================================\n" RESET);
                printf("ID           : " YELLOW "%d\n" RESET, staff[i].id);
                printf("Name         : " YELLOW "%s\n" RESET, staff[i].name);
                printf("Role         : " YELLOW "%s\n" RESET, staff[i].role);
                printf("Department   : " YELLOW "%s\n" RESET, staff[i].department);
                printf("Contact      : " YELLOW "%s\n" RESET, staff[i].contact);
                printf("Email        : " YELLOW "%s\n" RESET, staff[i].email);
                printf("Address      : " YELLOW "%s\n" RESET, staff[i].address);
                printf("Qualification: " YELLOW "%s\n" RESET, staff[i].qualification);
                printf("Salary       : " YELLOW "$%.2f\n" RESET, staff[i].salary);
                printf("Join Date    : " YELLOW "%s\n" RESET, staff[i].join_date);
                printf("Shift        : " YELLOW "%s\n" RESET, staff[i].shift);
                printf("Status       : " YELLOW "%s\n" RESET, staff[i].status);
                printf(CYAN "========================================\n" RESET);
                return;
            }
        }
        printf(RED "\nStaff not found!\n" RESET);
    }
    else if(choice == 2 || choice == 3 || choice == 4) {
        char search_term[50];

        if(choice == 2) {
            printf(BLUE "Enter staff name: " RESET);
            fgets(search_term, 50, stdin);
        }
        else if(choice == 3) {
            printf(BLUE "Enter role: " RESET);
            fgets(search_term, 50, stdin);
        }
        else {
            printf(BLUE "Enter department: " RESET);
            fgets(search_term, 50, stdin);
        }

        search_term[strcspn(search_term, "\n")] = 0;

        int found = 0;
        printf(YELLOW "\nSearch Results:\n");
        printf("ID\tName\t\t\tRole\t\tDepartment\t\tContact\n");
        printf("--------------------------------------------------------------------------------\n" RESET);

        for(int i = 0; i < staff_count; i++) {
            if((choice == 2 && strstr(staff[i].name, search_term)) ||
               (choice == 3 && strstr(staff[i].role, search_term)) ||
               (choice == 4 && strstr(staff[i].department, search_term))) {
                printf(GREEN "%d\t" RESET, staff[i].id);
                printf(CYAN "%-20s\t" RESET, staff[i].name);
                printf(MAGENTA "%-15s\t" RESET, staff[i].role);
                printf(BLUE "%-20s\t" RESET, staff[i].department);
                printf(YELLOW "%s\n" RESET, staff[i].contact);
                found = 1;
            }
        }

        if(!found) {
            printf(RED "No staff members found!\n" RESET);
        }
    }
    else {
        printf(RED "Invalid choice!\n" RESET);
    }
}

// Edit Doctor Information
void editDoctor() {
    printf(CYAN "========================================\n");
    printf(BOLD "       EDIT DOCTOR INFORMATION         \n");
    printf("========================================\n\n" RESET);

    if(doctor_count == 0) {
        printf(RED "No doctors available!\n" RESET);
        return;
    }

    int doctor_id;
    int found = 0;

    printf(CYAN "Available Doctors:\n");
    printf("--------------------------------------------------------------------------------\n" RESET);
    viewDoctors();

    printf(BLUE "\nEnter Doctor ID to edit: " RESET);
    scanf("%d", &doctor_id);

    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id == doctor_id) {
            found = 1;

            printf(CYAN "\n========================================\n");
            printf(BOLD "     EDITING DOCTOR ID: %d            \n", doctor_id);
            printf("========================================\n" RESET);

            char temp[100];
            getchar(); // Clear buffer

            printf("Current Name (" YELLOW "%s" RESET ")\n", doctors[i].name);
            printf("New Name (press Enter to keep current): ");
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(doctors[i].name, temp);
            }

            printf("\nCurrent Specialization (" YELLOW "%s" RESET ")\n", doctors[i].specialization);
            printf("New Specialization (press Enter to keep current): ");
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(doctors[i].specialization, temp);
            }

            printf("\nCurrent Contact (" YELLOW "%s" RESET ")\n", doctors[i].contact);
            printf("New Contact (press Enter to keep current): ");
            fgets(temp, 15, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(doctors[i].contact, temp);
            }

            printf("\nCurrent Availability (" YELLOW "%s" RESET ")\n", doctors[i].availability);
            printf("New Availability (press Enter to keep current): ");
            fgets(temp, 50, stdin);
            if(strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(doctors[i].availability, temp);
            }

            saveData();

            clearScreen();
            printf(GREEN "\n========================================\n");
            printf("   DOCTOR INFORMATION UPDATED!         \n");
            printf("========================================\n" RESET);
            printf("Doctor ID      : " YELLOW "%d\n" RESET, doctors[i].id);
            printf("Name           : " YELLOW "%s\n" RESET, doctors[i].name);
            printf("Specialization : " YELLOW "%s\n" RESET, doctors[i].specialization);
            printf("Contact        : " YELLOW "%s\n" RESET, doctors[i].contact);
            printf("Availability   : " YELLOW "%s\n" RESET, doctors[i].availability);
            printf(CYAN "========================================\n" RESET);
            break;
        }
    }

    if(!found) {
        printf(RED "\nDoctor with ID %d not found!\n" RESET, doctor_id);
    }
}

// View Doctor Statistics
void viewDoctorStatistics() {
    printf(CYAN "========================================\n");
    printf(BOLD "        DOCTOR STATISTICS              \n");
    printf("========================================\n\n" RESET);

    if(doctor_count == 0) {
        printf(RED "No doctors available!\n" RESET);
        return;
    }

    printf(YELLOW "Total Doctors: %d\n\n" RESET, doctor_count);
    printf(CYAN "Doctor Performance Report:\n");
    printf("================================================================================\n" RESET);
    printf(YELLOW "ID\tName\t\t\tSpecialization\t\tAppointments\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    int total_appointments = 0;

    for(int i = 0; i < doctor_count; i++) {
        int doctor_appointments = 0;

        // Count appointments for this doctor
        for(int j = 0; j < appointment_count; j++) {
            if(appointments[j].doctor_id == doctors[i].id) {
                doctor_appointments++;
            }
        }

        total_appointments += doctor_appointments;

        printf(GREEN "%d\t" RESET, doctors[i].id);
        printf(CYAN "%-20s\t" RESET, doctors[i].name);
        printf(MAGENTA "%-20s\t" RESET, doctors[i].specialization);

        if(doctor_appointments > 0) {
            printf(YELLOW "%d\n" RESET, doctor_appointments);
        } else {
            printf(RED "%d\n" RESET, doctor_appointments);
        }
    }

    printf(CYAN "================================================================================\n" RESET);
    printf(YELLOW "\nTotal Appointments across all doctors: %d\n" RESET, total_appointments);

    if(doctor_count > 0) {
        printf(YELLOW "Average appointments per doctor: %.2f\n" RESET,
               (float)total_appointments / doctor_count);
    }

    // Find most active doctor
    int max_appointments = 0;
    int most_active_index = -1;

    for(int i = 0; i < doctor_count; i++) {
        int count = 0;
        for(int j = 0; j < appointment_count; j++) {
            if(appointments[j].doctor_id == doctors[i].id) {
                count++;
            }
        }
        if(count > max_appointments) {
            max_appointments = count;
            most_active_index = i;
        }
    }

    if(most_active_index >= 0 && max_appointments > 0) {
        printf(GREEN "\nMost Active Doctor: %s (%d appointments)\n" RESET,
               doctors[most_active_index].name, max_appointments);
    }

    // Specialization summary
    printf(CYAN "\n========================================\n");
    printf("    Specialization Distribution         \n");
    printf("========================================\n" RESET);

    // Simple specialization count (can be improved with dynamic allocation)
    char specializations[100][50];
    int spec_count[100] = {0};
    int unique_specs = 0;

    for(int i = 0; i < doctor_count; i++) {
        int found = 0;
        for(int j = 0; j < unique_specs; j++) {
            if(strcmp(specializations[j], doctors[i].specialization) == 0) {
                spec_count[j]++;
                found = 1;
                break;
            }
        }
        if(!found && unique_specs < 100) {
            strcpy(specializations[unique_specs], doctors[i].specialization);
            spec_count[unique_specs] = 1;
            unique_specs++;
        }
    }

    for(int i = 0; i < unique_specs; i++) {
        printf(YELLOW "%-30s: %d doctor(s)\n" RESET, specializations[i], spec_count[i]);
    }

    printf(CYAN "========================================\n" RESET);
}

// View Detailed Doctor Information
void viewDoctorDetails(int doctor_id) {
    int found = 0;

    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id == doctor_id) {
            found = 1;

            printf(CYAN "========================================\n");
            printf(BOLD "        DETAILED DOCTOR INFORMATION    \n");
            printf("========================================\n" RESET);
            printf("Doctor ID      : " YELLOW "%d\n" RESET, doctors[i].id);
            printf("Name           : " YELLOW "%s\n" RESET, doctors[i].name);
            printf("Specialization : " YELLOW "%s\n" RESET, doctors[i].specialization);
            printf("Contact        : " YELLOW "%s\n" RESET, doctors[i].contact);
            printf("Availability   : " YELLOW "%s\n" RESET, doctors[i].availability);
            printf(CYAN "========================================\n" RESET);

            // Show appointments for this doctor
            printf(YELLOW "\nAppointments:\n" RESET);
            printf("--------------------------------------------------------------------------------\n");

            int has_appointments = 0;
            for(int j = 0; j < appointment_count; j++) {
                if(appointments[j].doctor_id == doctor_id) {
                    has_appointments = 1;
                    printf("Appointment ID: " GREEN "%d\n" RESET, appointments[j].id);
                    printf("Patient ID    : %d\n", appointments[j].patient_id);
                    printf("Date          : %s\n", appointments[j].date);
                    printf("Time          : %s\n", appointments[j].time);
                    printf("Status        : %s\n", appointments[j].status);
                    printf("--------------------------------------------------------------------------------\n");
                }
            }

            if(!has_appointments) {
                printf(RED "No appointments scheduled for this doctor.\n" RESET);
            }

            break;
        }
    }

    if(!found) {
        printf(RED "Doctor with ID %d not found!\n" RESET, doctor_id);
    }
}

// Today's earnings
void dailyRevenueReport() {
    printf(CYAN "========================================\n");
    printf(BOLD "         DAILY REVENUE REPORT          \n");
    printf("========================================\n\n" RESET);

    if(bill_count == 0) {
        printf(RED "No bills found!\n" RESET);
        return;
    }

    // Get today's date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char today[20];
    sprintf(today, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    float daily_total = 0;
    int daily_bills = 0;

    printf(YELLOW "Bills for Today (%s):\n", today);
    printf("================================================================================\n" RESET);
    printf(YELLOW "Bill No\tPatient ID\tTotal Amount\tStatus\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    for(int i = 0; i < bill_count; i++) {
        if(strcmp(bills[i].date, today) == 0) {
            printf(GREEN "%d\t" RESET, bills[i].bill_no);
            printf("%d\t\t" RESET, bills[i].patient_id);
            printf(YELLOW "$%.2f\t\t" RESET, bills[i].total_amount);
            printf(BLUE "%s\n" RESET, bills[i].status);

            daily_total += bills[i].total_amount;
            daily_bills++;
        }
    }

    printf(CYAN "================================================================================\n" RESET);
    printf(YELLOW "\nDaily Summary:\n" RESET);
    printf("Total Bills Generated: " GREEN "%d\n" RESET, daily_bills);
    printf("Total Revenue        : " GREEN "$%.2f\n" RESET, daily_total);

    if(daily_bills > 0) {
        printf("Average Bill Amount  : " GREEN "$%.2f\n" RESET, daily_total / daily_bills);
    }

    printf(CYAN "========================================\n" RESET);
}

// Monthly income
void monthlyRevenueReport() {
    printf(CYAN "========================================\n");
    printf(BOLD "        MONTHLY REVENUE REPORT         \n");
    printf("========================================\n\n" RESET);

    if(bill_count == 0) {
        printf(RED "No bills found!\n" RESET);
        return;
    }

    int month, year;
    printf(BLUE "Enter month (1-12): " RESET);
    scanf("%d", &month);
    printf(BLUE "Enter year: " RESET);
    scanf("%d", &year);

    float monthly_total = 0;
    int monthly_bills = 0;
    int days[32] = {0}; // Revenue per day

    printf(YELLOW "\nMonthly Revenue Report for %d/%d:\n", month, year);
    printf("================================================================================\n" RESET);
    printf(YELLOW "Date\t\tBill Count\tDaily Revenue\n");
    printf("--------------------------------------------------------------------------------\n" RESET);

    // Initialize days array
    for(int i = 1; i <= 31; i++) {
        days[i] = 0;
    }

    for(int i = 0; i < bill_count; i++) {
        int bill_month, bill_year, bill_day;
        sscanf(bills[i].date, "%d/%d/%d", &bill_day, &bill_month, &bill_year);

        if(bill_month == month && bill_year == year) {
            monthly_total += bills[i].total_amount;
            monthly_bills++;
            days[bill_day] += bills[i].total_amount;
        }
    }

    // Display daily breakdown
    for(int day = 1; day <= 31; day++) {
        if(days[day] > 0) {
            int day_bill_count = 0;
            for(int i = 0; i < bill_count; i++) {
                int bill_month, bill_year, bill_day;
                sscanf(bills[i].date, "%d/%d/%d", &bill_day, &bill_month, &bill_year);
                if(bill_month == month && bill_year == year && bill_day == day) {
                    day_bill_count++;
                }
            }
            printf("%02d/%02d/%d\t" YELLOW "%d\t\t" GREEN "$%.2f\n" RESET,
                   day, month, year, day_bill_count, days[day]);
        }
    }

    printf(CYAN "================================================================================\n" RESET);
    printf(YELLOW "\nMonthly Summary:\n" RESET);
    printf("Total Bills Generated: " GREEN "%d\n" RESET, monthly_bills);
    printf("Total Revenue        : " GREEN "$%.2f\n" RESET, monthly_total);

    if(monthly_bills > 0) {
        printf("Average Bill Amount  : " GREEN "$%.2f\n" RESET, monthly_total / monthly_bills);
        printf("Average Daily Revenue: " GREEN "$%.2f\n" RESET, monthly_total / 30.0);
    }

    printf(CYAN "========================================\n" RESET);
}
