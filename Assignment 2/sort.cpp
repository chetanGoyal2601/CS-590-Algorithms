#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
  return -1;
      else
  return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
      {
        A[i+1] = A[i];
        i = i - 1;
      }

      A[i+1] = key;
    }
}

int string_compare_digit(char a, char b) {
  
  if (a == b)
    return 0;

  else {
    if(a < b) {
    return -1;
    }

  else
    return 1;
  }

}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
  int i;
  char* key;
  int key_len;
  char aux;

  for (int j = l+1; j < r; j++) {
    key = A[j];
    key_len = A_len[j];
    i = j - 1;

    if(d <= A_len[j]){
        aux = A[j][d];
      }
    else {
            aux = '0';
        }

    /*
    if (d > A_len[j] - 1) {
      key[d] = '0';
    }

    if (d > A_len[j] - 1) {
      aux = '0';
    }
    else {
      aux = A[j][d];
    }
    */

    while ((i >= l) && A_len[i] >= d && (string_compare_digit(A[i][d], aux)>0)) {
        A[i+1] = A[i];
        A_len[i+1] = A_len[i];
        i = i - 1;

        /*
        if (d > A_len[i] - 1 && i >= l) {
            aux = '0';
        }
        else {
            aux = A[i][d];
        }
        */
        }

        A[i+1] = key;
        A_len[i+1] = key_len;
    }
    //std::cout << A << std::endl;
    //std::cout << A_len[0] << std::endl;
    
}


void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d) {
    int C[256];
    char aux;
    for (int i = 0; i < 256; i++) {
      C[i] = 0;
    }
    for (int i = 0; i < n; i++) {
      if (A_len[i] - 1 < d) {
        aux = '0';
      }
      else {
        aux = A[i][d];
      }
      C[int(aux)]++;
    }

    for (int i = 0; i<256; i++) {
      C[i] = C[i] + C[i-1];
    }

    for (int i = n-1; i >= 0; i--) {
      if (A_len[i] - 1 < d) {
        aux = '0';
      }
      else {
        aux = A[i][d];
      }
      B[C[int(aux)]] = A[i];
      B_len[C[int(aux)]] = A_len[i];
      C[int(aux)]--;
    }

    for (int i = 0; i < n; i++) {
      A[i] = B[i];
      A_len[i] = B_len[i];
    }
    
}


void radix_sort_is(char** A, int* A_len, int n, int m) {
    /*for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
    int max = A_len[0];
    for (int i = 1; i < n; i++){
        if(max < A_len[i]){
          max = A_len[i];
        }
    }
  for (int d = max; d >= 0; d--) {
    insertion_sort_digit(A, A_len, 0, n, d);
  }/*
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
}

void radix_sort_cs(char** A, int* A_len, int n, int m) {
   char** B = new char*[n];
   int* B_len = new int[n];

   for (int i = 0; i < n; ++i) {
     B[i] = new char[m+1];
     B_len[i] = A_len[i];
   }

   for (int d = m-1; d >= 0; d--) {
    counting_sort_digit(A, A_len, B, B_len, n, d);
  }
    //bool o = check_sorted(A, 0, n);
    //std::cout << o;
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
