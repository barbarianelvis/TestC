#include <iostream>
#include <numeric>
#include <cstdlib>
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
    return temp?( a / temp*b ):0;
}

int GenerateMixedUplinkArray(int order, int period[], int dataSize[], int of0, int of1, int of2, int of3,int of4){
	int dataToTransmit = 0;
	if ( order % period[0] == 0)
		{dataToTransmit = dataToTransmit + dataSize[0];};
	if ( order % period[1] == 0)
		{dataToTransmit = dataToTransmit + dataSize[1];};
	if ( order % period[2] == 0)
		{dataToTransmit = dataToTransmit + dataSize[2];};
	if ( order % period[3] == 0)
		{dataToTransmit = dataToTransmit + dataSize[3];};
	if ( order % period[4] == 0)
		{dataToTransmit = dataToTransmit + dataSize[4];};
	return dataToTransmit;
}

int main(){
	//Setup the parameters of indivisual traffic streams
	//Type in your own periods
	int pd0 = 2,
		pd1 = 3,
		pd2 = 4,
		pd3 = 6,
		pd4 = 9;
	int dataSize[10] = { 3, 6, 10, 15, 20 };
	
	//Compute GCD&LCM for all traffic streams
	int period[] = { pd0, pd1, pd2, pd3, pd4 };
	int G = 0, i = 0, temp = 0, length = sizeof( period )/4;
	
	int x0[36] = {0}, x1[36] = {0}, x2[36] = {0}, x3[36] = {0}, x4[36] = {0}, X[36] = {0}, ActiveTime = 0;
	
	//Setup the multiarray for storing multiple classes
    int Pmin[5][5] = {0};
    
	//Setup the check list array for store multiple classes
    int checkList[5] = {1,1,1,1,1};
    int L = accumulate ( period, period+5, 1, lcm );
    
    while ( i < length ){
    	if (i==0){
    		G = gcd( period[0],period[1] );
    		i = 1;
    	}
    	else
    		G = gcd( G, period[i] );
    	i++;
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
    	if (i == length-1 && checkList[length-1]==1)
    		{Pmin[k][0] = period[i];}
    	if (checkList[0]==0 && checkList[1]==0 && checkList[2]==0 && checkList[3]==0 && checkList[4]==0)
    		{break;}
    }
    
    cout << Pmin[0][0] << "," << Pmin[0][1] << "," << Pmin[0][2] << endl;
	cout << Pmin[1][0] << "," << Pmin[1][1] << "," << Pmin[1][2] << endl;
	//cout << Pmin[2][0] << "," << Pmin[2][1] << "," << Pmin[2][2] << endl;
	
	//Setup each array with each period in class 1.
	int of0=0, of1=0, of2=0, of3=0, of4=0;
	
	for (int d = 0; d < L; d++ ){
    	X[d] = GenerateMixedUplinkArray( d , period, dataSize, of0, of1, of2, of3, of4 );
    	
    	if ( X[d] > 0 )
    		{ActiveTime++;} 
	}
	
	cout << "{ ";
	for ( i =0; i < L; i++ ) 
		cout << X[i] << " ";
	cout << "}" << endl;
	
	cout << "ATR = " << double(ActiveTime)/double(L) << endl;
	
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





