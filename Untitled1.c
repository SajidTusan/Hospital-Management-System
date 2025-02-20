#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Patient {
    int id;
    char name[50];
    int age;
    char gender;
    char healthCondition[100];
    int isAdmitted;
    char date[11];
    char doctorName[50];
    char showHistory;
    int bedNo;
    char reasonForAdmission[100];
    char treatmentHistory[500];
};

struct Staff {
    int id;
    char name[50];
    int age;
    char gender;
    char department[50];
    char schedule[7][50];
    struct Staff *next;
};

// Function prototypes
void patientLogin();
void managementLogin();
void fixSchedule();
void viewTreatmentHistory();
void readPatientFromFile(struct Patient patients[], int *numPatients);
void writePatientToFile(struct Patient patient);
void readStaffFromFile(struct Staff **head);
void writeStaffToFile(struct Staff *staff);
void addPatient(struct Patient patients[], int *numPatients);
int isIdExisting(struct Patient patients[], int numPatients, int id);
void searchPatient(struct Patient patients[], int numPatients);
void dischargePatient(struct Patient patients[], int numPatients);
void displayTreatmentHistory(struct Patient patients[], int numPatients, int id);
void addStaff(struct Staff **head);
int checkExistingId(struct Staff *head, int id);
void searchStaff(struct Staff *head);
void addSchedule(struct Staff *head);
void displaySchedule(struct Staff *head);

int main() {
    // Read patient and staff information from files
    struct Patient patients[100];
    int numPatients = 0;
    readPatientFromFile(patients, &numPatients);

    struct Staff *staffHead = NULL;
    readStaffFromFile(&staffHead);

    // Display menu and get user's choice
    int choice;
    printf("Welcome!\n");
    printf("1. Patient Login\n");
    printf("2. Management Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Perform actions based on user's choice
    switch (choice) {
        case 1:
            patientLogin();
            break;
        case 2:
            managementLogin();
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    // Free memory for staff members before exiting
    while (staffHead != NULL) {
        struct Staff *temp = staffHead;
        staffHead = staffHead->next;
        free(temp);
    }

    return 0;
}

// Function definitions...

void patientLogin() {
    // Your patient login code goes here
    int uniqueId;
    char password[20];
    int loggedIn = 0;

    printf("Enter unique ID: ");
    scanf("%d", &uniqueId);

    printf("Enter password: ");
    scanf("%s", password);

    // Simulate login validation - for demonstration purpose always set to true
    loggedIn = 1;

    if (loggedIn) {
        printf("Patient login successful!\n");
        printf("Welcome, Patient %d!\n", uniqueId);
        // Display additional options
        printf("1. Fix Schedule\n");
        printf("2. View Treatment History\n");
        printf("Enter your choice: ");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                fixSchedule(); // Placeholder implementation
                break;
            case 2:
                viewTreatmentHistory(); // Placeholder implementation
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } else {
        printf("Invalid unique ID or password!\n");
    }
}

void managementLogin() {
    // Your management login code goes here
    struct Patient patients[100];
    int numPatients = 0;

    struct Staff *staffHead = NULL;

    int choice;

    printf("Enter management ID: ");
    scanf("%d", &choice);

    printf("Enter management password: ");
    char password[20];
    scanf("%s", password);

    // Simulate login validation - for demonstration purpose always set to true
    int loggedIn = 1;

    if (loggedIn) {
        printf("Management login successful!\n");
        printf("Welcome, Management ID %d!\n", choice);
        // Display additional options
        do {
            printf("\nHospital Management System\n");
            printf("1. Add Patient\n");
            printf("2. Search Patient\n");
            printf("3. Discharge Patient\n");
            printf("4. Add Staff\n");
            printf("5. Search Staff\n");
            printf("6. Add/Update Schedule\n");
            printf("7. Display Schedule\n");
            printf("8. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addPatient(patients, &numPatients);
                    break;
                case 2:
                    searchPatient(patients, numPatients);
                    break;
                case 3:
                    dischargePatient(patients, numPatients);
                    break;
                case 4:
                    addStaff(&staffHead);
                    break;
                case 5:
                    searchStaff(staffHead);
                    break;
                case 6:
                    addSchedule(staffHead);
                    break;
                case 7:
                    displaySchedule(staffHead);
                    break;
                case 8:
                    printf("Exiting the program.\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 8);

        // Free memory for staff members before exiting
        while (staffHead != NULL) {
            struct Staff *temp = staffHead;
            staffHead = staffHead->next;
            free(temp);
        }
    }
}

// Other function definitions...

void fixSchedule() {
    // Placeholder implementation
    printf("This function is a placeholder for fixing the schedule.\n");
}

void viewTreatmentHistory() {
    // Placeholder implementation
    printf("This function is a placeholder for viewing treatment history.\n");
}

// Function to add a patient
// Function to add a patient
void addPatient(struct Patient patients[], int *numPatients) {
    // Your add patient code goes here
    struct Patient newPatient;

    printf("Enter patient ID: ");
    scanf("%d", &newPatient.id);

    if (isIdExisting(patients, *numPatients, newPatient.id)) {
        printf("Existing ID number '%d'\n", newPatient.id);
        return;
    }

    printf("Enter patient name: ");
    scanf("%s", newPatient.name);

    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);

    printf("Enter patient gender (M/F): ");
    scanf(" %c", &newPatient.gender);

    printf("Enter patient health condition: ");
    scanf("%s", newPatient.healthCondition);

    int choice;
    printf("Choose patient status:\n");
    printf("1. For normal check-up\n");
    printf("2. For admission in the hospital\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        newPatient.isAdmitted = 0; // Normal check-up, not admitted

        // Additional options for normal check-up
        printf("Enter date (DD/MM/YYYY): ");
        scanf("%s", newPatient.date);

        printf("Enter consulting doctor name: ");
        scanf("%s", newPatient.doctorName);

        printf("Show previous treatment history? (Y/N): ");
        scanf(" %c", &newPatient.showHistory);

        if (newPatient.showHistory == 'Y') {
            displayTreatmentHistory(patients, *numPatients, newPatient.id);
        }
    } else if (choice == 2) {
        newPatient.isAdmitted = 1; // Admitted to the hospital
        // Additional options for admitted patients
        printf("Enter date of admission (DD/MM/YYYY): ");
        scanf("%s", newPatient.date);

        printf("Enter bed number: ");
        scanf("%d", &newPatient.bedNo);

        printf("Enter reason for admission: ");
        scanf("%s", newPatient.reasonForAdmission);
    } else {
        printf("Invalid choice!\n");
        return;
    }

    // Add the new patient to the array
    patients[*numPatients] = newPatient;
    (*numPatients)++;

    // Write patient information to file
    writePatientToFile(newPatient);
}


// Function to check if ID already exists in patients array
int isIdExisting(struct Patient patients[], int numPatients, int id) {
    // Implementation remains unchanged
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == id) {
            return 1; // ID exists
        }
    }
    return 0; // ID does not exist
}

// Other function definitions...
// Function to search for a patient
void searchPatient(struct Patient patients[], int numPatients) {
    // Your search patient code goes here
    int choice;
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int searchId;
    char searchName[50];

    switch (choice) {
        case 1:
            printf("Enter patient ID: ");
            scanf("%d", &searchId);

            for (int i = 0; i < numPatients; i++) {
                if (patients[i].id == searchId) {
                    printf("Patient ID: %d\n", patients[i].id);
                    printf("Name: %s\n", patients[i].name);
                    printf("Age: %d\n", patients[i].age);
                    printf("Gender: %c\n", patients[i].gender);
                    printf("Health Condition: %s\n", patients[i].healthCondition);
                    printf("Date: %s\n", patients[i].date);
                    printf("Consulting Doctor: %s\n", patients[i].doctorName);
                    printf("Show Treatment History: %c\n", patients[i].showHistory);
                    if (patients[i].isAdmitted) {
                        printf("Admission Status: Admitted\n");
                        printf("Bed Number: %d\n", patients[i].bedNo);
                        printf("Reason for Admission: %s\n", patients[i].reasonForAdmission);
                    } else {
                        printf("Admission Status: Discharged\n");
                    }

                    // Check if treatment history is requested
                    if (patients[i].showHistory == 'Y') {
                        displayTreatmentHistory(patients, numPatients, searchId);
                    }
                    return;
                }
            }
            printf("Patient with ID %d not found.\n", searchId);
            break;

        case 2:
            printf("Enter patient name: ");
            scanf("%s", searchName);

            for (int i = 0; i < numPatients; i++) {
                if (strcmp(patients[i].name, searchName) == 0) {
                    printf("Patient ID: %d\n", patients[i].id);
                    printf("Name: %s\n", patients[i].name);
                    printf("Age: %d\n", patients[i].age);
                    printf("Gender: %c\n", patients[i].gender);
                    printf("Health Condition: %s\n", patients[i].healthCondition);
                    printf("Date: %s\n", patients[i].date);
                    printf("Consulting Doctor: %s\n", patients[i].doctorName);
                    printf("Show Treatment History: %c\n", patients[i].showHistory);
                    if (patients[i].isAdmitted) {
                        printf("Admission Status: Admitted\n");
                        printf("Bed Number: %d\n", patients[i].bedNo);
                        printf("Reason for Admission: %s\n", patients[i].reasonForAdmission);
                    } else {
                        printf("Admission Status: Discharged\n");
                    }

                    // Check if treatment history is requested
                    if (patients[i].showHistory == 'Y') {
                        displayTreatmentHistory(patients, numPatients, patients[i].id);
                    }
                    return;
                }
            }
            printf("Patient with name '%s' not found.\n", searchName);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }
}

// Function to discharge a patient
void dischargePatient(struct Patient patients[], int numPatients) {
    // Your discharge patient code goes here
    printf("Enter patient ID to discharge: ");
    int dischargeId;
    scanf("%d", &dischargeId);

    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == dischargeId) {
            if (patients[i].isAdmitted) {
                patients[i].isAdmitted = 0;
                printf("Patient with ID %d has been discharged.\n", dischargeId);
            } else {
                printf("Patient with ID %d is already discharged.\n", dischargeId);
            }
            return;
        }
    }

    printf("Patient with ID %d not found.\n", dischargeId);
}

// Function to display treatment history for a patient
void displayTreatmentHistory(struct Patient patients[], int numPatients, int id) {
    // Your display treatment history code goes here
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].id == id) {
            // Check if treatment history is available
            if (strcmp(patients[i].treatmentHistory, "") != 0) {
                printf("Treatment History for Patient ID %d:\n", id);
                printf("%s\n", patients[i].treatmentHistory);
            } else {
                printf("No history found for Patient ID %d.\n", id);
            }
            return;
        }
    }
    printf("Patient with ID %d not found.\n", id);
}

// Function to add a staff member
void addStaff(struct Staff **head) {
    // Your add staff code goes here
    struct Staff *newStaff = (struct Staff *)malloc(sizeof(struct Staff));
    if (newStaff == NULL) {
        printf("Memory allocation error.\n");
        return;
    }
    printf("Enter staff ID: ");
    int id;
    scanf("%d", &id);

    if (checkExistingId(*head, id)) {
        printf("Existing ID number %d.\n", id);
        free(newStaff);
        return;
    }

    newStaff->id = id;
    printf("Enter staff name: ");
    scanf("%s", newStaff->name);

    printf("Enter staff age: ");
    scanf("%d", &newStaff->age);

    printf("Enter staff gender (M/F): ");
    scanf(" %c", &newStaff->gender);

    printf("Enter staff department: ");
    scanf("%s", newStaff->department);

    // Initialize schedule
    for (int i = 0; i < 7; i++) {
        strcpy(newStaff->schedule[i], "Off");
    }

    // Add new staff to the list
    newStaff->next = *head;
    *head = newStaff;

    // Write staff information to file
    writeStaffToFile(*head);
}

// Function to check if ID already exists in staff list
int checkExistingId(struct Staff *head, int id) {
    struct Staff *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return 1; // ID exists
        }
        current = current->next;
    }
    return 0; // ID does not exist
}

// Other function definitions...
// Function to search for a staff member
void searchStaff(struct Staff *head) {
    // Your search staff code goes here
    int searchId;
    printf("Enter staff ID to search: ");
    scanf("%d", &searchId);

    struct Staff *current = head;
    while (current != NULL) {
        if (current->id == searchId) {
            printf("Staff ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Gender: %c\n", current->gender);
            printf("Department: %s\n", current->department);
            printf("Schedule:\n");
            for (int i = 0; i < 7; i++) {
                printf("%d. %s\n", i + 1, current->schedule[i]);
            }
            return;
        }
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", searchId);
}

// Function to add/update schedule for a staff member
void addSchedule(struct Staff *head) {
    // Your add schedule code goes here
    int searchId;
    printf("Enter staff ID to add/update schedule: ");
    scanf("%d", &searchId);

    struct Staff *current = head;
    while (current != NULL) {
        if (current->id == searchId) {
            printf("Enter day number (1-7) to add/update schedule: ");
            int day;
            scanf("%d", &day);
            if (day < 1 || day > 7) {
                printf("Invalid day number.\n");
                return;
            }

            printf("Enter schedule for day %d: ", day);
            scanf("%s", current->schedule[day - 1]);
            printf("Schedule updated for day %d.\n", day);
            return;
        }
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", searchId);
}

// Function to display schedule for all staff members
void displaySchedule(struct Staff *head) {
    // Your display schedule code goes here
    struct Staff *current = head;
    while (current != NULL) {
        printf("Staff ID: %d\n", current->id);
        printf("Name: %s\n", current->name);
        printf("Department: %s\n", current->department);
        printf("Schedule:\n");
        for (int i = 0; i < 7; i++) {
            printf("%d. %s\n", i + 1, current->schedule[i]);
        }
        printf("\n");
        current = current->next;
    }
}

// Function to read patient information from file
void readPatientFromFile(struct Patient patients[], int *numPatients) {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open patients.txt file.\n");
        return;
    }

    printf("Reading patient data from file...\n");

    while (fscanf(file, "%d %s %d %c %s %d %s %s %c %d %s %s",
                  &patients[*numPatients].id,
                  patients[*numPatients].name,
                  &patients[*numPatients].age,
                  &patients[*numPatients].gender,
                  patients[*numPatients].healthCondition,
                  &patients[*numPatients].isAdmitted,
                  patients[*numPatients].date,
                  patients[*numPatients].doctorName,
                  &patients[*numPatients].showHistory,
                  &patients[*numPatients].bedNo,
                  patients[*numPatients].reasonForAdmission,
                  patients[*numPatients].treatmentHistory) != EOF) {
        (*numPatients)++;
    }

    fclose(file);
}

// Function to write patient information to file
void writePatientToFile(struct Patient patient) {
    // Your write patient to file code goes here
    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    fprintf(file, "%d %s %d %c %s %d %s %s %c %d %s %s\n",
            patient.id,
            patient.name,
            patient.age,
            patient.gender,
            patient.healthCondition,
            patient.isAdmitted,
            patient.date,
            patient.doctorName,
            patient.showHistory,
            patient.bedNo,
            patient.reasonForAdmission,
            patient.treatmentHistory);

    fclose(file);
}

// Function to read staff information from file
void readStaffFromFile(struct Staff **head) {
    FILE *file = fopen("staff.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open staff.txt file.\n");
        return;
    }

    printf("Reading staff data from file...\n");

    while (!feof(file)) {
        struct Staff *newStaff = (struct Staff *)malloc(sizeof(struct Staff));
        if (newStaff == NULL) {
            printf("Memory allocation error.\n");
            fclose(file);
            return;
        }

        fscanf(file, "%d %s %d %c %s",
               &newStaff->id,
               newStaff->name,
               &newStaff->age,
               &newStaff->gender,
               newStaff->department);

        // Initialize schedule
        for (int i = 0; i < 7; i++) {
            strcpy(newStaff->schedule[i], "Off");
        }

        // Add new staff to the list
        newStaff->next = *head;
        *head = newStaff;
    }

    fclose(file);
}

// Function to write staff information to file
void writeStaffToFile(struct Staff *staff) {
    // Your write staff to file code goes here
    FILE *file = fopen("staff.txt", "a");
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    fprintf(file, "%d %s %d %c %s\n",
            staff->id,
            staff->name,
            staff->age,
            staff->gender,
            staff->department);

    fclose(file);
}



