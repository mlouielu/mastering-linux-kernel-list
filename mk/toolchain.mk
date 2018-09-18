CFLAGS_WARN = -Wall -Werror -Wundef -Wstrict-prototypes -Wno-trigraphs		\
			  -fno-strict-aliasing -fno-common

CFLAGS_INCLUDE = \
	-I../include

CFLAGS_DEBUG = -g3 -O0

CFLAGS = \
	-std=gnu99 $(FLAGS_WARN) $(CFLAGS_INCLUDE) $(CFLAGS_DEBUG)
