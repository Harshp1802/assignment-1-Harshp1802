all: build

build:
	gcc shell.c pwd.c cd.c ls.c grep.c cat.c mv.c mk_dir.c ch_mod.c rm.c cp.c -o shell -lreadline
