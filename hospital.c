#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Global arrays to store data
Patient patients[1000];
Doctor doctors[100];
Appointment appointments[500];
Bill bills[300];

int patient_count = 0;
int doctor_count = 0;
int appointment_count = 0;
int bill_count = 0;

// Function prototypes
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
void saveData();
void loadData();
int getNewPatientId();
int getNewDoctorId();
int getNewAppointmentId();
int getNewBillNo();
int adminLogin();
void adminMenu();
void removeDoctor();

int main() {
    loadData();
    int choice;

    printf("========================================\n");
    printf("   HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("========================================\n");

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                viewDoctors();
                break;
            case 5:
                searchDoctor();
                break;
            case 6:
                scheduleAppointment();
                break;
            case 7:
                viewAppointments();
                break;
            case 8:
                generateBill();
                break;
            case 9:
                viewBills();
                break;
            case 10:
                if(adminLogin()) {
                    adminMenu();
                }
                break;
            case 11:
                saveData();
                printf("Thank you for using Hospital Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 11);

    return 0;
}

void displayMenu() {
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
}

void addPatient() {
    if(patient_count >= 1000) {
        printf("Patient database full!\n");
        return;
    }

    Patient p;
    p.id = getNewPatientId();

    printf("\n=== ADD NEW PATIENT ===\n");
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
    printf("Patient added successfully! Patient ID: %d\n", p.id);
}

void viewPatients() {
    if(patient_count == 0) {
        printf("No patients found!\n");
        return;
    }

    printf("\n=== ALL PATIENTS ===\n");
    printf("ID\tName\tAge\tGender\tContact\n");
    printf("------------------------------------------------\n");

    for(int i = 0; i < patient_count; i++) {
        printf("%d\t%s\t%d\t%s\t%s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].contact);
    }
}

void searchPatient() {
    if(patient_count == 0) {
        printf("No patients found!\n");
        return;
    }

    int choice;
    printf("\n=== SEARCH PATIENT ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        int id;
        printf("Enter patient ID: ");
        scanf("%d", &id);

        for(int i = 0; i < patient_count; i++) {
            if(patients[i].id == id) {
                printf("\nPatient Found:\n");
                printf("ID: %d\n", patients[i].id);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Gender: %s\n", patients[i].gender);
                printf("Contact: %s\n", patients[i].contact);
                printf("Address: %s\n", patients[i].address);
                printf("Medical History: %s\n", patients[i].medical_history);
                return;
            }
        }
        printf("Patient not found!\n");
    }
    else if(choice == 2) {
        char name[50];
        printf("Enter patient name: ");
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < patient_count; i++) {
            if(strstr(patients[i].name, name) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\tAge\tGender\tContact\n");
                    printf("------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%s\t%d\t%s\t%s\n",
                       patients[i].id, patients[i].name, patients[i].age,
                       patients[i].gender, patients[i].contact);
            }
        }
        if(!found) {
            printf("Patient not found!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}


void viewDoctors() {
    if(doctor_count == 0) {
        printf("No doctors found!\n");
        return;
    }

    printf("\n=== ALL DOCTORS ===\n");
    printf("ID\tName\t\tSpecialization\t\tContact\n");
    printf("--------------------------------------------------------\n");

    for(int i = 0; i < doctor_count; i++) {
        printf("%d\t%s\t%s\t\t%s\n",
               doctors[i].id, doctors[i].name, doctors[i].specialization,
               doctors[i].contact);
    }
}

void searchDoctor() {
    if(doctor_count == 0) {
        printf("No doctors found!\n");
        return;
    }

    int choice;
    printf("\n=== SEARCH DOCTOR ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Specialization\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        int id;
        printf("Enter doctor ID: ");
        scanf("%d", &id);

        for(int i = 0; i < doctor_count; i++) {
            if(doctors[i].id == id) {
                printf("\nDoctor Found:\n");
                printf("ID: %d\n", doctors[i].id);
                printf("Name: %s\n", doctors[i].name);
                printf("Specialization: %s\n", doctors[i].specialization);
                printf("Contact: %s\n", doctors[i].contact);
                printf("Availability: %s\n", doctors[i].availability);
                return;
            }
        }
        printf("Doctor not found!\n");
    }
    else if(choice == 2) {
        char name[50];
        printf("Enter doctor name: ");
        getchar();
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].name, name) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\tSpecialization\t\tContact\n");
                    printf("--------------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%s\t%s\t\t%s\n",
                       doctors[i].id, doctors[i].name, doctors[i].specialization,
                       doctors[i].contact);
            }
        }
        if(!found) {
            printf("Doctor not found!\n");
        }
    }
    else if(choice == 3) {
        char specialization[50];
        printf("Enter specialization: ");
        getchar();
        fgets(specialization, 50, stdin);
        specialization[strcspn(specialization, "\n")] = 0;

        int found = 0;
        for(int i = 0; i < doctor_count; i++) {
            if(strstr(doctors[i].specialization, specialization) != NULL) {
                if(!found) {
                    printf("\nSearch Results:\n");
                    printf("ID\tName\t\tSpecialization\t\tContact\n");
                    printf("--------------------------------------------------------\n");
                    found = 1;
                }
                printf("%d\t%s\t%s\t\t%s\n",
                       doctors[i].id, doctors[i].name, doctors[i].specialization,
                       doctors[i].contact);
            }
        }
        if(!found) {
            printf("No doctors found with this specialization!\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
}

void scheduleAppointment() {
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

    printf("\n=== SCHEDULE APPOINTMENT ===\n");

    printf("Available Patients:\n");
    viewPatients();
    printf("Enter patient ID: ");
    scanf("%d", &a.patient_id);

    printf("Available Doctors:\n");
    viewDoctors();
    printf("Enter doctor ID: ");
    scanf("%d", &a.doctor_id);

    printf("Enter date (DD/MM/YYYY): ");
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
    printf("Appointment scheduled successfully! Appointment ID: %d\n", a.id);
}

void viewAppointments() {
    if(appointment_count == 0) {
        printf("No appointments found!\n");
        return;
    }

    printf("\n=== ALL APPOINTMENTS ===\n");
    printf("ID\tPatient ID\tDoctor ID\tDate\t\tTime\tStatus\n");
    printf("------------------------------------------------------------\n");

    for(int i = 0; i < appointment_count; i++) {
        printf("%d\t%d\t\t%d\t\t%s\t%s\t%s\n",
               appointments[i].id, appointments[i].patient_id,
               appointments[i].doctor_id, appointments[i].date,
               appointments[i].time, appointments[i].status);
    }
}

void generateBill() {
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

    printf("\n=== GENERATE BILL ===\n");

    printf("Available Patients:\n");
    viewPatients();
    printf("Enter patient ID: ");
    scanf("%d", &b.patient_id);

    printf("Enter consultation fee: ");
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
        printf("\n Bill saved as: %s\n", filename);
    } else {
        printf("\n  Warning: Could not create text file for bill!\n");
    }

    // Display on screen
    printf("\n=== BILL GENERATED ===\n");
    printf("Bill No: %d\n", b.bill_no);
    printf("Patient ID: %d\n", b.patient_id);
    printf("Patient Name: %s\n", patient_name);
    printf("Consultation Fee: $%.2f\n", b.consultation_fee);
    printf("Medicine Charges: $%.2f\n", b.medicine_charges);
    printf("Room Charges: $%.2f\n", b.room_charges);
    printf("Lab Charges: $%.2f\n", b.lab_charges);
    printf("Total Amount: $%.2f\n", b.total_amount);
    printf("Date: %s\n", b.date);
    printf("Status: %s\n", b.status);
}

void viewBills() {
    if(bill_count == 0) {
        printf("No bills found!\n");
        return;
    }

    printf("\n=== ALL BILLS ===\n");
    printf("Bill No\tPatient ID\tTotal Amount\tDate\t\tStatus\n");
    printf("--------------------------------------------------------\n");

    for(int i = 0; i < bill_count; i++) {
        printf("%d\t%d\t\t$%.2f\t\t%s\t%s\n",
               bills[i].bill_no, bills[i].patient_id,
               bills[i].total_amount, bills[i].date, bills[i].status);
    }
}

// Utility functions for generating IDs
int getNewPatientId() {
    static int last_id = 1000;
    return ++last_id;
}

int getNewDoctorId() {
    static int last_id = 100;
    return ++last_id;
}

int getNewAppointmentId() {
    static int last_id = 5000;
    return ++last_id;
}

int getNewBillNo() {
    static int last_bill_no = 10000;
    return ++last_bill_no;
}

// File handling functions
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
}
//  ADMIN PANEL FUNCTIONS

// Admin Login Function
int adminLogin() {
    char username[50];
    char password[50];
    int attempts = 0;

    printf("\n========================================\n");
    printf("          ADMIN LOGIN PANEL            \n");
    printf("========================================\n");

    while(attempts < 3) {
        printf("\nUsername: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        // Default credentials (you can change these)
        if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("\n Login Successful! Welcome Admin!\n");
            return 1;  // Success
        } else {
            attempts++;
            printf(" Invalid credentials! Attempts remaining: %d\n", 3 - attempts);
        }
    }

    printf("\n Access Denied! Too many failed attempts.\n");
    return 0;  // Failed
}

// Admin Menu
void adminMenu() {
    int choice;

    do {
        printf("\n========================================\n");
        printf("             ADMIN PANEL                \n");
        printf("========================================\n");
        printf("  1. Add New Doctor                    \n");
        printf("  2. Remove Doctor                     \n");
        printf("  3. View All Doctors                  \n");
        printf("  4. Search Doctor                     \n");
        printf("  5. Logout                            \n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                removeDoctor();
                break;
            case 3:
                viewDoctors();
                break;
            case 4:
                searchDoctor();
                break;
            case 5:
                printf("\n Logged out successfully!\n");
                break;
            default:
                printf(" Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

// Remove Doctor Function
void removeDoctor() {
    if(doctor_count == 0) {
        printf("\n No doctors available to remove!\n");
        return;
    }

    int doctor_id;
    int found = 0;
    char confirm;

    printf("\n========================================\n");
    printf("            REMOVE DOCTOR               \n");
    printf("========================================\n\n");

    // Show all doctors
    printf("Available Doctors:\n");
    viewDoctors();

    printf("\nEnter Doctor ID to remove: ");
    scanf("%d", &doctor_id);

    // Search for the doctor
    for(int i = 0; i < doctor_count; i++) {
        if(doctors[i].id == doctor_id) {
            found = 1;

            // Display doctor details
            printf("\n========================================\n");
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
                printf("\n WARNING: This doctor has existing appointments!\n");
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

                printf("\n========================================\n");
                printf("     DOCTOR REMOVED SUCCESSFULLY!     \n");
                printf("========================================\n");
                printf(" Total doctors now: %d\n", doctor_count);
            } else {
                printf("\n Operation cancelled.\n");
            }

            return;
        }
    }

    if(!found) {
        printf("\n Doctor with ID %d not found!\n", doctor_id);
    }
}

// Modified addDoctor function (with better formatting)
void addDoctor() {
    if(doctor_count >= 100) {
        printf("\n Doctor database full! Cannot add more doctors.\n");
        return;
    }

    Doctor d;
    d.id = getNewDoctorId();

    printf("\n========================================\n");
    printf("           ADD NEW DOCTOR               \n");
    printf("========================================\n\n");

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

    printf("\n========================================\n");
    printf("     DOCTOR ADDED SUCCESSFULLY!       \n");
    printf("========================================\n");
    printf("Doctor ID      : %d\n", d.id);
    printf("Name           : %s\n", d.name);
    printf("Specialization : %s\n", d.specialization);
    printf("Contact        : %s\n", d.contact);
    printf("Availability   : %s\n", d.availability);
    printf("========================================\n");
    printf(" Total doctors: %d\n", doctor_count);
}
