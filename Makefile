
CXX = g++
OBJ = main.o audio_buffer.o \
			input/manager.o \
			input/sources/base.o input/sources/midi_file.o input/sources/test.o \
			nodes/base.o nodes/object.o nodes/cosine.o nodes/portaudio.o nodes/gate.o nodes/df2_low_pass.o nodes/adsr.o nodes/voice.o nodes/voice_assigner.o \
		  midi/file.o midi/track.o midi/event.o midi/helpers.o 

DEFS = -Dforeach=BOOST_FOREACH
BIN = dist/synth
FLAGS = -g -I . -Wall ${DEFS} #-Wextra -pedantic
LDFLAGS = -g -l portaudio


$(BIN): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $(BIN)
	cppcheck --quiet --enable=all .
	@echo Remember to do a const correctness check!

##
#  Root Directory
main.o: main.cpp
	$(CXX) $(FLAGS) -o $@ -c $<


audio_buffer.o: audio_buffer.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

##
#  Input Manager Directory
input/manager.o: input/manager.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

input/sources/base.o: input/sources/base.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

input/sources/midi_file.o: input/sources/midi_file.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

input/sources/test.o: input/sources/test.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

##
#  Midi Directory
midi/file.o: midi/file.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

midi/helpers.o: midi/helpers.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

midi/track.o: midi/track.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

midi/event.o: midi/event.cpp
	$(CXX) $(FLAGS) -o $@ -c $<


##
#  Node Directory
nodes/object.o: nodes/object.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/base.o: nodes/base.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/cosine.o: nodes/cosine.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/portaudio.o: nodes/portaudio.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/gate.o: nodes/gate.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/df2_low_pass.o: nodes/df2_low_pass.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/voice.o: nodes/voice.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/voice_assigner.o: nodes/voice_assigner.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

nodes/adsr.o: nodes/adsr.cpp
	$(CXX) $(FLAGS) -o $@ -c $<


clean:
	rm -f $(BIN)
	rm -f $(OBJ)

