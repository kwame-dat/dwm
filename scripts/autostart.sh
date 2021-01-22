#!/bin/bash

function run {
  if ! pgrep $1 ;
  then
    $@&
  fi
}

multi-monitor &
# xrandr --output eDP1 --auto --output DP1 --auto --scale 2x2 --right-of eDP1 &

# cursor active at boot
xsetroot -cursor_name left_ptr &

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

xrdb ~/.Xresources &

# Cursor active at boot
xsetroot -cursor_name left_ptr &

# Starting utility applications at boot time
run variety &
run nm-applet &
run xfce4-power-manager &
run picom &
run dunst &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
xmodmap ~/.Xmodmap &
run dwmblocks &

# starting user applications at boot time
run /usr/bin/emacs --daemon &
run copyq &
run nextcloud &
run syncthing -no-browser &
run kdeconnect-indicator &
sudo mount -a &
