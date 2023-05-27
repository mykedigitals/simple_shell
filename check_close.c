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
		dir = getenv_clone(content, "HOME=");
		if (!dir)
			cd_success = chdir((dir = getenv_clone(content, "PWD=")) ? dir : "/");
		else
			cd_success = chdir(dir);
	}
	else if (cmpare_strs(content->argv[1], "-") == 0)
	{
		if (!getenv_clone(content, "OLDPWD="))
		{
			_puts(wrkin_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_clone(content, "OLDPWD=")), _putchar('\n');
		cd_success = chdir((dir = getenv_clone(content, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_success = chdir(content->argv[1]);
	if (cd_success == -1)
	{
		print_err_mesg(content, "can't cd to ");
		write_string_with_buffer(content->argv[1]), write_with_buffer('\n');
	}
	else
	{
		env_setter(content, "OLDPWD", getenv_clone(content, "PWD="));
		env_setter(content, "PWD", getcwd(buff, 1024));
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
			print_err_mesg(content, "Illegal number: ");
			write_string_with_buffer(content->argv[1]);
			write_with_buffer('\n');
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
