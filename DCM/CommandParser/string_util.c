/*
 * =====================================================================================
 *
 *       Filename:  string_util.c
 *
 *    Description:  String utilities
 *
 *        Version:  1.0
 *        Created:  Thursday 03 August 2017 05:35:37  IST
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Networking Developer (AS), sachinites@gmail.com
 *        Company:  Brocade Communications(Jul 2012- Mar 2016), Current : Juniper Networks(Apr 2017 - Present)
 *
 * =====================================================================================
 */

#include "string_util.h"
#include <stdlib.h>
#include <assert.h>
#include "cliconst.h"
#include <ctype.h>
#include <stdio.h>

static char a_str[CONS_INPUT_BUFFER_SIZE];

static char * tokens[MAX_CMD_TREE_DEPTH];

void
init_token_array(){

    int i = 0;
    for(; i < MAX_CMD_TREE_DEPTH; i++){
        tokens[i] = calloc(1, LEAF_VALUE_HOLDER_SIZE);
    }
}

void
re_init_tokens(int token_cnt){
    
    int i = 0;
    for(; i < token_cnt; i++){
        memset(tokens[i], 0, LEAF_VALUE_HOLDER_SIZE);
    }
}

char** str_split2(char* _a_str, const char a_delim, size_t *token_cnt){
   
    char *token = NULL;
    int i = 0;

    memset(a_str, 0, CONS_INPUT_BUFFER_SIZE);
    memcpy(a_str, _a_str, strlen(_a_str));

    string_space_trim(a_str);

    if(strlen(a_str) < 1){
        *token_cnt = 0;
        return NULL;
    }

    token = strtok(a_str, &a_delim);
    if(token){
        strncpy(tokens[i], token, strlen(token));
        i++;
    }
    else{
        *token_cnt = 0;
        return NULL;
    }
    
    /* walk through other tokens */
    while( token != NULL ) 
    {
        token = strtok(NULL, &a_delim);
        if(token){
            strncpy(tokens[i], token, strlen(token));
            i++;
        }
    } 

    *token_cnt = i;
    return &tokens[0];
}

void
string_space_trim(char *string){

    if(!string)
        return;

    char* ptr = string;
    int len = strlen(ptr);

    if(!len){
        return;
    }

    if(!isspace(ptr[0]) && !isspace(ptr[len-1])){
        return;
    }

    while(len-1 > 0 && isspace(ptr[len-1])){
        ptr[--len] = 0;
    }

    while(*ptr && isspace(*ptr)){
        ++ptr, --len;
    }

    memmove(string, ptr, len + 1);
}


void
print_tokens(char **tokens){
    int i = 0;
    for ( ;*(tokens + i); i++)
    {
        printf("%d. %s\n", i, (*(tokens + i)));
    }
    free(tokens);
}
