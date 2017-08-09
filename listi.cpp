// listi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



int main()
{
	int k;
	int l;
	int i;
	int j=0;                      //stevilo zasedenih
	long long int option = 0;
	long long int saved = 0;
	long long int ploscina = 0;
	int lokacija;
	int splitcounter = 0;
	int change;
	int r = 0;                   //stevilo redundant listov
	static int splits[10000] = { 0 };
	int n;                        //stevilo listov
	static long long int listi[2][10000];
	ifstream ifs("listi10.in");
	ofstream ofs("listi10.out");
	ifs >> n;
	for (i = 0; i < n; i++){
		ifs >> listi[0][i] >> listi[1][i];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j != i) {
				if (listi[0][i] >= listi[0][j] && listi[1][i] >= listi[1][j]) {
					if (listi[0][j] != 0 && listi[1][j] != 0) {
						listi[0][j] = 0;
						listi[1][j] = 0;
						r++;
					}
					else continue;
				}
				else continue;
			}
		}
	}

	sort(listi[0], listi[0] + n);
	sort(listi[1], listi[1] + n);
	reverse(listi[0], listi[0]+n);
	reverse(listi[1], listi[1] + n);
	reverse(listi[1], listi[1] + n - r);
	n = n - r;
	splits[1] = n;
	i = 2;

	do{
		change = 0;
		for (j = 0; j <= i-2; j++) {
			lokacija = 0;
			saved = listi[0][splits[j]] * listi[1][splits[j+1]-1];
			l = (splits[j + 1] - splits[j]) - 1;
			for (k = splits[j]; k < splits[j+1]; k++) {
				option = listi[0][splits[j]] * (listi[1][k]) + listi[0][k+1] * listi[1][splits[j+1]-1];
				if (option < saved) {
					saved = option;
					lokacija = k + 1;
				}
				else continue;
			}
			if (saved != listi[0][splits[j]] * listi[1][splits[j + 1] - 1]&&saved >0&&lokacija!=0) {
				splitcounter++;
				splits[splitcounter + 1] = lokacija;
				change = 1;
			}
			else continue;
		}
		i = splitcounter + 2;
		sort(splits, splits+i);
	} while (change == 1);

	for (j = 0; j <= splitcounter; j++) {
		ploscina = ploscina + listi[0][splits[j]] * listi[1][splits[j + 1] - 1];
	}
	ofs << i << j;

	ofs <<'\n'<< "stevilo kupov je "<<splitcounter+1 <<", skupna ploscina je "<< ' '<<ploscina<<'\n';
	ofs << "listi po vrsti so:" << '\n';
	for (i = 0; i < n; i++) {
		ofs << listi[0][i] << ' '<< listi[1][i] << '\n';
	}
	ofs << "spliti (po katerem listu so kupi loceni) so:" << '\n';
	for (l = 0; l < splitcounter+2; l++) {
	ofs << splits[l] << ' ';
	}
	ofs << '\n';

    return 0;
}

