#!/bin/sh
green='\e[0;32m'
yellow='\e[0;33m'
white='\e[0;37m'

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

if [ ! -e /usr/bin/rwm ]; then
    ln -s ${PWD}/rwm /usr/bin/rwm
fi

if [ -d /etc/X11/sessions ]; then
    cp rwm-gdm.desktop /etc/X11/sessions/
fi

if [ -d /usr/share/xsessions ]; then
    cp rwm-kdm.desktop /usr/share/xsessions/
fi

if [ -d /usr/share/apps/kdm/sessions ]; then
    cp rwm-kdm.desktop /usr/share/apps/kdm/sessions/
fi

echo -e "${white}***********************************************"
echo -e "        ${green}RWM ${yellow}successfully installed${white}"
echo -e "***********************************************"
