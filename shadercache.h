#ifndef _SHADERCACHE_H
#define _SHADERCACHE_H

/* IMPORTANT: I don't own any of these shaders reference the
 * authors in the -a --authors commands or in the loadshaders.c file.
 *
 * This file stores the raw shader zip documents
 * that are held within the shaders directory.
 *
 * Reference the enum when indexing the shaders array.
 * 
 * TODO:
 * Have all the zip documents compressed into a tar.gz archive
 * and decompress the archive to reveal the zips. Better storage
 * since some shaders can be huge and take a good amount of space.*
 * */

enum _shader_reference {
    InternalName,
    ShaderCacheName,
} _shader_reference;

const char *shaders[][2] = {
    {"BSL_v8.1.03", "BSL_v8.1.03.zip"},
    {"CompShaders_v4.5", "ComplementaryShaders_v4.5.zip"},
    {"SEUSRenewed_v1.0.1", "SEUS-Renewed-v1.0.1.zip"},
    {"LaglessShaders_v1.10.2", "Lagless-Shaders-Standard_1.10.2.zip"},
    {"DrDestensShaders_v1.5.7", "DrDestens-Shaders_v1.5.7.zip"},
    {"TrilitonShaders_v8", "TrilitonShaders_v8.zip"}
};

#endif /* _SHADERCACHE_H */
