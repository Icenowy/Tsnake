#ifndef _TSGETTEXT_H
#define _TSGETTEXT_H

#ifndef NO_INTL
#include <libintl.h>
#else
#define textdomain(a)
#define gettext(a) a
#endif

#endif
