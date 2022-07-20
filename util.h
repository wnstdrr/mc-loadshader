#ifndef _UTIL_H
#define _UTIL_H

#include<stdlib.h>
#include<stdbool.h>
#define fsize(f)                                                               \
    ({                                                                         \
        int size;                                                              \
        fseek(f, 0L, SEEK_END);                                                \
        size = ftell(f);                                                       \
        rewind(f);                                                             \
        size;                                                                  \
    })
#define loadfail(f)                                                            \
    ({                                                                         \
        if (f != NULL) {                                                       \
            ;                                                                  \
        } else {                                                               \
            perror("Failed to open file context");                             \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    })
#define loadstatus(s) (s == true ? "Successfully!" : "Failed!")
#define shadersize(a, n)  (sizeof(a) / sizeof(a[n]))
#endif /* _UTIL_H */
