#include <iostream>
#include <numeric>
#include <cstdlib>
#include <math.h>

using namespace std;

struct app{
	int period;
	int dataSize;
	bool isUsed;
	//struct app *next;
};

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
	if ( (order+of0) % period[0] == 0)
		{dataToTransmit = dataToTransmit + dataSize[0];};
	if ( (order+of1) % period[1] == 0)
		{dataToTransmit = dataToTransmit + dataSize[1];};
	if ( (order+of2) % period[2] == 0)
		{dataToTransmit = dataToTransmit + dataSize[2];};
	if ( (order+of3) % period[3] == 0)
		{dataToTransmit = dataToTransmit + dataSize[3];};
	if ( (order+of4) % period[4] == 0)
		{dataToTransmit = dataToTransmit + dataSize[4];};
	return dataToTransmit;
}

int findGCDOffset(int localPeriod, int period[]){
	int temp = localPeriod;
	int G = 0;
	for ( int t=0; t < sizeof(period)/4; t++ ){
		if ( localPeriod == period[t] )
			{ t++; }
		else{
			G = gcd ( localPeriod, period[t] );
			if ( G !=1 && G <= temp )
				{ temp = G;}
		}
	}
	//cout << "Offset is " << temp << " for refined uplink.\n";
	return temp;
}

int main(){
	//Setup indivisual applications
	app App0, App1, App2, App3, App4;
	//Type in your own periods, data size, and the threshold.
	App0.period = 3,
	App1.period = 5,
	App2.period = 10,
	App3.period = 15,
	App4.period = 30;
	
	App0.dataSize = 8;
	App1.dataSize = 10;
	App2.dataSize = 15;
	App3.dataSize = 20;
	App4.dataSize = 25;
	
	int threshold = 60;
	//=========================================================
	App0.isUsed = false;
	App1.isUsed = false;
	App2.isUsed = false;
	App3.isUsed = false;
	App4.isUsed = false;
	
	int period[] = { App0.period, App1.period, App2.period, App3.period, App4.period };
	int dataSize[5] = { App0.dataSize, App1.dataSize, App2.dataSize, App3.dataSize, App4.dataSize };
	
	int G = 0, i = 0, temp = 0, length = sizeof( period )/4;
	int X[60] = {0}, ActiveTime = 0, lengthX = sizeof(X)/4;
	
	//Compute GCD&LCM for all traffic streams
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
    
    cout << "The periods of all apps are "; 
    for ( i=0; i < length; i++ ){
    	if (i == length-1)
    		cout << period[i] << "." << endl;
    	else
    		cout << period[i] << ",";
	}
    cout << "The LCM of all periods is " << L << endl;
    cout << "The GCD of all periods is " << G << endl;
    
	//Setup each array with each period via offset = 0.
	int of0=0, of1=0, of2=0, of3=0, of4=0;
	int gap = 0;
	for (int d = 0; d < lengthX; d++ ){
    	X[d] = GenerateMixedUplinkArray( d , period, dataSize, of0, of1, of2, of3, of4 );
	}
	
	double originalPower = 0;
	cout << "\nThe original uplink array:\n{ ";
	for ( i =0; i < lengthX; i++ ){
		cout << X[i] << " ";
		if (X[i] != 0){
			if (X[i] > threshold)
				{originalPower = originalPower + 13*( 10*log(X[i]) -5 ) + 0.4;}
			else
				{originalPower = originalPower + 7.7*( 10*log(X[i]) -5 ) + 1.6;}
		}
	} 
	cout << "}" << endl;
	cout << "Total power consumption: " << originalPower << "mW.\n";
	
	for (int d = 0; d < lengthX; d++ ){
    	X[d] = GenerateMixedUplinkArray( d , period, dataSize, of0, of1, of2, of3, of4 );
    	if ( X[d] > 0 )
    		{ActiveTime++;}
    	while (X[d] > threshold){
			gap = X[d] - threshold;
			if ( App4.isUsed == false && (d%App4.period)==0 ){
				of4 = period[4] - findGCDOffset( App4.period, period );
				//cout << "App 5 is chosen to modify.\n";
				App4.isUsed = true;
			}
			else if ( App3.isUsed == false && (d%App3.period)==0 ){
				of3 = period[3] - findGCDOffset( App3.period, period );
				//cout << "App 4 is chosen to modify.\n";
				App3.isUsed = true;
			}
			else if ( App2.isUsed == false && (d%App2.period)==0 ){
				of2 = period[2] - findGCDOffset( App2.period, period );
				//cout << "App 3 is chosen to modify.\n";
				App2.isUsed = true;
			}
			else if ( App1.isUsed == false && (d%App1.period)==0 ){
				of1 = period[1] - findGCDOffset( App1.period, period );
				//cout << "App 2 is chosen to modify.\n";
				App1.isUsed = true;
			}
			else 
				break;
			X[d] = GenerateMixedUplinkArray( d , period, dataSize, of0, of1, of2, of3, of4 );
		}
	}
	
	double modifiedPower = 0;
	cout << "\nThe refined uplink array:\n{ ";
	for ( i =0; i < lengthX; i++ ){ 
		cout << X[i] << " ";
		if ( X[i] != 0 ){
			if ( X[i] > threshold )
				{modifiedPower = modifiedPower + 13*(-5 + 10*log(X[i]))+0.4;}
			else
				{modifiedPower = modifiedPower + 7.7*(-5 + 10*log(X[i]))+1.6;}
		}
	}
	cout << "}" << endl;
	cout << "Total power consumption: " << modifiedPower << "mW.\n";
	cout << "Improved Power efficiency: " << 100*double(originalPower-modifiedPower)/ double(originalPower) << "%" << endl;
	
	cout << "ATR = " << double(ActiveTime)/double(lengthX) << endl;
	
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
    
    //system("pause");
    return 0;
}



    /*
    //Setup the multi-array for storing multiple classes
    //int Pmin[5][5] = {0};
    
	//Setup the check list array for store multiple classes
    int checkList[5] = {1,1,1,1,1};
    
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
	*/



