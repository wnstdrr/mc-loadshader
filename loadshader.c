#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shadercache.h"
#include "util.h"

// function definition for loadshader function
extern bool loadshader(const char *file);
extern bool shadercache(const char *shadername);
extern bool removeshader(const char *shadername);
extern void listshaders(void);
extern int installedsize(void);
extern char *path_dst(void);

const char help_msg[] = "loadshader.c [OPTION]... [FILE]...\n "
                        "-h  --help\tDisplay this help message\n "
                        "-a  --authors\tShader authors\n "
                        "-r  --remove\tRemove Shader\n "
                        "-f  --file\tLoad shader from file\n "
                        "-i  --installed\tList installed shaders\n "
                        "-c  --cache\tLoad shader from program cache\n "
                        "-l  --list\tList shader cache\n";

//TODO: generate authors automatically, this will do for now.
const char authors[] = "Shader authors\n "
                       " BSL_v8.1.03              (https://minecraftshader.com/bsl-shaders)                         ->  @ capttatsu\n "
                       " CompShaders_v4.5         (https://minecraftshader.com/complementary-shaders)               ->  @ EminGTR\n "
                       " SEUSRenewed_v1.0.1       (https://minecraftshader.com/sonic-ethers-unbelievable-shaders)   ->  @ Sonic Ether\n "
                       " LaglessShaders_v1.10.2   (https://minecraftshader.com/lagless-shaders/)                    ->  @ unknown\n "
                       " DrDestensShaders_v1.5.7  (https://minecraftshader.com/drdestens-shaders/)                  ->  @ DrDestens\n "
                       " TrilitonShaders_v8       (https://minecraftshader.com/triliton-shaders/)                   ->  @ Triliton\n";

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("%s", help_msg);
        return EXIT_SUCCESS;
    }
    // iterate through command line arguments
    register int size;
    bool load_status;
    for (size = 1; size < argc; size++) {
        if ((strcmp(argv[size], "-f")) == 0 ||
            strcmp(argv[size], "--file") == 0) {
            for (int i = size + 1; i < argc; i++) {
                load_status = loadshader(argv[i]);
                printf("Shader %s Loaded? %s\n", argv[i],
                       loadstatus(load_status));
                exit(EXIT_SUCCESS);
            }

        } else if (strcmp(argv[size], "-a") == 0 || strcmp(argv[size], "--authors") == 0) {
           printf("%s", authors);
           exit(EXIT_SUCCESS);
        } else if ((strcmp(argv[size], "-h") == 0) ||
                   strcmp(argv[size], "--help") == 0) {
            printf("%s", help_msg);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[size], "-i") == 0 || strcmp(argv[size], "--installed") == 0) {
            printf("Installed shaders: (%d)\n", installedsize());
            listshaders();
            exit(EXIT_SUCCESS);
        } else if ((strcmp(argv[size], "-r") == 0) ||
                   strcmp(argv[size], "--remove") == 0) {
            removeshader(argv[size + 1]);
            printf("Removed shader %s\n", argv[size + 1]);
            exit(EXIT_SUCCESS);
        }

        else if ((strcmp(argv[size], "-c") == 0) ||
                 strcmp(argv[size], "--cache") == 0) {
            // load shader cache stored in bin directory
            for (int i = size + 1; i < argc; i++) {
                for (long unsigned int j = 0;
                     j < shadersize(shaders, InternalName); j++) {
                    if (strcmp(argv[size + 1], shaders[j][InternalName]) == 0) {
                        load_status = shadercache(shaders[j][InternalName]);
                        printf("Shader %s Loaded (cache)? %s\n",
                               shaders[j][InternalName],
                               loadstatus(load_status));
                        exit(EXIT_SUCCESS);
                    } else {
                        continue;
                    }
                }
            }
        } else if (strcmp(argv[size], "-l") == 0 ||
                   strcmp(argv[size], "--list") == 0) {
            // list the shader cache options within the shaders directory
            long unsigned int i;
            printf("%s (%ld)\n", "Shader cache options:",
                   shadersize(shaders, ShaderCacheName));
            for (i = 0; i < shadersize(shaders, InternalName);
                 i++) {
                printf("  %-25s ->  %s\n", shaders[i][InternalName],
                       shaders[i][ShaderCacheName]);
            }
            exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}

bool loadshader(const char *file) {
    // Create a clone of the file and store in a buffer
    FILE *stream = fopen(file, "rb");
    loadfail(stream);

    // obtain file size and create a fixed buffer
    int file_size = fsize(stream);
    char content[file_size + 1];

    // read content into buffer and close stream
    fread(&content, file_size + 1, 1, stream);
    pclose(stream);
    // create a new file stream for writing
    char *path = (char *)malloc(sizeof(char) * PATH_MAX);

    // copy path into space
    int file_len = strlen(file) + 1;

    strncpy(path, "/home/", 7);
    strncat(path, getlogin(), PATH_MAX - strlen(getlogin()) + 1);
    strncat(path, "/.minecraft/shaderpacks/", 25);
    strncat(path, file, PATH_MAX - file_len);
    printf("%s\n", path);

    // open and create the new file to be written
    creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    FILE *stream_w = fopen(path, "wb");
    loadfail(stream_w);

    // write the content to the new file
    fwrite(&content, file_size, 1, stream_w);
    pclose(stream_w);
    free(path);
    return true;
}

bool shadercache(const char *shadername) {
    // load shader from the cache directory
    char *path = (char *)malloc(sizeof(char) * PATH_MAX);
    char *path_dst = (char *)malloc(sizeof(char) * PATH_MAX);
    strncpy(path, "shaders/", 9);

    strncpy(path_dst, "/home/", 7);
    strncat(path_dst, getlogin(), PATH_MAX - strlen(getlogin()) + 1);
    strncat(path_dst, "/.minecraft/shaderpacks/", 25);

    int file_len = strlen(shadername) + 1;
    for (unsigned long int i = 0; i < shadersize(shaders, InternalName);
         i++) {
        if (strcmp(shadername, shaders[i][InternalName]) == 0) {
            strncat(path, shaders[i][ShaderCacheName],
                    PATH_MAX - strlen(shaders[i][ShaderCacheName]) + 1);
            strncat(path_dst, shaders[i][ShaderCacheName], PATH_MAX - file_len);
        }
    }
    printf("%s\n", path_dst);
    FILE *stream = fopen(path, "rb");
    loadfail(stream);

    int file_size = fsize(stream);
    char content[file_size + 1];

    fread(&content, file_size + 1, 1, stream);
    pclose(stream);

    creat(path_dst, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    FILE *stream_w = fopen(path_dst, "wb");
    loadfail(stream_w);

    fwrite(&content, file_size, 1, stream_w);
    pclose(stream_w);

    free(path);
    free(path_dst);
    return true;
}

bool removeshader(const char *shadername) {
    char *path = path_dst();

    for (unsigned long int i = 0;
         i < shadersize(shaders, InternalName); i++) {
        if (strcmp(shadername, shaders[i][InternalName]) == 0) {
            strncat(path, shaders[i][ShaderCacheName],
                    PATH_MAX - strlen(shaders[i][ShaderCacheName]));
        } else {
            continue;
        }
        printf("%s\n", path);
        if (remove(path) != 0) {
            printf("Failed to remove shader %s\n", shadername);
            exit(EXIT_FAILURE);
        }
    }
    free(path);
    return true;
}

char *path_dst(void) {
    char *path_dst = (char *)malloc(sizeof(char) * PATH_MAX);

    strncpy(path_dst, "/home/", 7);
    strncat(path_dst, getlogin(), PATH_MAX - strlen(getlogin()) + 1);
    strncat(path_dst, "/.minecraft/shaderpacks/", 25);
    return path_dst;
}

void listshaders(void) {
    DIR *d;
    struct dirent *e;
    char *path = path_dst();
    d = opendir(path);
    while ((e = readdir(d)) != NULL) {
        if (strcmp(e -> d_name, ".") == 0 || strcmp(e -> d_name, "..") == 0) {
            continue;
        } else {
            printf("  %s\n", e -> d_name);
        }
    }
    closedir(d);
    free(path);
}

int installedsize(void) {
    DIR *d;
    struct dirent *e;
    char *path = path_dst();
    d = opendir(path);
    
    register int i = 0;
    while ((e = readdir(d)) != NULL) {
        if (strcmp(e -> d_name, ".") == 0 || strcmp(e -> d_name, "..") == 0) {
            continue;
        } else {
            i++;
        }
    }
    free(path);
    return i;
}
