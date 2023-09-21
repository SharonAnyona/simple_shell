#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*This is for command chaining */
#define CMD_AND         2
#define CMD_CHAIN       3
#define CMD_NORM        0
#define CMD_OR          1

/* This is for read/write buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/*return  1 when using system getline() function*/
#define USE_STRTOK 0
#define USE_GETLINE 0

/*This is  for convert_number() function*/
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


extern char **environ;

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


/**
 * struct liststr - for singly linked list
 * @num: for the field number
 * @str: is a string
 * @next: where next node is pointed to
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - has pseudo-arguements that are passed into a function,
 *		granting uniform prototype for function pointer struct
 *@arg: has getline containing arguments where a string is generated from
 *@argv: arg generated array of strings 
 *@path: current command string path
 *@env: local copy environ linked list
 *@environ:env LL custom modified copy
 *@history: node history
 *@alias: node alias
 *@env_changed: when on it indicates that environ was changed
 *@status:the last  exec'd command return status
 *@argc: count argument
 *@line_count: count error
 *@err_num: exic()s error code
 *@linecount_flag: when on then count this line of input
 *@fname: filename program
 *@cmd_buf: pointer address to cmd_buf, if chaining its on
 *@cmd_buf_type: &&, ; || CMD_type
 *@readfd: line input is read from this fd
 *@histcount: line history of number count
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 *struct builtin - has related function and builtin string 
 *@func: function
 *@type: command flag of builtin
 */


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /*cmd pointer ;buffer chain , for managing the memory*/
	int cmd_buf_type; /* CMD_type &&, ||, ; */
	int readfd;
	int histcount;
} info_t;


/* toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);


/* toem_history.c */
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);


/* toem_lists.c */
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* toem_lists1.c */
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);

/* toem_environ.c */
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);

/* toem_getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* toem_errors1.c */
int print_d(int, int);
char *convert_number(long int, int, int);
int _erratoi(char *);
void print_error(info_t *, char *);
void remove_comments(char *);

/* toem_atoi.c */
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);

/* toem_memory.c */
int bfree(void **);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_parser.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* toem_string1.c */
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);

/* toem_string.c */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);

/* toem_errors.c */
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);

/* loophsh.c */
int loophsh(char **);

int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);

#endif
