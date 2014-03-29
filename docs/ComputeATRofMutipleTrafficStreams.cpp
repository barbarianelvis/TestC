#include <iostream>
#include <numeric>
#include <cstdlib>
#include <iomanip> 
using namespace std;

int gcd(int a, int b){
    while(1){
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
		p3 = 60;
	//Compute GCD&LCM for all traffic streams
    int period[] = { p0, p1, p2, p3 };
	int i = 0, G = 0;
    double L = accumulate( period, period + 4, 1, lcm);
    
    while ( i < sizeof( period )/4 ){
    	if (i==0){
    		G = gcd( period[0],period[1] );
    		i = 1;
    	}
    	else
    		G = gcd( G, period[i] );
    	i++;
    }
    cout << "The LCM of all periods is " << L << endl;
    cout << "The GCD of all periods is " << G << endl;
    
    //Setup the traffic streams for all periods
    //Length of each array should be the number of LCM
	int x0[60] = {0}, x1[60] = {0}, x2[60] = {0}, x3[60] = {0}, x[60] = {0};
	
	//Length of ATR Array should be the number of p0*p1*p2
	//Type in the length of ATR array 
	double ATR[300] = {0}, j = 0;
	int of0, of1, of2, of3 = p3, k = 0;
	
	//Setup the fourth stream as reference stream.
	for ( i = 0; i < L; i++){
    	if ( (i+of3) % period[3] == 0)
			x3[i] = 1;
    	else
			x3[i] = 0;
	}
	
	//Setup the first stream with offset0.
	for (of0 = p0; of0 > 0; of0--){
		for ( i = 0; i < L; i++){
    		if ( (i+of0) % period[0] == 0)
				x0[i] = 1;
    		else
				x0[i] = 0;
		}
		//Setup the second stream with offset1.
		for (of1 = p1; of1 > 0; of1--){
			for ( i = 0; i < L; i++){
    			if ( (i+of1) % period[1] == 0)
					x1[i] = 1;
    			else
					x1[i] = 0;
			}
			//Setup the third stream with offset2.
			for ( of2 = p2; of2 > 0; of2-- ){
				for ( i = 0; i < L; i++){
    				if ( ( i + of2 ) % period[2] == 0)
						x2[i] = 1;
    				else
						x2[i] = 0;
				}
				//Compute the Active Time Ratio of all traffic streams
				j = 0;	
				for ( i = 0; i < L; i++ ){
					//Sum of total traffic stream
					x[i] = x0[i] + x1[i] + x2[i];// + x3[i];
					if ( x0[i]==1 || x1[i]==1 || x2[i])// || x3[i]==1 )
						j++;
				}
				ATR[k] = j/L;
				k++;
				//Test
				if (of0 == p0 && of1 == p1 && of2 == p2 ){
					cout << "With of0: " << p0-of0;
					cout << ", of1: " << p1-of1;
					cout << ", of2: " << p2-of2;
					cout << ",and of3: " << p3-of3 << endl;
					cout << "ATR: " << double(j/L) << endl;
						
					cout << "x[i] ={";
					for ( i =0; i < L; i++ )
						cout << x[i] << ",";
					cout << "}" << endl; 
				}
			}	
		}
	}
	
    i=0;
    double maxATR = ATR[0];
    double minATR = ATR[0];
    double sumATR =0;
    
	for ( i = 0; i < sizeof(ATR)/8; i++){
		if ( ATR[i] > maxATR)
			maxATR = ATR[i];
		else if ( ATR[i] < minATR)
			minATR = ATR[i];
		sumATR = ATR[i]+sumATR;
    }
    cout << "Size of ATR array: " << sizeof(ATR)/8 << endl;
    cout << "Max ATR: " << maxATR << endl;
    cout << "Min ATR: " << minATR << endl;
    cout << "Avg ATR: " << sumATR/(sizeof(ATR)/8) << endl;
    
    system("pause");
    return 0;
}
