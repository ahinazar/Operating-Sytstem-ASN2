#include "types.h"
#include "user.h"
#include "mmu.h"

char* arr[15];
char input[100];

void test_1_1(){
    for(int i=0; i<10; i++) {
        void *tmp = pmalloc();
        if (tmp == 0)
            printf(1, "ERROR - pmalloc returned null.\n");
        int protected_tmp = protect_page(tmp);
        if (protected_tmp == -1)
            printf(1, "ERROR - protect_page returned error.\n");
        int pfree_tmp = pfree(tmp);
        if (pfree_tmp == -1)
            printf(1, "ERROR - pfree returned error.\n");
    }

//// RUN IT ONLY IF NEED TO CHECK PROTECT FLAG IN PFREE
//    for(int i=0; i<10; i++) {
//        void *tmp = pmalloc();
//        if (tmp == 0)
//            printf(1, "ERROR - pmalloc returned null.\n");
//        int pfree_tmp = pfree(tmp);
//        if (pfree_tmp == 1)
//            printf(1, "ERROR - pfree returned error.\n");
//    }
}

void test_1_2(){
    int* pmalloc_arr[5];
    int* malloc_arr[5];

    for(int j=0; j<5;j++){
        pmalloc_arr[j] = (int*)pmalloc();
        malloc_arr[j] = (int*)malloc(sizeof(int));
        *pmalloc_arr[j] = *malloc_arr[j] = j*j;

        protect_page(pmalloc_arr[j]);
    }

    for(int i=0; i<5;i++){
        if(!(*pmalloc_arr[i]==i*i)){
            printf(1,"ERROR -- went wrong at pmalloc_arr=%d i=%d\n",*pmalloc_arr[i],i);
        }else if( !(*malloc_arr[i] == i*i)) {
            printf(1,"ERROR -- went wrong at malloc_arr i=%d\n",i);
        }
    }

    for(int i=0; i<5;i++){
        pfree(pmalloc_arr[i]);
        free(malloc_arr[i]);
    }

}

void test_for_none(){
    printf(1, "NONE policy.\nStarting the test...\n");
    for (int i = 0; i < 1000; i++){
        malloc(PGSIZE);
    }
    printf(1, "1000 sbrk operations has been made\nPlease check statistics. When your'e done, please enter some input to proceed.\n");
    gets(input, 100);

    printf(1, "Test passed if you didn't get error messages.\n");
}

void test_2_and_on() {
    for (int i = 0; i < 12; ++i) {
        arr[i] = sbrk(PGSIZE);
    }

    arr[12] = malloc(PGSIZE);
    arr[13] = malloc(PGSIZE);
    printf(1, "18 pages allocated (4 from exec and 14 with sbrk func that we did), THERE WILL BE PAGE FAULT NOW.\nPlease check statistics. When your'e done, please enter some input to proceed.\n");
    gets(input,100);

    if (fork() == 0) {
        printf(1, "FORK OPERATION HAS BEEN MADE. YOU ARE IN CHILD PROCESS.\n");
        printf(1, "Please check statistics. When your'e done, please enter some input to proceed.\n");
        gets(input, 100);
        arr[14] = malloc(PGSIZE);
        exit();
    }
    else {
        wait();
        printf(1, "YOU ARE IN FATHER PROCESS\n");
    }

    printf(1, "Test passed if you didn't get ERROR messages.\n");
}

int main(int argc, char *argv[]){
    printf(1,"Start testing Task 1...\n");

    test_1_1();
    test_1_2();

    printf(1, "Test for task 1 is finished.\nTest for task 2 and on is now running...\n");

#if SCFIFO
    printf(1, "SCFIFO policy.\nStarting the test...\n");
	test_2_and_on();
#endif

#if LIFO
    printf(1, "LIFO policy.\nStarting the test...\n");
	test_2_and_on();
#endif

#if NONE
    test_for_none();
#endif

    exit();
}