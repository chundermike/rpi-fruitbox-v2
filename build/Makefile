CXX          = g++
# CXXFLAGS     = -O3 -g0 -std=c++14 -D_RPI
CXXFLAGS     = -O3 -g0 -std=c++17 -D_RPI
INC          = -I/opt/vc/include
DEPS         = fruitbox.hpp fruitbox_types.hpp title_strips.hpp status.hpp playqueue.hpp audio.hpp config.hpp config_base.hpp database.hpp display.hpp \
               engine.hpp fruitbox_logo.hpp fruitbox_mouse_pointer.hpp dialog_font.hpp status_events.hpp userguide.hpp bitmap.hpp \
               joystick.hpp touch_areas.hpp mouse.hpp display_base.hpp input.hpp gpio.hpp dialog.hpp spectrum_analyser.hpp fast_random.hpp menus.hpp \
               input_event_labels.hpp camera_shutter_click.hpp
OBJ          = fruitbox.o display_base.o playqueue.o audio.o config.o database.o display.o engine.o title_strips.o status.o userguide.o bitmap.o joystick.o mouse.o input.o gpio.o dialog.o spectrum_analyser.o fast_random.o menus.o touch_areas.o
LIBS         = -lmpg123 -lm -ldl -L/opt/vc/lib/ -lcurl -lbcm_host -lpthread
ALLEGRO_LIBS = allegro-static-5 allegro_memfile-static-5 allegro_font-static-5 allegro_ttf-static-5 allegro_primitives-static-5 \
               allegro_image-static-5 allegro_audio-static-5 allegro_acodec-static-5 allegro_video-static-5

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INC)

../rpi/fruitbox: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CXXFLAGS) $(LIBS) `pkg-config --libs --static $(ALLEGRO_LIBS)`

.PHONY: clean
clean:
	rm -f *.o
	rm -f ../rpi/fruitbox
	touch Makefile
	touch *.?pp
