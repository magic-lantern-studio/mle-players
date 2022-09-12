bin_PROGRAMS=player

# Sources for player.
player_SOURCES= $(top_srcdir)/../../src/title.cxx $(top_srcdir)/../../src/main.cxx

# Compiler options for player
player_CPPFLAGS = -DMLE_REHEARSAL -DMLE_DIGITAL_WORKPRINT -DMLE_NOT_DLL -I$(MLE_ROOT)/include

# Libraries for player. The link order of the DSOs is important in order to resolve
# interdependencies between the stage, sets and roles. This is an architectural
# issue with how the parts are implemented.
player_LDADD = \
	-L$(MLE_ROOT)/lib/mle/rehearsal -lmlert -lXm -lXt \
	-L$(MLE_ROOT)/lib -lmleatk -lDWP -lmlmath -lmlutil \
	-L$(MLE_ROOT)/lib/mle/rehearsal -livroles \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dRole.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dColorMapMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dModelMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dTextureMapMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dSet.so \
	$(MLE_ROOT)/lib/mle/rehearsal/MleIvStage.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle2dRole.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle2dSet.so \
	$(MLE_ROOT)/lib/mle/rehearsal/libmlloaders.so \
	-L/usr/local/lib -lCoin -lSoXt -lXmu -lX11 -lXext

player_LDFLAGS = -Wl,-rpath,$(MLE_ROOT)/lib/mle/rehearsal:$(MLE_ROOT)/lib


if HAVE_LOG4CXX
#player_SOURCES += \
#    source.h \
#    source.cpp
	
player_CPPFLAGS += $(LOG4CXX_CFLAGS)
#player_CPPFLAGS += -DLINUX -D_REENTRANT -D_GNU_SOURCE -I/usr/local/include -I/usr/include/apr-1.0

player_LDFLAGS += -Wl,-rpath=/usr/local/lib
player_LDADD += $(LOG4CXX_LIBS)
#player_LDADD += -L/usr/local/lib -llog4cxx
endif