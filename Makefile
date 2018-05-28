EXE := mario.exe
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

CPPFLAGS := -IC:\SFML-2.4.2\include -MMD -MP -DSFML_STATIC
CXXFLAGS := -std=c++11 -Wall -W -pedantic
LDFLAGS  := -LC:\SFML-2.4.2\lib
LDLIBS   := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LDLIBS   += -lopengl32 -lwinmm -lgdi32 -ljpeg

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(EXE) $(OBJ) $(DEP)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEP)
endif
