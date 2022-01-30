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
typedef struct weeks weeks;
typedef struct competition competition;

// structures
struct leader
{
    char username[normal_limit];
    char password[normal_limit];
    char email[normal_limit];
};

struct player
{
    char team[100];
    int value;
    int id;
    char name[normal_limit];
    int attack;
    int defenece;

} def_val = {"Free-Agent"};

struct team
{
    int budget;
    int canBet;
    int score;
    int memberNumber;
    int gol_zade;
    int gol_khorde;
    int tafazol;
    int won;
    int lost;
    int drawn;
    int played;
    char status[20];
    int id;
    struct leader teamleader;
    char name[high_limit];
    struct player members[8];
    struct player choosenPlayers[5];
    struct player backupChoosenPlayers[5];



} deffault_value = { 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Unready"};

struct leagueStatus {
    int week;
    int transfer;
    char leagueStatus[10];
    char button[50];
    int participatedTeamId[4];

} deffault = { 0, 1, "inactive", "Start League"};

struct competition {
    char winner[high_limit];
    struct team firsteam;
    struct team secondteam;
} winner_value = { "None" };

struct weeks {
    int numberOfGames;
    struct competition week[12];
};


// global variables
int loginedTeamID = -1;
char button[normal_limit] = "Start League";



// function declration
void login();
void waiter();
void addTeam();
void loading();
void itemFive(); // shown in admin panel for control all league functions
void fixtures();
void addPlayer();
void showTeams();
void buyPlayer();
void showTable(); // show and update scoreboard after each game week
void sellPlayer();
void selectTeam(); // select and submit team
void resetCache(); // reset all data inlcuded all teams and players
void showPlayers();
void clearScreen(); 
void startLeague();
void showWeekData(); // after starting league, this function load to show all week games
void showScoreBoard();
void changePassword();
void mainPageLanding(); // first page landing
void leagueConductor(); // create league games for 6 weeks
void transformWindow(); // open and close transfer window
void adminPageLanding(); 
void resetLeagueCache(); // clear league cache
void upcomingOpponent();
void playGamesOfWeeks(); // every week call this fucntion twice
void normalUserLanding();
void encode(char str[50]); // encode password
void decode(char str[50]); // decode password
void powerReducer(int arr[5]); // player power reducer after each game
void shuffle(int* array, int n); // randomize an array
void fileRemover(char name[50]); // remove a file data
void fileOpener(char FileName[30]);
void teamSorter(team list[4], int s); // sort teams by their score 
void arrayPrinter(int arr[], int len); // print an array
void structSorter(player list[8], int s); // sort a struct by player value
void configFileUpdater(lStatus changedConfig); // update config file, given changed struct
void teamFileUpdater(team changedTeam, int count); // update team file, given changed struct
void playerFileUpdater(player changedPlayer, int count); // update player file, given changed player struct
void weekFileUpdater(int weekNumber, competition match); // update game results
int usernameUniqueChecker(char string[high_limit], team team); // checks if typed username is unique
int sellConfirmation(int sellIds, int teamID); // check some paramteres for selling players
int arrayChecker(int arr[], int a, int len); // check if a number exist in a array
int objectCounter(char filename[20]); // count number of teams/players
int calcDeffence(team myteam); // calculate members attack power
int calcAttack(team myteam); // calculate members deffence power
int checkIfTeamAreReady();
team teamFinder(int id); // find a team by its ID
weeks weeksReader(); // read week games data
lStatus configReader(); // read config file
player playerFinder(int id); // find a player by its ID


// main function
int main() {
    mainPageLanding();
}

    
// long functions
void forgotPassword() {
    printf("For recover your account you have to enter your E-mail:\n");
    char userEmail[high_limit];
    char userPass[high_limit];
    scanf("%s", userEmail);
    team myteam = deffault_value;
    int count = 0;
    int counter = objectCounter("teamcounter.txt");
    for (int i = 1; i <= counter; i++)
    {
        myteam = teamFinder(i);
        if (strcmp(myteam.teamleader.email, userEmail) == 0) {
            count++;
            break;
        }
    }
    if (count == 1) {
        printf("Enter your new password:\n");
        scanf("%s", userPass);
        encode(userPass);
        strcpy(myteam.teamleader.password, userPass);
        teamFileUpdater(myteam, counter);
        waiter();
        printf(FGREEN "Your password succesfully changed...\nredirecting...\n" RESET);
        loading();
        mainPageLanding();
    }
    else {
        printf("No user found with this E-mail");
        adminPageLanding();
    }

}
void normalUserLanding() {
    team myteam = teamFinder(loginedTeamID);
    clearScreen();
    printf("%s - Wallet: %d$\n", myteam.name, myteam.budget);
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
                printf(FGREEN "%s is saved for your team name!\n" RESET , newTeam.name);
                break;
            }
        }
        printf("Enter leader email: (next time you should login with this as your username)\n");
        while (True) {
            scanf("%s", newTeam.teamleader.email);
            if (emailUniqueChecker(newTeam.teamleader.email, newTeam) == 0) {
                printf(FRED "Somebody used your email, try again...\n" RESET);
            }
            else {
                break;
            }
        }
        char myuser[50];
        strcpy(myuser,newTeam.teamleader.email);
        encode(myuser);
        newTeam.id = teamNumber + 1;
        strcpy(newTeam.teamleader.username, newTeam.teamleader.email);
        strcpy(newTeam.teamleader.password, myuser);
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
    clearScreen();
    while (True) {
        FILE* file;
        file = fopen("teams.txt", "rb");
        team myteam;
        for (int i = 0; i < objectCounter("teamcounter.txt"); i++)
        {
            fread(&myteam, sizeof(myteam), 1, file);
            printf("ID: %d | Budget: %d | Members: %d | Name: %s | Status: %s | Score: %d \nLeader Informations:\nUsername: %s\nPassword: %s\nE-mail: %s\n-------------\t-------------\t-------------\t-------------\t\n", myteam.id, myteam.budget, myteam.memberNumber, myteam.name, myteam.status, myteam.score, myteam.teamleader.username, myteam.teamleader.password, myteam.teamleader.email);
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
        printf("  ------------------------------------------------------------------------------------\n");
        FILE* file;
        file = fopen("players.txt", "rb");
        player myplayer;
        printf("  ID\t\tName\t\tDeffence\tAttack\t\tValue\t\tTeam\n");
        printf("  ------------------------------------------------------------------------------------\n");
        for (int i = 0; i < objectCounter("playercounter.txt"); i++)
        {
            fread(&myplayer, sizeof(myplayer), 1, file);
            printf("  %d |\t\t%s\t|\t%d\t|\t%d\t|\t%d\t|\t%s\n", myplayer.id, myplayer.name, myplayer.defenece, myplayer.attack, myplayer.value, myplayer.team);
            printf("  ------------------------------------------------------------------------------------\n");
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
    clearScreen();
    lStatus config = configReader();
    if (config.week == 0) {
        startLeague();
    }
    else if (config.week == 13) {
        showTable();
        printf("What do you want to do now?\n1. Start a new league\n2. Do nothing and leave tha page\n");
        char inp[2];
        while (True) {
            scanf("%s", inp);
            if (strcmp(inp, "1") == 0) {
                team myteam = deffault_value;
                player myplayer = def_val;
                for (int i = 0; i < 4; i++)
                {
                    myteam = teamFinder(config.participatedTeamId[i]);
                    for (int i = 0; i < 5; i++)
                    {
                        myteam.choosenPlayers[i] = myteam.backupChoosenPlayers[i];
                        myplayer = playerFinder(myteam.choosenPlayers[i].id);
                        myplayer.attack = myteam.backupChoosenPlayers[i].attack;
                        myplayer.defenece = myteam.backupChoosenPlayers[i].defenece;
                        playerFileUpdater(myplayer, objectCounter("playercounter.txt"));
                    }
                    teamFileUpdater(myteam,objectCounter("teamcounter.txt"));
                }
                resetLeagueCache();
                waiter();
                fileOpener("config.txt");
                fileOpener("league.txt");
                adminPageLanding();
                break;
            }
            else if (strcmp(inp, "2") == 0) {
                adminPageLanding();
                break;
            }
            else {
                printf("Not valid input...\n");
            }
        }

    }
    else {
        if (checkIfTeamAreReady() == 1) {
            while (True) {
                printf("Games of new week has been started, Have a coffee!\n");
                Sleep(5000);
                printf(FGREEN "-----\n" RESET);
                playGamesOfWeeks();
                playGamesOfWeeks();
                lStatus config2 = configReader();
                team myt = deffault_value;
                player myp = def_val;
                if (config2.week == 6 || config2.week == 7) {
                    for (int i = 0; i < 4; i++)
                    {
                        myt = teamFinder(config2.participatedTeamId[i]);
                        for (int i = 0; i < 5; i++)
                        {
                            myt.choosenPlayers[i] = myt.backupChoosenPlayers[i];
                            myp = playerFinder(myt.choosenPlayers[i].id);
                            myp.attack = myt.backupChoosenPlayers[i].attack;
                            myp.defenece = myt.backupChoosenPlayers[i].defenece;
                            playerFileUpdater(myp, objectCounter("playercounter.txt"));
                        }
                        teamFileUpdater(myt, objectCounter("teamcounter.txt"));
                    }
                }
                printf(FGREEN "-----\n" RESET);
                printf(FCYAN "Updated Scoreboard:\n" RESET);
                showTable();
                printf("back? press enter!\n");
                char userinput[10];
                gets(userinput);
                if (getchar() == '\n') {
                    adminPageLanding();
                    break;
                }
            }
        }
        else {
            printf("All teams are not ready\nredirecting to menu...\n");
            Sleep(5000);
            loading();
            adminPageLanding();
        }


    }
}
void login() {
    clearScreen();
    char username[normal_limit];
    char password[normal_limit];
    char email[normal_limit];
    printf("Enter your E-mail to login:\n");
    scanf("%s", username);
    printf("Enter your password(diffault is your email) to login:\n");
    scanf("%s", password);
    if (strcmp(username, "Admin") == 0 || strcmp(username, "admin") == 0 || strcmp(username, "ADMIN") == 0) {
        if (strcmp(password, "Admin") == 0 || strcmp(password, "admin") == 0 || strcmp(password, "ADMIN") == 0) {
            adminPageLanding();
        }
        else {
            printf(FRED "You entered a wrong username or password, try again...\n" RESET);
            loading();
            mainPageLanding();
        }
    }
    else {
        encode(password);
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
        fclose(file);
        if (confirm == 1) {
            normalUserLanding();
        }
        else {
            printf(FRED "You entered a wrong username or password, try again...\n" RESET);
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
    fileOpener("league.txt");
    // end
    printf("Welcome sir, choose options below\n1- Login\n2- Forgot password\n3- Exit\n");
    while (True) {
        char userInput[10];
        scanf("%s",userInput);
        if (strcmp(userInput,"1") == 0) {
            login();
            break;
        }
        else if (strcmp(userInput, "2") == 0) {
            forgotPassword();
            break;
        }
        else if (strcmp(userInput, "3") == 0) {
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
    char button[100];
    lStatus config = configReader();
    if (config.week == 0) { strcpy(button, "Start League"); }
    else if (config.week == 1 || config.week == 2) { strcpy(button, "Start Week 1"); }
    else if (config.week == 3 || config.week == 4) { strcpy(button, "Start Week 2"); }
    else if (config.week == 5 || config.week == 6) { strcpy(button, "Start Week 3"); }
    else if (config.week == 7 || config.week == 8) { strcpy(button, "Start Week 4"); }
    else if (config.week == 9 || config.week == 10) { strcpy(button, "Start Week 5"); }
    else if (config.week == 11 || config.week == 12) { strcpy(button, "Start Week 6"); }
    else if (config.week == 13) { strcpy(button, "End Season and Announce The Champion"); }
    else { strcpy(button, "Start League"); }
    if (config.week == 7 || config.week == 8) {
        printf("Choose an option by typing its number:\n1. Add team\n2. add player\n3. show teams\n4. show players\n5. %s\n6. Open/Close Transfer Window\n7. Log out\n8. Clear data\n", button);
    }
    else {
        printf("Choose an option by typing its number:\n1. Add team\n2. add player\n3. show teams\n4. show players\n5. %s\n6. Log out\n7. Clear data\n", button);
    }
    if (config.week == 7 || config.week == 8) {
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
                transformWindow();
                break;
            }
            else if (userInput == 7) {
                mainPageLanding();
                break;
            }
            else if (userInput == 8) {
                resetCache();
                break;
            }
            else {
                printf("Not valid input, try again...\n");
            }
        }
    }
    else {
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
            else if (userInput == 7) {
                resetCache();
                break;
            }
            else {
                printf("Not valid input, try again...\n");
            }
        }
    }
}
void buyPlayer() {
    lStatus config = configReader();
    while (True) {
        lStatus config = configReader();
        if (config.transfer == 1) {
            clearScreen();
            FILE* players, * teams, * temp;
            int count = objectCounter("playercounter.txt");
            players = fopen("players.txt", "rb");
            player myplayer = def_val;
            team myteam = deffault_value;
            player arrid[100];
            for (int i = 0; i < count; i++)
            {
                fread(&myplayer, sizeof(myplayer), 1, players);
                arrid[i] = myplayer;
            }
            fclose(players);
            structSorter(arrid, count);
            printf("These players are Free-agent and you can buy them:\n---------------\n");
            for (int i = 0; i < count; i++)
            {
                myplayer = arrid[i];
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
                if (myteam.memberNumber < 8 && myteam.budget >= myplayer.value && strcmp(myplayer.team, "Free-Agent") == 0 || sellConfirmation(buyId, loginedTeamID) == 1) {
                    printf("Your purchase was succesfull!\nwait...\n");
                    strcpy(myplayer.team, myteam.name);
                    myteam.budget = myteam.budget - myplayer.value;
                    myteam.members[myteam.memberNumber] = myplayer;
                    myteam.memberNumber++;
                    Sleep(2000);
                    printf(FGREEN "Player %s added to your team\n" RESET, myplayer.name);
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
        else {
            printf(FRED "You dont have access to this page.\nredirecting to menu...\n" RESET);
            loading();
            normalUserLanding();
            break;
        }
    }
}
void sellPlayer() {
    lStatus config = configReader();
    while (True) {
        lStatus config = configReader();
        if (config.transfer == 1) {
            printf("You have these choices to sell:\n-------------\n");
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
                int k = sellConfirmation(sellId, loginedTeamID);
                if (strcmp(myplayer.team, myteam.name) != 0 || k == 1) {
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
            printf(FGREEN "Player %s sold, %d$ added to your wallet\n" RESET, myplayer.name, myplayer.value);
            printf("back? press enter!\n");
            char userinput[10];
            gets(userinput);
            if (getchar() == '\n') {
                normalUserLanding();
                break;
            }
        }
        else {
            printf(FRED "You dont have access to this page.\nredirecting to menu...\n" RESET);
            loading();
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
                printf("You have to select your squad for upcoming match, type 5 ID's for your squad:\n");
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
    while (True) {
        lStatus config = configReader();
        if (config.week == 0) {
            printf(FRED "League doesnt started yet. wait till admin start a new league...\n" RESET);
            Sleep(2000);
            loading();
            normalUserLanding();
        }
        else {
            showTable();
        }
        printf("back? press enter!\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }
    }
}
void fixtures() {
    while (True) {
        lStatus config = configReader();
        int arid[4] = {config.participatedTeamId[0], config.participatedTeamId[1], config.participatedTeamId[2], config.participatedTeamId[3]};
        if (arrayChecker(arid, loginedTeamID, 4) == 1) {
            weeks* myweek = malloc(sizeof(weeks));
            *myweek = weeksReader();
            if (config.week != 0) {
                printf(FGREEN "Finished Games:\n" RESET);
                for (int i = 0; i < 12; i++)
                {
                    if ((myweek->week[i].firsteam.id == loginedTeamID || myweek->week[i].secondteam.id == loginedTeamID) && strcmp(myweek->week[i].winner, "None") != 0) {
                        printf("%s VS %s | Winner: %s\n", myweek->week[i].firsteam.name, myweek->week[i].secondteam.name, myweek->week[i].winner);
                    }
                }
                printf(FGREEN "\nUpcoming opponents:\n" RESET);
                for (int i = config.week - 1; i < 12; i++)
                {
                    if (myweek->week[i].firsteam.id == loginedTeamID || myweek->week[i].secondteam.id == loginedTeamID) {
                        printf("%s VS %s\n", myweek->week[i].firsteam.name, myweek->week[i].secondteam.name);
                    }
                }
            }
            else {
                printf(FRED "League doesnt started yet...\n" RESET);
            }
        }
        else {
            printf(FRED "Your not participated in league" RESET);
        }
        printf("\nback? press enter!\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }
    }

}
void upcomingOpponent() {
    while (True) {
        lStatus config = configReader();
        int arid[4] = { config.participatedTeamId[0], config.participatedTeamId[1], config.participatedTeamId[2], config.participatedTeamId[3] };
        if (arrayChecker(arid, loginedTeamID, 4) == 1) {
            weeks* myweek = malloc(sizeof(weeks));
            *myweek = weeksReader();
            team myteam = deffault_value; team secondteam = deffault_value;
            int k = 0;
            int teamSelector = 0;
            if (config.week == 0) {
                printf(FRED "League doesnt started yet...\n" RESET);
                loading();
                normalUserLanding();
                break;
            }
            else {
                for (int i = config.week - 1; i < 12; i++)
                {
                    if (myweek->week[i].firsteam.id == loginedTeamID) {
                        k = i;
                        teamSelector = 2;
                        break;
                    }
                    else if (myweek->week[i].secondteam.id == loginedTeamID) {
                        k = i;
                        teamSelector = 1;
                        break;
                    }
                }
                if (teamSelector == 1) {
                    myteam = teamFinder(myweek->week[k].firsteam.id);
                    secondteam = teamFinder(myweek->week[k].secondteam.id);
                }
                else if (teamSelector == 2) {
                    myteam = teamFinder(myweek->week[k].secondteam.id);
                    secondteam = teamFinder(myweek->week[k].firsteam.id);
                }
                int firstTeamGoals = ((calcAttack(myteam) - calcDeffence(secondteam)) / 100);
                int secondTeamGoals = ((calcAttack(secondteam) - calcDeffence(myteam)) / 100);
                if (firstTeamGoals < 0) firstTeamGoals = 0;
                if (secondTeamGoals < 0) secondTeamGoals = 0;
                printf("\n\tName\t\tPlayes\t\tWon\t\tDrawn\t\tLost\t\tGF\t\tGA\t\tGD\t\tScore\t\t\n-------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("\t%s\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", myteam.name, myteam.played, myteam.won, myteam.drawn, myteam.lost, myteam.gol_zade, myteam.gol_khorde, myteam.tafazol, myteam.score);
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
                while (True) {
                    if (secondteam.canBet == 1) {
                        printf("Lets have a bet, What do you think about next game result?\n1. I won\n2. I lost\n3. Equal\n4. Exit\n");
                        char myinp[3]; scanf("%s", myinp);
                        if (firstTeamGoals < secondTeamGoals && strcmp(myinp, "1") == 0) {
                            printf(FGREEN "You choose a correct answer, 1$ added to your wallet" RESET);
                            secondteam.budget += 1; secondteam.canBet = 0;
                            teamFileUpdater(secondteam, objectCounter("teamcounter.txt"));
                            break;
                        }
                        else if (firstTeamGoals > secondTeamGoals && strcmp(myinp, "2") == 0) {
                            printf(FGREEN "You choose a correct answer, 1$ added to your wallet" RESET);
                            secondteam.budget += 1; secondteam.canBet = 0;
                            teamFileUpdater(secondteam, objectCounter("teamcounter.txt"));
                            break;
                        }
                        else if (firstTeamGoals == secondTeamGoals && strcmp(myinp, "3") == 0) {
                            printf(FGREEN "You choose a correct answer, 1$ added to your wallet" RESET);
                            secondteam.budget += 1; secondteam.canBet = 0;
                            teamFileUpdater(secondteam, objectCounter("teamcounter.txt"));
                            break;
                        }
                        else if (strcmp(myinp, "4") == 0) {
                            break;
                        }
                        else {
                            printf(FRED "You choose a wrong answer, your budget decreases 2$ sho khosh\n" RESET);
                            secondteam.canBet = 0;
                            secondteam.budget += -2;
                            teamFileUpdater(secondteam, objectCounter("teamcounter.txt"));
                            break;
                        }
                    }
                    else {
                        printf(FRED "You had a bet before, wait for next week games\n" RESET);
                        break;
                    }
                }
            }
        }
        else
            printf(FRED "Your team does not participated in league" RESET);
        printf("\nback? press enter!\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            normalUserLanding();
            break;
        }
        

    }

}
void changePassword() {
    clearScreen();
    FILE* file,*temp;
    team myteam = deffault_value;
    int count = objectCounter("teamcounter.txt");
    char inputUser[normal_limit];
    printf("if you got a \"OK\" message then you can login with your new password.\nEnter your new password:\n");
    scanf("%s", inputUser);
    encode(inputUser);
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
    printf(FGREEN "Your password successfully changed.\nYou automatically turn into menu in 3 seconds\n" RESET);
    loading();
    normalUserLanding();
}
void startLeague() {
    while (True) {
        FILE* file, * config;
        int replace = 0;
        int rep = 0;
        file = fopen("teams.txt", "rb");
        config = fopen("config.txt", "ab+");
        int count = objectCounter("teamcounter.txt");
        int teamIDs[800];
        int finalTeamList[4];
        team myteam = deffault_value;
        team myteam1 = deffault_value;
        team myteam2 = deffault_value;
        lStatus* league = malloc(sizeof(lStatus));
        lStatus* data = malloc(sizeof(lStatus));
        weeks* week = malloc(sizeof(weeks));
        for (int i = 0; i < count; i++)
        {
            fread(&myteam, sizeof(team), 1, file);
            if (myteam.memberNumber == 8 && strcmp(myteam.status,"Ready") == 0) { // changed data
                teamIDs[replace] = myteam.id;
                replace++;
            }
        }
        if (replace >= 4) {
            printf("Wait for a seconds...\n");
            Sleep(2000);
            clearScreen();
            printf("Available Teams to create a league, select 4 of them:\n");
            while (rep != replace)
            {
                myteam1 = teamFinder(teamIDs[rep]);
                printf("%d- %s\n", myteam1.id, myteam1.name);
                rep++;
            }
            int t1, t2, t3, t4;
            while (True) {
                scanf("%d%d%d%d", &t1, &t2, &t3, &t4);
                if (arrayChecker(teamIDs, t1, replace) == 1 && arrayChecker(teamIDs, t2, replace) == 1 && arrayChecker(teamIDs, t3, replace) == 1 && arrayChecker(teamIDs, t4, replace) == 1) {
                    break;
                }
                else {
                    printf(FRED "There is a problem with your request, try again...\n" RESET);
                }
            }
            int finalTeamList[4] = { t1,t2,t3,t4 };
            strcpy(league->leagueStatus, "Active");
            strcpy(league->button, "Start Week 1");
            league->week = 1;
            for (int i = 0; i < 4; i++)
            {
                myteam = teamFinder(finalTeamList[i]);
                for (int i = 0; i < 5; i++)
                {
                    myteam.backupChoosenPlayers[i] = myteam.choosenPlayers[i];
                }
                teamFileUpdater(myteam, objectCounter("teamcounter.txt"));
                league->participatedTeamId[i] = myteam.id;
            }
            league->transfer = 0;
            clearScreen();
            configFileUpdater(*league);
            fclose(config);
            fclose(file);
            leagueConductor();
            showWeekData();
        }
        else {
            printf("Not enough teams for start a league...\n");
            fclose(config);
            fclose(file);
        }
        printf("back? press enter\n");
        char userinput[10];
        gets(userinput);
        if (getchar() == '\n') {
            adminPageLanding();
            break;
        }
    }
    
}
void leagueConductor() {
    FILE* file,*leaguestatus;
    file = fopen("config.txt", "rb");
    leaguestatus = fopen("league.txt", "ab");
    lStatus* league = malloc(sizeof(lStatus));
    weeks* hafteyeBaziHa = malloc(sizeof(weeks));
    fread(league, sizeof(lStatus), 1, file);
    int id1 = league->participatedTeamId[0];
    int id2 = league->participatedTeamId[1];
    int id3 = league->participatedTeamId[2];
    int id4 = league->participatedTeamId[3];
    int locs[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int gameCharts[10][12][2] = {
        {{id1,id2},{id3,id4},{id1,id3},{id2,id4},{id1,id4},{id2,id3},{id3,id1},{id4,id2},{id4,id1},{id3,id2},{id2,id1},{id4,id3}},
        {{id1,id2},{id4,id3},{id1,id4},{id2,id3},{id1,id3},{id2,id4},{id4,id1},{id3,id2},{id2,id1},{id3,id4},{id4,id2},{id3,id1}},
        {{id2,id1},{id3,id4},{id2,id3},{id1,id4},{id2,id4},{id1,id3},{id3,id2},{id4,id1},{id4,id2},{id3,id1},{id4,id3},{id1,id2}},
        {{id2,id1},{id4,id3},{id2,id4},{id1,id3},{id2,id3},{id1,id4},{id4,id2},{id3,id1},{id4,id1},{id3,id2},{id1,id2},{id3,id4}},
        {{id1,id3},{id2,id4},{id1,id2},{id3,id4},{id1,id4},{id3,id2},{id2,id1},{id4,id3},{id2,id3},{id4,id1},{id3,id1},{id4,id2}},
        {{id1,id3},{id4,id2},{id1,id4},{id3,id2},{id1,id2},{id3,id4},{id4,id1},{id2,id3},{id2,id4},{id3,id1},{id2,id1},{id4,id3}},
        {{id3,id1},{id2,id4},{id3,id2},{id1,id4},{id3,id4},{id1,id2},{id2,id3},{id4,id1},{id2,id1},{id4,id3},{id4,id2},{id1,id3}},
        {{id3,id1},{id4,id2},{id3,id4},{id1,id2},{id3,id2},{id1,id4},{id4,id3},{id2,id1},{id2,id3},{id4,id1},{id2,id4},{id1,id3}},
        {{id1,id4},{id2,id3},{id1,id2},{id4,id3},{id1,id3},{id4,id2},{id2,id1},{id3,id4},{id3,id2},{id4,id1},{id2,id4},{id3,id1}},
        {{id4,id1},{id3,id2},{id4,id3},{id1,id2},{id4,id2},{id1,id3},{id3,id4},{id2,id1},{id2,id3},{id1,id4},{id3,id1},{id2,id4}}
    };

    int randInt = random(locs, 10);
    for (int i = 0; i < 12; i++)
    {
        hafteyeBaziHa->week[i].firsteam = teamFinder(gameCharts[randInt][i][0]);
        hafteyeBaziHa->week[i].secondteam = teamFinder(gameCharts[randInt][i][1]);
        strcpy(hafteyeBaziHa->week[i].winner, "None");

    }
    fwrite(hafteyeBaziHa, sizeof(weeks), 1, leaguestatus);
    fclose(file);
    fclose(leaguestatus);


}
void showWeekData() {
    clearScreen();
    FILE* weekDataFile,*config;
    weekDataFile = fopen("league.txt", "rb");
    config = fopen("config.txt", "ab+");
    team myteam1;
    team myteam2;
    lStatus* data = malloc(sizeof(lStatus));
    weeks* week = malloc(sizeof(weeks));
    fread(data, sizeof(lStatus), 1, config);
    fread(week, sizeof(weeks), 1, weekDataFile);
    printf(FGREEN "Your league has been started\n" RESET);
    printf("Your next move is: %s\nLeague Status: %s\n", data->button, data->leagueStatus);
    printf("Full season games are shown below:\n-------------\n");
    int weekCounter = 2;
    printf("WEEK 1\n");
    for (int i = 0; i < 12; i++)
    {
        myteam1 = teamFinder(week->week[i].firsteam.id);
        myteam2 = teamFinder(week->week[i].secondteam.id);
        printf("%s VS %s ---> Winner is: %s\n", myteam1.name, myteam2.name, week->week[i].winner);
        if (i % 2 == 1) {
            printf("-------------\n");
            if (i != 11) {
                printf("WEEK %d\n", weekCounter);
                weekCounter++;
            }
        }
    }
    fclose(config);
    fclose(weekDataFile);
}
void playGamesOfWeeks() {
    FILE* conf,*weekFile;
    conf = fopen("config.txt", "rb");
    weekFile = fopen("league.txt", "ab+");
    lStatus config = deffault;
    weeks* myweeks = malloc(sizeof(weeks));
    fread(myweeks, sizeof(weeks), 1, weekFile);
    fread(&config, sizeof(lStatus), 1, conf);
    int whichWeekShouldPlaye = config.week;
    int Team1Location = (whichWeekShouldPlaye * 2)-1;
    
    team team1,team2;
    team1 = teamFinder(myweeks->week[whichWeekShouldPlaye-1].firsteam.id);
    team2 = teamFinder(myweeks->week[whichWeekShouldPlaye-1].secondteam.id);
    int firstTeamGoals = ((calcAttack(team1) - calcDeffence(team2)) / 100);
    int secondTeamGoals = ((calcAttack(team2) - calcDeffence(team1)) / 100);
    if (firstTeamGoals < 0) firstTeamGoals = 0;
    if (secondTeamGoals < 0) secondTeamGoals = 0;
    if (firstTeamGoals > secondTeamGoals) {
        // first team changes
        team1.budget += 5;
        team1.score += 3;
        team1.gol_zade += firstTeamGoals; team1.gol_khorde += secondTeamGoals; team1.tafazol += firstTeamGoals - secondTeamGoals;
        team1.won++; team1.played++;
        // second team changes
        team2.budget += 1;
        team2.gol_zade += secondTeamGoals; team2.gol_khorde += firstTeamGoals; team2.tafazol += secondTeamGoals - firstTeamGoals;
        team2.lost++; team2.played++;
        strcpy(myweeks->week[whichWeekShouldPlaye - 1].winner, team1.name);
    }
    else if (firstTeamGoals < secondTeamGoals) {
        team1.budget += 1;
        team1.gol_zade += firstTeamGoals; team1.gol_khorde += secondTeamGoals; team1.tafazol += firstTeamGoals - secondTeamGoals;
        team1.lost++; team1.played++;
        team2.budget += 5;
        team2.score += 3;
        team2.gol_zade += secondTeamGoals; team2.gol_khorde += firstTeamGoals; team2.tafazol += secondTeamGoals - firstTeamGoals;
        team2.won++; team2.played++;
        strcpy(myweeks->week[whichWeekShouldPlaye - 1].winner, team2.name);
    }
    else if (firstTeamGoals == secondTeamGoals) {
        team1.budget += 3;
        team2.budget += 3;
        team1.score += 1; team2.score += 1;
        team1.gol_zade += firstTeamGoals; team1.gol_khorde += secondTeamGoals; team1.tafazol += firstTeamGoals - secondTeamGoals;
        team1.drawn++; team1.played++;
        team2.gol_zade += secondTeamGoals; team2.gol_khorde += firstTeamGoals; team2.tafazol += secondTeamGoals - firstTeamGoals;
        team2.drawn++; team2.played++;
        strcpy(myweeks->week[whichWeekShouldPlaye - 1].winner, "Equal");
    }
    else {
        printf("Something went wrong...\n");
    }
    int arr1[5] = { team1.choosenPlayers[0].id, team1.choosenPlayers[1].id,team1.choosenPlayers[2].id,team1.choosenPlayers[3].id,team1.choosenPlayers[4].id };
    int arr2[5] = { team2.choosenPlayers[0].id, team2.choosenPlayers[1].id,team2.choosenPlayers[2].id,team2.choosenPlayers[3].id,team2.choosenPlayers[4].id };
    printf("%s VS %s ---> Winner: %s\n",team1.name,team2.name,myweeks->week[whichWeekShouldPlaye - 1].winner);
    strcpy(team1.status, "Unready");
    strcpy(team2.status, "Unready");
    for (int i = 0; i < 5; i++)
    {
        myweeks->week[whichWeekShouldPlaye - 1].firsteam.choosenPlayers[i].attack -= 5;
        myweeks->week[whichWeekShouldPlaye - 1].firsteam.choosenPlayers[i].defenece -= 5;
        myweeks->week[whichWeekShouldPlaye - 1].secondteam.choosenPlayers[i].attack -= 5;
        myweeks->week[whichWeekShouldPlaye - 1].secondteam.choosenPlayers[i].defenece -= 5;
    }
    for (int i = 0; i < 5; i++)
    {
        team1.choosenPlayers[i].attack -= 5;
        team1.choosenPlayers[i].defenece -= 5;
        team2.choosenPlayers[i].attack -= 5;
        team2.choosenPlayers[i].defenece -= 5;
    }
    team1.canBet = 1; team2.canBet = 1;
    powerReducer(arr1);
    powerReducer(arr2);
    fclose(weekFile);
    fclose(conf);
    teamFileUpdater(team1, objectCounter("teamcounter.txt"));
    teamFileUpdater(team2, objectCounter("teamcounter.txt"));
    weekFileUpdater(whichWeekShouldPlaye - 1, myweeks->week[whichWeekShouldPlaye - 1]);
    config.week++;
    config.transfer = 0;
    configFileUpdater(config);

}
void showTable() {
    lStatus config = configReader();
    team* myteam = malloc(sizeof(team));
    team arr[4];
    int partic_team[4] = {config.participatedTeamId[0], config.participatedTeamId[1] ,config.participatedTeamId[2] ,config.participatedTeamId[3]};
    for (int i = 0; i < 4; i++)
    {
        *myteam = teamFinder(partic_team[i]);
        arr[i] = *myteam;
    }
    teamSorter(arr, 4);
    printf("\n\tName\t\tPlayes\t\tWon\t\tDrawn\t\tLost\t\tGF\t\tGA\t\tGD\t\tScore\t\t\n-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 4; i++)
    {
        *myteam = arr[i];
        printf("\t%s\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", myteam->name, myteam->played, myteam->won, myteam->drawn, myteam->lost, myteam->gol_zade, myteam->gol_khorde, myteam->tafazol, myteam->score);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
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
void resetCache() {
    fileRemover("teams.txt");
    fileRemover("players.txt");
    fileRemover("teamcounter.txt");
    fileRemover("playercounter.txt");
    remove("league.txt");
    remove("config.txt");
    waiter();
    printf(FGREEN "Done!" RESET);
    printf("You logged out in 3 seconds\n");
    loading();
    mainPageLanding();
}
void clearScreen() {
    system("cls");
}
void transformWindow() {
    lStatus config = deffault;
    config = configReader();
    printf("1. Close\n2. Open\n");
    char vrd[5];
    while (True) {
        scanf("%s", vrd);
        if (strcmp(vrd, "1") == 0) {
            config.transfer = 0;
            configFileUpdater(config);
            waiter();
            printf(FGREEN "Done!\nReturning back to panel...\n" RESET);
            Sleep(3000);
            adminPageLanding();
            break;
        }
        else if (strcmp(vrd, "2") == 0) {
            config.transfer = 1;
            configFileUpdater(config);
            waiter();
            printf(FGREEN "Done!\nReturning back to panel...\n" RESET);
            Sleep(3000);
            adminPageLanding();
            break;
        }
        else {
            printf("Not valid input...\n");
        }
    }
}
void encode(char *str) {
    int i = 0;
    int k;
    char temp;
    while (str[i] != '\0') {
        k = str[i];
        temp = k - 30;
        *(str + i) = temp;
        i++;
    }
}
void decode(char *str) {
    int i = 0;
    int k;
    char temp;
    while (str[i] != '\0') {
        k = str[i];
        temp = k + 30;
        *(str + i) = temp;
        i++;
    }
}
void resetLeagueCache() {
    lStatus config = configReader();
    team myteam = deffault_value;
    int teamids = 0;
    for (int i = 0; i < 4; i++)
    {
        teamids = config.participatedTeamId[i];
        myteam = teamFinder(teamids);
        myteam.won = 0, myteam.gol_khorde = 0, myteam.gol_zade = 0, myteam.tafazol = 0, myteam.drawn = 0, myteam.lost = 0, myteam.won = 0, myteam.score = 0, myteam.played = 0;
        teamFileUpdater(myteam, objectCounter("teamcounter.txt"));
    }
    remove("config.txt");
    remove("league.txt");
}
void powerReducer(int arr[5]) {
    int id;
    player myplayer = def_val;
    for (int i = 0; i < 5; i++)
    {
        id = arr[i];
        myplayer = playerFinder(id);
        myplayer.attack -= 5; myplayer.defenece -= 5;
        playerFileUpdater(myplayer, objectCounter("playercounter.txt"));
    }
}
void fileRemover(char name[50]) {
    FILE* file;
    file = fopen(name, "wb+");
    fclose(file);
}
void fileOpener(char FileName[30]) {
    FILE* file;
    file = fopen(FileName, "rb+");
    if (!file) {
        file = fopen(FileName, "wb+");
        if (strcmp(FileName, "config.txt") == 0) {
            lStatus config = deffault;
            strcpy(config.button, "Start League");
            fwrite(&config, sizeof(lStatus), 1, file);
        }
    }
    fclose(file);
}
void arrayPrinter(int arr[], int len) {
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
}
void structSorter(player list[200], int s)
{
    int i, j;
    player temp;

    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1 - i); j++)
        {
            if (list[j].value < list[j + 1].value)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}
void teamSorter(team list[4], int s)
{
    int i, j;
    team temp;

    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1 - i); j++)
        {
            if (list[j].score < list[j + 1].score)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
            else if (list[j].score == list[j + 1].score) {
                if (list[j].tafazol < list[j + 1].tafazol)
                {
                    temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
                else if (list[j].tafazol == list[j + 1].tafazol) {
                    if (list[j].gol_zade < list[j + 1].gol_zade)
                    {
                        temp = list[j];
                        list[j] = list[j + 1];
                        list[j + 1] = temp;
                    }
                    else if (list[j].gol_zade == list[j + 1].gol_zade) {
                        if (list[j].gol_khorde > list[j + 1].gol_khorde)
                        {
                            temp = list[j];
                            list[j] = list[j + 1];
                            list[j + 1] = temp;
                        }
                    }
                }
            }
        }
    }
}
void configFileUpdater(lStatus changedConfig) {
    FILE* config, * temp;
    config = fopen("config.txt", "wb");
    fclose(config);
    config = fopen("config.txt", "wb");
    fwrite(&changedConfig, sizeof(lStatus), 1, config);
    fclose(config);
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
void weekFileUpdater(int weekNumber, competition match) {
    FILE* weekFile;
    weekFile = fopen("league.txt", "ab+");
    weeks* week = malloc(sizeof(weeks));
    fread(week, sizeof(weeks), 1, weekFile);
    week->week[weekNumber] = match;
    fclose(weekFile); 
    weekFile = fopen("league.txt", "wb+");
    fwrite(week, sizeof(weeks), 1, weekFile); 
    fclose(weekFile);
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
    fclose(file);
    if (calcCounter == 1) {
        return False;
    }
    else
        return True;
}
int emailUniqueChecker(char string[high_limit], team team) {
    int count = objectCounter("teamcounter.txt");
    FILE* file;
    int calcCounter = 0;
    file = fopen("teams.txt", "rb");
    for (int i = 0; i < count; i++)
    {
        fread(&team, sizeof(team), 1, file);
        if (strcmp(team.teamleader.email, string) == 0)
            calcCounter++;
    }
    fclose(file);
    if (calcCounter == 1) {
        return False;
    }
    else
        return True;
}
int sellConfirmation(int sellIds, int teamID) {
    team myteam = deffault_value;
    myteam = teamFinder(teamID);
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (myteam.choosenPlayers[i].id == sellIds) {
            counter++;
        }
    }
    if (counter != 0) {
        return 1;
    }
    else
        return 0;
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
int objectCounter(char fileName[20]) {
    FILE* file;
    file = fopen(fileName, "rb");
    fseek(file, 0, SEEK_END);
    int k = ftell(file);
    fclose(file);
    return k;
}
int random(int arr[],int lenArr) {
    srand(time(NULL));
    int randomIndex = rand() % lenArr;
    int randomValue = arr[randomIndex];
    return randomValue;
}
int calcDeffence(team myteam) {
    int sumDef = 0;
    for (int i = 0; i < 5; i++)
    {
        sumDef += myteam.choosenPlayers[i].defenece;
    }
    return sumDef;
}
int calcAttack(team myteam) {
    int sumAttacks = 0;
    for (int i = 0; i < 5; i++)
    {
        sumAttacks = sumAttacks + myteam.choosenPlayers[i].attack;
    }
    return sumAttacks;
}
int checkIfTeamAreReady() {
    lStatus config = configReader(); int counter = 0;
    team myteam = deffault_value;
    for (int i = 0; i < 4; i++)
    {
        myteam = teamFinder(config.participatedTeamId[i]);
        if (strcmp(myteam.status, "Unready") == 0)
            counter++;
    }
    if (counter != 0)
        return 0;
    else
        return 1;
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
            fclose(file);
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
            fclose(file);
            return myteam;
        }
    }
}  
lStatus configReader() {
    FILE* conf; conf = fopen("config.txt", "ab+");
    lStatus configs;
    fread(&configs, sizeof(lStatus), 1, conf); fclose(conf);
    return configs;
}
weeks weeksReader() {
    weeks *myweek = malloc(sizeof(weeks));
    FILE* file;
    file = fopen("league.txt", "rb");
    fread(myweek, sizeof(weeks), 1, file);
    fclose(file);
    return *myweek;
}