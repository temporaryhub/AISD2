#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main() {

  char tab[40];
	gets(tab);
	int prz_os_cyfra = 0;
	int dl = strlen(tab);

	if (dl>1) {
		char prz_os_znak = tab[dl-2];
		prz_os_cyfra = prz_os_znak-'0';
	}

	char ost_znak = tab[dl-1];
	int os_cyfra = ost_znak-'0';
	int liczba = 10*prz_os_cyfra+os_cyfra;

	if (liczba == 0 & dl ==1 ) cout << 1 << endl;
	else if (liczba % 4 == 0) cout << 6 << endl;
	else if (liczba % 4 == 1) cout << 2 << endl;
	else if (liczba % 4 == 2) cout << 4 << endl;
	else cout << 8 << endl;
}
