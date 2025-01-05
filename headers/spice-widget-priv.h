/* -*- Mode: C; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
   Copyright (C) 2010 Red Hat, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __SPICE_WIDGET_PRIV_H__
#define __SPICE_WIDGET_PRIV_H__

#include <glib-object.h>

G_BEGIN_DECLS

extern "C"
{
#undef signals
#include "spice-widget.h"
#include "spice-grabsequence.h"
#include <GL/gl.h>
}
// 使用前向声明
class SpiceQt;

#define SPICE_DISPLAY_GET_PRIVATE(obj)                                  \
    (G_TYPE_INSTANCE_GET_PRIVATE((obj), SPICE_TYPE_DISPLAY, SpiceDisplayPrivate))

struct _SpiceDisplayPrivate {
    gint                    channel_id;
    gint                    monitor_id;

    /* options */
    bool                    keyboard_grab_enable;
    gboolean                keyboard_grab_inhibit;
    bool                    mouse_grab_enable;
    bool                    resize_guest_enable;

    /* state */
    gboolean                ready;
    gboolean                monitor_ready;
    enum SpiceSurfaceFmt    format;
    gint                    width, height, stride;
    gint                    shmid;
    gpointer                data_origin; /* the original display image data */
    gpointer                data; /* converted if necessary to 32 bits */
    GLuint                  texture_id;  // OpenGL 纹理 ID

    /* window border */
    gint                    ww, wh, mx, my;


    gboolean                cursor_init_done;     // 是否完成光标初始化
    gint                    cursor_width;          // 光标宽度
    gint                    cursor_height;         // 光标高度
    gint                    cursor_hot_x;          // 光标热点 X 坐标
    gint                    cursor_hot_y;          // 光标热点 Y 坐标
    gint                    cursor_x;              // 光标 X 坐标
    gint                    cursor_y;              // 光标 Y 坐标
    gboolean                cursor_visible;        // 光标是否可见
    gpointer                cursor_data;           // 光标图像数据

    bool                    convert;
    bool                    have_mitshm;
    gboolean                allow_scaling;
    gboolean                only_downscale;
    gboolean                disable_inputs;



    SpiceSession            *session;
    SpiceMainChannel        *main;
    SpiceChannel            *display;
    SpiceCursorChannel      *cursor;
    SpiceInputsChannel      *inputs;
    SpiceSmartcardChannel   *smartcard;
    SpiceQt                 *spiceQtInstance;

    enum SpiceMouseMode     mouse_mode;
    int                     mouse_grab_active;
    bool                    mouse_have_pointer;
    int                     mouse_last_x;
    int                     mouse_last_y;
    int                     mouse_guest_x;
    int                     mouse_guest_y;

    bool                    keyboard_grab_active;
    bool                    keyboard_have_focus;

    const guint16           *keycode_map;
    size_t                  keycode_maplen;
    uint32_t                key_state[512 / 32];
    int                     key_delayed_scancode;
    guint                   key_delayed_id;
    SpiceGrabSequence       *grabseq; /* the configured key sequence */
    gboolean                *activeseq; /* the currently pressed keys */
    gint                    mark;
    guint                   keypress_delay;
    gint                    zoom_level;
};

G_END_DECLS

#endif
