#include "header.h"

int main(int argc, char **argv)
{
FILE *fp ;
int i,end;
//check whether file name is given in cmd line arguments
    if(argc ==1)
    {
	printf("Usage:./a.out <.c file>\n");
	return e_failure;
    }
    //check for extension
    else
    {
	if(e_failure == extention(argv[1],&fp,&end))
	    return e_failure;
    }
//parsing(run till EOF)
    for(i=0;ftell(fp)!= end;i++)
    {
    if(e_failure == parse(fp))
    {
	fprintf(stderr,"parsing function unsuccessfull\n");
    }
    }
    printf("\nparsing: %s: done\n",argv[1]);
//keyword
  /*/ if(e_failure == keyword(fp))
   {
       fprintf(stderr,"keyword search function unsuccessfull\n");
   }
*/



}
