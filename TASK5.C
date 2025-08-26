#include<stdio.h>
#include<conio.h>
struct student {
int id;
char name[30];
int age;
};
void main(){
	    struct student students[3]={
	    {1, "reshmi ravidas",20},
	    {2,"suhani meena", 22},
	    {3,"aman vishvkarma",19},
	    };
	    int i;
	    clrscr();
	    printf("{\n");
	    printf("  \"students\":[\n");
	    for(i = 0; i< 3 ;i++){
	    printf("   {\n");
	    printf("   \"id\":%d,\n",students[i].id);
	    printf("   \"name\":\"%s\",\n",students[i].name);
	    printf("   \"age\":%d\n",students[i].age);

	    if(i==2)
	    printf("  }\n");
	    else
	    printf("   },\n");
	    }
	    printf("  ]\n");
	    printf("}\n");
	    getch();

	    }
