/*********************************************************************************************************

This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts 
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The 
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.

<Mauries A. Lopez>, DLSU ID# <12177539>

*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char String99[100];
typedef char String30[31];

typedef struct
{
    int nMonth;
    int nDay;
    int nYear;

}Date;

typedef struct
{
    String30 tripNumber;
    String30 passengerFirstName;
    String30 passengerLastName;
    String99 embarkPoint;
    int idNum;
    int prioNum;
    Date date;
    String99 dropOffPoint;

}Passenger;

typedef struct
{

    String30 userTripNumber;
    String30 userFirstName;
    String30 userLastName;
    String99 userEmbarkPoint;
    int userIdNum;
    int userPrioNum;
    Date userDate;
    String99 userDropOffPoint;

}User;

typedef struct
{
    String30 loadTripNumber;
    String30 loadFirstName;
    String30 loadLastName;
    String99 loadEmbarkPoint;
    int loadIdNum;
    int loadPrioNum;
    Date loadDate;
    String99 loadDropOffPoint;

}Load;


#include "lopezM_Passenger.c" // C File for all Passenger Features
#include "lopezM_ArrowExpressPersonel.c" // C File for all ArrowExpressPersonal Features

void displayMenu()
{
    printf("========================================================\n\n");
    printf("[ARROWS EXPRESS LINE EMBARKATION SYSTEM]\n\n");
    printf("[1] Passenger Features\n");
    printf("[2] Arrow Express Personnel Features\n");
    printf("[3] Exit\n");
    printf("\n========================================================\n");
    
}

/*  
    checkValidTripNumber is a function that checks the user input in the function if its valid trip number or not.

    @param userTripNumber = It is use for getting the user input for the trip number
    @param validTripNumber = The array of valid trip numbers
    @return = None

    Pre-condition = None
*/
void checkValidTripNumber ( String30 userTripNumber, 
                            String30 validTripNumber[20] )
{
    int i; //Variable for loop
    
    int nCheck = 0; //Variable to check if the user inputted trip number is valid or invalid

    do
    {
        printf("Enter Trip Number: ");
        scanf(" %s", userTripNumber);
        while ((getchar()) != '\n');

        for ( i = 0; i < 20; i++ ) //Loop to check if the user inputted trip number is valid or invalid
        {
            if ( strcmpi(validTripNumber[i], userTripNumber) == 0 ) //Compares all the validTripNumbers to the user inputted trip number
            {
                nCheck = 1; //If it is valid, then the nCheck variable is set to 1
            }
        }

    }while( nCheck != 1); //If the nCheck variable is not equal to 1, then the loop will continue
    
}

/*  
    initializeLoop is a function to initialize a variable to set it to 0 or null.

    @param passengerInfo = A struct where all passengers' information are stored
    @param userInfo = The structure array of loaded file passenger information that will be used with the embarkation card.
    @param loadInfo = The structure array of loaded file passenger information that will be used for viewing the past trips.
    @param nCapacityNum = The capacity of a specific trip with its 16 seats
    @param seatPrioNum = A 2D Array for storing the passenger's priority number according to their trip
    @param dropOffPointCount = A 2D Array for storing all the counts of drop off points in a specific trip
    @param allTrips = A 2D Array for storing the all the trips
    @return = None

    Pre-condition = None
*/
void initializeLoop( Passenger passengerInfo[320], 
                     User userInfo[320],
                     Load loadInfo[320],
                     int nCapacityNum[][16], 
                     int seatPrioNum[][16],
                     int dropOffPointCount[][16], 
                     char allTrips[][16] )
{
    int i, j; //Variable for loop

    for ( i = 0; i < 320; i++ ) //Loop for initializing the structure to null or 0
    {
        strcpy(passengerInfo[i].passengerFirstName, "\0"); strcpy(passengerInfo[i].passengerLastName, "\0");
        strcpy(passengerInfo[i].tripNumber, "\0"); strcpy(passengerInfo[i].embarkPoint, "\0");
        strcpy(passengerInfo[i].dropOffPoint, "\0"); passengerInfo[i].prioNum = 0;
        passengerInfo[i].idNum = 0; passengerInfo[i].date.nMonth = 0; passengerInfo[i].date.nDay = 0;
        passengerInfo[i].date.nYear = 0;

        strcpy(userInfo[i].userFirstName, "\0"); strcpy(userInfo[i].userLastName, "\0");
        strcpy(userInfo[i].userTripNumber, "\0"); strcpy(userInfo[i].userEmbarkPoint, "\0");
        strcpy(userInfo[i].userDropOffPoint, "\0"); userInfo[i].userPrioNum = 0;
        userInfo[i].userIdNum = 0; userInfo[i].userDate.nMonth = 0;userInfo[i].userDate.nDay = 0; 
        userInfo[i].userDate.nYear = 0;

        strcpy(loadInfo[i].loadTripNumber, "\0"); strcpy(loadInfo[i].loadFirstName, "\0");
        strcpy(loadInfo[i].loadLastName, "\0"); strcpy(loadInfo[i].loadEmbarkPoint, "\0");
        strcpy(loadInfo[i].loadDropOffPoint, "\0"); loadInfo[i].loadPrioNum = 0;
        loadInfo[i].loadIdNum = 0; loadInfo[i].loadDate.nMonth = 0; loadInfo[i].loadDate.nDay = 0;
        loadInfo[i].loadDate.nYear = 0;
        
    }  

    for ( i = 0; i < 20; i++ )
    {   
        for ( j = 0; j < 16; j++ )
        {
            allTrips[i][j] = 'O'; //Initializes the 2D array to letter O. To display O to available seats.
            seatPrioNum[i][j] = 7; //Initializes the 2D array to 0. 
            dropOffPointCount[i][j] = 0; //Initializes the 2D array to 0.
            nCapacityNum[i][j] = 0; 
        }
    }

}

/*  
    fixFileName is a function to have fileDateMonth, fileDateDay and fileDateYear combined into a single string named fileName

    @param fileName = A string variable where other strings will be stored.
    @param fileDateMonth = A string variable for the month from user input.
    @param fileDateDay = A string variable for the day from user input.
    @param fileDateYear = A string variable for the year from user input.
    @return = None

    Pre-condition = Input from the user must be in the format of DD/MM/YYYY
*/
void fixFileName ( String30 fileName, 
                   String30 fileDateMonth, 
                   String30 fileDateDay, 
                   String30 fileDateYear )
{
    
    strcpy(fileName, "Trip"); //Puts a Trip word on fileName
    strcat(fileName, "-"); 
    strcat(fileName, fileDateDay);
    strcat(fileName, "-");
    strcat(fileName, fileDateMonth);
    strcat(fileName, "-");
    strcat(fileName, fileDateYear);
    strcat(fileName, ".txt");

}

/*  
    fileCreation is a function to create the txt file of the passengers when the personel exits.

    @param passengerInfo = A struct where all passengers' information are stored
    @param fileDateMonth = A string variable for the month from user input.
    @param fileDateDay = A string variable for the day from user input.
    @param fileDateYear = A string variable for the year from user input.
    @param validTripNumber = A string array where all the valid trip numbers are stored.
    @param fileName = A string variable for fileDateMonth,Day, and Year to be stored in.
    @param fp = A file pointer
    @return = None

    Pre-condition = None
*/
void fileCreation( Passenger passengerInfo[320], 
                   String30 fileDateMonth, 
                   String30 fileDateDay, 
                   String30 fileDateYear, 
                   String30 validTripNumber[20], 
                   String30 fileName, 
                   FILE *fp)
{

    int i, j; //Local Variables

    fixFileName(fileName, fileDateMonth, fileDateDay, fileDateYear); //Gives the file name to be passed on fp = fopen(fileName, "a");

    //WRITE ALL PASSENGER INFO TO fileDate
    fp = fopen(fileName, "a"); //Opens the file in Append mode.

    for ( i = 0; i < 320; i++ ) //A loop for scanning all the Passenger Information in the struct
    {
        for ( j = 0; j < 20; j++ ) //A loop for going through all the trip numbers
        {
            if ( strcmpi(passengerInfo[i].tripNumber, validTripNumber[j]) == 0 ) //Compares a passenger's trip number to a valid trip number & It sorts out all the passengers without trip numbers.
            {
                fprintf(fp, "%s\n", passengerInfo[i].tripNumber);
                fprintf(fp, "%s\n", passengerInfo[i].embarkPoint);
                fprintf(fp, "%s %s\n", passengerInfo[i].passengerFirstName, passengerInfo[i].passengerLastName);
                fprintf(fp, "%d\n", passengerInfo[i].idNum);
                fprintf(fp, "%d\n", passengerInfo[i].prioNum);
                fprintf(fp, "%.2d %.2d %d\n", passengerInfo[i].date.nDay, passengerInfo[i].date.nMonth, passengerInfo[i].date.nYear);
                fprintf(fp, "%s\n", passengerInfo[i].dropOffPoint);
                fprintf(fp, "\n\n");
                
            }
        }

    }
    
    fclose(fp); //Properly closed the file after appending.

}

/*  
    fileLoad is a function to load files into the system.

    @param userInfo = The structure array of loaded file passenger information that will be used with the embarkation card.
    @param userFileName = A string variable for userDateMonth,Day, and Year to be stored in from the user input inside the function.
    @param fileStatusLoad = A variable to check if the file is loaded or not.
    @param fileStatusCount = A variable to count the number of passengers in the chosen file
    @param fp = A file pointer
    @return = None

    Pre-condition = All inputs from the Embarkation Card is valid.
                    All inputs are manually typed not copy pasted.
*/
void fileLoad ( User userInfo[320],
                Load loadInfo[320],
                String30 userFileName,
                int *fileStatusLoad,
                int *fileStatusCount,
                int loadMenuChoice, 
                FILE *fp)
{
    int i; //Local Variable
    int nMonth, nDay, nYear;
    int nSuccess = 0;
    String30 loadMonth, loadDay, loadYear, loadName;

    int nCount = 0;

    if ( loadMenuChoice == 1 ) //If the user chose to load the embarkation card file
    {
        *fileStatusLoad = 1;

        strcpy(userFileName, "EmbarkationCard"); //Puts a EmbarkCard word on userFileName
        strcat(userFileName, ".txt"); //Adds the .txt extension to the userFileName

        printf("\n[%s]\n", userFileName); //Displays the File Name that is used to read.

        fp = fopen(userFileName, "r"); //Opens the file in Read Mode

        if ( fp == NULL ) //If, the file is not created or detected. It will print an error message and create a EmbarkationCard file by itself.
        {
            printf("[ERROR] File not found.\n");

            fp = fopen("EmbarkationCard.txt", "w"); //Creates the file in Write Mode

            if ( fp == NULL ) //If the newly created file is not detected. It will print an error message.
            {
                printf("[ERROR] Failed to create file.\n");
            }
            else //If the newly created file is detected. It will print a success message.
            {
                printf("[SUCCESS] File created.\n");
            }

        }
        else //Else, the file is detected. It will print a success message.
        {
            printf("[SUCCESS] File is already loaded.\n");
        }

        for ( i = 0; i < 320; i++ ) //A loop for scanning all the Passenger Information in the struct
        {
            fscanf(fp, "%s", userInfo[i].userTripNumber);
            fscanf(fp, " %[^\n]s\n", userInfo[i].userEmbarkPoint);
            fscanf(fp, " %s %[^\n]s", userInfo[i].userFirstName, userInfo[i].userLastName);
            fscanf(fp, " %d", &userInfo[i].userIdNum);
            fscanf(fp, " %d", &userInfo[i].userPrioNum);
            fscanf(fp, " %d %d %d", &userInfo[i].userDate.nDay, &userInfo[i].userDate.nMonth, &userInfo[i].userDate.nYear);
            fscanf(fp, " %[^\n]s", userInfo[i].userDropOffPoint);

            if ( userInfo[i].userPrioNum != 0 )
            {
                nCount++; //Counts the number of passengers with a priority number
            }

        }
    }
    else if ( loadMenuChoice == 2 ) //If the user chose to load the Past Trip card file
    {
        do
        {

            printf("Enter Date (DD MM YYYY): "); //Asks the user to input the date of the file to be loaded.
            scanf(" %d%d%d", &nDay, &nMonth, &nYear);
            while ((getchar()) != '\n');

            if ( nMonth >= 1 && nMonth <= 12 && 
                 nDay >= 1 && nDay <= 31 && 
                 nYear == 2022 ) //If statement for checking if month, day and year is valid.
            {
                printf("[SUCCESS] Date is valid. \n");
                sprintf(loadDay, "%.2d", nDay); //Converts the day to a string with 2 digits.
                sprintf(loadMonth, "%.2d", nMonth); //Converts the month to a string with 2 digits.
                sprintf(loadYear, "%d", nYear); //Converts the year to a string.

                strcpy(loadName, "Trip"); //Puts a Trip word on userFileName
                strcat(loadName, "-");
                strcat(loadName, loadDay);
                strcat(loadName, "-");
                strcat(loadName, loadMonth);
                strcat(loadName, "-");
                strcat(loadName, loadYear);
                strcat(loadName, ".txt");

                printf("[DATE ENTERED]: [%s]\n", loadName); //Displays the File Name that is used to read.

                fp = fopen(loadName, "r"); //Opens the file in Read Mode

                if ( fp == NULL ) //If, the file is not created or detected. It will print an error message.
                {
                    printf("[ERROR] File not found.\n");

                }
                else //Else, the file is detected. It will print a success message.
                {
                    printf("[SUCCESS] File is already loaded.\n");
                }
 
                nSuccess = 1; //Sets the nSuccess variable to 1 to break the loop.
            }
            else
            {
                printf("[ERROR] Invalid Date. \n");
                nSuccess = 0; //Sets the nSuccess variable to 0 to continue the loop.
            }

        }while( nSuccess == 0 );


        for ( i = 0; i < 320; i++ ) //A loop for scanning all the Past trip text file in the struct
        {

            fscanf(fp, "%s", loadInfo[i].loadTripNumber);
            fscanf(fp, " %[^\n]s\n", loadInfo[i].loadEmbarkPoint);
            fscanf(fp, " %s %[^\n]s", loadInfo[i].loadFirstName, loadInfo[i].loadLastName);
            fscanf(fp, " %d", &loadInfo[i].loadIdNum);
            fscanf(fp, " %d", &loadInfo[i].loadPrioNum);
            fscanf(fp, " %d %d %d", &loadInfo[i].loadDate.nDay, &loadInfo[i].loadDate.nMonth, &loadInfo[i].loadDate.nYear);
            fscanf(fp, " %[^\n]s", loadInfo[i].loadDropOffPoint);

        }
 
    }

    *fileStatusCount = nCount; //Sets the fileStatusCount variable to the number of passengers with a priority number.
    fclose(fp); //Properly closed the file after appending.

}

/*  
    fileView is a function to view the information of a txt file into the terminal.

    @param userInfo = The structure array of loaded file passenger information that will be used with the embarkation card.
    @param loadInfo = The structure array of loaded file passenger information that will be used for viewing the past trips.
    @param loadMenuChoice = A variable that holds the user's choice of which file to view.
    @return = None

    Pre-condition = None
*/
void fileView( User userInfo[320],
               Load loadInfo[320],
               int loadMenuChoice )
{
    int i, j; //Local variable

    printf("\n");

    if ( loadMenuChoice == 1 ) //If the user chose to view the embarkation card file
    {
        for ( i = 0; i < 320; i++ ) //A loop for scanning all the Passenger Information in the struct
        {
            if ( userInfo[i].userPrioNum != 0 ) //If, a passenger does not have any priority number. It means it is not yet registered. Hence, it will stop looping until the last priority number it detects.
            {
                printf("[Trip Number] - [%s]\n", userInfo[i].userTripNumber);
                printf("[Embarkation Point] - [%s]\n", userInfo[i].userEmbarkPoint);
                printf("[Name] - [%s %s]\n", userInfo[i].userFirstName, userInfo[i].userLastName);
                printf("[I.D Number] - [%d]\n", userInfo[i].userIdNum);
                printf("[Priority Number] - [%d]\n", userInfo[i].userPrioNum);
                printf("[Date of Trip] - [%d %d %d]\n", userInfo[i].userDate.nMonth, userInfo[i].userDate.nDay, userInfo[i].userDate.nYear);
                printf("[Drop-off Point] - [%s]\n", userInfo[i].userDropOffPoint);
                printf("\n");        
            }

        }
    }
    else if ( loadMenuChoice == 2 ) //If the user chose to view the Past Trip card file
    {
        Load temp; //Variable for temporary structures

        for (i = 0; i < 320; i++) //A loop for scanning all the passenger info in the structure
        {
            for (j = i + 1; j < 320; j++) //A loop for scanning all the the next passenger info in the structure
            {
                if (loadInfo[i].loadPrioNum > loadInfo[j].loadPrioNum) //If, the recent passenger's priority number is greater than the next passenger's priority number.
                {
                    temp = loadInfo[i]; //Sets the temp variable to the recent passenger's information.
                    loadInfo[i] = loadInfo[j]; //Sets the recent passenger's information to the next passenger's information.
                    loadInfo[j] = temp; //Sets the next passenger's information to the temp variable.
                
                }
           }
        }

        for ( i = 0; i < 320; i++ ) //A loop for scanning all the Passenger Information in the struct
        {
            if ( loadInfo[i].loadPrioNum != 0 ) //If, a passenger does not have any priority number. It means it is not yet registered. Hence, it will stop looping until the last priority number it detects.
            {
                printf("[Trip Number] - [%s]\n", loadInfo[i].loadTripNumber);
                printf("[Embarkation Point] - [%s]\n", loadInfo[i].loadEmbarkPoint);
                printf("[Name] - [%s %s]\n", loadInfo[i].loadFirstName, loadInfo[i].loadLastName);
                printf("[I.D Number] - [%d]\n", loadInfo[i].loadIdNum);
                printf("[Priority Number] - [%d]\n", loadInfo[i].loadPrioNum);
                printf("[Date of Trip] - [%d %d %d]\n", loadInfo[i].loadDate.nMonth, loadInfo[i].loadDate.nDay, loadInfo[i].loadDate.nYear);
                printf("[Drop-off Point] - [%s]\n", loadInfo[i].loadDropOffPoint);
                printf("\n");
            }
        }
    }

}

/*  
    checkSystem is a function for knowing when will the system create the txt file or not.

    @param passengerInfo = A struct where all passengers' information are stored.
    @param validTripNumber = The array of valid trip numbers
    @return = Values 0 or 1 to know the system's status 

    Pre-condition = None
*/
int checkSystem( Passenger passengerInfo[320], 
                 String30 validTripNumber[20] )
{
    int i, j; //Local variable

    //[0] = System does not have any passenger/s.
    //[1] = System have passenger/s
    int nSystem = 0; //Variable for returning the system's status

    for ( i = 0; i < 320; i++ ) //A loop for scanning all the trip numbers of all passengers.
    {
        for ( j = 0; j < 20; j++ ) //A loop for going through all the valid trip numbers.
        {
            if ( strcmpi(passengerInfo[i].tripNumber, validTripNumber[j]) == 0 ) //If, a trip number of a passenger is the same with the valid trip numbers. It means that the system have a passenger.
            {
                nSystem = 1; //Gives nSystem a value of 1 to know that there is a passenger in the system
            }
        }
    }

    return nSystem; //Returns either 0 or 1.

}

/*
    dateFormat is a function for checking and asking the user for the date when the system starts.

    @param fileDateMonth = A string where it stores the user input of the month from the function itself.
    @param fileDateDay = A string where it stores the user input of the day from the function itself.
    @param fileDateYear = A string where it stores the user input of the year from the function itself.
    @param nMonth = A integer variable for getting the month of the date from the function itself.
    @param nDay = A integer variable for getting the day of the date from the function itself.
    @param nYear = A integer variable for getting the year of the date from the function itself.
    @return = None

    Pre-condition = None
*/
void dateFormat ( String30 fileDateMonth, 
                  String30 fileDateDay, 
                  String30 fileDateYear,
                  int *nMonth,
                  int *nDay,
                  int *nYear )
{
    int nSuccess = 0;
    int tempMonth, tempDay, tempYear;
    
    do
    {
        printf("Enter Date (DD MM YYYY): ");
        scanf("%d%d%d",&tempDay, &tempMonth, &tempYear); //Gets the user input of the date.
        while ((getchar()) != '\n');

        if ( tempMonth >= 1 && tempMonth <= 12 && 
             tempDay >= 1 && tempDay <= 31 && 
             tempYear == 2022 ) //If statement for checking if month, day and year is valid.
        {
            printf("[SUCCESS] Date is valid. \n");

            //This is like differentiating the month, day and year of the system with the dates that is going to be used for a passenger's date of trip.
            sprintf(fileDateDay, "%.2d", tempDay); //Sets the fileDateDay to the user input of the day.
            sprintf(fileDateMonth, "%.2d", tempMonth); //Sets the fileDateMonth to the user input of the month.
            sprintf(fileDateYear, "%d", tempYear); //Sets the fileDateYear to the user input of the year.
            printf("[DATE ENTERED]: [%s-%s-%s]\n", fileDateDay, fileDateMonth, fileDateYear); 
            nSuccess = 1; //Gives nSuccess a value of 1 to break the loop.
        }
        else
        {
            printf("[ERROR] Invalid Date. \n");
            nSuccess = 0; //Gives nSuccess a value of 0 to continue the loop.
        }

    }while( nSuccess == 0 );  

    //Putting the user input from the function here into the passenger's date of trip.
    *nMonth = tempMonth; 
    *nDay = tempDay;
    *nYear = tempYear;

}

int main()
{  
    //GENERAL VARIABLES
    int i; //For looping
    int nCountPassenger = 0; //This counts on what number did the Passenger embark
    String30 userTripNumber; //Variable to store the Trip Number from the Menus
    int systemStatus = 0; //This gets the value being returned by the function of checkSystem.

    //FILE VARIABLES
    int fileStatusLoad = 0; //This acts as the status indicator if the file is loaded or not.
    int fileStatusCount = 0; //A variable to count the number of passengers in the chosen file
    int *pFileStatusLoad; //Pointer to the fileStatusLoad
    int *pFileStatusCount; //Pointer to the fileStatusCount
    pFileStatusLoad = &fileStatusLoad; //Sets the pointer to the fileStatusLoad 
    pFileStatusCount = &fileStatusCount; //Sets the pointer to the fileStatusCount
    FILE *fp; //Pointer for the file
    String30 fileName; //Variable for setting the file name
    String30 userFileName; //Variable for getting the file name from the user
    String30 fileDateMonth, fileDateDay, fileDateYear, fileDate; //String variables for the user input of Date before starting the system.
    int loadMenuChoice = 0; //Variable for getting the user input of the load menu.

    //VARIABLES FOR FILE NAME
    int nMonth, nDay, nYear; //Variables for the date
    int *pMonth, *pDay, *pYear; //Pointers for the date
    pMonth = &nMonth; //Sets the pointer to the nMonth
    pDay = &nDay; //Sets the pointer to the nDay
    pYear = &nYear; //Sets the pointer to the nYear

    //VARIABLES FOR ALL THE VALID TRIP NUMBERS
    String30 validTripNumber[20] = { {"AE101"}, {"AE102"}, {"AE103"}, {"AE104"}, {"AE105"}, {"AE106"}, {"AE107"}, {"AE108"}, 
                                     {"AE109"}, {"AE150"}, {"AE151"}, {"AE152"}, {"AE153"}, {"AE154"}, {"AE155"}, {"AE156"}, 
                                     {"AE157"}, {"AE158"}, {"AE159"}, {"AE160"} };

    //VARIABLES FOR ALL THE VALID TRIP NUMBERS FOR LAGUNA AND MANILA
    String30 validTripNumberLaguna[11] = { {"AE150"}, {"AE151"}, {"AE152"}, {"AE153"}, {"AE154"}, {"AE155"}, 
                                           {"AE156"}, {"AE157"}, {"AE158"}, {"AE159"}, {"AE160"} };
    String30 validTripNumberManila[9] = { {"AE101"}, {"AE102"}, {"AE103"}, {"AE104"}, {"AE105"}, {"AE106"}, {"AE107"}, {"AE108"}, {"AE109"} };

    //VARIABLES FOR ALL THE VALID EMBARKATION POINT FOR LAGUNA AND MANILA
    String99 validEmbarkPointLaguna[4] = { {"DLSU Laguna Campus"}, {"Milagros Del Rosario Building"}, {"MRR Building"}, {"DLSU Laguna Campus East Canopy"} };
    String99 validEmbarkPointManila[2] = { {"DLSU Manila Campus"}, {"DLSU South Gate Driveway"} };

    //VARIABLES FOR ALL THE DROP OFF POINTS FOR LAGUNA AND MANILA
    String99 validDropOffPointLaguna[4] = { {"Petron Gasoline Station along Gil Puyat Avenue"}, {"Gate 1 South Gate"}, {"Gate 2 North Gate"}, {"Gate 4 Gokongwei Gate"} };
    String99 validDropOffPointManila[3] = { {"Mamplasan Toll Exit"}, {"Phase 5 San Jose Village"}, {"Milagros Del Rosario Building East Canopy"} };
 
    //STRUCT VARIABLES
    Passenger passengerInfo[320]; //Array of passenger structs
    User userInfo[320]; //Array of loaded passenger structs for embarkation card
    Load loadInfo[320]; //Array of loaded passenger structs for past trip
    
    //PASSENGER CAPACITY COUNT VARIABLE
    int nCapacityNum[20][16]; //Array of passenger capacity numbers
    int checkValidCapacity = 0; //Variable for checking if the passenger is in the capacity

    //VARIABLES FOR PASSENGER MENU
    char nPassengerMenu2Choice; //Variable for Passenger Menu 2, answer from Add Passenger Y/N.
    int nMenuChoice = 0; //Variable for the Main Menu Choice
    int nPassengerMenuChoice; //Variable for the Passenger Menu Choice
    int statusEmbark = 0; //Variable for the Embarkation Card Status

    //VARIABLES FOR ARROW EXPRESS PERSONEL MENU
    int nArrowExpressChoice; //Variable for the Arrow Express Personnel Menu Choice
    String30 searchLastName; //Variable for the Search Passenger Function
    
    //VARIABLES FOR DROP-OFF POINTS COUNT
    int dropOffPointCount[20][16]; //Array of drop off points count

    //VARIABLES FOR SEAT ASSIGNMENTS OF THE PASSENGERS
    char allTrips[20][16]; //2D Array of all trips
    int seatNumber[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; //Variable for the Seat Number per Trip
    int seatPrioNum[20][16]; //2D Array of seat priority numbers in each trip.

    //Loop for initializing the arrays to be set either to null or 0 or both.
    initializeLoop(passengerInfo, userInfo, loadInfo, nCapacityNum, seatPrioNum, dropOffPointCount, allTrips );

    dateFormat(fileDateMonth, fileDateDay, fileDateYear, &nMonth, &nDay, &nYear); //Function for getting the date of the file and storing it in the variables.

    //LOOP FOR THE WHOLE SYSTEM
    do
    {   

        //IF STATEMENT TO CHECK IF THE USER INPUT IS STILL VALID OR INVALID
        if ( nMenuChoice < 1 || nMenuChoice > 3 || nPassengerMenu2Choice >= 1 && nPassengerMenu2Choice <= 3 )
        {
            displayMenu(); //FUNCTION FOR DISPLAYING MAIN MENU
            scanf(" %d", &nMenuChoice); 
            while ((getchar()) != '\n');           
        }

        //SWITCH STATEMENT FOR MAIN MENU
        switch( nMenuChoice )
        {
            //CASE 1: PASSENGER FEATURES
            case 1:

                //LOOP FOR PASSENGER FEATURES MENU
                do
                {
                    nPassengerMenuChoice = choicePassengerMenu(); //Function for displaying passenger features menu and asking for user's choice

                    //SWITCH STATEMENT FOR PASSENGER FEATURES MENU
                    switch( nPassengerMenuChoice )
                    {   
                        //CASE 1: EMBARKATION REGISTRATION AND BUS ASSIGNMENT
                        case 1:

                            //LOOP FOR ASKING IF USER WANTS TO ADD A PASSENGER UNTIIL THE USER CHOOSE 'N' or NO
                            do
                            {

                                printf("\n[NOTE] Add passenger? (Y/N): "); 
                                scanf(" %c", &nPassengerMenu2Choice);
                                while ((getchar()) != '\n');

                                //IF THE USER CHOOSE 'Y' OR YES, THE FUNCTION FOR EMBARKING A PASSENGER WILL BE CALLED
                                if ( nPassengerMenu2Choice == 'Y' || nPassengerMenu2Choice == 'y' )
                                {
                                    system("CLS");

                                    fileStatusLoad = 0;
                                    fileStatusCount = nCountPassenger;
                                    statusEmbark = inputEmbarkation( passengerInfo, userInfo, nPassengerMenu2Choice, nCountPassenger, nCapacityNum, dropOffPointCount, seatPrioNum, fileStatusLoad, fileStatusCount, nMonth, nDay, nYear,
                                                                     seatNumber, validTripNumber, validTripNumberLaguna, validTripNumberManila, validEmbarkPointLaguna, validEmbarkPointManila, validDropOffPointLaguna, validDropOffPointManila);

                                    if ( statusEmbark == 1 )
                                    {
                                        printf("\n[NOTE] Embarkation Card successfully signed.\n");
                                        identifyTrip(passengerInfo, nCountPassenger, validTripNumber, seatNumber, seatPrioNum, allTrips, nCapacityNum); //Function for assigning them to their trip and this function will call a function to assign a seat.
                                        writeEmbarkation(passengerInfo, nCountPassenger, fp); //Function for writing the passenger information to the embarkation card file.
                                        printf("\n\n"); 
                                        nCountPassenger++; //This acts as a counter for the number of passengers
                                        
                                    }
                                    else
                                    {
                                        printf("\n[NOTE] Embarkation Card failed to signed.\n");
                                    }    
                                    
                                }
                                //IF THE USER CHOOSE 'N' OR NO, THE SYSTEM WILL PRINT THAT EMBARKATION CARD IS NOT SIGNED
                                else if ( nPassengerMenu2Choice == 'N' || nPassengerMenu2Choice == 'n' )
                                {
                                    printf("[ERROR] Embarkation Card is NOT SIGNED.\n");
                                    
                                }
                                //IF THE USER CHOOSE NEITHER FROM THE TWO, IT WILL PRINT INVALID INPUT 
                                else
                                {
                                    printf("[ERROR] Invalid Input.\n");
                                }

                            }while( nPassengerMenu2Choice == 'Y' || nPassengerMenu2Choice == 'y' && nMenuChoice != 0 ); //Loop until the user choose 'N' or NO
                            
                            break;

                        //CASE 2: DISPLAY SCHEDULES
                        case 2:
                            displaySchedule(); //Function to display all the schedules of the arrow express line shuttles
                            break;
                        
                        //CASE 3: BACK
                        case 3:
                            nMenuChoice = 0; //Setting to 0 to go back to the main menu
                            break;
                        default:
                            break;

                    }

                }while( nPassengerMenuChoice != 3 ); //Loop until the user choose '3' to go back to the main menu

                break;

            //CASE 2: ARROW EXPRESS PERSONNEL FEATURES
            case 2:

                displayArrowExpressMenu(); //Function for displaying arrow express personnel menu
                scanf(" %d", &nArrowExpressChoice);
                while ((getchar()) != '\n');

                //SWITCH STATEMENT FOR THE USER INPUT FROM THE ARROW EXPRESS PERSONNEL MENU
                switch( nArrowExpressChoice )
                {
                    //CASE 1: VIEW HOW MANY PASSENGERS ARE IN PER TRIP
                    case 1:
                        checkValidTripNumber(userTripNumber, validTripNumber); //Function for checking if the user input is valid
                        getTripNumber(userTripNumber, nCapacityNum, validTripNumber, allTrips); //Function for getting the trip number to be pass on to the function for displaying the number of passengers in each trip
                        break;
                    //CASE 2: VIEW HOW MANY PASSENGERS ON A DROP OFF PER TRIP
                    case 2:
                        checkValidTripNumber(userTripNumber, validTripNumber); //Function for checking if the user input is valid
                        viewCountOfPassengerDropOff( passengerInfo, userTripNumber, dropOffPointCount, validTripNumber, validTripNumberLaguna, 
                                                     validTripNumberManila, validDropOffPointLaguna, validDropOffPointManila); //Function for displaying the number of passengers on a drop off
                        break;
                    //CASE 3: VIEW THE PASSENGERS ON A TRIP
                    case 3:
                        checkValidTripNumber(userTripNumber, validTripNumber); //Function for checking if the user input is valid
                        viewPassengersInfo(passengerInfo, userTripNumber); //Function for dispalying the passengers' information on a trip
                        break;
                    case 4:

                        loadMenuChoice = displayLoadMenu(); //Function for displaying load menu and asking for user's choice

                        if ( loadMenuChoice >= 1 && loadMenuChoice <= 2 ) //If the user choose 1 or 2, the function for loading the passengers will be called
                        {
                            fileLoad(userInfo, loadInfo, userFileName, &fileStatusLoad, &fileStatusCount, loadMenuChoice, fp); //Function for loading the file

                            for ( i = nCountPassenger; i < fileStatusCount; i++ ) //Loop for adding the passengers to the array
                            {
                                
                                statusEmbark = inputEmbarkation( passengerInfo, userInfo, nPassengerMenu2Choice, nCountPassenger, nCapacityNum, dropOffPointCount, seatPrioNum, fileStatusLoad, fileStatusCount, nMonth, nDay, nYear,
                                                                 seatNumber, validTripNumber, validTripNumberLaguna, validTripNumberManila, validEmbarkPointLaguna, validEmbarkPointManila, validDropOffPointLaguna, validDropOffPointManila);
                                if ( statusEmbark == 1 ) //If the function for embarking a passenger is successful
                                {
                                    identifyTrip(passengerInfo, nCountPassenger, validTripNumber, seatNumber, seatPrioNum, allTrips, nCapacityNum); //Function for assigning them to their trip and this function will call a function to assign a seat.
                                    printf("\n\n");  
                                    nCountPassenger++; 
                                }
                                else if ( statusEmbark == 0 ) //If the function for embarking a passenger is unsuccessful
                                {
                                    printf("\n[ERROR] Embarkation Card failed to signed.\n");
                                    i = fileStatusCount;
                                }
                                  
                            }  

                            nCountPassenger = fileStatusCount; //Setting the counter to the number of passengers loaded from the file                                                           
        
                        }
                        break;
                    //CASE 5: VIEW THE PASSENGERS WITH THE LAST NAME OF THE USER INPUT
                    case 5:
                        printf("Enter Last Name: ");
                        scanf(" %[^\n]s", searchLastName);
                        while ((getchar()) != '\n'); 
                        searchPassenger(passengerInfo, searchLastName); //Function for searching the passenger with the last name of the user input
                        break;
                    case 6:
                        loadMenuChoice = displayLoadMenu(); //Function for displaying load menu and asking for user's choice
                        fileView(userInfo, loadInfo, loadMenuChoice); //Function for viewing the loaded file
                        break;
                    case 7:
                        nMenuChoice = 0; //Setting to 0 to go back to the main menu
                        break;
                    default:
                        break;
                }
                break;

            //CASE 3: EXIT
            case 3:
                //CHECK IF THE USER INPUTTED PASSENGER INFOS
                systemStatus = checkSystem(passengerInfo, validTripNumber);
                
                if ( systemStatus == 0 ) //Statement to know if the system will create a file or not. Depending if there's a passenger or none.
                {
                    printf("[SUCCESS] Closed Program\n");

                }
                else 
                {
                    printf("[SYSTEM] Creating File...\n");
                    fileCreation(passengerInfo ,fileDateMonth, fileDateDay, fileDateYear, validTripNumber, fileName, fp); //Function for creating a file
                    printf("[SYSTEM] File is created.\n");
                    printf("[SUCCESS] Closed Program\n");
                }

                nMenuChoice = 3;
                break;

            default:
                break;
        }
            
    }while( nMenuChoice != 3); //Loop until the user choose '3' to exit the program

    return 0;

}
