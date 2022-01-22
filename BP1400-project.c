// BE NUME KHUDA
#pragma warning(disable:4996)

// libraries
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"colors.h"



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
typedef struct leagueStatus lStatus;


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
    int memberNumber;
    char status[20];
    int id;
    struct leader teamleader;
    char name[high_limit];
    struct player members[8];
    struct player choosenPlayers[5];

} deffault_value = { 100,0,"Unready"};

struct competition {
    char winner[high_limit];
    struct team firsteam;
    struct team secondteam;
} winner_value = { "None" };

struct leagueStatus {
    int week;
    char leagueStatus[50];
    char button[50];
    struct team teams[4];

} deffault = { 0, "inactive", "Start League"};


// global variables
int loginedTeamID = -1;
char button[normal_limit] = "Start League";



// function declration
void login();
void waiter();
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
void startLeague();
void showScoreBoard();
void changePassword();
void mainPageLanding();
void adminPageLanding();
void upcomingOpponent();
void normalUserLanding();
void fileOpener(char FileName[30]);
void arrayPrinter(int arr[], int len);
void structSorter(player list[8], int s);
void teamFileUpdater(team changedTeam, int count);
void playerFileUpdater(player changedPlayer, int count);
int usernameUniqueChecker(char string[high_limit], team team);
int objectCounter(char filename[20]);
int arrayChecker(int arr[], int a, int len);
player playerFinder(int id);
team teamFinder(int id);




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
    team myteam = teamFinder(loginedTeamID);
    clearScreen();
    printf("Wallet: %d$\n", myteam.budget);
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
        file = fopen("teamcounter.txt", "ab");
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
        teams = fopen("teams.txt", "ab+");
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
        file = fopen("teams.txt", "rb");
        team myteam;
        for (int i = 0; i < objectCounter("teamcounter.txt"); i++)
        {
            fread(&myteam, sizeof(myteam), 1, file);
            printf("ID: %d | Budget: %d | Members: %d | Name: %s | Status: %s \nLeader Informations:\nUsername: %s\nPassword: %s\nE-mail: %s\n-------------\n", myteam.id, myteam.budget, myteam.memberNumber, myteam.name, myteam.status, myteam.teamleader.username, myteam.teamleader.password, myteam.teamleader.email);
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
        counter = fopen("playercounter.txt", "ab+");
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
        file = fopen("players.txt", "ab");
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
        file = fopen("players.txt", "rb");
        player myplayer;
        for (int i = 0; i < objectCounter("playercounter.txt"); i++)
        {
            fread(&myplayer, sizeof(myplayer), 1, file);
            printf("ID: %d | Name: %s | Deffence power: %d | Attack power: %d | Value: %d | Team: %s \n", myplayer.id, myplayer.name, myplayer.defenece, myplayer.attack, myplayer.value, myplayer.team);
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
        int counterNumber = objectCounter("teamcounter.txt");
        file = fopen("teams.txt", "rb");
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
    fileOpener("teams.txt");
    fileOpener("players.txt");
    fileOpener("teamcounter.txt");
    fileOpener("playercounter.txt");
    fileOpener("config.txt");
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
            startLeague();
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
    while (True) {
        clearScreen();
        FILE* players, * teams, * temp;
        int count = objectCounter("playercounter.txt");
        players = fopen("players.txt", "rb");
        player myplayer = def_val;
        team myteam = deffault_value;
        printf("These players are Free-agent and you can buy them:\n---------------\n");
        for (int i = 0; i < count; i++)
        {
            fread(&myplayer, sizeof(myplayer), 1, players);
            if (strcmp(myplayer.team, "Free-Agent") == 0) {
                printf("ID: %d | Name: %s | Deffence power: %d | Attack power: %d | Value: %d | Team: %s\n", myplayer.id, myplayer.name, myplayer.defenece, myplayer.attack, myplayer.value, myplayer.team);
                printf("---------------\n");
            }
        }
        while (True) {
            printf("Type player ID to buy:\n");
            int buyId = -1;
            while (True) {
                scanf("%d", &buyId);
                if (buyId > count) {
                    printf(FRED "Not valid number, try again...\n" RESET);
                }
                else
                    break;
            }
            myplayer = playerFinder(buyId);
            myteam = teamFinder(loginedTeamID);
            if (myteam.memberNumber < 8 && myteam.budget >= myplayer.value && strcmp(myplayer.team, "Free-Agent") == 0) {
                printf("Your purchase was succesfull!\nwait...\n");
                strcpy(myplayer.team, myteam.name);
                myteam.budget = myteam.budget - myplayer.value;
                myteam.members[myteam.memberNumber] = myplayer;
                myteam.memberNumber++;
                //Sleep(2000);
                printf(FGREEN "Player %s added to your team\n" RESET , myplayer.name);
                break;
            }
            else {
                printf(FRED "There is a problem with your purchase, check if you wrote a wrong ID\n" RESET);
            }
        }
        // our bought player stored in myplayer
        // our updated team details stored in myteam
        // lets update files...

        teamFileUpdater(myteam, objectCounter("teamcounter.txt"));
        playerFileUpdater(myplayer, objectCounter("playercounter.txt"));
        printf("back? press enter!\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }
    }
}
void sellPlayer() {
    while (True) {
        printf("You have these choices to sell:\n-------------\n");
        FILE* players, * teams;
        team myteam = deffault_value;
        player temp = def_val;
        strcpy(temp.team, "");
        player myplayer = def_val;
        int sellId = -1;
        myteam = teamFinder(loginedTeamID);
        for (int i = 0; i < myteam.memberNumber; i++)
        {
            printf("ID: %d | Name: %s | Attack: %d | Deffence: %d | Value: %d\n-------------\n", myteam.members[i].id, myteam.members[i].name, myteam.members[i].attack, myteam.members[i].defenece, myteam.members[i].value);
        }
        printf("Enter player ID to sell:\n");
        while (True) {
            scanf("%d", &sellId);
            myplayer = playerFinder(sellId);
            if (strcmp(myplayer.team, myteam.name) != 0) {
                printf(FRED "Invalid ID, try again...\n" RESET);
            }
            else {
                strcpy(myplayer.team, "Free-Agent");
                myteam.budget = myteam.budget + myplayer.value;
                for (int i = 0; i < myteam.memberNumber; i++)
                {
                    if (myteam.members[i].id == sellId) {
                        myteam.members[i] = temp;
                    }
                }
                structSorter(&myteam.members, myteam.memberNumber);
                myteam.memberNumber--;
                waiter();
                break;
            }

        }
        // myplayer store new value of sold player
        // myteam store new value of team
        teamFileUpdater(myteam, objectCounter("teamcounter.txt"));
        playerFileUpdater(myplayer, objectCounter("playercounter.txt"));
        printf(FGREEN "Player %s sold, %d$ added to your wallet\n" RESET , myplayer.name, myplayer.value);
        printf("back? press enter!\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }

    }

}
void selectTeam() {
    while (True) {
        printf("Your players:\n");
        team myteam = deffault_value;
        int teamMemberIDs[8];
        int p1, p2, p3, p4, p5;
        int counter = 0;
        myteam = teamFinder(loginedTeamID);
        for (int i = 0; i < myteam.memberNumber; i++)
        {
            printf("ID: %d | Name: %s | Attack: %d | Deffence: %d | Value: %d \n-------------\n", myteam.members[i].id, myteam.members[i].name, myteam.members[i].attack, myteam.members[i].defenece, myteam.members[i].value);
            teamMemberIDs[i] = myteam.members[i].id;
        }
        printf("Your selected squad is: %s, %s, %s, %s, %s\n", myteam.choosenPlayers[0].name, myteam.choosenPlayers[1].name, myteam.choosenPlayers[2].name, myteam.choosenPlayers[3].name, myteam.choosenPlayers[4].name);
        if (myteam.memberNumber == 8) {
            while (True) {
                counter = 0;
                printf("You have to select your squad for upcoming math, type 5 ID's for your squad:\n");
                scanf("%d%d%d%d%d", &p1, &p2, &p3, &p4, &p5);
                int typedIDs[5] = { p1,p2,p3,p4,p5 };
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (typedIDs[i] == teamMemberIDs[j]) {
                            counter++;
                            break;
                        }
                    }
                }
                if (counter == 5) {
                    printf("Wait until we submit your team...\n");
                    myteam.choosenPlayers[0] = playerFinder(p1);
                    myteam.choosenPlayers[1] = playerFinder(p2);
                    myteam.choosenPlayers[2] = playerFinder(p3);
                    myteam.choosenPlayers[3] = playerFinder(p4);
                    myteam.choosenPlayers[4] = playerFinder(p5);
                    Sleep(2000);
                    strcpy(myteam.status, "Ready");
                    teamFileUpdater(myteam, objectCounter("teamcounter.txt"));
                    printf(FGREEN "Your team with %s, %s, %s, %s, %s submited!\n" RESET, myteam.choosenPlayers[0].name, myteam.choosenPlayers[1].name, myteam.choosenPlayers[2].name, myteam.choosenPlayers[3].name, myteam.choosenPlayers[4].name);
                    break;
                }
                else {
                    printf(FRED "There is a problem with your squad, try again...\n" RESET);
                }
            }
        }
        printf("Press Enter key to back...\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }
    }
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
    int count = objectCounter("teamcounter.txt");
    char inputUser[normal_limit];
    printf("if you got a \"OK\" message then you can login with your new password.\nEnter your new password:\n");
    scanf("%s", inputUser);
    file = fopen("teams.txt", "rb");
    temp = fopen("temp.txt", "wb");

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
    temp = fopen("temp.txt", "rb");
    file = fopen("teams.txt", "wb");
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
void startLeague() {
    FILE* file, * config;
    int replace = 0;
    int rep = 0;
    file = fopen("teams.txt", "rb");
    config = fopen("config.txt", "ab+");
    int count = objectCounter("teamcounter.txt");
    int teamIDs[800];
    int finalTeamList[4];
    team myteam = deffault_value;
    lStatus league = deffault;
    lStatus data = deffault;
    for (int i = 0; i < count; i++)
    {
        fread(&myteam, sizeof(myteam), 1, file);
        if (myteam.memberNumber == 8) {
            teamIDs[replace] = myteam.id;
            replace++;
        }
    }
    if (replace >= 4) {
        printf("Wait for a seconds...\n");
        while (rep != 4)
        {
            int selectedTeamForLeage = random(teamIDs, replace);
            if (arrayChecker(finalTeamList, selectedTeamForLeage, rep) == 0) {
                finalTeamList[rep] = selectedTeamForLeage;
                rep++;
            }
        }
        strcpy(league.leagueStatus, "Active");
        strcpy(league.button, "Start Week 1");
        for (int i = 0; i < 4; i++)
        {
            myteam = teamFinder(finalTeamList[i]);
            league.teams[i] = myteam;
        }
        clearScreen();
        fwrite(&league, sizeof(league), 1, config);
        fclose(config);
        config = fopen("config.txt", "r+");
        fread(&data, sizeof(data), 1, config);
        printf("League:\nStatus: %s\nNext Move: %s\nParticipated Teams:\n1- %s\n2- %s\n3- %s\n4- %s\n", data.leagueStatus, data.button, data.teams[0].name, data.teams[1].name, data.teams[2].name, data.teams[3].name);
        fclose(config);
        fclose(file);
    }
    else {
        printf("Not enough teams for start a league...\n");
    }

}




// short functions
void waiter() {
    printf("wait...\n");
    Sleep(2000);
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
void clearScreen() {
    system("cls");
}
void fileOpener(char FileName[30]) {
    FILE* file;
    file = fopen(FileName, "rb+");
    if (!file) {
        file = fopen(FileName, "wb+");
    }
    fclose(file);
}
void arrayPrinter(int arr[], int len) {
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
}
void structSorter(player list[8], int s)
{
    int i, j;
    player temp;

    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1 - i); j++)
        {
            if (list[j].id < list[j + 1].id)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}
void teamFileUpdater(team changedTeam, int count) {
    FILE* teams, * temp;
    teams = fopen("teams.txt", "rb");
    temp = fopen("temp.txt", "wb");
    team mySecondTeam = deffault_value;
    for (int i = 0; i < count; i++)
    {
        fread(&mySecondTeam, sizeof(mySecondTeam), 1, teams);
        if (mySecondTeam.id == changedTeam.id) {
            fwrite(&changedTeam, sizeof(changedTeam), 1, temp);
        }
        else {
            fwrite(&mySecondTeam, sizeof(mySecondTeam), 1, temp);
        }
    }
    fclose(teams);
    fclose(temp);
    temp = fopen("temp.txt", "rb");
    teams = fopen("teams.txt", "wb");
    for (int i = 0; i < count; i++)
    {
        fread(&changedTeam, sizeof(changedTeam), 1, temp);
        fwrite(&changedTeam, sizeof(changedTeam), 1, teams);
    }
    fclose(teams);
    fclose(temp);
    remove("temp.txt");
}
void playerFileUpdater(player changedPlayer, int count) {
    FILE *players, * temp;
    players = fopen("players.txt", "rb");
    temp = fopen("temp.txt", "wb");
    player mySecondPlayer = def_val;
    for (int i = 0; i < count; i++)
    {
        fread(&mySecondPlayer, sizeof(mySecondPlayer), 1, players);
        if (mySecondPlayer.id == changedPlayer.id) {
            fwrite(&changedPlayer, sizeof(changedPlayer), 1, temp);
        }
        else {
            fwrite(&mySecondPlayer, sizeof(mySecondPlayer), 1, temp);
        }
    }
    fclose(players);
    fclose(temp);
    temp = fopen("temp.txt", "rb");
    players = fopen("players.txt", "wb");
    for (int i = 0; i < count; i++)
    {
        fread(&changedPlayer, sizeof(changedPlayer), 1, temp);
        fwrite(&changedPlayer, sizeof(changedPlayer), 1, players);
    }
    fclose(players);
    fclose(temp);
    remove("temp.txt");
}
int usernameUniqueChecker(char string[high_limit], team team) {
    int count = objectCounter("teamcounter.txt");
    FILE* file;
    int calcCounter = 0;
    file = fopen("teams.txt", "rb");
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
int objectCounter(char fileName[20]) {
    FILE* file;
    file = fopen(fileName, "rb");
    fseek(file, 0, SEEK_END);
    return ftell(file);
}
int arrayChecker(int arr[], int a, int len) {
    int checker = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == a) {
            checker++;
            break;
        }
    }
    if (checker == 1) {
        return 1;
    }
    else
        return 0;
}
int random(int arr[],int lenArr) {
    srand(time(NULL));
    int randomIndex = rand() % lenArr;
    int randomValue = arr[randomIndex];
    return randomValue;
}

player playerFinder(int id) {
    FILE *file;
    file = fopen("players.txt", "rb");
    int count = objectCounter("playercounter.txt");
    player myplayer = def_val;
    for (int i = 0; i < count; i++)
    {
        fread(&myplayer, sizeof(myplayer), 1, file);
        if (myplayer.id == id) {
            return myplayer;
        }
    }
}
team teamFinder(int id) {
    FILE* file;
    file = fopen("teams.txt", "rb");
    int count = objectCounter("teamcounter.txt");
    team myteam = deffault_value;
    for (int i = 0; i < count; i++)
    {
        fread(&myteam, sizeof(myteam), 1, file);
        if (myteam.id == id) {
            return myteam;
        }
    }
}  