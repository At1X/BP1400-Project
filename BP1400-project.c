// BE NUME KHUDA

// libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <stdbool.h>

// defines
#define normal_limit 50


// function declaration
void clearScreen();
void forgotPassword();
void login();
void adminPageLanding();
void normalUserLanding();
void addTeam();
void addPlayer();
void showTeams();
void showPlayers();
void itemFive();
void  mainPageLanding();

// variables
char email[normal_limit];
char username[normal_limit];
char password[normal_limit];

int main() {
    mainPageLanding();
    return 0;
}

// functions
void clearScreen() {
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
void mainPageLanding() {
    clearScreen();
    printf("Welcome sir, choose options below\n1- Login\n2- Forgot password\n3- Exit\n");
    while (1) {
        int userInput = 0;
        scanf("%d",&userInput);
        if (userInput == 1) {
            login();
            break;
        }
        else if (userInput == 2) {
            forgotPassword();
            break;
        }
        else if (userInput == 3) {
            break;
        }
        else {
            printf("Not valid input, try again...\n");
        }
    }
    printf("See you soon!");
}
void forgotPassword() {
    printf("For recover your account you have to enter your E-mail\n");
}
void login() {
    printf("Enter your E-mail to login:\n");
    gets(username); 
    printf("Enter your password(diffault is your email) to login:\n");
    gets(password);
    if (strcmp(username,"Admin") || strcmp(username,"admin")) {
        if (strcmp(password,"Admin") || strcmp(password,"admin")) {
            adminPageLanding();
        }
    }
}
void adminPageLanding() {
    clearScreen();
    int userInput = 0;
    printf("Choose an option by typing its number:\n1- Add team\n2- add player\n3- show teams\n4- show players\n5- item 5\n6- Log out\n");
    while (1) {
        scanf("%d",&userInput);
        if (userInput == 1) {
            addTeam();
        }
        else if (userInput == 2) {
            addPlayer();
        }
        else if (userInput == 3) {
            showTeams();
        }
        else if (userInput == 4) {
            showPlayers();
        }
        else if (userInput == 5) {
            itemFive();
        }
        else if (userInput == 6) {
            break;
        }
        else {
            printf("Not valid input, try again...\n");
        }
    }
    mainPageLanding();
}
void normalUserLanding() {
    printf("Choose an option:\n1- Buy player(buy)\n2- Sell player(sell)\n3- Select team/submit team(steam)\n4- Show scoreboard(scoreboard)\n5- Fixtures(fixt)\n6- Upcoming opponent(upop)\n7- Change password(changepsw)\n8- Exit(wq)");
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