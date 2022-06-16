#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
        int p1, p2,p3;
    for (int i = 0; i <= n; i++)  
    {  
        for (int j = 0; j <=m ; j++) {
          if (i == 0 || j == 0)  
                P[i][j]=H[i][j] = 0;  
        }
            
    }  

    for(int i=1; i<=n ; i++){
            for(int j=1; j<=m; j++){
                if(X[i-1] == Y[j-1]){
                        p1 = H[i-1][j-1]+2;
                }
                else{
                        p1 = H[i-1][j-1]-1;}
                p2 = H[i-1][j]-1;
                p3 = H[i][j-1]-1;

                if(p1 >= p2 && p1 >= p3)
                        H[i][j] = p1;
                else{
                if(p2 >= p1 && p2 >= p3)
                        H[i][j] = p2;
                else
                        H[i][j] = p3;
                }

                if(H[i][j] == p1){
                                P[i][j] = 'd';
                        }
                else{
                if(H[i][j] == p2){
                        P[i][j] = 'u';}
                else{
                        P[i][j] = 'l';
                }
                
            }
            }

    }
// cout<<H[n][m]<<endl;

return;
}


/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
        int p1, p2, p3;
        	
       for (int i = 0; i <= n; i++){
	    for (int j = 0; j <= m; j++){
		H[i][j] = 0;
                P[i][j] = '-';
            }
       }
       memoized_SW_AUX(X, Y, P, H,n, m );
      
        // if (m == 0 || n == 0) 
        //         return ;

        // if (H[n][m] != 0){ 
        //    H[n][m] = H[n][m] ; 
        // }
        // else{
        //        H[n][m] = memoized_SW_AUX(X, Y, P, H,n, m );
        // }

        return;

        // cout<< H[n][m] << endl; 
        // }
}


/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
	        int p1, p2, p3;
        if (m == 0 || n == 0) 
                return 0; 

        if (H[n][m] != 0){ 
           return H[n][m] ; 
        }
        if (X[n - 1] == Y[m- 1]) {
               p1 = memoized_SW_AUX(X, Y, P, H,n- 1, m - 1)+2; 
        }
        else{
                p1= memoized_SW_AUX(X, Y,P,H ,n-1, m - 1) -1;
        
        } 
        p2 = memoized_SW_AUX(X, Y,P,H ,n-1, m) -1;
        p3 = memoized_SW_AUX(X, Y,P,H ,n, m-1) -1;

        if(p1 >= p2 && p1 >= p3){
                H[n][m] = p1;
        }
        else{
                if(p2 >= p1 && p2 >= p3)
                        H[n][m] = p2;
                else
                        H[n][m] = p3;
        }

        if(H[n][m] == p1){
                        P[n][m] = 'd';
                }
        else{
        if(H[n][m] == p2){
                P[n][m] = 'u';}
        else{
                P[n][m] = 'l';
        }
        
        }

        return H[n][m] ;  
}

/*
 * Print X'
 */

void print_Seq_Align_X(char* X, char** P, int n, int m){
        if(m <0 || n<0){
                // reverseStr(newX);
                // cout<X[n-1]<<endl;
                return ;
        }
	if(P[n][m] == 'd'){
                // newX += X[n-1]; 
                print_Seq_Align_X(X, P, n-1, m-1);
                cout<<X[n-1] << endl;
        }
        if(P[n][m] == 'l'){
                // newX += '-';
                
                print_Seq_Align_X(X, P, n, m-1);
                cout<<"-"<< endl;
        }
        if(P[n][m] == 'u'){
                // newX += X[n-1]; 
                print_Seq_Align_X(X, P, n-1, m);
                cout<<X[n-1] << endl;
        }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
                if(m<0 || n<0){
                        return;
                }
		if(P[n][m] == 'd'){
                print_Seq_Align_Y(Y, P, n-1, m-1);
                        cout<<Y[m-1] << endl;
        }
               if(P[n][m] == 'l'){
                print_Seq_Align_Y(Y, P, n, m-1);
                cout<<Y[m-1] << endl;
        }
               if(P[n][m] == 'u'){
                print_Seq_Align_Y(Y, P, n-1, m);
                cout<<"-"<< endl;
        }
}
