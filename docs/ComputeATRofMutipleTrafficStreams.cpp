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
	int p0 = 2,
		p1 = 5,
		p2 = 30,
		p3 = 60,
		p4 = 240;

	int d0 = 3,
		d1 = 15,
		d2 = 4,
		d3 = 8,
		d4 = 10;
		
	int threshold = 26;
	double P0 = -4;
	
	double alphaH = 54;
	double betaH = 1.5;
	double alphaL = 7.2;
	double betaL = 1.6;
	
	//Compute GCD&LCM for all traffic streams
	int period[] = { p0, p1, p2, p3, p4 };
	int i = 0, G = 0;
	double L = accumulate(period, period + 5, 1, lcm);

	cout << "The LCM of all periods is " << L << endl;
	//cout << "The GCD of all periods is " << G << endl;

	//Setup the traffic streams for all periods
	//Length of each array should be the number of LCM
	int x0[240] = { 0 }, 
		x1[240] = { 0 }, 
		x2[240] = { 0 }, 
		x3[240] = { 0 }, 
		x4[240] = { 0 }, 
		 x[240] = { 0 };

	//Length of ATR Array should be the number of p0*p1*p2*p3
	//Type in the length of ATR array 
	double ATR[18000] = {0}, j = 0;
	double Power[18000] = {0}, dataSize = 0;
	int of0 = 0, of1 = 0, of2 = 0, of3 = 0, of4 = 0;
	int k = 0;

	//Setup the fourth stream as reference stream.
	of4 = 0;
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
					Power[k] = 0;
					dataSize = 0;
					
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
						//Compute transmission power.
						if ( x[i] !=0 ){
							if (dataSize > threshold){
								Power[k] = Power[k] + alphaH*( P0 + 10*log(dataSize) ) + betaH;}
							else{
								Power[k] = Power[k] + alphaL*( P0 + 10*log(dataSize) ) + betaL;}
						}
						//Initialize.
						dataSize = 0;
						
						if (i == (L - 1)){
							ATR[k] = j / L;
							if (Power[k] <= 175){
								cout << "Of0: " << of0 << ", Of1: " << of1 << ", Of2: " << of2 << ", Of3: " << of3 << ", Of4: " << of4 << endl;
								cout << "ATR: " << ATR[k] << endl;
								cout << "Power: " << Power[k] << endl;
							}
							if (Power[k] >= 50000){
								cout << "Of0: " << of0 << ", Of1: " << of1 << ", Of2: " << of2 << ", Of3: " << of3 << ", Of4: " << of4 << endl;
								cout << "ATR: " << ATR[k] << endl;
								cout << "Power: " << Power[k] << endl;
							}
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
	double maxPower = Power[0];
	double minPower = Power[0];
	double sumPower = 0;
	//cout << "Power[0] = " << Power[0] << endl;

	for (i = 0; i < sizeof(ATR)/8; i++){
		if (ATR[i] > maxATR)
			maxATR = ATR[i];
		else if (ATR[i] < minATR)
			minATR = ATR[i];
		sumATR = ATR[i] + sumATR;
	}
	for (i = 0; i < sizeof(Power)/8; i++){
		if (Power[i] > maxPower)
			maxPower = Power[i];
		else if (Power[i] < minPower)
			minPower = Power[i];
		sumPower = Power[i] + sumPower;
	}
	
	
	cout << "\nSize of ATR array: " << sizeof(ATR)/8 << endl;
	cout << "Max ATR: " << maxATR << endl;
	cout << "Min ATR: " << minATR << endl;
	cout << "Avg ATR: " << sumATR / (sizeof(Power)/8) << endl << endl;
	cout << "Max Power: " << maxPower << endl;
	cout << "Min Power: " << minPower << endl;
	cout << "Avg Power: " << sumPower / (sizeof(Power)/8) << endl;
	
	system("pause");
}

