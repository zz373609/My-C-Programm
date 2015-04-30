/*
 * Headstart for Assignment 2
 * CS 4420/5420
 * 
 * Student Name:
 * 

 * 
 * 
 * 
 * 
 */


#include <stdio.h>
#include <string.h> /* for strdup */
#include "parser.h"

static int IsAlphaNum(char c)  /* is this a valid char for a pathname or filename? */
{
  if (c >= 'A' && c <= 'Z') return 1;
  if (c >= 'a' && c <= 'z') return 1;
  if (c >= '0' && c <= '9') return 1;
  if (c == '.' || c == '_' || c == '/' ||c == '\\'||c == '\"'|| c == '-' || c  == '=' || c == '$') return 1;
  return 0;
}


/************** COPYWORD **************
  This function copies a word (token) to the appropriate field
  of the struct CommandData data, and resets state. It
  returns 1 if successful, 0 if it detects an error.
  This is called from the function ParseCommandLine
**************************************************/
static int CopyWord(char *token, struct CommandData *data, int *state)
{
    switch (*state) {
        case COMMAND: 
             data->TheCommands[data->numcommands].command = strdup(token);
             data->TheCommands[data->numcommands].numargs = 0;
             *state = ARG;
             return 1;
        case ARG: 
             data->TheCommands[data->numcommands].args[data->TheCommands[data->numcommands].numargs] = strdup(token);
             /* this is one of the ugliest lines of code that I have ever written */
             data->TheCommands[data->numcommands].numargs++;
             if (data->TheCommands[data->numcommands].numargs > 10) {
		 fprintf(stderr,"Error, too many arguments\n");
                 return 0;
	      }
              return 1;
        case INFILE: 
             if (data->infile != NULL) {
                 fprintf(stderr,"Error, stdin redirected twice\n");
                 return 0;
	     }
	     data->infile = strdup(token);
             *state = UNDEF;
             return 1;
        case OUTFILE: 
             if (data->outfile != NULL) {
                 fprintf(stderr,"Error, stdout is redirected twice\n");
                 return 0;
	     }
	     data->outfile = strdup(token);
             *state = UNDEF;
             return 1; 
         case UNDEF:
             fprintf(stderr,"Error, bad syntax on the command line\n");
             return 0;
    };
    /* we should never get here */
    fprintf(stderr,"Error in CopyWord\n");
    return 0;
}

/********* PARSECOMMANDLINE ***********************************
   This function parses the commandline line, and populates
   the struct CommandData data.  

   Returns 1 if it successfully parsed the command line,
   Returns 0 if it found an error 

   Logic - it passes through the while loop once for each character
   in the line.
   It copies string names into token, and when it gets to the end,
   it calls CopyWord to copy token to the appropriate field in data based on the
   state.   White spaces are ignored, the < and > characters change
   the state, & sets the background flag to 1.
*************************************************************/
int ParseCommandLine(char *line, struct CommandData *data)
{
    int i, j;
    char token[256];
    int inaword;
    int state;

    i=0;
    j=0;
    inaword = 0;
    state = COMMAND;
    data->numcommands = 0;
    data->TheCommands[0].command=NULL;
    data->infile = data->outfile = NULL;
    data->background = 0;

    while (line[i] != '\0' && line[i] != '\n') {
        if (IsAlphaNum(line[i])) {
            if (inaword) {
	        token[j++]=line[i];
            }
            else { /* starting a new word */
	        j = 0;
                token[j++] = line[i];
                inaword = 1;
            }
        }
        else {  /* not an alphanumeric character */
            if (inaword) { /* we have found the end of a token */
	        token[j]='\0';
                inaword = 0;
                if (CopyWord(token,data,&state)==0)
	             return 0;
	     }
                     
            switch (line[i]) {
                case ' ': 
                    break;
	        case '>': 
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
	            }
                    state = OUTFILE;
	            break;
                case '<': 
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
	            }
                    state = INFILE;
	            break;
	        case '|':
                  if (state == COMMAND || state == INFILE || state == OUTFILE) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");
                        return 0;
	            }
		  data->numcommands++;
                  state = COMMAND;
                  data->TheCommands[data->numcommands].command = NULL;
                  data->TheCommands[data->numcommands].numargs = 0;
                  break;
                   
                case '&': 
                    if (state == OUTFILE || state == INFILE || state == COMMAND) {
                        fprintf(stderr, "Error, bad syntax on the command line\n");    
                        return 0;
	            }
                    data->background = 1;
                    break;
                default : 
                    fprintf(stderr,"Error, invalid character on command line %c\n",line[i]);
                    return 0;
            }; /* end of switch */
        } /* end of else */
        i++;
    } /* end of while loop */
    /* we have gotten to the end of the line, there may still be a
       string that has not been processed */

    if (inaword) {
        token[j]='\0';
        if (CopyWord(token,data,&state)==0) {
            return 0;
	}
    }

    /* do some final error checking */
    if (state == INFILE && data->infile == NULL) {
        fprintf(stderr,"Error, < but no filename\n");
        return 0;
    }
    if (state == OUTFILE && data->outfile == NULL) {
        fprintf(stderr,"Error, > but no filename\n");
        return 0;
    }
    if (state == COMMAND) {
      fprintf(stderr,"Error, bad syntax on command line\n");
      return 0;
    }
      
    if (data->TheCommands[0].command == NULL) {
        fprintf(stderr, "Error, no command\n");
        return 0;
    }
    data->numcommands++;
    return 1;
}



       
  


