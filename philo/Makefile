# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 18:24:09 by dfranke           #+#    #+#              #
#    Updated: 2022/07/15 10:31:59 by dfranke          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= philo
FILES:= \
		checks \
		init \
		main \
		states \
		terminate \
		threads \
		utils \

#-------libft--------
LIBFT_DIR:=./libft/

CC:=gcc
SOURCES_DIR:=srcs/
HEADER_DIR:=includes/
OBJECTS_DIR:=objs/
IFLAGS:=-I $(HEADER_DIR)
CFLAGS:=-Wall -Werror -Wextra $(IFLAGS) -pthread

#------Paths---------
SOURCES:=$(addprefix $(SOURCES_DIR),$(addsuffix .c,$(FILES)))
OBJECTS:=$(addprefix $(OBJECTS_DIR),$(addsuffix .o,$(FILES)))
#====================

#------Colors--------
BLACK:="\033[1;30m"
RED:="\033[1;31m"
BGREEN:="\033[1;32m"
GREEN:="\033[0;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
#====================
CACHE:=.cache_exists


all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LFLAGS)
	@echo $(BGREEN) " -> OK" $(EOC)
	
$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c | $(CACHE)
	@echo $(CYAN) " -> Compiling $< into $@" $(EOC)
	@$(CC) $(CFLAGS) -c $< -o $@

$(CACHE):
	@mkdir -p $(OBJECTS_DIR)
	@touch $(CACHE)
	
clean:
	@rm -f $(CACHE)
	@rm -rf $(OBJECTS_DIR)
	@echo $(GREEN) " -> $(NAME) cache cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"  -> $(NAME) deleted"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY:		all clean fclean re

norm:
	@norminette -R CheckForbiddenSourceHeader $(SOURCES) $(HEADER_DIR)