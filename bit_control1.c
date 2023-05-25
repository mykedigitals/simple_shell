#include "shell.h"

/**
 * change_alias_to_val - replaces any aliases defined in the
 *      shell with their respective values
 * @element: struct parameter
 * rFw: It does this by searching for an alias with a prefix matching
 *      the first argument in the element struct, and if found,
 *      replacing it with the alias value
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int change_alias_to_val(shell_args *element)
{
        int count;
        l_list *alias_node;
        char *alias_value;

        for (count = 0; count < 10; count++)
        {
                alias_node = obtain_beginingnode(element->alias,
                                element->argv[0], '=');
                if (!alias_node)
                        return (0);
                free(element->argv[0]);
                alias_value = locate_char(alias_node->str, '=');
                if (!alias_value)
                        return (0);
                alias_value = double_str(alias_value + 1);
                if (!alias_value)
                        return (0);
                element->argv[0] = alias_value;
        }
        return (1);
}

/**
 * access_cmd_order - This will check if the command is part of
 *	command order could be "WITH" or "EITHER" order, and modify a
 *	buffer based on result of the access
 * @element: struct parameter
 * @cd_buff: buffer's command
 * @buffpost: buffer's address of current position
 * @cd_sort: buffer's starting position
 * @lenght_buff: command buffer's length
 *
 * Return: nil
 */
void access_cmd_order(shell_args *element, char *cd_buff,
		size_t *buffpost, size_t cd_sort, size_t lenght_buff)
{
	size_t present_post = *buffpost;

	if (element->cd_buff_category == CMD_WIT)
	{
		if (element->status)
		{
			cd_buff[cd_sort] = 0;
			present_post = lenght_buff;
		}
	}
	if (element->cd_buff_category == CMD_EI)
	{
		if (!element->status)
		{
			cd_buff[cd_sort] = 0;
			present_post = lenght_buff;
		}
	}

	*buffpost = present_post;
}


/**
 * order_cmd_discover - determines the type of command chaining
 *	as being a chain delimeter
 * @element: the parameter struct
 * @cd_buff: the char buffer
 * @buffpost: address of current position in cd_buff
 *
 * Return: 1 (order separator), or else 0
 */
int order_cmd_discover(shell_args *element, char *cd_buff,
		size_t *buffpost)
{
	size_t present_post = *buffpost;

	if (cd_buff[present_post] == '|' && cd_buff[present_post + 1] == '|')
	{
		cd_buff[present_post] = 0;
		present_post++;
		element->cd_buff_category = CMD_EI;
	}
	else if (cd_buff[present_post] == '&' && cd_buff[present_post + 1] == '&')
	{
		cd_buff[present_post] = 0;
		present_post++;
		element->cd_buff_category = CMD_WIT;
	}
	else if (cd_buff[present_post] == ';') /* found end of this command */
	{
		cd_buff[present_post] = 0; /* replace semicolon with null */
		element->cd_buff_category = CMD_ORDER;
	}
	else
		return (0);
	*buffpost = present_post;
	return (1);
}

