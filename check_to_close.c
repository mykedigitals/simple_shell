#include "shell.h"


/**
 * change_directory - changes the current
 * working directory of the shell
 * @content: struct parameter
 * Desc: getcwd gets the current working directory and
 * stores it in the buffer. If it is empty, it sets
 * the dir variable to the value of the HOME environment
 * variable, and if that fails, it sets dir to the
 * value of the PWD environment variable. It then calls
 * the chdir function to change the current working
 * directory to the value of dir. If the first argument
 * is not empty, the function checks if it is equal to "-".
 * If it is, it prints the current working directory
 * to standard output and sets the dir variable to the value
 * of the OLDPWD. If the first argument is not empty
 * and not equal to "-", the function simply calls chdir to
 * change the current working directory to the value of
 * the first argument. Then it sets OLDPWD and PWD to the
 * shell's environment variable table
 *
 * Return: 0 (success), 1 (error)
 */
int change_directory(sh_args *content)
{
	int cd_success;
	char buff[1024], *wrkin_dir, *dir;

	wrkin_dir = getcwd(buff, 1024);
	if (wrkin_dir == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!content->argv[1])
	{
		dir = getenv_clone(content, "HOME=");
		if (dir == NULL)
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
 * shell_exit - terminates the shell's working process
 * @content: struct parameter
 *
 * Return: 0
 */
int shell_exit(sh_args *content)
{
	int exitcheck;

	if (content->argv[1])
	{
		/* converts exit argument to an integer */
		exitcheck = exit_str_to_int(content->argv[1]);

		/* If the exit arg is not a valid integer, print an err mesg */
		if (exitcheck == -1)
		{
			content->status = 2;
			print_err_mesg(content, "Error number: ");
			write_string_with_buffer(content->argv[1]);
			write_with_buffer('\n');
			return (1);
		}
		content->err_num = exit_str_to_int(content->argv[1]);
		return (-2);
	}
	content->err_num = -1;
	return (-2);
}
