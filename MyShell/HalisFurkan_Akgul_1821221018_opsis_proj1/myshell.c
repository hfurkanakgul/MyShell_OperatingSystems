#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// parametre adedini bulan fonksiyon.
int sayiBulma(char **parca){  
    int sayac=0;            
    int i=0;                
    while(i<strlen(parca)){
        if(parca[i]==NULL){
            break;
        }
        else{
            sayac++;
        }
        i++;
    }
    return sayac;
}

// Çıkış yapılana kadar kullanıcıdan input alır.
int inputAl(char *kgirisi) 
{
    printf("\n myshell>> ");
    char boyut[200];
    gets(boyut); 
    if (strlen(boyut) != 0)
    {
        strcpy(kgirisi, boyut);
        return 1;
    }
    else
    {
        return 0;
    }
}

// Aynı anda birden fazla komutu çalıştırabilmek için komutları pipe çizgisine göre sıralıyoruz.
void ayitDikcizgi(char * inp, char ** bolme) {
  int i = 0;
  while(i < 200) {
    bolme[i] = strsep( & inp, "|");

    if (bolme[i] == NULL) {
      break;
    }
    i++;
  }
}

  // Bir komutdaki parametleri sıralıyoruz.
void ayirBosluk(char * inp, char ** bolme) {
  int i=0;
  while(i<200) {
    bolme[i] = strsep( & inp, " ");
    if (bolme[i] == NULL) {
      break;
    }
    if (strlen(bolme[i]) == 0) {
      i--;
    }
    i++;
  }
}

  // Bir komutdaki çalıştırılması gereken fonksiyon çalıştırılır.
void sorgular(char **parca)      
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("\n yanlis bir komut girdiniz");
        return;
    }
    else if (pid == 0)             //İlk girdiğimiz komutun ne olduğuna bağlı olduğu fonksiyona veya bash'in bir fonksiyonuna gider.
    {
        if (strcmp("cat", parca[0]) == 0)
        {  
        execv("/bin/cat", parca);
        }
        else if (strcmp("ls", parca[0]) == 0)
        {  
        execv("/bin/ls", parca);
        }
        else if (strcmp("bash", parca[0]) == 0)
        {  
        execv("/bin/bash", parca) ;  
        }
        else if (strcmp("tekrar", parca[0]) == 0)
        {
            if (atoi(parca[2]) < 0  || sayiBulma(parca)!=3)
            {
                printf("Parametre sayisi hatasi");
            }
            else
            {
                if (execv(parca[0], parca) < 0)
                {
                    printf("\n yanlis bir komut girdiniz");
                }
            }
        }
        else if (strcmp("islem", parca[0]) == 0)
        {
            if (sayiBulma(parca)!=4)
            {
                printf("Parametre sayisi hatasi");
            }
            else if((strcmp("topla",parca[1]) != 0) && (strcmp("cikar",parca[1]) !=0 )  ){
            printf("Yanlis bir islem girdiniz");
            } 
            else  
            {   
                if (execv(parca[0], parca) < 0)
                {
                    printf("\n yanlis bir komut girdiniz");
                }
            }
        }
         else if (strcmp("clear", parca[0]) == 0)
        {  
          execv("/bin/clear", parca); 
        }
        else if (execv(parca[0], parca) < 0)
        {
            printf("\n yanlis bir komut girdiniz");
        }
        exit(0);
    }
    else
    {
        wait(NULL);
        return;
    }
}

int main(int argc, char *argv[])
{   
    char *argList[200] = {NULL};
    char userCom[200] = {NULL};
    char *comList[200] = {NULL};
    
    // Kullanıcıdan bir veya birden fazla komut alıyoruz. 
    // Komutları kontrol ediyor ve parçalıyoruz. Ve bunları parçalayarak gerekli bulundukları fonksiyonları çağırıyoruz.
    while (1)
    {
        if (!inputAl(userCom))
        {
            continue;
        }
        ayitDikcizgi(userCom, comList);
        int i =0;
        while (i < 200)
        {
            if (comList[i] == NULL)
            {
                break;
            }
            else
            {
                ayirBosluk(comList[i], argList);
                if (strcmp("exit", comList[i]) == 0)
                {
                    exit(0);
                }
                else
                {
                    sorgular(argList);
                }
            }
            i++;
        }
        
    }
    
    return 0;
}