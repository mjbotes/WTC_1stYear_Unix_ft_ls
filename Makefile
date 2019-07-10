NAME = ft_ls

# Project builds and dirs
SRCDIR = ./srcs/
SRCNAMES = ft_filereader.c ft_files.c ft_dirs.c  ft_printlongformat.c ft_timeconverter.c main.c
SRCNAMES += ft_filesort.c ft_flags.c ft_error.c 
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./incudes/
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Libft builds and dirs
LIBDIR = ./ft_printf/libft/
LIBFT = ./ft_printf/libft/libft.a
LIBINC = ./ft_printflibft//

PRINTFDIR = ./ft_printf/
PRINTF = ./ft_printf/libftprintf.a
PRINTFINC = ./ft_printf/include/

# Optimization and Compiler flags and commands
CC = gcc
OPFLAGS = -O3 -funroll-loops
CFLAGS = -Wall -Werror -Wextra
# Debugging flags
DEBUG = -g

# Main rule
all: $(BUILDDIR) $(LIBFT) $(PRINTF) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(DEBUG) $(CFLAGS) -I$(LIBINC) -I$(PRINTFINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(OPFLAGS) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(LIBFT) $(PRINTF)

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

$(PRINTF):
	make -C $(PRINTFDIR)

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
