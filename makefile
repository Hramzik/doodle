

cc         = gcc
cppfolder1 = src/hash_table/cpp
cppfolder2 = src/func_testing/cpp
cppfolder3 = src/optimizing/cpp
cppfolder4 = src/timer/cpp
exefolder  = exe

define flags
	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
endef

define compile_3_opt
	$(sc) $(cc) $1 $2 $3 -o $4 $(flags) -O3 -mavx2
endef

define compile_6_opt_pg
	$(sc) $(cc) $1 $2 $3 $4 $5 $6 -o $7 $(flags) -O0 -mavx2 -pg
endef

define compile_5_opt_pg
	$(sc) $(cc) $1 $2 $3 $4 $5 -o $6 $(flags) -O2 -mavx2 -pg
endef

sc = @ #showcommands
default_name = prog
default_path = $(exefolder)/$(default_name)


all: optimize


test:
	$(call compile_opt,     $(cppfolder)/main.cpp, $(cppfolder)/graphics.cpp, $(default_path))

test_functions:
	$(call compile_3_opt, \
	$(cppfolder1)/hash_table.cpp, \
	$(cppfolder2)/main.cpp, \
	$(cppfolder2)/func_testing.cpp, \
	$(default_path))

optimize:
	$(call compile_6_opt_pg, \
	$(cppfolder1)/hash_table.cpp, \
	$(cppfolder1)/crc32.obj, \
	$(cppfolder2)/func_testing.cpp, \
	$(cppfolder3)/build_and_search.cpp, \
	$(cppfolder3)/main.cpp, \
	$(cppfolder4)/timer.cpp, \
	$(default_path))