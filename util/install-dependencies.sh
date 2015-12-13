. /etc/os-release

ensure() {
	while [ "$1" ]; do
		which $1 || echo "Missing $1"
		shift
	done
}

case "$NAME" in
	Ubuntu|Debian)
		sudo apt-get install libncurses-dev build-essential make gettext
		;;
	"AOSC OS")
		sudo apt-get install ncurses make gettext gcc
		;;
	*)
		echo "Unsupported Distribution." 1>&2
		echo "You need to ensure you have the following binaries" 1>&2
		echo "g++ (version 4.8+), make, msgfmt" 1>&2
		echo "And you should ensure you have development files of " 1>&2
		echo "ncurses library installed." 1>&2
		ensure g++ make msgfmt
		[ -e /usr/include/curses.h ] && echo "Missing curses development files"
		;;
esac
	
