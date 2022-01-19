// BE NUME KHUDA
#pragma warning(disable:4996)

// libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<conio.h>

// defines
#define normal_limit 50


// function declration
void mainPageLanding();
void adminPageLanding();
void login();
void addTeam();
void addPlayer();
void showTeams();
void showPlayers();
void itemFive();
void buyPlayer();
void sellPlayer();
void selectTeam();
void showScoreBoard();
void fixtures();
void upcomingOpponent();
void changePassword();
void normalUserLanding();

// main func
int main() {
    mainPageLanding();
    return 0;
}


// functions
void clearScreen() {
    system("cls");
}
void forgotPassword() {
    printf("For recover your account you have to enter your E-mail\n");
}
void normalUserLanding() {
    clearScreen();
    printf("Choose an option:\n1. Buy player\n2. Sell player\n3. Select team/submit team\n4. Show scoreboard\n5. Fixtures\n6. Upcoming opponent\n7. Change password\n8. Exit\n");
    int userInput = 0;
    while (1) {
        scanf("%d", &userInput);
        if (userInput == 1) {
            buyPlayer();
            break;
        }
        else if (userInput == 2) {
            sellPlayer();
            break;
        }
        else if (userInput == 3) {
            selectTeam();
            break;
        }
        else if (userInput == 4) {
            showScoreBoard();
            break;
        }
        else if (userInput == 5) {
            fixtures();
            break;
        }
        else if (userInput == 6) {
            upcomingOpponent();
            break;
        }
        else if (userInput == 7) {
            changePassword();
            break;
        }
        else if (userInput == 8) {
            mainPageLanding();
            break;
        }
        else {
            printf("Not valid input, try again...\n");
        }
    }
}
void addTeam() {
    printf("Successfully worked! clicked Item: 1\n");
}
void addPlayer() {
    printf("Successfully worked! clicked Item: 2\n");
}
void showTeams() {
    printf("Successfully worked! clicked Item: 3\n");
}
void showPlayers() {
    printf("Successfully worked! clicked Item: 4\n");
}
void itemFive() {
    printf("Successfully worked! clicked Item: 5\n");
}
void login() {
    char username[normal_limit];
    char password[normal_limit];
    char email[normal_limit];
    printf("Enter your E-mail to login:\n");
    scanf("%s", username);
    printf("Enter your password(diffault is your email) to login:\n");
    scanf("%s", password);
    if (strcmp(username, "Admin") == 0 || strcmp(username, "admin") == 0) {
        if (strcmp(password, "Admin") == 0 || strcmp(password, "admin") == 0) {
            adminPageLanding();
        }
    }
    else {
        normalUserLanding();
    }
}
void mainPageLanding() {
    clearScreen();
    printf("Welcome sir, choose options below\n1- Login\n2- Forgot password\n3- Exit\n");
    while (1) {
        int userInput = 0;
        scanf_s("%d", &userInput);
        if (userInput == 1) {
            login();
            break;
        }
        else if (userInput == 2) {
            forgotPassword();
            break;
        }
        else if (userInput == 3) {
            clearScreen();
            printf("See you soon!");
            exit(0);
        }
        else {
            printf("Not valid input, try again...\n");
        }
    }


}
void adminPageLanding() {
    clearScreen();
    int userInput = 0;
    printf("Choose an option by typing its number:\n1. Add team\n2. add player\n3. show teams\n4. show players\n5. item 5\n6. Log out\n");
    while (1) {
        scanf("%d", &userInput);
        if (userInput == 1) {
            addTeam();
            break;
        }
        else if (userInput == 2) {
            addPlayer();
            break;
        }
        else if (userInput == 3) {
            showTeams();
            break;
        }
        else if (userInput == 4) {
            showPlayers();
            break;
        }
        else if (userInput == 5) {
            itemFive();
            break;
        }
        else if (userInput == 6) {
            mainPageLanding();
            break;
        }
        else {
            printf("Not valid input, try again...\n");
        }
    }
}
void buyPlayer() {
    printf("Succesfully clicked on button 1");
}
void sellPlayer() {
    printf("Succesfully clicked on button 2");
}
void selectTeam() {
    printf("Succesfully clicked on button 3");
}
void showScoreBoard() {
    printf("Succesfully clicked on button 4");
}
void fixtures() {
    printf("Succesfully clicked on button 5");
}
void upcomingOpponent() {
    printf("Succesfully clicked on button 6");
}
void changePassword() {
    printf("Succesfully clicked on button 7");
}
