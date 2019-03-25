#include "header.h"
//to check the extension
status extention(char *arr,FILE **fp,int *end)
{
    //check for file extention
    int j;
    for(j=0;arr[j] != '\0';j++)
    {
	if(arr[j] == '.')
	{
	    char *temp = &arr[j];
	    if(0 == strcmp(".c",temp))
	    {
		break;
	    }
	    else
	    {
		puts("Not a C file");
		//return e_failure;
	    }
	}
    }

    if(arr[j] == '\0')
    {
	puts("file extension not specified/not proper");
	return e_failure;
    }
    //if c file -> open the file 
    *fp = fopen(arr,"r");//open file in read mode
    if(*fp == NULL)
    {
	fprintf(stderr,"opening of %s file unsuccessfull", arr);
	return e_failure;
    }
    int i;
    //open the file n check whether it is empty or not
    fseek(*fp, 0L, SEEK_SET);
    int start = ftell(*fp);
    fseek(*fp,0L,SEEK_END);
    *end = ftell(*fp);
    fseek(*fp, 0L, SEEK_SET);
    if(start == (*end))
    {
	fprintf(stderr,"file is empty\n");
	return e_failure;
    }

    return e_success;
}

status parse(FILE *fp)
{
    int i=0;
    char buf[1000];
    char temp;
    char iden[1000];
    int j=0,count =0;
    do
    {
	fread(&buf[i],1,1,fp);
	if(buf[i] == '"')
	{
	    buf[i++]='"';
	    fread(&buf[i],1,1,fp);
	    for( ;buf[i++] != '"'; )
	    {  
		fread(&buf[i],1,1,fp);
	    }
	    buf[i++] ='\0';
	    buf[i]='"';
	    break;
	}

	else	if(buf[i] == ' '|| buf[i] == '\n'||buf[i] == ';')
	{
	    buf[i]='\0';
	    strcpy(iden,buf);
	    if(e_failure == keyword(iden))
	    {
		fprintf(stderr,"keyword not found\n");
	    }
	    if(e_failure == variable(iden))
	    {
		fprintf(stderr,"keyword not found\n");
	    }
    
	    break;
	}

	else	if(buf[i] == '('|| buf[i]=='=')
	{
	    fseek(fp,-1L,SEEK_CUR);
	    fread(&temp,1,1,fp);
	    buf[i] = '\0';
	    if(e_failure == variable(buf))
	    {
		fprintf(stderr,"identifier not found\n");
	    }
	    break;
	}
/*	else	if(buf[i] == '=')
	{   
	    fseek(fp,-1L,SEEK_CUR);
	    fread(&temp,1,1,fp);
	    buf[i] = '\0';
	    if(e_failure == variable(buf))
	    {
		fprintf(stderr,"identifier not found\n");
	    }
	    break;
	}*/

	else if(0 != isdigit(buf[i]))
	{

	    printf("literal:	%c\n",buf[i]);
	    break;
	}    
	else if(buf[i]==')'||buf[i]=='('||buf[i]=='{' || buf[i] == '}' || buf[i] == '+'||buf[i] == '-'||buf[i]=='*' || buf [i] == '/'||buf[i] == '=')
	{
	    printf("operator:	%c\n",buf[i]);
	    break;
	}
	else
	{
	    temp =  buf[i];
	}
    }while(buf[i++] != '\n');
    if(buf[i]=='"')
    {
	if(e_failure == s_n_literals(buf))
	{
	    fprintf(stderr,"s_n_literals not found\n");
	}
    }
    if(buf[i] == '\0')
    {
#if 0
	if(e_failure == keyword(iden))
	{
	    fprintf(stderr,"keyword not found\n");
	}
#endif
	/*if(e_failure == variable(iden))
	  {
	  fprintf(stderr,"keyword not found\n");
	  }*/
    }

    if(e_failure == operators(&temp))
    {
	fprintf(stderr,"operator not found\n");
    }
    if(e_failure == literals(&temp))
    {
	fprintf(stderr,"Literals not found\n");
    }

    return e_success;
}









status s_n_literals(char *buf)
{
    int i=0;
    if(buf[i++] == '"');
    if(buf[i]>='a'|| buf[i]<='z'|| buf[i] <= 'A' || buf[i] >= 'Z' ||buf[i]<='0'||buf[i]>= '9')
    {
	printf("s_n_literals:	%s\n",buf);
    }

}


status keyword( char *buf)
{
    char key[32][10]={"auto", "break","case ", "char", "const","continue","deafult","do","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","double","else","enum","extern", "float","for","goto"};




    int i=0;
    if(buf[0] == '\0')
	return e_success;
    for(i=0;i<32;i++)
    {
	if(0 == strcmp(buf,key[i]))
	{
	    printf("keyword:	%s\n",key[i]);
	}
    }
    return e_success;
}
status variable( char *buf)
{
    if (buf[0] == '\0')
	return e_success;
    char key[32][10]={"auto", "break","case ", "char", "const","continue","deafult","do","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","double","else","enum","extern", "float","for","goto", "if"};

    int i=0;
    int count=2;
    for(i=0;i<32;i++)
    {
	if(count= strcmp(buf,key[i]));

	if(count == 0)
	{
	    return e_success;
	}
    }
    if(count != 0)
	printf("identifier:	%s\n",buf);

}


/*status identifier( char *buf)
  {
  char key[3][10]={"main","printf","scanf"};

  int i=0;
  for(i=0;i<3;i++)
  {
  if(0 == strcmp(buf,key[i]))
  {
  printf("identifier:	%s\n",key[i]);
  }
  }
  return e_success;
  }*/
status operators( char *buf)
{

    char key[5][10]={"(",")","{","}","="};
    char str[2];
    str[0]=*buf;
    str[1]='\0';

    int i;
    for(i=0;i<5;i++)
    {
	if(0 == strcmp(str,key[i]))
	{
	    printf("operator:	%s\n",key[i]);
	}

    }
    *buf='a';
    return e_success;
}
status literals( char *buf)
{

    char key[5][10]={"0","1","2","3","4"};
    char str[2];
    str[0]=*buf;
    str[1]='\0';

    int i;
    for(i=0;i<5;i++)
    {
	if(0 == strcmp(str,key[i]))
	{
	    printf("literals:	%s\n",key[i]);
	}
    }
    *buf = 'a';
    return e_success;
}
