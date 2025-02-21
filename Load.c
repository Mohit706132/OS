#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer_size 41
#define mem_size 100

char M[mem_size][4]={'\0'}; // Memory
char IR[4]; // Instruction
int IC; // Counter
int C; // Toggle 0-F 1-T
char R[5]; // Register
char buffer[buffer_size]; // 40 byte buffer
int SI; //Interrrpt
int JC = 0; //JOB Counter 

FILE *input = NULL,*output = NULL ;


//functions
void init(); 
void MOS(); //Master Mode
void EUP(); //Execute User Program
void SE(); //Start Execution
void WRITE();
void READ();
void TERMINATE();
void LoadR();
void StoreR();
void compare();

void memdump(){
    for (int i = 0; i < mem_size; i++)
    {
        if(i<10)
        printf("M[0%d] : |%c|%c|%c|%c|\n",i,M[i][0],M[i][1],M[i][2],M[i][3]);
        else
        printf("M[%d] : |%c|%c|%c|%c|\n",i,M[i][0],M[i][1],M[i][2],M[i][3]);
    }
}

void readIR(char IR[],char *m){
    for (int i = 0; i < 4; i++)
    {
        IR[i] = m[i];
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
    
    R[4]='\0';

    IC = 0; // counter to 0
    
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
            SE();
        }
        else if ((check=strstr(buffer,"$END")) != NULL)
        {
            printf("\nEND of Job %d\n",++JC);
        }
        
        if (load)
        {
            // printf("%s\n",buffer);
            char *r= buffer;
            int i,l;
        while ( *r != '\n' )
        {
            l=( *r != 'H' )?4:1;
            for (int j = 0; j < l; j++,r++)
            {
                M[m][j]= *r;
            }
            m++;
        }
        }   
    }
    
}

void READ(){
    int m = ((int)IR[2]-48)*10+((int)IR[3]-48);
    // printf("%d",m);
    fgets(buffer,sizeof(buffer),input);
    // printf("%s",buffer);
    char *r= buffer;
    while (*r != '\n'){
        // printf("%c",*r);
        for (int i = 0; i < 4; i++){
            M[m][i] = *r++;
            if( *r == '\n' )
                break;
        }
        m++;
    }
}

void WRITE(){
    int add =((int)IR[2]-48)*10+((int)IR[3]-48),j=0;
    for (int i = add ; i < add + 10; i++)
    {
        for(int j=0; j<4 ; j++)
        fputc(M[i][j],output);
    }
    fputc('\n',output);
}
void TERMINATE(){
    printf("\n\n");
    fputc('\n',output);
    fputc('\n',output);
    memdump();
    LOAD();
}

void LoadR(){
    readIR(R,&M[((int)IR[2]-48)*10+((int)IR[3]-48)]);
    // printf("R:%s\n",R);
}

void StoreR(){
    readIR(M[((int)IR[2]-48)*10+((int)IR[3]-48)],R);
    // char temp[5];
    // temp[4]='\0';
    // memcpy(temp,M[((int)IR[2]-48)*10+((int)IR[3]-48)],4);
    // printf("M[%d] : %s\n",((int)IR[2]-48)*10+((int)IR[3]-48),temp);
}

void compare(){
    char temp[5];
    temp[4]='\0';
    memcpy(temp,M[((int)IR[2]-48)*10+((int)IR[3]-48)],4);
    if (!strcmp(R,temp))
    C=1;
    else
    C=0;
    // printf("R : %s\nM[%d] : %s\nC:%d\n",R,((int)IR[2]-48)*10+((int)IR[3]-48),temp,C);
}

void MOS(){
    (SI==1) ? READ() : (SI==2) ? WRITE() : (SI==3) ? TERMINATE() : 0 ;
}

void EUP(){
    readIR(IR,M[IC]);
    IC++;
    SI = 0;
    // printf("%d\t",IC);
    switch (IR[0])
    {
    case 'G':
        SI =1; MOS(); break;
    case 'P':
        SI =2; MOS(); break;
    case 'H':
        SI =3; MOS(); return;
    case 'L':
        LoadR(); break;
    case 'S':
        StoreR(); break;
    case 'C':
        compare(); break;
    case 'B':
    if (C)
    {
        IC = ((int)IR[2]-48)*10+((int)IR[3]-48);
    }else
    break;
    // printf("IC :%d\n",IC);
    default: break;;
    }
    EUP();
}

void SE(){
    IC=0;
    EUP();
}

int main()
{
    input = fopen("input.txt", "r");
    output = fopen("output.txt","w");

    if (input == NULL || output == NULL) {
        printf("The file is not opened");
        exit(0);
    }
    LOAD();

    return 0;
}
