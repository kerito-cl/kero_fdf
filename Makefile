
NAME	:= fdf
CFLAGS	:=  -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a
SRCS	:= coloring.c  draw_map.c  ft_split.c \
			 line_algo.c  main.c  matrix.c  matrix_color.c \
			 rotation.c  utils.c error.c \
			gnl/ft_atoi.c  gnl/get_next_line.c  gnl/get_next_line_utils.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx: $(LIBS)

$(LIBS):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -ldl -lglfw -pthread -lm -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
