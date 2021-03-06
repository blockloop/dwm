/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char dmenufont[]       = "TerminessTTF Nerd Font Mono:size=15";
static const char *fonts[]          = { "TerminessTTF Nerd Font Mono:size=15" };
static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#3B4252";
static const char col_gray3[]       = "#D8DEE9";
static const char col_gray4[]       = "#ECEFF4";
static const char col_cyan[]        = "#4C566A";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "5", "6", "7", "", "9" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title                    tags mask     isfloating   monitor */
	{ "Firefox",            NULL,       NULL,                 1 << 1,       0,           -1 },
	{ "Gimp",               NULL,       "GIMP Startup",       0,            1,           -1 },
	{ "Keybase",            NULL,       NULL,                 1 << 3,       0,           -1 },
	{ "Slack",              NULL,       NULL,                 1 << 2,       0,           -1 },
	{ "Spotify",            NULL,       NULL,                 1 << 7,       0,           -1 },
	{ "jetbrains-goland",   NULL,       NULL,                 1 << 6,       0,           -1 },
	{ "jetbrains-goland",   NULL,       "win0",               0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[\\]", dwindle                },
	{ "[@]",  spiral                 },
	{ "|M|",  centeredmaster         },
	{ "[M]",  monocle                },
	{ "[]=",  tile                   },
	{ "><>",  NULL                   }, /* no layout function means floating behavior */
	{ ">M>",  centeredfloatingmaster },
	{ NULL,   NULL                   },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "/usr/bin/rofi", "-show", "combi", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *autorandrcmd[] = { "/usr/bin/autorandr", "--force", "-c", NULL };
/* function key commands */
static const char *mutecmd[] = { "volume", "toggle", NULL };
static const char *volupcmd[] = { "volume", "5%+", NULL };
static const char *voldowncmd[] = { "volume", "5%-", NULL };
static const char *miccmd[] = { "togglemic", NULL };
static const char *blupcmd[] = { "xbacklight", "-inc", "5", NULL };
static const char *bldowncmd[] = { "xbacklight", "-dec", "5", NULL };
/* Spotify media controls */
static const char *spotifyplaycmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.PlayPause", NULL };
static const char *spotifystopcmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Stop", NULL };
static const char *spotifyprevcmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Previous", NULL };
static const char *spotifynextcmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Next", NULL };

static const char *xkillcmd[] = { "xkill", NULL };
static const char *lockscreencmd[] = { "xautolock", "-locknow", NULL };
static const char *sswincmd[] = { "scapture", "win", NULL };
static const char *ssareacmd[] = { "scapture", "area", NULL };


#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
        { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	{ MODKEY,                       XK_u,      focusurgent,    {0} },

	{ 0,                XF86XK_AudioMute,         spawn, {.v = mutecmd } },
	{ 0,                XF86XK_AudioLowerVolume,  spawn, {.v = voldowncmd } },
	{ 0,                XF86XK_AudioRaiseVolume,  spawn, {.v = volupcmd } },
	{ 0,                XF86XK_MonBrightnessUp,   spawn, {.v = blupcmd} },
	{ 0,                XF86XK_MonBrightnessDown, spawn, {.v = bldowncmd} },
	{ 0,                XF86XK_AudioMicMute,      spawn, {.v = miccmd} },
	{ MODKEY|ShiftMask, XK_m,                     spawn, {.v = miccmd} },

	{ 0,                  XF86XK_AudioPlay, spawn, {.v = spotifyplaycmd} },
	{ MODKEY|ControlMask, XK_Return,        spawn, {.v = spotifyplaycmd} },
	{ 0,                  XF86XK_AudioStop, spawn, {.v = spotifystopcmd} },
	{ 0,                  XF86XK_AudioPrev, spawn, {.v = spotifyprevcmd} },
	{ 0,                  XF86XK_AudioNext, spawn, {.v = spotifynextcmd} },

	{ 0,                            XF86XK_Display, spawn, {.v = autorandrcmd} },
	{ MODKEY|ShiftMask|ControlMask, XK_d,           spawn, {.v = autorandrcmd} },

	{ MODKEY|ShiftMask, XK_q,     spawn, {.v = xkillcmd} },
	{ MODKEY,           XK_space, spawn, {.v = roficmd} },
	{ MODKEY|ShiftMask, XK_l,     spawn, {.v = lockscreencmd} },
	{ MODKEY|ShiftMask, XK_a,     spawn, {.v = ssareacmd} },
	{ MODKEY|ShiftMask, XK_w,     spawn, {.v = sswincmd} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

