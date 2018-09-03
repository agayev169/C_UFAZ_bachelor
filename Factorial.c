#include<stdio.h>

int i=0,j=0,fact[200000],k=0,l=1,n=0,temp=0;
    
int main() {
    fact[0]=1;
    scanf("%d",&n);
    for (i=2;i<=n;i++){
		for (j=0;j<l;j++){
			k=temp+i*fact[j];
        	fact[j]=k%10;
       		temp=k/10;
        }   
        while (temp>0){
        	fact[l++]=temp%10;
            temp=temp/10;
		}          
	}
    for (i=l-1;i>-1;i--)
    printf("%d\n",fact[i]);
}
