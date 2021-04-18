GR	= \033[32;1m #	Green
RE	= \033[31;1m #	Red
YE	= \033[33;1m #	Yellow
CY	= \033[36;1m #	Cyan
SCY	= \033[36m #	Small Cyan
RC	= \033[0m #	Reset Colors

NAME = ft_irc
CP = clang++
SRCDIR = ./srcs/
SRC = main.cpp Message.cpp Server.cpp User.cpp Channel.cpp \
		Tools/Utils.cpp Parsing/Init_parser.cpp

SRC := $(addprefix $(SRCDIR), $(SRC))
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -std=c++98 -I ./includes/
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
