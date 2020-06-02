#include <stdio.h>
#include <dirent.h>
#include <string.h>

typedef struct namefiles {
    char names[3000][100];
    char paths_names[3000][100];
    int count_names;
    char try_paths[3000][100];
    int count_try_paths;
} namefiles;

int search(namefiles *nf, char *name_for_search) {
    int i =0;
    for (i = 0; i < nf->count_names; ++i) {
        if (!strcmp(nf->names[i], name_for_search)) {
            return i;
        }
    }
    return -1;
}

int open_file(namefiles *nf, int num) {
    char path[100];

    strcpy(path, nf->paths_names[num]);
    strcat(path, "/");
    strcat(path, nf->names[num]);

    char str[100];
    FILE *f = fopen(path, "r");

    while (fgets(str, 9, f)) {
        if (!strcmp(str, "Deadlock")) {
            return 0;
        } else if (!strcmp(str, "Minotaur")) {
            return 1;
        } else {
            fgets(str,2,f);
            fgets(str,100,f);
            if(str[strlen(str)-1]=='\n'){
                str[strlen(str)-1]='\0';
            }
            num = search(nf,str);
            if(open_file(nf,num)){
                strcpy(path, nf->paths_names[num]);
                strcat(path, "/");
                strcat(path, nf->names[num]);
                strcpy(nf->try_paths[nf->count_try_paths],path);
                nf->count_try_paths++;
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}


int list_dir(const char *try_path, namefiles *nf) {
    char path[1000];
    strcpy(path, try_path);
    DIR *dir = opendir(path);
    if (!dir) return 1;
    struct dirent *de = readdir(dir);
    while (de) {
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 &&
            strcmp(de->d_name, "..") != 0) {
            int len = strlen(path);
            strcat(path, "/");
            strcat(path, de->d_name);
            list_dir(path, nf);
            path[len] = '\0';
        }
        if (de->d_type == DT_REG) {
            strcpy(nf->names[nf->count_names], de->d_name);
            strcpy(nf->paths_names[nf->count_names], path);
            nf->count_names++;
        }
        de = readdir(dir);
    }
    closedir(dir);
    return 0;
}

int make(char* dir,namefiles *nf){
    int num = 0;
    if(!list_dir(dir, nf)) {
        char *name_for_search = "file.txt";
        char path[100];
        num = search(nf, name_for_search);
        strcpy(path, nf->paths_names[num]);
        strcat(path, "/");
        strcat(path, nf->names[num]);
        strcpy(nf->try_paths[nf->count_try_paths], path);
        nf->count_try_paths++;
        FILE *f=fopen("./result.txt","w");
        if (open_file(nf, num)) {
            fputs(nf->try_paths[0],f);
            int i=0;
            for (i = nf->count_try_paths; i > 0; --i) {
                fputs(nf->try_paths[i],f);
                fputs("\n",f);
            }
        }
    }
}


int main() {
    char *dir = "./labyrinth";
    
    namefiles nf;
    nf.count_names = 0;
    nf.count_try_paths=0;

    make(dir,&nf);
    return 0;
}
