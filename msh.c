#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
void help()
{
  printf("enter Linux commands, or ‘exit’ to exit\n");
}
int main()
{
  const int string_size = 121;
  char string[string_size];
  char ex[6] = {'e', 'x', 'i', 't','\n','\0'};
  char help[6] = {'h', 'e', 'l', 'p','\n','\0'};
  char today[7] = {'t', 'o', 'd', 'a','y','\n','\0'};
  printf("msh> ");
  while( fgets(string, string_size , stdin) )
  {
    if (string[119]=='\n'|| string[119]=='\0')
    {
      //if input is not exit
      if(strcmp(string,ex))
      {
          //if input is not help
          if(strcmp(string,help))
          {
              if(strcmp(string,today))
                {
                  int rc = fork();
                  if(rc==0)
                  {

                    char *token = strtok (string," \n\t");
                    char *myargs[5];
                    int i =0;

                    //filling string array with tokens
                    while (token != NULL)
                    {
                      myargs[i]=strdup(token);
                      token = strtok (NULL, " \n\t");
                      i+=1;
                    }
                    myargs[i]=NULL;

                    //if execvp return print error
                    if(execvp(myargs[0], myargs))
                    {
                      printf("msh: %s: %s\n", myargs[0], strerror(errno));
                      exit(errno);
                    }
                  }

                  //parent msh process
                  else
                  {
                    wait(NULL);
                    printf("msh> ");
                  }

                }
                else
                {
                  int day, month, year;
                  time_t now;
                  time(&now);
                  struct tm *local = localtime(&now);
                  day = local->tm_mday;        	// get day of month (1 to 31)
                  month = local->tm_mon + 1;   	// get month of year (0 to 11)
                  year = local->tm_year + 1900;	// get year since 1900
                  printf("%02d/%02d/%d\n", month,day, year);
                  printf("msh> ");
                }
                
            }
            else
            {
              printf("enter Linux commands, or ‘exit’ to exit\n");
              printf("msh> ");
            }

      }
      else
      {
        break;
      }

    }
    else
    {
      int ch;
      while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
      {}
      string[119]='\0';
      printf("error:input too long\n");
      printf("msh> ");
    }

  }
  return 0;
}
