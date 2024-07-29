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
CFLAGS	= -g -Wextra -Wall -Werror
HEADERS	= -I ./include -I $(LIBMLX)/include/MLX42/ -I $(LIBFT) -I $(LIBGNL) #esto es para que busque los .h en la carpeta include
LIBS	= $(LIBMLX)/libmlx42.a -Iinclude -lglfw -ldl -pthread -lm
LIBS42	= -framework Cocoa -framework OpenGL -framework IOKit $(LIBMLX)/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC		= gcc
SRCS	= src/main.c \
			src/moves.c \
			src/collision.c \
			src/utils.c \
			src/raycaster.c \
			src/player.c \
			src/walls.c \
			src/view.c \
			src/textures.c \
			src/init.c \
			src/parser/scene.c \
			src/parser/stuff.c \
			src/parser/validation.c \
			src/parser/color_textures.c \
			src/parser/utils.c \
			src/parser/errors.c \
			src/parser/is.c \
			src/parser/is_map.c \
			src/parser/strings.c \
			src/parser/fill_map.c \

OBJS	= ${SRCS:.c=.o}
BONUSSRC =	src/bonus/main_bonus.c \
			src/bonus/moves_bonus.c \
			src/bonus/collision_bonus.c \
			src/bonus/raycaster_bonus.c \
			src/bonus/player_bonus.c \
			src/bonus/walls_bonus.c \
			src/bonus/view_bonus.c \
			src/bonus/parser/scene_bonus.c \
			src/bonus/parser/stuff_bonus.c \
			src/bonus/parser/validation_bonus.c \
			src/bonus/parser/color_textures_bonus.c \
			src/bonus/parser/utils_bonus.c \
			src/bonus/parser/errors_bonus.c \
			src/bonus/parser/is_bonus.c \
			src/bonus/parser/is_map_bonus.c \
			src/bonus/parser/strings_bonus.c \
			src/bonus/parser/fill_map_bonus.c \
			src/bonus/hooks_bonus.c \
			src/bonus/minimap_bonus.c \
			src/bonus/bonus_bonus.c \
			src/bonus/textures_bonus.c \
			src/bonus/init_bonus.c \
			src/bonus/utils_bonus.c \

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

bonus: libmlx libft.a get_next_line.a $(BONUSOBJ) inc/cub3d_bonus.h
	@echo "\n$(AMARILLO) **** Compilando CUB3D BONUS **** $(DEF_COLOR)\n"
	@$(CC) $(BONUSOBJ) $(LIBS) $(LIBFT)/libft.a $(LIBGNL)/get_next_line.a $(HEADERS) -o $(NAME)
	@echo "\n$(VERDE) **** CUB3D BONUS compilado **** $(DEF_COLOR)\n"

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
