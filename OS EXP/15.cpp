#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES_PER_DIR 100
#define MAX_DIRS 100

struct File {
    char name[50];
    int size;
};

struct Directory {
    char name[50];
    struct File files[MAX_FILES_PER_DIR];
    int file_count;
};

struct TwoLevelDir {
    struct Directory dirs[MAX_DIRS];
    int dir_count;
};

void addDirectory(struct TwoLevelDir *dir, char *dir_name) {
    if (dir->dir_count < MAX_DIRS) {
        strcpy(dir->dirs[dir->dir_count].name, dir_name);
        dir->dirs[dir->dir_count].file_count = 0;
        dir->dir_count++;
        printf("Directory '%s' created\n", dir_name);
    } else {
        printf("Maximum number of directories reached\n");
    }
}

void addFile(struct TwoLevelDir *dir, char *dir_name, char *file_name, int size) {
    int i, found = 0;
    for (i = 0; i < dir->dir_count; i++) {
        if (strcmp(dir->dirs[i].name, dir_name) == 0) {
            if (dir->dirs[i].file_count < MAX_FILES_PER_DIR) {
                struct File new_file;
                strcpy(new_file.name, file_name);
                new_file.size = size;
                dir->dirs[i].files[dir->dirs[i].file_count++] = new_file;
                printf("File '%s' added to directory '%s'\n", file_name, dir_name);
            } else {
                printf("Directory '%s' is full, cannot add more files\n", dir_name);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Directory '%s' not found, creating it now...\n", dir_name);
        addDirectory(dir, dir_name);
        addFile(dir, dir_name, file_name, size);
    }
}

void displayContents(struct TwoLevelDir *dir) {
    int i, j;
    for (i = 0; i < dir->dir_count; i++) {
        printf("Directory: %s\n", dir->dirs[i].name);
        printf("Files:\n");
        for (j = 0; j < dir->dirs[i].file_count; j++) {
            printf(" %s - Size: %d\n", dir->dirs[i].files[j].name, dir->dirs[i].files[j].size);
        }
    }
}

int main() {
    struct TwoLevelDir root_dir;
    root_dir.dir_count = 0;

    // Adding directories before adding files
    addDirectory(&root_dir, "Documents");
    addDirectory(&root_dir, "Images");

    addFile(&root_dir, "Documents", "Report.docx", 2048);
    addFile(&root_dir, "Documents", "Presentation.pptx", 4096);
    addFile(&root_dir, "Images", "Photo1.jpg", 1024);

    displayContents(&root_dir);
    return 0;
}

