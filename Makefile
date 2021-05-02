GR	= \033[32;1m #	Green
RE	= \033[31;1m #	Red
YE	= \033[33;1m #	Yellow
CY	= \033[36;1m #	Cyan
SCY	= \033[36m #	Small Cyan
RC	= \033[0m #	Reset Colors

NAME = webserv
CP = clang++
SRCDIR = ./srcs/
SRC = main.cpp Parsing/Init_parser.cpp Tools/Utils.cpp Config.cpp

SRC := $(addprefix $(SRCDIR), $(SRC))
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -std=c++98 -I ./includes/ #-fsanitize=address
RM = /bin/rm -f

$(NAME): $(SRC)
	$(CP) $(CFLAGS) $? -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
