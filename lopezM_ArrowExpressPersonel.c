#include <stdio.h>
#include <string.h>

/*  
    displayLoadMenu is a function that displays the load menu and returns the user's choice.

    @param None
    @return nChoice = the user's choice

    Pre-condition = None
*/
int displayLoadMenu()
{

    int nChoice = 0;

    do
    {
        printf("========================================================\n\n");
        printf("[1] Embarkation Card\n");
        printf("[2] Past Trip\n");
        printf("[3] Back\n");
        printf("\n========================================================\n");

        scanf(" %d", &nChoice);
        while ((getchar()) != '\n');

    }while( nChoice < 1 || nChoice > 3 );
    
    return nChoice;  
}

void displayArrowExpressMenu()
{

    printf("========================================================\n\n");
    printf("[ARROW EXPRESS PERSONEL FEATURE]\n\n");
    printf("[1] View the capacity of a trip\n");
    printf("[2] View a trip with a counter for the drop-off points\n");
    printf("[3] View passengers' information of a trip\n");
    printf("[4] Load passenger information\n");
    printf("[5] Search a passenger\n");
    printf("[6] View a file\n");
    printf("[7] Back\n");
    printf("\n========================================================\n");
}

/*  
    viewPassengersInfo is a function to view all the passengers to be seen in the terminal according to their priority number.

    @param passengerInfo = A struct where all passengers' information are stored.
    @param userTripNumber = A string variable where it stores the user input 

    Pre-condition = None
*/
void viewPassengersInfo( Passenger passengerInfo[320], 
                         String30 userTripNumber )
{
    int i, j; //Local Variables

    Passenger temp; //Variable for temporary structures

    printf("\n[TRIP NUMBER]: [%s]\n", userTripNumber); //Display the user input trip number

    for (i = 0; i < 320; i++) //A loop for scanning all the passenger info in the structure
    {
        for (j = i + 1; j < 320; j++) //A loop for scanning all the the next passenger info in the structure
        {
            if (passengerInfo[i].prioNum > passengerInfo[j].prioNum) //If, the recent passenger's priority number is greater than the next passenger's priority number.
            {
                temp = passengerInfo[i];
                passengerInfo[i] = passengerInfo[j]; 
                passengerInfo[j] = temp;
                
            }
        }
    }

    for ( i = 0; i < 320; i++ ) //A loop for scanning all the passenger info in the structure
    {
        if ( strcmpi(passengerInfo[i].tripNumber, userTripNumber) == 0 ) //If, a passenger's trip number is the same with a valid trip number. It will print the information of that passenger.
        { 
            printf("\n[Embarkation Point] - [%s]", passengerInfo[i].embarkPoint);
            printf("\n[Name] - [%s %s]", passengerInfo[i].passengerFirstName, passengerInfo[i].passengerLastName);
            printf("\n[I.D Number] - [%d]", passengerInfo[i].idNum);
            printf("\n[Priority Number] - [%d]", passengerInfo[i].prioNum);
            printf("\n[Date of Trip] - [%.2d-%.2d-%d]", passengerInfo[i].date.nDay, passengerInfo[i].date.nMonth, passengerInfo[i].date.nYear);
            printf("\n[Drop-Off Point] - [%s]", passengerInfo[i].dropOffPoint);
            printf("\n");
        }
    }

    printf("\n");

}

/*  
    viewCountOfPassengers is a function to display the seats available and the capacity of a trip to be seen in the terminal.

    @param passengerInfo = A struct where all passengers' information are stored
    @param nCapacityNum = An array of integer containing the numbers of seats in each trip.
    @param validTripNumber = A string array where all the valid trip numbers are stored.
    @param allTrips = A string array where all the trip numbers are stored.

    Pre-condition = None
*/
void viewCountOfPassengers( String30 userTripNumber, 
                            int nCapacityNum[], 
                            String30 validTripNumber[20],
                            char allTrips[] )
{
    int i, j; //Local Variable

    for ( i = 0; i < 20; i++ ) //A Loop for scanning all the valid trip number
    {
        if ( strcmpi(validTripNumber[i], userTripNumber) == 0 ) //If, the user input trip number is the same with a valid trip number, it will display the number of passengers inside that trip.
        {
            printf("\n[TRIP NUMBER]: [%s]\n", validTripNumber[i]);
            printf("[Number of Passengers]: [%d]\n\n", nCapacityNum[i]);
            i = 20;
        }
    }
    
    //A loop for displaying all the seats.
    for ( i = 0; i < 20; i++ )
    {
        if ( nCapacityNum[i] <= 13 )
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
        else
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


    printf("\n\n");

}
/*  
    getTripNumber is a function to get the trip number index to be passed on to viewCountOfPassengers function

    @param userTripNumber = A string variable where it stores the user input
    @param nCapacityNum = An array of integer containing the numbers of seats in each trip.
    @param validTripNumber = A string array where all the valid trip numbers are stored.
    @param allTrips = A string array where all the trip numbers are stored.

    Pre-condition = None
*/
void getTripNumber( String30 userTripNumber,
                    int nCapacityNum[][16],
                    String30 validTripNumber[20],
                    char allTrips[][16])
{
    int i; //Local Variable

    for ( i = 0; i < 20; i++ ) //A loop for scanning all the valid trip number  
    {
        if ( strcmpi(userTripNumber, validTripNumber[i]) == 0 ) //If, the latest passenger has the the same trip number with a valid trip number. He/she will be assign to a seat.
        {
            viewCountOfPassengers( userTripNumber, nCapacityNum[i], validTripNumber, allTrips[i]);
            i = 20;
        }
    }

}

/*  
    searchPassenger is a function to view a specific passenger with the last name from the user input

    @param passengerInfo = A struct where all passengers' information are stored.
    @param userLastName = A string where it stores the last name being inputted by the user from the main function

    Pre-condition = None
*/
void searchPassenger( Passenger passengerInfo[320], 
                      String30 userLastName )
{
    int i; //Local Variable

    for ( i = 0; i < 320; i++ ) //A loop for scanning all the passengers' information
    {
        if ( strcmpi(passengerInfo[i].passengerLastName, userLastName) == 0 ) //If, A passenger's last name with the last name inputted by the user. It will print his/her information.
        {
            printf("\n[Trip Number] - [%s]", passengerInfo[i].tripNumber);
            printf("\n[Embarkation Point] - [%s]", passengerInfo[i].embarkPoint);
            printf("\n[Name] - [%s %s]", passengerInfo[i].passengerFirstName, passengerInfo[i].passengerLastName);
            printf("\n[I.D Number] - [%d]", passengerInfo[i].idNum);
            printf("\n[Priority Number] - [%d]", passengerInfo[i].prioNum);
            printf("\n[Date of Trip] - [%.2d-%.2d-%d]", passengerInfo[i].date.nDay, passengerInfo[i].date.nMonth, passengerInfo[i].date.nYear);
            printf("\n[Drop-Off Point] - [%s]", passengerInfo[i].dropOffPoint);
            printf("\n");
        }
    }

    printf("\n");
}

/*  
    viewCountOfPassengerDropOff is where the user will view the passengers who dropped off at a certain drop-off point per trip.

    @param passengerInfo = A struct where all passengers' information are stored.
    @param passengerTripNumber = A string where it stores the trip number being inputted by the user from the embarkation card
    @param dropOffPointCount = A 2D Array for storing all the counts of drop off points in a specific trip
    @param validTripNumber = A string array where all the valid trip numbers are stored.
    @param validTripNumberLaguna = A string array where all the valid trip numbers of Laguna are stored.
    @param validTripNumberManila = A string array where all the valid trip numbers of Manila are stored.
    @param validDropOffPointLaguna = A string array where all the the valid drop off points of Laguna are stored.
    @param validDropOffPointManila = A string array where all the the valid drop off points of Manila are stored.


    Pre-condition = None
*/
void viewCountOfPassengerDropOff( Passenger passengerInfo[320], 
                                  String30 passengerTripNumber,
                                  int dropOffPointCount[][16],
                                  String30 validTripNumber[20],
                                  String30 validTripNumberLaguna[11],
                                  String30 validTripNumberManila[9],
                                  String99 validDropOffPointLaguna[4],
                                  String99 validDropOffPointManila[3] )
{

    int i, x, j, y;
    
    printf("\n[TRIP NUMBER]: [%s]\n", passengerTripNumber);

    for ( i = 0; i < 320;  i++ )
    {
        if ( strcmpi(passengerTripNumber, passengerInfo[i].tripNumber) == 0) //If the user input is the same with a passenger/s trip number. Proceed
        {
            for ( y = 0; y < 11; y++ )
            {
                if ( strcmpi(passengerInfo[i].tripNumber, validTripNumberLaguna[y]) == 0 ) //If the trip number is within the trip numbers of Laguna. Proceed
                {
                    for ( x = 0; x < 20; x++ )
                    {
                        if ( strcmpi(passengerTripNumber, validTripNumber[x]) == 0 ) //If the user input is the same with a trip number. Proceed
                        {
                            for ( j = 0; j < 4; j++ )
                            {
                                printf("\n[%s]: [%d]", validDropOffPointLaguna[j], dropOffPointCount[x][j]); //This displays all the drop off points of Laguna and the count of how many is going to that drop off point.
                                i = 320;
                            }
                        }
                    }
                }
            }

            
            for ( y = 0; y < 9; y++ )
            {
                if ( strcmpi(passengerInfo[i].tripNumber, validTripNumberManila[y]) == 0 )
                {
                    for ( x = 0; x < 20; x++ )
                    {
                        if ( strcmpi(passengerTripNumber, validTripNumber[x]) == 0 )
                        {
                            for ( j = 0; j < 3; j++ )
                            {
                                printf("\n[%s]: [%d]", validDropOffPointManila[j], dropOffPointCount[x][j]); 
                                i = 320;
                            }
                        }
                    }
                }
            }

        }

    }

    printf("\n\n");

    

}
