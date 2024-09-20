.PHONY: all Release Debug  сlean doxygen

all: run_dir/main.exe

Release: run_dir/main.exe

Debug: run_dir/main.exe

сlean:
	rm $(DIROBJFILES)

OBJFILES := main.o read.o sort.o write.o
FLAGS := -Werror -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code  -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE -g

DIROBJFILES := $(addprefix obj/, $(OBJFILES))

doxygen:
	doxygen

run_dir/main.exe : $(DIROBJFILES)
	g++ $(FLAGS) $(DIROBJFILES) -o $@

obj/%.o : %.cpp
	g++ $< -c  -o $@


