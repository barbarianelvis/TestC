#include <iostream>
#include <numeric>
#include <cstdlib>
#include <iomanip>
#include <math.h> 
using namespace std;

int gcd(int a, int b){
	while (1){
		if (a == 0)
			return b;
		b %= a;
		if (b == 0)
			return a;
		a %= b;
	}
}

int lcm(int a, int b){
	int temp = gcd(a, b);
	return temp ? (a / temp * b) : 0;
}

int main(){
	//Setup the parameters of indivisual traffic streams
	//Type in your own periods
	int p0 = 3,
		p1 = 5,
		p2 = 10,
		p3 = 15,
		p4 = 30;

	int d0 = 8,
		d1 = 10,
		d2 = 15,
		d3 = 20,
		d4 = 25;
		
	int threshold = 0;

	//Compute GCD&LCM for all traffic streams
	int period[] = { p0, p1, p2, p3, p4 };
	int i = 0, G = 0;
	double L = accumulate(period, period + 5, 1, lcm);

	while (i < sizeof(period) / 4){
		if (i == 0){
			G = gcd(period[0], period[1]);
			i = 1;
		}
		else
			G = gcd(G, period[i]);
		i++;
	}
	cout << "The LCM of all periods is " << L << endl;
	cout << "The GCD of all periods is " << G << endl;

	//Setup the traffic streams for all periods
	//Length of each array should be the number of LCM
	int x0[30] = { 0 }, x1[30] = { 0 }, x2[30] = { 0 }, x3[30] = { 0 }, x4[30] = { 0 }, x[30] = { 0 };

	//Length of ATR Array should be the number of p0*p1*p2
	//Type in the length of ATR array 
	double ATR[2250] = {0}, j = 0;
	int Power[2250] = {0}, dataSize = 0;
	int of0 = 0, of1 = 0, of2 = 0, of3 = 0, of4 = 0;
	int k = 0;

	//Setup the fourth stream as reference stream.
	of4 = p4;
	for (i = 0; i < L; i++){
		if ((i + of4) % p4 == 0)
			x4[i] = 1;
		else
			x4[i] = 0;
	}

	//Setup the first stream with offset0.
	for (of0 = 0; of0 < p0; of0++){
		for (i = 0; i < L; i++){
			if ((i + of0) % p0 == 0)
				x0[i] = 1;
			else
				x0[i] = 0;
		}
		//Setup the second stream with offset1.
		for (of1 = 0; of1 < p1; of1++){
			for (i = 0; i < L; i++){
				if ((i + of1) % p1 == 0)
					x1[i] = 1;
				else
					x1[i] = 0;
			}
			//Setup the third stream with offset2.
			for (of2 = 0; of2 < p2; of2++){
				for (i = 0; i < L; i++){
					if ((i + of2) % p2 == 0)
						x2[i] = 1;
					else
						x2[i] = 0;
				}
				//Setup the fourth stream with offset3.
				for (of3 = 0; of3 < p3; of3++){
					for (i = 0; i < L; i++){
						if ((i + of3) % p3 == 0)
							x3[i] = 1;
						else
							x3[i] = 0;
					}
					//Compute the Active Time Ratio of all traffic streams
					j = 0;
					for (i = 0; i < L; i++){
						x[i] = x0[i] + x1[i] + x2[i] + x3[i] + x4[i];
						
						if (x[i]>0){
							j++;
						}
						if (x0[i]==1)
							dataSize = dataSize + d0;
						if (x1[i]==1)
							dataSize = dataSize + d1;
						if (x2[i]==1)
							dataSize = dataSize + d2;
						if (x3[i]==1)
							dataSize = dataSize + d3;
						if (x4[i]==1)
							dataSize = dataSize + d4;
						
						if (dataSize > threshold){
							Power[k] = 13*(-5 + log(dataSize))+0.4; 
						}
						else{
							Power[k] = 7.7*(-5 + log(dataSize))+1.6;
						}
						
						if (i == (L - 1)){
							ATR[k] = j / L;
							k++;
						}
						
					}
				}
			}
		}
	}
	i = 0;
	double maxATR = ATR[0];
	double minATR = ATR[0];
	double sumATR = 0;

	for (i = 0; i < sizeof(ATR) / 8; i++){
		if (ATR[i] > maxATR)
			maxATR = ATR[i];
		else if (ATR[i] < minATR)
			minATR = ATR[i];
		sumATR = ATR[i] + sumATR;
	}
	cout << "Size of ATR array: " << sizeof(ATR) / 8 << endl;
	cout << "Max ATR: " << maxATR << endl;
	cout << "Min ATR: " << minATR << endl;
	cout << "Avg ATR: " << sumATR / (sizeof(ATR) / 8) << endl;

	system("pause");
}

