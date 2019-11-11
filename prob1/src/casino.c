#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define VIEW_AMT 100
#define CHANGE_AMT 200

typedef char			_t_name;
typedef unsigned int	_t_money;
typedef unsigned int	_t_gcnt;
typedef char			_t_flag;

typedef struct _user_info {
	_t_name  name[6];
	_t_money deposit;
	_t_gcnt  win_count;
	_t_gcnt  lose_count;
	_t_money betting_history[100];
	_t_gcnt  betting_history_count;
	_t_flag	betting_history_result[100];

} User_Info;

int read_int()
{
	long int i;
	char *p;

	char buf[100];
	if(fgets(buf, sizeof(buf), stdin) != NULL) {
		i = strtol(buf, &p, 10);
		if(buf[0] != '\n' && (*p == '\n' || *p == '\0')) {
			return i;
		}
	}
	return -1;
}


void print_user_info(User_Info* user) 
{
	printf("-----------------------------------------------------------\n");
	printf("ID\t\t: %s\n", user->name);
	printf("Deposit	\t: %d USD\n", user->deposit);
	printf("Win game \t: %d\n", user->win_count);
	printf("Lose game\t: %d\n", user->lose_count);
	printf("Betting history\n");
	for(int i = 0; i < user->betting_history_count; i++) {
		printf("   Round %d, Betting Amount : %d, Result : ", (i+1), user->betting_history[i]);
		if(user->betting_history_result[i] == 'W') {
			printf("Win\n");
		}
		else {
			printf("Lose\n");
		}
	}
	printf("-----------------------------------------------------------\n");
	fflush(stdout);
}

int get_random(int modulus)
{
	time_t t;
	srand((unsigned)time(&t));
	return rand() % modulus;	
}

void create_user(User_Info* user)
{
	printf("At first, you should make your ID for this game.\n");
	printf("Enter your ID (five characters) : ");
	fflush(stdout);
	//scanf("%5s%[^\n]s\n", user->name);
	fgets(user->name, 6, stdin);

	while(user->deposit <= 0) {
		user->deposit = get_random(100) % 100;
	}
	printf("\nYour initial condition is :\n");
	fflush(stdout);
	print_user_info(user);
	printf("\nIf you lose all deposit, this game will be over.\n");
	printf("Now..let's start! Good luck!\n\n");
	fflush(stdout);
}

void wellcome_banner()
{
	printf("===========================================================\n");
	printf("Welcome to the Casino World!\n");
	printf("This game do not require any seed money,\n");
	printf("it will be deposited depending on your luck for free.\n");
	printf("Have a good time!\n");
	printf("===========================================================\n\n");
	fflush(stdout);
}

int betting(User_Info* user, _t_money* betamt)
{
	while(1) {
		printf("\nBetting amount (USD) : ");
		fflush(stdout);
		int result = read_int();
		if(result <= 0) {
			printf("\nNo, no, you entered wrong number, please re-enter right number..\n");
			fflush(stdout);
			continue;
		}
		*betamt = (_t_money)result;
		if(*betamt > user->deposit) {
			printf("\nYou can not bet more money than you have..\n");
			fflush(stdout);
			continue;
		} 
		user->betting_history[user->betting_history_count] = *betamt;	
		return 0;
	}
}

void game_loop(User_Info* user)
{
	while(1){
		_t_money betamt;
		betting(user, &betamt);
		printf("You are betting : %d USD\n", betamt);
		printf("Now, start game!! :\n");
		fflush(stdout);

		printf("> Your Number : ");
		int a[3];
		for(int i = 0; i < 3; i++) {
			a[i] = get_random(10);
			printf("%d ", a[i]); fflush(stdout); sleep(1);
		}
		if(a[0] == a[1] && a[0] == a[2] && a[1] == a[2]) {
			printf("\n\n** Wow!!, Jackpot!!! You will have 100 times more than your betting amount!! **\n\n");
			fflush(stdout);
			user->deposit = user->deposit + betamt*100;
			user->win_count++;
			user->betting_history_result[user->betting_history_count] = 'W';
		}
		else if(a[0] == a[1] || a[0] == a[2] || a[1] == a[2]) {
			printf("\n\n** Two number is same, you will have 2 times more than your betting amount.\n\n");
			fflush(stdout);
			user->deposit = user->deposit + betamt*10;
			user->win_count++;
			user->betting_history_result[user->betting_history_count] = 'W';
		}
		else {
			printf("\n\n...You lose your betting money...sorry...\n\n");
			fflush(stdout);
			user->deposit = user->deposit - betamt;
			user->lose_count++;
		}
		user->betting_history_count++;
		print_user_info(user);			

		if(user->deposit <= 0) {
			printf("\nYou lost your all money, see you again~\n\n");
			break;
		}
		else {
			while(1) {
				printf("\nMenu :\n");
				printf("   - Another game [y]\n");
				printf("   - Exit game [n]\n");
				if(user->deposit >= VIEW_AMT) {
					printf("   - View betting history [h]\n");
				}
				if(user->deposit >= CHANGE_AMT) {
					printf("   - If you have to show your betting history to your family, you can change it for your safety. [m]\n");
				}
				printf("\nWhich option do you select? ");
				fflush(stdout);
				char buf[2];
				if(fgets(buf, sizeof(buf), stdin) != NULL) {
					while(getchar() != '\n');
					if(buf[0] == 'y') {
						printf("\n"); fflush(stdout);
						break;
					}
					else if(buf[0] == 'n') {
						printf("\n\nBye...see you again\n");
						fflush(stdout);
						return;
					}
					else if(buf[0] == 'h' && user->deposit >= VIEW_AMT) {
						printf("\nWhich round do you want to view? (number) ");
						fflush(stdout);
						int index = read_int();
						if(index <= 0) {
							printf("-----------------------------------------------------------\n");
							printf("\n..Oh..no, did you try to exploit?...come on, do not....\n");
							printf("-----------------------------------------------------------\n");
							continue;
						}
						printf("-----------------------------------------------------------\n");
						printf("\nThe %d round's your betting amount is %d, and you ", index, user->betting_history[index-1]);
						if(user->betting_history_result[index-1] == 'W') {
							printf("Win.\n");
						}
						else {
							printf("Lose.\n");
						}
						printf("-----------------------------------------------------------\n");
						fflush(stdout);
					}
					else if(buf[0] == 'm' & user->deposit >= CHANGE_AMT) {
						printf("\nWhich round do you want to change? (number) ");
						fflush(stdout);
						int index = read_int();
						if(index <= 0) {
							printf("-----------------------------------------------------------\n");
							printf("\n..Oh..no, did you try to exploit?...come on, do not....\n");
							printf("-----------------------------------------------------------\n");
							continue;
						}
						printf("\nWhat amount do you want to change?.. (number) ");
						fflush(stdout);
						int amt = read_int();
						user->betting_history[index-1] = amt;
						printf("-----------------------------------------------------------\n");
						printf("\nThe %d round's your betting amount is %d, and you ", index, user->betting_history[index-1]);
						if(user->betting_history_result[index-1] == 'W') {
							printf("Win.\n");
						}
						else {
							printf("Lose.\n");
						}
						printf("-----------------------------------------------------------\n");
						fflush(stdout);
					}
					else {
						printf("\nWrong answer..\n");
						fflush(stdout);
					}
				}
				else {
					printf("\nWrong answer..\n");
				}
			}
		}
	}
}

int main()
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	wellcome_banner();
	User_Info user; user.deposit=0; user.win_count=0; user.lose_count=0; user.betting_history_count=0;
	for(int i = 0; i < 100; i++) {
		user.betting_history[i] = 0;
		user.betting_history_result[i] = 'L';
	}
	create_user(&user);
	game_loop(&user);
	return 0;
}
