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
void viewPatients();
void searchPatient();
void addDoctor();
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

int main() {
    loadData();
    int choice;

    printf("=== HOSPITAL MANAGEMENT SYSTEM ===\n");

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
                addDoctor();
                break;
            case 5:
                viewDoctors();
                break;
            case 6:
                searchDoctor();
                break;
            case 7:
                scheduleAppointment();
                break;
            case 8:
                viewAppointments();
                break;
            case 9:
                generateBill();
                break;
            case 10:
                viewBills();
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
    printf("4. Add New Doctor\n");
    printf("5. View All Doctors\n");
    printf("6. Search Doctor\n");
    printf("7. Schedule Appointment\n");
    printf("8. View Appointments\n");
    printf("9. Generate Bill\n");
    printf("10. View Bills\n");
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

void addDoctor() {
    if(doctor_count >= 100) {
        printf("Doctor database full!\n");
        return;
    }

    Doctor d;
    d.id = getNewDoctorId();

    printf("\n=== ADD NEW DOCTOR ===\n");
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

    printf("Enter availability: ");
    fgets(d.availability, 50, stdin);
    d.availability[strcspn(d.availability, "\n")] = 0;

    doctors[doctor_count++] = d;

    saveData();
    printf("Doctor added successfully! Doctor ID: %d\n", d.id);
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

    printf("\n=== BILL GENERATED ===\n");
    printf("Bill No: %d\n", b.bill_no);
    printf("Patient ID: %d\n", b.patient_id);
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
