// BE NUME KHUDA

// libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// defines
#define normal_limit 50


// function declaration
void  mainPageLanding();
void forgotPassword();
void adminPageLanding();
void normalUserLanding();


// variables
char email[normal_limit];
char username[normal_limit];
char password[normal_limit];

int main() {
    mainPageLanding();
    return 0;
}

// functions
void mainPageLanding() {
    printf("Welcome sir, choose options below\n1- Login(L)\n2- Forgot password(f)\n");
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
    printf("Choose an option:\n1- Add team(add)\n2- add player(addp)\n3- show teams(showt)\n4- show players(showp)\n5- item 5(it5)");
}
void normalUserLanding() {
    printf("Choose an option:\n1- Buy player(buy)\n2- Sell player(sell)\n3- Select team/submit team(steam)\n4- Show scoreboard(scoreboard)\n5- Fixtures(fixt)\n6- Upcoming opponent(upop)\n7- Change password(changepsw)\n8- Exit(wq)");
}