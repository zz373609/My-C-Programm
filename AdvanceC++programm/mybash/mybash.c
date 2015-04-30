//Zhiqiang Zhang
//Xinyi Wang
//cs4420
//Email: zz373609@ohio.edu
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include "parser.h"
char internalvars[100][100];
char internalvals[100][100];

int  numinternalvars;


int executenonexternal(char * cmd, char ** argv,int n){
    char* argv2[102];
    memcpy(argv2+1,argv,100*sizeof(char*));
    argv2[n+1]=0;
    argv2[0]=cmd;
   // printf("args: %d",n);
    if( access(cmd,X_OK) == 0)
        return execvp(cmd,argv2);

    char* pPath;
        char cwd[100];
    pPath = getenv ("PATH");

    char * curdir = strtok(pPath,":");
    char * cpath;
    
    while ( curdir != NULL){
        strcpy(cwd,curdir);
        char * ctemp = strcat(cwd,"/");
        cpath = strcat(ctemp,cmd);
        //printf("testcmd: %s\n",cpath);
        if(access( cpath, X_OK )==0)
            return execvp(cpath,argv2);
        curdir = strtok(NULL,":");
    }
    return -1;
}


void process_argument(char ** curarg){
 if(**curarg=='$'){
                        int foundvar=0;
                        int n;
                        for ( n=0;n<numinternalvars;n++)
                          if(strncmp((*curarg)+1,internalvars[n],100)==0){
                           // printf("found variable %s=%s\n",internalvars[n],internalvals[n]);
                            *curarg=internalvals[n];
                            foundvar=1;
                        }
                        if(!foundvar){
                          char * newval = getenv((*curarg)+1);
                          if(newval != NULL)
                            *curarg=newval;
                        }
                        //printf("displaying variable: %s\n",*curarg);

                    }

                    if(strstr(*curarg,"="))
                    {
                     // printf("assign\n");
                        int n;
                        char * var = strtok(*curarg,"=");
                        char * val = strtok(NULL,"=");
                        int found=0;

                        for( n=0;n<numinternalvars;n++)
                            if(strcmp(var,internalvars[n])==0){
                                strncpy(internalvals[n],val,100);
                                found=1;
                            }
                       if(found==0){
                           strcpy(internalvars[numinternalvars],var);
                           strcpy(internalvals[numinternalvars],val);                    
                           //printf("adding variable %i\n",numinternalvars);

                           numinternalvars++;
                           
                       }
//                     printf("assignment %s=%s\n",var,val);


                    }
}


void execute(struct CommandData * cdata,int command,int * lastfd)
{
        pid_t pid;
        int status;
        if ( cdata->TheCommands[command].numargs == 0)
                cdata->TheCommands[command].args[0]="";
        if ((pid = fork()) < 0) {     // fork a child process           
                printf("ERROR: forking child process failed");
                exit(1);
        }
        else if (pid == 0) {          // for the child process
                //if (arg_list[0] != NULL) {  
                char ** argv = cdata->TheCommands[command].args;
                int i;
                int argc=cdata->TheCommands[command].numargs;
        //      char * curarg;
            //argv[0]=cdata->TheCommands[command].command
            process_argument(&(cdata->TheCommands[command].command));
                //curarg=strtok(NULL," \t\n");
                
                
                for(i=0;i<argc;i++){
                    process_argument(argv+i);

                }
                if(strcmp( cdata->TheCommands[command].command , "cd")==0 )
                {
                    i=chdir(argv[0]);
                    return;
                }
                if(strcmp( cdata->TheCommands[command].command , "exit")==0 )
                {
                    exit(0);
                }
                if(command == 0) {
                        if( cdata->infile != NULL){
                                //printf("redir in\n");
                                int in;
                                close(0);
                                in=open(cdata->infile,O_RDONLY);
                                dup2(in,0);
                        }}else {
                                //printf("repipe in\n");

                                close(0);
                                dup2(lastfd[0],0);
                        }
                if(command == cdata->numcommands-1){
                        if(cdata->outfile != NULL){
        //                      printf("redir out\n");
                                int out;
                                out=open(cdata->outfile,O_WRONLY|O_CREAT|O_TRUNC,
                                65535// S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
                                 );
                                 close(1);
                                 dup2(out,1);
                        }}else {
                //              printf("repipe out\n");

                                close(1);
                                dup2(lastfd[1],1);
                        }
                if (executenonexternal(cdata->TheCommands[command].command, argv,argc) < 0) {     // execute the command  
                        printf("ERROR: exec failed");
                        exit(1);
                }
        }
        else {     


                char ** argv = cdata->TheCommands[command].args;
                int argc=cdata->TheCommands[command].numargs;
                int i;
                //char * curarg;
            process_argument(&(cdata->TheCommands[command].command));
                //curarg=strtok(NULL," \t\n");


                for(i=0;i<argc;i++){
                        process_argument(argv+i);
                }

                if(strcmp(argv[0],"export")==0)
                  {
                    int n;
                    for( n=0;n<numinternalvars;n++)
                      if(strcmp(internalvars[n],argv[1])==0){
                        //printf("exporting %s=%s\n",internalvars[n],internalvals[n]);
                        setenv(internalvars[n],internalvals[n],1);
                      }
                  }
        // if( command == cdata->numcommands-1)
        if(! cdata ->background)    {                        // for the parent:      
        while (wait(&status) != pid)       // wait for completion 
                ;
        if( command != cdata->numcommands-1) 
        close(lastfd[1]);}
        //close(lastfd[1]);
    }
}



int main(int argc, char *argv[])
{
        int i;
        int j;
        int fd[2] = {0,0},lfd[2] = {0,0},nfd[2] = {0,0};
        char * cc;
        int count=0;
        numinternalvars=0;
        extern char **environ;
        
        
        char cwd[LINE_MAX];
        char input[LINE_MAX];
        struct CommandData data;
        
        while(strncmp(input,"exit",4)!=0){
        if(getcwd(cwd,sizeof(cwd)) == NULL)
                perror("getcwd() error");
        else
                printf("%s > ",cwd); 
        cc=gets(input);
        i=(int)cc;
        ParseCommandLine(input, &data);
        
       /* printf("\nNumber of simple commands : %d\n",data.numcommands);
        
          printf("\ninfile = %s\toutfile = %s\n",
                        data.infile,
                        data.outfile);*/
        for(i = 0; i<data.numcommands;i++){
                if(i <data.numcommands-1){
                pipe(fd);
                lfd[0]=nfd[0];
                nfd[0]=fd[0];
                lfd[1]=fd[1];
                }
                else{
                  lfd[0]=nfd[0];
                }
          count=0;
                if(strcmp( data.TheCommands[i].command , "set")==0 ||
                   strcmp( data.TheCommands[i].command , "cd")==0 ||
                   strcmp( data.TheCommands[i].command , "exit")==0 ||
                   strcmp( data.TheCommands[i].command , "jobs")==0 ||
                   strcmp( data.TheCommands[i].command , "kill")==0 ||
                   strcmp( data.TheCommands[i].command , "fg")==0 ||
                   strcmp( data.TheCommands[i].command , "bg")==0 ||
                   strcmp( data.TheCommands[i].command , "pwd")==0 )
                        count++;
                
                //printf("command%d : %s\n",i+1,data.TheCommands[i].command);
       if(data.TheCommands[i].args[0]!=NULL)
                for(j = 0; j<data.TheCommands[i].numargs;j++)
                    // if we find an = we make thsi an assignment argument whos value is then replaced by the variable
                    //if this starts with $ we evaluate everythign after $
                   
                
                        printf("arg[%d] %s\n",j+1,data.TheCommands[i].args[j]);
                //}
                //if(count== 0 ){
                        execute(&data,i,lfd);
        //      }
        }//end for
        
         if(data.infile == NULL)
                    printf("Input file: NULL\n");
            else
                printf("Input file : %s\n",data.infile);
            if(data.outfile == NULL)
                    printf("Output file: NULL\n");
        else
                    printf("Output file : %s\n",data.outfile);
        if(data.background == 0)
                printf("Background option : OFF\n");
        else
                printf("Background option : ON\n");
                
        if(count==0)
                printf("Built-in command  : OFF\n");
        else
                printf("Built-in command  : NO\n");
                        
                printf("\n");
              
        if(strcmp(input, "set")==0){
            for(i = 0;environ[i]!=NULL;i++ ){
                printf("%s\n",environ[i]);
            }
            printf("showing all %i variables\n",numinternalvars);
            for(i = 0;i<numinternalvars;i++ ){
                printf("internal %s=%s\n",internalvars[i],internalvals[i]);

            }
        } //*/
        //if(count == 0 )       
//        if(strlen(input)>0)
//              execute(input);
        }

    exit(0);
}




//this was my idea