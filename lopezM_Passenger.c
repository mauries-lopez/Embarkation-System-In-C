#include <stdio.h>
#include <string.h>

void displayPriorityInfo()
{
    int prioNum[6] = {1, 2, 3, 4, 5, 6};
    String99 prioInfo[6] = { "Faculty and ASF with Inter-campus assignments",
                             "Students with inter-campus enrolled subjects or enrolled in thesis using Inter-campus facilities",
                             "Researchers",
                             "Academic Coordinators level and up for Faculty and ASF, and Director level and up for ASAP",
                             "University Fellows",
                             "Employees and Students with official business" };

    int i;
    
    printf("\n===========================================================================================================\n\n");
    printf("[PRIORITY GROUPS]\n");
    for ( i = 0; i < 6; i++ )
    {
        printf("[%d] = [%s]\n", prioNum[i], prioInfo[i]);
    }
    printf("\n===========================================================================================================\n");
}

void displaySchedule()
{
    int y;

    String99 tripNumberA[20] = { "AE101", "AE102", "AE103", 
                                 "AE104", "AE105", "AE106", 
                                 "AE107", "AE108", "AE109" };

    String99 tripNumberB[20] = { "AE150", "AE151", "AE152", 
                                 "AE153", "AE154", "AE155", 
                                 "AE156", "AE157", "AE158", 
                                 "AE159", "AE160" };

    String99 ETDA[20] = { "6:00 AM", "7:30 AM", "9:30 AM", 
                          "11:00 AM", "1:00 PM", "2:30 PM", 
                          "3:30 PM", "5:00 PM", "6:15 PM" };

    String99 ETDB[20] = { "5:30 AM", "5:45 AM", "7:00 AM", 
                          "7:30 AM", "9:00 AM", "11:00 AM", 
                          "1:00 PM", "2:30 PM", "3:30 PM", "5:00 PM", "6:15 PM" };

    printf("\n========================================================\n");
    printf("\n[MANILA TO LAGUNA ROUTE SCHEDULE]\n");
    printf("Trip #: \tETD: \t\n");

    for (y = 0; y < 9; y++)
    {
        printf("[%s] \t[%s]\n", tripNumberA[y], ETDA[y]);
    }
    printf("\n[LAGUNA TO MANILA ROUTE SCHEDULE]\n");
    printf("Trip #: \tETD: \t\n");
    for (y = 0; y < 11; y++)
    {
        printf("[%s] \t[%s]\n", tripNumberB[y], ETDB[y]);
    }
    printf("\n========================================================\n");
}

/*  
    swapSeat a function to swap the seat number of two passengers.

    @param a = An int variable where it stores the first passenger's seat number.
    @param b = An int variable where it stores the second passenger's seat number.
    @return = None

    Pre-condition = None
*/
void swapSeat ( int *a, 
                int *b )
{
    int temp;

    temp = *a;
    *a = *b; 
    *b = temp;
}

/* 
    assignSeat is a function to assign a respective seat to a passenger in their respective trip number according to their priority number.

    @param passengerInfo = A struct where all passengers' information are stored
    @param nCountPassenger = This acts like the index of the passenger in the passengerInfo struct
    @param validTripNumber = A string array where all the valid trip numbers are stored.
    @param seatNumber = An array of integer containing numbers from 1 to 16.
    @param tripDisplay = A string to which gets the trip number of a passenger
    @param seatPrioNum = A 2D Array for storing the passenger's priority number according to their trip
    @param allTrips = A 2D Array for storing the all the trips
    @param nCapacityNum = An array of integer containing the numbers of seats in each trip.
    @return = None

    Pre-condition = None
*/
void assignSeat ( Passenger passengerInfo[320], 
                  int nCountPassenger, 
                  String30 validTripNumber[20], 
                  int seatNumber[16], 
                  String30 tripDisplay,
                  int seatPrioNum[], 
                  char allTrips[],
                  int nCapacityNum[] )
{

    int i, j;
    int min;

    //This loop is for the Straight Selection Sort
    for ( i = 0; i < 16-1; i++ )
    {
        min = i;
        for ( j = i + 1; j < 16; j++ )
        {
            if ( seatPrioNum[min] > seatPrioNum[j]) //If the priority number of the current seat is greater than the priority number of the next seat, then swap the seats.
            {
                min = j;
            }
        }
        swapSeat ( &seatPrioNum[min], &seatPrioNum[i] ); //Swap the seat number of two passengers
    }

    //This loop is for assigning the passenger to a seat number
    for ( i = 0; i < 320; i++ ) 
    {
        for ( j = 0; j < 16; j++ )
        {
            if ( passengerInfo[i].prioNum == passengerInfo[nCountPassenger].prioNum && passengerInfo[i].prioNum == seatPrioNum[j] ) 
            {
                printf("\n[SYSTEM]: [%s %s] is on Seat #[%d].", passengerInfo[nCountPassenger].passengerFirstName, passengerInfo[nCountPassenger].passengerLastName, seatNumber[j]);
                i = 320;
                j = 16;
            }
        }
    }

    //This loop is for displaying if there are available and unavailable seat in the trip.
    for ( i = 0; i < 16; i++ )
    {
        if ( allTrips[i] == 'O' ) //If the seat is available, then display 'O'
        {
            allTrips[i] = 'X'; //If the seat is unavailable, then display 'X'
            i = 16;          
        }
    }
 
    printf("\n");

    //This loop is for displaying the available and unavailable seats through a grid.
    printf("\n[Trip Number] = [%s]\n", tripDisplay);

    for ( i = 0; i < 20; i++ )
    {
        if ( nCapacityNum[i] <= 13 ) //If the number of seats in the trip is less than or equal to 13, then display the format of a 13 seater trip
        {
            for ( j = 0; j < 13; j++ )
            {
                printf("[%c]", allTrips[j]);

                if ( j % 3 == 2 )
                {
                    printf("\n");
                }

            }

            i = 20;
        }
        else //If the trip capacity is greater than 13, then display the format of a 16 seater trip
        {
            for ( j = 0; j < 16; j++ )
            {
                printf("[%c]", allTrips[j]);

                if ( j % 4 == 3 )
                {
                    printf("\n");
                }

                if ( j == 11 )
                {
                    printf("   ");
                }

                if ( j == 14 )
                {
                    printf("\n");
                }

            }

            i = 20;
        }
    }
    

}

/*  
    identifyTrip is a function to know which trip is the passenger according to their input.

    @param passengerInfo = The structure array of passenger information
    @param nCountPassenger = This acts like the index of the passenger in the passengerInfo struct
    @param validTripNumber = The array of valid trip numbers
    @param seatNumber = An array of integer containing numbers from 1 to 16.
    @param seatPrioNum = A 2D Array for storing the passenger's priority number according to their trip
    @param allTrips = A 2D Array for storing the Trips and on how many seats are there inside the Trip.
    @return = None

    Pre-condition = None
*/
void identifyTrip( Passenger passengerInfo[320], 
                   int nCountPassenger, 
                   String30 validTripNumber[20], 
                   int seatNumber[16],
                   int seatPrioNum[][16], 
                   char allTrips[][16],
                   int nCapacityNum[][16] )
{
    
    int i; //Local Variable

    for ( i = 0; i < 20; i++ ) //A loop for scanning all the valid trip number  
    {
        if ( strcmpi(passengerInfo[nCountPassenger].tripNumber, validTripNumber[i]) == 0 ) //If, the latest passenger has the the same trip number with a valid trip number. He/she will be assign to a seat.
        {
            assignSeat(passengerInfo, nCountPassenger, validTripNumber, seatNumber, passengerInfo[nCountPassenger].tripNumber, seatPrioNum[i], allTrips[i], nCapacityNum[i]);
            i = 20;
        }
    }

}

/* 
    countDropOffPoint is a function to count the number of passengers who have dropped off at a drop off point.

    @param passengerDropOffPoint = A string for storing the Passenger's drop off point from the embarkation card
    @param passengerTripNumber = A string for the storing the Passenger's trip number from the embarkation card
    @param dropOffPointCount = A 2D array for storing the number of passengers who dropped off at a specific drop off point
    @param validDropOffPointLaguna = A string variable of all the valid drop off points in Laguna
    @param validDropOffPointManila = A string variable for all the valid drop off points in Manila
    @param validTripNumber = The array of valid trip numbers 
    @param statusDropOff = An integer to tell if the function should add or subtract from the drop off point count
    @return = None

    Pre-condition = None
*/
void countDropOffPoint( String30 passengerDropOffPoint,
                        String30 passengerTripNumber,
                        int dropOffPointCount[][16],
                        String99 validDropOffPointLaguna[4], 
                        String99 validDropOffPointManila[3],
                        String30 validTripNumber[20],
                        int statusDropOff )
{

    int i, j; //Local Variable
    
    //ADD ONE TO THE COUNT OF A DROP OFF POINT OF LAGUNA WHEN THE PASSENGER TRIP NUMBER IS THE SAME WITH A VALIDTRIP NUMBER

    for ( i = 0; i < 20; i++ )
    {
        if ( strcmpi(passengerTripNumber, validTripNumber[i]) == 0 )
        {
            for ( j = 0; j < 4; j++ )
            {   
                if ( statusDropOff == 0 )
                {
                    if ( strcmpi(passengerDropOffPoint, validDropOffPointLaguna[j]) == 0 ) //If the passenger's drop off point is the same with a valid drop off point in Laguna, then add one to the count of that drop off point.
                    {
                        dropOffPointCount[i][j] = dropOffPointCount[i][j] + 1;
                        j = 4;
                        i = 20;
                    }
                }
                else if ( statusDropOff == 1 )
                {
                    if ( strcmpi(passengerDropOffPoint, validDropOffPointLaguna[j]) == 0 ) //If the passenger's drop off point is the same with a valid drop off point in Laguna, then add one to the count of that drop off point.
                    {
                        dropOffPointCount[i][j] = dropOffPointCount[i][j] - 1;
                        j = 4;
                        i = 20;
                    }                    
                }

            }

            for ( j = 0; j < 3; j++ )
            {
                if ( statusDropOff == 0 )
                {
                    if ( strcmpi(passengerDropOffPoint, validDropOffPointManila[j]) == 0 ) //If the passenger's drop off point is the same with a valid drop off point in Manila, then add one to the count of that drop off point.
                    {
                        dropOffPointCount[i][j] = dropOffPointCount[i][j] + 1;
                        j = 3;
                        i = 20;
                    }
                }
                else if ( statusDropOff == 1 )
                {
                    if ( strcmpi(passengerDropOffPoint, validDropOffPointManila[j]) == 0 ) //If the passenger's drop off point is the same with a valid drop off point in Manila, then add one to the count of that drop off point.
                    {
                        dropOffPointCount[i][j] = dropOffPointCount[i][j] - 1;
                        j = 3;
                        i = 20;
                    }                    
                }
            }

        }
    }

}

/*  
    checkTripCapacity is a function which adds a quantity of passenger in a certain trip.

    @param passengerTripNumber = A string that stores the user input of the trip number from the embarkation card.
    @param nCapacityNum = An array of integer that stores the amount of passengers on a trip.
    @param validTripNumber = The array of valid trip numbers
    @return nValid = It will return 0 if the capacity is not yet over 16. While, 1 when it is over 16

    Pre-condition = None
*/
int checkTripCapacity( String99 passengerTripNumber, 
                       int nCapacityNum[],
                       String30 validTripNumber[20] )
{

    int i; //Local Variable

    //[0] = If the trip number is not yet full.
    //[1] = If the trip number is full
    int nValid = 0; 

    for (i = 0; i < 20; i++) // A loop for scanning all the valid trip numbers
    {

        if ( strcmpi(passengerTripNumber, validTripNumber[i]) == 0 ) // If statement for comparing the passenger's trip number and all valid trip numbers
        {
            
            if ( nCapacityNum[i] >= 0 && nCapacityNum[i] <= 16 ) // If statement for checking if the capacity is over 16
            {
                nCapacityNum[i] = nCapacityNum[i] + 1; // Adds 1 to the specific index being passed on to i.
            }

            if ( nCapacityNum[i] > 12 ) // If the capacity is greater than 12, it will display an alert.
            {
                printf("[ALERT] Trip %s is now being over-loaded.\n", passengerTripNumber);
            }

            if ( nCapacityNum[i] > 16 ) // If the capacity is greater than 16, it will remove the latest passenger trying to go that specific trip.
            {
                nCapacityNum[i] = nCapacityNum[i] - 1;
                i = 20;
                nValid = 1; // nValid will be set to 1.

            }
        }
     
    }

    return nValid; //Returns either 0 or 1.

}

/* 
    inputEmbarkation is a function to where the passenger will sign up to get in their trips. It will ask the user to input the embarkation card. Also includes the error handling in case the user input is not valid.

    @param passengerInfo = A struct where all passengers' information are stored.
    @param userInfo = A struct where all the loaded information are stored.
    @param nPassengerMenu2Choice = An integer that stores the user's choice of the menu 2.
    @param nCountPassenger = The number of how many passengers registered in the embarkation card
    @param nCapacityNum = An array of integer that stores the amount of passengers on a trip.
    @param dropOffPointCount = A 2D array for storing the number of passengers who dropped off at a specific drop off point
    @param seatPrioNum = A 2D Array for storing the passenger's priority number according to their trip 
    @param fileStatusLoad = A boolean variable to check if the file is loaded or not.
    @param fileStatusCount = A variable to count the number of passengers in the txt file.
    @param nMonth = A integer variable for getting the month of the date of the whole system.
    @param nDay = A integer variable for getting the day of the date of the whole system.
    @param nYear = A integer variable for getting the year of the date of the whole system.
    @param seatNumber = A string variable for storing the seat number of the passenger.
    @param validTripNumber = The array of valid trip numbers
    @param validTripNumberLaguna = A string array where all the valid trip numbers of Laguna are stored.
    @param validTripNumberManila = A string array where all the valid trip numbers of Manila are stored.
    @param validEmbarkPointLaguna = A string variable for all the valid embarkation point in Laguna
    @param validEmbarkPointManila = A string variable for all the valid embarkation point in Manila
    @param validDropOffPointLaguna = A string variable of all the valid drop off points in Laguna
    @param validDropOffPointManila = A string variable for all the valid drop off points in Manila
    @return = None

    Pre-condition = A passenger did not repeat embarking in the same day.
                    ID Number is valid.

*/
int inputEmbarkation( Passenger passengerInfo[320],
                      User userInfo[320],
                      char nPassengerMenu2Choice, 
                      int nCountPassenger, 
                      int nCapacityNum[][16], 
                      int dropOffPointCount[][16],
                      int seatPrioNum[][16],
                      int fileStatusLoad,
                      int fileStatusCount,
                      int nMonth,
                      int nDay,
                      int nYear,
                      int seatNumber[16],
                      String30 validTripNumber[20],
                      String30 validTripNumberLaguna[11],
                      String30 validTripNumberManila[9],
                      String99 validEmbarkPointLaguna[4], 
                      String99 validEmbarkPointManila[2], 
                      String99 validDropOffPointLaguna[4], 
                      String99 validDropOffPointManila[3] )
{

    int i, j; //Local variables for loops

    int nSuccess = 0; //Variable for do-while loop

    int nCountIdNum = 0; //Variable for ID Number

    int nCountDate = 0; //Variable for Date

    int statusEmbark = 0; //Variable for checking if the embarkation is signed or not

    //PLACES
    //[1] = Manila
    //[2] = Laguna
    int nPlace = 0; //Variable for determining if the passenger is in Laguna or Manila

    String99 tripNumber; //Variable for user input of trip number
    String99 loadTripNumber; //Variable to say that embark function should get the txt file infomation

    int checkCapacity = 0;  //Variable for the status of a trip if its full or still available
    
    String30 tempFullName; //Variable for storing the full name of the passenger
    int nameLen = 0; // Variable for storing the length of the full name to be used in the for loop
    int nameCount = 0; // Variable for counting the number of invalid characters in the full name
        
        if ( statusEmbark == 0 ) //If the passenger is yet to sign up for the trip
        {
            do //LOOP FOR TRIP NUMBER UNTIL VALID
            {

                if ( fileStatusLoad == 1 ) //If the function is called in the load section of the personel.
                {
                    strcpy(passengerInfo[nCountPassenger].tripNumber, userInfo[nCountPassenger].userTripNumber);
                }
                else
                {
                    displaySchedule();
                    printf("\n[Trip Number]: ");
                    scanf(" %[^\n]s", passengerInfo[nCountPassenger].tripNumber);
                }

                strcpy(tripNumber, passengerInfo[nCountPassenger].tripNumber);   
                
                for ( j = 0; j < 20; j++ )
                {
                    if ( strcmpi(passengerInfo[nCountPassenger].tripNumber, validTripNumber[j]) == 0 )
                    {
                        for ( i = 0; i < 11; i++ )
                        {
                            if ( strcmpi(passengerInfo[nCountPassenger].tripNumber, validTripNumberLaguna[i]) == 0 ) //If the trip number is valid in Laguna
                            {
                                printf("[SUCCESS] Trip number is VALID.\n");
                                nPlace = 2;
                                statusEmbark++;
                                nSuccess = 1;
                                i = 11;
                                j = 20;
                            }
                        }

                        for ( i = 0; i < 9; i++ )
                        {
                            if ( strcmpi(passengerInfo[nCountPassenger].tripNumber, validTripNumberManila[i]) == 0 ) //If the trip number is valid in Manila
                            {
                                printf("[SUCCESS] Trip number is VALID.\n");
                                nPlace = 1;
                                statusEmbark++;
                                nSuccess = 1;
                                i = 9;
                                j = 20;
                            }
                        }
                            
                    }

                }
                
            }while( nSuccess == 0 );
        }

        if ( statusEmbark == 1 ) //If the passenger is done putting in their trip number
        {
            do //LOOP FOR EMBARKATION POINT UNTIL VALID
            {   
                nSuccess = 0;

                if ( fileStatusLoad == 1 ) //If the function is called in the load section of the personel.
                {
                    strcpy(passengerInfo[nCountPassenger].embarkPoint, userInfo[nCountPassenger].userEmbarkPoint);
                }
                else
                {
                    
                    if ( nPlace == 2 )
                    {
                        printf("\n========================================================\n\n");
                        printf("[EMBARKATION POINTS FOR LAGUNA]\n\n");

                        for ( j = 0; j < 4; j++ )
                        {
                            printf("[%s]", validEmbarkPointLaguna[j]);
                            printf("\n");
                        }

                        printf("\n========================================================\n");

                    }
                    else if ( nPlace == 1 )
                    {
                        printf("\n========================================================\n\n");
                        printf("[EMBARKATION POINTS FOR MANILA]\n\n");

                        for ( j = 0; j < 2; j++ )
                        {
                            printf("[%s]", validEmbarkPointManila[j]);
                            printf("\n");
                        }

                        printf("\n========================================================\n");
                    }

                    printf("\n[Embarkation Point]: ");
                    scanf(" %[^\n]s", passengerInfo[nCountPassenger].embarkPoint);

                }

                for ( j = 0; j < 4; j++ )
                {
                    if ( strcmpi(passengerInfo[nCountPassenger].embarkPoint, validEmbarkPointLaguna[j]) == 0 && nPlace == 2) //If the embarkation point is valid in Laguna
                    {
                        printf("[SUCCESS] Embarkation Point is VALID.\n");
                        statusEmbark++;
                        nSuccess = 1;
                        nPlace = 2;
                        j = 4;
                    }

                }

                for ( j = 0; j < 2; j++ )
                {
                    if ( strcmpi(passengerInfo[nCountPassenger].embarkPoint, validEmbarkPointManila[j]) == 0 && nPlace == 1) //If the embarkation point is valid in Manila
                    {
                        printf("[SUCCESS] Embarkation Point is VALID.\n");
                        statusEmbark++;
                        nSuccess = 1;
                        nPlace = 1;
                        j = 2;
                    }
                }


            }while( nSuccess == 0 );
        }


        if ( statusEmbark == 2 ) //If the passenger is done putting in their embarkation point
        {
            do //LOOP FOR PASSENGER NAME UNTIL VALID
            {
                nSuccess = 0;
                
                if ( fileStatusLoad == 1 ) //If the function is called in the load section of the personel.
                {
                    strcpy(passengerInfo[nCountPassenger].passengerFirstName, userInfo[nCountPassenger].userFirstName);
                    strcpy(passengerInfo[nCountPassenger].passengerLastName, userInfo[nCountPassenger].userLastName);
                }
                else
                {
                    printf("\n[NOTE]: FIRST and LAST Name only.");
                    printf("\n[Passenger Full Name]: ");
                    scanf(" %s %[^\n]s", passengerInfo[nCountPassenger].passengerFirstName, passengerInfo[nCountPassenger].passengerLastName);	
                }
        
                strcpy(tempFullName, passengerInfo[nCountPassenger].passengerFirstName); //Storing the first name of the passenger in tempFullName
                strcat(tempFullName, passengerInfo[nCountPassenger].passengerLastName); //Storing the last name of the passenger in tempFullName
                nameLen = strlen(tempFullName); //Storing the length of the full name
                
                //IF TEMPFULLNAME HAS A SPECIAL CHARACTER OR NUMBERS, IT ASK FOR A NEW NAME

                for ( i = 0; i < nameLen; i++ )
                {
                    if ( tempFullName[i] >= '!' && tempFullName[i] <= '@' || 
                        tempFullName[i] >= '[' && tempFullName[i] <= '`' || 
                        tempFullName[i] >= '{' && tempFullName[i] <= '~' ) //If the name has a special character or number
                    {
                        printf("[ERROR] Passenger Name has a SPECIAL CHARACTER.\n");
                        nameCount = nameCount + 1;
                        nSuccess = 0;
                        i = nameLen;

                    }
                    else //If the name has no special character or number
                    {
                        nameCount = 0;
                    }
                }

                if ( nameCount == 0 )  //If the name has no special character or number
                {
                    printf("[SUCCESS] Passenger Name is VALID.\n");
                    statusEmbark++;
                    nSuccess = 1;
                }
                
        
            }while ( nSuccess == 0 );
        }


        if ( statusEmbark == 3 ) //If the passenger is done putting in their name
        {
            do //LOOP FOR ID NUMBER UNTIL VALID
            {

                if ( fileStatusLoad == 1 )
                {
                    passengerInfo[nCountPassenger].idNum = userInfo[nCountPassenger].userIdNum;
                }
                else
                {
                    printf("\n[ID Number]: ");
                    scanf(" %d", &passengerInfo[nCountPassenger].idNum);
                    while ((getchar()) != '\n');
                }

                if ( passengerInfo[nCountPassenger].idNum > 10000000 && passengerInfo[nCountPassenger].idNum < 99999999 ) //This is to check if the ID number is within 8 digits or atleast 8 digits.
                {
                    printf("[SUCCESS] ID Number is VALID.\n");
                    statusEmbark++;
                    nSuccess = 1;
                    nCountIdNum = 0;
                }
                else
                {
                    nCountIdNum = 1; //If the ID number is not within 8 digits, this will be 1 as it indicates that it is not within 8 digits or less than 8 digits.
                }
                        
            }while( nCountIdNum != 0 );
        }
        
        if ( statusEmbark == 4 ) //If the passenger is done putting in their ID number
        {
            do //LOOP FOR PRIORITY NUMBER UNTIL VALID
            {
                nSuccess = 0;
                
                if ( fileStatusLoad == 1 )
                {
                    passengerInfo[nCountPassenger].prioNum = userInfo[nCountPassenger].userPrioNum;
                }
                else
                {
                    displayPriorityInfo();

                    printf("\n[Priority Number]: ");
                    scanf(" %d", &passengerInfo[nCountPassenger].prioNum);
                    while ((getchar()) != '\n');
                }

                if ( passengerInfo[nCountPassenger].prioNum < 1 || passengerInfo[nCountPassenger].prioNum > 6 ) //If the priority number is lower than 1 or higher than 6
                {   
                    nSuccess = 0;
                }
                else if ( passengerInfo[nCountPassenger].prioNum >= 1 && passengerInfo[nCountPassenger].prioNum <= 6 ) //If the priority number is within 1 and 6
                {
                    printf("[SUCCESS] Priority Number is VALID.\n");

                    for ( i = 0; i < 320; i++ )
                    {
                        for ( j = 0; j < 20; j++ )
                        {
                            if ( strcmpi(passengerInfo[i].tripNumber, validTripNumber[j]) == 0 ) //This is getting the index of what trip number the passenger is embarking on.
                            {
                                seatPrioNum[j][nCountPassenger] = passengerInfo[nCountPassenger].prioNum; //This is getting the priority number of the passenger.
                                j = 20;
                                i = 320;
                            }
                        }
                    }   

                    statusEmbark++;
                    nSuccess = 1;
                }

            }while( nSuccess == 0 );
        }
    
        if ( fileStatusLoad == 1 )
        {
            userInfo[nCountPassenger].userDate.nMonth = nMonth;
            userInfo[nCountPassenger].userDate.nDay = nDay;
            userInfo[nCountPassenger].userDate.nYear = nYear;
            
            passengerInfo[nCountPassenger].date.nMonth = userInfo[nCountPassenger].userDate.nMonth;
            passengerInfo[nCountPassenger].date.nDay = userInfo[nCountPassenger].userDate.nDay;
            passengerInfo[nCountPassenger].date.nYear = userInfo[nCountPassenger].userDate.nYear;

        }
        else
        {
            passengerInfo[nCountPassenger].date.nMonth = nMonth;
            passengerInfo[nCountPassenger].date.nDay = nDay;
            passengerInfo[nCountPassenger].date.nYear = nYear;
            
        }
        
        printf("[SUCCESS] Date of Trip: %.2d-%.2d-%d.\n", passengerInfo[nCountPassenger].date.nDay, passengerInfo[nCountPassenger].date.nMonth, passengerInfo[nCountPassenger].date.nYear);

        if( statusEmbark == 5 )
        { 
            do //LOOP FOR DROP-OFF POINT UNTIL VALID
            {
                nSuccess = 0;

                if ( fileStatusLoad == 1 )
                {
                    strcpy(passengerInfo[nCountPassenger].dropOffPoint, userInfo[nCountPassenger].userDropOffPoint);
                }
                else
                {
                    if ( nPlace == 2 )
                    {
                        printf("\n========================================================\n\n");
                        printf("[DROP-OFF POINTS FOR LAGUNA]\n\n");

                        for ( j = 0; j < 4; j++ )
                        {
                            printf("[%s]", validDropOffPointLaguna[j]);
                            printf("\n");
                        }

                        printf("\n========================================================\n");

                    }
                    else if ( nPlace == 1 )
                    {
                        printf("\n========================================================\n\n");
                        printf("[DROP-OFF POINTS FOR MANILA]\n\n");

                        for ( j = 0; j < 3; j++ )
                        {
                            printf("[%s]", validDropOffPointManila[j]);
                            printf("\n");
                        }

                        printf("\n========================================================\n");
                    }

                    printf("\n[Drop-Off Point]: ");
                    scanf(" %[^\n]s", passengerInfo[nCountPassenger].dropOffPoint);
                }
                
                switch ( nPlace )
                {
                    //Laguna Drop Off Point
                    case 1:
                        for ( j = 0; j < 3; j++ )
                        {
                            if ( strcmpi(passengerInfo[nCountPassenger].dropOffPoint, validDropOffPointManila[j]) == 0 ) //This getting the index of the drop off point for Laguna
                            {
                                printf("[SUCCESS] Drop-Off Point is VALID.\n");
                                countDropOffPoint( passengerInfo[nCountPassenger].dropOffPoint, passengerInfo[nCountPassenger].tripNumber, dropOffPointCount, validDropOffPointLaguna, validDropOffPointManila, validTripNumber, 0 );
                                j = 3;
                                statusEmbark++;
                                nSuccess = 1;
                            }
                        }
                        break;
    
                    //Manila Drop Off Point
                    case 2:

                        for ( j = 0; j < 4; j++ )
                        {
                            if ( strcmpi(passengerInfo[nCountPassenger].dropOffPoint, validDropOffPointLaguna[j]) == 0 ) //This getting the index of the drop off point for Manila
                            {
                                printf("[SUCCESS] Drop-Off Point is VALID.\n");
                                countDropOffPoint( passengerInfo[nCountPassenger].dropOffPoint, passengerInfo[nCountPassenger].tripNumber, dropOffPointCount, validDropOffPointLaguna, validDropOffPointManila, validTripNumber, 0 );
                                j = 4;
                                statusEmbark++;
                                nSuccess = 1;
                            }
                        }
                        break;
                } 
                           
            }while( nSuccess == 0 );
        }


        if ( statusEmbark == 0 && fileStatusLoad == 1 )
        {
            printf("[ERROR] Please try again.\n");

            return 0;
        }
        else if ( statusEmbark == 6 && fileStatusLoad == 1 || statusEmbark == 6 && fileStatusLoad == 0) //If embark function did not detect error, then the function will continue in scanning the trip number for capacity.
        {
            for ( i = 0; i < 20; i++ )
            {
                if ( strcmpi(passengerInfo[nCountPassenger].tripNumber, validTripNumber[i]) == 0 ) //This is getting the index of what trip number the passenger is embarking on.
                {
                    checkCapacity = checkTripCapacity(tripNumber, nCapacityNum[i], validTripNumber); //This is checking the capacity of the trip.
                    i = 20;
                }
            }            

            if ( checkCapacity == 1 ) //If the trip is full, then the function will display error.
            {

                printf("\n[ERROR] Trip Number is FULL.\n");
                printf("[ERROR] Please choose another trip.\n");
                printf("[SYSTEM] Hi! [%s %s], please re-enter your information.\n", passengerInfo[nCountPassenger].passengerFirstName, passengerInfo[nCountPassenger].passengerLastName);
                countDropOffPoint( passengerInfo[nCountPassenger].dropOffPoint, passengerInfo[nCountPassenger].tripNumber, dropOffPointCount, validDropOffPointLaguna, validDropOffPointManila, validTripNumber, 1);
                return 0;
            }
            else //If the trip is not full, return 1
            {
                return 1;
            }
            
        }

}

void displayPassengerMenu()
{
    printf("========================================================\n\n");
    printf("[PASSENGER FEATURES]\n\n");
    printf("[1] Embark Now!\n");
    printf("[2] View Schedule\n");
    printf("[3] Back\n");
    printf("\n========================================================\n");

}


/*  
    choicePassengerMenu a function that ask for an input from the user and return it to the main function. This is only for the Passenger Menu

    @param = None
    @return = Returns a number from 1 to 3.

    Pre-condition = None
*/
int choicePassengerMenu()
{
    int nPassengerMenuChoice = 0; //Local Variable for user input

    displayPassengerMenu(); //A function to display the passenger menu
    
    if ( nPassengerMenuChoice < 1 || nPassengerMenuChoice > 3 ) //If statement for limiting user to input from numbers 1 to 3
    {
        scanf(" %d", &nPassengerMenuChoice);
        while ((getchar()) != '\n');
    }

    return nPassengerMenuChoice; //Returns the user input
}

/*
    writeEmbarkation is a function that will write the passenger information to the embarkation card.txt file

    @param passengerInfo = This is the array of passenger information
    @param nCountPassenger = The number of how many passengers registered in the embarkation card
    @param fp = This is the file pointer for the embarkation card.txt file
    @return = None

    Pre-condition = None
*/
void writeEmbarkation ( Passenger passengerInfo[320], 
                        int nCountPassenger,  
                        FILE *fp )
{
    int i = 0;

    fp = fopen("EmbarkationCard.txt", "a");

    //print the newly embarked passenger into the embarkationcard.txt file
    fprintf(fp, "%s\n", passengerInfo[nCountPassenger].tripNumber);
    fprintf(fp, "%s\n", passengerInfo[nCountPassenger].embarkPoint);
    fprintf(fp, "%s %s\n", passengerInfo[nCountPassenger].passengerFirstName, passengerInfo[nCountPassenger].passengerLastName);
    fprintf(fp, "%d\n", passengerInfo[nCountPassenger].idNum);
    fprintf(fp, "%d\n", passengerInfo[nCountPassenger].prioNum);
    fprintf(fp, "%s\n", passengerInfo[nCountPassenger].dropOffPoint);
    fprintf(fp, "\n\n");

    fclose(fp);
        
}