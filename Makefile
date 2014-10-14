TARGET  = Assignment2
SRCS	= 	Util/time \
		Util/cmdLineParser \
		Util/geometry \
		Util/geometry.todo \
		Image/bmp \
		Image/image \
		Image/image.todo \
		Image/jpeg \
		Image/lineSegments \
		Image/lineSegments.todo \
		Ray/mouse \
		Ray/rayBox \
		Ray/rayBox.todo \
		Ray/rayCamera \
		Ray/rayCamera.todo \
		Ray/rayCone \
		Ray/rayCone.todo \
		Ray/rayCylinder \
		Ray/rayCylinder.todo \
		Ray/rayDirectionalLight \
		Ray/rayDirectionalLight.todo \
		Ray/rayFileInstance \
		Ray/rayGroup \
		Ray/rayGroup.todo \
		Ray/rayKey \
		Ray/rayPointLight \
		Ray/rayPointLight.todo \
		Ray/rayScene \
		Ray/rayScene.todo \
		Ray/raySphere \
		Ray/raySphere.todo \
		Ray/raySpotLight \
		Ray/raySpotLight.todo \
		Ray/rayTriangle \
		Ray/rayTriangle.todo \
		Ray/rayWindow \
		main

CC   = g++
CFLAGS		+= -I.
ifeq ($(shell uname), Darwin)
	LFLAGS	+= -LJPEG -lJPEG -framework OpenGL -framework GLUT
else
	LFLAGS	+= -LJPEG -lJPEG -lglut -lGLU -lGL
endif

OBJECTS		= ${addsuffix .o, ${SRCS}}
CLEAN		= *.o *~ ${TARGET} *.dsp *.dsw *.bak Ray/*.o Ray/*~ Image/*.o Image/*~ Util/*.o Util/*~

#############################################################
all: debug

debug: CFLAGS += -DDEBUG -g3
debug: ${TARGET}

release: CFLAGS += -O2 -DRELEASE -pipe -fomit-frame-pointer
release: ${TARGET}

${TARGET}: JPEG/libJPEG.a ${OBJECTS}
	${CC} -o $@ ${OBJECTS} ${LFLAGS}

clean:	
	/bin/rm -f ${CLEAN}
	${MAKE} -C JPEG clean

.cpp.o:
	${CC} ${CFLAGS} -o $@ -c $<

JPEG/libJPEG.a:
	${MAKE} -C JPEG
