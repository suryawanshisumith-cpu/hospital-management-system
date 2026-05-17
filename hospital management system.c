#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= PATIENT STRUCTURE ================= */

struct Patient
{
    int id;
    char name[50];
    char gender[10];
    int age;
    char disease[50];

    char doctor[50];

    int roomNo;

    char medicine[50];
    int medicineRate;
    int medicineQty;

    int consultationFee;

    int bedDays;
    int bedCharge;

    int totalBill;
};

/* ================= DOCTOR STRUCTURE ================= */

struct Doctor
{
    int id;
    char name[50];
    char specialization[50];
};

/* ================= APPOINTMENT STRUCTURE ================= */

struct Appointment
{
    int patientId;
    int doctorId;
    char date[20];
};

/* ================= EMERGENCY QUEUE ================= */

struct EmergencyPatient
{
    int id;
    char name[50];
    char disease[50];
};

struct EmergencyPatient queue[100];

int front = -1;
int rear = -1;

/* ================= BED SYSTEM ================= */

int totalBeds = 10;
int availableBeds = 10;

/* ================= LOGIN SYSTEM ================= */

void login()
{
    int role;
    int password;

    printf("\n========== LOGIN SYSTEM ==========\n");

    printf("\n1. Admin");
    printf("\n2. Doctor");
    printf("\n3. Receptionist");

    printf("\n\nEnter Role: ");
    scanf("%d", &role);

    printf("Enter Password: ");
    scanf("%d", &password);

    if(role == 1 && password == 1111)
    {
        printf("\nAdmin Login Successful!\n");
    }
    else if(role == 2 && password == 2222)
    {
        printf("\nDoctor Login Successful!\n");
    }
    else if(role == 3 && password == 3333)
    {
        printf("\nReceptionist Login Successful!\n");
    }
    else
    {
        printf("\nInvalid Login!\n");
        exit(0);
    }
}

/* ================= AUTO DOCTOR ASSIGNMENT ================= */

void assignDoctor(char doctor[])
{
    int x;

    printf("\n1. MBBS General");
    printf("\n2. Ortho");
    printf("\n3. Cardio");

    printf("\nEnter Disease Choice: ");
    scanf("%d", &x);

    if(x == 1)
    {
        strcpy(doctor, "Dr.Sumit");
    }
    else if(x == 2)
    {
        strcpy(doctor, "Dr.Ritesh");
    }
    else if(x == 3)
    {
        strcpy(doctor, "Dr.Ajay");
    }
    else
    {
        strcpy(doctor, "NotAssigned");
    }

    printf("\nAssigned Doctor: %s\n", doctor);
}

/* ================= ADD PATIENT ================= */

void addPatient()
{
    FILE *fp;

    struct Patient p;

    int medicineCost;

    if(availableBeds == 0)
    {
        printf("\nNo Beds Available!\n");
        return;
    }

    fp = fopen("patients.txt", "a");

    if(fp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf("%s", p.name);

    printf("Enter Gender: ");
    scanf("%s", p.gender);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Disease: ");
    scanf("%s", p.disease);

    assignDoctor(p.doctor);

    printf("Enter Room Number: ");
    scanf("%d", &p.roomNo);

    printf("Enter Medicine Name: ");
    scanf("%s", p.medicine);

    printf("Enter Medicine Rate: ");
    scanf("%d", &p.medicineRate);

    printf("Enter Medicine Quantity: ");
    scanf("%d", &p.medicineQty);

    printf("Enter Consultation Fee: ");
    scanf("%d", &p.consultationFee);

    printf("Enter Bed Days: ");
    scanf("%d", &p.bedDays);

    if(p.bedDays == 1)
    {
        p.bedCharge = 1000;
    }
    else if(p.bedDays == 2)
    {
        p.bedCharge = 1500;
    }
    else if(p.bedDays >= 3)
    {
        p.bedCharge = 2000;
    }
    else
    {
        p.bedCharge = 0;
    }

    medicineCost =
        p.medicineRate * p.medicineQty;

    p.totalBill =
        medicineCost +
        p.consultationFee +
        p.bedCharge;

    fprintf(fp,
            "%d %s %s %d %s %s %d %s %d %d %d %d %d\n",

            p.id,
            p.name,
            p.gender,
            p.age,
            p.disease,

            p.doctor,
            p.roomNo,

            p.medicine,
            p.medicineRate,
            p.medicineQty,

            p.consultationFee,
            p.bedCharge,
            p.totalBill);

    fclose(fp);

    availableBeds--;

    printf("\nPatient Added Successfully!\n");

    printf("\n========== BILL ==========\n");

    printf("Medicine Cost: %d\n", medicineCost);

    printf("Consultation Fee: %d\n", p.consultationFee);

    printf("Bed Charge: %d\n", p.bedCharge);

    printf("TOTAL BILL: %d\n", p.totalBill);

    printf("\nRemaining Beds: %d\n", availableBeds);
}

/* ================= DISPLAY PATIENTS ================= */

void displayPatients()
{
    FILE *fp;

    struct Patient p;

    int check;

    fp = fopen("patients.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Patient Records Found!\n");
        return;
    }

    printf("\n========== PATIENT RECORDS ==========\n");

    while(1)
    {
        check = fscanf(fp,
                       "%d %s %s %d %s %s %d %s %d %d %d %d %d",

                       &p.id,
                       p.name,
                       p.gender,
                       &p.age,
                       p.disease,
                       p.doctor,
                       &p.roomNo,
                       p.medicine,
                       &p.medicineRate,
                       &p.medicineQty,
                       &p.consultationFee,
                       &p.bedCharge,
                       &p.totalBill);

        if(check != 13)
        {
            break;
        }

        printf("\nID: %d", p.id);

        printf("\nName: %s", p.name);

        printf("\nGender: %s", p.gender);

        printf("\nAge: %d", p.age);

        printf("\nDisease: %s", p.disease);

        printf("\nDoctor: %s", p.doctor);

        printf("\nRoom Number: %d", p.roomNo);

        printf("\nMedicine: %s", p.medicine);

        printf("\nTotal Bill: %d", p.totalBill);

        printf("\n-----------------------------\n");
    }

    fclose(fp);
}

/* ================= SEARCH PATIENT ================= */

void searchPatient()
{
    FILE *fp;

    struct Patient p;

    int id;
    int found = 0;

    int check;

    fp = fopen("patients.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &id);

    while(1)
    {
        check = fscanf(fp,
                       "%d %s %s %d %s %s %d %s %d %d %d %d %d",

                       &p.id,
                       p.name,
                       p.gender,
                       &p.age,
                       p.disease,
                       p.doctor,
                       &p.roomNo,
                       p.medicine,
                       &p.medicineRate,
                       &p.medicineQty,
                       &p.consultationFee,
                       &p.bedCharge,
                       &p.totalBill);

        if(check != 13)
        {
            break;
        }

        if(p.id == id)
        {
            found = 1;

            printf("\nPatient Found!\n");

            printf("ID: %d\n", p.id);

            printf("Name: %s\n", p.name);

            printf("Disease: %s\n", p.disease);

            printf("Doctor: %s\n", p.doctor);

            printf("Room Number: %d\n", p.roomNo);

            printf("Total Bill: %d\n", p.totalBill);
        }
    }

    if(found == 0)
    {
        printf("\nPatient Not Found!\n");
    }

    fclose(fp);
}

/* ================= DISCHARGE PATIENT ================= */

void dischargePatient()
{
    FILE *fp, *temp;

    struct Patient p;

    int id;
    int found = 0;

    int check;

    fp = fopen("patients.txt", "r");
    temp = fopen("temp.txt", "w");

    if(fp == NULL)
    {
        printf("\nNo Patient Records Found!\n");
        return;
    }

    printf("\nEnter Patient ID to Discharge: ");
    scanf("%d", &id);

    while(1)
    {
        check = fscanf(fp,
                       "%d %s %s %d %s %s %d %s %d %d %d %d %d",

                       &p.id,
                       p.name,
                       p.gender,
                       &p.age,
                       p.disease,
                       p.doctor,
                       &p.roomNo,
                       p.medicine,
                       &p.medicineRate,
                       &p.medicineQty,
                       &p.consultationFee,
                       &p.bedCharge,
                       &p.totalBill);

        if(check != 13)
        {
            break;
        }

        if(p.id == id)
        {
            found = 1;

            printf("\n========== DISCHARGE SUMMARY ==========\n");

            printf("Patient Name: %s\n", p.name);

            printf("Disease: %s\n", p.disease);

            printf("Doctor: %s\n", p.doctor);

            printf("Room Number: %d\n", p.roomNo);

            printf("Final Bill: %d\n", p.totalBill);

            availableBeds++;
        }
        else
        {
            fprintf(temp,
                    "%d %s %s %d %s %s %d %s %d %d %d %d %d\n",

                    p.id,
                    p.name,
                    p.gender,
                    p.age,
                    p.disease,
                    p.doctor,
                    p.roomNo,
                    p.medicine,
                    p.medicineRate,
                    p.medicineQty,
                    p.consultationFee,
                    p.bedCharge,
                    p.totalBill);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if(found)
    {
        printf("\nPatient Discharged Successfully!\n");

        printf("Available Beds: %d\n", availableBeds);
    }
    else
    {
        printf("\nPatient Not Found!\n");
    }
}
/* ================= BED AVAILABILITY ================= */

void bedAvailability()
{
    printf("\n========== BED STATUS ==========\n");

    printf("Total Beds: %d\n", totalBeds);

    printf("Available Beds: %d\n", availableBeds);

    printf("Occupied Beds: %d\n", totalBeds - availableBeds);
}

/* ================= ADD DOCTOR ================= */

void addDoctor()
{
    FILE *fp;

    struct Doctor d;

    fp = fopen("doctors.txt", "a");

    printf("\nEnter Doctor ID: ");
    scanf("%d", &d.id);

    printf("Enter Doctor Name: ");
    scanf("%s", d.name);

    printf("Enter Specialization: ");
    scanf("%s", d.specialization);

    fprintf(fp,
            "%d %s %s\n",

            d.id,
            d.name,
            d.specialization);

    fclose(fp);

    printf("\nDoctor Added Successfully!\n");
}

/* ================= DISPLAY DOCTORS ================= */

void displayDoctors()
{
    FILE *fp;

    struct Doctor d;

    fp = fopen("doctors.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Doctor Records Found!\n");
        return;
    }

    printf("\n========== DOCTOR RECORDS ==========\n");

    while(fscanf(fp,
                 "%d %s %s",

                 &d.id,
                 d.name,
                 d.specialization) != EOF)
    {
        printf("\nDoctor ID: %d", d.id);

        printf("\nDoctor Name: %s", d.name);

        printf("\nSpecialization: %s\n", d.specialization);
    }

    fclose(fp);
}

/* ================= BOOK APPOINTMENT ================= */

void bookAppointment()
{
    FILE *fp;

    struct Appointment a;

    fp = fopen("appointments.txt", "a");

    printf("\nEnter Patient ID: ");
    scanf("%d", &a.patientId);

    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctorId);

    printf("Enter Appointment Date: ");
    scanf("%s", a.date);

    fprintf(fp,
            "%d %d %s\n",

            a.patientId,
            a.doctorId,
            a.date);

    fclose(fp);

    printf("\nAppointment Booked Successfully!\n");
}

/* ================= DISPLAY APPOINTMENTS ================= */

void displayAppointments()
{
    FILE *fp;

    struct Appointment a;

    fp = fopen("appointments.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Appointment Records Found!\n");
        return;
    }

    printf("\n========== APPOINTMENT RECORDS ==========\n");

    while(fscanf(fp,
                 "%d %d %s",

                 &a.patientId,
                 &a.doctorId,
                 a.date) != EOF)
    {
        printf("\nPatient ID: %d", a.patientId);

        printf("\nDoctor ID: %d", a.doctorId);

        printf("\nDate: %s\n", a.date);
    }

    fclose(fp);
}

/* ================= EMERGENCY ENQUEUE ================= */

void enqueue()
{
    if(rear == 99)
    {
        printf("\nQueue Overflow!\n");
        return;
    }

    if(front == -1)
    {
        front = 0;
    }

    rear++;

    printf("\nEnter Emergency Patient ID: ");
    scanf("%d", &queue[rear].id);

    printf("Enter Patient Name: ");
    scanf("%s", queue[rear].name);

    printf("Enter Emergency Disease: ");
    scanf("%s", queue[rear].disease);

    printf("\nEmergency Patient Added!\n");
}

/* ================= EMERGENCY DEQUEUE ================= */

void dequeue()
{
    if(front == -1 || front > rear)
    {
        printf("\nNo Emergency Patients!\n");
        return;
    }

    printf("\nTreating Emergency Patient\n");

    printf("ID: %d\n", queue[front].id);

    printf("Name: %s\n", queue[front].name);

    printf("Disease: %s\n", queue[front].disease);

    front++;

    if(front > rear)
    {
        front = rear = -1;
    }
}

/* ================= DISPLAY EMERGENCY QUEUE ================= */

void displayQueue()
{
    int i;

    if(front == -1)
    {
        printf("\nNo Emergency Patients!\n");
        return;
    }

    printf("\n========== EMERGENCY QUEUE ==========\n");

    for(i = front; i <= rear; i++)
    {
        printf("\nPatient %d\n", i - front + 1);

        printf("ID: %d\n", queue[i].id);

        printf("Name: %s\n", queue[i].name);

        printf("Disease: %s\n", queue[i].disease);
    }
}

/* ================= MAIN FUNCTION ================= */

int main()
{
    int choice;

    login();

    do
    {
        printf("\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n");

        printf("\n1. Add Patient");
        printf("\n2. Display Patients");
        printf("\n3. Search Patient");
        printf("\n4. Discharge Patient");
        printf("\n5. Bed Availability");

        printf("\n6. Add Doctor");
        printf("\n7. Display Doctors");

        printf("\n8. Book Appointment");
        printf("\n9. Display Appointments");

        printf("\n10. Add Emergency Patient");
        printf("\n11. Treat Emergency Patient");
        printf("\n12. Display Emergency Queue");

        printf("\n13. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                dischargePatient();
                break;

            case 5:
                bedAvailability();
                break;

            case 6:
                addDoctor();
                break;

            case 7:
                displayDoctors();
                break;

            case 8:
                bookAppointment();
                break;

            case 9:
                displayAppointments();
                break;

            case 10:
                enqueue();
                break;

            case 11:
                dequeue();
                break;

            case 12:
                displayQueue();
                break;

            case 13:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 13);

    return 0;
}