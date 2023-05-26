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
	char buff[1024], *current_dir, *folder;

	current_dir = getcwd(buff, 1024);
	if (current_dir == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!element->argv[1])
	{
		folder = getsurr_clone(element, "HOME=");
		if (folder == NULL)
			ch_win = chdir((folder = getsurr_clone(element, "PWD=")) ? folder : "/");
		else
			ch_win = chdir(folder);
	}
	else if (string_sku(element->argv[1], "-") == 0)
	{
		if (!getsurr_clone(element, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getsurr_clone(element, "OLDPWD=")), _putchar('\n');
		ch_win = chdir((folder = getsurr_clone(element, "OLDPWD=")) ? folder : "/");
	}
	else
		ch_win = chdir(element->argv[1]);
	if (ch_win == -1)
	{
		prt_mes_eror(element, "can't cd to ");
		create_thread_in_render(element->argv[1]), create_in_space('\n');
	}
	else
	{
		make_env(element, "OLDPWD", getsurr_clone(element, "PWD="));
		make_env(element, "PWD", getcwd(buff, 1024));

	}
	return (0);
}




/**
 * shell_out - terminates the shell's working process
 * @element: struct parameter
 *
 * Return: 0
 */
int shell_out(shell_args *element)
{
	int test_exit;

	if (element->argv[1])
	{
		/* converts exit argument to an integer */
		test_exit = end_from_str(element->argv[1]);

		/* If the exit arg is not a valid integer, print an err mesg */
		if (test_exit == -1)
		{
			element->status = 2;
			prt_mes_eror(element, "Error number: ");
			create_thread_in_render(element->argv[1]);
			create_in_space('\n');
			return (1);
		}
		element->err_num = end_from_str(element->argv[1]);
		return (-2);
	}
	element->err_num = -1;
	return (-2);
}
