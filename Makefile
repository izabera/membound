membound: membound.c
	$(CC) -march=native -Ofast -static $^ -o $@
	sudo setcap cap_sys_resource+ep $@
