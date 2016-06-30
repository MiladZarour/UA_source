#include <inttypes.h>
#include <string.h>
#include <math.h>
#include "includes.h"
#include "def_parser.h"
#include "yw_internal.h"
#include "yw.h"
#include "input.h"

#include "yparobo.h"
#include "font.h"

extern int bact_id;


NC_STACK_ilbm * loadDisk_screen(_NC_STACK_ypaworld *yw)
{
    CDAUDIO_t arg;
    arg.command = 1;
    sub_4444D4(&arg);

    const char *v3;

    if ( yw->screen_width <= 360 )
        v3 = "disk320.ilbm";
    else if ( yw->screen_width > 600 )
        v3 = "disk640.ilbm";
    else
        v3 = "disk512.ilbm";

    char rsrc_def[128];

    strcpy(rsrc_def, get_prefix_replacement("rsrc"));

    set_prefix_replacement("rsrc", "data:mc2res");

    NC_STACK_ilbm *disk = (NC_STACK_ilbm *)init_get_class("ilbm.class", 0x80001000, v3, 0x80002008, 1, 0x80002009, 1, 0);

    set_prefix_replacement("rsrc", rsrc_def);

    return disk;
}

void draw_splashScreen(_NC_STACK_ypaworld *yw, NC_STACK_ilbm *splashScreen)
{
    if ( splashScreen )
    {
        rstr_arg204 a4;

        call_vtbl(splashScreen, 3, 0x80002000, &a4.pbitm, 0); // bitmap_func3

        a4.float4  = -1.0;
        a4.float8  = -1.0;
        a4.floatC  =  1.0;
        a4.float10 =  1.0;
        a4.float14 = -1.0;
        a4.float18 = -1.0;
        a4.float1C =  1.0;
        a4.float20 =  1.0;

        NC_STACK_win3d *win3d;
        gfxEngine__getter(0x8000300D, &win3d, 0);

        if ( win3d )
        {
            displ_arg263 v4;
            v4.bitm = yw->pointers__bitm[5];
            v4.pointer_id = 6;

            call_method(win3d, 263, &v4);

            call_method(win3d, 257);
            call_method(win3d, 215);

            call_method(win3d, 202, &a4);

            call_method(win3d, 216);
            call_method(win3d, 258);

            call_method(win3d, 257);
            call_method(win3d, 215);

            call_method(win3d, 202, &a4);

            call_method(win3d, 216);
            call_method(win3d, 258);
        }
    }
}

void drawSplashScreenWithTOD(_NC_STACK_ypaworld *yw, NC_STACK_ilbm *splashScreen, const char *text)
{
    if ( splashScreen )
    {
        rstr_arg204 a4;

        call_vtbl(splashScreen, 3, 0x80002000, &a4.pbitm, 0); // bitmap_func3

        a4.float4  = -1.0;
        a4.float8  = -1.0;
        a4.floatC  =  1.0;
        a4.float10 =  1.0;
        a4.float14 = -1.0;
        a4.float18 = -1.0;
        a4.float1C =  1.0;
        a4.float20 =  1.0;

        NC_STACK_win3d *win3d;
        gfxEngine__getter(0x8000300D, &win3d, 0);

        if ( win3d )
        {
            displ_arg263 v4;
            v4.bitm = yw->pointers__bitm[5];
            v4.pointer_id = 6;

            call_method(win3d, 263, &v4);

            call_method(win3d, 257);
            call_method(win3d, 215);

            call_method(win3d, 202, &a4);

            splashScreen_OutText(yw, win3d, text, yw->screen_width / 7, yw->screen_height / 5);

            call_method(win3d, 216);
            call_method(win3d, 258);

            call_method(win3d, 257);
            call_method(win3d, 215);

            call_method(win3d, 202, &a4);

            splashScreen_OutText(yw, win3d, text, yw->screen_width / 7, yw->screen_height / 5);

            call_method(win3d, 216);
            call_method(win3d, 258);
        }
    }
}

void deleteSplashScreen(_NC_STACK_ypaworld *yw, NC_STACK_ilbm *splashScreen)
{
    if ( splashScreen )
        delete_class_obj(splashScreen);
}

void sb_0x44ca90__sub4(_NC_STACK_ypaworld *yw)
{
    if ( yw->history )
    {
        while ( 1 )
        {
            yw_f726c_nod *hnode = (yw_f726c_nod *)RemHead(&yw->history->lst);

            if (!hnode)
                break;

            nc_FreeMem(hnode->bufStart);
            nc_FreeMem(hnode);
        }

        nc_FreeMem(yw->history);
        yw->history = NULL;
    }

    yw->history = (yw_f726c *)AllocVec(sizeof(yw_f726c), 65537);

    if ( yw->history )
    {
        memset(yw->history, 0, sizeof(yw_f726c));
        init_list(&yw->history->lst);
    }
}

int sb_0x44ca90__sub6(_NC_STACK_ypaworld *yw)
{
    yw->map_events = (map_event *)AllocVec(sizeof(map_event), 65537);

    return yw->map_events != NULL;
}

int sb_0x44ca90__sub7(_NC_STACK_ypaworld *yw, int event_loop_id)
{
    //Event funcs
    int sub_4D51A4(_NC_STACK_ypaworld *yw);
    int sub_4D5218(_NC_STACK_ypaworld *yw);
    int sub_4D5160(_NC_STACK_ypaworld *yw);
    int sub_4D528C(_NC_STACK_ypaworld *yw);
    int sub_4D5300(_NC_STACK_ypaworld *yw);
    int sub_4D5348(_NC_STACK_ypaworld *yw);
    int sub_4D5360(_NC_STACK_ypaworld *yw);

    map_event *mevnts = yw->map_events;
    mevnts->field_8 = -1;
    mevnts->field_C = 0;
    mevnts->field_4 = 0;
    mevnts->event_count = 0;
    mevnts->event_loop_id = event_loop_id;

    if (event_loop_id == 1)
    {
        evnt *ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 5000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 0;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D51A4;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 47;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D5218;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 48;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D5160;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 49;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 6;
        ev->field_10 = 15000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 60;
        ev->field_18++;
    }
    else if ( event_loop_id == 2 )
    {
        evnt *ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 5000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 0;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D51A4;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 47;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D528C;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 50;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 2;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D5160;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 64;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 51;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 52;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 20000;
        ev->field_4 = sub_4D5160;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 53;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 6;
        ev->field_10 = 15000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 61;
        ev->field_18++;
    }
    else if ( event_loop_id == 3 )
    {
        evnt *ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 3000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 0;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 8000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 59;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 60000;
        ev->field_4 = sub_4D5300;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 54;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 94;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 3000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 95;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 60000;
        ev->field_4 = sub_4D5348;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 97;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 96;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 3000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 98;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 9000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 99;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 5000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 0;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 60000;
        ev->field_4 = sub_4D5160;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 101;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 100;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 4000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 102;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 3;
        ev->field_10 = 60000;
        ev->field_4 = sub_4D5360;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 55;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 3000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 103;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 5;
        ev->field_10 = 45000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 0;
        ev->field_18++;


        ev = &mevnts->evnts[ mevnts->event_count ];
        mevnts->event_count++;

        memset(ev, 0, sizeof(evnt));

        ev->field_0 = 4;
        ev->field_10 = 60000;
        ev->field_4 = NULL;
        ev->field_14 = 0;
        ev->field_1C[ ev->field_18 ] = 104;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 56;
        ev->field_18++;
        ev->field_1C[ ev->field_18 ] = 65;
        ev->field_18++;
    }

    return 1;
}

void  sub_44F500(_NC_STACK_ypaworld *yw, int id)
{
    yw_field34 *fld34 = &yw->field_34[id];

    cellArea *cell = fld34->p_cell;

    if ( cell )
    {
        fld34->p_cell = NULL;

        if ( id == yw->field_38 - 1 )
            yw->field_38--;

        cell->field_3B = 0;
        cell->field_3A = 0;

        if ( yw->blg_map )
        {
            bitmap_intern *bitm;
            call_vtbl(yw->blg_map, 3, 0x80002000, &bitm, 0);

            uint8_t *tmp = (uint8_t *)bitm->buffer + fld34->x + fld34->y * bitm->width;
            *tmp = 0;
        }
    }
}

int sb_0x44ca90__sub3(_NC_STACK_ypaworld *yw)
{
    yw->field_30 = (yw_f30 *)AllocVec(sizeof(yw_f30) * 64 * 64, 65537);

    if ( yw->field_30 )
    {
        yw->field_34 = (yw_field34 *)AllocVec(sizeof(yw_field34) * 256, 65537);

        if ( yw->field_34 )
        {
            for (int i = 0; i < 256; i++)
                sub_44F500(yw, i);

            yw->field_3c = 0;
            yw->field_38 = 0;
        }
        else
        {
            if ( yw->field_30 )
            {
                nc_FreeMem(yw->field_30);
                yw->field_30 = NULL;
            }
            return 0;
        }
    }
    else
    {
        if ( yw->field_34 )
        {
            nc_FreeMem(yw->field_34);
            yw->field_34 = NULL;
            yw->field_38 = 0;
        }

        if ( yw->field_30 )
        {
            nc_FreeMem(yw->field_30);
            yw->field_30 = NULL;
        }
        return 0;
    }
    return 1;
}

void sb_0x44ca90__sub5(_NC_STACK_ypaworld *yw)
{
    memset(yw->field_80, 0, sizeof(yw_f80) * 8);
}

void sb_0x44ca90__sub2(_NC_STACK_ypaworld *yw, mapProto *mapp)
{
    NC_STACK_win3d *win3d;
    gfxEngine__getter(0x8000300D, &win3d, 0);

    for (int i = 0; i < 8; i++)
    {
        if (mapp->palettes[i][0])
        {
            NC_STACK_ilbm *ilbm = (NC_STACK_ilbm *)init_get_class("ilbm.class", 0x80001000, mapp->palettes[i], 0x80002006, 1, 0);

            if (ilbm)
            {
                rstr_261_arg v7;
                v7.pal_num = 256;
                v7.pal_id = i;
                v7.entrie_id = 0;

                call_vtbl(ilbm, 3, 0x80002007, &v7.pal_entries, 0);

                if ( i )
                    call_method(win3d, 261, &v7);
                else
                    call_vtbl(win3d, 2, 0x80002007, v7.pal_entries, 0);

                delete_class_obj(ilbm);
            }
            else
            {
                ypa_log_out("WARNING: slot #%d [%s] init failed!\n", i, mapp->palettes[i]);
            }
        }
    }
}

int sb_0x44ca90__sub8(_NC_STACK_ypaworld *yw)
{
    yw->samples = (yw_samples *)AllocVec(sizeof(yw_samples), 65537);
    if ( !yw->samples )
        return 0;

    yw->samples->field_0 = -1;
    sub_423DB0(&yw->samples->field_4);

    return 1;
}

int sb_0x44ca90(_NC_STACK_ypaworld *yw, mapProto *mapp, int levelID, int a5)
{
    int ok = 0;

    memset(mapp, 0, sizeof(mapProto));

    memset(yw->field_7796, 0, sizeof(player_status) * 8);

    yw->field_1614 = 0;
    yw->field_1a04 = 0;
    yw->field_1a08 = 0;
    yw->field_1a00 = 0;
    yw->field_1a1c = 0;
    yw->field_161c = 0;

    yw->field_2d90->levelID = levelID;
    yw->field_2d90->field_48 = a5;
    yw->field_2d90->field_40 = 0;
    yw->field_2d90->gate_count = 0;
    yw->field_2d90->supetItems_count = 0;
    yw->field_2d90->ownerMap__has_vehicles = 0;
    yw->field_2d90->field_60 = 0;

    yw->field_1a60 = 0;
    yw->field_1a98 = NULL;
    yw->field_1aac = 0;
    yw->current_bact = NULL;
    yw->field_1b78 = NULL;
    yw->field_1b7c = NULL;
    yw->field_1b80 = NULL;
    yw->field_1b84 = NULL;
    yw->field_1b88 = NULL;
    yw->field_1ab0 = 0;
    yw->field_160c = 0;
    yw->field_1610 = 0;
    yw->field_7882 = 1;
    yw->field_7886 = 1;
    yw->field_788A = 0;
    yw->field_81AF = 0;
    yw->field_241c = 0;
    yw->field_1628 = 0;
    yw->field_162A = 0;
    yw->field_1624 = 0;
    yw->vehicle_sector_ratio_1 = 0;
    yw->field_8283 = 0;
    yw->field_1a20 = 0;

    memset(yw->field_2d90->gates, 0, sizeof(gateProto) * 8);
    memset(yw->field_2d90->supetItems, 0, sizeof(supetItemProto) * 8);
    memset(yw->gems, 0, sizeof(gemProto) * 8);
    memset(&yw->field_81CB, 0, sizeof(yw_81cb));
    memset(yw->field_1bac, 0, sizeof(int) * 8);

    yw->field_753A = 0;
    yw->field_7542 = 0;
    yw->field_754A = 0;
    yw->field_755A = 0;
    yw->field_7552 = 0;

    if ( !yw->one_game_res )
    {
        if ( yw->game_default_res != yw->shell_default_res )
        {
            inputEngine__setter(0x80001007, 0, 0);
            gfxEngine__setter(0x80003007, yw->game_default_res, 0);

            windd__window_params *a2;
            gfxEngine__getter(0x80003007, &a2, 0);
            inputEngine__setter(0x80001007, a2, 0);

            int width, height;

            gfxEngine__getter(0x80003003, &width, 0x80003004, &height, 0x8000300D, &yw->win3d, 0);
            yw->screen_width = width;
            yw->screen_height = height;

            call_vtbl(yw->win3d, 2, 0x80005000, (yw->field_73CE & 0x40) != 0, 0);

            if ( yw->screen_width >= 512 )
            {
                load_font( get_lang_string(yw->string_pointers_p2, 15, "MS Sans Serif,12,400,0") );
            }
            else
            {
                load_font( get_lang_string(yw->string_pointers_p2, 16, "Arial,8,400,0") );
            }
        }
    }

    NC_STACK_ilbm *diskScreenImage = loadDisk_screen(yw);

    if ( diskScreenImage )
        draw_splashScreen(yw, diskScreenImage);


    char rsr[256];

    strcpy(rsr, get_prefix_replacement("rsrc"));

    set_prefix_replacement("rsrc", "data:fonts");

    int v19 = load_fonts_and_icons(yw);

    set_prefix_replacement("rsrc", rsr);

    if ( !v19 )
        return 0;

    int tod = loadTOD(yw, "tod.def");

    const char *text = get_lang_string(yw->string_pointers_p2, tod + 2490, " ");

    tod++;
    if ( tod + 2490 > 2510 )
        tod = 0;

    writeTOD(yw, "tod.def", tod);

    if ( diskScreenImage )
    {
        drawSplashScreenWithTOD(yw, diskScreenImage, text);
        deleteSplashScreen(yw, diskScreenImage);
    }

    yw->p_1_grp_cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        yw->p_1_grp[0][i] = 0;
        yw->p_1_grp[1][i] = 0;
        yw->p_1_grp[2][i] = 100000;
        yw->p_1_grp[3][i] = 0;
    }

    sb_0x44ca90__sub4(yw);

    milesEngine__getter(0x80004003, &yw->audio_volume, 0);

    sb_0x44ca90__sub8(yw);
    sb_0x44ca90__sub6(yw);

    set_prefix_replacement("rsrc", "data:");

    if ( sub_4DA41C(yw, mapp, yw->LevelNet->mapInfos[yw->field_2d90->levelID].mapPath) && (mapp->flags & 0x7F) == 0x7F )
    {
        sb_0x44ca90__sub7(yw, mapp->event_loop);

        if ( !sb_0x44ca90__sub3(yw) )
            return 0;

        sb_0x44ca90__sub5(yw);

        char a1[32];
        sprintf(a1, "data:set%d", mapp->setNumber);

        set_prefix_replacement("rsrc", a1);

        sb_0x44ca90__sub2(yw, mapp);

        if ( yw_LoadSet(yw, mapp->setNumber) )
        {
            if ( yw_loadSky(yw, mapp->sky) )
                ok = 1;
        }
    }

    return ok;
}

int cells_mark_type(_NC_STACK_ypaworld *yw, const char *a2)
{
    if ( !yw->typ_map )
        return 0;

    bitmap_intern *bitm;
    call_vtbl(yw->typ_map, 3, 0x80002000, &bitm, 0);

    uint8_t *typMap = (uint8_t *)bitm->buffer;

    yw->sectors_maxX2 = bitm->width;
    yw->sectors_maxY2 = bitm->height;

    yw->map_Width_meters = yw->sectors_maxX2 * 1200.0;
    yw->map_Height_meters = yw->sectors_maxY2 * 1200.0;

    int sectors_count = yw->sectors_maxY2 * yw->sectors_maxX2;

    memset(yw->cells, 0, sizeof(cellArea) * sectors_count);

    for (int i = 0; i < sectors_count; i++)
    {
        cellArea *cell = &yw->cells[i];
        secType *sectp = &yw->secTypes[ typMap[i] ];

        init_list(&cell->field_3C);

        cell->sec_type = typMap[i];
        cell->field_2E = sectp->field_0;
        cell->field_2F = 0;

        if ( sectp->field_0 == 1)
        {
            cell->buildings_health[0][0] = sectp->buildings[0][0]->build_health;
        }
        else
        {
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    cell->buildings_health[j][k] = sectp->buildings[j][k]->build_health;
        }
    }
    return 1;
}

int cells_mark_owner(_NC_STACK_ypaworld *yw, const char *a2)
{
    memset(yw->sectors_count_by_owner, 0, sizeof(int) * 8);

    if ( !yw->own_map )
        return 0;

    bitmap_intern *bitm;
    call_vtbl(yw->own_map, 3, 0x80002000, &bitm, 0);       // bitmap_func3

    uint8_t *ownmap = (uint8_t *)bitm->buffer;

    if ( bitm->width != yw->sectors_maxX2 || bitm->height != yw->sectors_maxY2 )
    {
        ypa_log_out("Mapsize mismatch %s: is [%d,%d], should be [%d,%d].\n", a2, bitm->width, bitm->height, yw->sectors_maxX2, yw->sectors_maxY2);
        delete_class_obj(yw->own_map);
        yw->own_map = NULL;
        return 0;
    }


    for (int yy = 0; yy < yw->sectors_maxY2; yy++)
    {
        uint8_t *ownmapp = ownmap + yy * yw->sectors_maxX2;
        cellArea *cells = yw->cells + yy * yw->sectors_maxX2;

        for (int xx = 0; xx < yw->sectors_maxX2; xx++)
        {
            if ( xx > 0 && yy > 0 && xx != yw->sectors_maxX2 - 1 && yy != yw->sectors_maxY2 - 1 )
                cells[xx].owner = ownmapp[xx];
            else
                cells[xx].owner = 0;

            yw->sectors_count_by_owner[ (int)cells[xx].owner ]++;
        }
    }

    return 1;
}

int cells_mark_hight(_NC_STACK_ypaworld *yw, const char *a2)
{
    if ( !yw->hgt_map )
        return 0;

    bitmap_intern *bitm;
    call_vtbl(yw->hgt_map, 3, 0x80002000, &bitm, 0);

    uint8_t *hgtMap = (uint8_t *)bitm->buffer;

    if ( bitm->width != yw->sectors_maxX2 || bitm->height != yw->sectors_maxY2 )
    {
        ypa_log_out("Mapsize mismatch %s: is [%d,%d], should be [%d,%d].\n", a2, bitm->width, bitm->height, yw->sectors_maxX2, yw->sectors_maxY2);
        delete_class_obj(yw->hgt_map);
        yw->hgt_map = NULL;
        return 0;
    }

    int sectors_cnt = yw->sectors_maxY2 * yw->sectors_maxX2;

    for (int i = 0; i < sectors_cnt; i++)
    {
        yw->cells[i].sector_height_meters = hgtMap[i] * -100.0;
    }

    for (int y = 1; y < yw->sectors_maxY2; y++)
    {
        for (int x = 1; x < yw->sectors_maxX2; x++)
        {
            int yy = y - 1;
            int xx = x - 1;

            int cur_sector_id = x + y * yw->sectors_maxX2;
            int left_sector = xx + y * yw->sectors_maxX2;
            int left_up_sector = xx + yy * yw->sectors_maxX2;
            int up_sector = x + yy * yw->sectors_maxX2;

            yw->cells[cur_sector_id].smooth_height = (yw->cells[cur_sector_id].sector_height_meters +
                    yw->cells[left_sector].sector_height_meters +
                    yw->cells[left_up_sector].sector_height_meters +
                    yw->cells[up_sector].sector_height_meters ) / 4.0;
        }
    }

    return 1;
}

int yw_createRobos(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, int robos_count, mapRobo *robo)
{
    stru_2d90 *f2d90 = yw->field_2d90;

    if ( f2d90->field_48 != 1 )
    {
        f2d90->ownerMap__has_vehicles = 0;
        f2d90->field_60 = 2;

        for (int i = 0; i < robos_count; i++)
        {
            mapRobo *v8 = robo + i;

            ypaworld_arg136 v14;
            v14.pos_x = v8->pos_x;
            v14.pos_y = -30000.0;
            v14.pos_z = v8->pos_z;

            v14.field_14 = 0;
            v14.field_18 = 50000.0;
            v14.field_1C = 0;
            v14.field_40 = 0;

            ypaworld_arg146 v15;
            v15.vehicle_id = v8->vehicle;
            v15.pos.sx = v8->pos_x;
            v15.pos.sy = v8->pos_y;
            v15.pos.sz = v8->pos_z;

            call_method(ywo, 136, &v14);

            if ( v14.field_20 )
                v15.pos.sy = v14.field_30 + v8->pos_y;

            NC_STACK_ypabact *bact = (NC_STACK_ypabact *)call_method(ywo, 146, &v15);

            if ( bact )
            {
                int v20 = 0;

                call_method(ywo, 134, bact);

                __NC_STACK_ypabact *bact_int;
                call_vtbl(bact, 3, 0x80001003, &bact_int, 0); // ypabact_func3

                int v12;

                if ( i )
                {
                    v12 = v8->energy;
                }
                else
                {
                    v12 = v8->energy / 4;

                    if ( v12 < yw->maxroboenergy )
                    {
                        v12 = yw->maxroboenergy;
                        v20 = yw->maxreloadconst;
                    }

                }

                bact_int->owner = v8->owner;
                bact_int->energy = v12;
                bact_int->energy_2 = v12;

                if ( !v20 )
                {
                    if ( v8->reload_const )
                        v20 = v8->reload_const;
                    else
                        v20 = bact_int->energy_2;
                }

                bact_int->reload_const_or_energy2 = v20;

                call_vtbl(bact, 2, 0x80001007, 1, 0);
                call_vtbl(bact, 2, 0x8000200B, 15, 0);
                call_vtbl(bact, 2, 0x80002008, v12, 0);
                call_vtbl(bact, 2, 0x8000200A, v12, 0);

                yw->field_2d90->ownerMap__has_vehicles |= 1 << v8->owner;

                call_vtbl(bact, 2, 0x80002002, v8->con_budget, 0);
                call_vtbl(bact, 2, 0x80002003, v8->def_budget, 0);
                call_vtbl(bact, 2, 0x80002004, v8->rad_budget, 0);
                call_vtbl(bact, 2, 0x80002005, v8->pow_budget, 0);
                call_vtbl(bact, 2, 0x80002006, v8->saf_budget, 0);
                call_vtbl(bact, 2, 0x8000200F, v8->cpl_budget, 0);
                call_vtbl(bact, 2, 0x80002011, v8->rob_budget, 0);
                call_vtbl(bact, 2, 0x80002010, v8->rec_budget, 0);
                call_vtbl(bact, 2, 0x80002013, v8->viewangle, 0);
                call_vtbl(bact, 2, 0x80002014, v8->saf_delay, 0);
                call_vtbl(bact, 2, 0x80002015, v8->pow_delay, 0);
                call_vtbl(bact, 2, 0x80002017, v8->cpl_delay, 0);
                call_vtbl(bact, 2, 0x80002016, v8->rad_delay, 0);
                call_vtbl(bact, 2, 0x80002018, v8->def_delay, 0);
                call_vtbl(bact, 2, 0x80002019, v8->con_delay, 0);
                call_vtbl(bact, 2, 0x8000201B, v8->rec_delay, 0);
                call_vtbl(bact, 2, 0x8000201A, v8->rob_delay, 0);

                if ( !i )
                {
                    call_vtbl(bact, 2, 0x80001004, 1, 0);
                    call_vtbl(bact, 2, 0x80001005, 1, 0);
                }
            }
        }
    }
    return 1;
}

int sub_44B9B8(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, const char *mapp)
{
    if ( !yw->blg_map )
        return 0;

    bitmap_intern *bitmp;
    call_vtbl(yw->blg_map, 3, 0x80002000, &bitmp, 0);

    uint8_t *blgMap = (uint8_t *)bitmp->buffer;

    if ( bitmp->width != yw->sectors_maxX2 || bitmp->height != yw->sectors_maxY2 )
    {
        ypa_log_out("Mapsize mismatch %s: is [%d,%d], should be [%d,%d].\n", mapp, bitmp->width, bitmp->height, yw->sectors_maxX2, yw->sectors_maxY2);
        delete_class_obj(yw->blg_map);
        yw->blg_map = NULL;
        return 0;
    }

    for ( int y = 0; y < yw->sectors_maxY2; y++)
    {
        uint8_t *blgln = blgMap + y * yw->sectors_maxX2;
        cellArea *cellln = yw->cells + y * yw->sectors_maxX2;

        for ( int x = 0; x < yw->sectors_maxX2; x++)
        {
            if (blgln[x] && cellln[x].owner)
            {
                ypaworld_arg148 arg148;

                arg148.ownerID = cellln[x].owner;
                arg148.ownerID2 = cellln[x].owner;
                arg148.blg_ID = blgln[x];
                arg148.field_C = 1;
                arg148.field_18 = 0;
                arg148.x = x;
                arg148.y = y;

                call_method(ywo, 148, &arg148);
            }
        }
    }

    return 1;
}

void yw_InitSquads(_NC_STACK_ypaworld *yw, int squad_cnt, squadProto *squads)
{
    if ( yw->field_2d90->field_48 != 1 )
    {
        for (int i = 0; i < squad_cnt; i++)
        {
            squadProto *squad = squads + i;

            if (squad->field_0)
            {
                NC_STACK_yparobo *robo = NULL;

                bact_node *nod = (bact_node *)yw->bact_list.head;
                while ( nod->next )
                {
                    if ( nod->bact->field_24 == 3 && nod->bact->owner == squad->owner)
                    {
                        robo = (NC_STACK_yparobo *)nod->bacto;
                        break;
                    }

                    nod = (bact_node *)nod->next;
                }

                if ( !robo )
                {
                    ypa_log_out("WARNING: yw_InitSquads(): no host robo for squad[%d], owner %d!\n", i, squad->owner);
                }
                else
                {
                    robo_arg133 arg133;
                    arg133.type = squad->vehicle;
                    arg133.num = squad->num;
                    arg133.hetero_vehicles = 0;
                    arg133.field_14 = (squad->useable == 0) + 2;

                    ypaworld_arg136 arg136;
                    arg136.pos_x = squad->pos_x;
                    arg136.pos_y = -50000.0;
                    arg136.pos_z = squad->pos_z;
                    arg136.field_14 = 0;
                    arg136.field_1C = 0;
                    arg136.field_40 = 0;
                    arg136.field_18 = 100000.0;
                    call_method(yw->self_full, 136, &arg136);

                    if ( arg136.field_20 )
                    {
                        arg133.pos.sx = arg136.field_2C;
                        arg133.pos.sz = arg136.field_34;
                        arg133.pos.sy = arg136.field_30 + -50.0;
                    }
                    else
                    {
                        yw_130arg sect_info;
                        sect_info.pos_x = squad->pos_x;
                        sect_info.pos_z = squad->pos_z;

                        if ( !call_method(yw->self_full, 130, &sect_info) )
                        {
                            ypa_log_out("yw_InitSquads(): no valid position for squad[%d]!\n", i);
                            return;
                        }

                        arg133.pos.sx = squad->pos_x;
                        arg133.pos.sy = sect_info.pcell->sector_height_meters;
                        arg133.pos.sz = squad->pos_z;
                    }
                    // Create squad by robo method
                    call_method(robo, 133, &arg133); // yparobo_func133
                }

            }
        }
    }
}

void yw_InitBuddies(_NC_STACK_ypaworld *yw)
{

    int vhcl_ids[128];

    if ( yw->field_2d90->buddies_count )
    {
        int squad_sn = 0;

        while ( 1 )
        {
            robo_arg133 bact_add;
            memset(&bact_add, 0, sizeof(robo_arg133));

            bact_add.field_14 = 2;

            int v3 = -1;

            bact_add.hetero_vehicles = vhcl_ids;

            for (int i = 0; i < yw->field_2d90->buddies_count; i++)
            {
                yw_buddy *buddy = &yw->field_2d90->buddies[i];

                if (!buddy->field_6)
                {
                    if (v3 == -1)
                    {
                        v3 = buddy->commandid;
                        bact_add.type = buddy->type;
                        bact_add.hetero_vehicles[ bact_add.num ] = buddy->type;
                        bact_add.num++;
                        buddy->field_6 = 1;

                    }
                    else if ( v3 == buddy->commandid )
                    {
                        bact_add.hetero_vehicles[ bact_add.num ] = buddy->type;
                        bact_add.num++;
                        buddy->field_6 = 1;
                    }
                }
            }

            if ( v3 != -1 )
            {
                bact_add.pos.sx = yw->field_1b80->field_621.sx + sin(squad_sn * 1.745) * 500.0;
                bact_add.pos.sy = yw->field_1b80->field_621.sy;
                bact_add.pos.sz = yw->field_1b80->field_621.sz + cos(squad_sn * 1.745) * 500.0;

                ypaworld_arg136 arg136;
                arg136.pos_x = bact_add.pos.sx + 0.5;
                arg136.pos_y = -50000.0;
                arg136.pos_z = bact_add.pos.sz + 0.75;
                arg136.field_14 = 0;
                arg136.field_18 = 100000.0;
                arg136.field_1C = 0;
                arg136.field_40 = 0;

                call_method(yw->self_full, 136, &arg136);

                if ( arg136.field_20 )
                    bact_add.pos.sy = arg136.field_30 + -100.0;

                call_method(yw->field_1b78, 133, &bact_add); //robo 133 method

                squad_sn++;
            }
            else
            {
                for (int i = 0; i < yw->field_2d90->buddies_count; i++)
                    yw->field_2d90->buddies[i].field_6 = 0;

                break;
            }
        }
    }
}

void yw_InitTechUpgradeBuildings(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw)
{
    yw->field_2b7c = 0;
    yw->last_modify_build = 0;
    yw->last_modify_vhcl = 0;
    yw->last_modify_weapon = 0;
    yw->field_2b78 = -1;

    for (int i = 0; i < 8; i++)
    {
        if ( yw->gems[0].field_0 )
        {
            int xx = yw->gems[i].sec_x;
            int yy = yw->gems[i].sec_y;

            cellArea *cell = &yw->cells[xx + yy * yw->sectors_maxX2];

            if (yw->gems[i].building)
            {
                if ( cell->field_3A != 3 || yw->gems[i].building != cell->field_3B )
                {
                    ypaworld_arg148 arg148;
                    arg148.ownerID = cell->owner;
                    arg148.ownerID2 = cell->owner;
                    arg148.blg_ID = yw->gems[i].building;
                    arg148.x = xx;
                    arg148.y = yy;
                    arg148.field_C = 1;
                    arg148.field_18 = 0;

                    call_method(ywo, 148, &arg148);
                }
            }

            cell->field_3A = 4;
            cell->field_3B = i;
        }
    }
}

void yw_InitGates(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < yw->field_2d90->gate_count; i++)
    {
        gateProto *gate = &yw->field_2d90->gates[i];

        cellArea *cell = &yw->cells[gate->sec_x + yw->sectors_maxX2 * gate->sec_y];

        gate->pcell = cell;

        ypaworld_arg148 arg148;
        arg148.ownerID = cell->owner;
        arg148.ownerID2 = gate->pcell->owner;
        arg148.blg_ID = gate->closed_bp;
        arg148.field_C = 1;
        arg148.x = gate->sec_x;
        arg148.y = gate->sec_y;
        arg148.field_18 = 0;

        call_method(yw->self_full, 148, &arg148);

        gate->pcell->field_3A = 5;
        gate->pcell->field_3B = i;

        for (int j = 0; j < gate->keySectors_count; j++)
        {
            int xx = gate->keySectors[j].x;
            int yy = gate->keySectors[j].y;

            if ( xx && xx < yw->sectors_maxX2 - 1 && yy && yy < yw->sectors_maxY2 - 1 )
            {
                gate->keySectors[j].cell = &yw->cells[xx + yw->sectors_maxX2 * yy];
            }
        }
    }
}

void yw_InitSuperItems(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < yw->field_2d90->supetItems_count; i++)
    {
        supetItemProto *stoudson = &yw->field_2d90->supetItems[i];
        cellArea *cell = &yw->cells[stoudson->sec_x + yw->sectors_maxX2 * stoudson->sec_y];

        stoudson->pcell = cell;

        ypaworld_arg148 arg148;
        arg148.ownerID = cell->owner;
        arg148.ownerID2 = stoudson->pcell->owner;
        arg148.blg_ID = stoudson->inactive_bp;
        arg148.field_C = 1;
        arg148.x = stoudson->sec_x;
        arg148.y = stoudson->sec_y;
        arg148.field_18 = 0;

        call_method(yw->self_full, 148, &arg148);

        stoudson->pcell->field_3A = 8;
        stoudson->pcell->field_3B = i;

        for (int j = 0; j < stoudson->keySectors_count; j++)
        {
            int xx = stoudson->keySectors[j].x;
            int yy = stoudson->keySectors[j].y;

            if ( xx && xx < yw->sectors_maxX2 - 1 && yy && yy < yw->sectors_maxY2 - 1 )
            {
                stoudson->keySectors[j].cell = &yw->cells[xx + yw->sectors_maxX2 * yy];
            }
        }

        stoudson->field_EC = 0;
        stoudson->field_F0 = 0;
        stoudson->field_F4 = 0;
        stoudson->field_4 = 0;
    }
}

void sub_44F748(_NC_STACK_ypaworld *yw)
{
    // Apply power to sectors and clean power matrix for next compute iteration.

    for (int y = 0; y < yw->sectors_maxY2; y++)
    {
        for (int x = 0; x < yw->sectors_maxX2; x++)
        {
            cellArea *cell = yw->cells + x + y * yw->sectors_maxX2;
            yw_f30 *tt = &yw->field_30[ x + y * 64 ];

            tt->owner = cell->owner;
            cell->field_2F = tt->field_1; // Apply power to cell
            tt->field_1 = 0; // Clean matrix's power
        }
    }

    yw->field_3c = 0; // Next power station for recompute power is first
}


void sub_44F958(_NC_STACK_ypaworld *yw, cellArea *cell, char secX, char secY, uint8_t owner)
{
    if ( cell->owner != owner )
    {
        yw_arg184 arg184;
        arg184.t26.secX = secX;
        arg184.t26.secY = secY;
        arg184.t26.owner = owner;
        arg184.type = 2;

        call_method(yw->self_full, 184, &arg184);

        if ( cell->field_3A == 2 )
        {
            arg184.type = 6;

            call_method(yw->self_full, 184, &arg184);
        }

        yw->sectors_count_by_owner[cell->owner]--;
        yw->sectors_count_by_owner[owner]++;

        cell->owner = owner;
    }
}

void sb_0x44fc60__sub0(_NC_STACK_ypaworld *yw, int secX, int secY, cellArea *cell, yw_arg129 *a5, int a6)
{
    int energon[8];

    if ( a6 == 255 )
    {
        a6 = cell->owner;

        memset(energon, 0, sizeof(energon));

        __NC_STACK_ypabact *nod = (__NC_STACK_ypabact *)cell->field_3C.head;

        while ( nod->next )
        {
            energon[nod->owner] += nod->energy;

            nod = (__NC_STACK_ypabact *)nod->next;
        }

        energon[0] = 0;

        for (int i = 0; i < 8; i++)
        {
            if ( energon[i] > energon[a6] )
                a6 = i;
        }
    }

    if ( cell->owner != a6 )
    {
        if ( cell->field_3A == 2 )
        {
            if ( yw->field_1b80->owner == a6 )
            {
                if ( a5 && a5->unit )
                {
                    yw_arg159 v21;
                    v21.unit = a5->unit;
                    v21.field_4 = 78;
                    v21.txt = NULL;
                    v21.field_C = 45;

                    call_method(yw->self_full, 159, &v21);
                }
            }
            else if ( cell->owner == yw->field_1b80->owner )
            {
                yw_arg159 v24;
                v24.unit = NULL;
                v24.field_4 = 78;
                v24.txt = NULL;
                v24.field_C = 67;

                call_method(yw->self_full, 159, &v24);
            }
        }
        else
        {
            for (int i = 0; i < yw->field_2d90->gate_count; i++)
            {
                gateProto *gate = yw->field_2d90->gates + i;

                for (int j = 0; j < gate->keySectors_count; j++)
                {
                    if ( cell == gate->keySectors[j].cell )
                    {
                        if ( yw->field_1b80->owner == a6 )
                        {
                            yw_arg159 v23;
                            v23.unit = NULL;
                            v23.field_4 = 80;
                            v23.txt = NULL;
                            v23.field_C = 82;

                            call_method(yw->self_full, 159, &v23);
                        }
                        else if ( yw->field_1b80->owner == cell->owner )
                        {
                            yw_arg159 v22;
                            v22.unit = NULL;
                            v22.field_4 = 80;
                            v22.txt = NULL;
                            v22.field_C = 81;

                            call_method(yw->self_full, 159, &v22);
                        }
                    }
                }
            }
        }
    }

    sub_44F958(yw, cell, secX, secY, a6);
}

void sb_0x44fc60(_NC_STACK_ypaworld *yw, cellArea *cell, int secX, int secY, int a5, yw_arg129 *a6)
{
    if ( secX && secY && yw->sectors_maxX2 - 1 != secX && yw->sectors_maxY2 - 1 != secY )
    {
        int helth = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                helth += cell->buildings_health[i][j];
            }
        }

        if ( cell->field_3A == 2 )
        {
            if ( helth )
            {
                int v13 = (helth * yw->field_34[ cell->field_3B ].power) / 256 ;

                if ( v13 < 0 )
                    v13 = 0;
                else if ( v13 > 255 )
                    v13 = 255;

                yw->field_34[cell->field_3B].power_2 = v13;
            }
            else
            {
                sub_44F500(yw, cell->field_3B);
            }
        }

        if ( cell->field_2E == 1 )
        {
            if ( helth < 224 )
                sb_0x44fc60__sub0(yw, secX, secY, cell, a6, a5);
        }
        else if ( helth < 1728 )
        {
            sb_0x44fc60__sub0(yw, secX, secY, cell, a6, a5);
        }
    }
    else
    {
        sub_44F958(yw, cell, secX, secY, 0);
    }
}



void sub_44DBF8(_NC_STACK_ypaworld *yw, int _dx, int _dz, int _dxx, int _dzz, struct_44dbf8 *a6, int flags)
{
    int v8 = flags;

    a6->sklt = NULL;
    a6->field_1E = 0;
    a6->field_1C = 0;

    if ( _dxx >= 1  &&  _dxx < 4 * yw->sectors_maxX2 - 1  &&  _dzz >= 1  &&  _dzz < 4 * yw->sectors_maxY2 - 1 )
    {
        a6->sec_x = _dxx / 4;
        a6->sec_y = _dzz / 4;

        a6->p_cell = &yw->cells[a6->sec_x + yw->sectors_maxX2 * (_dzz / 4)];

        if ( _dxx % 4 && _dzz % 4 )
        {
            a6->field_1C = 1;

            int v14, v16;

            if ( a6->p_cell->field_2E == 1 )
            {
                v14 = 0;
                v16 = 0;

                if ( (_dxx / 4) == (_dx / 4)  &&  (_dz / 4) == (_dzz / 4) )
                    v8 = flags & 0xFFFE;

                a6->pos_x =   1200.0 * a6->sec_x + 600.0;
                a6->pos_y = a6->p_cell->sector_height_meters;
                a6->pos_z = -(1200.0 * a6->sec_y + 600.0);
            }
            else
            {
                v16 = (_dxx % 4) - 1;
                v14 = 2 - ((_dzz % 4) - 1);

                if ( _dxx == _dx && _dzz == _dz )
                    v8 = flags & 0xFFFE;

                a6->pos_z = -(_dzz * 300.0);
                a6->pos_x = _dxx * 300.0;
                a6->pos_y = a6->p_cell->sector_height_meters;
            }

            a6->field_1E = v8;

            int model_id = yw->secTypes[a6->p_cell->sec_type].buildings[v16][v14]->health_models [   yw->build_hp_ref[    a6->p_cell->buildings_health[v16][v14]    ]    ];

            if ( v8 & 1 )
                a6->sklt = yw->legos[model_id].selected_sklt_intern;
            else
                a6->sklt = yw->legos[model_id].sklt_obj_intern;
        }
        else
        {
            a6->pos_y = 0;
            a6->pos_x = _dxx * 300.0;
            a6->pos_z = -(_dzz * 300.0);

            if ( _dxx == _dx && _dzz == _dz )
                v8 = flags & 0xFE;

            a6->field_1E = v8;

            if ( _dxx % 4 == 0 && _dzz % 4 == 0)
            {
                a6->sklt = yw->ColCross.skeleton_internal;
                a6->field_1C = 4;
            }
            else if ( _dxx % 4 == 0 && _dzz % 4 != 0 )
            {
                a6->sklt = yw->ColSide.skeleton_internal;
                a6->field_1C = 2;
            }
            else if ( _dxx % 4 != 0 && _dzz % 4 == 0 )
            {
                a6->sklt = yw->ColSide.skeleton_internal;
                a6->field_1C = 3;
            }
        }

        if ( a6->field_1C && !a6->sklt )
        {
            ypa_log_out("yw_GetSklt: WARNING, not CZT_INVALID, but Sklt NULL!\n");

            const char *v17 = "UNKNOWN";

            switch ( a6->field_1C )
            {
            case 4:
                v17 = "czt_cross_slurp";
                break;
            case 2:
                v17 = "czt_vside_slurp";
                break;
            case 3:
                v17 = "czt_hside_slurp";
                break;
            case 1:
                v17 = "czt_lego";
                break;
            default:
                break;
            }
            ypa_log_out("    Type=%s, sec_x=%d, sec_y=%d.\n", v17, a6->sec_x, a6->sec_y);

            a6->field_1C = 0;
        }
    }
}

void sub_44DF60(skeleton_64_stru *arg, int id)
{
    int16_t *vtx = &arg->pol_entries[id]->v1;

    pol_entries2 *triangle = &arg->triangles[id];

    int vtx1 = vtx[0];
    int vtx2 = vtx[1];
    int vtx3 = vtx[2];

    float sy1 = arg->POO[vtx2].pos3f.sy - arg->POO[vtx1].pos3f.sy;
    float sz1 = arg->POO[vtx2].pos3f.sz - arg->POO[vtx1].pos3f.sz;
    float sx1 = arg->POO[vtx2].pos3f.sx - arg->POO[vtx1].pos3f.sx;
    float sz2 = arg->POO[vtx3].pos3f.sz - arg->POO[vtx2].pos3f.sz;
    float sx2 = arg->POO[vtx3].pos3f.sx - arg->POO[vtx2].pos3f.sx;
    float sy2 = arg->POO[vtx3].pos3f.sy - arg->POO[vtx2].pos3f.sy;

    triangle->field_4 = sx2 * sz1 - sx1 * sz2;
    triangle->field_0 = sy1 * sz2 - sy2 * sz1;
    triangle->field_8 = sx1 * sy2 - sx2 * sy1;

    float v28 = sqrt((triangle->field_4 * triangle->field_4) + (triangle->field_0 * triangle->field_0) + (triangle->field_8 * triangle->field_8));

    if (v28 != 0.0)
    {
        triangle->field_0 = triangle->field_0 / v28;
        triangle->field_4 = triangle->field_4 / v28;
        triangle->field_8 = triangle->field_8 / v28;
    }
    triangle->field_C = -(triangle->field_4 * arg->POO[vtx1].pos3f.sy + triangle->field_0 * arg->POO[vtx1].pos3f.sx + triangle->field_8 * arg->POO[vtx1].pos3f.sz);
}

void sub_44E07C(_NC_STACK_ypaworld *yw, struct_44dbf8 *arg)
{
    if ( arg->field_1C == 2 )
    {
        cellArea *cur = arg->p_cell;
        cellArea *left = arg->p_cell - 1;

        if ( !(arg->field_1E & 1) || fabs( (int)(cur->sector_height_meters - left->sector_height_meters)) < 500.0 )
        {

            arg->sklt->POO[0].pos3f.sy = left->sector_height_meters;
            arg->sklt->POO[1].pos3f.sy = cur->sector_height_meters;
            arg->sklt->POO[2].pos3f.sy = cur->sector_height_meters;
            arg->sklt->POO[3].pos3f.sy = left->sector_height_meters;

            sub_44DF60(arg->sklt, 0);
        }
        else
        {
            arg->sklt = yw->colsub_sklt_intrn;

            if ( cur->sector_height_meters > left->sector_height_meters )
                arg->pos_y = cur->sector_height_meters;
            else
                arg->pos_y = left->sector_height_meters;
        }
    }
    else if ( arg->field_1C == 3 )
    {
        cellArea *cur = arg->p_cell;
        cellArea *up = arg->p_cell - yw->sectors_maxX2;

        if ( !(arg->field_1E & 1) || fabs( (int)(cur->sector_height_meters - up->sector_height_meters)) < 500.0 )
        {
            arg->sklt->POO[0].pos3f.sy = up->sector_height_meters;
            arg->sklt->POO[1].pos3f.sy = up->sector_height_meters;
            arg->sklt->POO[2].pos3f.sy = cur->sector_height_meters;
            arg->sklt->POO[3].pos3f.sy = cur->sector_height_meters;

            sub_44DF60(arg->sklt, 0);
        }
        else
        {
            arg->sklt = yw->colsub_sklt_intrn;

            if ( cur->sector_height_meters > up->sector_height_meters )
                arg->pos_y = cur->sector_height_meters;
            else
                arg->pos_y = up->sector_height_meters;
        }
    }
    else if ( arg->field_1C == 4 )
    {

        int kk = 0;

        cellArea *cur = arg->p_cell;
        cellArea *left = arg->p_cell - 1;
        cellArea *up = arg->p_cell - yw->sectors_maxX2;
        cellArea *leftup = arg->p_cell - yw->sectors_maxX2 - 1;

        if ( arg->field_1E & 1 )
        {
            float cs = cur->sector_height_meters;
            float ls = left->sector_height_meters;
            float us = up->sector_height_meters;
            float lus = leftup->sector_height_meters;

            float v15, v16, v17, v18;

            if ( cs >= ls )
                v15 = ls;
            else
                v15 = cs;

            if ( us >= lus )
                v16 = lus;
            else
                v16 = us;

            if ( v15 < v16 )
                v16 = v15;

            if ( cs <= ls )
                v17 = ls;
            else
                v17 = cs;

            if ( us <= lus )
                v18 = lus;
            else
                v18 = us;

            if ( v17 > v18 )
                v18 = v17;

            if ( fabs( (int)(v18 - v16) ) > 300.0 )
            {
                arg->sklt = yw->colsub_sklt_intrn;
                arg->pos_y = v18;
                kk = 1;
            }
        }
        if ( !kk )
        {
            arg->sklt->POO[0].pos3f.sy = leftup->sector_height_meters;
            arg->sklt->POO[1].pos3f.sy = up->sector_height_meters;
            arg->sklt->POO[2].pos3f.sy = cur->sector_height_meters;
            arg->sklt->POO[3].pos3f.sy = left->sector_height_meters;
            arg->sklt->POO[4].pos3f.sy = cur->smooth_height;

            sub_44DF60(arg->sklt, 0);
            sub_44DF60(arg->sklt, 1);
            sub_44DF60(arg->sklt, 2);
            sub_44DF60(arg->sklt, 3);
        }
    }
}

int sub_44D36C(float dx, float dy, float dz, int id, skeleton_64_stru *sklt)
{
    pol_entries2 *triangle = &sklt->triangles[id];

    int v7 = 0;

    float v24 = fabs(triangle->field_0);
    float v23 = fabs(triangle->field_4);
    float v27 = fabs(triangle->field_8);

    float v9 = (v24 <= v23 ? v23 : v24 );
    v9 = (v9 <= v27 ? v27 : v9);

    if ( v9 == v24 )
    {
        int prev = sklt->pol_entries[id]->num_vertices - 1;

        for (int i = 0; i < sklt->pol_entries[id]->num_vertices; i++)
        {
            int16_t *vtx = &sklt->pol_entries[id]->v1;

            skeleton_type1 *v12 = &sklt->POO[ vtx[i] ];
            skeleton_type1 *v13 = &sklt->POO[ vtx[prev] ];

            if ( ( (v13->pos3f.sz <= dz && dz < v12->pos3f.sz) ||
                    (v12->pos3f.sz <= dz && dz < v13->pos3f.sz) ) &&
                    v13->pos3f.sy + (v12->pos3f.sy - v13->pos3f.sy) * (dz - v13->pos3f.sz) / (v12->pos3f.sz - v13->pos3f.sz) > dy )
            {
                v7 = v7 == 0;
            }

            prev = i;
        }
    }
    else if ( v9 == v23 )
    {
        int prev = sklt->pol_entries[id]->num_vertices - 1;

        for (int i = 0; i < sklt->pol_entries[id]->num_vertices; i++)
        {
            int16_t *vtx = &sklt->pol_entries[id]->v1;

            skeleton_type1 *v12 = &sklt->POO[ vtx[i] ];
            skeleton_type1 *v13 = &sklt->POO[ vtx[prev] ];

            if ( ( (v13->pos3f.sz <= dz && dz < v12->pos3f.sz) ||
                    (v12->pos3f.sz <= dz && dz < v13->pos3f.sz) ) &&
                    v13->pos3f.sx + (v12->pos3f.sx - v13->pos3f.sx) * (dz - v13->pos3f.sz) / (v12->pos3f.sz - v13->pos3f.sz) > dx )
            {
                v7 = v7 == 0;
            }

            prev = i;
        }
    }
    else if ( v9 == v27 )
    {
        int prev = sklt->pol_entries[id]->num_vertices - 1;

        for (int i = 0; i < sklt->pol_entries[id]->num_vertices; i++)
        {
            int16_t *vtx = &sklt->pol_entries[id]->v1;

            skeleton_type1 *v12 = &sklt->POO[ vtx[i] ];
            skeleton_type1 *v13 = &sklt->POO[ vtx[prev] ];

            if ( ( (v13->pos3f.sy <= dy && dy < v12->pos3f.sy) ||
                    (v12->pos3f.sy <= dy && dy < v13->pos3f.sy) ) &&
                    v13->pos3f.sx + (v12->pos3f.sx - v13->pos3f.sx) * (dy - v13->pos3f.sy) / (v12->pos3f.sy - v13->pos3f.sy) > dx )
            {
                v7 = v7 == 0;
            }

            prev = i;
        }
    }
    return v7;
}

void sub_44D8B8(ypaworld_arg136 *arg, struct_44dbf8 *loc)
{
    for ( int i = 0; i < loc->sklt->pol_count; i++)
    {
        pol_entries2 *triangle = &loc->sklt->triangles[i];

        float v11 = triangle->field_4 * arg->field_18 + triangle->field_0 * arg->field_14 + triangle->field_8 * arg->field_1C;
        if ( v11 > 0.0 )
        {
            float v19 = -(triangle->field_4 * arg->pos_y + triangle->field_0 * arg->pos_x + triangle->field_8 * arg->pos_z + triangle->field_C) / v11;
            if ( v19 > 0.0 && v19 <= 1.0 && v19 < arg->field_24 )
            {
                float pz = arg->field_1C * v19 + arg->pos_z;
                float py = arg->field_18 * v19 + arg->pos_y;
                float px = arg->field_14 * v19 + arg->pos_x;

                if ( sub_44D36C(px, py, pz, i, loc->sklt) )
                {
                    arg->field_20 = 1;
                    arg->field_24 = v19;
                    arg->field_2C = loc->pos_x + px;
                    arg->field_30 = loc->pos_y + py;
                    arg->field_34 = loc->pos_z + pz;
                    arg->field_38 = i;
                    arg->field_3C = loc->sklt;
                }
            }
        }
    }
}


void ypaworld_func2__sub0__sub0(_NC_STACK_ypaworld *yw)
{
    if ( !yw->field_739A || (!(yw->field_73CE & 4) && !(yw->field_73CE & 8)) )
    {
        if ( yw->field_1b84 )
        {
            yw->field_7562 = yw->field_1614;

            winp_71arg winp71;
            winp71.effID = 0;
            winp71.state = 1;
            winp71.p4 = 0;
            winp71.p3 = 0;
            winp71.p2 = 0;
            winp71.p1 = 0;

            input__func66__params arg66;

            if ( yw->input_class )
            {
                arg66.field_0 = 1;
                arg66.funcID = 71;
                arg66.field_4 = 0;
                arg66.vals = &winp71;

                call_method(yw->input_class, 66, &arg66);
            }

            int v2;
            float v13;
            float v14;
            float v15;
            float v16;
            float v17;
            float v18;
            float v19;
            float v22;
            float v24;
            float v25;


            switch ( yw->field_1b84->field_24 )
            {
            case 1:
                v2 = 3;
                v16 = 300.0;
                v13 = 800.0;
                v15 = 1.0;
                v14 = 2.0;
                v25 = 1.0;
                v18 = 0.0;
                v17 = 0.7;
                v24 = 0.3;
                v22 = 1.0;
                v19 = 0.5;
                break;

            case 2:
            case 8:
                v2 = 1;
                v16 = 200.0;
                v13 = 500.0;
                v15 = 0.6;
                v14 = 1.0;
                v25 = 1.0;
                v22 = 1.0;
                v17 = 0.1;
                v24 = 0.3;
                v19 = 0.4;
                v18 = 0.0;
                break;

            case 6:
                v2 = 2;
                v16 = 200.0;
                v13 = 500.0;
                v15 = 1.0;
                v14 = 2.0;
                v25 = 1.0;
                v18 = 0.0;
                v17 = 0.1;
                v24 = 0.3;
                v22 = 1.0;
                v19 = 0.75;
                break;

            default:
                v2 = -1;
                break;
            }

            if ( v2 != -1 )
            {
                float v4 = (yw->field_1b84->mass - v16) / (v13 - v16);
                float v5 = (yw->field_1b84->maxrot - v15) / (v14 - v15);

                float v21 = (v19 - v24) * v4 + v24;
                float v23 = (v18 - v22) * v4 + v22;

                float v20 = (v17 - v25) * v5 + v25;

                if ( v21 < v24)
                    v21 = v24;
                else if (v21 > v19)
                    v21 = v19;

                if ( v23 < v18 )
                    v23 = v18;
                else if ( v23 > v22)
                    v23 = v22;

                if ( v20 < v17)
                    v20 = v17;
                else if ( v20 > v25)
                    v20 = v25;

                yw->field_7566 = v2;
                yw->field_756A = v23;
                yw->field_756E = v21;

                winp71.effID = v2;
                winp71.p1 = v21;
                winp71.state = 0;
                winp71.p2 = v23;

                winp71.p4 = 0;
                winp71.p3 = 0;

                if ( yw->input_class )
                {
                    arg66.field_4 = 0;
                    arg66.field_0 = 1;
                    arg66.vals = &winp71;
                    arg66.funcID = 71;

                    call_method(yw->input_class, 66, &arg66);
                }

                winp71.state = 0;
                winp71.p1 = v20;
                winp71.p4 = 0;
                winp71.p3 = 0;
                winp71.p2 = 0;
                winp71.effID = 4;

                if ( yw->input_class )
                {
                    arg66.field_4 = 0;
                    arg66.field_0 = 1;
                    arg66.funcID = 71;
                    arg66.vals = &winp71;
                    call_method(yw->input_class, 66, &arg66);
                }
            }
        }
    }
}




NC_STACK_ypabact *yw_createUnit(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, int model_id)
{
    const char *unit_classes_names [11] =
    {
        "dummy.class",      // 0
        "ypabact.class",    // 1
        "ypatank.class",    // 2
        "yparobo.class",    // 3
        "ypamissile.class", // 4
        "ypazepp.class",    // 5
        "ypaflyer.class",   // 6
        "ypaufo.class",     // 7
        "ypacar.class",     // 8
        "ypagun.class",     // 9
        "ypahovercraft.class" //10
    };

    NC_STACK_ypabact *bacto = NULL;
    __NC_STACK_ypabact *bact = NULL;

    // Find dead units
    bact_node *node = (bact_node *)yw->dead_cache.head;

    while (node->next)
    {
        if (node->bact->field_24 == model_id)
        {
            bacto = node->bact->self;
            bact = node->bact;
            break;
        }

        node = (bact_node *)node->next;
    }

    if ( !bacto )
    {
        bacto = (NC_STACK_ypabact *)init_get_class(unit_classes_names[model_id], 0x80001001, ywo, 0);

        if ( !bacto )
            return NULL;

        call_vtbl(bacto, 3, 0x80001003, &bact, 0);
    }

    call_method(bacto, 96, 0); // Reset bact

    bact->ypabact__id = bact_id;
    bact->owner = 0;

    bact->field_651.m00 = 1.0;    // 1.0
    bact->field_651.m01 = 0;
    bact->field_651.m02 = 0;
    bact->field_651.m10 = 0;
    bact->field_651.m11 = 1.0;    // 1.0
    bact->field_651.m12 = 0;
    bact->field_651.m20 = 0;
    bact->field_651.m21 = 0;
    bact->field_651.m22 = 1.0;    // 1.0

    bact_id++;

    return bacto;
}


void sub_44BF34(vhclSndFX *sndfx)
{
    char rsr[256];

    if ( !sndfx->wavs[0] && !sndfx->single_sample )
    {
        strcpy(rsr, get_prefix_replacement("rsrc"));

        set_prefix_replacement("rsrc", "data:");

        if ( sndfx->extS.cnt )
        {
            for (int i = 0; i < sndfx->extS.cnt; i++)
            {
                sndfx->wavs[i] = (NC_STACK_wav *)init_get_class("wav.class", 0x80001000, sndfx->extSampleNames[i], 0);

                if ( sndfx->wavs[i] )
                {
                    sampl *sample;
                    call_vtbl(sndfx->wavs[i], 3, 0x80002000, &sample, 0);

                    sndfx->extS.sndExts[i].sample = sample;
                    sndfx->extS.sndExts[i].field_14 = sample->SampleRate * sndfx->extS.sndExts[i].field_C / 11000;
                    sndfx->extS.sndExts[i].field_18 = sample->SampleRate * sndfx->extS.sndExts[i].field_10 / 11000;

                    if ( sndfx->extS.sndExts[i].field_14 > sample->bufsz )
                        sndfx->extS.sndExts[i].field_14 = sample->bufsz;

                    if ( !sndfx->extS.sndExts[i].field_18 )
                        sndfx->extS.sndExts[i].field_18 = sample->bufsz;

                    if ( sndfx->extS.sndExts[i].field_18 + sndfx->extS.sndExts[i].field_14 > sample->bufsz )
                        sndfx->extS.sndExts[i].field_18 = sample->bufsz - sndfx->extS.sndExts[i].field_14;
                }
                else
                {
                    ypa_log_out("Warning: Could not load sample %s.\n", sndfx->extSampleNames[i]);
                }
            }
        }
        else if ( sndfx->sample_name[0] )
        {
            sndfx->single_sample = (NC_STACK_wav *)init_get_class("wav.class", 0x80001000, sndfx->sample_name, 0);

            if ( !sndfx->single_sample )
                ypa_log_out("Warning: Could not load sample %s.\n", sndfx->sample_name);
        }

        set_prefix_replacement("rsrc", rsr);
    }
}


void sub_4D7F60(_NC_STACK_ypaworld *yw, int x, int y, stru_a3 *sct, base77Func *bs77)
{
    sct->dword8 = 0;
    sct->dword4 = 0;

    if ( x >= 0  &&  x < yw->sectors_maxX2  &&  y >= 0  &&  y < yw->sectors_maxY2 )
    {
        sct->dword4 = 1;
        sct->p_cell = yw->cells + x + yw->sectors_maxX2 * y;
        sct->smooth_height = sct->p_cell->smooth_height;

        flag_xyz grp_1;
        grp_1.flag = 7;
        grp_1.x = x * 1200.0 + 600.0;
        grp_1.z = -(y * 1200.0 + 600.0);
        grp_1.y = sct->p_cell->sector_height_meters;

        sct->x = grp_1.x;
        sct->y = grp_1.y;
        sct->z = grp_1.z;

        call_method(yw->additionalBeeBox, 68, &grp_1);

        if ( call_method(yw->additionalBeeBox, 77, bs77) )
        {
            sct->dword8 = 1;
        }
    }
}

void sub_4D806C(_NC_STACK_ypaworld *yw, stru_a3 *sct, base77Func *bs77)
{
    if ( sct->dword8 )
    {
        cellArea *pcell = sct->p_cell;

        flag_xyz grp_1;
        grp_1.flag = 7;
        grp_1.x = sct->x;
        grp_1.y = sct->y;
        grp_1.z = sct->z;

        int v22 = 0;

        flag_xyz scel;

        if ( pcell->field_3A == 1 )
        {
            yw_f80 *v5 = &yw->field_80[ pcell->field_3B ];

            scel.flag = 2;
            scel.y = (float)v5->field_4 / (float)v5->field_8;

            pcell->sec_type = yw->BuildProtos[ v5->blg_ID ].sec_type;
            pcell->field_2E = yw->secTypes[ pcell->sec_type ].field_0;

            v22 = 1;
        }

        int v17, v20;

        if ( pcell->field_2E == 1 )
        {
            v17 = 0;
            v20 = 1;
        }
        else
        {
            v17 = -1;
            v20 = 3;
        }

        for (int zz = 0; zz < v20; zz++)
        {
            for (int xx = 0; xx < v20; xx++)
            {
                grp_1.x = (v17 + xx) * 300.0 + sct->x;
                grp_1.z = (v17 + zz) * 300.0 + sct->z;

                if ( v22 )
                {
                    NC_STACK_base *bld = yw->legos[ yw->secTypes[ pcell->sec_type ].buildings[xx][zz]->health_models[0] ].base;

                    call_vtbl(bld, 2, 0x80001024, 0, 0);

                    call_method(bld, 72, &scel);
                    call_method(bld, 68, &grp_1);
                    call_method(bld, 77, bs77);

                    call_vtbl(bld, 2, 0x80001024, 1, 0);
                }
                else
                {
                    NC_STACK_base *bld = yw->legos[ yw->secTypes[ pcell->sec_type ].buildings[xx][zz]->health_models[ yw->build_hp_ref[ pcell->buildings_health[xx][zz] ] ] ].base;

                    call_method(bld, 68, &grp_1);
                    call_method(bld, 77, bs77);
                }
            }
        }
    }

    __NC_STACK_ypabact *bact = (__NC_STACK_ypabact *)sct->p_cell->field_3C.head;

    while ( bact->next )
    {
        if ( sct->dword8 || bact->field_24 == 3)
            call_method(bact->self, 66, bs77);

        bact = (__NC_STACK_ypabact *)bact->next;
    }
}

void yw_renderSky(_NC_STACK_ypaworld *yw, base77Func *rndr_params)
{
    if ( yw->sky_loaded_base )
    {
        float v6 = rndr_params->field_24;
        flag_xyz v5;
        v5.x = yw->current_bact->field_621.sx;
        v5.y = yw->field_15f4 + yw->current_bact->field_621.sy;
        v5.z = yw->current_bact->field_621.sz;
        v5.flag = 7;

        call_method(yw->sky_loaded_base, 68, &v5);

        rndr_params->field_24 = 32000.0;

        call_method(yw->sky_loaded_base, 77, rndr_params);

        rndr_params->field_24 = v6;
    }
}


int sb_0x4d7c08__sub1__sub0__sub0(_NC_STACK_ypaworld *yw, float xx, float yy)
{
    int v7 = ((xx + 150) / 300) / 4;
    int v8 = ((-yy + 150) / 300) / 4;

    if ( v7 <= 0 || v7 >= yw->sectors_maxX2 || v8 <= 0 || v8 >= yw->sectors_maxY2 || !yw->current_bact )
        return 0;

    int v11 = abs(yw->current_bact->field_c - v7);
    int v12 = abs(yw->current_bact->field_10 - v8);

    if ( v11 + v12 <= (yw->field_1368 - 1) / 2 )
        return 1;

    return 0;
}

void sb_0x4d7c08__sub1__sub0(_NC_STACK_ypaworld *yw, float xx, float yy, float posx, float posy, base77Func *arg)
{
    if ( yw->superbomb_wall_vproto )
    {
        if ( xx > 0.0 && yy < 0.0 && xx < yw->map_Width_meters && -yw->map_Height_meters < yy )
        {
            if ( sb_0x4d7c08__sub1__sub0__sub0(yw, xx, yy) )
            {
                int v10 = yw->VhclProtos[yw->superbomb_wall_vproto].vp_normal;

                NC_STACK_base *wall_base = yw->vhcls_models[v10].base;
                base_1c_struct *wall_trigo = yw->vhcls_models[v10].trigo;

                if ( wall_base && wall_trigo )
                {
                    float v28 = 0.0;

                    int v23 = (xx + 150) / 300;
                    int v26 = (-yy + 150) / 300;

                    if ( (v23 & 3) && (v26 & 3) )
                    {
                        v28 = yw->cells[ (v26 / 4) * yw->sectors_maxX2 + (v23 / 4) ].sector_height_meters;
                    }
                    else
                    {
                        ypaworld_arg136 v22;
                        v22.field_14 = 0;
                        v22.field_18 = 50000.0;
                        v22.field_1C = 0;
                        v22.pos_x = xx;
                        v22.pos_y = -25000.0;
                        v22.pos_z = yy;
                        v22.field_40 = 0;

                        call_method(yw->self_full, 136, &v22);

                        if ( v22.field_20 )
                        {
                            v28 = v22.field_30;
                        }
                    }


                    wall_trigo->grp_1.sx = xx;
                    wall_trigo->grp_1.sy = v28;
                    wall_trigo->grp_1.sz = yy;

                    float v29 = xx - posx;
                    float v30 = yy - posy;

                    float v27 = sqrt( POW2(v29) + POW2(v30) );
                    if ( v27 > 0.0 )
                    {
                        v29 /= v27;
                        v30 /= v27;
                    }

                    wall_trigo->scale_rotation.m00 = v30;
                    wall_trigo->scale_rotation.m01 = 0;
                    wall_trigo->scale_rotation.m02 = -v29;
                    wall_trigo->scale_rotation.m10 = 0;
                    wall_trigo->scale_rotation.m11 = 1.0;
                    wall_trigo->scale_rotation.m12 = 0;
                    wall_trigo->scale_rotation.m20 = v29;
                    wall_trigo->scale_rotation.m21 = 0.0;
                    wall_trigo->scale_rotation.m22 = v30;

                    call_method(wall_base, 77, arg);
                }
            }
        }
    }
}

void sb_0x4d7c08__sub1(_NC_STACK_ypaworld *yw, base77Func *arg)
{
    // Render super items
    for (int i = 0; i < yw->field_2d90->supetItems_count; i++)
    {
        supetItemProto *supr = &yw->field_2d90->supetItems[i];

        if ( supr->field_4 == 3 )
        {
            float a4 = supr->sec_x * 1200.0 + 600.0;
            float a5 = -(supr->sec_y * 1200.0 + 600.0);


            float v14 = sqrt( POW2(yw->map_Width_meters) + POW2(yw->map_Height_meters) );

            if ( supr->field_104 > 300 && supr->field_104 < v14 )
            {
                float v17 = (2 * supr->field_104) * 3.1415 / 300.0;

                if ( v17 > 2.0 )
                {
                    float v9 = 6.283 / v17;

                    for (float j = 0.0; j < 6.283; j = j + v9 )
                    {
                        float v10 = supr->field_104;
                        float a3 = v10 * sin(j) + a5;
                        float a2 = v10 * cos(j) + a4;

                        sb_0x4d7c08__sub1__sub0(yw, a2, a3, a4, a5, arg);
                    }
                }
            }
        }
    }
}


NC_STACK_base * sb_0x4d7c08__sub3__sub0(_NC_STACK_ypaworld *yw, stru_a3 *sct, stru_a3 *sct2, float a4, float a5)
{
    if ( sct->dword4 != 1 || sct2->dword4 != 1 || (sct->dword8 != 1 && sct2->dword8 != 1) )
        return 0;

    int i = yw->secTypes[ sct->p_cell->sec_type ].field_1;
    int j = yw->secTypes[ sct2->p_cell->sec_type ].field_1;

    NC_STACK_base *bs = yw->slurps2[i][j].skeletons_bas;
    skeleton_64_stru *skel = yw->slurps2[i][j].skeleton_internal;

    flag_xyz grp_1;
    grp_1.flag = 5;
    grp_1.x = sct2->x;
    grp_1.z = sct2->z;

    call_method(bs, 68, &grp_1);

    for (int i = 0; i < 4; i++)
        skel->POO[i].pos3f.sy = sct->y;

    for (int i = 4; i < 8; i++)
        skel->POO[i].pos3f.sy = sct2->y;

    skel->POO[8].pos3f.sy = a5;
    skel->POO[9].pos3f.sy = a4;

    return bs;
}

NC_STACK_base * sb_0x4d7c08__sub3__sub1(_NC_STACK_ypaworld *yw, stru_a3 *sct, stru_a3 *sct2, float a4, float a5)
{
    if ( sct->dword4 != 1 || sct2->dword4 != 1 || (sct->dword8 != 1 && sct2->dword8 != 1) )
        return NULL;

    int i = yw->secTypes[ sct->p_cell->sec_type ].field_1;
    int j = yw->secTypes[ sct2->p_cell->sec_type ].field_1;

    NC_STACK_base *bs = yw->slurps1[i][j].skeletons_bas;
    skeleton_64_stru *skel = yw->slurps1[i][j].skeleton_internal;

    flag_xyz grp_1;
    grp_1.flag = 5;
    grp_1.x = sct2->x;
    grp_1.z = sct2->z;

    call_method(bs, 68, &grp_1);

    for (int i = 0; i < 4; i++)
        skel->POO[i].pos3f.sy = sct->y;

    for (int i = 4; i < 8; i++)
        skel->POO[i].pos3f.sy = sct2->y;

    skel->POO[8].pos3f.sy = a5;
    skel->POO[9].pos3f.sy = a4;

    return bs;
}




stru_a3 rendering_sectors[10][10];

void sb_0x4d7c08__sub3(_NC_STACK_ypaworld *yw, base77Func *arg)
{
    //Render empty sectors and modify landscape linking parts
    for (int i = 0; i < yw->field_1368; i++)
    {
        for (int j = 0; j < yw->field_1368 - 1; j++)
        {
            stru_a3 *sct = &rendering_sectors[j][i];
            stru_a3 *sct2 = &rendering_sectors[j + 1][i];

            float h = rendering_sectors[j + 1][i].smooth_height;
            float h2 = rendering_sectors[j + 1][i + 1].smooth_height;

            NC_STACK_base *bs = sb_0x4d7c08__sub3__sub0(yw, sct, sct2, h, h2);
            if ( bs )
                call_method(bs, 77, arg);
        }
    }

    for (int i = 0; i < yw->field_1368 - 1; i++)
    {
        for (int j = 0; j < yw->field_1368; j++)
        {
            stru_a3 *sct = &rendering_sectors[j][i];
            stru_a3 *sct2 = &rendering_sectors[j][i + 1];

            float h = rendering_sectors[j][i + 1].smooth_height;
            float h2 = rendering_sectors[j + 1][i + 1].smooth_height;

            NC_STACK_base *bs = sb_0x4d7c08__sub3__sub1(yw, sct, sct2, h, h2);
            if ( bs )
                call_method(bs, 77, arg);

        }
    }
}

void sb_0x4d7c08(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, base_64arg *bs64, int a2)
{
    if ( yw->current_bact )
    {
        base_1c_struct *v5 = sub_430A28();

        if ( v5 )
            sub_430A38(v5);

        base77Func rndrs;

        rndrs.field_0 = bs64->field_4;
        rndrs.field_4 = bs64->field_0;
        rndrs.field_14 = 0;
        rndrs.curOutPoly = p_outPolys;
        rndrs.field_18 = 2000;
        rndrs.polysData = p_polysdata;
        rndrs.field_1C = 1;
        rndrs.polysData_end = p_polysdata_end;

        rndrs.field_20 = 17.0;

        if ( dword_514EFC )
            rndrs.field_20 = 1.0;

        if ( yw->field_1368 == 5 )
            rndrs.field_24 = 1500.0;
        else
            rndrs.field_24 = 3500.0;

        int v6 = yw->field_1368 - 1;

        for (int j = 0; j < v6; j++)
        {
            for (int i = 0; i < v6; i++)
            {
                rendering_sectors[j][i].dword4 = 0;
                rendering_sectors[j][i].dword8 = 0;
            }
        }

        int v29 = v6 / 2;
        for (int i = 0; i <= v29; i++)
        {
            int v28 = v29 - i;

            for (int j = -i; j <= i; j++)
            {
                stru_a3 *sct = &rendering_sectors[v29 + j][v29 - v28];

                sub_4D7F60(yw, j + yw->current_bact->field_c, -v28 + yw->current_bact->field_10, sct, &rndrs);

                if ( sct->dword4 )
                    sub_4D806C(yw, sct, &rndrs);

            }

            if ( -v28 != v28 )
            {
                for (int j = -i; j <= i; j++)
                {
                    stru_a3 *sct = &rendering_sectors[v29 + j][v29 + v28];

                    sub_4D7F60(yw, j + yw->current_bact->field_c, v28 + yw->current_bact->field_10, sct, &rndrs);

                    if ( sct->dword4 )
                        sub_4D806C(yw, sct, &rndrs);
                }
            }
        }

        sb_0x4d7c08__sub3(yw, &rndrs);
        sb_0x4d7c08__sub1(yw, &rndrs);

        if ( yw->field_15f8 )
            yw_renderSky(yw, &rndrs);

        bs64->field_C = rndrs.field_14;

        yw->field_1B6A = rndrs.field_14;
        yw->field_1b6c = rndrs.curOutPoly - p_outPolys;

        if ( yw->field_1b6c > 1 && !dword_514EFC )
            qsort(p_outPolys, yw->field_1b6c, sizeof(polys), sub_4D7BFC);

        call_method(yw->win3d, 213, 0);

        for (int i = 0; i < yw->field_1b6c; i++)
        {
            polysDat *pol = p_outPolys[i].data;
            pol->render_func(&pol->datSub);
        }

        call_method(yw->win3d, 214, 0);

        if ( a2 )
        {
            call_method(yw->win3d, 215, 0);
            sb_0x4d7c08__sub0(yw);
            call_method(yw->win3d, 216, 0);
        }
    }
}


void sb_0x456384__sub0__sub0(_NC_STACK_ypaworld *yw)
{
    for( int y = 0; y < yw->sectors_maxY2; y++ )
    {
        for( int x = 0; x < yw->sectors_maxX2; x++ )
        {
            yw_f30 *f30 = &yw->field_30[y * 64 + x];
            cellArea *cell = &yw->cells[x + y * yw->sectors_maxX2];

            f30->field_1 = 0;
            f30->owner = cell->owner;

        }
    }

    yw->field_3c = 0;
}

int sb_0x456384__sub0(_NC_STACK_ypaworld *yw, int x, int y, int power)
{
    int v13 = 0;
    cellArea *cell = &yw->cells[x + y * yw->sectors_maxX2];

    int v7;
    for (v7 = 0; v7 < yw->field_38; v7++)
    {
        if ( !yw->field_34[v7].p_cell )
        {
            v13 = 1;
            break;
        }
    }

    if ( v7 >= 256 )
        return -1;

    if ( !v13 )
        yw->field_38 = v7 + 1;

    yw_field34 *v9 = &yw->field_34[v7];
    v9->x = x;
    v9->y = y;
    v9->power = power;
    v9->power_2 = power;
    v9->p_cell = cell;

    cell->field_3A = 2;
    cell->field_3B = v7;

    sb_0x456384__sub0__sub0(yw);

    return v7;
}


void sb_0x456384(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, int x, int y, int ownerid2, int blg_id, int a7)
{
    char v30[272];
    memset(v30, 0, 272);

    cellArea *cell = &yw->cells[ yw->sectors_maxX2 * y + x ];
    BuildProto *bld = &yw->BuildProtos[ blg_id ];
    secType *sectp = &yw->secTypes[ bld->sec_type ];

    int v43 = 1;

    NC_STACK_ypabact *robo = NULL;

    if ( x && y && yw->sectors_maxX2 - 1 != x && yw->sectors_maxY2 - 1 != y )
    {
        bitmap_intern *bitm_blg;
        call_vtbl(yw->blg_map, 3, 0x80002000, &bitm_blg, 0);

        uint8_t *tmp = (uint8_t *)bitm_blg->buffer + x + y * bitm_blg->width;
        *tmp = blg_id;

        bitmap_intern *bitm_typ;
        call_vtbl(yw->typ_map, 3, 0x80002000, &bitm_typ, 0);

        tmp = (uint8_t *)bitm_typ->buffer + x + y * bitm_typ->width;
        *tmp = bld->sec_type;

        cell->sec_type = bld->sec_type;
        cell->field_2F = 0;
        cell->field_3A = 3;
        cell->field_2E = sectp->field_0;
        cell->field_3B = blg_id;

        int v49;

        if ( sectp->field_0 == 1 )
        {
            memset(cell->buildings_health, 0, sizeof(cell->buildings_health));
            v49 = 1;
        }
        else
        {
            v49 = 3;
        }

        for (int i = 0; i < v49; i++)
        {
            for (int j = 0; j < v49; j++)
            {
                cell->buildings_health[i][j] = sectp->buildings[i][j]->build_health;
            }
        }

        if ( bld->model_id == 1 )
            sb_0x456384__sub0(yw, x, y, bld->power);

        sub_44F958(yw, cell, x, y, ownerid2);

        bact_node *node = (bact_node *)yw->bact_list.head;

        while(node->next)
        {
            if (node->bact->field_24 == 3 && node->bact->owner == ownerid2)
            {
                robo = node->bacto;
                break;
            }

            node = (bact_node *)node->next;
        }

        if ( yw->field_757E )
        {
            if ( robo != yw->field_1b78 )
                v43 = 0;
        }

        if ( !a7 )
        {
            if ( robo && v43 )
            {
                NC_STACK_ypagun *commander = NULL;

                int v39;
                call_vtbl(robo, 3, 0x80002007, &v39, 0);

                v39++;

                call_vtbl(robo, 2, 0x80002007, v39, 0);

                int v52 = 0;

                for (int i = 0; i < 8; i++)
                {
                    if ( !bld->sbacts[i].sbact_vehicle )
                        break;

                    ypaworld_arg146 v33;
                    v33.vehicle_id = bld->sbacts[i].sbact_vehicle;
                    v33.pos.sx = bld->sbacts[i].sbact_pos_x + x * 1200.0 + 600.0;
                    v33.pos.sy = bld->sbacts[i].sbact_pos_y;
                    v33.pos.sz = bld->sbacts[i].sbact_pos_z - (y * 1200.0 + 600.0);

                    NC_STACK_ypagun *gunn = (NC_STACK_ypagun *)call_method(ywo, 146, &v33);

                    if ( gunn )
                    {
                        __NC_STACK_ypabact *gbct;
                        call_vtbl(gunn, 3, 0x80001003, &gbct, 0);

                        gbct->owner = ownerid2;

                        gun_arg128 v32;
                        v32.field_0 = 0;
                        v32.dir.sx = bld->sbacts[i].sbact_dir_x;
                        v32.dir.sy = bld->sbacts[i].sbact_dir_y;
                        v32.dir.sz = bld->sbacts[i].sbact_dir_z;

                        call_method(gunn, 128, &v32);

                        bact_arg119 v34;
                        v34.field_0 = 4;
                        v34.field_8 = 0;
                        v34.field_4 = 0;

                        call_method(gunn, 119, &v34);

                        gbct->field_931 = 500;
                        gbct->field_67D.sx = 1.0;
                        gbct->field_67D.sy = 1.0;
                        gbct->field_67D.sz = 1.0;

                        gbct->field_32 = robo;
                        gbct->field_2E = v39;

                        if ( yw->field_757E )
                        {
                            gbct->ypabact__id |= ownerid2 << 24;
                            /**(_DWORD *)&v30[v52 + 16] = gbct->ypabact__id;
                            *(float *)&v30[v52 + 20] = bld->sbacts[i].sbact_dir_x;
                            *(float *)&v30[v52 + 24] = bld->sbacts[i].sbact_dir_y;
                            *(float *)&v30[v52 + 28] = bld->sbacts[i].sbact_dir_z;
                            *(float *)&v30[v52 + 32] = gbct->field_621.sx;
                            *(float *)&v30[v52 + 36] = gbct->field_621.sy;
                            *(float *)&v30[v52 + 40] = gbct->field_621.sz;
                            *(_WORD *)&v30[v52 + 44] = bld->sbacts[i].sbact_vehicle;*/
                        }

                        if ( commander )
                        {
                            call_method(commander, 72, gunn);
                        }
                        else
                        {
                            commander = gunn;

                            call_method(robo, 72, gunn);
                        }
                    }

                    v52 += 32;
                }
            }

            if ( yw->field_757E && v43 && robo )
            {
                /**(_DWORD *)v30 = 1013;
                *(_DWORD *)&v30[4] = yw->field_1614;
                v30[12] = ownerid2;*/

                yw_arg181 v31;
                v31.field_14 = 2;
                v31.field_10 = 0;
                v31.field_8 = yw->GameShell->callSIGN;
                v31.field_C = 1;
                v31.value = v30;
                v31.val_size = 272;
                v31.field_18 = 1;

                call_method(yw->self_full, 181, &v31);
            }
        }
    }
}

void ypaworld_func148__sub0(_NC_STACK_ypaworld *yw, int x, int y)
{
    __NC_STACK_ypabact *node = (__NC_STACK_ypabact *) yw->cells[yw->sectors_maxX2 * y + x].field_3C.head;

    while ( node->next )
    {
        int v5 = 0;

        if ( yw->field_757E )
        {
            if ( node->owner == yw->field_1b84->owner )
            {
                if ( node->field_3D5 != 2 && node->field_3D5 != 5 && node->field_3D5 != 4 )
                {
                    if ( node->field_24 == 9 )
                    {
                        int a4;
                        call_vtbl(node->self, 3, 0x80002006, &a4, 0);

                        if (!a4)
                            v5 = 1;
                    }
                }
            }
        }
        else
        {
            if ( node->field_3D5 != 2 && node->field_3D5 != 5 && node->field_3D5 != 4 )
            {
                if ( node->field_24 == 9 )
                {
                    int a4;
                    call_vtbl(node->self, 3, 0x80002006, &a4, 0);

                    if (!a4)
                        v5 = 1;
                }
            }
        }

        if ( v5 )
        {
            bact_arg84 v8;
            v8.energy = -22000000;
            v8.unit = NULL;

            call_method(node->self, 84, &v8);
        }

        node = (__NC_STACK_ypabact *)node->next;
    }
}

int ypaworld_func148__sub1(_NC_STACK_ypaworld *yw, int id, int a4, int x, int y, int ownerID2, char blg_ID)
{
    if ( id < 8 && !yw->field_80[id].field_0 && x && y && x != yw->sectors_maxX2 - 1 && y != yw->sectors_maxY2 - 1 )
    {
        yw->field_80[id].field_4 = 0;
        yw->field_80[id].field_0 = 1;
        yw->field_80[id].field_8 = a4;
        yw->field_80[id].x = x;
        yw->field_80[id].y = y;
        yw->field_80[id].ownerID2 = ownerID2;
        yw->field_80[id].blg_ID = blg_ID;

        cellArea *cell = &yw->cells[yw->sectors_maxX2 * y + x];
        cell->field_3A = 1;
        cell->field_3B = id;

        bact_node *node = (bact_node *)yw->bact_list.head;

        while (node->next)
        {
            if ( node->bact->field_24 == 3 && ownerID2 == node->bact->owner )
            {
                sub_423F74(&node->bact->field_5A, 11);
                break;
            }

            node = (bact_node *)node->next;
        }

        return 1;
    }

    return 0;
}

int ypaworld_func137__sub0__sub0(skeleton_64_stru *skl, int id, float x, float y, float z, float r, yw_137loc *out)
{
    int num = skl->pol_entries[id]->num_vertices;
    int16_t *v7 = &skl->pol_entries[id]->v1;

    xyz tmp;
    tmp.sx = 0.0;
    tmp.sy = 0.0;
    tmp.sz = 0.0;

    for (int i = 0; i < num; i++)
    {
        int16_t idd = v7[i];
        tmp.sx += skl->POO[ idd ].pos3f.sx;
        tmp.sy += skl->POO[ idd ].pos3f.sy;
        tmp.sz += skl->POO[ idd ].pos3f.sz;
    }

    float v19 = (float)num;

    float xx = tmp.sx / v19 - x;
    float yy = tmp.sy / v19 - y;
    float zz = tmp.sz / v19 - z;


    float v26 = sqrt(xx * xx + yy * yy + zz * zz);

    if ( v26 <= r )
        return 0;

    out->pos.sx = xx / v26 * r + x;
    out->pos.sy = yy / v26 * r + y;
    out->pos.sz = zz / v26 * r + z;

    return 1;
}

void ypaworld_func137__sub0(ypaworld_arg137 *arg, struct_44dbf8 *a2)
{
    float xx = arg->pos.sx;
    float yy = arg->pos.sy;
    float zz = arg->pos.sz;

    for (int i = 0; i < a2->sklt->pol_count; i++)
    {
        pol_entries2 *tria = &a2->sklt->triangles[i];

        float t0 = tria->field_0;
        float t1 = tria->field_4;
        float t2 = tria->field_8;

        float v9 = t0 * arg->pos2.sx + t1 * arg->pos2.sy + t2 * arg->pos2.sz;

        if ( v9 > 0.0 )
        {
            float v26 = -(t0 * xx + t1 * yy + t2 * zz + tria->field_C) / ((t0 * t0 + t1 * t1 + t2 * t2) * arg->radius);

            if ( v26 > 0.0 && v26 <= 1.0 )
            {
                float rd = arg->radius * v26;


                float tx = t0 * rd + xx;
                float ty = t1 * rd + yy;
                float tz = t2 * rd + zz;

                int v27 = 0;

                yw_137loc v18;

                if ( !ypaworld_func137__sub0__sub0(a2->sklt, i, tx, ty, tz, arg->radius, &v18) || sub_44D36C(v18.pos.sx, v18.pos.sy, v18.pos.sz, i, a2->sklt) )
                    v27 = 1;

                if ( v27 )
                {
                    if ( arg->coll_count < arg->coll_max )
                    {
                        int pos = arg->coll_count;

                        arg->collisions[pos].pos1.sx = a2->pos_x + tx;
                        arg->collisions[pos].pos1.sy = a2->pos_y + ty;
                        arg->collisions[pos].pos1.sz = a2->pos_z + tz;
                        arg->collisions[pos].pos2.sx = tria->field_0;
                        arg->collisions[pos].pos2.sy = tria->field_4;
                        arg->collisions[pos].pos2.sz = tria->field_8;
                        arg->collisions[pos].field_1C = tria->field_C;

                        arg->coll_count++;
                    }
                }
            }
        }
    }
}

__NC_STACK_ypabact * sub_48C244(NC_STACK_ypaworld *ywo, int a2, char owner)
{
    bact_node *robos = (bact_node *)ywo->stack__ypaworld.bact_list.head;
    while (robos->next)
    {
        if ( robos->bact->field_24 == 3 && robos->bact->owner == owner)
        {
            if ( robos->bact->field_2E == a2 )
            {
                if ( robos->bact->field_3D5 == 2 )
                    return NULL;
                else
                    return robos->bact;
            }
            else
            {
                bact_node *units = (bact_node *)robos->bact->list2.head;
                while (units->next)
                {

                    if ( units->bact->field_2E == a2 )
                    {
                        if ( units->bact->field_3D5 == 2 )
                            return NULL;
                        else
                            return units->bact;
                    }

                    units = (bact_node *)units->next;
                }
            }
        }

        robos = (bact_node *)robos->next;
    }

    return NULL;
}


void ypaworld_func64__sub20(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, int dtime)
{
    for(int i = 0; i < 8; i++)
    {
        if ( yw->field_80[i].field_0 )
        {
            yw->field_80[i].field_4 += dtime;

            if ( yw->field_80[i].field_4 >= yw->field_80[i].field_8 )
            {
                yw->field_80[i].field_0 = 0;

                int v8 = yw->field_80[i].y;
                int v10 = yw->field_80[i].x;

                cellArea * v11 = &yw->cells[v10 + v8 * yw->sectors_maxX2];

                int a6 = yw->field_80[i].blg_ID;

                v11->field_3A = 0;
                v11->field_3B = 0;

                sb_0x456384(ywo, yw, v10, v8, yw->field_80[i].ownerID2, a6, 0);

                if ( yw->field_80[i].ownerID2 == yw->field_1b80->owner )
                {
                    if ( yw->BuildProtos[a6].model_id )
                    {
                        yw_arg159 arg159;

                        arg159.unit = yw->field_1b80;
                        arg159.txt = 0;
                        arg159.field_4 = 65;

                        if ( yw->BuildProtos[a6].model_id == 1 )
                            arg159.field_C = 36;
                        else if ( yw->BuildProtos[a6].model_id == 2 )
                            arg159.field_C = 38;
                        else if ( yw->BuildProtos[a6].model_id == 3 )
                            arg159.field_C = 37;
                        else
                            arg159.field_C = 0;

                        call_method(ywo, 159, &arg159);
                    }
                }
            }
        }
    }
}

void ypaworld_func64__sub6__sub0(_NC_STACK_ypaworld *yw)
{
    for(int i = 0; i < 8; i++)
        yw->field_1bac[i] = 0;

    bact_node *robo_node = (bact_node *)yw->bact_list.head;

    while (robo_node->next)
    {
        if ( robo_node->bact->field_24 == 3 )
        {
            if ( robo_node->bact->field_3D5 != 2 &&  robo_node->bact->field_3D5 != 5 )
            {
                bact_node *comnd_node = (bact_node *)robo_node->bact->list2.head;

                while(comnd_node->next)
                {
                    if ( comnd_node->bact->field_3D5 != 2 && comnd_node->bact->field_3D5 != 5 )
                    {
                        int a4 = 0;

                        if ( comnd_node->bact->field_24 == 9 )
                            call_vtbl(comnd_node->bact->self, 3, 0x80002006, &a4, 0);

                        if ( a4 == 0 )
                        {
                            yw->field_1bac[ comnd_node->bact->owner ]++;


                            bact_node *unit_node = (bact_node *)comnd_node->bact->list2.head;

                            while( unit_node->next )
                            {
                                if ( unit_node->bact->field_3D5 != 2 && unit_node->bact->field_3D5 != 5 )
                                    yw->field_1bac[ unit_node->bact->owner ]++;

                                unit_node = (bact_node *)unit_node->next;
                            }
                        }
                    }

                    comnd_node = (bact_node *)comnd_node->next;
                }

            }
        }

        robo_node = (bact_node *)robo_node->next;
    }
}


void ypaworld_func64__sub6(_NC_STACK_ypaworld *yw)
{
    int v13[8];

    for (int i = 0; i < 8; i++)
        v13[i] = 0;

    for (int i = 0; i < yw->field_38; i++)
    {
        yw_field34 *v4 = &yw->field_34[i];

        if (v4->p_cell)
            v13[ v4->p_cell->owner ] += v4->power_2;
    }

    ypaworld_func64__sub6__sub0(yw);

    for (int i = 0; i < 8; i++)
    {
        v13[i] /= 2;

        if ( v13[i] <= 0 )
        {
            yw->field_1bec[i] = 0;
            yw->field_1bcc[i] = 0;
        }
        else
        {
            int v15 = yw->sectors_count_by_owner[i];

            if ( v15 < 0 )
                v15 = 0;

            yw->field_1bcc[i] = (float)v15 / (float)v13[i];
            yw->field_1bec[i] = (float)v15 / (float)v13[i];

            if ( yw->field_757E )
            {
                if ( yw->unit_limit_type_1 == 1 )
                {
                    int v16 = yw->field_1bac[yw->field_1b80->owner] - yw->unit_limit_1;

                    if ( v16 > 0 )
                    {
                        int v10 = (float)yw->unit_limit_arg_1 * 0.01 * (float)v16;

                        yw->field_1bcc[i] -= v10;
                        yw->field_1bec[i] -= v10;
                    }
                }
            }

            if ( yw->field_1bcc[i] >= 0.0 )
            {
                if ( yw->field_1bcc[i] > 1.0 )
                    yw->field_1bcc[i] = 1.0;
            }
            else
            {
                yw->field_1bcc[i] = 0;
            }

            if ( yw->field_1bec[i] < 0.0 )
                yw->field_1bec[i] = 0;
        }
    }
}


void ypaworld_func64__sub5__sub0(_NC_STACK_ypaworld *yw, int a2)
{
    yw_field34 *v3 = &yw->field_34[a2];

    int v7 = v3->power_2;
    int v10 = 0;

    while (v7 > 0)
    {
        v7 >>= 1;
        v10++;
    }

    int v9 = v3->power_2;

    int v11 = -v10;
    int v12 = v10 + 1;

    int v13 = -v10;
    int v21 = v10 + 1;

    if ( v3->x + v11 < 1 )
        v11 = 1 - v3->x;

    if ( v3->y + v13 < 1 )
        v13 = 1 - v3->y;

    if ( v3->x + v12 >= yw->sectors_maxX2 )
        v12 = yw->sectors_maxX2 - v3->x - 1;

    if ( v3->y + v21 >= yw->sectors_maxY2 )
        v21 = yw->sectors_maxY2 - v3->y - 1;

    for (int i = v13; i < v21; i++)
    {
        for (int j = v11; j < v12; j++)
        {
            int v17 = v9  >>  yw->sqrt_table[abs(j)][abs(i)];

            yw_f30 *v14 = &yw->field_30[j + v3->x + ((i + v3->y) * 64) ];

            if ( v14->owner == v3->p_cell->owner )
            {
                int v18 = v17 + v14->field_1; // Add power to this cell

                if ( v18 > 255 )
                    v18 = 255;

                v14->field_1 = v18;
            }

        }
    }
}

void ypaworld_func64__sub5(_NC_STACK_ypaworld *yw)
{
    // Recompute power on sectors
    if ( yw->field_38 ) // If we have powerstations
    {
        int v2 = yw->field_3c; // current power station

        while ( !yw->field_34[v2].p_cell && v2 < yw->field_38 ) //If current power station is null - go to first not null or to end
            v2++;

        if ( v2 < yw->field_38 ) // if we found any power station
        {
            if ( yw->field_34[v2].power_2 ) // if this power station has power
                ypaworld_func64__sub5__sub0(yw, v2); // Add power to power matrix

            yw->field_3c = v2 + 1; // go to next station in next update loop
        }
        else // If we reach end of power stations list, apply power to sectors
        {
            sub_44F748(yw); // Apply power to sectors and clean power matrix for next compute iteration.
        }
    }
}

int sub_47EDDC(yw_f726c *hist, int bufsize)
{
    yw_f726c_nod *node = (yw_f726c_nod *)AllocVec(16, 65537);

    if ( node )
    {
        node->bufStart = (uint8_t *)AllocVec(bufsize, 65537);
        if ( node->bufStart )
        {
            node->bufEnd = &node->bufStart[bufsize];

            AddTail(&hist->lst, node);

            hist->last_bufStart = node->bufStart;
            hist->last_bufEnd = node->bufEnd;
            hist->numNodes++;
            return 1;
        }
        else
        {
            nc_FreeMem(node);
        }
    }

    return 0;
}


void sub_4D12D8(_NC_STACK_ypaworld *yw, int id, int a3)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    sitem->field_4 = 1;
    sitem->field_F0 = 0;
    sitem->field_F4 = sitem->pcell->owner;

    if ( !a3 )
    {
        sitem->field_EC = yw->field_1614;
        sitem->field_FC = 0;
        sitem->field_100 = 0;
        sitem->field_F8 = sitem->countdown;
    }

    ypaworld_arg148 arg148;
    arg148.ownerID = sitem->pcell->owner;
    arg148.ownerID2 = sitem->pcell->owner;
    arg148.blg_ID = sitem->active_bp;
    arg148.field_C = 1;
    arg148.x = sitem->sec_x;
    arg148.y = sitem->sec_y;
    arg148.field_18 = 0;

    call_method(yw->self_full, 148, &arg148);

    sitem->pcell->field_3A = 8;
    sitem->pcell->field_3B = id;

    yw_arg159 arg159;
    arg159.unit = 0;
    arg159.field_4 = 94;

    if ( sitem->type == 1 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 250, "Superbomb activated.");
        arg159.field_C = 70;
    }
    else if ( sitem->type == 2 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 254, "Superwave activated.");
        arg159.field_C = 74;
    }
    else
    {
        arg159.field_C = 0;
        arg159.txt = "Cant happen.";
    }

    call_method(yw->self_full, 159, &arg159);
}

void sub_4D1594(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    sitem->field_4 = 2;

    ypaworld_arg148 arg148;
    arg148.ownerID = sitem->pcell->owner;
    arg148.ownerID2 = sitem->pcell->owner;
    arg148.blg_ID = sitem->inactive_bp;
    arg148.field_C = 1;
    arg148.x = sitem->sec_x;
    arg148.y = sitem->sec_y;
    arg148.field_18 = 0;

    call_method(yw->self_full, 148, &arg148);

    sitem->pcell->field_3A = 8;
    sitem->pcell->field_3B = id;

    yw_arg159 arg159;
    arg159.unit = 0;
    arg159.field_4 = 93;

    if ( sitem->type == 1 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 252, "Superbomb frozen.");
        arg159.field_C = 72;
    }
    else if ( sitem->type == 2 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 256, "Superwave frozen.");
        arg159.field_C = 76;
    }
    else
    {
        arg159.field_C = 0;
        arg159.txt = "Cant happen.";
    }

    call_method(yw->self_full, 159, &arg159);
}

void sub_4D1444(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];
    sitem->field_4 = 3;
    sitem->field_F0 = yw->field_1614;

    ypaworld_arg148 arg148;
    arg148.ownerID = sitem->pcell->owner;
    arg148.ownerID2 = sitem->pcell->owner;
    arg148.blg_ID = sitem->trigger_bp;
    arg148.field_C = 1;
    arg148.x = sitem->sec_x;
    arg148.y = sitem->sec_y;
    arg148.field_18 = 0;

    call_method(yw->self_full, 148, &arg148);

    sitem->pcell->field_3A = 8;
    sitem->pcell->field_3B = id;

    yw->field_2d90->supetItems[id].field_108 = 0;

    yw_arg159 arg159;
    arg159.field_4 = 95;
    arg159.unit = 0;

    if ( sitem->type == 1 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 251, "Superbomb triggered.");
        arg159.field_C = 71;
    }
    else if ( sitem->type == 2 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 255, "Superwave triggered.");
        arg159.field_C = 75;
    }
    else
    {
        arg159.field_C = 0;
        arg159.txt = "Cant happen.";
    }

    call_method(yw->self_full, 159, &arg159);
}


__NC_STACK_ypabact * sb_0x47b028__sub0(int bactid, _NC_STACK_ypaworld *yw)
{
    bact_node *station = (bact_node *)yw->bact_list.head;

    while ( station->next )
    {
        if ( bactid == station->bact->ypabact__id )
            return station->bact;

        bact_node *commander = (bact_node *)station->bact->list2.head;

        while ( commander->next )
        {
            if ( bactid == commander->bact->ypabact__id )
                return station->bact;

            bact_node *slave = (bact_node *)commander->bact->list2.head;

            while ( slave->next )
            {
                if ( bactid == slave->bact->ypabact__id )
                    return station->bact;

                slave = (bact_node *)slave->next;
            }

            commander = (bact_node *)commander->next;
        }

        station = (bact_node *)station->next;
    }

    return NULL;
}

void sb_0x47b028(_NC_STACK_ypaworld *yw, bact_node *bct1, bact_node *bct2, int a3)
{
    bact_arg80 arg80;
    arg80.pos = bct1->bact->field_621;

    if ( bct1->bact->field_24 == 9 )
        arg80.field_C = 4;
    else
        arg80.field_C = 0;

    call_method(bct1->bacto, 80, &arg80);

    if ( bct1->bact->field_24 == 9 )
    {
        NC_STACK_ypagun *guno = (NC_STACK_ypagun *)bct1->bacto;

        gun_arg128 arg128;
        arg128.dir = guno->stack__ypagun.dir;
        arg128.field_0 = 0;

        call_method(bct1->bacto, 128, &arg128);
    }

    bact_arg119 arg78;
    arg78.field_0 = bct1->bact->field_3D5;
    arg78.field_4 = 0;
    arg78.field_8 = 0;
    call_method(bct1->bacto, 78, &arg78);

    if ( bct1->bact->field_3D6 & 0x800 )
    {
        arg78.field_0 = 0;
        arg78.field_8 = 0;
        arg78.field_4 = 2048;
        call_method(bct1->bacto, 78, &arg78);
    }

    if ( bct1->bact->field_3D6 & 0x100 )
    {
        arg78.field_0 = 0;
        arg78.field_8 = 0;
        arg78.field_4 = 256;
        call_method(bct1->bacto, 78, &arg78);
    }

    if ( a3 )
    {
        if ( bct1->bact->owner == 1 )
            call_vtbl(yw->self_full, 2, 0x80002010, bct1->bacto, 0);
    }
    else
    {
        bct1->bact->field_32 = bct2->bacto;
        bct1->bact->owner = bct2->bact->owner;
    }

    if ( bct1->bact->field_3DE == 2 )
    {
        bct1->bact->field_3DE = 0;

        bact_arg67 arg67;
        arg67.field_8 = sb_0x47b028__sub0((int)bct1->bact->field_3e8, yw);
        arg67.field_0 = 6;
        arg67.field_4 = 0;
        call_method(bct1->bacto, 67, &arg67);
    }

    if ( bct1->bact->field_3DE == 1 )
    {
        bct1->bact->field_3DE = 0;

        bact_arg67 arg67_1;
        arg67_1.field_0 = 5;
        arg67_1.targ = bct1->bact->field_3ec;
        arg67_1.field_4 = 0;

        call_method(bct1->bacto, 67, &arg67_1);
    }
}


int ypaworld_func64__sub4(_NC_STACK_ypaworld *yw, base_64arg *arg)
{
    if ( yw->field_757E )
        return 0;

    if ( !yw->field_160c )
    {
        if ( arg->field_8->dword8 == 0xA0 || arg->field_8->downed_key == VK_PAUSE )
        {
            yw->field_160c = 1;
            yw->field_1610 = arg->field_0;
        }
        return 0;
    }

    if ( arg->field_8->downed_key )
    {
        yw->field_160c = 0;
        arg->field_0 = yw->field_1610;
    }
    else
    {
        call_method(yw->win3d, 257, 0);

        call_vtbl(yw->win3d, 2, 0x80003001, 0, 0);

        call_method(yw->win3d, 192, 0);

        xyz a2a;
        a2a.sx = yw->field_1334.sx;
        a2a.sy = yw->field_1334.sy + 50000.0;
        a2a.sz = yw->field_1334.sz;

        xyz a3;
        a3.sx = 0;
        a3.sy = 0;
        a3.sz = 0;

        mat3x3 a4;
        a4.m00 = 1.0;
        a4.m01 = 0;
        a4.m02 = 0;
        a4.m10 = 0;
        a4.m11 = 1.0;
        a4.m12 = 0;
        a4.m20 = 0;
        a4.m22 = 1.0;
        a4.m21 = 0;

        sub_423EFC(1, &a2a, &a3, &a4);

        if ( arg->field_0 / 500 & 1 )
        {
            const char *v6 = get_lang_string(yw->string_pointers_p2, 14, "*** GAME PAUSED, HIT KEY TO CONTINUE ***");

            char v10[256];
            char *pcur = v10;

            fntcmd_select_tileset(&pcur, 15);

            fntcmd_set_xpos(&pcur, 0);
            fntcmd_set_center_ypos(&pcur, -yw->font_default_h / 2);

            pcur = sub_45148C(yw->tiles[15], pcur, v6, yw->screen_width);

            fntcmd_set_end(&pcur);

            w3d_a209 arg209;
            arg209.includ = 0;
            arg209.cmdbuf = v10;

            call_method(yw->win3d, 215, 0);
            call_method(yw->win3d, 209, &arg209);
            call_method(yw->win3d, 216, 0);
        }

        sb_0x424c74();

        call_method(yw->win3d, 258, 0);
    }
    return 1;
}


void ypaworld_func64__sub2(_NC_STACK_ypaworld *yw)
{
    yw->field_1b70 = 0;

    if ( yw->field_1b78 != yw->field_1b7c )
    {
        roboGun *guns = NULL;
        call_vtbl(yw->field_1b78, 3, 0x8000200E, &guns, 0);

        if ( guns )
        {
            for (int i = 0; i < 8; i++)
            {
                if ( yw->field_1b7c == guns[i].gun_obj )
                    yw->field_1b70 = 1;
            }
        }
    }
}


void ypaworld_func64__sub9(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < yw->field_2d90->gate_count ; i++ )
    {
        gateProto *gate = &yw->field_2d90->gates[i];

        int v21 = 6;

        if ( gate->pcell->owner == yw->field_1b80->owner )
        {
            for(int j = 0; j < gate->keySectors_count; j++)
            {
                if (gate->keySectors[j].cell)
                {
                    if (gate->keySectors[j].cell->owner != yw->field_1b80->owner)
                    {
                        v21 = 5;
                        break;
                    }
                }
            }
        }
        else
        {
            v21 = 5;
        }

        if ( gate->pcell->field_3A != v21 )
        {
            ypaworld_arg148 arg148;
            arg148.ownerID = gate->pcell->owner;
            arg148.ownerID2 = gate->pcell->owner;
            arg148.field_C = 1;
            arg148.x = gate->sec_x;
            arg148.y = gate->sec_y;
            arg148.field_18 = 0;

            if ( v21 == 6 )
            {
                arg148.blg_ID = gate->opened_bp;
            }
            else
            {
                arg148.blg_ID = gate->closed_bp;

                yw_arg159 arg159;
                arg159.unit = 0;
                arg159.field_4 = 65;
                arg159.txt = get_lang_string(yw->string_pointers_p2, 224, "TRANSPORTER GATE CLOSED!");
                arg159.field_C = 24;

                call_method(yw->self_full, 159, &arg159);
            }

            call_method(yw->self_full, 148, &arg148);

            gate->pcell->field_3A = v21;
            gate->pcell->field_3B = i;
        }

        if ( v21 == 6 )
        {
            int energ = 0;

            __NC_STACK_ypabact *v8 = (__NC_STACK_ypabact *)gate->pcell->field_3C.head;
            while (v8->next)
            {
                if ( v8->field_3D5 != 2 && v8->field_3D5 != 5 )
                {
                    if ( v8->field_24 != 3 && v8->field_24 != 4 && v8->field_24 != 9 )
                        energ += (v8->energy_2 + 99) / 100;
                }
                v8 = (__NC_STACK_ypabact *)v8->next;
            }

            if ( energ <= yw->beamenergy )
            {
                if ( yw->field_1614 - yw->field_1a00 > 60000 )
                {
                    yw_arg159 arg159_1;
                    arg159_1.unit = 0;
                    arg159_1.field_4 = 49;
                    arg159_1.txt = get_lang_string(yw->string_pointers_p2, 223, "TRANSPORTER GATE OPENED!");
                    arg159_1.field_C = 23;

                    call_method(yw->self_full, 159, &arg159_1);
                    yw->field_1a00 = yw->field_1614;
                }
            }
            else
            {
                if ( yw->field_1614 - yw->field_1a00 > 40000 )
                {
                    yw_arg159 arg159_2;
                    arg159_2.unit = 0;
                    arg159_2.field_4 = 10;
                    arg159_2.txt = get_lang_string(yw->string_pointers_p2, 258, "WARNING: BEAM GATE FULL!");
                    arg159_2.field_C = 46;

                    call_method(yw->self_full, 159, &arg159_2);
                    yw->field_1a00 = yw->field_1614;
                }
            }
        }
    }
}


int sub_4D11C0(_NC_STACK_ypaworld *yw, int id, int owner)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    if ( sitem->pcell->owner != owner )
        return 0;

    if ( !sitem->keySectors_count )
        return 1;

    for (int i = 0; i < sitem->keySectors_count; i++)
    {
        if ( sitem->keySectors[i].cell->owner != owner )
            return 0;
    }
    return 1;
}

int sub_4D12A0(_NC_STACK_ypaworld *yw, int owner)
{
    bact_node *bct = (bact_node *)yw->bact_list.head;

    while ( bct->next )
    {
        if ( bct->bact->field_24 == 3 && owner == bct->bact->owner )
            return 1;

        bct = (bact_node *)bct->next;
    }

    return 0;
}

void sub_4D16C4(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    sitem->field_4 = 0;
    sitem->field_EC = 0;
    sitem->field_F0 = 0;
    sitem->field_F4 = 0;
    sitem->field_F8 = 0;

    ypaworld_arg148 arg148;
    arg148.ownerID = sitem->pcell->owner;
    arg148.ownerID2 = sitem->pcell->owner;
    arg148.blg_ID = sitem->inactive_bp;
    arg148.field_C = 1;
    arg148.x = sitem->sec_x;
    arg148.y = sitem->sec_y;
    arg148.field_18 = 0;

    call_method(yw->self_full, 148, &arg148);

    sitem->pcell->field_3A = 8;
    sitem->pcell->field_3B = id;

    yw_arg159 arg159;
    arg159.unit = NULL;
    arg159.field_4 = 92;

    if ( sitem->type == 1 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 253, "Superbomb deactivated.");
        arg159.field_C = 73;
    }
    else if ( sitem->type == 2 )
    {
        arg159.txt = get_lang_string(yw->string_pointers_p2, 257, "Superwave deactivated.");
        arg159.field_C = 77;
    }
    else
    {
        arg159.field_C = 0;
        arg159.txt = "Cant happen.";
    }

    call_method(yw->self_full, 159, &arg159);
}

void ypaworld_func64__sub19__sub0(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    int v7 = 0;

    bact_node *v5 = (bact_node *)yw->bact_list.head;
    while(v5->next)
    {
        if ( v5->bact->field_24 == 3 && sitem->field_F4 == v5->bact->owner )
        {
            v7 = 1;
            break;
        }

        v5 = (bact_node *)v5->next;
    }

    if ( v7 )
    {
        if ( sub_4D11C0(yw, id, sitem->field_F4) )
        {
            if ( sitem->field_F8 > 0 )
                sitem->field_F8 = sitem->field_F8 - yw->field_1618;
            else
                sub_4D1444(yw, id);
        }
        else if ( sitem->keySectors_count )
        {
            sub_4D1594(yw, id);
        }
        else
        {
            sub_4D12D8(yw, id, 0);
        }
    }
    else
    {
        sub_4D16C4(yw, id);
    }
}


void ypaworld_func64__sub19__sub3(_NC_STACK_ypaworld *yw, int id)
{
    if ( yw->GameShell )
    {
        supetItemProto *sitem = &yw->field_2d90->supetItems[id];

        int v4 = sitem->field_F8 / 1024;

        if ( v4 < 10 && v4 != sitem->field_100 )
        {
            sub_423F74(&yw->GameShell->samples1_info, 3);
            sitem->field_100 = v4;
        }

        int v5 = v4 / 10;
        if ( v5 != sitem->field_FC )
        {
            sub_423F74(&yw->GameShell->samples1_info, 3);
            sitem->field_FC = v5;
        }
    }
}

int sub_4D1230(_NC_STACK_ypaworld *yw, int id, int a3)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    if ( sitem->pcell->owner == a3 )
        return 0;

    if ( !sitem->keySectors_count )
        return 1;

    for (int i = 0; i < sitem->keySectors_count; i++)
    {
        if (sitem->keySectors[i].cell->owner == a3)
            return 0;
    }

    return 1;
}

void ypaworld_func64__sub19__sub1(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    int v7 = 0;

    bact_node *bct = (bact_node *)yw->bact_list.head;
    while ( bct->next )
    {
        if ( bct->bact->field_24 == 3 && sitem->field_F4 == bct->bact->owner )
        {
            v7 = 1;
            break;
        }

        bct = (bact_node *)bct->next;
    }

    if ( !v7 )
        sub_4D16C4(yw, id);
    else
    {
        if ( sub_4D11C0(yw, id, sitem->field_F4) )
            sub_4D12D8(yw, id, 1);
        else if ( sub_4D1230(yw, id, sitem->field_F4) )
            sub_4D16C4(yw, id);
    }
}

void ypaworld_func64__sub19__sub2__sub0__sub0(_NC_STACK_ypaworld *yw, supetItemProto *sitem, float a5, float a6, float a7)
{
    int lastt = yw->sectors_maxY2 * yw->sectors_maxX2;

    for(int i = 0; i < lastt; i++)
    {
        cellArea *cell = &yw->cells[i];

        __NC_STACK_ypabact *bct = (__NC_STACK_ypabact *)cell->field_3C.head;

        while(bct->next)
        {
            int v9 = 1;

            if ( yw->field_757E )
            {
                if ( bct->owner != yw->field_1b84->owner || bct->owner == sitem->field_F4 || bct->field_3D5 == 2 )
                    v9 = 0;
            }
            else if ( bct->owner == sitem->field_F4 || bct->field_3D5 == 2 )
            {
                v9 = 0;
            }

            if ( v9 )
            {
                float v10 = a5 - bct->field_621.sx;
                float v11 = a6 - bct->field_621.sz;

                if ( sqrt(POW2(v10) + POW2(v11)) < a7 )
                {
                    bact_arg84 arg84;
                    arg84.energy = -22000000;
                    arg84.unit = 0;

                    call_method(bct->self, 84, &arg84);
                }
            }

            bct = (__NC_STACK_ypabact *)bct->next;
        }

    }
}

void ypaworld_func64__sub19__sub2__sub0(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    sitem->field_104 = (yw->field_1614 - sitem->field_F0) * 1200.0 / 2400.0;

    float a5 = sitem->sec_x * 1200.0 + 600.0;
    float a6 = -(sitem->sec_y * 1200.0 + 600.0);

    float v19 = sqrt(POW2(yw->map_Width_meters) + POW2(yw->map_Height_meters));

    if ( sitem->field_104 > 300 && sitem->field_104 - sitem->field_108 > 200 && sitem->field_104 < v19 )
    {
        float v9 = (2 * sitem->field_104) * 3.1415 / 150.0;

        sitem->field_108 = sitem->field_104;

        if ( v9 > 2.0 )
        {
            for (float v25 = 0.0; v25 < 6.283 ; v25 += 6.283 / v9 )
            {
                float v10 = sitem->field_104;
                float v26 = cos(v25) * v10 + a5;
                float v21 = sin(v25) * v10 + a6;

                if ( v26 > 600.0 && v21 < -600.0 && v26 < yw->map_Width_meters - 600.0 && v21 > -(yw->map_Height_meters - 600.0) )
                {
                    int v12 = yw->fxnumber;

                    yw->fxnumber = 2;

                    yw_arg129 arg129;
                    arg129.pos.sx = v26;
                    arg129.pos.sy = sitem->pcell->sector_height_meters;
                    arg129.pos.sz = v21;
                    arg129.field_10 = 200000;
                    arg129.field_14 = sitem->field_F4;
                    arg129.unit = 0;

                    call_method(yw->self_full, 129, &arg129);

                    yw->fxnumber = v12;
                }
            }
        }
    }

    ypaworld_func64__sub19__sub2__sub0__sub0(yw, sitem, a5, a6, sitem->field_104);
}

void ypaworld_func64__sub19__sub2(_NC_STACK_ypaworld *yw, int id)
{
    supetItemProto *sitem = &yw->field_2d90->supetItems[id];

    if ( !sub_4D1230(yw, id, sitem->field_F4) && sub_4D12A0(yw, sitem->field_F4) )
    {
        if ( sitem->type == 1 )
            ypaworld_func64__sub19__sub2__sub0(yw, id);
    }
    else
    {
        sub_4D16C4(yw, id);
    }
}

void ypaworld_func64__sub19(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < yw->field_2d90->supetItems_count; i++)
    {
        supetItemProto *sitem = &yw->field_2d90->supetItems[i];

        if ( sitem->type )
        {
            switch ( sitem->field_4 )
            {
            case 0:
                if ( sub_4D11C0(yw, i, sitem->pcell->owner) )
                {
                    if ( sub_4D12A0(yw, sitem->pcell->owner) )
                        sub_4D12D8(yw, i, 0);
                }
                break;

            case 1:
                ypaworld_func64__sub19__sub0(yw, i);
                ypaworld_func64__sub19__sub3(yw, i);
                break;

            case 2:
                ypaworld_func64__sub19__sub1(yw, i);
                break;

            case 3:
                ypaworld_func64__sub19__sub2(yw, i);
                break;

            default:
                break;
            }
        }
    }
}

void sub_4D6958(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *unit, samples_collection1 *collection)
{
    if ( unit == yw->field_1b80 )
    {
        collection->field_0 = yw->field_1b84->field_621;
    }
    else
    {
        xyz tmp;
        tmp.sx = unit->field_621.sx - yw->field_1b84->field_621.sx;
        tmp.sy = unit->field_621.sy - yw->field_1b84->field_621.sy;
        tmp.sz = unit->field_621.sz - yw->field_1b84->field_621.sz;

        float v11 = sqrt(POW2(tmp.sx) + POW2(tmp.sy) + POW2(tmp.sz));

        if ( v11 > 0.0 )
        {
            tmp.sx *= 100.0 / v11;
            tmp.sy *= 100.0 / v11;
            tmp.sz *= 100.0 / v11;
        }

        collection->field_0.sx = yw->field_1b84->field_621.sx + tmp.sx;
        collection->field_0.sy = yw->field_1b84->field_621.sy + tmp.sy;
        collection->field_0.sz = yw->field_1b84->field_621.sz + tmp.sz;
    }
}

void ypaworld_func64__sub23(_NC_STACK_ypaworld *yw)
{
    yw_samples *smpls = yw->samples;

    if ( smpls->field_0 >= 0 )
    {
        __NC_STACK_ypabact *unit = smpls->field_360;

        if ( unit->field_3D5 != 2 )
        {
            sub_4D6958(yw, unit, &smpls->field_4);

            smpls->field_4.field_C = yw->field_1b84->field_605.sx * yw->field_1b84->field_611;
            smpls->field_4.field_10 = yw->field_1b84->field_605.sy * yw->field_1b84->field_611;
            smpls->field_4.field_14 = yw->field_1b84->field_605.sz * yw->field_1b84->field_611;
        }

        if ( smpls->field_4.samples_data[0].field_12 & 2 )
        {
            sb_0x4242e0(&smpls->field_4);
        }
        else
        {
            sub_423DD8(&smpls->field_4);

            if ( smpls->field_35C )
                delete_class_obj(smpls->field_35C);

            memset(smpls, 0, sizeof(yw_samples));
            smpls->field_0 = -1;
        }
    }
}

void ypaworld_func64__sub3(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_1b84->p_cell_area->owner != yw->field_1b80->owner )
    {
        if ( yw->field_1b84->p_cell_area->owner )
        {
            if ( yw->field_1b74 == yw->field_1b80->owner || !yw->field_1b74 )
            {
                if ( yw->field_1614 - yw->field_1a08 > 10000 )
                {
                    yw_arg159 arg159;
                    arg159.unit = yw->field_1b84;
                    arg159.field_4 = 24;
                    arg159.txt = get_lang_string(yw->string_pointers_p2, 222, "ENEMY SECTOR ENTERED");
                    arg159.field_C = 22;

                    call_method(yw->self_full, 159, &arg159);
                }

                yw->field_1a08 = yw->field_1614;
            }
        }
    }
}

void sub_44A094(_NC_STACK_ypaworld *yw)
{
    yw->p_1_grp_cnt++;

    if ( yw->p_1_grp_cnt >= 5 )
    {
        if ( yw->p_1_grp[0][0] > 200 )
            yw->p_1_grp[0][0] = 0;

        for (int i = 0; i < 8; i++)
        {
            if ( yw->p_1_grp[0][i] )
            {
                if ( yw->p_1_grp[0][i] < yw->p_1_grp[2][i] )
                    yw->p_1_grp[2][i] = yw->p_1_grp[0][i];

                if ( yw->p_1_grp[0][i] > yw->p_1_grp[1][i] )
                    yw->p_1_grp[1][i] = yw->p_1_grp[0][i];

                yw->p_1_grp[3][i] += yw->p_1_grp[0][i];
            }
        }
    }
}

int yw_RestoreVehicleData(_NC_STACK_ypaworld *yw)
{
    char buf[256];

    if ( yw->GameShell )
    {
        scrCallBack funcs[3];
        memset(funcs, 0, sizeof(funcs));

        sprintf(buf, "save:%s/%d.rst", yw->GameShell->user_name, yw->field_2d90->levelID);

        funcs[0].func = VhclProtoParser;
        funcs[0].world = yw;

        funcs[1].func = WeaponProtoParser;
        funcs[1].world = yw;

        funcs[2].world2 = yw;
        funcs[2].func = BuildProtoParser;

        return def_parseFile(buf, 3, funcs, 2);
    }

    return 1;
}

void sub_471AB8(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_2d90->field_40 == 1 )
    {
        gateProto *gate = &yw->field_2d90->gates[ yw->field_2d90->field_4C ];

        yw->LevelNet->mapInfos[ yw->field_2d90->levelID ].field_0 = 3;

        for (int i = 0; i < gate->target_level_count; i++)
        {
            if ( yw->LevelNet->mapInfos[ gate->target_levels[i] ].field_0 == 1 )
                yw->LevelNet->mapInfos[ gate->target_levels[i] ].field_0 = 2;
        }
    }
    else if ( yw->field_2d90->field_40 == 2 && !yw_RestoreVehicleData(yw) )
    {
        ypa_log_out("yw_RestoreVehicleData() failed.\n");
    }
}

void ypaworld_func151__sub6(_NC_STACK_ypaworld *yw)
{
    if ( yw->samples )
    {
        sub_423DD8(&yw->samples->field_4);

        if ( yw->samples->field_35C )
            delete_class_obj(yw->samples->field_35C);

        memset(yw->samples, 0, sizeof(yw_samples));

        yw->samples->field_0 = -1;

        nc_FreeMem(yw->samples);
        yw->samples = NULL;
    }
}

void sub_4F1A60(__NC_STACK_ypabact *bact)
{
    nlist *a4;
    call_vtbl(bact->self, 3, 0x80001008, &a4, 0);

    while ( 1 )
    {
        bact_node *bct = (bact_node *)RemHead(a4);

        if ( !bct )
            break;

        bact_node *v5;
        bact_node *v6;
        call_vtbl(bct->bacto, 3, 0x80001011, &v5, 0);
        call_vtbl(bct->bacto, 3, 0x80001012, &v6, 0);

        if ( bct == v5 )
        {
            v5->bact->field_3e8 = NULL;
            v5->bact->field_3DE = 0;
            v5->bact->field_945 = 0;
        }
        else if ( bct == v6 )
        {
            v6->bact->field_3f8 = NULL;
            v6->bact->field_3DF = 0;
            v6->bact->field_945 = 0;
        }
        else
        {
            log_netlog("Hein BlЎd\n");
        }
    }
}

void sub_4F1B34(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact)
{
    while ( 1 )
    {
        bact_node *v4 = (bact_node *)bact->list3.head;

        if (!v4->next)
            break;

        if ( v4->bact->field_3DE == 2 )
        {
            bact_node *nd;
            call_vtbl(v4->bacto, 3, 0x80001011, &nd, 0);

            Remove(nd);

            v4->bact->field_3DE = 0;
        }

        sub_4F1A60(v4->bact);

        bact_node *weap_selfie;

        call_vtbl(v4->bacto, 3, 0x80002003, &weap_selfie, 0);
        Remove(weap_selfie);

        v4->bact->parent_bacto = NULL;

        call_method(yw->self_full, 144, v4->bacto);

        v4->bact->field_3D6 |= 0x400;
    }
}

void sub_4F1BE8(_NC_STACK_ypaworld *yw, bact_node *bct)
{
    if ( bct->bact->field_24 == 9 )
    {
        int a4;
        call_vtbl(bct->bacto, 3, 0x80002006, &a4, 0);

        if ( a4 )
        {
            roboGun *v4;
            call_vtbl(bct->bact->field_32, 3, 0x8000200E, &v4, 0);

            for (int i = 0; i < 8; i++)
            {
                if ( bct->bacto == v4[i].gun_obj )
                    v4[i].gun_obj = NULL;
            }
        }
    }
}

void sub_4C8EB4(_NC_STACK_ypaworld *yw, bact_node *bct)
{
    while ( 1 )
    {
        bact_node *cmnder = (bact_node *)bct->bact->list2.head;

        if ( !cmnder->next )
            break;

        while ( 1 )
        {
            bact_node *slave = (bact_node *)cmnder->bact->list2.head;

            if ( !slave->next )
                break;

            sub_4F1B34(yw, slave->bact);
            sub_4F1A60(slave->bact);
            sub_4F1BE8(yw, slave);

            slave->bact->field_3D6 |= 0x400;
            slave->bact->field_3D5 = 2;

            call_method(yw->self_full, 144, slave->bacto);
        }

        sub_4F1B34(yw, cmnder->bact);
        sub_4F1A60(cmnder->bact);
        sub_4F1BE8(yw, cmnder);

        cmnder->bact->field_3D6 |= 0x400;
        cmnder->bact->field_3D5 = 2;

        call_method(yw->self_full, 144, cmnder->bacto);
    }

    if ( bct->bact->field_24 == 3 )
    {
        roboGun *a4;
        call_vtbl(bct->bacto, 3, 0x8000200E, &a4, 0);

        for (int i = 0; i < 8; i++)
            a4[i].gun_obj = NULL;
    }

    sub_4F1A60(bct->bact);
    sub_4F1B34(yw, bct->bact);

    bct->bact->field_3D5 = 2;

    call_method(yw->self_full, 144, bct->bacto);

    bct->bact->field_3D6 |= 0x400;
}

void sub_44C144(vhclSndFX *sndfx)
{
    for (int i = 0; i < sndfx->extS.cnt; i++)
    {
        if ( sndfx->wavs[i] )
        {
            delete_class_obj(sndfx->wavs[i]);
            sndfx->wavs[i] = NULL;
        }
    }

    if ( sndfx->single_sample )
    {
        delete_class_obj(sndfx->single_sample);
        sndfx->single_sample = NULL;
    }
}

void ypaworld_func151__sub0(_NC_STACK_ypaworld *yw)
{
    sub_424CC8();

    for (int i = 0; i < 256; i++)
    {
        VhclProto *vhcl = &yw->VhclProtos[i];
        for (int j = 0; j < 12; j++)
        {
            sub_44C144(&vhcl->sndFX[j]);
        }
    }

    for (int i = 0; i < 128; i++)
    {
        WeapProto *weap = &yw->WeaponProtos[i];
        for (int j = 0; j < 3; j++)
        {
            sub_44C144(&weap->sndFXes[j]);
        }
    }

    for (int i = 0; i < 128; i++)
    {
        sub_44C144(&yw->BuildProtos[i].sndfx);
    }
}

void ypaworld_func151__sub1(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_34 )
    {
        nc_FreeMem(yw->field_34);
        yw->field_34 = NULL;
        yw->field_38 = 0;
    }

    if ( yw->field_30 )
    {
        nc_FreeMem(yw->field_30);
        yw->field_30 = NULL;
    }
}

void sub_4EE710(_NC_STACK_ypaworld *yw, yw_arg184 *arg, player_status *pl_status)
{
    switch ( arg->type )
    {
    case 2:
        pl_status[arg->t26.owner].p4++;
        pl_status[arg->t26.owner].p5++;
        break;

    case 3:
    {
        int owner = (arg->t34.field_1 >> 3) & 7;
        int v8 = arg->t34.field_1 & 0xC0;

        pl_status[owner].p1++;

        if ( v8 == 0x80 )
        {
            pl_status[owner].p2++;
            pl_status[owner].p5 += 20;
        }
        else if ( v8 == 0xC0 )
        {
            pl_status[owner].p2++;
            pl_status[owner].p5 += 200;
        }
        else
        {
            pl_status[owner].p5 += 10;
        }

        if ( arg->t34.field_2 & 0x8000 )
            pl_status[owner].p5 += 1000;
    }
    break;

    case 6:
        pl_status[arg->t26.owner].p5 += 100;
        pl_status[arg->t26.owner].p6++;
        break;

    case 7:
        pl_status[arg->t7.owner].p5 += 500;
        pl_status[arg->t7.owner].p7++;
        break;

    default:
        break;
    }
}

uint8_t *yw_histbf_write_evnt(uint8_t *st, yw_arg184 *arg)
{
    uint8_t *cr = st;

    switch ( arg->type )
    {
    case 1:
        *cr = arg->type;
        cr++;

        *(int32_t *)cr = arg->t15.field_1;
        cr += 4;
        break;

    case 2:
    case 6:
        *cr = arg->type;
        cr++;

        *cr = arg->t26.secX;
        cr++;

        *cr = arg->t26.secY;
        cr++;

        *cr = arg->t26.owner;
        cr++;
        break;

    case 3:
    case 4:
        *cr = arg->type;
        cr++;

        *cr = arg->t34.field_1;
        cr++;

        *(int16_t *)cr = arg->t34.field_2;
        cr += 2;

        *cr = arg->t34.field_4;
        cr++;

        *cr = arg->t34.field_5;
        cr++;
        break;

    case 5:
        *cr = arg->type;
        cr++;

        *(int32_t *)cr = 0;
        cr += 4;

        printf("MAKE ME histbuff type 5!\n");
        break;

    case 7:
        *cr = arg->type;
        cr++;

        *cr = arg->t7.secX;
        cr++;

        *cr = arg->t7.secY;
        cr++;

        *cr = arg->t7.owner;
        cr++;

        *cr = arg->t7.field_4;
        cr++;

        *cr = arg->t7.field_5;
        cr++;

        *(int16_t *)cr = arg->t7.last_vhcl;
        cr += 2;

        *(int16_t *)cr = arg->t7.last_weapon;
        cr += 2;

        *(int16_t *)cr = arg->t7.last_build;
        cr += 2;
        break;

    default:
        break;
    }

    return cr;
}

uint8_t *yw_histbf_read_evnt(uint8_t *st, yw_arg184 *arg)
{
    uint8_t *cr = st;

    switch ( *cr )
    {
    case 1:
        arg->type = *cr;
        cr++;

        arg->t15.field_1 = *(int32_t *)cr;
        cr += 4;
        break;

    case 2:
    case 6:
        arg->type = *cr;
        cr++;

        arg->t26.secX = *cr;
        cr++;

        arg->t26.secY = *cr;
        cr++;

        arg->t26.owner = *cr;
        cr++;
        break;

    case 3:
    case 4:
        arg->type = *cr;
        cr++;

        arg->t34.field_1 = *cr;
        cr++;

        arg->t34.field_2 = *(int16_t *)cr;
        cr += 2;

        arg->t34.field_4 = *cr;
        cr++;

        arg->t34.field_5 = *cr;
        cr++;
        break;

    case 5:
        arg->type = *cr;
        cr++;

        arg->t15.field_1 = 0;
        cr += 4;

        printf("MAKE ME histbuff type 5!\n");
        break;

    case 7:
        arg->type = *cr;
        cr++;

        arg->t7.secX = *cr;
        cr++;

        arg->t7.secY = *cr;
        cr++;

        arg->t7.owner = *cr;
        cr++;

        arg->t7.field_4 = *cr;
        cr++;

        arg->t7.field_5 = *cr;
        cr++;

        arg->t7.last_vhcl = *(int16_t *)cr;
        cr += 2;

        arg->t7.last_weapon = *(int16_t *)cr;
        cr += 2;

        arg->t7.last_build = *(int16_t *)cr;
        cr += 2;
        break;

    default:
        memset(arg, 0, sizeof(yw_arg184));
        break;
    }

    return cr;
}

void ypaworld_func184__sub0(_NC_STACK_ypaworld *yw, yw_f726c *hist_list, yw_arg184 *arg)
{
    if ( hist_list->last_bufStart || sub_47EDDC(hist_list, 4096) )
    {
        int tlen = 0;

        switch ( arg->type )
        {
        case 1:
            tlen = 5;

            hist_list->field_C++;
            hist_list->field_10 = yw->field_1614;

            if ( hist_list->field_1C )
            {
                if ( *hist_list->field_1C == 1 )
                    hist_list->last_bufStart = hist_list->field_1C;
            }

            break;

        case 2:
        case 6:
            tlen = 4;
            break;

        case 3:
        case 4:
            tlen = 6;
            break;

        case 5:
            tlen = 5;
            break;

        case 7:
            tlen = 12;
            break;

        default:
            break;
        }

        if ( tlen )
        {
            hist_list->field_1C = hist_list->last_bufStart;

            if ( hist_list->last_bufStart + tlen + 1 < hist_list->last_bufEnd || sub_47EDDC(hist_list, 4096) )
            {
                hist_list->last_bufStart = yw_histbf_write_evnt(hist_list->last_bufStart, arg);
            }
            else
                return;
        }


        if ( yw->GameShell )
        {
            if ( yw->GameShell->field_0x1cd8 )
                sub_4EE710(yw, arg, yw->field_7796);
        }
    }
}

void sub_480868(_NC_STACK_ypaworld *yw)
{
    dprintf("MAKE ME %s (scene events)\n", "sub_480868");
}

void ypaworld_func151__sub5(_NC_STACK_ypaworld *yw)
{
    if ( yw->map_events )
    {
        nc_FreeMem(yw->map_events);
        yw->map_events = NULL;
    }
}

void ypaworld_func64__sub11(_NC_STACK_ypaworld *yw)
{
    dprintf("MAKE ME %s (joy vibrate)\n", "ypaworld_func64__sub11");
}

int recorder_startrec(_NC_STACK_ypaworld *yw)
{
    recorder *rcrd = yw->sceneRecorder;

    rcrd->do_record = 0;
    rcrd->field_40 = 0;
    rcrd->seqn++;
    rcrd->level_id = yw->field_2d90->levelID;
    rcrd->frame_id = 0;
    rcrd->time = 0;
    rcrd->bacts_count = 0;
    rcrd->field_34 = 0;
    rcrd->ainf_size = 0;

    char a1[256];
    sprintf(a1, "env/snaps/m%02d%04d.raw", yw->field_2d90->levelID, rcrd->seqn);

    rcrd->mfile = new_MFILE();

    if ( !rcrd->mfile )
        return 0;

    rcrd->mfile->file_handle = FOpen(a1, "wb");
    if ( !rcrd->mfile->file_handle )
    {
        del_MFILE(rcrd->mfile);
        rcrd->mfile = 0;
        return 0;
    }

    if ( sub_412F98(rcrd->mfile, 1) )
    {
        FClose(rcrd->mfile->file_handle);
        del_MFILE(rcrd->mfile);
        rcrd->mfile = 0;
        return 0;
    }

    sub_412FC0(rcrd->mfile, TAG_SEQN, TAG_FORM, -1);
    sub_412FC0(rcrd->mfile, 0, TAG_SINF, 4);

    sub_413564(rcrd->mfile, 2, &rcrd->seqn);
    sub_413564(rcrd->mfile, 2, &rcrd->level_id);

    sub_413290(rcrd->mfile);

    rcrd->do_record = 1;
    return 1;
}

void recorder_stoprec(_NC_STACK_ypaworld *yw)
{
    recorder *rcrd = yw->sceneRecorder;
    rcrd->do_record = 0;

    if ( rcrd->mfile )
    {
        sub_413290(rcrd->mfile);

        FClose(rcrd->mfile->file_handle);

        del_MFILE(rcrd->mfile);

        rcrd->mfile = NULL;
    }
}

void sb_0x447720(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( inpt->downed_key == VK_MULTIPLY && (inpt->winp131arg.flag & 0x100 || yw->easy_cheat_keys) )
    {
        sub_4476AC(yw);

        yw_arg159 info_msg;
        info_msg.txt = "Screenshot saved.";
        info_msg.unit = NULL;
        info_msg.field_4 = 100;
        info_msg.field_C = 0;

        call_method(yw->self_full, 159, &info_msg);
    }


    if ( yw->do_screenshooting )
    {
        if ( inpt->downed_key == VK_DIVIDE && (inpt->winp131arg.flag & 0x100 || yw->easy_cheat_keys) )
        {
            yw->do_screenshooting = 0;

            yw_arg159 info_msg;
            info_msg.txt = "Screenshotting: stopped.";
            info_msg.unit = NULL;
            info_msg.field_4 = 100;
            info_msg.field_C = 0;

            call_method(yw->self_full, 159, &info_msg);
        }


        char a1[256];
        sprintf(a1, "env/snaps/s%d_%04d", yw->screenshot_seq_id, yw->screenshot_seq_frame_id);

        yw->screenshot_seq_frame_id++;

        NC_STACK_win3d *win3d;
        gfxEngine__getter(0x8000300D, &win3d, 0);

        char *v13 = a1;

        call_method(win3d, 274, &v13);
    }
    else if ( inpt->downed_key == VK_DIVIDE && (inpt->winp131arg.flag & 0x100 || yw->easy_cheat_keys) )
    {
        yw->screenshot_seq_frame_id = 0;
        yw->do_screenshooting = 1;
        yw->screenshot_seq_id++;

        yw_arg159 info_msg;
        info_msg.txt = "Screenshotting: started.";
        info_msg.unit = NULL;
        info_msg.field_4 = 100;
        info_msg.field_C = 0;

        call_method(yw->self_full, 159, &info_msg);
    }

    if ( yw->sceneRecorder->do_record )
    {
        if ( inpt->downed_key == VK_SUBTRACT && (inpt->winp131arg.flag & 0x100 || yw->easy_cheat_keys) )
        {
            recorder_stoprec(yw);

            yw_arg159 info_msg;
            info_msg.txt = "Replay recordering: stopped.";
            info_msg.unit = NULL;
            info_msg.field_4 = 100;
            info_msg.field_C = 0;

            call_method(yw->self_full, 159, &info_msg);
        }

    }
    else
    {
        if ( inpt->downed_key == VK_SUBTRACT && (inpt->winp131arg.flag & 0x100 || yw->easy_cheat_keys) )
        {
            recorder_startrec(yw);

            yw_arg159 info_msg;
            info_msg.txt = "Replay recordering: started.";
            info_msg.unit = NULL;
            info_msg.field_4 = 100;
            info_msg.field_C = 0;

            call_method(yw->self_full, 159, &info_msg);
        }
    }
}

void recorder_update_time(_NC_STACK_ypaworld *yw, int dtime)
{
    yw->sceneRecorder->time += dtime;
    yw->sceneRecorder->field_40 -= dtime;
}

void recorder_store_bact(_NC_STACK_ypaworld *yw, recorder *rcrd, nlist *bct_lst)
{
    bact_node *bct = (bact_node *)bct_lst->head;
    while (bct->next)
    {
        if ( bct->bact->ypabact__id >= 0xFFFF || bct->bact == yw->field_1b80 )
        {
            if ( rcrd->bacts_count < rcrd->max_bacts )
            {
                rcrd->bacts[ rcrd->bacts_count ] = bct->bact;
                rcrd->bacts_count++;
            }

            recorder_store_bact(yw, rcrd, &bct->bact->list3);
            recorder_store_bact(yw, rcrd, &bct->bact->list2);
        }

        bct = (bact_node *)bct->next;
    }
}

void rotmat_to_euler(mat3x3 *mat, xyz *out)
{
    float sy = sqrt(POW2(mat->m00) + POW2(mat->m10));

    bool singular = sy < 1e-6;

    if ( !singular )
    {
        out->sx = atan2(mat->m21, mat->m22);
        out->sy = atan2(-mat->m20, sy);
        out->sz = atan2(mat->m10, mat->m00);
    }
    else
    {
        out->sx = atan2(-mat->m12, mat->m11);
        out->sy = atan2(-mat->m20, sy);
        out->sz = 0.0;
    }
}

void euler_to_rotmat(xyz *euler, mat3x3 *out)
{
    float _cx = cos(euler->sx);
    float _sx = sin(euler->sx);
    float _cy = cos(euler->sy);
    float _sy = sin(euler->sy);
    float _cz = cos(euler->sz);
    float _sz = sin(euler->sz);

    out->m00 = _cy * _cz;
    out->m01 = _sy * _sx * _cz - _cx * _sz;
    out->m02 = _sy * _cx * _cz + _sx * _sz;
    out->m10 = _cy * _sz;
    out->m11 = _sy * _sx * _sz + _cx * _cz;
    out->m12 = _sy * _cx * _sz - _sx * _cz;
    out->m20 = -_sy;
    out->m21 = _cy * _sx;
    out->m22 = _cy * _cx;
}

int recorder_sort_bact(const void *a1, const void *a2)
{
    return (*(__NC_STACK_ypabact **)a1)->ypabact__id - (*(__NC_STACK_ypabact **)a2)->ypabact__id;
}

void recorder_world_to_frame(_NC_STACK_ypaworld *yw, recorder *rcrd)
{
    rcrd->bacts_count = 0;
    recorder_store_bact(yw, rcrd, &yw->bact_list);

    qsort(rcrd->bacts, rcrd->bacts_count, 4, recorder_sort_bact);

    for (int i = 0; i < rcrd->bacts_count; i++)
    {
        __NC_STACK_ypabact *bact = rcrd->bacts[i];

        trec_bct *oinf = &rcrd->oinf[i];

        oinf->bact_id = bact->ypabact__id;
        oinf->pos = bact->field_621;

        xyz euler;
        rotmat_to_euler(&bact->field_651, &euler);

        const float pi2 = 6.283185307;

        oinf->rot_x = dround(euler.sx * 127.0 / pi2);
        oinf->rot_y = dround(euler.sy * 127.0 / pi2);
        oinf->rot_z = dround(euler.sz * 127.0 / pi2);

        NC_STACK_base *a4;
        call_vtbl(bact->self, 3, 0x8000100C, &a4, 0);

        if ( a4 == bact->vp_normal.base )
        {
            oinf->vp_id = 1;
        }
        else if ( a4 == bact->vp_fire.base )
        {
            oinf->vp_id = 2;
        }
        else if ( a4 == bact->vp_wait.base )
        {
            oinf->vp_id = 3;
        }
        else if ( a4 == bact->vp_dead.base )
        {
            oinf->vp_id = 4;
        }
        else if ( a4 == bact->vp_megadeth.base )
        {
            oinf->vp_id = 5;
        }
        else if ( a4 == bact->vp_genesis.base )
        {
            oinf->vp_id = 6;
        }
        else
        {
            oinf->vp_id = 0;
        }

        oinf->bact_type = (bact->field_24 != 4) + 1;
        oinf->vhcl_id = bact->id;

        uint16_t *ssnd = &rcrd->sound_status[i * 2];
        ssnd[0] = 0;

        for (int j = 0; j < 16; j++)
        {
            if (bact->field_5A.samples_data[j].field_12 & 0x92)
                ssnd[0] |= 1 << j;
        }

        ssnd[1] = bact->field_5A.samples_data[0].pitch;
    }
}

void recorder_pack_soundstates(recorder *rcrd)
{
    uint8_t *in = (uint8_t *)rcrd->sound_status;
    int in_pos = 0;

    uint8_t *output = (uint8_t *)rcrd->ainf;
    int out_pos = 0;

    int max_bytes_count = 4 * rcrd->bacts_count;

    while ( in_pos < max_bytes_count )
    {
        if ( in_pos >= max_bytes_count - 1 || in[in_pos] != in[in_pos + 1] )
        {
            int ctrl_byte_pos = out_pos;
            int cnt_bytes = 0;

            while (cnt_bytes < 0x80)
            {
                if ( in_pos >= max_bytes_count )
                    break;
                else if ( in_pos < max_bytes_count - 2 && in[in_pos] == in[in_pos + 1] && in[in_pos] == in[in_pos + 2] )
                    break;

                output[out_pos] = in[in_pos];
                in_pos++;
                out_pos++;

                cnt_bytes++;
            }

            output[ctrl_byte_pos] = cnt_bytes - 1;
        }
        else
        {
            int cnt_bytes = 0;

            uint8_t smplbyte = in[in_pos];
            while ( in_pos < max_bytes_count )
            {
                if ( in[in_pos] != smplbyte )
                    break;

                if ( cnt_bytes >= 0x80 )
                    break;

                in_pos++;
                cnt_bytes++;
            }
            output[out_pos] = 0x101 - cnt_bytes;
            output[out_pos + 1] = smplbyte;
            out_pos += 2;
        }
    }

    rcrd->ainf_size = out_pos;
}

void recorder_unpack_soundstates(recorder *rcrd)
{
    uint8_t *out = (uint8_t *)rcrd->sound_status;
    uint8_t *in = (uint8_t *)rcrd->ainf;
    uint8_t *in_end = ((uint8_t *)rcrd->ainf) + rcrd->ainf_size;

    while ( in < in_end )
    {
        uint8_t bt = *in;
        in++;

        if ( bt > 0x80 )
        {
            for (int i = 0; i < 0x101 - bt; i++)
            {
                *out = *in;
                out++;
            }

            in++;
        }
        else if ( bt < 0x80 )
        {
            bt += 1;

            memcpy(out, in, bt);

            out += bt;
            in += bt;
        }
    }
}

void recorder_write_frame(_NC_STACK_ypaworld *yw)
{
    recorder *rcrd = yw->sceneRecorder;

    if ( rcrd->field_40 < 0 )
    {
        recorder_world_to_frame(yw, yw->sceneRecorder);
        rcrd->ctrl_bact_id = yw->field_1b84->ypabact__id;
        recorder_pack_soundstates(rcrd);


        int frame_size = 24;
        int oinf_size = 22 * rcrd->bacts_count;
        int v5 = 16 * rcrd->field_34;

        if ( oinf_size )
        {
            frame_size = oinf_size + 32;

            if ( frame_size & 1 )
                frame_size++;
        }

        if ( rcrd->ainf_size )
        {
            frame_size += rcrd->ainf_size + 8;

            if ( frame_size & 1 )
                frame_size++;
        }

        if ( v5 )
        {
            frame_size += v5 + 8;

            if ( frame_size & 1 )
                frame_size++;
        }
        sub_412FC0(rcrd->mfile, TAG_FRAM, TAG_FORM, frame_size);
        sub_412FC0(rcrd->mfile, 0, TAG_FINF, 12);

        sub_413564(rcrd->mfile, 4, &rcrd->frame_id);
        sub_413564(rcrd->mfile, 4, &rcrd->time);
        sub_413564(rcrd->mfile, 4, &rcrd->ctrl_bact_id);

        sub_413290(rcrd->mfile);

        if ( oinf_size )
        {
            sub_412FC0(rcrd->mfile, 0, TAG_OINF, oinf_size);

            for (int i = 0; i < rcrd->bacts_count; i++)
            {
                trec_bct *oinf = &rcrd->oinf[i];

                sub_413564(rcrd->mfile, 4, &oinf->bact_id);
                sub_413564(rcrd->mfile, 4, &oinf->pos.sx);
                sub_413564(rcrd->mfile, 4, &oinf->pos.sy);
                sub_413564(rcrd->mfile, 4, &oinf->pos.sz);
                sub_413564(rcrd->mfile, 1, &oinf->rot_x);
                sub_413564(rcrd->mfile, 1, &oinf->rot_y);
                sub_413564(rcrd->mfile, 1, &oinf->rot_z);
                sub_413564(rcrd->mfile, 1, &oinf->vp_id);
                sub_413564(rcrd->mfile, 1, &oinf->bact_type);
                sub_413564(rcrd->mfile, 1, &oinf->vhcl_id);
            }

            sub_413290(rcrd->mfile);
        }

        if ( rcrd->ainf_size )
        {
            sub_412FC0(rcrd->mfile, 0, TAG_AINF, rcrd->ainf_size);
            sub_413564(rcrd->mfile, rcrd->ainf_size, rcrd->ainf);
            sub_413290(rcrd->mfile);
        }

        if ( v5 )
        {
            sub_412FC0(rcrd->mfile, 0, TAG_MODE, v5);
            sub_413564(rcrd->mfile, v5, rcrd->field_20);
            sub_413290(rcrd->mfile);
        }

        sub_413290(rcrd->mfile);

        rcrd->field_34 = 0;
        rcrd->field_40 += 250;
        rcrd->frame_id += 1;
    }
}


int ypaworld_func64__sub22__sub0(_NC_STACK_ypaworld *yw, int event_id)
{
    evnt *ev = &yw->map_events->evnts[event_id];

    if ( !ev->field_8 )
        ev->field_8 = yw->field_1614;

    if ( ev->field_0 == 1 )
    {
        if ( ev->field_C )
            return 3;
        else
        {
            ev->field_C = 1;

            if ( ev->field_4 )
            {
                if ( ev->field_4(yw) )
                    return 3;
            }
        }

        return 1;
    }
    else if ( ev->field_0 == 5 )
    {
        if ( (yw->field_1614 - ev->field_8) > ev->field_10 )
        {
            if ( ev->field_C )
                return 3;

            ev->field_C = 1;

            if ( ev->field_4 )
            {
                if ( ev->field_4(yw) )
                    return 3;
            }

            return 1;
        }
        return 2;
    }
    else if ( ev->field_0 == 2 )
    {
        if ( (yw->field_1614 - ev->field_8) <= ev->field_10 )
            return 3;

        ev->field_8 = yw->field_1614;

        if ( ev->field_4 )
        {
            if ( ev->field_4(yw) )
                return 3;
        }
        return 1;
    }
    else if ( ev->field_0 == 4 )
    {
        if ( !ev->field_C )
        {
            ev->field_C = 1;

            if ( ev->field_4 )
            {
                if ( ev->field_4(yw) )
                    return 3;
            }
            return 1;
        }

        if ( (yw->field_1614 - ev->field_8) <= ev->field_10 )
            return 3;

        ev->field_8 = yw->field_1614;

        if ( ev->field_4 )
        {
            if ( ev->field_4(yw) )
                return 3;
        }

        return 1;
    }
    else if ( ev->field_0 == 3 )
    {
        if ( ev->field_4 )
        {
            if ( ev->field_4(yw) )
                return 3;

            return 1;
        }
        return 3;
    }
    else if ( ev->field_0 == 6 )
    {
        if ( (yw->field_1614 - ev->field_8) <= ev->field_10 )
            return 2;

        if ( ev->field_C )
            return 3;

        ev->field_C = 1;

        if ( ev->field_4 )
            ev->field_4(yw);

        if ( sub_4C885C() != 3 )
        {
            extern int dword_5C8B78;
            extern listview exit_menu;

            dword_5C8B78 = 8;
            const char *v14 = get_lang_string(yw->string_pointers_p2, 2470, "2470 == EXIT TUTORIAL MISSION ?");
            sb_0x4c87fc(yw, v14, &exit_menu);
        }
        return 6;
    }

    return 1;
}

void ypaworld_func64__sub22__sub1(_NC_STACK_ypaworld *yw, int evnt_id)
{
    map_event *mevent = yw->map_events;
    mevent->field_8 = evnt_id;

    evnt *ev = &mevent->evnts[evnt_id];

    mevent->field_C = yw->field_1614;

    yw_arg159 arg159;
    arg159.field_4 = 100;
    arg159.unit = NULL;
    arg159.field_C = ev->field_1C[ ev->field_14 ];

    ev->field_14++;

    if ( ev->field_14 >= ev->field_18 )
        ev->field_14 = 0;

    arg159.txt = NULL;

    call_method(yw->self_full, 159, &arg159);
}

void ypaworld_func64__sub22(_NC_STACK_ypaworld *yw)
{
    map_event *mevent = yw->map_events;
    if ( mevent->event_loop_id )
    {
        int v3 = 3;
        int i;

        for (i = 0; i < mevent->event_count; i++ )
        {
            v3 = ypaworld_func64__sub22__sub0(yw, i);

            if ( v3 != 3 )
                break;
        }

        if ( v3 == 1 && i < mevent->event_count )
        {
            if ( i == mevent->field_8 )
            {
                if ( (yw->field_1614 - mevent->field_C) > mevent->evnts[ mevent->field_8 ].field_10 )
                    ypaworld_func64__sub22__sub1(yw, mevent->field_8);
            }
            else
            {
                ypaworld_func64__sub22__sub1(yw, i);
            }

        }
    }
}

int recorder_open_replay(recorder *rcrd)
{
    rcrd->mfile = new_MFILE();

    if ( !rcrd->mfile )
        return 0;

    rcrd->mfile->file_handle = FOpen(rcrd->filename, "rb");

    if ( !rcrd->mfile->file_handle )
    {
        del_MFILE(rcrd->mfile);

        rcrd->mfile = NULL;
        return 0;
    }

    if ( sub_412F98(rcrd->mfile, 0) )
    {
        FClose(rcrd->mfile->file_handle);
        del_MFILE(rcrd->mfile);

        rcrd->mfile = NULL;
        return 0;
    }

    if ( read_next_IFF(rcrd->mfile, 2) )
    {
        FClose(rcrd->mfile->file_handle);
        del_MFILE(rcrd->mfile);

        rcrd->mfile = NULL;
        return 0;
    }

    MFILE_S1 *v3 = GET_FORM_INFO_OR_NULL(rcrd->mfile);

    if ( v3->TAG == TAG_FORM && v3->TAG_EXTENSION == TAG_SEQN )
        return 1;

    return 0;
}


int recorder_create_camera(_NC_STACK_ypaworld *yw)
{
    NC_STACK_ypabact *bacto = (NC_STACK_ypabact *)init_get_class("ypabact.class", 0x80001001, yw->self_full, 0);

    if ( !bacto )
        return 0;

    __NC_STACK_ypabact *bact = &bacto->stack__ypabact;

    call_method(bacto, 96, 0);

    bact->ypabact__id = 0;
    bact->owner = 1;

    bact->field_651.m00 = 1.0;
    bact->field_651.m01 = 0;
    bact->field_651.m02 = 0;
    bact->field_651.m10 = 0;
    bact->field_651.m11 = 1.0;
    bact->field_651.m12 = 0;
    bact->field_651.m20 = 0;
    bact->field_651.m21 = 0;
    bact->field_651.m22 = 1.0;

    sub_423DB0(&bact->field_5A);

    call_method(yw->self_full, 134, bacto);

    call_vtbl(bacto, 2, 0x80001004, 1, 0);
    call_vtbl(bacto, 2, 0x80001005, 1, 0);

    yw->field_1b78 = bacto;
    yw->field_1b80 = bact;
    yw->field_1b88 = &bact->list2;

    sub_430A20(&bact->field_87D);

    return 1;
}



void recorder_read_framedata(recorder *rcrd)
{
    while ( read_next_IFF(rcrd->mfile, 2) != -2 )
    {
        MFILE_S1 *v3 = GET_FORM_INFO_OR_NULL(rcrd->mfile);

        switch ( v3->TAG )
        {
        case TAG_FLSH:
            rcrd->field_78 |= 1;
            read_next_IFF(rcrd->mfile, 2);
            break;

        case TAG_FINF:
            mfread(rcrd->mfile, &rcrd->frame_id, 4);
            mfread(rcrd->mfile, &rcrd->time, 4);
            mfread(rcrd->mfile, &rcrd->ctrl_bact_id, 4);
            read_next_IFF(rcrd->mfile, 2);
            break;

        case TAG_OINF:
        {
            rcrd->bacts_count = v3->TAG_SIZE / 22;

            for (int i = 0; i < rcrd->bacts_count; i++)
            {
                for (int i = 0; i < rcrd->bacts_count; i++)
                {
                    trec_bct *oinf = &rcrd->oinf[i];

                    mfread(rcrd->mfile, &oinf->bact_id, 4);
                    mfread(rcrd->mfile, &oinf->pos.sx, 4);
                    mfread(rcrd->mfile, &oinf->pos.sy, 4);
                    mfread(rcrd->mfile, &oinf->pos.sz, 4);
                    mfread(rcrd->mfile, &oinf->rot_x, 1);
                    mfread(rcrd->mfile, &oinf->rot_y, 1);
                    mfread(rcrd->mfile, &oinf->rot_z, 1);
                    mfread(rcrd->mfile, &oinf->vp_id, 1);
                    mfread(rcrd->mfile, &oinf->bact_type, 1);
                    mfread(rcrd->mfile, &oinf->vhcl_id, 1);
                }

            }

            read_next_IFF(rcrd->mfile, 2);
        }
        break;

        case TAG_AINF:
            mfread(rcrd->mfile, rcrd->ainf, v3->TAG_SIZE);
            rcrd->ainf_size = v3->TAG_SIZE;

            recorder_unpack_soundstates(rcrd);

            read_next_IFF(rcrd->mfile, 2);
            break;

        case TAG_MODE:
            mfread(rcrd->mfile, rcrd->field_20, v3->TAG_SIZE);
            rcrd->field_34 = v3->TAG_SIZE / 16;

            read_next_IFF(rcrd->mfile, 2);
            break;

        default:
            read_default(rcrd->mfile);
            break;
        }
    }
}

__NC_STACK_ypabact *sub_46F3AC(_NC_STACK_ypaworld *yw, trec_bct *oinf)
{
    NC_STACK_ypabact *bacto = NULL;
    __NC_STACK_ypabact *bact = NULL;

    if ( oinf->bact_type == 2 )
    {
        if ( oinf->vhcl_id )
        {
            ypaworld_arg146 arg146;
            arg146.vehicle_id = oinf->vhcl_id;
            arg146.pos.sx = 0;
            arg146.pos.sy = 0;
            arg146.pos.sz = 0;

            VhclProto *prot = &yw->VhclProtos[ oinf->vhcl_id ];

            int v6 = prot->model_id;

            prot->model_id = 1;

            bacto = (NC_STACK_ypabact *)call_method(yw->self_full, 146, &arg146);

            yw->VhclProtos[oinf->vhcl_id].model_id = v6;
        }
        else
        {
            bacto = (NC_STACK_ypabact *)init_get_class("ypabact.class", 0x80001001, yw->self_full, 0);
            if ( bacto )
            {
                bact = &bacto->stack__ypabact;

                call_method(bacto, 96, 0);

                bact->ypabact__id = 0;
                bact->owner = 1;

                bact->field_651.m00 = 1.0;
                bact->field_651.m01 = 0;
                bact->field_651.m02 = 0;
                bact->field_651.m10 = 0;
                bact->field_651.m11 = 1.0;
                bact->field_651.m12 = 0;
                bact->field_651.m20 = 0;
                bact->field_651.m21 = 0;
                bact->field_651.m22 = 1.0;
            }
        }
    }
    else
    {
        ypaworld_arg146 arg147;
        arg147.vehicle_id = oinf->vhcl_id;
        arg147.pos.sx = 0;
        arg147.pos.sy = 0;
        arg147.pos.sz = 0;

        bacto = (NC_STACK_ypabact *)call_method(yw->self_full, 147, &arg147);
    }

    if ( bacto )
    {
        bact = &bacto->stack__ypabact;

        if ( bact->parent_bacto )
            Remove(&bact->list_node);

        bact->ypabact__id = oinf->bact_id;
        bact->field_32 = yw->field_1b7c;
        bact->parent_bacto = yw->field_1b7c;
        bact->parent_bact = yw->field_1b84;
    }

    return bact;
}

void recorder_set_bact_pos(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact, xyz *pos)
{
    yw_130arg arg130;
    arg130.pos_x = pos->sx;
    arg130.pos_z = pos->sz;

    if ( call_method(yw->self_full, 130, &arg130) )
    {
        if ( bact->p_cell_area )
            Remove(bact);

        AddTail(&arg130.pcell->field_3C, bact);

        bact->p_cell_area = arg130.pcell;
        bact->field_62D = bact->field_621;
        bact->field_621 = *pos;
        bact->field_c = arg130.sec_x;
        bact->field_10 = arg130.sec_z;
    }
}

void sub_46F5C8(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact, trec_bct *oinf, uint16_t *ssnd, float a5, float a6)
{
    xyz bct_pos;
    bct_pos.sx = (oinf->pos.sx - bact->field_621.sx) * a5 + bact->field_621.sx;
    bct_pos.sy = (oinf->pos.sy - bact->field_621.sy) * a5 + bact->field_621.sy;
    bct_pos.sz = (oinf->pos.sz - bact->field_621.sz) * a5 + bact->field_621.sz;

    recorder_set_bact_pos(yw, bact, &bct_pos);

    bact->field_605.sx = bact->field_621.sx - bact->field_62D.sx;
    bact->field_605.sy = bact->field_621.sy - bact->field_62D.sy;
    bact->field_605.sz = bact->field_621.sz - bact->field_62D.sz;

    float v82 = sqrt( POW2(bact->field_605.sx) + POW2(bact->field_605.sy) + POW2(bact->field_605.sz) );
    if ( v82 > 0.0 )
    {
        bact->field_605.sx /= v82;
        bact->field_605.sy /= v82;
        bact->field_605.sz /= v82;

        if ( a6 <= 0.0 )
            bact->field_611 = 0;
        else
            bact->field_611 = (v82 / a6) / 6.0;
    }
    else
    {
        bact->field_605.sx = 1.0;
        bact->field_605.sy = 0;
        bact->field_605.sz = 0;

        bact->field_611 = 0;
    }

    const float pi2 = 3.141592653589793 * 2.0;

    xyz euler;
    euler.sx = oinf->rot_x / 127.0 * pi2;
    euler.sy = oinf->rot_y / 127.0 * pi2;
    euler.sz = oinf->rot_z / 127.0 * pi2;

    mat3x3 tmp;
    euler_to_rotmat(&euler, &tmp);

    mat3x3 tmp2;

    tmp2.m00 = (tmp.m00 - bact->field_651.m00) * a5 + bact->field_651.m00;
    tmp2.m01 = (tmp.m01 - bact->field_651.m01) * a5 + bact->field_651.m01;
    tmp2.m02 = (tmp.m02 - bact->field_651.m02) * a5 + bact->field_651.m02;

    float v80 = sqrt( POW2(tmp2.m00) + POW2(tmp2.m01) + POW2(tmp2.m02) );
    if ( v80 > 0.0 )
    {
        tmp2.m00 /= v80;
        tmp2.m01 /= v80;
        tmp2.m02 /= v80;
    }
    else
    {
        tmp2.m00 = 1.0;
        tmp2.m01 = 0.0;
        tmp2.m02 = 0.0;
    }


    tmp2.m10 = (tmp.m10 - bact->field_651.m10) * a5 + bact->field_651.m10;
    tmp2.m11 = (tmp.m11 - bact->field_651.m11) * a5 + bact->field_651.m11;
    tmp2.m12 = (tmp.m12 - bact->field_651.m12) * a5 + bact->field_651.m12;

    v80 = sqrt( POW2(tmp2.m10) + POW2(tmp2.m11) + POW2(tmp2.m12) );
    if ( v80 > 0.0 )
    {
        tmp2.m10 /= v80;
        tmp2.m11 /= v80;
        tmp2.m12 /= v80;
    }
    else
    {
        tmp2.m10 = 0.0;
        tmp2.m11 = 1.0;
        tmp2.m12 = 0.0;
    }


    tmp2.m20 = (tmp.m20 - bact->field_651.m20) * a5 + bact->field_651.m20;
    tmp2.m21 = (tmp.m21 - bact->field_651.m21) * a5 + bact->field_651.m21;
    tmp2.m22 = (tmp.m22 - bact->field_651.m22) * a5 + bact->field_651.m22;

    v80 = sqrt( POW2(tmp2.m20) + POW2(tmp2.m21) + POW2(tmp2.m22) );
    if ( v80 > 0.0 )
    {
        tmp2.m20 /= v80;
        tmp2.m21 /= v80;
        tmp2.m22 /= v80;
    }
    else
    {
        tmp2.m20 = 0.0;
        tmp2.m21 = 0.0;
        tmp2.m22 = 1.0;
    }

    bact->field_651 = tmp2;

    base_1c_struct *v43 = NULL;
    NC_STACK_base *v44 = NULL;

    switch ( oinf->vp_id )
    {
    case 1:
        v43 = bact->vp_normal.trigo;
        v44 = bact->vp_normal.base;
        break;

    case 2:
        v43 = bact->vp_fire.trigo;
        v44 = bact->vp_fire.base;
        break;

    case 3:
        v43 = bact->vp_wait.trigo;
        v44 = bact->vp_wait.base;
        break;

    case 4:
        v43 = bact->vp_dead.trigo;
        v44 = bact->vp_dead.base;
        break;

    case 5:
        v43 = bact->vp_megadeth.trigo;
        v44 = bact->vp_megadeth.base;
        break;

    case 6:
        v43 = bact->vp_genesis.trigo;
        v44 = bact->vp_genesis.base;
        break;

    default:
        break;
    }

    if ( v44 && v43 )
        call_vtbl(bact->self, 2, 0x8000100C, v44, 0x8000100F, v43, 0);

    bact->field_5A.samples_data[0].pitch = ssnd[1];

    for(int i = 0; i < 16; i++)
    {
        int v48 = 1 << i;
        if ( v48 & ssnd[0] )
        {
            if ( !(bact->field_3B2 & v48) )
            {
                bact->field_3B2 |= v48;
                sub_423F74(&bact->field_5A, i);
            }
        }
        else
        {
            if ( bact->field_3B2 & v48 )
            {
                bact->field_3B2 &= ~v48;

                if ( bact->field_5A.samples_data[i].field_12 & 1 )
                    sub_424000(&bact->field_5A, i);
            }
        }
    }
}


void sub_46FDA0(_NC_STACK_ypaworld *yw, recorder *rcrd, float a5, int period)
{
    float fperiod = period / 1000.0;
    bact_node *v6 = (bact_node *)yw->field_1b84->list2.head;

    int i = 0;

    while ( i < rcrd->bacts_count )
    {
        trec_bct *oinf = &rcrd->oinf[i];
        uint16_t *ssnd = &rcrd->sound_status[2 * i];

        if ( v6->next )
        {
            if ( oinf->bact_id > v6->bact->ypabact__id )
            {
                bact_node *next = (bact_node *)v6->next;

                call_method(yw->self_full, 144, v6->bacto);

                v6 = next;
            }
            else if ( oinf->bact_id < v6->bact->ypabact__id )
            {
                __NC_STACK_ypabact *v10 = sub_46F3AC(yw, oinf);

                if ( v10 )
                {
                    sub_46F5C8(yw, v10, oinf, ssnd, 1.0, fperiod);

                    v10->list_node.prev = v6->prev;
                    v10->list_node.next = v6;

                    v6->prev->next = &v10->list_node;
                    v6->prev = &v10->list_node;

                    i++;
                }
            }
            else // ==
            {
                sub_46F5C8(yw, v6->bact, oinf, ssnd, a5, fperiod);
                v6 = (bact_node *)v6->next;

                i++;
            }
        }
        else
        {
            __NC_STACK_ypabact *v13 = sub_46F3AC(yw, oinf);

            if ( v13 )
            {
                sub_46F5C8(yw, v13, oinf, ssnd, 1.0, fperiod);

                AddTail(&yw->field_1b84->list2, &v13->list_node);

                v6 = (bact_node *)v13->list_node.next;

                i++;
            }
        }
    }

    while ( v6->next )
    {
        bact_node *next = (bact_node *)v6->next;

        call_method(yw->self_full, 144, v6->bacto);

        v6 = next;
    }
}

int recorder_go_to_frame(_NC_STACK_ypaworld *yw, recorder *rcrd, int wanted_frame_id)
{
    int frame_id = wanted_frame_id;
    int cur_frame_id = 0;

    if ( frame_id >= 0 )
    {
        if ( frame_id >= rcrd->field_74 )
            frame_id = rcrd->field_74 - 1;
    }
    else
    {
        frame_id = 0;
    }

    if ( rcrd->mfile )
    {
        FClose(rcrd->mfile->file_handle);
        del_MFILE(rcrd->mfile);
        rcrd->mfile = NULL;
    }

    if ( recorder_open_replay(rcrd) )
    {
        while ( read_next_IFF(rcrd->mfile, 2) != -2 )
        {
            MFILE_S1 *v7 = GET_FORM_INFO_OR_NULL(rcrd->mfile);

            if ( v7->TAG != TAG_FORM || v7->TAG_EXTENSION != TAG_FRAM )
            {
                read_default(rcrd->mfile);
            }
            else
            {
                if ( cur_frame_id == frame_id )
                {
                    recorder_read_framedata(rcrd);

                    yw->field_1614 = rcrd->time;

                    sub_46FDA0(yw, rcrd, 1.0, 0);
                    return 1;
                }

                cur_frame_id++;
                read_default(rcrd->mfile);
            }
        }
    }
    return 0;
}


void ypaworld_func163__sub1(_NC_STACK_ypaworld *yw, recorder *rcrd, int a3)
{
    if ( a3 )
    {
        rcrd->field_78 &= 0xFFFFFFFE;

        while ( rcrd->field_74 - 1 != rcrd->frame_id  &&  (a3 + yw->field_1614) > rcrd->time )
        {
            if ( read_next_IFF(rcrd->mfile, 2) != -1 )
            {
                MFILE_S1 *v5 = GET_FORM_INFO_OR_NULL(rcrd->mfile);

                if ( v5->TAG == TAG_FORM && v5->TAG_EXTENSION == TAG_FRAM )
                    recorder_read_framedata(rcrd);
            }
        }


        if ( rcrd->field_74 - 1 == rcrd->frame_id )
        {
            recorder_go_to_frame(yw, rcrd, 0);
        }
        else
        {
            if ( rcrd->field_78 & 1 )
            {
                yw->field_1614 = rcrd->time;
                sub_46FDA0(yw, rcrd, 1.0, a3);
            }
            else
            {
                float v9 = (float)a3 / (float)(rcrd->time - yw->field_1614);

                yw->field_1614 += a3;

                sub_46FDA0(yw, rcrd, v9, a3);
            }
        }
    }
}

void ypaworld_func163__sub2__sub1(_NC_STACK_ypaworld *yw, float fperiod, struC5 *inpt)
{
    recorder *rcrd = yw->replayer;

    float v20 = rcrd->rotation_matrix.m20;
    float v18 = rcrd->rotation_matrix.m22;

    float v13 = inpt->sliders_vars[0] * 250.0 * fperiod;
    float v14 = -inpt->sliders_vars[2] * 250.0 * fperiod;
    float v15 = -inpt->sliders_vars[1] * 150.0 * fperiod;

    float v17 = sqrt( POW2(v20) + POW2(v18) );
    if ( v17 > 0.0 )
    {
        v20 /= v17;
        v18 /= v17;
    }

    rcrd->field_44.sz += v15 * v18;
    rcrd->field_44.sx += v15 * v20;

    float v21 = rcrd->rotation_matrix.m00;
    float v19 = rcrd->rotation_matrix.m02;

    float v16 = sqrt( POW2(v21) + POW2(v19) );
    if ( v16 > 0.0 )
    {
        v21 /= v16;
        v19 /= v16;
    }

    rcrd->field_44.sy += v14;
    rcrd->field_44.sz += v19 * v13;
    rcrd->field_44.sx += v21 * v13;
}

void ypaworld_func163__sub2__sub0(_NC_STACK_ypaworld *yw, float fperiod, struC5 *inpt)
{
    float v3 = inpt->sliders_vars[10] * 2.5 * fperiod;

    if ( fabs(v3) > 0.001 )
    {
        float cs = cos(v3);
        float sn = sin(-v3);

        mat3x3 a2;
        a2.m00 = cs;
        a2.m01 = 0;
        a2.m02 = sn;
        a2.m10 = 0;
        a2.m11 = 1.0;
        a2.m12 = 0;
        a2.m20 = -sn;
        a2.m21 = 0;
        a2.m22 = cs;

        mat3x3 v7;
        mat_mult(&yw->replayer->rotation_matrix, &a2, &v7);
        yw->replayer->rotation_matrix = v7;
    }

    float v5 = inpt->sliders_vars[11] * 2.5 * fperiod;

    if ( fabs(v5) > 0.001 )
    {
        float cs = cos(v5);
        float sn = sin(v5);

        mat3x3 a2;
        a2.m00 = 1.0;
        a2.m01 = 0;
        a2.m02 = 0;
        a2.m10 = 0;
        a2.m11 = cs;
        a2.m12 = sn;
        a2.m20 = 0;
        a2.m21 = -sn;
        a2.m22 = cs;

        mat3x3 a3;
        mat_mult(&a2, &yw->replayer->rotation_matrix, &a3);
        yw->replayer->rotation_matrix = a3;
    }
}

void ypaworld_func163__sub2(_NC_STACK_ypaworld *yw, recorder *rcrd, __NC_STACK_ypabact *bact, struC5 *inpt)
{
    extern tehMap robo_map;
    extern squadMan squadron_manager;

    float fperiod = inpt->period / 1000.0;

    if ( yw->field_17c0 || !(inpt->winp131arg.flag & 0x80) )
    {
        if ( yw->field_17c0 )
        {
            if ( inpt->winp131arg.flag & 0x80 )
                yw->field_17c0 = 0;
        }
    }
    else
    {
        if ( inpt->winp131arg.selected_btn != &robo_map.frm_1  &&  inpt->winp131arg.selected_btn != &squadron_manager.lstvw.frm_1 )
            yw->field_17c0 = 1;
    }

    if ( inpt->but_flags & 1 )
    {
        rcrd->rotation_matrix.m00 = 1.0;
        rcrd->rotation_matrix.m01 = 0;
        rcrd->rotation_matrix.m02 = 0;
        rcrd->rotation_matrix.m10 = 0;
        rcrd->rotation_matrix.m11 = 1.0;
        rcrd->rotation_matrix.m12 = 0;
        rcrd->rotation_matrix.m20 = 0;
        rcrd->rotation_matrix.m21 = 0;
        rcrd->rotation_matrix.m22 = 1.0;
    }

    ypaworld_func163__sub2__sub1(yw, fperiod, inpt);

    if ( yw->field_17c0 )
        ypaworld_func163__sub2__sub0(yw, fperiod, inpt);

    if ( rcrd->field_80 == 16 )
    {
        recorder_set_bact_pos(yw, bact, &rcrd->field_44);
        bact->field_651 = rcrd->rotation_matrix;
    }
    else if ( rcrd->field_80 == 18 )
    {

        bact_node *v11 = (bact_node *)yw->field_1b88->head;
        __NC_STACK_ypabact *v12 = NULL;

        while (v11->next)
        {
            if ( rcrd->field_84 == v11->bact->ypabact__id )
            {
                v12 = v11->bact;
                break;
            }

            v11 = (bact_node *)v11->next;
        }

        if ( v12 )
        {
            xyz v35;
            v35.sx = v12->field_651.m10 * rcrd->field_44.sy + v12->field_651.m00 * rcrd->field_44.sx + v12->field_651.m20 * rcrd->field_44.sz + v12->field_621.sx;
            v35.sy = v12->field_651.m11 * rcrd->field_44.sy + v12->field_651.m01 * rcrd->field_44.sx + v12->field_651.m21 * rcrd->field_44.sz + v12->field_621.sy;
            v35.sz = v12->field_651.m12 * rcrd->field_44.sy + v12->field_651.m02 * rcrd->field_44.sx + v12->field_651.m22 * rcrd->field_44.sz + v12->field_621.sz;

            recorder_set_bact_pos(yw, bact, &v35);
            mat_mult(&rcrd->rotation_matrix, &v12->field_651, &bact->field_651);
        }
    }
    else if ( rcrd->field_80 == 20 )
    {
        bact_node *v17 = (bact_node *)yw->field_1b88->head;
        __NC_STACK_ypabact *v18 = NULL;

        while (v17->next)
        {
            if ( rcrd->ctrl_bact_id == v17->bact->ypabact__id )
            {
                v18 = v17->bact;
                break;
            }

            v17 = (bact_node *)v17->next;
        }

        if ( v18 )
        {
            xyz a3a;
            a3a.sx = v18->field_651.m10 * rcrd->field_44.sy + v18->field_651.m00 * rcrd->field_44.sx + v18->field_651.m20 * rcrd->field_44.sz + v18->field_621.sx;
            a3a.sy = v18->field_651.m11 * rcrd->field_44.sy + v18->field_651.m01 * rcrd->field_44.sx + v18->field_651.m21 * rcrd->field_44.sz + v18->field_621.sy;
            a3a.sz = v18->field_651.m12 * rcrd->field_44.sy + v18->field_651.m02 * rcrd->field_44.sx + v18->field_651.m22 * rcrd->field_44.sz + v18->field_621.sz;
            recorder_set_bact_pos(yw, bact, &a3a);

            mat_mult(&rcrd->rotation_matrix, &v18->field_651, &bact->field_651);
        }
    }

    bact->field_605.sx = bact->field_62D.sx - bact->field_621.sx;
    bact->field_605.sy = bact->field_62D.sy - bact->field_621.sy;
    bact->field_605.sz = bact->field_62D.sz - bact->field_621.sz;

    float v39 = sqrt( POW2(bact->field_605.sx) + POW2(bact->field_605.sy) + POW2(bact->field_605.sz) );
    if ( v39 <= 0.0 )
    {
        bact->field_605.sx = 1.0;
        bact->field_605.sy = 0;
        bact->field_605.sz = 0;
        bact->field_611 = 0;
    }
    else
    {
        bact->field_605.sx /= v39;
        bact->field_605.sy /= v39;
        bact->field_605.sz /= v39;

        if ( fperiod <= 0.0 )
            bact->field_611 = 0;
        else
            bact->field_611 = v39 / fperiod / 6.0;
    }

    bact->field_87D.grp_1 = bact->field_621;
    bact->field_87D.scale_rotation = bact->field_651;
}

void ypaworld_func163__sub0(_NC_STACK_ypaworld *yw, struC5 *inpt)
{

}





//Scene events funcs

int sub_4D51A4(_NC_STACK_ypaworld *yw)
{
    bact_node *bct = (bact_node *)yw->bact_list.head;

    while ( bct->next )
    {

        if ( bct->bact != yw->field_1b80 && bct->bact->field_24 == 3 && bct->bact->field_3D5 != 2 )
            return (yw->field_1b80 != yw->field_1b84 && !yw->field_1b70) || yw->field_2414;

        bct = (bact_node *)bct->next;
    }

    return 1;
}

int sub_4D5218(_NC_STACK_ypaworld *yw)
{
    bact_node *bct = (bact_node *)yw->bact_list.head;

    while ( bct->next )
    {

        if ( bct->bact != yw->field_1b80 && bct->bact->field_24 == 3 && bct->bact->field_3D5 != 2 )
            return (yw->field_1b80 != yw->field_1b84 && !yw->field_1b70) || yw->field_2414 <= 0;

        bct = (bact_node *)bct->next;
    }

    return 1;
}

int sub_4D5160(_NC_STACK_ypaworld *yw)
{
    bact_node *bct = (bact_node *)yw->bact_list.head;

    while ( bct->next )
    {

        if ( bct->bact != yw->field_1b80 && bct->bact->field_24 == 3 && bct->bact->field_3D5 != 2 )
            return 0;

        bct = (bact_node *)bct->next;
    }

    return 1;
}

int sub_4D528C(_NC_STACK_ypaworld *yw)
{
    extern tehMap robo_map;

    bact_node *bct = (bact_node *)yw->bact_list.head;

    while ( bct->next )
    {

        if ( bct->bact != yw->field_1b80 && bct->bact->field_24 == 3 && bct->bact->field_3D5 != 2 )
            return (yw->field_1b80 != yw->field_1b84 && !yw->field_1b70) || !(robo_map.cmd_flag & 0x20);

        bct = (bact_node *)bct->next;
    }

    return 1;
}

int sub_4D5300(_NC_STACK_ypaworld *yw)
{
    if ( !yw->field_38 )
        return 0;

    for (int i = 0; i < yw->field_38; i++)
    {
        if ( yw->field_34[i].p_cell )
        {
            if ( yw->field_34[i].p_cell->owner == yw->field_1b80->owner )
            {
                return 1;
            }
        }
    }

    return 0;
}

int sub_4D5348(_NC_STACK_ypaworld *yw)
{
    return yw->field_1b80->p_cell_area->field_3A == 2;
}

int sub_4D5360(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < yw->field_2d90->gate_count; i++)
    {
        if ( yw->field_2d90->gates[i].pcell->field_3A == 6 )
            return 1;
    }

    return 0;
}
