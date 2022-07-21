# mc-loadshader
Load Minecraft shaders for Optifine through the command-line

# Installation

To install mc-loadshader first clone this repository

```console
git clone "https://github.com/wnstdrr/mc-loadshader"
```

Next make sure you have `make` installed. To build from source
in the mc-loadshader directory run `make` and you will be given
and executable named `mc-loadshader`.

# Features

The current features of `mc-loadshader`.

## Authors

I don't own any of these shaders, I am simply using them for the cache and examples.
If you want to reference the original authors the -a or --authors option provides each
authors handle as well as a link to the original project.

Example:

```console
./mc-loadshader --authors
```

## Installing shaders

Use the -f or --file options and -c or --cache options when installing a shader from a zip file or from cache. The program expects the shader to be
in the same directory as `mc-loadshader` if installing from zip. Alternativly you could add your custom shader to the shadercache.h header
to allow for the shader to be cached and used later or use the ones provided.

Example -f --file:

```console
./mc-loadshader --file BSL_v8.1.03.zip
```

Example -c --cache:

```console
./mc-loadshader --cache BSL_v8.1.03
```

## Removing shaders

Use the -r or --remove option when removing a shader. Make sure that you reference the InternalName
of the shader and not the zip file itself. For information on InternalName see -l or --list.

Example -r --remove:

```console
./mc-loadshader --remove BSL_v8.1.03
```

## Listing installed and cache

You can list the currently installed shaders that are located in the default directory for shaders
using the -i or --installed options. You can also list the cache using -c or --cache options. The cache
options are hard coded to accept spesfic name or aliases for shaders, more can be appended by modifiying the
shadercache.h source file.

Example -i --installed:

```console
./mc-loadshader --installed 
```

Example -l --list:

```console
./mc-loadshader --list
```
