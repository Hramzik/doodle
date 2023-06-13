

cc = gcc

MAIN_FOLDER  = src
GAME_FOLDER  = src/game/cpp
FIELD_FOLDER = src/field/cpp
LIB_FOLDER   = src/lib

exefolder = exe

define flags
	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
endef

define flags_sdl
	-LC:\Users\hramz_3vliuy6\Desktop\lib\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
endef

define flags_cut_bc_of_sdl
	-Wshadow -Winit-self -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
endef

define compile_sdl_opt_4
	$(sc) $(cc) $1 $2 $3 $4 -o $5 $(flags_sdl) $(flags_cut_bc_of_sdl) -Ofast -mavx2
endef

define compile_sdl
	$(sc) $(cc) $1 $2 $3 $4 $5 $6 $7 $8 -o $9 $(flags_sdl) $(flags_cut_bc_of_sdl)
endef

sc = @ #showcommands
default_name = prog
default_path = $(exefolder)/$(default_name)


all: game


game:
	$(sc) $(cc) \
\
	$(MAIN_FOLDER)/main.cpp, \
	$(GAME_FOLDER)/c-dtors.cpp, \
	$(GAME_FOLDER)/game-media.cpp, \
	$(GAME_FOLDER)/game.cpp, \
	$(GAME_FOLDER)/keyboard_input.cpp, \
	$(FIELD_FOLDER)/field.cpp, \
	$(FIELD_FOLDER)/c-dtors.cpp, \
	$(FIELD_FOLDER)/players.cpp, \
	$(FIELD_FOLDER)/platforms.cpp, \
	$(LIB_FOLDER)/logs.cpp, \
\
	-o $(default_path) $(flags_sdl) $(flags_cut_bc_of_sdl)

