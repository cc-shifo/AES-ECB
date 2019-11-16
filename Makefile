#
# crypto/aes/Makefile
#

TOP=	.
CC=	g++
OPT_LEVEL = -O0
#OPT_FLAGS = -O2
INCLUDES= -I ./include
CFLAG=-g $(OPT_LEVEL) -W -Wall -Wstrict-prototypes \
	-Wundef -Wunknown-pragmas -Wunreachable-code \
	-Wfloat-equal -W -Wimplicit -Wconversion

CFLAGS= $(INCLUDES) $(CFLAG)
AR=		ar cr

SLIB=$(TOP)/libaesecb.a
DLIB=$(TOP)/libaesecb.so
LIBSRC=aes_core.c \
       aes_ecb.c
LIBOBJ=aes_core.o \
       aes_ecb.o

LDFLAGS = -L. -laesecb
TEST_APP = test.app

all:	so.lib $(TEST_APP)

a.lib:	$(LIBOBJ)
	$(AR) -o $(SLIB) $(LIBOBJ)
#	$(RANLIB) $(SLIB) || echo Never mind.
#	@touch a_lib

# export LD_LIBRARY_PATH=$my_so_lib_path:$LD_LIBRARY_PATH
so.lib:
	$(CC) $(CFLAGS) -o $(DLIB) $(LIBSRC) -fPIC -shared 

$(TEST_APP): main.c aesecblib.h
	$(CC) $(CFLAG) -o $@ $^  -L. -laesecb

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f *.s *.S *.o *.obj lib tags core .pure .nfs* *.old *.bak fluff *.so *.a $(TEST_APP)


	
# DO NOT DELETE THIS LINE -- make depend depends on it.

#aes_cbc.o: ./include/aes.h ./include/modes.h
#aes_cbc.o: ./include/opensslconf.h aes_cbc.c
#aes_cfb.o: ./include/aes.h ./include/modes.h
#aes_cfb.o: ./include/opensslconf.h aes_cfb.c
aes_core.o: ./include/aes.h ./include/e_os2.h
aes_core.o: ./include/opensslconf.h aes_core.c aes_locl.h
#aes_ctr.o: ./include/aes.h ./include/modes.h
#aes_ctr.o: ./include/opensslconf.h aes_ctr.c
aes_ecb.o: ./include/aes.h ./include/e_os2.h
aes_ecb.o: ./include/opensslconf.h aes_ecb.c aes_locl.h
#aes_ige.o: ./e_os.h ./include/aes.h ./include/bio.h
#aes_ige.o: ./include/buffer.h ./include/crypto.h
#aes_ige.o: ./include/e_os2.h ./include/err.h
#aes_ige.o: ./include/lhash.h ./include/opensslconf.h
#aes_ige.o: ./include/opensslv.h ./include/ossl_typ.h
#aes_ige.o: ./include/safestack.h ./include/stack.h
#aes_ige.o: ./include/symhacks.h ../cryptlib.h aes_ige.c aes_locl.h
#aes_misc.o: ./include/aes.h ./include/crypto.h
#aes_misc.o: ./include/e_os2.h ./include/opensslconf.h
#aes_misc.o: ./include/opensslv.h ./include/ossl_typ.h
#aes_misc.o: ./include/safestack.h ./include/stack.h
#aes_misc.o: ./include/symhacks.h aes_locl.h aes_misc.c
#aes_ofb.o: ./include/aes.h ./include/modes.h
#aes_ofb.o: ./include/opensslconf.h aes_ofb.c
#aes_wrap.o: ./e_os.h ./include/aes.h
#aes_wrap.o: ./include/bio.h ./include/buffer.h
#aes_wrap.o: ./include/crypto.h ./include/e_os2.h
#aes_wrap.o: ./include/err.h ./include/lhash.h
#aes_wrap.o: ./include/modes.h ./include/opensslconf.h
#aes_wrap.o: ./include/opensslv.h ./include/ossl_typ.h
#aes_wrap.o: ./include/safestack.h ./include/stack.h
#aes_wrap.o: ./include/symhacks.h ../cryptlib.h aes_wrap.c
