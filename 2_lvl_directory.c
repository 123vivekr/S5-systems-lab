#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 100

typedef struct file {
    char *name;
    struct file *next;
} file;

typedef struct dir {
    char *name;
    int n_files;
    file *files;
    struct dir *next;
} dir;

typedef struct maindir {
    char *name;
    int n_dir;
    dir *dir;
    struct maindir *next;
} maindir;

maindir *start = NULL;

int main(void) {
    int hld;
    printf("Enter number of high level directory: ");
    scanf("%d", &hld);
    for(int i = 0; i < hld; ++i) {
        maindir *ptr = (maindir*) malloc(sizeof(maindir));
        ptr->next = NULL;
        ptr->name = (char*) malloc(sizeof(char) * MAX_NAME);
        if(start == NULL)
            start = ptr;
        else {
            maindir *temp = start;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = ptr;
        }
        printf("Enter HLD %d name: ", i + 1);
        scanf("%s", ptr->name);
        printf("Enter number of HLD %d sub-directory(s): ", i + 1);
        scanf("%d", &ptr->n_dir);
        ptr->dir = NULL;
        for(int j = 0; j < ptr->n_dir; ++j) {
            dir *ptrsub = (dir*) malloc(sizeof(dir));
            ptrsub->next = NULL;
            ptrsub->name = (char*) malloc(sizeof(char) * MAX_NAME);
            if(ptr->dir == NULL)
                ptr->dir = ptrsub;
            else {
                dir *tempsub = ptr->dir;
                while(tempsub->next != NULL)
                    tempsub = tempsub->next;
                tempsub->next = ptrsub;
            }
            printf("Name of sub-directory %d: ", j+1);
            scanf("%s", ptrsub->name);
            printf("Number of files in sub-directory %d: ", i+1);
            scanf("%d", &ptrsub->n_files);
            for(int k = 0; k < ptrsub->n_files; ++k) {
                file *fileptr = (file*) malloc(sizeof(file));
                fileptr->next = NULL;
                fileptr->name = (char*) malloc(sizeof(char) * MAX_NAME);
                if(ptrsub ->files == NULL)
                    ptrsub->files = fileptr;
                else {
                    file *tempfile = ptrsub->files;
                    while(tempfile->next != NULL)
                        tempfile = tempfile->next;
                    tempfile->next = fileptr;
                }
                printf("Name of file %d: ", k+1);
                scanf("%s", fileptr->name);
            }
        }
    }

    maindir *ptr = start;
    for(maindir *ptr = start; ptr != NULL; ptr = ptr->next) {
        printf("%s:\n", ptr->name);
        for(dir *subptr = ptr->dir; subptr != NULL; subptr = subptr->next) {
            printf("\t%s:\n", subptr->name);
            printf("\t\t");
            for(file* fileptr = subptr->files; fileptr != NULL; fileptr = fileptr->next)
                printf("%s ", fileptr->name);
            printf("\n");
        }
    }
    return 0;
}
