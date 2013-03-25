/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-*-medium-*-*-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#212121";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#a1b5cd";
static const char selbordercolor[]  = "#696969";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#97b26b";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "term", "vim", "www", "im", "media", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 2,       False,       -1 },
	{ "surf",  NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Namoroka",  NULL,       NULL,       1 << 2,       False,       -1 },//firefox with code name as wm class
	{ "Gvim",  NULL,       NULL,       1 << 1,       False,       -1 },//gvim 
	{ "Pidgin",  NULL,       NULL,       1 << 3,       True,       -1 }, 
	{ "chromium",  NULL,       NULL,       1 << 2,       False,       -1 }, 
	{ "Chromium",  NULL,       NULL,       1 << 2,       False,       -1 }, 
	{ "google-chrome",  NULL,       NULL,       1 << 2,       False,       -1 }, 
	{ "Google-chrome",  NULL,       NULL,       1 << 2,       False,       -1 }, 
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */
static const int nmaster      = 1;    /* number of clients in master area */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        0x26,                      0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0x5f,                      7)
	TAGKEYS(                        0xe7,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask              button          function        argument */
	{ ClkLtSymbol,          0,                      Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                      Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                      Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                      Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,                 Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,                 Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,       Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                      Button1,        view,           {0} },
	{ ClkTagBar,            0,                      Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,                 Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,                 Button3,        toggletag,      {0} },
};

