#include "../drivers/screen.h"
#include "../libc/types/hashtable.h"
#include "../libc/string.h"
#include "shell.h"

#define HELP  1
#define CLEAR 2
#define ECHO  3
#define ADD   4
#define MULT  5
#define HALT  6

static hashtable_t *lookup_table;
static char *sections[3]; 

void shell_init()
{
    clear_screen();

    sections[0] = "CLEAR\n   -Clear the screen\n"
        "ECHO [message]\n   -Echos a message to the screen";
    // TODO: Filesystem
    sections[1] = "LIST\n   -List files in current directory\n"
        "READ [file]\n   -Print contents of a file to the screen";
    sections[2] = "ADD [num1] [num2]\n   -Add two numbers together\n"
        "MULT [num1] [num2]\n    -Multiply two numbers together";

    lookup_table = table_create(10);
    table_add(lookup_table, "HELP", HELP);
    table_add(lookup_table, "CLEAR", CLEAR);
    table_add(lookup_table, "ECHO", ECHO);
    table_add(lookup_table, "ADD", ADD);
    table_add(lookup_table, "MULT", MULT);
    table_add(lookup_table, "HALT", HALT);
}

void print_help(int argc, char **args)
{
    if (argc > 1) {
        int section = atoi(args[1]) - 1;
        if ((unsigned) section > sizeof(sections) / sizeof(char*)) {
            kprint("Invalid section!");
        }
        else
        {
            kprint("-----Section Reference-----\n");
            kprint(sections[section]);
        }
    }
    else
    {
        kprint("-----Thunder-OS Command Reference-----\n"
               "HELP <section>\n"
               "   -Retrieve either a command list or general information regarding a command\n\n"
               "-----Sections-----\n"
               "1) Shell Management\n"
               "2) File I/O\n"
               "3) General Thunder-ness");
    }
}

void echo(int argc, char **args)
{
    for (int i = 1; i < argc; i++)
    {
        kprint(args[i]);
        kprint(" ");
    }
}

void add(int argc, char **args) {
    if (argc >= 3) {
        char *exp = kmalloc(64);
        strcat(exp, args[1][0]);
        strcat(exp, '+');
        strcat(exp, args[2][0]);
        strcat(exp, '=');
        kprint(exp);

        int sum = atoi(args[1]) + atoi(args[2]);
        char out[64];
        itoa(sum, out);
        kprint(out);
    } else {
        kprint("Malformed command!");
    }
}


void mult(int argc, char **args) {
    if (argc >= 3) {
        char *exp = kmalloc(64);
        strcat(exp, args[1][0]);
        strcat(exp, '*');
        strcat(exp, args[2][0]);
        strcat(exp, '=');
        kprint(exp);

        int sum = atoi(args[1]) * atoi(args[2]);
        char out[64];
        itoa(sum, out);
        kprint(out);
    } else {
        kprint("Malformed command!");
    }
}

void shell_command(char* command)
{
    char **args = split(command, ' ');
    int argc = 1;
    for(int i = 0; command[i]; i++)
        if(command[i] == ' ')
            argc++;

    switch (table_find(lookup_table, args[0]))
    {
        case HELP:
            print_help(argc, args);
            break;
        case CLEAR:
            clear_screen();
            break;
        case ECHO:
            echo(argc, args);
            break;
        case ADD:
            add(argc, args);
            break;
        case MULT:
            mult(argc, args);
            break;
        case HALT:
            kprint("Halting CPU!");
            asm volatile("hlt");
            break;
        default:
            kprint("Unkown Command! Type HELP for more information");
    }
    
    kprint("\nThunder-OS> ");
}

