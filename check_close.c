#include "shell.h"


/**
 * c_dir_shell - changes the current
 * working directory of the shell
 * @content: struct parameter
 *
 * Return: 0 (success), 1 (error)
 */
int c_dir_shell(sh_args *content)
{
	char *wrkin_dir, *dir, buff[1024];
	int cd_success;

	wrkin_dir = getcwd(buff, 1024);
	if (!wrkin_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!content->argv[1])
	{
		dir = getduplicate_surr(content, "HOME=");
		if (!dir)
			cd_success = chdir((dir = getduplicate_surr(content, "PWD=")) ? dir : "/");
		else
			cd_success = chdir(dir);
	}
	else if (strings_weigh(content->argv[1], "-") == 0)
	{
		if (!getduplicate_surr(content, "OLDPWD="))
		{
			_puts(wrkin_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getduplicate_surr(content, "OLDPWD=")), _putchar('\n');
		cd_success = chdir((dir = getduplicate_surr(content, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_success = chdir(content->argv[1]);
	if (cd_success == -1)
	{
		error_msg_print(content, "can't cd to ");
		using_buffer_to_write_str(content->argv[1]), using_buffer_to_write('\n');
	}
	else
	{
		surr_set(content, "OLDPWD", getduplicate_surr(content, "PWD="));
		surr_set(content, "PWD", getcwd(buff, 1024));
	}
	return (0);
}


/**
 * assist_cmd -  to provide a placeholder
 * for the "help" command in a shell program
 * @content: struct parameter
 *
 * Return: 0
 */
int assist_cmd(sh_args *content)
{
	char **arg_v;

	arg_v = content->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_v); /* temp att_unused workaround */
	return (0);
}


/**
 * close_sh - terminates the shell's working process
 * @content: struct parameter
 *
 * Return: 0
 */
int close_sh(sh_args *content)
{
	int exitcheck;

	if (content->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = close_str_intt(content->argv[1]);
		if (exitcheck == -1)
		{
			content->status = 2;
			error_msg_print(content, "Illegal number: ");
			using_buffer_to_write_str(content->argv[1]);
			using_buffer_to_write('\n');
			return (1);
		}
		content->err_num = close_str_intt(content->argv[1]);
		return (-2);
	}
	content->err_num = -1;
	return (-2);
}


/**
 * close_str_intt - converts string inputs to integer
 * @str: string being converted
 * Desc: It then checks whether the first character
 * of the input string is a + sign. If it is, it increments
 * the pointer (str++) to move past the + sign. whether each
 * character is a digit between 0 and 9. If it is, it
 * multiplies the converted_output by 10 and adds the
 * value of the current digit to it. If the converted_output
 * exceeds the maximum value of an integer (INT_MAX),
 * the function returns -1 indicating an error
 *
 * Return: 0 , -1 (error, if the input string contains non-numeric characters)
 */
int close_str_intt(char *str)
{
	int count = 0;
	unsigned long int converted_output = 0;

	if (*str == '+')
		str++;

	for (count = 0;  str[count] != '\0'; count++)
	{
		if (str[count] >= '0' && str[count] <= '9')
		{
			converted_output *= 10;
			converted_output += (str[count] - '0');
			if (converted_output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (converted_output);
}
