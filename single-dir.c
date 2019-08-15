#include <stdio.h>
#include <stdlib.h>

typedef struct File {
    int fno;
    char *name;
    int size;
} fileent;

typedef struct Directory {
    // inode
    int dno;
    // directory name
    char *name;
    // number of files in directory
    int n_files;
    // file pointers
    fileent* files;
} dirent;

typedef struct DirList {
    dirent dir;
    struct dirlist *next;
} dirlist;

int main(void)
{
    dirlist *start = NULL;
    int op = 1;
    int c = 0; // directory counter
    while(op != 0) {
        printf("0. Exit\n");
        printf("1. New directory\n");
        printf("Choose option: ");
        scanf("%d", &op);
        switch(op) {
            case 0:
                break;

            case 1:
                printf("\nName: ");
                dirlist *new = (dirlist*) malloc(sizeof(dirlist));
                new->next = NULL;
                new->dir.dno = c++;
                new->dir.name = (char*) malloc(sizeof(char) * 20);
                scanf("%s", new->dir.name);
                printf("\nNumber of files: ");
                scanf("%d", &new->dir.n_files);
                new->dir.files = (fileent*) malloc(sizeof(fileent) * new->dir.n_files);
                int cf = 0; // file coounter
                for(int i = 0; i < new->dir.n_files; ++i) {
                    new->dir.files[i].fno = cf++;
                    printf("\nEnter file %d name: ", i+1);
                    new->dir.files[i].name = (char*) malloc(sizeof(char) * 20);
                    scanf("%s", new->dir.files[i].name);
                    printf("\nEnter file %d size: ", i+1);
                    scanf("%d", &new->dir.files[i].size);
                }

                if(start == NULL)
                    start = new;
                else {
                    dirlist *ptr = start;
                    while(ptr->next != NULL)
                        ptr = ptr->next;
                    ptr->next = new;
                }
                break;

            default:
                printf("\nInvalid option\n");
        }
    }

    printf("\n-----------------------------------\n");
    printf("Directory structure: single level\n");
    dirlist *ptr = start;
    while(ptr != NULL) {
        printf("%s: \n", ptr->dir.name);
        for(int i = 0; i < ptr->dir.n_files; ++i) {
            printf("\t %s: %d", ptr->dir.files[i].name, ptr->dir.files[i].size);
        }
        printf("\n");
        ptr = ptr->next;
    }
    return 0;
}
