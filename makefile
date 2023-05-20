

cc        = gcc
cppfolder = src/cpp
exefolder = exe

define flags
	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
endef

define compile_opt
	$(sc) $(cc) $1 $2 $3 $4 $5 $6 -o $7 $(flags) -O3 -mavx2
endef

define compile
	$(sc) $(cc) $1 $2 $3 $4 $5 $6 -o $7 $(flags)
endef

sc = @ #showcommands
default_name = prog
default_path = $(exefolder)/$(default_name)


all: mixer


test:
	$(call compile_opt,     $(cppfolder)/main.cpp, $(cppfolder)/graphics.cpp, $(default_path))

hash:
	$(call compile_opt, \
	$(cppfolder)/main.cpp, \
	$(cppfolder)/common.cpp, \
	$(cppfolder)/graphics/graphics.cpp, \
	$(cppfolder)/alpha/alpha.cpp, $(default_path))

