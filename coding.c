#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
struct BusRoute {
    int routeNumber;
    char source[50];
    char destination[50];
    float regularFare;
    float studentFare;
};
void userMenu();
void displayUserLogins();
int isRouteExists(int routeNumber);

#define MAX_ROUTES 100
struct BusRoute busRoutes[MAX_ROUTES];
int routeCount = 0;
FILE *fp;
char filename[20];
struct user_login{
	char name[20];
    char password[20];
}user;
int admin_login() {
   system("cls");
   printf("\033[92m");
    printf("\n\n\n\t\t\t\t\t\t\t\t*-*-ADMIN LOGIN-*-*");
    printf("\n\t\t\t\t\t\t\t\033[1;96m    <-------------------------->\033[0m\n\n ");
    char adminname[20], password[20];
    printf("\n\n\t\t\t Admin Username: ");
    scanf("%s", adminname);
    printf("\n\t\t\t Password: ");
    scanf("%s", password);
    if (strcmp(adminname, "admin") == 0 && strcmp(password, "admin") == 0) {
        return 1; 
    } else {
    	printf("\033[1;31m"); // Set text color to red
        printf("\n\n\t\t\t\t\t\tLogin failed.\n");
        printf("\033[0m"); // Reset text color to default
        while (getchar() != '\n') {
            // Discard characters until a newline is encountered
        }
        printf("\n\n\t\t\t\t\t\tPress enter to go back....");
        getch();
        return 0;
    }
}
void register_user() {
    system("cls");
     printf("\033[92m");
     printf("\n\n\n\t\t\t\t\t\t\t\t*-*-REGISTRATION-*-*");
    printf("\n\t\t\t\t\t\t\t   \033[1;96m <------------------------->\033[0m\n\n ");
    printf("\n\n\n\n\t\t\t\t \x1b[36m ~~Enter the details~~\033[0m  ");
    printf("\n\n\t\t\t\t Username:");
    scanf("%s", user.name);
    FILE *checkFile = fopen("user_data.txt", "r");
    char check[20];
    int usernameTaken = 0; // Flag to check if the username is already taken
    while (fscanf(checkFile, "%s", check) != EOF) {
        if (strcmp(check, user.name) == 0) {
            usernameTaken = 1;
            break;
        }
    }
    fclose(checkFile);
    if (usernameTaken) {
        printf("\n\n\n\n\t\t\t\t\033[1;96m Username already taken, please choose another:\033[0m");
        getch();
        register_user();
    }
    printf("\n\t\t\t\tEnter password:\t");
    scanf("%s", user.password);
    while (1) {
        if (strlen(user.password) < 6) {
            printf("\n\n\t\t\t\t\t\033[1;96m Too short! Enter password again:\033[0m");
            scanf("\n%s", user.password);
        } else {
            break;
        }
    }
    FILE *fp = fopen("user_data.txt", "a");
    if (fp == NULL) {
        printf("\n\n\t\t\t\t\tError opening user data file for writing.\n");
        return;
    }
    fprintf(fp, "%s %s\n", user.name, user.password);
    fclose(fp);
    system("cls");
    printf("\n\n\n\t\033[1;96mCheck user: \033[0m");
    printf("\n\n\t\t\tUSERNAME:\t%s", user.name);
    printf("\n\n\t\t\tPASSWORD:\t%s", user.password);
    char y_n;
    printf("\n\n\n\n\n\t\t\t\tWant to enter again? (y/n): ");
    if ((y_n = getch()) == 'y') {
        register_user();
    } else if (y_n == 'n') {
        printf("\033[1;32m"); // Green text
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\tSuccessfully registered!\n");
        printf("\n\n\n\n\t\t\t\t\t\t\t\t Welcome, %s!", user.name);
        printf("\033[0m"); // Reset text color to default
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t Enter any key to continue.....");
        getch();
        userMenu();
    }
}
void already_user() {
    system("cls");
    char name_sign[20];
    char password_sign[20];
    char read_name[20];
    char read_password[20];
        printf("\033[92m");	
        printf("\n\n\n\t\t\t\t\t\t\t\t*-*-MEMBER SIGN IN-*-*");
        printf("\n\t\t\t\t\t\t\t   \033[1;96m <----------------------------->\033[0m\n\n ");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tUSERNAME: ");
    scanf("%19s", name_sign); 
    fp = fopen("user_data.txt", "r");
    int user_found = 0; // Flag to check if the user was found
    while (fscanf(fp, "%s %s", read_name, read_password) != EOF) {
        if (strcmp(name_sign, read_name) == 0) {
            printf("\n\t\t\t\t\t\tPASSWORD: ");
            scanf("%19s", password_sign);
            if (strcmp(password_sign, read_password) == 0) {
                printf("\033[1;32m"); // Green text
                printf("\n\n\n\t\t\t\t\t\t\t\t~~Log in successful~~");
                printf("\n\n\t\t\t\t\t\t\t\t~~WELCOME %s!~~", name_sign);
                printf("\033[0m"); // Reset text color to default
                printf("\n\n\n\n\n\t\t\t\t\t\t\t\tEnter any key to continue.....");
                getch();
                strcpy(user.name, name_sign);
                strcpy(user.password, password_sign);
                fclose(fp);
                userMenu();
                return;
            } else {
                printf("\033[1;31m"); // Red text
                printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWrong password!");
                printf("\033[0m"); // Reset text color to default
                printf("\n\n\n\t\t\t\t\t\t\t1. Try Again");
                printf("\n\t\t\t\t\t\t\t2. Back");
                  printf("\n\n\n\n\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m ");
                char choice = getch();
                switch (choice) {
                    case '1':
                    	already_user();
                        break;
                    case '2':
                         return;
                    default:
                        printf("\033[1;31m"); // Red text
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
                        printf("\033[0m"); // Reset text color to default
                }
            }
        }
    }
    printf("\033[1;31m"); // Red text
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tYou have not registered!");
    printf("\033[0m"); // Reset text color to default
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t1. Register");
    printf("\n\t\t\t\t\t\t\t\t2. Back");
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m");
    char choice = getch();
    switch (choice) {
        case '1':
            fclose(fp);
            register_user();
            break;
        case '2':
            fclose(fp);
            return; // Go back to the main menu
        default:
            printf("\033[1;31m"); // Red text
           printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
            printf("\033[0m"); // Reset text color to default
    }
    fclose(fp);
}
void addRoute() {
    system("cls");
    printf("\033[1;91m");
    printf("\n\n\n\n\n\t\t\t\t\t  *-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
    printf("\033[1;92m");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t        =               ADD NEW ROUTE                =");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\033[1;91m");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\033[37m");
    struct BusRoute newRoute;
    printf("\n\n\n\n\n\t\t\t\t\t\033[1;96mEnter Route Number:\033[0m ");
    scanf("%d", &newRoute.routeNumber);
    if (isRouteExists(newRoute.routeNumber)) {
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\033[1;91mRoute with number %d already exists!:\033[0m\n", newRoute.routeNumber);
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue...");
        getch();
        return; 
    }
    printf("\n\t\t\t\t\t\033[1;96mEnter Source:\033[0m ");
    scanf("%s", newRoute.source);
    printf("\n\t\t\t\t\t\033[1;96mEnter Destination:\033[0m");
    scanf("%s", newRoute.destination);
    printf("\n\t\t\t\t\t\033[1;96mEnter Regular Fare:\033[0m ");
    scanf("%f", &newRoute.regularFare);
    printf("\n\t\t\t\t\t\033[1;96mEnter Student Fare (with discount):\033[0m ");
    scanf("%f", &newRoute.studentFare);
    FILE *fp = fopen("bus_routes.txt", "a");
    fprintf(fp, "%d %s %s %.2f %.2f\n", newRoute.routeNumber, newRoute.source, newRoute.destination, newRoute.regularFare, newRoute.studentFare);
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t\033[92mRoute added successfully!\033[0m");
    printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...");
    getch();
}
int isRouteExists(int routeNumber) {
    FILE *fp = fopen("bus_routes.txt", "r");
    struct BusRoute route;
    while (fscanf(fp, "%d %s %s %f %f", &route.routeNumber, route.source, route.destination, &route.regularFare, &route.studentFare) != EOF) {
        if (route.routeNumber == routeNumber) {
            fclose(fp);
            return 1; 
        }
    }
    fclose(fp);
    return 0; 
}
void displayRoute() {
    do{
	system("cls");
    printf("\033[1;91m");
    printf("\n\n\n\n\n\n\t\t\t\t\t  *-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
    printf("\033[1;92m");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t        =             AVAILABLE BUS ROUTES           =");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\033[1;91m");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\033[37m");
    FILE *fp = fopen("bus_routes.txt", "r");
    if (fp == NULL) {
        printf("\n\n\n\n\t\t\t\t\t\t\t\033[1;31m       No routes available. \033[0m\n\n");
        printf("\n\n\n\n\t\t\t\t\t\t\t\tPress any key to continue...");
        getch();
        return;
    }
    struct BusRoute route;
    printf("\n\n\n\n\n\n\t\t\t\t\033[1;96m%-15s  %-30s%-30s%-15s  %-15s\n\033[0m", "Route Number", "Source", "Destination", "Regular Fare", "Student Fare");
    printf("\t\t\t\033[1;96m       --------------   --------                      -------------                 --------------   --------------\033[0m\n\n");
    while (fscanf(fp, "%d %s %s %f %f", &route.routeNumber, route.source, route.destination, &route.regularFare, &route.studentFare) != EOF) {
        printf("\t\t\t\t%-15d  %-30s%-30s%-15.2f  %-15.2f\n", route.routeNumber, route.source, route.destination, route.regularFare, route.studentFare);
    }
printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue.....");
    fclose(fp);}
    while(getch()==0);
}
void deleteRoute() {
    system("cls");
    printf("\033[1;91m");
    printf("\n\n\n\n\n\t\t\t\t\t  *-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
     printf("\033[1;92m");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t        =             DELETE BUS ROUTE                =");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\033[1;91m");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\033[37m");
    char sourceToDelete[50];
    char destinationToDelete[50];
    int found = 0;
    printf("\n\n\n\n\n\t\t\t\t\t\033[1;96mEnter Source:\033[0m ");
    scanf("%s", sourceToDelete);
    printf("\n\t\t\t\t\t\033[1;96mEnter Destination:\033[0m");
    scanf("%s", destinationToDelete);
    FILE *inputFile = fopen("bus_routes.txt", "r");
    if (inputFile == NULL) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\033[1;91mError opening the file!\033[0m\n");
        exit(1);
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\033[1;91mError opening the temporary file!\033[0m\n");
        fclose(inputFile);
        exit(1);
    }
    struct BusRoute route;
    while (fscanf(inputFile, "%d %s %s %f %f", &route.routeNumber, route.source, route.destination, &route.regularFare, &route.studentFare) != EOF) {
        if (strcmp(route.source, sourceToDelete) == 0 && strcmp(route.destination, destinationToDelete) == 0) {
            // Route matches the source and destination to delete, so skip it (do not write to temp file)
            found = 1;
        } else {
            // Write other routes to the temp file
            fprintf(tempFile, "%d %s %s %.2f %.2f\n", route.routeNumber, route.source, route.destination, route.regularFare, route.studentFare);
        }
    }
    fclose(inputFile);
    fclose(tempFile);
    if (found) {
        // Remove the original file and rename the temp file
        remove("bus_routes.txt");
        rename("temp.txt", "bus_routes.txt");
        printf("\n\n\n\n\n\n\t\t\t\t\t\033[92mRoute with Source '%s' and Destination '%s' deleted successfully.\033[0m\n", sourceToDelete, destinationToDelete);
    } else {
        printf("\n\n\n\n\n\n\t\t\t\t\t\033[1;91mNo route found with Source '%s' and Destination '%s'.\033[0m\n", sourceToDelete, destinationToDelete);
        remove("temp.txt"); // Remove the temporary file if no changes were made
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue...");
    getch();
}
void displayUserLogins() {
    system("cls");
    printf("\033[1;91m");
     printf("\n\n\n\n\n\t\t\t\t\t  *-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
     printf("\033[1;92m");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t        =                 USER INFO                 =");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\033[1;91m");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
     printf("\033[37m");
    FILE *fp = fopen("user_data.txt", "r");
    if (fp == NULL) {
         printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\033[1;91mError opening the file!\033[0m\n");
        fclose(fp);
    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue...");
    getch();
    }
    else{
    struct user_login user;
    printf("\n\n\n\n\t\t\t\t\t \033[1;96m%-15s%-10s\n\033[0m ", "USERNAME", "PASSWORD");    
    printf("\t\t\t\t\t\033[1;96m----------     -----------\033[0m");
    while (fscanf(fp, "%s %s", user.name, user.password) != EOF) {
        printf("\n\t\t\t\t\t%-15s| %-7s", user.name, user.password);
    }
    fclose(fp);
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue...");
    getch();
}
}
void displayRoutesByUserChoice() {
	do {
        system("cls");
         printf("\033[1;91m");
        printf("\n\n\n\n\n\n\t\t\t\t\t  *-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-*");
         printf("\033[1;92m");
        printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\n\t\t\t\t\t        =        DISPLAY BUS ROUTES BY CHOICE        =");
        printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\033[1;91m");
        printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
          printf("\033[37m");
        char sourceFilter[50];
        char destinationFilter[50];
        printf("\n\n\n\n\n\t\t\t\033[1;96mEnter source (leave blank for no filter):  \033[0m");
        fflush(stdin);
        gets(sourceFilter);
        printf("\033[\t\t\t1;96mEnter destination (leave blank for no filter):  \033[0m ");
        fflush(stdin);
        gets(destinationFilter);
        FILE* inputFile = fopen("bus_routes.txt", "r");
        if (inputFile == NULL) {
            printf("\n\n\n\n\t\t\t\t\t\t\t\033[1;31mNo buses are availabe \033[0m\n");
			 printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress anykey to continue....");
			 getch();
            return;
        }
        struct BusRoute route;
         int bookingsFound = 0;
        while (fscanf(inputFile, "%d %s %s %f %f", &route.routeNumber, route.source, route.destination, &route.regularFare, &route.studentFare) != EOF) {
            if ((strlen(sourceFilter) == 0 || strcmp(route.source, sourceFilter) == 0) &&
                (strlen(destinationFilter) == 0 || strcmp(route.destination, destinationFilter) == 0)) {
               if (!bookingsFound) {
			 printf("\n\n\n\n\n\n\t\t\t\t\033[1;96m%-15s  %-30s%-30s%-15s  %-15s\n\033[0m", "Route Number", "Source", "Destination", "Regular Fare", "Student Fare");
    printf("\t\t\t\033[1;96m       --------------   --------                      -------------                 --------------   --------------\033[0m\n\n");}
                printf("\t\t\t\t%-15d  %-30s%-30s%-15.2f  %-15.2f\n", route.routeNumber, route.source, route.destination, route.regularFare, route.studentFare);
             bookingsFound = 1;
			}
        }
        fclose(inputFile);
        if (!bookingsFound) {
                   printf("\n\n\n\n\t\t\t\t\t\t\t\033[1;31mNo buses are availabe \033[0m\n");}
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue....");
}while(getch()==0);
}
void userMenu() {
    int choice;
    do {
        system("cls");
        printf("\033[92m");	
        printf("\n\n\n\t\t\t\t\t\t\t\t*-*-User Page-*-*");
        printf("\n\t\t\t\t\t\t\t   \033[1;96m <------------------------------>\033[0m\n\n ");
        printf("\n\n\n");
        printf("\n\t\t\t\t\t\t\t*************************************");
        printf("\x1b[36m");
        printf("\n\t\t\t\t\t\t\t*       ||     User Menu    ||      *\n");
        printf("\033[0m");
        printf("\t\t\t\t\t\t\t*************************************");
        printf("\n");
        printf("\t\t\t\t\t\t\t| %-2s | %-28s | \n", "1.", "Display Routes by Choice","|");
        printf("\t\t\t\t\t\t\t| %-2s | %-28s | \n", "2.", "Display Routes","|");
        printf("\t\t\t\t\t\t\t| %-2s | %-28s | \n", "3.", "Exit","|");
        printf("\t\t\t\t\t\t\t*************************************");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayRoutesByUserChoice();
                break;
            case 2:
                displayRoute();
                break;
            case 3:
            	system("cls");
            	printf("\033[1;31m");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tThank You for Visiting Us. Have a good time!\n");
                printf("\033[0m");
                 printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue...");
                 getch();
                exit(0);
            default:{
                printf("\033[1;31m");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
                printf("\033[0m");
                 printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue...");
                 getch();
                break;}
        }
    } while (1);
}
int main() {
    system("cls");    
    printf("\033[1;91m");
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t BUS ROUTE MANAGEMENT SYSTEM");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n\n\n\n\n\n\n\n");
    printf("\033[1;92m");
    printf("\t\t\t\t\tW       W  EEEEEEE  L          CCCCC   OOOO   M     M  EEEEEEE\n");
    printf("\t\t\t\t\tW       W  E        L        CC       O    O  MM   MM  E      \n");
    printf("\t\t\t\t\tW   W   W  EEEEEEE  L       CC        O    O  M M M M  EEEEEEE\n");
    printf("\t\t\t\t\tW W   W W  E        L        CC       O    0  M  M  M  E      \n");
    printf("\t\t\t\t\tW       W  EEEEEEE  LLLLLL     CCCCC   OOOO   M     M  EEEEEEE\n");
     printf("\n\t\t\t\t\033[1;96m *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\033[0m\n\n ");
    printf("\033[0m");
    printf("\n\n\n\n\n\n\t\t\t\t\t Enter any key to continue.....");
    getch();

    while (1) {
        system("cls"); 
        start :
        printf("\033[92m");	
        printf("\n\n\n\t\t\t\t\t\t\t\t*-*-Select User Type-*-*");
        printf("\n\t\t\t\t\t\t\t   \033[1;96m <------------------------------>\033[0m\n\n ");
        printf("\n\n\t\t\t\t\t\t1. Administrator\n");
        printf("\n\t\t\t\t\t\t2. Passenger\n");
         
        printf("\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m ");
        char choice = getchar();
	    switch (choice) { 
            case '1': {
                int adminChoice = admin_login();
                if (adminChoice == 1) {
                	printf("\n\n\n\n\t\t\t\t\t\t\t\t\033[1;93m~~Log in successful~~\033[0m\n");
                    printf("\n\n\n\t\t\t\t\t\t\t         \033[1;38;5;207m**WELCOME Admin!**\033[0m\n");
                    printf("\n\n\n\t\t\t Enter any key to continue.....");
                    getch();
                    while (1){
                    system("cls");
                    printf("\033[92m");
                    printf("\n\n\n\t\t\t\t\t\t\t\t   -*-ADMIN PAGE-*-");
                    printf("\n\t\t\t\t\t\t\t      \033[1;96m<--------------------------->\033[0m");
                    printf("\n\n\n");
        printf("\n\n\n\n\t\t\t\t\t\t\t\t*****************************");
        printf("\x1b[36m"); 
        printf("\n\t\t\t\t\t\t\t\t*   ||Administrator Menu||  *\n");
        printf("\033[0m");
        
        printf("\t\t\t\t\t\t\t\t*****************************");
        printf("\n");
        printf("\t\t\t\t\t\t\t\t| %-2s | %-20s | \n", "1.", "Add Route","|");
        printf("\t\t\t\t\t\t\t\t| %-2s | %-20s | \n", "2.", "Display Routes","|");
        printf("\t\t\t\t\t\t\t\t| %-2s | %-20s |\n", "3.", "Delete Route","|");
        printf("\t\t\t\t\t\t\t\t| %-2s | %-20s | \n", "4.", "User Info","|");
        printf("\t\t\t\t\t\t\t\t| %-2s | %-20s |\n", "0.", "Log Out","|");
        printf("\t\t\t\t\t\t\t        ***************************");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m ");
                    scanf(" %d", &adminChoice);  // Read the 
                    while (getchar() != '\n') {
            // Discard characters until a newline is encountered
        }
                    switch (adminChoice) {

                        case 1:
                           addRoute();
                            break;
                        case 2:
                           displayRoute();
                            break;
                        case 3: {
                            deleteRoute();
                            break;}
                        case 4: {
                            displayUserLogins();
                            break;}
                        case 0:
                        	system("cls");
                        	printf("\033[1;91m");
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t Exiting Admin Login.");
                            printf("\033[0m");
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue...");
                            getch();
                            system("cls");
                            goto start;
                        default:
                        	printf("\033[1;31m");
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
                            printf("\033[0m");
                    
                }
               
            } }
			 break;}
            case '2': {
                system("cls");
                printf("\033[92m");
               printf("\n\n\n\t\t\t\t\t\t\t\t*-*-USER LOGIN-*-*");
               printf("\n\t\t\t\t\t\t\t   \033[1;96m <------------------------->\033[0m\n\n ");
                printf("\n\n\t\t\t\t\t1. Log in");
                printf("\n\t\t\t\t\t2. Register");
                printf("\n\t\t\t\t\t3. Exit\n");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\033[1;95mEnter your choice:\033[0m ");
                switch (getch()) {
                    case '1':
                        already_user();
                        break;
                    case '2':
                        register_user();
                        break;
                    case '3':
                        system("cls");
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\033[1;91mExiting program. Goodbye!!\n\033[0m\n");
                        exit(0);
                    default:
                    	printf("\033[1;31m");
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
                        printf("\033[0m");
                        break;
                }
                break;
            }
            default:
            	printf("\033[1;31m");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWrong choice*_*");
                printf("\033[0m");
                getch();
                break;
        }
    }
    return 0;
}
