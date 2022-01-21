// BE NUME KHUDA
#pragma warning(disable:4996)

// libraries
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>



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
    char team[100];
    int value;
    int id;
    char name[normal_limit];
    int attack;
    int defenece;

} def_val = {"Free-Agent"};

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

// global variables
int loginedTeamID = -1;


// function declration
void login();
void addTeam();
void loading();
void itemFive();
void fixtures();
void addPlayer();
void showTeams();
void buyPlayer();
void sellPlayer();
void selectTeam();
void showPlayers();
void clearScreen();
void showScoreBoard();
void changePassword();
void mainPageLanding();
void adminPageLanding();
void upcomingOpponent();
void normalUserLanding();
void fileOpener(char FileName[30]);
int teamCounter(char filename[20]);
int usernameUniqueChecker(char string[high_limit], team team);



// main function
int main() {
    mainPageLanding();
    return 0;
}


// long functions
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
    while (True) {
        clearScreen();
        FILE* file, * teams;
        file = fopen("teamcounter.txt", "a");
        fseek(file, 0, SEEK_END);
        int teamNumber = ftell(file);
        team newTeam = deffault_value;
        printf("Enter your team name:\n");
        while (True) {
            scanf("%s", newTeam.name);
            if (usernameUniqueChecker(newTeam.name, newTeam) == 0)
                printf("Somebody used your username, try again...\n");
            else {
                printf("%s is saved for your team name!\n", newTeam.name);
                break;
            }
        }
        printf("Enter leader email: (next time you should login with this as your username)\n");
        scanf("%s", newTeam.teamleader.email);
        newTeam.id = teamNumber + 1;
        strcpy(newTeam.teamleader.username, newTeam.teamleader.email);
        strcpy(newTeam.teamleader.password, newTeam.teamleader.email);
        putc('Q', file);    // for counting teams
        fclose(file);
        teams = fopen("teams.txt", "a+");
        fwrite(&newTeam, sizeof(newTeam), 1, teams);
        printf("Succesfully aded!\n");
        fclose(teams);
        printf("Add more? (yes/no)\n");
        char userInput[12];
        scanf("%s", userInput);
        if (strcmp(userInput, "yes") == 0) {
            addTeam();
            break;
        }
        else {
            adminPageLanding();
            break;
        }
    }
}
void showTeams() {
    while (True) {
        FILE* file;
        file = fopen("teams.txt", "r");
        team myteam;
        for (int i = 0; i < teamCounter("teamcounter.txt"); i++)
        {
            fread(&myteam, sizeof(myteam), 1, file);
            printf("ID: %d | Budget: %d | Name: %s\nLeader Informations:\nUsername: %s\nPassword: %s\nE-mail: %s\n-------------\n", myteam.id, myteam.budget, myteam.name, myteam.teamleader.username, myteam.teamleader.password, myteam.teamleader.email);
        }
        fclose(file);
        printf("Back? (yes/no)\n");
        char userInput[10];
        scanf("%s", userInput);
        if (strcmp(userInput, "yes") == 0) {
            adminPageLanding();
            break;
        }
        else if (strcmp(userInput, "no") == 0) {
            printf("Dude! why no? there is no more data to show, we back you to admin...\n");
            loading();
            adminPageLanding();
            break;
        }
    }
}
void addPlayer() {
    while (True) {
        clearScreen();
        FILE* file, * counter;
        counter = fopen("playercounter.txt", "a");
        fseek(counter, 0, SEEK_END);
        int teamNumber = ftell(counter);
        player newPlayer = def_val;
        printf("Enter player name:\n");
        scanf("%s", newPlayer.name);
        printf("Enter player value:\n");
        scanf("%d", &newPlayer.value);
        printf("Enter player attacking power:\n");
        scanf("%d", &newPlayer.attack);
        printf("Enter player deffencing power:\n");
        scanf("%d", &newPlayer.defenece);
        newPlayer.id = teamNumber + 1;
        putc('R', counter);
        fclose(counter);
        file = fopen("players.txt", "a");
        fwrite(&newPlayer, sizeof(newPlayer), 1, file);
        printf("player %s succesfully added\n", newPlayer.name);
        fclose(file);
        printf("Add more? (yes/no)\n");
        char userInput[12];
        scanf("%s", userInput);
        if (strcmp(userInput, "yes") == 0) {
            addPlayer();
            break;
        }
        else {
            adminPageLanding();
            break;
        }
    }
}
void showPlayers() {
    while (True) {
        clearScreen();
        printf("---------------\n");
        FILE* file;
        file = fopen("players.txt", "r");
        player myplayer;
        for (int i = 0; i < teamCounter("playercounter.txt"); i++)
        {
            fread(&myplayer, sizeof(myplayer), 1, file);
            printf("ID: %d | Name: %s | Deffence power: %d | Attack power: %d | Value: %d | Team: %s\n", myplayer.id, myplayer.name, myplayer.defenece, myplayer.attack, myplayer.value, myplayer.team);
            printf("---------------\n");
        }
        fclose(file);
        printf("Back? (yes/no)\n");
        char userInput[10];
        scanf("%s", userInput);
        if (strcmp(userInput, "yes") == 0) {
            adminPageLanding();
            break;
        }
        else if (strcmp(userInput, "no") == 0) {
            printf("Dude! why no? there is no more data to show, we back you to admin...\n");
            loading();
            adminPageLanding();
            break;
        }
    }
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
        FILE* file,*counter;
        team myteam = deffault_value;
        int counterNumber = teamCounter("teamcounter.txt");
        file = fopen("teams.txt", "r");
        int confirm = 0;
        for (int i = 0; i < counterNumber; i++)
        {
            fread(&myteam, sizeof(myteam), 1, file);
            if (strcmp(username, myteam.teamleader.username) == 0 && strcmp(password, myteam.teamleader.password) == 0) {
                loginedTeamID = myteam.id;
                confirm++;
                break;
            }

        }
        if (confirm == 1) {
            normalUserLanding();
        }
        else {
            printf("You entered a wrong username or password, try again...\n");
            loading();
            mainPageLanding();
        }
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
    fileOpener("playercounter.txt");
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
            printf("--------\nSee you soon!\n-------\n");
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
    clearScreen();
    FILE* file,*temp;
    team myteam = deffault_value;
    int count = teamCounter("teamcounter.txt");
    char inputUser[normal_limit];
    printf("if you got a \"OK\" message then you can login with your new password.\nEnter your new password:\n");
    scanf("%s", inputUser);
    file = fopen("teams.txt","r");
    temp = fopen("temp.txt", "w");

    for (int i = 0; i < count; i++)
    {
        fread(&myteam, sizeof(myteam), 1, file);
        if (myteam.id == loginedTeamID) {
            strcpy(myteam.teamleader.password, inputUser);
            fwrite(&myteam, sizeof(myteam), 1, temp);
        }
        else {
            fwrite(&myteam, sizeof(myteam), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    temp = fopen("temp.txt", "r");
    file = fopen("teams.txt", "w");
    for (int i = 0; i < count; i++)
    {
        fread(&myteam, sizeof(myteam), 1, temp);
        fwrite(&myteam, sizeof(myteam), 1, file);
    }
    fclose(file);
    fclose(temp);
    remove("temp.txt");
    printf("Your password successfully changed.\nYou automatically turn into menu in 3 seconds\n");
    loading();
    normalUserLanding();
}

// short functions
void clearScreen() {
    system("cls");
}
void fileOpener(char FileName[30]) {
    FILE* file;
    file = fopen(FileName, "r+");
    if (!file) {
        file = fopen(FileName, "w+");
    }
    fclose(file);
}
void loading() {
    Sleep(1000);
    printf("---------- 3 ----------");
    Sleep(1000);
    printf("\r---------- 2 ----------");
    Sleep(1000);
    printf("\r---------- 1 ----------");
    Sleep(1000);
}
int usernameUniqueChecker(char string[high_limit], team team) {
    int count = teamCounter("teamcounter.txt");
    FILE* file;
    int calcCounter = 0;
    file = fopen("teams.txt", "r");
    for (int i = 0; i < count; i++)
    {
        fread(&team, sizeof(team), 1, file);
        if (strcmp(team.name, string) == 0)
            calcCounter++;
    }
    if (calcCounter == 1) {
        return False;
    }
    else
        return True;
}
int teamCounter(char fileName[20]) {
    FILE* file;
    file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

