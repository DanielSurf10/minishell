/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:24:59 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 22:26:21 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	print_result(int num_test, t_token_list *expected, t_token_list *result);
void	add_on_list(t_token_list **token_list, int type, char *lexeme);

void	test_01(int num_test)
{
	// ARRANGE
	char			*line = "";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_02(int num_test)
{
	// ARRANGE
	char			*line = "echo a";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "echo");
	add_on_list(&expected, WORD, "a");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_03(int num_test)
{
	// ARRANGE
	char			*line = "\"a\"b\'c\'";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "\"a\"b\'c\'");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_04(int num_test)
{
	// ARRANGE
	char			*line = "echo \"a\"";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "echo");
	add_on_list(&expected, WORD, "\"a\"");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_05(int num_test)
{
	// ARRANGE
	char			*line = "\"a\" b \'c\'";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "\"a\"");
	add_on_list(&expected, WORD, "b");
	add_on_list(&expected, WORD, "\'c\'");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_06(int num_test)
{
	// ARRANGE
	char			*line = "abc|123";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "abc");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "123");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_07(int num_test)
{
	// ARRANGE
	char			*line = "cmd1 \"|\" arg1";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "cmd1");
	add_on_list(&expected, WORD, "\"|\"");
	add_on_list(&expected, WORD, "arg1");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_08(int num_test)
{
	// ARRANGE
	char			*line = "\"a\'\"";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "\"a\'\"");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_09(int num_test)
{
	// ARRANGE
	char			*line = "<><";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, REDIRECT_INPUT, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_10(int num_test)
{
	// ARRANGE
	char			*line = "\"abc|123\"";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "\"abc|123\"");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_11(int num_test)
{
	// ARRANGE
	char			*line = "\"oi";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	expected = NULL;

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_12(int num_test)
{
	// ARRANGE
	char			*line = "||";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, PIPE, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_13(int num_test)
{
	// ARRANGE
	char			*line = "| |";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, PIPE, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_14(int num_test)
{
	// ARRANGE
	char			*line = "|||";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, PIPE, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_15(int num_test)
{
	// ARRANGE
	char			*line = "(|())";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "(");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "())");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_16(int num_test)
{
	// ARRANGE
	char			*line = "cmd<in";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "cmd");
	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "in");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_17(int num_test)
{
	// ARRANGE
	char			*line = "<<cmd";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_HEREDOC, NULL);
	add_on_list(&expected, WORD, "cmd");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_18(int num_test)
{
	// ARRANGE
	char			*line = ">>cmd";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_OUTPUT_APPEND, NULL);
	add_on_list(&expected, WORD, "cmd");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_19(int num_test)
{
	// ARRANGE
	char			*line = "<<<";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_HEREDOC, NULL);
	add_on_list(&expected, REDIRECT_INPUT, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_20(int num_test)
{
	// ARRANGE
	char			*line = ">><<";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_OUTPUT_APPEND, NULL);
	add_on_list(&expected, REDIRECT_HEREDOC, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_21(int num_test)
{
	// ARRANGE
	char			*line = ">\"><\"<";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "\"><\"");
	add_on_list(&expected, REDIRECT_INPUT, NULL);

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_22(int num_test)
{
	// ARRANGE
	char			*line = "<in cmd|&&><)|>>(|\"|><)\"";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "in");
	add_on_list(&expected, WORD, "cmd");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "&&");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, ")");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, REDIRECT_OUTPUT_APPEND, NULL);
	add_on_list(&expected, WORD, "(");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "\"|><)\"");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_23(int num_test)
{
	// ARRANGE
	char			*line = "oi|alo|bom dia|ola";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "oi");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "alo");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "bom");
	add_on_list(&expected, WORD, "dia");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "ola");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_24(int num_test)
{
	// ARRANGE
	char			*line = "alo&&oi||       oi";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "alo&&oi");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "oi");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_25(int num_test)
{
	// ARRANGE
	char			*line = "ls -l | grep a | cat -e";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "ls");
	add_on_list(&expected, WORD, "-l");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "grep");
	add_on_list(&expected, WORD, "a");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "cat");
	add_on_list(&expected, WORD, "-e");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);
}

void	test_26(int num_test)
{
	// ARRANGE
	char			*line = "< infile";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "infile");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&expected);
	token_clear_list(&result);

}

void	test_27(int num_test)
{
	// ARRANGE
	char			*line = "< infile > outfile";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "infile");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "outfile");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

void	test_28(int num_test)
{
	// ARRANGE
	char			*line = "< infile cat > outfile -e";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "infile");
	add_on_list(&expected, WORD, "cat");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "outfile");
	add_on_list(&expected, WORD, "-e");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

void	test_29(int num_test)
{
	// ARRANGE
	char			*line = "/bin/cat < todo > out > out1 > out2 < todo";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "/bin/cat");
	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "todo");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "out");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "out1");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "out2");
	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "todo");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

void	test_30(int num_test)
{
	// ARRANGE
	char			*line = "< infile1 cat | echo hi > outfile1";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, REDIRECT_INPUT, NULL);
	add_on_list(&expected, WORD, "infile1");
	add_on_list(&expected, WORD, "cat");
	add_on_list(&expected, PIPE, NULL);
	add_on_list(&expected, WORD, "echo");
	add_on_list(&expected, WORD, "hi");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "outfile1");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

void	test_31(int num_test)
{
	// ARRANGE
	char			*line = "cat \'\'";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "cat");
	add_on_list(&expected, WORD, "\'\'");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

void	test_32(int num_test)
{
	// ARRANGE
	char			*line = "echo hello > \"fdasdfsa\"";
	t_token_list	*expected = NULL;
	t_token_list	*result;

	add_on_list(&expected, WORD, "echo");
	add_on_list(&expected, WORD, "hello");
	add_on_list(&expected, REDIRECT_OUTPUT, NULL);
	add_on_list(&expected, WORD, "\"fdasdfsa\"");

	// ACT
	result = get_token_list(line);

	// ASSERT
	print_result(num_test, expected, result);

	// CLEAR
	token_clear_list(&result);
	token_clear_list(&expected);
}

// Tests
// echo a
// "a"b'c'
// echo "a"
// "a" b 'c'
// abc|123
// cmd1 "|" arg1
// "a'"
// <><
// "abc|123"
// "oi
// ||
// | |
// |||
// (|())
// cmd<in
// <<cmd
// >>cmd
// <<<
// >><<
// >"><"<
// <in cmd|&&><)|>>(|"|><)"
// oi|alo|bom dia|ola
// alo&&oi||       oi
// ls -l | grep a | cat -e
// < infile
// < infile > outfile
// < infile cat > outfile -e
// /bin/cat < todo > out > out1 > out2 < todo
// < infile1 cat | echo hi > outfile1
// cat \'\'
// echo hello > \"fdasdfsa\"

int	main(void)
{
	void (*test_functions[])(int) =
	{
		test_01,
		test_02,
		test_03,
		test_04,
		test_05,
		test_06,
		test_07,
		test_08,
		test_09,
		test_10,
		test_11,
		test_12,
		test_13,
		test_14,
		test_15,
		test_16,
		test_17,
		test_18,
		test_19,
		test_20,
		test_21,
		test_22,
		test_23,
		test_24,
		test_25,
		test_26,
		test_27,
		test_28,
		test_29,
		test_30,
		test_31,
		test_32,
	};

	printf(YELLOW "Token tests:" RST "\n");
	for (int i = 0; i < sizeof(test_functions) / sizeof(test_functions[0]); i++)
		test_functions[i](i + 1);
}
