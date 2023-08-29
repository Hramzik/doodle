

cc = gcc

MAIN_FOLDER         = src
GAME_FOLDER         = src/game/cpp
ENGINE_FOLDER       = src/engine/cpp
SINGLEPLAYER_FOLDER = src/singleplayer/cpp
TIMER_FOLDER        = src/timer/cpp
LIST_FOLDER         = src/list/cpp
ARRAY_FOLDER        = src/array/cpp
LIB_FOLDER          = src/lib

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
	$(MAIN_FOLDER)/main.cpp \
	$(TIMER_FOLDER)/timer.cpp \
	$(LIST_FOLDER)/list.cpp \
	$(ARRAY_FOLDER)/array.cpp \
	$(LIB_FOLDER)/logs.cpp \
	$(LIB_FOLDER)/my_math.cpp \
	$(GAME_FOLDER)/c-dtors.cpp \
	$(GAME_FOLDER)/render.cpp \
	$(GAME_FOLDER)/game_media.cpp \
	$(GAME_FOLDER)/game.cpp \
	$(GAME_FOLDER)/keyboard.cpp \
	$(GAME_FOLDER)/platforms.cpp \
	$(GAME_FOLDER)/background_render.cpp \
	$(ENGINE_FOLDER)/engine.cpp \
	$(ENGINE_FOLDER)/c-dtors.cpp \
	$(ENGINE_FOLDER)/motion.cpp \
	$(ENGINE_FOLDER)/players.cpp \
	$(ENGINE_FOLDER)/platforms.cpp \
	$(SINGLEPLAYER_FOLDER)/singleplayer.cpp \
	$(SINGLEPLAYER_FOLDER)/c-dtors.cpp \
	$(SINGLEPLAYER_FOLDER)/cheats.cpp \
	$(SINGLEPLAYER_FOLDER)/keyboard.cpp \
	-o $(default_path) $(flags_sdl) $(flags_cut_bc_of_sdl)

