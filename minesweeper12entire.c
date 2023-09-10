#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <windows.h>
#pragma warning(disable:4996)

struct person {
	char name[51] = { 0 };
	int win = 0;
	int loss = 0;
};
void design1(int i);
void design2(long int i);
void design(int t);
void beep();
int mainpage(struct person*);
void changename(struct person*);
int play(struct person*);
int openzero(int f);

wchar_t playfield[12][12];
int n, countminet, arrmine[40], countmine, countflag;

int main() {
	_setmode(_fileno(stdout), _O_U8TEXT);
	srand(time(NULL));
	struct person user;
	wprintf(L"\n \x1b[1;35;40mHello my friend\x1b[1;37;40m! \x1b[1;35;40mWelcome to \x1b[1;37;40m** Minesweeper **\n \x1b[1;35;40mEnter your username to enter the main page\x1b[1;37;40m:\n");
	scanf("%[^\n]S", user.name);
	system("cls||clear");
	int a = mainpage(&user);
	if (a == -1)
		return 0;
} //main ???? 
//****************************************************************************mainpage
int mainpage(struct person* user) {
	system("cls");
	char ch;
	system("color 0B");
	wprintf(L"\n \x1b[1;96;40m\x0004 Username: \x1b[1;37;40m%S\n \x1b[1;96;40m\x0004 Number of wins: \x1b[1;37;40m%d\n \x1b[1;96;40m\x0004 Number of losses: \x1b[1;37;40m%d\n\n", user->name, user->win, user->loss);
	wprintf(L" \x1b[1;96;40mPlease choose an option:(enter 1/2/3)\n");
	wprintf(L" \x1b[1;37;40m1* \x1b[1;93;40mChange name!\n \x1b[1;37;40m2* \x1b[1;34;40mplay!\n \x1b[1;37;40m3* \x1b[1;31;40mexit!\n\x1b[1;37;40m");
line1:getchar();
	ch = getchar();
	if (ch == '1') {
		getchar();
		system("cls||clear");
		changename(user);
		return 1;
	}
	else if (ch == '2') {
		getchar();
		system("cls||clear");
		play(user);
		return 1;
	}
	else if (ch == '3')
		return -1;
	else if (ch != '1' && ch != '2' && ch != '3') {
		wprintf(L" \a\x1b[1;31;40mPlease enter a number from 1 to 3:\x1b[1;37;40m\n");
		goto line1;
	}
}
//***********************************************************************changename
void changename(struct person* user) {
	system("color 0E");
	wprintf(L"\n Enter your desired username:\n\x1b[1;37;40m");
	scanf("%[^\n]s", user->name);
	system("cls");
	mainpage(user);
} //????? ???
//*******************************************************************************play
int play(struct person* user) {
	_setmode(_fileno(stdout), _O_U8TEXT);
line4:system("cls||clear");
	char ch, s[6];
	int size;
	wprintf(L"\n \x1b[1;34;40mChoose a playground:(enter 1/2)\n \x1b[1;37;40m1* \x1b[1;95;40mSmall(9*9)\n \x1b[1;37;40m2* \x1b[1;96;40mMedium(12*12)\n\x1b[1;37;40m");
line2:ch = getchar();
	if (ch == '1') {
		countmine = 10;
		countminet = 10;
		countflag = 10;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				playfield[i][j] = L'.';
		}
	}
	if (ch == '2') {
		size = 12;
		countmine = 20;
		countminet = 20;
		countflag = 20;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++)
				playfield[i][j] = L'.';
		}
	}
	else if (ch != '1' && ch != '2') {
		wprintf(L"\a \x1b[1;31;40mPlease enter a number from 1 or 2:\n\x1b[1;37;40m");
		getchar();
		goto line2;
	}
	system("cls||clear");
	wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
	if (ch == '1')
		n = 9;
	else n = 12;
	for (int i = 0; i < n; i++) {
		wprintf(L"\n\x007C");
		for (int j = 0; j < n; j++)
			wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
	}

	int i = 0;
	while (i < countminet) {
		int count = 0;
		int a = rand() % (n * n) + 1;
		for (int k = 0; k < n; k++) {
			if (a % n != 0 && playfield[k][a % n - 1] == L'\x01A0')
				count++;
			if (a % n == 0 && playfield[k][n - 1] == L'\x01A0')
				count++;
		}
		if (a % n != 0 && playfield[a / n][a % n - 1] == L'.' && count < 3) {
			if (i == 0) {
				wprintf(L"\n\n\x1b[1;35;40mThe upper ");
			}
			if (i == 1) {
				wprintf(L"\x1b[1;95;40mleft house ");
			}
			if (i == 2) {
				wprintf(L"\x1b[1;34;40mis house ");
			}
			if (i == 3) {
				wprintf(L"\x1b[1;94;40mnumber 1, ");
			}
			if (i == 4) {
				wprintf(L"\x1b[1;36;40mand moving ");
			}
			if (i == 5) {
				wprintf(L"\x1b[1;96.40mto the right, ");
			}
			if (i == 6) {
				wprintf(L"\x1b[1;32;40mthe number of ");
			}
			if (i == 7) {
				wprintf(L"\x1b[1;33;40mhouses, ");
			}
			if (i == 8) {
				wprintf(L"\x1b[1;31;40mincreases.");
			}
			if (i == 9)
				wprintf(L"\x1b[1;91;40m ");
			if (i == 10)
				wprintf(L"\x1b[1;97;40m ");
			if (i == 11)
				wprintf(L"\x1b[1;90;40m ");
			playfield[a / n][a % n - 1] = L'\x01A0';
			arrmine[i] = a;// arry of number of places that have mine
			i++;
		}
		if (a % n == 0 && playfield[a / n - 1][n - 1] == L'.' && count < 3) {
			if (i == 0)
				wprintf(L"\n\n\x1b[1;35;40mThe upper ");
			if (i == 1)
				wprintf(L"\x1b[1;95;40mleft house ");
			if (i == 2)
				wprintf(L"\x1b[1;34;40mis house ");
			if (i == 3)
				wprintf(L"\x1b[1;94;40mnumber 1, ");
			if (i == 4)
				wprintf(L"\x1b[1;36;40mand moving ");
			if (i == 5)
				wprintf(L"\x1b[1;96.40mto the right, ");
			if (i == 6)
				wprintf(L"\x1b[1;32;40mthe number of ");
			if (i == 7)
				wprintf(L"\x1b[1;33;40mhouses, ");
			if (i == 8)
				wprintf(L"\x1b[1;31;40mincreases.");
			if (i == 9)
				wprintf(L"\x1b[1;91;40m ");
			if (i == 10)
				wprintf(L"\x1b[1;97;40m ");
			if (i == 11)
				wprintf(L"\x1b[1;90;40m ");
			playfield[a / n - 1][n - 1] = L'\x01A0';
			arrmine[i] = a;// arry of number of places that have mine
			i++;
		}

	}//making random playfield
line6: wprintf(L"\n\x1b[1;37;40mEnter a numer from 1 to %d + space + R or L: ", n * n); //////goto////////
line3:getchar();
	scanf("%[^\n]s", s);
	if (s[0] != '0' && s[0] != '1' && s[0] != '2' && s[0] != '3' && s[0] != '4' && s[0] != '5' && s[0] != '6' && s[0] != '7' && s[0] != '8' && s[0] != '9') {
		wprintf(L"\n\a\x1b[1;31;40mThe input is incorrect.\x1b[1;37;40m");
		goto line6;
	}
	int f = atoi(strtok(s, " "));
	char* p = strtok(NULL, " ");
	if (p == NULL) {
		wprintf(L"\n\a\x1b[1;31;40mThe input is incorrect.\x1b[1;37;40m");
		goto line6;
	}
	else if (strcmp(p, "R") != 0 && strcmp(p, "r") != 0 && strcmp(p, "L") != 0 && strcmp(p, "l") != 0) {
		wprintf(L"\n\a\x1b[1;31;40mThe input is incorrect.\x1b[1;37;40m");
		goto line6;
	}

	if (f % n != 0) {
		if (playfield[f / n][f % n - 1] == '0' || playfield[f / n][f % n - 1] == '1' || playfield[f / n][f % n - 1] == '2' || playfield[f / n][f % n - 1] == '3' || playfield[f / n][f % n - 1] == '4' || playfield[f / n][f % n - 1] == '5' || playfield[f / n][f % n - 1] == '6' || playfield[f / n][f % n - 1] == '7' || playfield[f / n][f % n - 1] == '8' || f > n * n) {
			wprintf(L"\n\a\x1b[1;31;40mThe number is illegal.Enter an other number + space + R or L:\x1b[1;37;40m");
			goto line3;
		}// چک کردن مجاز بودن خانه
	}

	if (f % n == 0) {
		if (playfield[f / n - 1][n - 1] == '0' || playfield[f / n - 1][n - 1] == '1' || playfield[f / n - 1][n - 1] == '2' || playfield[f / n - 1][n - 1] == '3' || playfield[f / n - 1][n - 1] == '4' || playfield[f / n - 1][n - 1] == '5' || playfield[f / n - 1][n - 1] == '6' || playfield[f / n - 1][n - 1] == '7' || playfield[f / n - 1][n - 1] == '8' || f > n * n) {
			wprintf(L"\a\x1b[1;31;40mThe number is illegal.Enter an other number + space + R or L:\x1b[1;37;40m");
			goto line3;
		}// چک کردن مجاز بودن خانه
	}
	system("cls||clear");
	bool b;
	for (i = 0; i < countminet; i++)
		if (arrmine[i] == f) {
			b = 1;// می شودb=1اگر درون خانه وارد شده بمب باشد 
			break;
		}
	if (i == countminet)
		b = 0;
	if (b) {
		if (strcmp(p, "L") == 0 || strcmp(p, "l") == 0) {      /////////LLL//////

			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x01A0') {
				user->loss++;
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] == L'\x01A0') {
							Beep(500, 400);
							for (int k = 0; k < 300000000; k++);
							wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						else if (playfield[i][j] == L'\x2660')
							wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						else if (playfield[i][j] == '.')
							wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				wprintf(L"\n\n \x1b[1;96;40mYou lost! \x1b[1;31;40m\x2665\x1b[1;37;40m");
				wprintf(L"\n\n Do you want to continue?(Y/N)");
			line5: getchar();
				ch = getchar();
				if (ch == 'Y' || ch == 'y') {
					getchar();
					goto line4;
				}
				else if (ch == 'N' || ch == 'n') {
					mainpage(user);
					return 1;///////////possibility of error and bug///////////////
				}
				else {
					wprintf(L"\a \x1b[1;31;40mPlease enter Y/N:\x1b[1;37;40m");
					goto line5;
				}
			}

			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x01A0') {
				user->loss++;
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] == L'\x01A0') {
							Beep(500, 400);
							for (int k = 0; k < 300000000; k++);
							wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						else if (playfield[i][j] == L'\x2660')
							wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						else if (playfield[i][j] == '.')
							wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				wprintf(L"\n\n \x1b[1;96;40mYou lost! \x1b[1;31;40m\x2665\x1b[1;37;40m");
				wprintf(L"\n\n Do you want to continue?(Y/N)");
			line20: getchar();
				ch = getchar();
				if (ch == 'Y' || ch == 'y') {
					getchar();
					goto line4;
				}
				else if (ch == 'N' || ch == 'n') {
					mainpage(user);
					return 1;///////////possibility of error and bug///////////////
				}
				else {
					wprintf(L"\a \x1b[1;31;40mPlease enter Y/N:\x1b[1;37;40m");
					goto line20;
				}
			}
			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x2660') {
				goto line6;
			}
			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x2660') {
				goto line6;
			}

		}


		else if (strcmp(p, "R") == 0 || strcmp(p, "r") == 0) {  //////RRR/////
			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x01A0') {
				if (countflag > 0) {
					playfield[f / n][f % n - 1] = L'\x2660';
					countmine--;
					countflag--;
				}
				if (countmine == 0) {
					user->win++;
					wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
					for (int i = 0; i < n; i++) {
						wprintf(L"\n\x007C");
						for (int j = 0; j < n; j++) {
							if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x01A0')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);

						}
					}
					int t = 0;
					design(t);
					wprintf(L"\n\n Do you want to continue?(Y/N)");
				line7: getchar();
					ch = getchar();
					if (ch == 'Y' || ch == 'y') {
						getchar();
						goto line4;
					}
					else if (ch == 'N' || ch == 'n') {
						mainpage(user);
						return 1;///////////possibility of error and bug///////////////
					}
					else {
						wprintf(L" \a\x1b[1;31;40mPlease enter Y/N:");
						goto line7;
					}
				}
				else {
					wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
					for (int i = 0; i < n; i++) {
						wprintf(L"\n\x007C");
						for (int j = 0; j < n; j++) {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x01A0')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
					}
					goto line6;//////////////possibility of error/////////
				}
			}

			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x01A0') {
				if (countflag > 0) {
					playfield[f / n - 1][n - 1] = L'\x2660';
					countmine--;
					countflag--;
				}
				if (countmine == 0) {
					user->win++;
					wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
					for (int i = 0; i < n; i++) {
						wprintf(L"\n\x007C");
						for (int j = 0; j < n; j++) {
							if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x01A0')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);

						}
					}
					int t = 0;
					design(t);
					wprintf(L"\n\n Do you want to continue?(Y/N)");
				line25: getchar();
					ch = getchar();
					if (ch == 'Y' || ch == 'y')
						goto line4;
					else if (ch == 'N' || ch == 'n') {
						mainpage(user);
						return 1;///////////possibility of error and bug///////////////
					}
					else {
						wprintf(L" \a\x1b[1;31;40mPlease enter Y/N:");
						goto line25;
					}
				}
				else {
					wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
					for (int i = 0; i < n; i++) {
						wprintf(L"\n\x007C");
						for (int j = 0; j < n; j++) {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == L'\x01A0')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
					}
					goto line6;//////////possibility of error//////////
				}
			}

			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x2660') {
				playfield[f / n][f % n - 1] = L'\x01A0';
				countmine++;
				countflag++;
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C");
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x2660') {
				playfield[f / n - 1][n - 1] = L'\x01A0';
				countmine++;
				countflag++;
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C");
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

		}
	}
	else {
		if (strcmp(p, "L") == 0 || strcmp(p, "l") == 0) {
			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x2660') {
				goto line6;
			}

			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x2660') {
				goto line6;
			}

			else {
				openzero(f);///////////////openzero///////////////
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}
		}
		else if (strcmp(p, "R") == 0 || strcmp(p, "r") == 0) {    /////RRRR/////
			if (f % n != 0 && playfield[f / n][f % n - 1] == L'\x2660') {
				countflag++;
				playfield[f / n][f % n - 1] = L'.';
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

			if (f % n == 0 && playfield[f / n - 1][n - 1] == L'\x2660') {
				countflag++;
				playfield[f / n - 1][n - 1] = L'.';
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

			else if (f % n != 0 && playfield[f / n][f % n - 1] == L'.') {
				if (countflag > 0) {
					playfield[f / n][f % n - 1] = L'\x2660';
					countflag--;
				}
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						else if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

			else if (f % n == 0 && playfield[f / n - 1][n - 1] == L'.') {
				if (countflag > 0) {
					playfield[f / n - 1][n - 1] = L'\x2660';
					countflag--;
				}
				wprintf(L"\n \x1b[1;90;40m\x01A0\x1b[1;37;40m: %d\t\x1b[1;31;40m\x2660\x1b[1;37;40m: %d\x1b[1;37;40m", countmine, countflag);//نمایشگر مرحله بازی
				for (int i = 0; i < n; i++) {
					wprintf(L"\n\x007C");
					for (int j = 0; j < n; j++) {
						if (playfield[i][j] != L'\x01A0') {
							if (playfield[i][j] == L'\x2660')
								wprintf(L"\x1b[1;31;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
							else if (playfield[i][j] == '.')
								wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
							else wprintf(L"\x1b[1;32;40m%c\x1b[1;37;40m\x007C", playfield[i][j]);
						}
						if (playfield[i][j] == L'\x01A0')
							wprintf(L"\x1b[1;90;40m.\x1b[1;37;40m\x007C", playfield[i][j]);
					}
				}
				goto line6;
			}

		}
	}
}

void design1(int i) {
	_setmode(_fileno(stdout), _O_U8TEXT);
	wprintf(L"\n\x1b[1;35;40m\x0359   \x1b[1;96;40m\x0001   \x1b[1;91;40m\x25AA   \x1b[1;92;40m\x0001   \x1b[1;93;40m\x2022   \x1b[1;34;40m\x0001   \x1b[1;32;40m\x030A   \x1b[1;37;40m\x0001   \x1b[1;35;40m\x030A   \x1b[1;93;40m\x0001");
	wprintf(L"\n\x1b[1;35;40m\x0001   \x1b[1;96;40m\x030A   \x1b[1;91;40m\x0001   \x1b[1;92;40m\x030A   \x1b[1;93;40m\x0001   \x1b[1;34;40m\x0359   \x1b[1;32;40m\x0001   \x1b[1;37;40m\x25AA   \x1b[1;35;40m\x0001   \x1b[1;93;40m\x2022");
	i++;
	if (i < 9)
		design1(i);
}

void design2(int i) {
	_setmode(_fileno(stdout), _O_U8TEXT);
	wprintf(L"\n\x1b[1;35;40m\x0001   \x1b[1;96;40m\x030A   \x1b[1;91;40m\x0001   \x1b[1;92;40m\x030A   \x1b[1;93;40m\x0001   \x1b[1;34;40m\x0359   \x1b[1;32;40m\x0001   \x1b[1;37;40m\x25AA   \x1b[1;35;40m\x0001   \x1b[1;93;40m\x2022");
	wprintf(L"\n\x1b[1;35;40m\x0359   \x1b[1;96;40m\x0001   \x1b[1;91;40m\x25AA   \x1b[1;92;40m\x0001   \x1b[1;93;40m\x2022   \x1b[1;34;40m\x0001   \x1b[1;32;40m\x030A   \x1b[1;37;40m\x0001   \x1b[1;35;40m\x030A   \x1b[1;93;40m\x0001");
	i++;
	if (i < 9)
		design2(i);
}
void design(int t) {
	int i = 0;
	wprintf(L"\033[%d;%dH", 1, 1);
	design1(i);
	beep();
	wprintf(L"\033[%d;%dH", 1, 1);
	design2(i);
	wprintf(L"\n\n \x1b[1;96;40mYou won! \x1b[1;37;40m\x0001");
	if (t <= 8) {
		t++;
		design(t);
	}
}

void beep() {
	Beep(7040, 70);
	Beep(7902, 70);
	Beep(4186.009, 70);
	Beep(4698.636, 70);
	Beep(5274.042, 70);
	Beep(5587.652, 70);
	Beep(6271.928, 70);
}

int openzero(int f) {
	int b, d, e, g, count = 0;
	b = f - n;     d = f - 1;     e = f + 1;       g = f + n;
	if (f % n != 0) {

		if (b % n != 0) {
			if (1 <= b && b <= n * n) {
				if (f % n - 2 <= b % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == b)
							count++;
				}
			}
		}
		if (b % n == 0) {
			if (1 <= b && b <= n * n) {
				if (f % n - 2 <= n - 1 && n - 1 <= f % n) {
					for (int i = 0; i < countminet; i++)
						if (b == arrmine[i])
							count++;
				}
			}
		}

		if (d % n != 0) {
			if (1 <= d && d <= n * n) {
				if (f % n - 2 <= d % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == d)
							count++;
				}
			}
		}
		if (d % n == 0) {
			if (1 <= d && d <= n * n) {
				if (f % n - 2 <= n - 1 && n - 1 <= f % n) {
					for (int i = 0; i < countminet; i++)
						if (d == arrmine[i])
							count++;
				}
			}
		}

		if (e % n != 0) {
			if (1 <= e && e <= n * n) {
				if (f % n - 2 <= e % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == e)
							count++;
				}
			}
		}
		if (e % n == 0) {
			if (1 <= e && e <= n * n) {
				if (f % n - 2 <= n - 1 && n - 1 <= f % n) {
					for (int i = 0; i < countminet; i++)
						if (e == arrmine[i])
							count++;
				}
			}
		}

		if (g % n != 0) {
			if (1 <= g && g <= n * n) {
				if (f % n - 2 <= g % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == g)
							count++;
				}
			}
		}
		if (g % n == 0) {
			if (1 <= g && g <= n * n) {
				if (f % n - 2 <= n - 1 && n - 1 <= f % n) {
					for (int i = 0; i < countminet; i++)
						if (g == arrmine[i])
							count++;
				}
			}
		}
	}
	if (f % n == 0) {

		if (b % n != 0) {
			if (1 <= b && b <= n * n) {
				if (n - 2 <= b % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == b)
							count++;
				}
			}
		}
		if (b % n == 0) {
			if (1 <= b && b <= n * n) {
				if (n - 2 <= n - 1) {
					for (int i = 0; i < countminet; i++)
						if (b == arrmine[i])
							count++;
				}
			}
		}

		if (d % n != 0) {
			if (1 <= d && d <= n * n) {
				if (n - 2 <= d % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == d)
							count++;
				}
			}
		}
		if (d % n == 0) {
			if (1 <= d && d <= n * n) {
				if (n - 2 <= n - 1) {
					for (int i = 0; i < countminet; i++)
						if (d == arrmine[i])
							count++;
				}
			}
		}

		if (e % n != 0) {
			if (1 <= e && e <= n * n) {
				if (n - 2 <= e % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == e)
							count++;
				}
			}
		}
		if (e % n == 0) {
			if (1 <= e && e <= n * n) {
				if (n - 2 <= n - 1) {
					for (int i = 0; i < countminet; i++)
						if (e == arrmine[i])
							count++;
				}
			}
		}

		if (g % n != 0) {
			if (1 <= g && g <= n * n) {
				if (n - 2 <= g % n - 1) {
					for (int i = 0; i < countminet; i++)
						if (arrmine[i] == g)
							count++;
				}
			}
		}
		if (g % n == 0) {
			if (1 <= g && g <= n * n) {
				if (n - 2 <= n - 1) {
					for (int i = 0; i < countminet; i++)
						if (g == arrmine[i])
							count++;
				}
			}
		}

	}

	if (f % n != 0)
		switch (count) {             /////////////switch case break///////////////
		case 0:playfield[f / n][f % n - 1] = '0'; break;
		case 1:playfield[f / n][f % n - 1] = '1'; break;
		case 2:playfield[f / n][f % n - 1] = '2'; break;
		case 3:playfield[f / n][f % n - 1] = '3'; break;
		case 4:playfield[f / n][f % n - 1] = '4'; break;
		case 5:playfield[f / n][f % n - 1] = '5'; break;
		case 6:playfield[f / n][f % n - 1] = '6'; break;
		case 7:playfield[f / n][f % n - 1] = '7'; break;
		case 8:playfield[f / n][f % n - 1] = '8';
		}
	else if (f % n == 0)
		switch (count) {             /////////////switch case break///////////////
		case 0:playfield[f / n - 1][n - 1] = '0'; break;
		case 1:playfield[f / n - 1][n - 1] = '1'; break;
		case 2:playfield[f / n - 1][n - 1] = '2'; break;
		case 3:playfield[f / n - 1][n - 1] = '3'; break;
		case 4:playfield[f / n - 1][n - 1] = '4'; break;
		case 5:playfield[f / n - 1][n - 1] = '5'; break;
		case 6:playfield[f / n - 1][n - 1] = '6'; break;
		case 7:playfield[f / n - 1][n - 1] = '7'; break;
		case 8:playfield[f / n - 1][n - 1] = '8';
		}
	if (count != 0)
		return 1;
	else if (count == 0) {
		if (f % n != 0 && f % n != 1) {
			if (b % n == 0) {
				if (1 <= b && b <= n * n && playfield[b / n - 1][n - 1] == '.')
					openzero(b);
			}
			if (b % n != 0) {
				if (1 <= b && b <= n * n && playfield[b / n][b % n - 1] == '.')
					openzero(b);
			}
			if (d % n == 0) {
				if (1 <= d && d <= n * n && playfield[d / n - 1][n - 1] == '.')
					openzero(d);
			}
			if (d % n != 0) {
				if (1 <= d && d <= n * n && playfield[d / n][d % n - 1] == '.')
					openzero(d);
			}
			if (e % n == 0) {
				if (1 <= e && e <= n * n && playfield[e / n - 1][n - 1] == '.')
					openzero(e);
			}
			if (e % n != 0) {
				if (1 <= e && e <= n * n && playfield[e / n][e % n - 1] == '.')
					openzero(e);
			}
			if (g % n == 0) {
				if (1 <= g && g <= n * n && playfield[g / n - 1][n - 1] == '.')
					openzero(g);
			}
			if (g % n != 0) {
				if (1 <= g && g <= n * n && playfield[g / n][g % n - 1] == '.')
					openzero(g);
			}
		}
		else if (f % n == 0) {
			if (b % n == 0) {
				if (1 <= b && b <= n * n && playfield[b / n - 1][n - 1] == '.')
					openzero(b);
			}
			if (b % n != 0) {
				if (1 <= b && b <= n * n && playfield[b / n][b % n - 1] == '.')
					openzero(b);
			}
			if (d % n == 0) {
				if (1 <= d && d <= n * n && playfield[d / n - 1][n - 1] == '.')
					openzero(d);
			}
			if (d % n != 0) {
				if (1 <= d && d <= n * n && playfield[d / n][d % n - 1] == '.')
					openzero(d);
			}
			if (g % n == 0) {
				if (1 <= g && g <= n * n && playfield[g / n - 1][n - 1] == '.')
					openzero(g);
			}
			if (g % n != 0) {
				if (1 <= g && g <= n * n && playfield[g / n][g % n - 1] == '.')
					openzero(g);
			}
		}
		else if (f % n == 1) {
			if (b % n == 0) {
				if (1 <= b && b <= n * n && playfield[b / n - 1][n - 1] == '.')
					openzero(b);
			}
			if (b % n != 0) {
				if (1 <= b && b <= n * n && playfield[b / n][b % n - 1] == '.')
					openzero(b);
			}
			if (e % n == 0) {
				if (1 <= e && e <= n * n && playfield[e / n - 1][n - 1] == '.')
					openzero(e);
			}
			if (e % n != 0) {
				if (1 <= e && e <= n * n && playfield[e / n][e % n - 1] == '.')
					openzero(e);
			}
			if (g % n == 0) {
				if (1 <= g && g <= n * n && playfield[g / n - 1][n - 1] == '.')
					openzero(g);
			}
			if (g % n != 0) {
				if (1 <= g && g <= n * n && playfield[g / n][g % n - 1] == '.')
					openzero(g);
			}
		}
	}
}