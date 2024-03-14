#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
 
main(int argc, char *argv[])
{  
   FILE *fin, *fout;
   char c, A[80], B[80];
   int  j,k,nc, a,b,s,t, x,y, ptr[26];
 
   sscanf(argv[1],"%d", &a); 
   sscanf(argv[2],"%d", &b); 
   fin =fopen(argv[3],"r"); 
 
   for (j=0; j<26; j++) ptr[j]=0;
   ptr[ 1]= 1;  ptr[ 3]= 9;  ptr[ 5]=21;  ptr[ 7]=15;  
   ptr[ 9]= 3;  ptr[11]=19;  ptr[15]= 7;  ptr[17]=23;
   ptr[19]=11;  ptr[21]= 5;  ptr[23]=17;  ptr[25]=25;
 
   nc=0;  
   fscanf(fin,"%c",&c); A[0]=c;
   while (c != '\n') {fscanf(fin,"%c",&c); A[++nc]=c;}
f   printf("y=%2d x + %d (mod 26)\n", a,b); 
   printf("plaintext:  "); 
   for (j=0; j<nc; j++) printf("%c",A[j]); printf("\n");
 
   if (a%2==0 || a==13 || a>25 || b>25) 
     printf("(a,b)=(%2d,%2d) is invalid\n",a,b);
   else {s=ptr[a]; t=(s*(26-b))%26;}
 
   for (k=0; k<nc; k++) {
     x=(int) A[k] - (int) 'a';
     y=(a*x+b)%26; 
     B[k]=(char) (y+65);
   }
   printf("ciphertext: "); 
   for (j=0; j<nc; j++) printf("%c",B[j]); printf("\n");
 
   printf("Decipher: y=%2dx + %2d\n",s,t);
   for (k=0; k<nc; k++) {
     y=(int) B[k] - (int) 'A';
     x=(s*y+t)%26; 
     A[k]=((x==23)? ' ' : (char) (x+97));
   }
   printf("decrypted message: "); 
   for (j=0; j<nc; j++) printf("%c",A[j]); printf("\n");
   printf("\n");
}