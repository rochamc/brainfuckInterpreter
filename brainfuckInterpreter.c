/*

    Brainfuck language interpreter

*/

#include<stdio.h>
unsigned char mem[30000] ={0}; //cells
unsigned char src[30000] ={0};      //source code to be interpreted

int stack[30000] = {0};
int stackpos = -1;


int findEndLoop(int currentpos)
{
    int count = 0;
    int x = currentpos+1;
    while(1){
      if((src[x] == ']')&&(count == 0))
            break;
      if(src[x] == '[')
          count++;
      if (src[x] == ']')
            count--;
      x++;
    }
    return x;
}

int readSource()
{
    int x = 0;

    FILE *fp;

    fp = fopen ("bf.txt", "rt");
    src[x] = getc(fp);
    while(!feof(fp)){
        x++;
        src[x] = getc(fp);
    }
    fclose(fp);
    return x-1;
}


int main()
{
   unsigned char *p;
   int i=0,srcpos = 0, srcsize;

   p = mem;

   srcsize = readSource();

   while(srcpos <= 30000)
   {

        if((srcpos == srcsize)&&(stackpos < 0)&&(*p == 0)){
            return 0;
        }

        switch(src[srcpos]){
            case '+':
                 ++*p;
                 break;
            case '-':
                 --*p;
                 break;
            case '>':
                 ++p;
                 break;
            case '<':
                 --p;
                 break;
            case '[':{
                 if(*p > 0){
                    stackpos++;
                    stack[stackpos] = srcpos;
                 }
                 else{
                    srcpos = findEndLoop(srcpos);
                 }
                 break;
            }
            case ']': {
                    srcpos = stack[stackpos] -1;
                    stackpos--;
                 break;
            }
            case '.':
                 putchar(*p);
                 break;
            case ',':
                 *p = getchar();
                 break;
            default:
                 break;
        }

        srcpos++;

   }

}
