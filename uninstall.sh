#!/bin/sh
green='\e[0;32m'
yellow='\e[0;33m'
white='\e[0;37m'

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi
 
if [ -f /usr/bin/rwm ]; then
rm /usr/bin/rwm
fi
 
if [ -f /etc/X11/sessions/rwm-gdm.desktop ]; then
rm /etc/X11/sessions/rwm-gdm.desktop
fi
 
if [ -f /usr/share/xsessions/rwm-kdm.desktop ]; then
rm /usr/share/xsessions/rwm-kdm.desktop
fi
 
if [ -f /usr/share/apps/kdm/sessions/rwm-kdm.desktop ]; then
rm /usr/share/apps/kdm/sessions/rwm-kdm.desktop
fi
 
echo -e "${white}***********************************************"
echo -e " ${green}Antico ${yellow}successfully uninstalled${white}"
echo -e "***********************************************"