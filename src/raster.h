#ifndef RASTER_H_INCLUDED
#define RASTER_H_INCLUDED

#include "engine_gfx.h"

extern class_stored raster_class_off;

struct xyxyNNN
{
	int x1;
	int y1;
	int x2;
	int y2;
	int NNN;
};

struct ua_dRect
{
	int x1;
	int y1;
	int x2;
	int y2;
};

struct ua_fRect
{
	float x1;
	float y1;
	float x2;
	float y2;
};

struct __NC_STACK_raster
{
	bitmap_intern *bitm_intern;
	DWORD field_4; // Color?
	DWORD field_8; // and Color2 ?
    DWORD field_c;
//  int field_10;
//  int field_14;
//  int field_18;
//  int field_1c;
//  int field_20;
	xyxyNNN field_24;
	xyxyNNN field_38;
//  int field_4c;
//  int field_50;
//  int field_54;
//  int field_58;
//  int field_5c;
//  int field_60;
//  int field_64;
//  int field_68;
//  int field_6c;
//  int field_70;
//  int field_74;
//  int field_78;
//  int field_7c;
//  int field_80;
//  int field_84;
//  int field_88;
//  int field_8c;
//  int field_90;
//  int field_94;
//  int field_98;
//  int field_9c;
//  int field_a0;
//  int field_a4;
//  int field_a8;
//  int field_ac;
//  int field_b0;
//  int field_b4;
//  int field_b8;
//  int field_bc;
//  int field_c0;
//  int field_c4;
//  int field_c8;
//  int field_cc;
//  int field_d0;
//  int field_d4;
//  int field_d8;
//  int field_dc;
//  int field_e0;
//  int field_e4;
//  int field_e8;
//  int field_ec;
//  int field_f0;
//  int field_f4;
//  int field_f8;
//  int field_fc;
//  int field_100;
//  int field_104;
//  int field_108;
//  int field_10c;
//  int field_110;
//  int field_114;
//  int field_118;
//  int field_11c;
//  int field_120;
//  int field_124;
//  int field_128;
//  int field_12c;
//  int field_130;
//  int field_134;
//  int field_138;
//  int field_13c;
//  int field_140;
//  int field_144;
//  int field_148;
	tiles_stru *tiles[256];
	int field_54c;
	int field_550;
	float field_554;
	float field_558;
//  int field_55c;
//  int field_560;
//  int field_564;
//  int field_568;
//  int field_56c;
//  int field_570;
//  int field_574;
//  int field_578;
//  int field_57c;
//  int field_580;
//  int field_584;
//  int field_588;
//  int field_58c;
//  int field_590;
//  int field_594;
//  int field_598;
//  int field_59c;
};

struct NC_STACK_raster : public NC_STACK_bitmap
{
	__NC_STACK_raster stack__raster;
};


struct w3d_func198arg
{
	float x1;
	float y1;
	float x2;
	float y2;
};

struct w3d_func199arg
{
	int x1;
	int y1;
	int x2;
	int y2;
};

struct rstr_arg204
{
	bitmap_intern *pbitm;
	float float4;
	float float8;
	float floatC;
	float float10;
	float float14;
	float float18;
	float float1C;
	float float20;
};

struct rstr_loc204
{
	bitmap_intern *pbitm;
	int dword4;
	int dword8;
	int dwordC;
	int dword10;
	int dword14;
	int dword18;
	int dword1C;
	int dword20;
	int dword24;
};

struct rstr_arg217
{
	DWORD dword0;
	DWORD dword4;
	DWORD dword8;
};

struct rstr_218_arg
{
	bitmap_intern *bitm_intern;
	bitmap_intern *bitm_intern2;
	int flg;
	ua_fRect rect1;
	ua_fRect rect2;
};

#endif // RASTER_H_INCLUDED