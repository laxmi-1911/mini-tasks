#include<stdio.h>
#include<conio.h>
void main()
{
int i,n,max,arr[100];     //declaration of variable
clrscr();                                     //for clear screen
printf("enter the number of element :");
scanf("%d",&n);                       //accept number of element from the user
printf("\n enter the values :\n");
for(i=0; i<=n-1;i++)     //this loop for indexing
{
scanf("%d",& arr[i]);
}
max = arr[0];
for(i=0;i<=n-1;i++) //this loop for output
{
if(max < arr[i])  //if any oyher element is greater than maximum ,than the value is replace by that element
max=arr[i];
}
printf("\n the maximum value is :%d",max); //large number will be printed
getch();
}

//thank you