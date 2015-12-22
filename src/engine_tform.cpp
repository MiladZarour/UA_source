#include "includes.h"
#include "engine_tform.h"
#include "math.h"
#include "utils.h"

stored_functions *classvtbl_get_tformEngine();

int tformEngine__init(unsigned int, ...);
void tformEngine__deinit();
void tformEngine__setter(unsigned int, ...);
void tformEngine__getter(unsigned int, ...);


stored_functions_engine tform_engine_vtbl = {tformEngine__init, tformEngine__deinit, tformEngine__setter, tformEngine__getter};



class_stored tform_engine_off (NULL, NULL, "MC2engines:tform_NG.engine", classvtbl_get_tformEngine);


stored_functions *classvtbl_get_tformEngine()
{
	return (stored_functions *)&tform_engine_vtbl;
}


SinCos *SinCos_table = NULL;

key_value_stru tform_keys[4] = {{"tform.backplane", KEY_TYPE_DIGIT, 0x1000},
	{"tform.frontplane", KEY_TYPE_DIGIT, 0x10},
	{"tform.zoomx", KEY_TYPE_DIGIT, 0x140},
	{"tform.zoomy", KEY_TYPE_DIGIT, 0xC8}
};

float tform_backplane;
float tform_frontplane;
float tform_zoomx;
float tform_zoomy;

int tformEngine__init(unsigned int, ...)
{
	get_keyvalue_from_ini(0, tform_keys, 4);

	tform_backplane = tform_keys[0].value.val;
	tform_frontplane = tform_keys[1].value.val;
	tform_zoomx = tform_keys[2].value.val;
	tform_zoomy = tform_keys[3].value.val;

	SinCos_table = (SinCos *)AllocVec(sizeof(SinCos) * 361, 1);

	if ( !SinCos_table)
		return 0;

	for (int i = 0; i < 361; i++)
	{
		float rad = i * 3.141592653589793 / 180.0;

		SinCos_table[i].sin = sin(rad);
		SinCos_table[i].cos = cos(rad);
	}

	return 1;
}

void tformEngine__deinit()
{
	if (SinCos_table)
		nc_FreeMem(SinCos_table);
}

void tformEngine__setter(unsigned int a1, ...)
{
	stack_vals vals[128];

	if (a1 != 0)
	{
		va_list va;
		va_start(va, a1);

		va_to_arr(vals, 128, a1, va);

		va_end(va);
	}

	stack_vals *val = find_id_in_stack2(0x80002002, vals);
	if ( val )
		tform_zoomx = val->value;

	val = find_id_in_stack2(0x80002003, vals);
	if ( val )
		tform_zoomy = val->value;

	val = find_id_in_stack2(0x80002004, vals);
	if ( val )
		tform_backplane = val->value;

	val = find_id_in_stack2(0x80002005, vals);
	if ( val )
		tform_frontplane = val->value;
}

void tformEngine__getter(unsigned int a1, ...)
{
	stack_vals vals[128];

	if (a1 != 0)
	{
		va_list va;
		va_start(va, a1);
		va_to_arr(vals, 128, a1, va);
		va_end(va);
	}

	int *tmp = (int *)find_id_in_stack_def_val(0x80002002, 0, vals);
	if ( tmp )
		*tmp = ((int)tform_zoomx) << 16;

	tmp = (int *)find_id_in_stack_def_val(0x80002003, 0, vals);
	if ( tmp )
		*tmp = ((int)tform_zoomy) << 16;

	tmp = (int *)find_id_in_stack_def_val(0x80002004, 0, vals);
	if ( tmp )
		*tmp = ((int)tform_backplane) << 16;

	tmp = (int *)find_id_in_stack_def_val(0x80002005, 0, vals);
	if ( tmp )
		*tmp = ((int)tform_frontplane) << 16;
}