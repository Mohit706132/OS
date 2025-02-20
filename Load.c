#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer_size 41
#define mem_size 100

char M[mem_size][4]={'\0'}; // Memory
char IR[4]; // Instruction
int IC[2]; // Counter
int C; // Toggle 0-F 1-T
char R[4]; // Register
char buffer[buffer_size]; // 40 byte buffer

FILE *input,*output;

//functions
void init(); 
void MOS(); //Master Mode
void UEP(); //Execute User Program
void SE(); //Start Execution

void memdump(){
    for (int i = 0; i < mem_size-60; i++)
    {
        printf("M[%d] : |%c|%c|%c|%c|\n",i,M[i][0],M[i][1],M[i][2],M[i][3]);
    }
}

void init(){
    //memory to space
    for (int i = 0; i < mem_size; i++)
    {
        M[i][0] =' ';
        M[i][1] =' ';
        M[i][2] =' ';
        M[i][3] =' ';
    }
    // buffer to 0
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] = 0;
    }
    // Register to space
    for (int i = 0; i < 4; i++)
    {
        IR[i]= ' ';
        R[i]=' ';
    }

    IC[0]=0;
    IC[1]=0;
    
    C = 0; // flag to false by default
}
void LOAD(){
    int load = 0,m=0;
    while (fgets(buffer,sizeof(buffer),input)){
        char *check = NULL;
        if ((check=strstr(buffer,"$AMJ")) != NULL)
        {
            init();
            load = 1;
            continue;
        }
        else if ((check=strstr(buffer,"$DTA")) != NULL)
        {
            load = 0;
            
        }
        else if ((check=strstr(buffer,"$END")) != NULL)
        {
            printf("\nEND\n ");
        }
        
        if (load)
        {
            // printf("%s\n",buffer);
            char *r= buffer;
            int i,l;
        while ( *r != '\0' )
        {
            l=( *r != 'H' )?4:1;
            for (int j = 0; j < l; j++,r++)
            {
                M[m][j]= *r;
            }
            m++;
            if ( *r == '\n' )
            break;
        }
        }   
    }
    memdump();
}
int main()
{
    input = fopen("input.txt", "r");

    if (input == NULL) {
        printf("The file is not opened");
        exit(0);
    }
    LOAD();

    return 0;
}
