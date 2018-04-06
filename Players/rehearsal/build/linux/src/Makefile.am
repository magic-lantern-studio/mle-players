bin_PROGRAMS=player

# Sources for player.
player_SOURCES= $(top_srcdir)/../../src/title.cxx $(top_srcdir)/../../src/main.cxx

# Compiler options for player
player_CPPFLAGS = -DMLE_REHEARSAL -DMLE_NOT_DLL -I$(MLE_ROOT)/include

# Libraries for player. The link order of the DSOs is important in order to resolve
# interdependencies between the stage, sets and roles. This is an architectural
# issue with how the parts are implemented.
player_LDADD = \
	-L$(MLE_ROOT)/lib/mle/rehearsal -lmlert -lXm -lXt \
	-L$(MLE_ROOT)/lib -lmleatk -lDWP -lmlmath \
	-livroles $(MLE_ROOT)/lib/mle/rehearsal/Mle3dRole.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dColorMapMediaref.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dModelMediaref.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dTextureMapMediaref.so \
	$(MLE_ROOT)/lib/Mle3dSet.so \
	$(MLE_ROOT)/lib/mle/rehearsal/MleIvStage.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle2dRole.so \
	$(MLE_ROOT)/lib/Mle2dSet.so \
	-lCoin -lSoXt -lXmu -lX11 -lXext
