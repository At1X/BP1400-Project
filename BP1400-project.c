// BE NUME KHUDA
#pragma warning(disable:4996)

// libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>



// defines
#define small_limit 20
#define normal_limit 50
#define high_limit 100
#define super_high_limit 500
#define False 0
#define True  1
typedef struct player player;
typedef struct leader leader;
typedef struct team team;

// structures
struct player
{
    int value;
    int id;
    char name[normal_limit];
    int attack;
    int defenece;
    char team[100];
};

struct leader
{
    char username[normal_limit];
    char password[normal_limit];
    char email[normal_limit];
};

struct team
{
    int budget;
    int id;
    struct leader teamleader;
    char name[high_limit];
    struct player members[8];

} deffault_value = { 100 };



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
void fileOpener();
int teamCounter();
int emailUniqueChecker();
int usernameUniqueChecker();


// main func
int main() {
    mainPageLanding();
    return 0;
}


// long functions
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
    while (True) {
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
    clearScreen();
    FILE *file,*teams;
    file = fopen("teamcounter.txt", "a");
    fseek(file, 0, SEEK_END);
    int teamNumber = ftell(file);
    team newTeam = deffault_value;
    printf("Enter your team name:\n");
    scanf("%s", newTeam.name);
    printf("Enter leader email: (next time you should login with this as your username)\n");
    while (True) {
        scanf("%s", newTeam.teamleader.email);
        if (emailUniqueChecker(newTeam.teamleader.email, newTeam) == 0)
            printf("Somebody used your email, try again...\n");
        else {
            printf("Succesfully added.\n");
            break;
        }
    }
    newTeam.id = teamNumber + 1;
    strcpy(newTeam.teamleader.username, newTeam.teamleader.email);
    strcpy(newTeam.teamleader.password, newTeam.teamleader.email);
    putc('Q', file);    // for counting teams
    fclose(file);
    teams = fopen("teams.txt", "a+");
    fwrite(&newTeam, sizeof(newTeam), 1, teams);
    fclose(teams);
}
void addPlayer() {
    printf("Successfully worked! clicked Item: 2\n");
}
void showTeams() {
    FILE *file;
    file = fopen("teams.txt", "r");
    team myteam;
    for (int i = 0; i < teamCounter(); i++)
    {
        fread(&myteam, sizeof(myteam), 1, file);
        printf("ID: %d | Budget: %d | Name: %s\nLeader Informations\nUsername: %s\nPassword: %s\nE-mail: %s\n-------------\n", myteam.id, myteam.budget, myteam.name, myteam.teamleader.username, myteam.teamleader.password, myteam.teamleader.email);
    }
    fclose(file);
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
    // make essential files ready
    fileOpener("leaders.txt");
    fileOpener("teams.txt");
    fileOpener("players.txt");
    fileOpener("config.txt");
    fileOpener("teamcounter.txt");
    // end
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


// short functions
void fileOpener(char FileName[30]) {
    FILE* file;
    file = fopen(FileName, "r+");
    if (!file) {
        file = fopen(FileName, "w+");
    }
    fclose(file);
}
int emailUniqueChecker(char string[high_limit], team team) {
    int count = teamCounter();
    FILE* file;
    int calcCounter = 0;
    file = fopen("teams.txt", "r");
    for (int i = 0; i < count; i++)
    {
        fread(&team, sizeof(team), 1, file);
        if (strcmp(team.teamleader.email, string) == 0)
            calcCounter++;
    }
    if (calcCounter == 1) {
        return False;
    }
    else
        return True;
}
int usernameUniqueChecker(char string[high_limit], team team) {
    int count = teamCounter();
    FILE* file;
    int calcCounter = 0;
    file = fopen("teams.txt", "r");
    for (int i = 0; i < count; i++)
    {
        fread(&team, sizeof(team), 1, file);
        if (strcmp(team.teamleader.username, string) == 0)
            calcCounter++;
    }
    if (calcCounter == 1) {
        return False;
    }
    else
        return True;
}
int teamCounter() {
    FILE* file;
    file = fopen("teamcounter.txt", "r");
    fseek(file, 0, SEEK_END);
    return ftell(file);
}
