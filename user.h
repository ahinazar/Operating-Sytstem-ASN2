struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int yield(void);
// ********** CHANGED 1 START **********
void created_by_pmalloc(void* p);
int set_pte_w_off(void* p);
void turn_on_w(void* p);
int is_pte_w_on(void* p, int* is_created_by_pmalloc);
// ********** CHANGED 1 END **********

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
// ********** CHANGED 1 START **********
void* pmalloc();
int protect_page(void* ap);
int pfree(void* p);
int return_pmalloed_pages();
// ********** CHANGED 1 END **********
