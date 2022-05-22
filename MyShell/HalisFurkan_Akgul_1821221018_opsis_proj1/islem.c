#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

int main(int argc, char *argv[])
{   
    char *argList[4];
    argList[0]=argv[1];
    argList[1]=argv[2];
    argList[2]=argv[3];
    argList[3]=NULL;

    int a;
    int i=fork();
    if (i==0)
    {
        a = execv(argList[0],argList);
    }
    else{
        wait(&a);
        if(strcmp("topla",argList[0])==0){
            printf("%s + %s \nResult :  %d \n",argList[1],argList[2],WEXITSTATUS(a));  
        }                                                                     
        else if(strcmp("cikar",argList[0])==0){
              printf("%s - %s \nResult :  %d \n",argList[1],argList[2],WEXITSTATUS(a));  
        }
    }

    return 0;
}

    

