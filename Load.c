#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define buffer_size 42
#define mem_size 100

typedef unsigned char byte_t; //to eliminate signed misinterpretation while converting back to integer from Ascii stored format

char M[mem_size][4]={'\0'}; // Memory
char IR[4]; // Instruction
short int IC; // 2 byte Counter
int C; // Toggle 0-F 1-T
char R[5]; // Register
char A[4]; // Accumalator
int overflow; // Overflow
char buffer[buffer_size]; // 40 byte buffer
int SI; //Interrrpt
int JC = 0; //JOB Counter for debugging purpose
div_t res; // struct for division has quot and rem
FILE *input = NULL,*output = NULL ;

//functions
void init(); //intializes memory, register with space, buffer and C with 0  
void MOS(); //Master Mode
void EUP(); //Execute User Program
void SE(); //Start Execution
void READ(); //Reads 1 block data from data card to specified memory
void WRITE(); //Writes 1 block to output file
void TERMINATE(); //Terminates current job by writing 2 blank lines
void LoadR(); //Loads 1 word from specified memory(1 word) to Register
void StoreR(); //Stores content of R to specified memory(1 word)
void compare(); //Compares content of R and specified memory and sets carry flag accordingly
int char_int(); // converts IR[2,3] to integer address to acess Memoery location
void add(); //Adds Content of A and specified memory location and stores in A
void sub(); //
void division(); // Useing in built in division function from stlib
void mul(); //
int toINT(byte_t *m); //converts Ascii to Integer
void storeInt(int n, byte_t *m); //Stores integer from dta to memory, Not useful anymore due to change in LD functionality need to be discarded 
void printM(); //Prints Ascii encoded Integer to output file in integer 
void NumStore(byte_t *m); //Stores value of Accumlator into Memory location
void ALoad(char *r,int n); // Loads Accumlator 
void NumLoad(char *r); // Like GD but for numbers.
void L_shift(); 
void R_shift();
void AND();
void OR();
void XOR();
void NOT();




int char_int(){
    return ((int)IR[2]-48)*10+((int)IR[3]-48);
}

void memdump(){
    for (int i = 0; i < mem_size-60; i++)
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
        if ((check=strstr(buffer,"$AMJ")) != NULL){
            init();
            load = 1;
            continue;
        }
        else if ((check=strstr(buffer,"$DTA")) != NULL){
            load = 0;
            SE();
        }
        else if ((check=strstr(buffer,"$END")) != NULL){
            printf("\nEND of Job %d\n",++JC);
            LOAD();
        }
        if (load){
            // printf("%s",buffer);
            char *r= buffer;
            int l;
            while ( *r != '\n' ){
            l = ( *r != 'H' )?4:1;
            
            for (int j = 0; j < l; j++,r++)
                M[m][j]= *r;

            m++;
            } 
        }  
    }
}

void READ(){
    int m = (char_int());
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
    int add =(char_int()),j=0;
    for (int i = add ; i < add + 10; i++){
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
}

void LoadR(){
    readIR(R,&M[(char_int())]);
    // printf("R:%s\n",R);
}

void StoreR(){
    readIR(M[(char_int())],R);
    // char temp[5];
    // temp[4]='\0';
    // memcpy(temp,M[(char_int())],4);
    // printf("M[%d] : %s\n",(char_int()),temp);
}

void compare(){
    char temp[5];
    temp[4]='\0';
    memcpy(temp,M[(char_int())],4);
    if (!strcmp(R,temp))
        C=1;
    else
        C=0;
    // printf("R : %s\nM[%d] : %s\nC:%d\n",R,(char_int()),temp,C);
}


int toINT(byte_t *m){
    return (m[3]+ (m[2]<<8) + (m[1]<<16)+ (m[0]<<24));
}


void storeInt(int n, byte_t *m){
    // printf("-%d-\n",n);
    m[0]=(byte_t)(n>>24);
    m[1]=(byte_t)(n>>16)&(255);
    m[2]=(byte_t)(n>>8)&(255);
    m[3]=(byte_t)(n>>0)&(255);
    // printf("--%d--\n",m[0]);
    // printf("--%d--\n",m[1]);
    // printf("--%d--\n",m[2]);
    // printf("--%d--\n",m[3]);
    // printf("M[N]:%d\n ", toINT(M[(char_int())]));
}

void printM(){
    int n = toINT(M[(char_int())]);
    fprintf(output,"%d",n);
}

void NumStore(byte_t *m) {
    // int n = toINT(A), b = 0;
    // char a[12];
    
    // printf("n: %d\n", n);
    // while (n != 0) {
    //     a[b++] = (char)(n % 10 + '0');
    //     n = n / 10;
    // }
    // a[b] = '\0';
    

    // printf("\nB: %d\nC: ", b);

    // while (b-- >=0) {
    //     for (int i = 0; i < 4; i++) {
    //         if(b-i<0)
    //         break;
    //         printf("%c", a[b]);
    //         m[i] = a[b-i]; 
    //     }
    //     m++;
    // }
    // printf("\nM: %s\tb: %d", m, b);
    for (int i = 0; i < 4 ; i++)
        m[i]=A[i];
}

void ALoad(char *r,int n){
    r[0]=(char)(n>>24);
    r[1]=(char)(n>>16)&(255);
    r[2]=(char)(n>>8)&(255);
    r[3]=(char)(n>>0)&(255);
}

void NumLoad(char *r){
    int n; 
    while ( fscanf(input,"%d",&n))
    {
        r[0]=(char)(n>>24);
        r[1]=(char)(n>>16)&(255);
        r[2]=(char)(n>>8)&(255);
        r[3]=(char)(n>>0)&(255);
        r+=4;
    }
    // printf("n:%d\n",n);
    // printf("--%d--\n",R[0]);
    // printf("--%d--\n",R[1]);
    // printf("--%d--\n",R[2]);
    // printf("--%d--\n",R[3]);
}

void add(){
    int n;
    fscanf(input,"%d",&n);
    printf("M(N):%d\n",n);
    storeInt(n,M[(char_int())]);
    int a = toINT(A) + toINT(M[(char_int())]);
    // printf("ADD:%d",a);
    storeInt(a,A);
    fgets(buffer,buffer_size,input);
}


void sub(){
    int n;
    fscanf(input,"%d",&n);
    printf("M(N):%d\n",n);
    storeInt(n,M[(char_int())]);
    int a = toINT(A) - toINT(M[(char_int())]);
    // printf("SUB:%d",a);
    storeInt(a,A);
    fgets(buffer,buffer_size,input);
}

void division(){
    int n;
    fscanf(input,"%d",&n);
    printf("M(N):%d\n",n);
    storeInt(n,M[(char_int())]);
    res = div(toINT(A),toINT(M[(char_int())]));
    printf("Q:%d\tR:%d\n",res.quot,res.rem);
    storeInt(res.quot,A);
    storeInt(res.rem,R);
}

void mul(){
    int n;
    fscanf(input,"%d",&n);
    // printf("M(N):%d\n",n);
    // printf("A:%d\n",toINT(A));
    storeInt(n,M[(char_int())]);
    long long int a =(long long) toINT(A)*toINT(M[(char_int())]);
    printf("%d",a);
    if (a>(long)INT_MAX)
        overflow = 1;
    else
        storeInt(a,A);
}

void L_shift(){
    // printf("%d\n",char_int());
    int n = toINT(A)<<char_int();
    // printf("n:%d\n",n);
    ALoad(A,n);
    // printf("R:%s",R);
}

void R_shift(){
    int n = toINT(A)>>char_int();
    printf("n:%d\n",n);
    ALoad(A,n);
    // printf("R:%s",R);
}

void AND(){
    int n;
    fscanf(input,"%d",&n);
    storeInt(n,M[(char_int())]);
    // printf("A:%d\tM[]:%d\n",toINT(A),toINT(M[char_int()]));
    int a = toINT(A) & toINT(M[char_int()]);
    printf("%d",a);
    ALoad(A,a);
}

void OR(){
    int n;
    fscanf(input,"%d",&n);
    storeInt(n,M[(char_int())]);
    // printf("A:%d\tM[]:%d\n",toINT(A),toINT(M[char_int()]));
    int a = toINT(A) | toINT(M[char_int()]);
    printf("%d",a);
    ALoad(A,a);
}

void XOR(){
    int n;
    fscanf(input,"%d",&n);
    storeInt(n,M[(char_int())]);
    // printf("A:%d\tM[]:%d\n",toINT(A),toINT(M[char_int()]));
    int a = toINT(A) ^ toINT(M[char_int()]);
    printf("%d",a);
    ALoad(A,a);
}

void NOT(){
    int a = !toINT(A);
    printf("%d",a);
    ALoad(A,a);
}

void MOS(){
    (SI==1) ? READ() : (SI==2) ? WRITE() : (SI==3) ? TERMINATE() : 0 ;
}

void EUP(){
    readIR(IR,M[IC]);
    IC++;
    SI = 0;
    // printf("%d\t",IC);

    if (IR[0] == 'G' && IR[1] == 'D') { SI =1; MOS(); }
    else if (IR[0] == 'P' && IR[1] == 'D'){ SI =2; MOS(); }
    else if (IR[0] == 'H'){ SI =3; MOS(); return; }
    else if (IR[0] == 'L' && IR[1] == 'R'){ LoadR(); }
    else if (IR[0] == 'S' && IR[1] == 'R'){ StoreR(); }
    else if (IR[0] == 'B' && IR[1] == 'T'){ if (C) IC = (char_int()); }
    else if (IR[0] == 'C' && IR[1] == 'R'){ compare(); }

    else if (IR[0] == 'L' && IR[1] == 'D'){ NumLoad(M[char_int()]);}
    else if (IR[0] == 'S' && IR[1] == 'A'){ NumStore(M[(char_int())]); }
    else if (IR[0] == 'P' && IR[1] == 'M'){ printM(); }
    else if (IR[0] == 'A' && IR[1] == 'D'){ add(); }
    else if (IR[0] == 'S' && IR[1] == 'B'){ sub(); }
    else if (IR[0] == 'D' && IR[1] == 'I'){ division(); }
    else if (IR[0] == 'M' && IR[1] == 'L'){ mul(); }
    else if (IR[0] == 'L' && IR[1] == 'S'){ L_shift(); }
    else if (IR[0] == 'R' && IR[1] == 'S'){ R_shift(); }
    else if (IR[0] == 'A' && IR[1] == 'N'){ AND();}
    else if (IR[0] == 'O' && IR[1] == 'R'){ OR(); }
    else if (IR[0] == 'X' && IR[1] == 'O'){ XOR(); }
    else if (IR[0] == 'N' && IR[1] == 'T'){ NOT(); }
    else{
        printf("Wrong Instrunction Found!!\nCheck Instructuins\n");
        exit(0);
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
    freopen("Terminal.txt","w",stdout);

    if (input == NULL || output == NULL) {
        printf("The file is not opened");
        exit(0);
    }
    LOAD();

    fclose(input);
    fclose(output);

    return 0;
}