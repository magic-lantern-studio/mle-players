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
	-livroles $(MLE_ROOT)/lib/mle/rehearsal/Mle3dRole.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dColorMapMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dModelMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dTextureMapMediaRef.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle3dSet.so \
	$(MLE_ROOT)/lib/mle/rehearsal/MleIvStage.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle2dRole.so \
	$(MLE_ROOT)/lib/mle/rehearsal/Mle2dSet.so \
	-lCoin -lSoXt -lXmu -lX11 -lXext
