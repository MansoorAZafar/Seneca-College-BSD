/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  : Mansoor Ahmad Zafar
Student ID#: 100503226
Email      : mzafar15@myseneca.ca
Section    : NBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend(); 
   	    //printf("\n"); // I ADDED THIS PRINTLINE SINCE I NEEDED IT CUS OF SPACING
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void displayAllPatients(const struct Patient patient[], int max, int fmt)
{

    displayPatientTableHeader();
    int i = 0;
    int count = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    i = 0;
    for (i = 0; i < max; i++) {

        if (patient[i].patientNumber > 0) {
            printf("%05d %-15s ", patient[i].patientNumber,
                patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            //printf("\ni is %d", i);
        }
        else {
            //printf("I didnt display properly..\n");
            //i++;
        }

    }
    putchar('\n');
    //suspend();
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientData(const struct Patient patient[], int max) {
    int choice = 0;
    printf("Search Options\n");
    printf("==========================\n"
        "1) By patient number\n"
        "2) By phone number\n"
        "..........................\n"
        "0) Previous menu\n"
        "..........................\n"
        "Selection: ");
    scanf("%d", &choice);
    switch (choice) {
    case 0: printf("\n"); break;
    case 1: searchPatientByPatientNumber(patient, max); break;
    case 2: searchPatientByPhoneNumber(patient, max); break;
    default: while (choice < 0 || choice > 2) { printf("\nPick a valid number : "); scanf("%d", &choice); } break;
    }
    //putchar('\n');
    if (choice != 0) { searchPatientData(patient, max); }
    return;
}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void addPatient(struct Patient patient[], int max) {
    int i = 0, count = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    if (count == max) {
        //printf("Max value is %d and count value is %d", max, count);
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else {
        //inputPatient(&patient[count]);
        printf(""
            "Patient Data Input\n"
            "------------------\n"
            "Number: ");
        scanf("%d", &patient[count].patientNumber);
        printf(""
            "Name  : ");
        inputCString(patient[count].name, 1, NAME_LEN);
        printf("\n"
            "Phone Information\n"
            "-----------------\n"
            "How will the patient like to be contacted?\n"
            "1. Cell\n"
            "2. Home\n"
            "3. Work\n"
            "4. TBD\n"
            "Selection: ");
        int choice = 0;
        scanf("%d", &choice);
	char*ch; printf("\n");
        switch (choice) {
        case 1: ch = "CELL"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[count].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[count].phone.number); printf("\n"); break;
        case 2: ch = "HOME"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[count].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[count].phone.number); printf("\n"); break;
        case 3: ch = "WORK"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[count].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[count].phone.number); printf("\n"); break;
        case 4: ch = "TBD"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[count].phone.description[i] = ch[i]; } break;
        default: while (choice < 1 || choice > 4) { printf("Invalid choice... "); scanf("%d", &choice); }; break;
        }

        printf("*** New patient record added ***\n\n");
        //suspend();
    }

}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void editPatient(struct Patient patient[], int max) {
    int i = 0; int choice = 0; char*ch; int z = 0; int pos = 0;
    printf("Enter the patient number: ");
    int num = 0;
    scanf("%d", &num);
    printf("\nEdit Patient (0%d)\n", num);
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == num) {
	    pos = i;
            printf("=========================\n");
            printf("1) NAME : %s\n", patient[pos].name);
            printf("2) PHONE: ");
            printf("(");
            int k = 0;
            if (patient[pos].phone.description[0] != 'T') {
                for (k = 0; k < 10; k++) { printf("%c", patient[pos].phone.number[k]); if (k == 2) { printf(")"); } if (k == 5) { printf("-"); } }
            }
            else {
                for (k = 0; k < 10; k++) { printf("_"); if (k == 2) { printf(")"); } if (k == 5) { printf("-"); } }
            }
            
            printf("\n-------------------------\n"
                "0) Previous menu\n"
                "-------------------------\n"
                "Selection: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1: printf("\nName  : "); inputCString(patient[pos].name, 1, max); printf("\nPatient record updated!\n"); break;
            case 2: 
                printf("\nPhone Information\n"
                "-----------------\n"
                "How will the patient like to be contacted?\n"
                "1. Cell\n"
                "2. Home\n"
                "3. Work\n"
                "4. TBD\n"
                "Selection: ");
                int pick = 0;
                scanf("%d", &pick);
		
                printf("Contact: ");
                if (pick == 1) { printf("CELL"); ch = "CELL"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; }}
                else if (pick == 2) { printf("HOME"); ch = "HOME"; i = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                else if (pick == 3) { printf("WORK"); ch = "WORK"; i = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; }}
                else { printf("TBD"); }
                printf("Number : ");
		scanf("%s",  patient[pos].phone.number);
                printf("\nPatient record updated!\n");
                break;
            }
            while (choice != 0) {
            	z = 0;
	        printf("\nEdit Patient (0%d)\n", num);
                printf("=========================\n");
                printf("1) NAME : %s\n", patient[pos].name);
                printf("2) PHONE: "); 
                printf("(");
                k = 0;
                if (patient[i].phone.description[0] != 'T') {
                    for (k = 0; k < 10; k++) { printf("%c", patient[pos].phone.number[k]); if (k == 2) { printf(")"); } if (k == 5) { printf("-"); } }
                }
                else {
                    for (k = 0; k < 10; k++) { printf("_"); if (k == 2) { printf(")"); } if (k == 5) { printf("-"); } }
                }
                printf("\n-------------------------\n"
                    "0) Previous menu\n"
                    "-------------------------\n"
                    "Selection: ");

                scanf("%d", &choice);
                switch (choice) {
                case 1: printf("\nName  : "); inputCString(patient[pos].name, 1, max); printf("\nPatient record updated!\n"); break;
                case 2: 
                    printf("\nPhone Information\n"
                        "-----------------\n"
                        "How will the patient like to be contacted?\n"
                        "1. Cell\n"
                        "2. Home\n"
                        "3. Work\n"
                        "4. TBD\n"
                        "Selection: ");
                    int pick = 0;
                    scanf("%d", &pick);
                    printf("\nContact: ");
                    if (pick == 1) { printf("CELL\n"); ch = "CELL"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; }}
                    else if (pick == 2) { printf("HOME\n"); ch = "HOME"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                    else if (pick == 3) { printf("WORK\n"); ch = "WORK"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; }}
                    else { printf("TBD"); }
                    printf("Number : ");
		    scanf("%s", patient[pos].phone.number);
                    printf("\nPatient record updated!\n");
                    break;
		case 0: printf("\n"); break;
                }
                i = max;
                //suspend();
            
            }
            return;
        }
    }
    printf("*** No Records Found ***");
    suspend();
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void removePatient(struct Patient patient[], int max) {
    int i = 0, num = 0, pos = -1;
    printf("Enter the patient number: ");
    scanf("%d", &num);
    //SET THIER PAT NUM TO 0 AND STORE THE POSITION
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == num) {
            pos = i;
            i = max;
        }
    }
    if (pos == -1) {
        printf("\nERROR: Patient record not found!\n\n");
    }
    else{
    printf("\nName  : %s\n", patient[pos].name);
    printf("Number: 0%d\n", num);
    printf("Phone : ");
    printf("(");
    int k = 0;
    for (k = 0; k < 10; k++) { printf("%c", patient[pos].phone.number[k]); if (k == 2) { printf(")"); } if (k == 5) { printf("-"); } }
    printf(" (%s)", patient[pos].phone.description);
    char selection;
    printf("\n\nAre you sure you want to remove this patient record? (y/n): ");
    selection = inputCharOption("yn");
    //putchar('\n');
    if (selection == 'n')
    {
        printf("Operation aborted.\n\n");
        return;
    }
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == num) {
            //printf("%d num is \nand patient num is %d \n", num, patient[i].patientNumber);
            patient[i].patientNumber = 0;
            pos = i;
            i = max;
        }
    }
    printf("Patient record has been removed!\n\n");
    

    //PUSH EVERYTHING BACK ONE SPOT UNLESS THE FIRST SPOT
    for (i = max-1; i < pos; i++) {
        if (pos) {
            ;
        }
        else{
        patient[i] = patient[i - 1];
        }
    }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int num = 0, i = 0, count = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    i = 0;
    printf("\nSearch by patient number: ");
    scanf("%d", &num);
    putchar('\n');
    i = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == num) {
            displayPatientData(&patient[i], FMT_FORM);
 	    printf("\n");
	    suspend();
	    //printf("\n");
	    return;
        }
    }
    printf("*** No records found ***\n\n");

    suspend();
    //printf("\n");
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    char num[PHONE_LEN + 1]; int i = 0; int exist = 0;
    //for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    i = 0;
    printf("\nSearch by phone number: "); 
    scanf("%s", num);
    putchar('\n'); displayPatientTableHeader(); //printf("\n"); 
    i = 0;
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, num) == 0) {
            displayPatientData(&patient[i], max);
            //suspend();
	    exist++;
            //return;
        }
    }
    if(exist >= 1){ printf("\n"); suspend(); return; }
    printf("\n*** No records found ***\n\n");
    suspend();
    return;

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int nextPatientNumber(const struct Patient patient[], int max) {
    int i = 0, pos = 0, count = 0, pos2 = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    // cant do bubble sort because it's a 'const' structure :/
    for (i = 0; i < count - 1; i++) {
        if (patient[i].patientNumber > patient[i + 1].patientNumber) {
            pos = i;
        }
    }
    for (i = 0; i < count - 1; i++) {
        if ((patient[i].patientNumber > patient[i + 1].patientNumber) && i != pos) {
            pos2 = i;
        }
    }
    return pos2;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) {
    int i = 0, pos = 0, count = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }

    for (i = 0; i < count; i++) {
        if (patient[i].patientNumber == patientNumber) {
            pos = i;
            i = max;
            return pos;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPatient(struct Patient* patient) {
    printf("Number: ");
    scanf("%d", &patient->patientNumber); 
    printf(""
        "Name :");
    inputCString(patient->name, 1, NAME_LEN);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPhoneData(struct Phone* phone) {
    int i = 0;
    printf("\n"
        "Phone Information\n"
        "---------------- -\n"
        "How will the patient like to be contacted ?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    int choice = 0;
    scanf("%d", &choice);
    char* ch;
    switch (choice) {
    case 1:ch = "CELL"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { phone->description[i] = ch[i]; } printf("\nNumber: "); scanf("%s", phone->number); break;
    case 2:ch = "HOME"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { phone->description[i] = ch[i]; } printf("\nNumber: "); scanf("%s", phone->number); break;
    case 3:ch = "WORK"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { phone->description[i] = ch[i]; } printf("\nNumber: "); scanf("%s", phone->number); break;
    case 4:break;
    default: while (choice < 1 || choice > 4) { printf("Invalid choice... "); scanf("%d", &choice); }; break;
    }
    
}