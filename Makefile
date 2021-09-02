# ================================ VARIABLES ================================= #

# The name of your executable
NAME	= webserv

# Compiler and compiling flags
CC	= clang++
CFLAGS	= -Wall -Werror -Wextra -std=c++98

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 #-fsanitize=address
endif

# Folder name
SRCDIR	= srcs/
INCDIR	= includes/
OBJDIR	= bin/

# Add include folder
CFLAGS	+= -I $(INCDIR)

# Linking stage flags
LDFLAGS =

###▼▼▼<src-updater-do-not-edit-or-remove>▼▼▼
# **************************************************************************** #
# **   Generated with https://github.com/lorenuars19/makefile-src-updater   ** #
# **************************************************************************** #

SRCS =\
	./srcs/Tools/Utils.cpp\
	./srcs/Config.cpp\
	./srcs/CheckConfig.cpp\
	./srcs/Parsing/Init_parser.cpp\
	./srcs/main.cpp\
	./srcs/Server.cpp\
	./srcs/SubServ.cpp\
	./srcs/Client.cpp\
	./srcs/Request.cpp\
	./srcs/Response.cpp\
	./srcs/ResponseHeader.cpp\

HEADERS =\
	./includes/Exceptions.hpp\
	./includes/Config.hpp\
	./includes/Server.hpp\
	./includes/General.hpp\
	./includes/Request.hpp\
	./includes/Response.hpp\
	./includes/ResponseHeader.hpp\
	# ./includes/Socket.hpp\

###▲▲▲<src-updater-do-not-edit-or-remove>▲▲▲

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.cpp=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(NAME)

# Compiling
$(OBJDIR)%.o : %.cpp
	@mkdir -p $(OBJDIR)
	#@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(NAME)	: $(SRCS) $(HEADERS) $(OBJS)
	#@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	#@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

# Cleaning
clean :
	#@printf "$(RE)--- Removing $(OBJDIR)$(RC)"
	@rm -rf $(OBJDIR)

fclean : clean
	#@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re
