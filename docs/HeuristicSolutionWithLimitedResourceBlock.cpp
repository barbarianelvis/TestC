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
	int p0 = 3,
		p1 = 2,
		p2 = 6,
		p3 = 11,
		p4 = 9;
	int dataSize[10];
	//Compute GCD&LCM for all traffic streams
	int period[] = { p0, p1, p2, p3, p4 };
	int G = 0, i = 0, temp = 0, length = sizeof( period )/4;
	int arrayG[5] = { 0, 0, 0, 0, 0 };
	//Setup the multiarray for store multiple classes
    double Pmin[5][5] = {0};
	//Setup the check list array for store multiple classes
    int checkList[5] = {1,1,1,1,1};
    double L = accumulate( period, period + 4, 1, lcm);
    while ( i < length ){
    	if (i==0){
    		G = gcd( period[0],period[1] );
    		i = 1;
    	}
    	else
    		G = gcd( G, period[i] );
    	i++;
    }
    
    for ( i=1; i < length; i++){
    	for (int j=0; j<i; j++){
    		if ( period[j] > period[i] ){
    			temp = period[i];
    			period[i] = period[j];
    			period[j] = temp;
    		}
    	}
    }
    
    cout << "The array of all periods is "; 
    for ( i=0; i < length; i++ ){
    	if (i == length-1)
    		cout << period[i] << "." << endl;
    	else
    		cout << period[i] << ",";
	}
    cout << "The LCM of all periods is " << L << endl;
    cout << "The GCD of all periods is " << G << endl;
    
	//Classify multiple period with same GCD using checkList[5];
	int k = 0, shift = 0, m = 0;
    for ( i=0; i<length; i++){
    	cout << checkList[0] << checkList[1] << checkList[2] << checkList[3] << checkList[4] << endl;
    	if (checkList[i] == 1){
    		for (int j=i; j<length; j++){
    			if ( period[j]%period[i]==0 && checkList[j] == 1 ){
    				Pmin[k][m] = period[j];
    				checkList[j] = 0;
    				m++;
    			}
    			else
    				shift++;
    		}
    		k++;
    		shift = 0;
    		m = 0;
    	}
    	if (i == length-1 && checkList[length-1]==1){
    		Pmin[k][0] = period[i];
    	}
    }
    
    cout << Pmin[0][0] << Pmin[0][1] << Pmin[0][2] << endl;
	cout << Pmin[1][0] << Pmin[1][1] << Pmin[1][2] << endl;
	cout << Pmin[2][0] << Pmin[2][1] << Pmin[2][2] << endl; 
	
	//Calculate the GCD of each PeroidMin array.
	//k = 0, i = 0;
	//int arrayG[5] = 0;
	/*while ( i < length ){
    	if (Pmin[k][i+1]!=0){
    		G = gcd( Pmin[k][i],Pmin[k][i+1] );
    	}
    	
    	i++;
    	k++; 
    }*/
    
    system("pause");
    return 0;
} 
