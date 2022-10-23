#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    esh_tester.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 07:00:01 by moabid            #+#    #+#              #
#    Updated: 2022/09/20 18:55:12 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MINISHELL-TESTER
RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C . > /dev/null
if [ $? -ne 0 ]; then
	echo "${RED}Compilation failed${RESET}"
	exit 1
else
	printf "$BOLDGREEN Compilation succeeded %s$RESET\n" "✓ "
	clear
fi

chmod +x minishell .
touch test
ls > test

function exec_test()
{
	TEST1=$(echo $@ | ./minishell 2>&-)
	ES_1=$(echo $?)
	TEST2=$(echo $@ | bash 2>&-)
	ES_2=$(echo $?)
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$TEST1$RESET\n"
		printf $BOLDGREEN"Expected output : \n%.20s\n$TEST2$RESET\n"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.2
}

# ECHO TESTS
printf "$BOLDBLUE ECHO $BOLDWHITE TESTS $RESET\n"
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
exec_test 'echo -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n -n hi'
exec_test 'echo -n -n -n -n -n -n -n -n -n -n -nnnnnnn -n -n -n -n -n hi'
exec_test 'echo -n -n -n -n -n -n -n -n -n -n -nnnnnnn -n -n -n -n -nnnnnnn hi'
exec_test 'echo -n -n -naaaaaa -n -n hi -n -n -n'

# SIMPLE TESTS
printf "$BOLDBLUE SIMPLE $BOLDWHITE TESTS $RESET\n"
exec_test "cat test"
exec_test "false"
exec_test "true"

# PIPE TESTS
printf "$BOLDBLUE PIPE $BOLDWHITE TESTS $RESET\n"
exec_test 'cat test | grep file | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls | ls | ls | ls | ls | ls | ls | ls | ls | ls'
exec_test 'false | ls | grep file'
exec_test 'ls | true | grep file'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls| echo hi'
exec_test 'ls |echo hi'
# # REDIRECTION TESTS
printf "$BOLDBLUE REDIRECTION $BOLDWHITE TESTS $RESET\n"

exec_test 'ls | grep file | wc -l'
exec_test 'ls | grep file > test2'
exec_test 'ls | grep file | wc -l > test2'
exec_test 'ls | grep file | grep file | grep file | grep file | wc -l > test2'
exec_test 'ls | grep file | wc -l >> test2'
exec_test 'ls | grep file | grep file | grep file | grep file | wc -l >> test2'
exec_test 'ls | grep file | wc -l > test3 | wc -l'
exec_test 'ls | grep file > test2 | wc -l > test3 | wc -l'
exec_test '< test'
exec_test '< test grep hi | wc -l'
exec_test '< test > test2'
exec_test '< test grep file > test2'
exec_test '< test grep hi | wc -l > test2'
exec_test '< test grep hi | grep hi | grep hi | grep hi | wc -l > test2'
exec_test '< test >> test2'
exec_test '< test grep hi | wc -l >> test2'
exec_test '< test grep hi | grep hi | grep hi | grep hi | wc -l >> test2'
exec_test '< test grep hi | wc -l > test3 | wc -l'
exec_test '< test grep hi > test2 | wc -l > test3 | wc -l'
exec_test '< test grep hi > test2 | wc -l > test3 | wc -l > test4'
exec_test '<test'
exec_test '<test grep hi|wc -l'
exec_test '<test>test2'
exec_test '<test grep file>test2'
exec_test '<test grep hi |grep hi| grep hi |grep hi| wc -l>test2'

# EXIT
printf "$BOLDBLUE EXIT $BOLDWHITE TESTS $RESET\n"
exec_test "exit"
exec_test "exit 42"
exec_test "exit 0"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "ls | exit"
exec_test "ls | exit | ls"
exec_test "ls | exit | grep file"

# ERROR 
printf "$BOLDBLUE ERROR $BOLDWHITE TESTS $RESET\n"
exec_test "blabla"
exec_test "echo hi | echoo hi | echo hi"
exec_test '< test grep hi > test2 | wccc -l > test3 | wc -l > test4'
exec_test '< test grep hi > test2 | wc -l > test3 | wccccc -l > test4'
exec_test '< fuck grep file'

# ENV EXPANSIONS
printf "$BOLDBLUE ENV AND EXPORT $BOLDWHITE TESTS $RESET\n"
exec_test 'echo $HOME $USER $PWD'
exec_test 'echo $"HOME" $USE"R" $PWD'
exec_test 'env | sort | grep -v SHLVL | grep -v _='

printf "$BOLDBLUE ERROR $BOLDWHITE TESTS $RESET\n"
exec_test 'echo ||'
exec_test '<'
exec_test '>'
exec_test '<>>'
exec_test '<<'

printf "$BOLDBLUE PLEASE MAKE SURE TO TEST THESE CASES MANUALY\n$RESET"
printf "$BOLDWHITE echo \$bullshit \$bullshit \$bullshit $RESET\n"
printf "$BOLDWHITE girl=guy kid=adult echo \$girl \$kid $RESET\n"

# SYNTAX ERROR
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'


rm "test" test2 test3 test4 test_dir &> /dev/null