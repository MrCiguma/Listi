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
	int p = 0;                    //povrsina
	int option = 0;
	int saved = 0;
	int ploscina = 0;
	int lokacija;
	int splitcounter = 0;
	int counter;
	int change;
	int r = 0;                   //stevilo redundant listov
	static int splits[10000] = { 0 };
	static int visina[10000] = { 0 };
	static int sirina[10000] = { 0 };
	int n;                        //stevilo listov
	static int listi[2][10000];
	ifstream ifs("listi07.in");
	ofstream ofs("listi07.out");
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
			counter = 0;
			lokacija = 0;
			saved = listi[0][splits[j]] * listi[1][splits[j+1]-1];
			l = (splits[j + 1] - splits[j]) - 1;
			for (k = 0; k < l; k++) {
				option = listi[0][splits[j]] * (listi[1][k]) + listi[0][k+1] * listi[1][splits[j+1]-1];
				if (option < saved) {
					saved = option;
					lokacija = k + 1 + splits[j];
				}
				else continue;
			}
			//ofs << saved << ' ' << lokacija << '\n';
			//ofs <<'\n' << j << ' ' << k <<' '<< l<<'\n';
			//for (l = 0; l < n; l++) {
			//	ofs << splits[l] << ' ';
			//}
			//ofs << '\n';
			if (saved != listi[0][splits[j]] * listi[1][splits[j + 1] - 1]&&saved >0&&lokacija!=0) {
				splitcounter++;
				counter++;
				splits[splitcounter + 1] = lokacija;
				//ofs << "tu" << ' ' << j << ' ' << k <<' '<<l<<'\n';
				change = 1;
			}
			else continue;
		}
		i = splitcounter + 2;
		sort(splits, splits+i);
		//ofs << i << '\n';

		//for (l = 0; l < n; l++) {
		//ofs << splits[l] << ' ';
		//}
		//ofs << '\n';
	} while (change == 1);

	for (j = 0; j <= splitcounter; j++) {
		ploscina = ploscina + listi[0][splits[j]] * listi[1][splits[j + 1] - 1];
	}

	ofs <<'\n'<< "stevilo kupov je "<<splitcounter+1 <<", skupna ploscina je "<< ' '<<ploscina<<'\n';
	ofs << "listi po vrsti so:" << '\n';
	for (i = 0; i < n; i++) {
		ofs << listi[0][i] << ' '<< listi[1][i] << '\n';
	}
	ofs << "spliti so:" << '\n';
	for (l = 0; l < splitcounter+2; l++) {
	ofs << splits[l] << ' ';
	}
	ofs << '\n';

    return 0;
}

