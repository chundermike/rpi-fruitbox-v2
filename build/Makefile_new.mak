CPP         = g++
CFLAGS      = -O3 -g0 -std=c++14
INC         = -I/opt/vc/include
LIBS_RPI    = -lbcm_host
LIBS        = -lmpg123 -lm -ldl -L/opt/vc/lib/ -lcurl
STATIC_LIBS = allegro-static-5 allegro_memfile-static-5 allegro_font-static-5 allegro_ttf-static-5 allegro_primitives-static-5 \
              allegro_image-static-5 allegro_audio-static-5 allegro_acodec-static-5 allegro_video-static-5

%.o: %.cpp %.hpp
	$(CPP) -c -o $@ $< $(CFLAGS) $(INC)

# ./fruitbox: $(OBJ)
../fruitbox: $(OBJ)
#	$(CPP) -Wall -o $@ $^ $(CFLAGS) $(LIBS) $(LIBS_RPI) `pkg-config --libs --static $(STATIC_LIBS)`
	$(CPP) -Wall -o $@ $^ $(CFLAGS) $(LIBS) `pkg-config --libs --static $(STATIC_LIBS)`

.PHONY: clean
clean:
	rm -f *.o
	rm -f ../fruitbox
	touch Makefile
	touch *.?pp
