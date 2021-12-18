#!/bin/bash
function run {
  if ! pgrep $1 ;
  then
    $@&
  fi
}

# Setup my Touchpad to my liking
xinput --set-prop "SYNA2393:00 06CB:7A13 Touchpad" "libinput Tapping Enabled" 1 &
xinput --set-prop "SYNA2393:00 06CB:7A13 Touchpad" "libinput Natural Scrolling Enabled" 1 &
xinput --set-prop "SYNA2393:00 06CB:7A13 Touchpad" "libinput Accel Speed" 1 &

# Keyboard changes
## make CapsLock behave like Ctrl:
setxkbmap -option ctrl:nocaps &

## make short-pressed Ctrl behave like Escape:
xcape -e 'Control_L=Escape'

## Increase keyboard key repeat
xset r rate 300 80 &

# Cursor active at boot
xsetroot -cursor_name left_ptr &

# Starting utility applications at boot time
run /usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1
run dwmblocks
run dunst
run picom --experimental-backends
run xbindkeys -f ~/.xbindkeysrc
# run variety
run caffeine -a
################ Start Apps At Boot Time ###################
run /usr/bin/emacs --daemon &
run solaar -w hide
run nextcloud &
run redshift &
