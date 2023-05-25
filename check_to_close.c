#include "shell.h"


/**
 * ch_directory - changes the current
 * working directory of the shell
 * @element: struct parameter
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
int ch_directory(shell_args *element)
{
	int ch_win;
	char buff[1024], *current_dir, *dir;

	current_dir = getcwd(buff, 1024);
	if (current_dir == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!element->argv[1])
	{
		dir = getenv_clone(element, "HOME=");
		if (dir == NULL)
			ch_win = chdir((dir = getenv_clone(element, "PWD=")) ? dir : "/");
		else
			ch_win = chdir(dir);
	}
	else if (cmpare_strs(element->argv[1], "-") == 0)
	{
		if (!getenv_clone(element, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_clone(element, "OLDPWD=")), _putchar('\n');
		ch_win = chdir((dir = getenv_clone(element, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_win = chdir(element->argv[1]);
	if (ch_win == -1)
	{
		print_err_mesg(element, "can't cd to ");
		write_string_with_buffer(element->argv[1]), write_with_buffer('\n');
	}
	else
	{
		env_setter(element, "OLDPWD", getenv_clone(element, "PWD="));
		env_setter(element, "PWD", getcwd(buff, 1024));
	}
	return (0);
}




/**
 * shell_exit - terminates the shell's working process
 * @element: struct parameter
 *
 * Return: 0
 */
int shell_exit(shell_args *element)
{
	int exitcheck;

	if (element->argv[1])
	{
		/* converts exit argument to an integer */
		exitcheck = exit_str_to_int(element->argv[1]);

		/* If the exit arg is not a valid integer, print an err mesg */
		if (exitcheck == -1)
		{
			element->status = 2;
			print_err_mesg(element, "Error number: ");
			write_string_with_buffer(element->argv[1]);
			write_with_buffer('\n');
			return (1);
		}
		element->err_num = exit_str_to_int(element->argv[1]);
		return (-2);
	}
	element->err_num = -1;
	return (-2);
}
