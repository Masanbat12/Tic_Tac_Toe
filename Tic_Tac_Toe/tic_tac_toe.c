#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#ifdef _WIN32
    #define OS "nt"
#elif __unix__
    #define OS "posix"
#endif 

void board(char x, char o, char *u1, char *u2, char *a);
void rules();
int checkforwin(char *a);
bool decision(char *x, char *o, char *u1);

int main() {
    FILE *program;
    char x, o;
    program = fopen("score.txt", "a+");
    fclose(program);
    char a[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char u1[50], u2[50];
    int player = 1;
    int choice, score = -1;
    char symbol;

    if (strcmp(OS, "nt") == 0)
        system("color 09");

    rules();
    printf("\n\nType 1 to start the game:\nType 2 to view leader board:\n");
    int cho;
    scanf("%d", &cho);
    switch(cho) {
        case 1:
            do {
                program = fopen("score.txt", "a+");
                printf("\nEnter name of player1: ");
                scanf("%s", u1);
                fprintf(program, "\n%s", u1);
                printf("Enter name of player2: ");
                scanf("%s", u2);
                fprintf(program, "\t%s", u2);
                fclose(program);
                if (!strcmp(u1, u2)) {
                    printf("Enter names of different players!\n\n");
                }
            } while (!strcmp(u1, u2));
            decision(&x, &o, u1);
            if (strcmp(OS, "nt") == 0)
                system("color fc");
            board(x, o, u1, u2, a);
            do {
                player = (player % 2) ? 1 : 2;
                printf("%s Type any digit from 1-9 to fill your response: ", (player == 1) ? u1 : u2);
                scanf("%d", &choice);
                symbol = (player == 1) ? x : o;
                if (choice >= 1 && choice <= 9 && a[choice - 1] == '0' + choice) {
                    a[choice - 1] = symbol;
                } else {
                    printf("Wrong Selection\n");
                    player--;
                }
                score = checkforwin(a);
                player++;
                board(x, o, u1, u2, a);
            } while (score == -1);
            program = fopen("score.txt", "a+");
            if (score == 1) {
                printf("\n\nPlayer %d %s Wins!\n\n", player % 2 + 1, (player % 2) ? u2 : u1);
                fprintf(program, "\t%s", (player % 2) ? u2 : u1);
            } else {
                printf("\n\nGame Draws!\n\n");
                fprintf(program, "\t%s", "DRAW");
            }
            fclose(program);
            break;
        case 2:
            if (strcmp(OS, "nt") == 0) 
                system("cls");
            else if (strcmp(OS, "posix") == 0)
                system("clear");
            printf("\n\n");
            printf("\tLEADERBOARD\n\n");
            char c;
            program = fopen("score.txt", "r");
            while ((c = getc(program)) != EOF) {
                printf("%c", c);
            }
            fclose(program);
            break;
        default:
            printf("\n\nShould have typed 1 to play the game!\nHope to see you back soon!\n\n");
            break;
    }
    return 0;
}
int checkforwin(char *a)
{
    if(a[0]==a[1] && a[1]==a[2])
        return 1;
    else if(a[3]==a[4] && a[4]==a[5])
        return 1;
    else if(a[6]==a[7] && a[7]==a[8])
        return 1;
    else if(a[0]==a[3] && a[3]==a[6])
        return 1;
    else if(a[1]==a[4] && a[4]==a[7])
        return 1;
    else if(a[2]==a[5] && a[5]==a[8])
        return 1;
    else if(a[0]==a[4] && a[4]==a[8])
        return 1;
    else if(a[2]==a[4] && a[4]==a[6])
        return 1;
    else if(a[0]!='1' && a[1]!='2' && a[2]!='3' && a[3]!='4' && a[4]!='5' && a[5]!='6' && a[6]!='7' && a[7]!='8' && a[8]!='9')
        return 0;
    else
        return -1;
}

void board(char x, char o, char *u1, char *u2, char *a)
{
    if (strcmp(OS, "nt") == 0)
        system("cls");
     else if (strcmp(OS, "posix") == 0)
        system("clear");
    printf("\tTic-Tac-Toe\n\n");
        printf("\n\n");
        printf("%s:- (%c)\n%s:-  (%c)\n\n\n",u1,x,u2,o);

        printf("  %c |  %c | %c\n",a[0],a[1],a[2]);
        printf("    |    |    \n");
        printf("----|----|----\n");
        printf("    |    |    \n");
        printf("  %c |  %c | %c\n",a[3],a[4],a[5]);
        printf("    |    |    \n");
        printf("----|----|----\n");
        printf("  %c |  %c | %c\n",a[6],a[7],a[8]);
        printf("    |    |    \n");
    }
void rules()
{
    char link;
    printf("\tTic-Tac-Toe\n\n");
    printf("Welcome to the most played 2D game and a sort of fun using X and O\n\n");
    printf("Rules:-\n");
    printf("\n1:Each player will be entering the number to put respective X or O in the desired position");
    printf("\n2:Player who gets a combination of 3 same characters either diagonal or horizontally or \n  vertically will be declared as the winner");
    printf("\n\nEnjoy the game! Be a Winner!\n\n");
    printf("For more clarifications and understanding press Y else type any other character:- ");
    scanf("%c",&link);
    if (link == 'y' || link == 'Y') {
        if (strcmp(OS, "nt") == 0)
            system("start http://www.wikihow.com/Play-Tic-Tac-Toe");
        else if (strcmp(OS, "posix") == 0)
            system("firefox http://www.wikihow.com/Play-Tic-Tac-Toe");
    }

}
bool decision(char *x, char *o, char *u1)
{
    char dec;
    printf("\n\n");
    do {
        printf("Player1 %s choose the X or 0:",u1);
        dec=getchar();
        scanf("%c", &dec);
    } while(dec!='X' && dec!='x' && dec!='0');
    if (dec=='X' || dec=='x') {
        *x='X';
        *o='0';
    }
    else {
        *x='0';
        *o='X';
    }
    return 1;
}