xgettext `find src -name '*.cpp'` -o po/tsnake.pot.tmp
msgmerge po/tsnake.pot{,.tmp} -U
rm -f po/tsnake.pot.tmp
( for i in po/*.po; do msgmerge $i po/tsnake.pot -U ; done )

