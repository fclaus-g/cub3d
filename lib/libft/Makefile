# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernandoclaus <fernandoclaus@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 10:58:45 by fclaus-g          #+#    #+#              #
#    Updated: 2023/05/23 11:47:36 by fernandocla      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
#fuentes
SRC =  \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_tolower.c \
	ft_toupper.c ft_strlen.c ft_isalnum.c ft_strlcpy.c \
	ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
	ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_itoa.c ft_striteri.c ft_strmapi.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
#compilador
CC = gcc
#flags
LIB = ar -crs #crea la libreria
CFLAGS = -Wall -Werror -Wextra #flags de compilacion
OBJ = $(SRC:.c=.o) #los objetos son los .c pasado a .o
RM = rm -f #comando para borrar
OPTION = -c #opcion para compilar reemplazando el nombre del archivo por *.o
BONUSSRC = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	 ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	 ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
	

BONUSOBJ = $(BONUSSRC:.c=.o)

INCLUDE = libft.h

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDE)#NAME DEPENDE DE OBJ E INCLUDE(que es el .h)
	$(LIB) $(NAME) $(OBJ)
#crea la libreria con los objetos

bonus : $(OBJ) $(BONUSOBJ) $(INCLUDE)
	$(LIB) $(NAME) $(BONUSOBJ) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) $(OPTION) $(SRC)
	
%.o : %.c #los *.o dependen de los *.c
	$(CC) -c $(CFLAGS) $< -o $@
#si un *.c cambia, se recompila el *.o

clean : 
	$(RM) $(OBJ) $(BONUSOBJ)

fclean: clean 
	$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY : all clean fclean re bonus rebonus
