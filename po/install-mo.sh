set -e
mkdir -p $1

pkg=tsnake

for i in po/*.mo
do
	fname=$(basename $i)
	lang=$(echo $fname | cut -d . -f 1)
	mkdir -p $1/$lang/LC_MESSAGES/
	cp $i $1/$lang/LC_MESSAGES/${pkg}.mo
done
