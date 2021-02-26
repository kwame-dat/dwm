/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 40;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]              = {"JetBrains Mono:size=8",
                                        "JoyPixels:size=8:antialias=true:autohint=true",
                                        "FontAwesome:size=8:antialias=true:autohint=true",
                                        };
static const char dmenufont[]       = "JetBrains Mono:size=8";
static const char col_gray1[]           = "#0b1c2c";
static const char col_gray2[]           = "#1a1a1a";
static const char col_gray3[]           = "#96b5B4";
static const char col_gray4[]           = "#d7d7d7";
static const char col_blue[]            = "#9765F4";
static const char col_red[]             = "#8f3d3d";
static const char col_yellow[]          = "#b38c00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_red,  col_blue  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                         instance    title                  tags mask    isfloating   monitor  scratch key */
	{ "Gimp",                        NULL,       NULL,                  0,           1,           -1,       0},
	{ "mpv",                         NULL,       NULL,                  0,           1,           -1,       0},
	{ "Firefox",                     NULL,       NULL,                  1,           0,           -1,       0},
  { "qutebrowser",                 NULL,       NULL,                  1,           0,           -1,       0},
  { "Google-chrome",               NULL,       NULL,                  1,           0,           -1,       0},
  { "Vivaldi-stable",              NULL,       NULL,                  1,           0,           -1,       0},
  { "Chromium",                    NULL,       NULL,                  1,           0,           -1,       0},
  { "Brave-browser",               NULL,       NULL,                  1,           0,           -1,       0},
  { "Firefox",                     NULL,       NULL,                  1,           0,           -1,       0},
  { "Emacs",                       NULL,       NULL,                  2,           0,           -1,       0},
  { "calibre",                     NULL,       NULL,                  2,           0,           -1,       0},
  { "Evolution",                   NULL,       NULL,                  2,           0,           -1,       0},
  { "jetbrains-phpstorm",          NULL,       NULL,                  2,           0,           -1,       0},
  { "whatsdesk",                   NULL,       NULL,                  1 << 2,      0,           -1,       0},
  { "Signal",                      NULL,       NULL,                  1 << 2,      0,           -1,       0},
  { "Slack",                       NULL,       NULL,                  1 << 2,      0,           -1,       0},
  { "Microsoft Teams - Preview",   NULL,       NULL,                  1 << 3,      0,           -1,       0},
  { "zoom",                        NULL,       NULL,                  1 << 3,      0,           -1,       0},
  { "DBeaver",                     NULL,       NULL,                  1 << 4,      0,           -1,       0},
  { "Insomnia",                    NULL,       NULL,                  1 << 5,      0,           -1,       0},
  { "Postman",                     NULL,       NULL,                  1 << 5,      0,           -1,       0},
  { "VirtualBox Manager",          NULL,       NULL,                  1 << 6,      0,           -1,       0},
  { "Nextcloud",                   NULL,       NULL,                  1 << 8,      0,           -1,       0},
	{ NULL,                          NULL,       "scratchpad",          0,           1,           -1,       's'},
	{ NULL,                          NULL,       "musicscratchpad",     0,           1,           -1,       'm'},
	{ NULL,                          NULL,       "vpnscratchpad",       0,           1,           -1,       'v'},
	{ NULL,                          NULL,       "webcamscratchpad",    0,           1,           -1,       'w'},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */


#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#define XF86Search            0x1008ff1b
#include "vanitygaps.c"
#include <X11/XF86keysym.h>


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|M|",      centeredmaster },
	{ "HHH",      grid },
	{ "[@]",      spiral },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *filecmd[]  = { "thunar", NULL };
static const char *scratchpadcmd[] = {"s", "alacritty", "-t", "scratchpad", NULL}; 
static const char *musicscratchpadcmd[] = {"m", "alacritty", "-t", "musicscratchpad", "-e", "ncmpcpp", NULL}; 
static const char *vpnscratchpadcmd[] = {"v", "alacritty", "-t", "vpnscratchpad", "-e", "vpn", NULL}; 
static const char *webcamscratchpadcmd[] = {"w", "mpv", "--title=", "webcamscratchpad", "av://v4l2:/dev/video0 --profile low-latency --untimed", NULL}; 

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_equal,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },

  /* MOD +.....  KEYS */
	{ MODKEY,                       XK_t,             togglescratch,     {.v = scratchpadcmd } },
	{ MODKEY,                       XK_f,             togglefullscr,     {0} },
	{ MODKEY,                       XK_space,         spawn,             SHCMD("~/.config/rofi/launcher/launcher.sh") },
	{ MODKEY,                       XK_s,             togglesticky,      {0} },
  { MODKEY,                       XK_e,             spawn,             SHCMD("emacsclient -c -a ''") },
	{ MODKEY,		                    XK_bracketright,  cyclelayout,       {.i = -1 } },
	{ MODKEY,                       XK_bracketleft,   cyclelayout,       {.i = +1 } },
	{ MODKEY,                       XK_p,             spawn,             SHCMD("rofi-pass") },
	{ MODKEY,                       XK_b,             spawn,             SHCMD("rofi-surfraw") },
	{ MODKEY,                       XK_r,             quit,              {1} }, 
	{ MODKEY,                       XK_Return,        spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_q,             killclient,     {0} },

  /* MOD + SHIFT KEYS */
	{ MODKEY|ShiftMask,             XK_Return,        spawn,      {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_b,             togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_v,             togglescratch,  {.v = vpnscratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_w,             togglescratch,  {.v = webcamscratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_m,             togglescratch,  {.v = musicscratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_j,             rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,             rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_s,             spawn,          SHCMD("flameshot gui")}, 


  /* SUPER + ALT KEYS */
  { MODKEY|Mod1Mask,              XK_a,  spawn,         SHCMD("emacsclient -c -a '' --eval '(itechytony/day-view)'") },
  { MODKEY|Mod1Mask,              XK_e,  spawn,         SHCMD("emacs") },
  { MODKEY|Mod1Mask,              XK_m,  spawn,         SHCMD("xfce4-settings-manager") },
  { MODKEY|Mod1Mask,              XK_s,  spawn,         SHCMD("slack") },
  { MODKEY|Mod1Mask,              XK_t,  spawn,         SHCMD("teams") },
  { MODKEY|Mod1Mask,              XK_p,  spawn,         SHCMD("pamac-manager") },
  { MODKEY|Mod1Mask,              XK_v,  spawn,         SHCMD("pavucontrol") },
  { MODKEY|Mod1Mask,              XK_f,  spawn,         SHCMD("firefox") },
  { MODKEY|Mod1Mask,              XK_g,  spawn,         SHCMD("chromium -no-default-browser-check") },
  { MODKEY|Mod1Mask,              XK_q,  spawn,         SHCMD("qutebrowser") },
  { MODKEY|Mod1Mask,              XK_b,  spawn,         SHCMD("brave") },
  { MODKEY|Mod1Mask,              XK_w,  spawn,         SHCMD("whatsdesk") },
  { MODKEY|Mod1Mask,              XK_d,  spawn,         SHCMD("dbeaver") },
  { MODKEY|Mod1Mask,              XK_z,  spawn,         SHCMD("zoom") },
  { MODKEY|Mod1Mask,              XK_i,  spawn,         SHCMD("insomnia-designer") },
  { MODKEY|Mod1Mask,              XK_c,  spawn,         SHCMD("rofi -show calc") },
  { MODKEY|Mod1Mask,              XK_o,  spawn,         SHCMD("picom-toggle") },
  { MODKEY|Mod1Mask,              XK_n,  spawn,         SHCMD("nitrogen") },

  /* MULTIMEDIA KEYS */
  { 0, XF86XK_AudioMute,		        spawn,		SHCMD("amixer -q set Master toggle") },
  { 0, XF86XK_AudioRaiseVolume,	    spawn,		SHCMD("amixer -q set Master 2%+") },
  { 0, XF86XK_AudioLowerVolume,	    spawn,		SHCMD("amixer -q set Master 2%-") },
  { 0, XF86XK_AudioPrev,		        spawn,		SHCMD("playerctl previous") },
  { 0, XF86XK_AudioNext,		        spawn,		SHCMD("playerctl next") },
  { 0, XF86XK_AudioPause,		        spawn,		SHCMD("playerctl play-pause") },
  { 0, XF86XK_AudioPlay,		        spawn,		SHCMD("playerctl play-pause") },
  { 0, XF86XK_AudioStop,		        spawn,		SHCMD("playerctl stop") },
  { 0, XF86XK_AudioRewind,	        spawn,		SHCMD("mpc seek -10") },
  { 0, XF86XK_AudioForward,	        spawn,		SHCMD("mpc seek +10") },
  { 0, XF86XK_AudioMicMute,	        spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
  { 0, XF86XK_PowerOff,		          spawn,		SHCMD("sysact") },
  { 0, XF86XK_ScreenSaver,	        spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
  { 0, XF86XK_MonBrightnessUp,	    spawn,		SHCMD("xbacklight -inc 2") },
  { 0, XF86XK_MonBrightnessDown,    spawn,		SHCMD("xbacklight -dec 2") },

  { 0, XF86XK_AudioMute,		        spawn,		SHCMD("amixer -q set Master toggle") },

  { 0, XK_F7,       togglescratch,  {.v = vpnscratchpadcmd } },
  { 0, XK_F8,       togglescratch,  {.v = musicscratchpadcmd } },
  { 0, XF86Search,  spawn,          SHCMD("~/.config/rofi/launcher/launcher.sh") },
  { 0, XK_F9,       spawn,          SHCMD("~/.config/rofi/launcher/launcher.sh") },
  { 0, XK_F11,      togglefullscr,  {0}},

  /* MISC KEYS */
  { ControlMask|Mod1Mask,         XK_Delete,  spawn,         SHCMD("xkill") },
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

