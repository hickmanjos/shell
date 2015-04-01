#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

void parse_arg(char* arg, char* argv[], char input[])
{
    char shell[256];
    getcwd(shell, 255);
    cout << shell << ":~$ ";
    cin.getline(input,50);

	arg = strtok(input, " ");
	int i = 0;

	while(arg != NULL)
	{
	    argv[i] = arg;
	    i++;
	    arg = strtok(NULL, " ");
	}
}

void exec_arg(char* argv[])
{
    pid_t pid;
    pid = fork();
    switch(pid)
    {
        case -1:
            cout << "DEBUG:Fork Failure" << endl;
            exit(-1);
        case  0:
            execvp(argv[0], argv);

            if(execvp(argv[0], argv) == -1)
            {
                cout << "Command Not Found: " << argv[0] << endl;
                exit(0);
            }

        default:
            wait(NULL);
            cout << endl << "Shell Process Finished" << endl;
    }

}

void clean_arry(char* argv[])
{
    for(int i=0; i < 40; i++){argv[i] = NULL;}
}

int main()
{
   char* arg;
   char* argv[40];
   char input[50];

   while(argv[0] != NULL)
   {
    clean_arry(argv);
   	parse_arg(arg, argv, input);

   	if(strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0 )
   	{
        break;
   	}

    else if(strcmp(argv[0],"cd") == 0)
   	{
        chdir(argv[1]);
        wait(NULL);
        cout << endl << "Shell Process Finished" << endl;
   	}


	else
	{
        exec_arg(argv);
	}

   }
   return 1;
}
