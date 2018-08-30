CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = normal_mode.h disp_dir.h command_mode_main.h commandModeDisp.h
OBJ = main.o normal_mode.o commandModeDisp.o command_mode_main.o disp_dir.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

