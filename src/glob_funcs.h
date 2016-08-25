#ifndef GLOB_FUNCS_H_INCLUDED
#define GLOB_FUNCS_H_INCLUDED

#include "MFILE.h"
#include "MC.h"
#include "ini.h"

struct g_engines
{
    int __AllocCount;
    int __AllocSize;
    int __AllocMax;
    int file_handles;
    char MC_RES_CLASS_ENGINE[3][256];
    const char *some_params_pointers[32];
    int some_params_count;
    NC_STACK_display *display___win3d;
    int field_3D4;
    nlist stru_525D68;
};


void nc_FreeMem(void *);
void *AllocVec(size_t size, int a2);

struct nnode_str: nnode
{
    char str[32];
    char str2[256];
};

const char * get_prefix_replacement(const char *prefix);
int set_prefix_replacement(const char *str1, const char *str2);

char * file_path_copy_manipul(const char *src, char *dst, int size);


void sub_412810(const char *a1, char *a2, int num);


#endif // GLOB_FUNCS_H_INCLUDED
