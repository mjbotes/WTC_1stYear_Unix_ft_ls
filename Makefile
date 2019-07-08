NAME = ft_ls

# Project builds and dirs
SRCDIR = ./srcs/
SRCNAMES = ft_fileReader.c ft_files.c ft_dirs.c  ft_printlongformat.c ft_timeConverter.c main.c
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./incudes/
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Libft builds and dirs
LIBDIR = ./libft/
LIBFT = ./libft/libft.a
LIBINC = ./libft//

# Optimization and Compiler flags and commands
CC = gcc
OPFLAGS = -O3 -funroll-loops
CFLAGS = -Wall -Werror -Wextra
# Debugging flags
DEBUG = -g

# Main rule
all: $(BUILDDIR) $(LIBFT) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(DEBUG) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(OPFLAGS) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(LIBFT)

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

# Cleaning up the build files
clean:
	rm -rf $(BUILDDIR)
	make -C $(LIBDIR) clean

# Getting rid of the project file
fclean: clean
	rm -rf $(NAME)
	make -C $(LIBDIR) fclean

# Do both of the above
re: fclean all

# Just in case those files exist in the root dir
.PHONY: all fclean clean re
