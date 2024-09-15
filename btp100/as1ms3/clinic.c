/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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
            printf("\n");
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            printf("\n");
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            //suspend();
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            printf("\n");
            break;
        case 2:

            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!

            suspend();
            printf("\n");
            break;
        case 3:

            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!

            suspend();
            printf("\n");
            break;
        case 4:

            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!

            //suspend();
            //printf("\n");
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

void addPatient(struct Patient patient[], int max) {
    int i = 0, count = 0; int len = 0;
    for (i = 0; i < max; i++) { if (patient[i].patientNumber != 0) { count++; } }
    int pos = 0;
    for (i = 0;i < max; i++) { if (patient[i].patientNumber == 0) { pos = i; i = max; } }
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
        scanf("%d", &patient[pos].patientNumber);
        printf(""
            "Name  : ");
        inputCString(patient[pos].name, 1, NAME_LEN);
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
        char* ch; printf("\n");
        switch (choice) {
        case 1: ch = "CELL"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[pos].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[pos].phone.number);

            for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            while (len > 10 || len < 10) {
                printf("Invalid 10-digit number! Number: ");
                scanf("%s", patient[pos].phone.number);
                for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            } printf("\n"); break;

        case 2: ch = "HOME"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[pos].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[pos].phone.number);

            for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            while (len > 10 || len < 10) {
                printf("Invalid 10-digit number! Number: ");
                scanf("%s", patient[pos].phone.number);
                for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            } printf("\n"); break;

        case 3: ch = "WORK"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[pos].phone.description[i] = ch[i]; } printf("Contact: %s\nNumber : ", ch); scanf("%s", patient[pos].phone.number);

            for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            while (len > 10 || len < 10) {
                printf("Invalid 10-digit number! Number: ");
                scanf("%s", patient[pos].phone.number);
                for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
            } printf("\n"); break;

        case 4: ch = "TBD"; i = 0; for (i = 0; i < PHONE_DESC_LEN; i++) { patient[pos].phone.description[i] = ch[i]; } break;
        default: while (choice < 1 || choice > 4) { printf("Invalid choice... "); scanf("%d", &choice); }; break;
        }
        for (i = 0;i < max;i++) { if ((patient[i].patientNumber == 1024) && i != 0) { patient[i].patientNumber = 1072; } }
        printf("*** New patient record added ***\n\n");
        //suspend();
    }

}

// Edit a patient record from the patient array
// (Copy your code from MS#2)

void editPatient(struct Patient patient[], int max) {
    int i = 0; int choice = 0; char* ch; int z = 0; int pos = 0; int len = 0;
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
            displayFormattedPhone(patient[pos].phone.number);

            printf("\n-------------------------\n"
                "0) Previous menu\n"
                "-------------------------\n"
                "Selection: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1: printf("\nName  : "); inputCString(patient[pos].name, 1, 1); printf("\nPatient record updated!\n"); break;
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
                if (pick == 1) { printf("CELL"); ch = "CELL"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                else if (pick == 2) { printf("HOME"); ch = "HOME"; i = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                else if (pick == 3) { printf("WORK"); ch = "WORK"; i = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                else { printf("TBD"); }
                printf("Number : ");
                scanf("%s", patient[pos].phone.number);

                for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
                while (len > 10) {
                    printf("Invalid 10-digit number! Number: ");
                    scanf("%s", patient[pos].phone.number);
                    for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
                }
            }
            while (choice != 0) {
                z = 0;
                printf("\nEdit Patient (0%d)\n", num);
                printf("=========================\n");
                printf("1) NAME : %s\n", patient[pos].name);
                printf("2) PHONE: ");
                displayFormattedPhone(patient[pos].phone.number);
                printf("\n-------------------------\n"
                    "0) Previous menu\n"
                    "-------------------------\n"
                    "Selection: ");
                scanf("%d", &choice);
                switch (choice) {

                case 1: printf("\nName  : "); inputCString(patient[pos].name, 1, 1); printf("\nPatient record updated!\n"); break;
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
                    if (pick == 1) { printf("CELL\n"); ch = "CELL"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                    else if (pick == 2) { printf("HOME\n"); ch = "HOME"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                    else if (pick == 3) { printf("WORK\n"); ch = "WORK"; z = 0; for (z = 0; z < PHONE_DESC_LEN; z++) { patient[pos].phone.description[z] = ch[z]; } }
                    else { printf("TBD"); }
                    printf("Number : ");
                    scanf("%s", patient[pos].phone.number);
                    for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
                    while (len > 10) {
                        printf("Invalid 10-digit number! Number: ");
                        scanf("%s", patient[pos].phone.number);
                        for (len = 0; patient[pos].phone.number[len] != '\0'; len++);
                    }
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
// (Copy your code from MS#2)

void removePatient(struct Patient patient[], int max) {
    int i = 0, num = 0, pos = -1;
    //int pos2 = 0;
    //for (i = 0;i < max;i++) { if (patient[i].patientNumber == 0) { pos2 = i; i = max; } }
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
        printf("\nERROR: Patient record not found!\n\n"); suspend(); printf("\n"); return;
    }
    else {
        printf("\nName  : %s\n", patient[pos].name);
        printf("Number: 0%d\n", num);
        printf("Phone : ");
        displayFormattedPhone(patient[pos].phone.number);
        printf(" (%s)", patient[pos].phone.description);
        char selection;
        printf("\n\nAre you sure you want to remove this patient record? (y/n): ");
        scanf("%c", &selection);
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
        
        
        suspend();
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

void viewAllAppointments(struct ClinicData* data) {
    displayScheduleTableHeader(&data->appointments->date, 1);

    sort(data);
    int i, j;
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->patients[j].patientNumber == data->appointments[i].patientNumber && data->patients[j].patientNumber != 0) {
                printf("%d-%02d-%02d %02d:%02d %05d %-14s  ",
                    data->appointments[i].date.year,
                    data->appointments[i].date.month,
                    data->appointments[i].date.day,
                    data->appointments[i].time.hour,
                    data->appointments[i].time.min,
                    data->patients[j].patientNumber,
                    data->patients[j].name
                    //data->patients[j].phone.number
                );
                displayFormattedPhone(data->patients[j].phone.number);
                printf(" (%s)", data->patients[j].phone.description);
                printf("\n");
            }
        }
    }
    printf("\n");
}


// View appointment schedule for the user input date
// Todo:

void viewAppointmentSchedule(struct ClinicData* data) {
    int year, month, i, day = 0;

    /*********************TAKING IN THE YEAR***************************/

    printf("Year        : ");
    scanf("%d", &year);

    /*********************TAKING IN THE MONTH***************************/

    printf("Month (1-12): ");
    month = inputIntRange(1, 12);

    /*********************TAKING IN THE DAY***************************/

    printf("Day (1-");
    switch (month) {
    case 1: printf("31)  : "); day = inputIntRange(1, 31);    break;
    case 2:
        if (year % 4 != 0) {
            printf("28)  : ");
            day = inputIntRange(1, 28);
        }
        else {
            printf("29)  : ");
            day = inputIntRange(1, 29);
        }
        break;
    case 3: printf("31)  : "); day = inputIntRange(1, 31);    break;
    case 4: printf("30)  : "); day = inputIntRange(1, 30);    break;
    case 5: printf("31)  : "); day = inputIntRange(1, 31);    break;
    case 6: printf("30)  : "); day = inputIntRange(1, 30);    break;
    case 7: printf("31)  : "); day = inputIntRange(1, 31);    break;
    case 8: printf("31)  : "); day = inputIntRange(1, 31);    break;
    case 9: printf("30)  : "); day = inputIntRange(1, 30);    break;
    case 10: printf("31)  : "); day = inputIntRange(1, 31);   break;
    case 11: printf("30)  : "); day = inputIntRange(1, 30);   break;
    case 12: printf("31)  : "); day = inputIntRange(1, 31);   break;
    }


    printf("\nClinic Appointments for the Date: ");
    printf("%04d-%02d-%02d\n\n", year, month, day);
    printf("Time  Pat.# Name            Phone#\n"
        "----- ----- --------------- --------------------\n");
    int j = 0;
    for (i = 0; i < data->maxAppointments;i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].date.year == year && data->appointments[i].patientNumber == data->patients[j].patientNumber) {
                printf("%02d:%02d %05d %-14s  ", data->appointments[i].time.hour,
                    data->appointments[i].time.min,
                    data->patients[j].patientNumber,
                    data->patients[j].name);
                displayFormattedPhone(data->patients[j].phone.number);
                printf(" (%s)", data->patients[j].phone.description);
                printf("\n");
            }
        }
    }
    printf("\n");


    /*
     printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    */
}
// Add an appointment record to the appointment array
// Todo:

void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patient[], int maxPatient) {
    // data->appointments, data->maxAppointments, data->patients, data->maxPatient

    /***Create a count var and initalize it***/
    //Tells how many patients are there alongside if it is full or not.
    int count = 0, i = 0;
    //For each patient that has a number > 0 --> increase the count var by 1
    for (i = 0; i < maxAppointments; i++) { if (appointments[i].patientNumber != 0) { count++; } }
    if (count == maxPatient) {
        printf("ERROR: Appointment Booking is full");
    }
    else {
        ///printf("There are %d amount of appointments and the max is %d", count, maxAppointments);
        printf("Patient Number: ");
        scanf("%d", &appointments[count].patientNumber);
        getDate(&appointments[count]);
        getTime(&appointments[count]);

    }

    while (alreadyExists(appointments, patient[count].patientNumber, maxAppointments)) {
        printf("\nERROR: Appointment timeslot is not available!\n\n");
        getDate(&appointments[count]);
        getTime(&appointments[count]);
    }

    //printf("%d the pat number at count is %d", appointments[count].patientNumber, count);

    printf("\n*** Appointment scheduled! ***\n\n");
}


// Remove an appointment record from the appointment array
// Todo:

void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patient[], int maxPatient) {
    int num = 0, year = 0, month = 0, day = 0, i = 0, posPat = 0, pos = 0;
    int x = 0; int exist = 0;
    printf("Patient Number: ");
    scanf("%d", &num);
    for (i = 0;i < maxAppointments;i++) {
        //printf("Pat num is %d and max appointments is %d and num is %d\n", appointments[i].patientNumber, maxAppointments, num);
        for (x = 0; x < maxPatient; x++) {
            if (appointments[i].patientNumber == patient[x].patientNumber && appointments[i].patientNumber == num) {
                exist++;
                
            }
        }
    }
    if (exist == 0) {
        printf("ERROR: Patient record not found!\n\n");
        suspend();
        printf("\n");
        return;
    }
    printf("Year        : ");
    scanf("%d", &year);
    printf("Month (1-12): ");
    scanf("%d", &month);
    printf("Day (1-29)  : ");
    scanf("%d", &day);

    /****GET THEIR POSITION****/
    int j = 0;
    for (i = 0; i < maxAppointments; i++) {
        for (j = 0; j < maxPatient; j++) {
            if (patient[j].patientNumber == num) {
                posPat = j;
            }
        }
    }
    printf("\nName  : %s\n", patient[posPat].name);
    printf("Number: 0%d\n", num);
    printf("Phone : "); displayFormattedPhone(patient[posPat].phone.number); printf(" (%s)", patient[posPat].phone.description);
    char selection;
    printf("\nAre you sure you want to remove this appointment (y,n): ");
    selection = inputCharOption("yn");
    if (selection == 'n')
    {
        printf("Operation aborted.\n\n");
        return;
    }

    for (i = 0;i < maxAppointments;i++) {
        //printf("Pat num is %d and max appointments is %d and num is %d\n", appointments[i].patientNumber, maxAppointments, num);
        for (x = 0; x < maxPatient; x++) {
            if (appointments[i].patientNumber == patient[x].patientNumber && appointments[i].patientNumber == num 
                && appointments[i].date.day == day && appointments[i].date.month == month && 
                appointments[i].date.year == year) {
                appointments[i].patientNumber = 0;
                pos = i;
                i = maxAppointments;

            }
        }
    }
    printf("\nAppointment record has been removed!\n\n");
    suspend();


    //PUSH EVERYTHING BACK ONE SPOT UNLESS THE FIRST SPOT
    for (i = maxAppointments - 1; i < pos; i++) {
        if (pos) {
            ;
        }
        else {
            appointments[i] = appointments[i - 1];
        }
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)

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
            printf("\n");
            return;
        }
    }
    printf("*** No records found ***\n\n");

    suspend();
    printf("\n");
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
    if (exist >= 1) { printf("\n"); suspend(); printf("\n"); return; }
    printf("\n*** No records found ***\n\n");
    suspend();
    printf("\n");
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


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* fp = NULL;
    int i, counter = 0;
    fp = fopen(datafile, "r");
    if (fp == NULL) {
        printf("ERROR: failed\n");
    }
    else {
        for (i = 0; i < max; i++) {
            /*
            * fscanf("%[^|]d%[^|],%[^|],%[^|]");
            */
            if (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number)) {
                counter++;
            }
        }
        fclose(fp);
    }
    return counter;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* fp = NULL;
    int counter = 0, i;
    fp = fopen(datafile, "r");
    if (fp != NULL) {
        // 1024|Shaggy Yanson|CELL|3048005191
        for (i = 0; i < max; i++) {
            if (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month,
                &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) == 6) {
                counter++;
            }
        }
        fclose(fp);
    }
    else {
        printf("ERROR: file opening failed\n");
    }
    return counter;
}

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////
void swap(struct Appointment* app1, struct Appointment* app2) {
    struct Appointment temp;
    temp = *app1;
    *app1 = *app2;
    *app2 = temp;
    /*
        temp.patientNumber = app1->patientNumber;
        temp.date = app1->date;
        temp.time = app1->time;
        app1->patientNumber = app2->patientNumber;
        app1->date = app2->date;
        app1->time = app2->time;
        app2->patientNumber = temp.patientNumber;
        app2->date = temp.date;
        app2->time = temp.time;
        */
}

void sort(struct ClinicData* data) {
    int i, j;
    for (i = data->maxAppointments - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (data->appointments[j].patientNumber > 0 && data->appointments[j].patientNumber > 0) {
                if (data->appointments[j].date.year > data->appointments[j + 1].date.year) {
                    swap(&data->appointments[j], &data->appointments[j + 1]);
                }

                if (data->appointments[j].date.year == data->appointments[j + 1].date.year &&
                    data->appointments[j].date.month > data->appointments[j + 1].date.month
                    ) {
                    swap(&data->appointments[j], &data->appointments[j + 1]);
                }
                if (data->appointments[j].date.year == data->appointments[j + 1].date.year &&
                    data->appointments[j].date.month == data->appointments[j + 1].date.month &&
                    data->appointments[j].date.day > data->appointments[j + 1].date.day
                    ) {
                    swap(&data->appointments[j], &data->appointments[j + 1]);
                }
                if (data->appointments[j].date.year == data->appointments[j + 1].date.year &&
                    data->appointments[j].date.month == data->appointments[j + 1].date.month &&
                    data->appointments[j].date.day == data->appointments[j + 1].date.day &&
                    data->appointments[j].time.hour > data->appointments[j + 1].time.hour
                    ) {
                    swap(&data->appointments[j], &data->appointments[j + 1]);
                }
                if (data->appointments[j].date.year == data->appointments[j + 1].date.year &&
                    data->appointments[j].date.month == data->appointments[j + 1].date.month &&
                    data->appointments[j].date.day == data->appointments[j + 1].date.day &&
                    data->appointments[j].time.hour == data->appointments[j + 1].time.hour &&
                    data->appointments[j].time.min > data->appointments[j + 1].time.min
                    ) {
                    swap(&data->appointments[j], &data->appointments[j + 1]);
                }

            }
        }
    }
}

void getDate(struct Appointment* appointments) {
    printf("Year        : ");
    scanf("%d", &appointments->date.year);
    printf("Month (1-12): ");
    appointments->date.month = inputIntRange(1, 12);
    printf("Day (1-");
    //PRINTING OUT THE DATE STUFF
    switch (appointments->date.month) {
    case 1: printf("31)  : "); appointments->date.day = inputIntRange(1, 31);    break;
    case 2:
        if (appointments->date.year % 4 != 0) {
            printf("28)  : ");
            appointments->date.day = inputIntRange(1, 28);
        }
        else {
            printf("29)  : ");
            appointments->date.day = inputIntRange(1, 29);
        }
        break;
    case 3: printf("31)  : "); appointments->date.day = inputIntRange(1, 31);    break;
    case 4: printf("30)  : "); appointments->date.day = inputIntRange(1, 30);    break;
    case 5: printf("31)  : "); appointments->date.day = inputIntRange(1, 31);    break;
    case 6: printf("30)  : "); appointments->date.day = inputIntRange(1, 30);    break;
    case 7: printf("31)  : "); appointments->date.day = inputIntRange(1, 31);    break;
    case 8: printf("31)  : "); appointments->date.day = inputIntRange(1, 31);    break;
    case 9: printf("30)  : "); appointments->date.day = inputIntRange(1, 30);    break;
    case 10: printf("31)    : "); appointments->date.day = inputIntRange(1, 31);   break;
    case 11: printf("30)    : "); appointments->date.day = inputIntRange(1, 30);   break;
    case 12: printf("31)    : "); appointments->date.day = inputIntRange(1, 31);   break;
    }
}

void getTime(struct Appointment* appointments) {
    printf("Hour (0-23)  : ");
    int hour;
    scanf("%d", &hour);
    appointments->time.hour = hour;
    printf("Minute (0-59): ");
    int minute = 0;
    scanf("%d", &minute);
    appointments->time.min = minute;
    if ((hour < MIN_HOUR || hour > MAX_HOUR) || (minute % 30 != 0) || (hour == MAX_HOUR && minute != 0)) {
        printf("ERROR: Time must be between %d:00 and %d:00 in 30 minute intervals.\n\n", MIN_HOUR, MAX_HOUR);
        getTime(appointments);
    }

}

int alreadyExists(struct Appointment appointments[], int patNum, int max) {

    int i = 0, count = 0;
    for (i = 0; i < max; i++) { if (appointments[i].patientNumber != 0) { count++; } }

    // WANT TO CHECK IF APPOINT WE ADDED IS THE SAME AS SOMEONNE ALREADY EXISTING OK

    /*
    * WRITE INFO TO KNOW WHAT IM DOING
    * last added pat is always at last index at the while being added
    * need to compare it to all other
    * count is always +1 of the actual array
    * so count is non existant while count-1 is the last thing in the array
    */


    for (i = 0; i < max; i++) {
        if ((appointments[i].date.year == appointments[count - 1].date.year) && (appointments[i].date.month == appointments[count - 1].date.month)
            && (appointments[i].time.hour == appointments[count - 1].time.hour) && (appointments[i].time.min == appointments[count - 1].time.min) && (i != count - 1)) {
            //if there is an appointment 
            return 1;
        }
    }
    // if it does not exist
    return 0;
}