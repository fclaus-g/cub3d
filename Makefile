NAME	= cub3d

DEF_COLOR	= \033[0;39m
VERDE		= \033[1;92m
ROJO		= \033[0;91m
AMARILLO	= \033[0;33m
AZUL		= \033[0;34m

#DIRECTORIOS
LIBMLX	= ./MLX42/build
LIBFT	= ./lib/libft
LIBGNL	= ./lib/get_next_line

#COMPILADOR
CFLAGS	= -g -Wextra -Wall -Werror -Wunreachable-code -Ofast -fPIE
HEADERS	= -I ./include -I $(LIBMLX)/include/MLX42/ -I $(LIBFT) -I $(LIBGNL) #esto es para que busque los .h en la carpeta include
LIBS	= $(LIBMLX)/libmlx42.a -Iinclude -lglfw -ldl -pthread -lm
LIBS42	= -framework Cocoa -framework OpenGL -framework IOKit $(LIBMLX)/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC		= gcc
SRCS	= src/main.c \
			src/minimap.c \
			src/moves.c \
			src/map_validation.c \
			src/utils.c \
			src/raycaster.c \
			src/player.c \
			src/walls.c \
			src/view.c \
			src/textures.c \
			src/bonus.c


OBJS	= ${SRCS:.c=.o}
BONUSSRC = ${shell find ./bonus -iname "*.c"} # @TODO: Cambiar a solo los archivos necesarios
BONUSOBJ = ${BONUSSRC:.c=.o}

all: libmlx libft.a get_next_line.a $(NAME)

libft.a:
	@echo "\n$(AMARILLO) **** Compilando LIBFT **** $(DEF_COLOR)\n"
	@make -C ${LIBFT}
	@echo "\n$(VERDE) **** LIBFT compilada **** $(DEF_COLOR)\n"
get_next_line.a:
	@echo "\n$(AMARILLO) **** Compilando GNL **** $(DEF_COLOR)\n"
	@make -C ${LIBGNL}
	@echo "\n$(VERDE) **** GNL compilada **** $(DEF_COLOR)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"

#COMPILACION
$(NAME): $(OBJS) inc/cub3d.h
	@echo "\n$(AMARILLO) **** Compilando CUB3D **** $(DEF_COLOR)\n"
	@$(CC) $(OBJS) $(LIBS) $(LIBFT)/libft.a $(LIBGNL)/get_next_line.a $(HEADERS) -o $(NAME)
	@echo "\n$(VERDE) **** CUB3D compilado **** $(DEF_COLOR)\n"

%.o: bonus/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<\n)"
	
#$(BONUSOBJ):$(BONUSSRC)	
#	$(CC) $(CFLAGS) $(BONUSSRC)

debug:
		@gcc -Wall -Wextra -Werror -g ./bonus/*.c $(LIBFT)/libft.a $(LIBGNL)/get_next_line.a \
		$(LIBS42)
		@echo "\033[0;32mArchivo debug generado"
clean:
	@echo "\n$(AZUL) **** Borrando archivos objeto **** $(DEF_COLOR)\n"
	@rm -f src/*.o
	@rm -f $(BONUSOBJ)
	@make clean -C ${LIBFT}
	@make clean -C ${LIBGNL}
#	@make clean -C ${LIBMLX}
	@echo "\n$(VERDE) **** Archivos objeto borrados **** $(DEF_COLOR)\n"

fclean: clean
	@echo "\n$(AZUL) **** Borrando ejecutable **** $(DEF_COLOR)\n"
	@rm -f $(NAME)
	@rm -f so_long_bonus
	@make fclean -C ${LIBFT}
	@make fclean -C ${LIBGNL}
	@echo "\n$(VERDE) **** Ejecutable borrado **** $(DEF_COLOR)\n"

re: clean all

.PHONY: all, clean, fclean, re, libmlx
