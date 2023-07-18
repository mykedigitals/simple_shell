#include "shell.h"


/**
 * analyse_cmd_chain - evaluates if a given command is a link in a
 * command chain (either a "AND" or "OR" chain), then modifies
 * a buffer in accordance with the results.
 * @content: struct parameter
 * @cmd_buffer: buf's  character
 * @buffer_pos: cmand buffer's address of present position
 * @cmd_index:  cmand buffer's starting position
 * @buffer_len: cmd buffer's length
 *
 * Return: nil
 */
void analyse_cmd_chain(sh_args *content, char *cmd_buffer,
		size_t *buffer_pos, size_t cmd_index, size_t buffer_len)
{
	size_t current_pos = *buffer_pos;

	if (content->cmd_buf_type == CMD_AND)
	{
		if (content->status)
		{
			cmd_buffer[cmd_index] = 0;
			current_pos = buffer_len;
		}
	}
	if (content->cmd_buf_type == CMD_OR)
	{
		if (!content->status)
		{
			cmd_buffer[cmd_index] = 0;
			current_pos = buffer_len;
		}
	}

	*buffer_pos = current_pos;
}


/**
 * observe_cmd_chain - determines whether the
 * command chaining is a chain delimeter.
 * @content: the value struct
 * @cmd_buffer: the character buf
 * @buffer_pos: location of present position in commd_buf
 *
 * Return: 1 (chain delimeter), else 0
 */
int observe_cmd_chain(sh_args *content, char *cmd_buffer,
		size_t *buffer_pos)
{
	size_t current_pos = *buffer_pos;

	if (cmd_buffer[current_pos] == '|' && cmd_buffer[current_pos + 1] == '|')
	{
		cmd_buffer[current_pos] = 0;
		current_pos++;
		content->cmd_buf_type = CMD_OR;
	}
	else if (cmd_buffer[current_pos] == '&' && cmd_buffer[current_pos + 1] == '&')
	{
		cmd_buffer[current_pos] = 0;
		current_pos++;
		content->cmd_buf_type = CMD_AND;
	}
	else if (cmd_buffer[current_pos] == ';') /* found end of this command */
	{
		cmd_buffer[current_pos] = 0; /* replace semicolon with null */
		content->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*buffer_pos = current_pos;
	return (1);
}


/**
 * rm_content - puts a new string in place
 * of the content of a string.
 * @oldStrPtr: the address to the former string
 * @newStr: the current string
 *
 * Return: 1 if string is replaced
 */
int rm_content(char **oldStrPtr, char *newStr)
{
	free(*oldStrPtr);
	*oldStrPtr = newStr;
	return (1);
}


/**
 * rp_refer_val - substitutes any shell-defined aliases
 * with their corresponding values.
 * @content: struct parameter
 * Desc: This is accomplished by looking for an alias in
 * the content struct that has a prefix matching the first
 * parameter, and if one is found, replacing it with the
 * alias value.
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int rp_refer_val(sh_args *content)
{
	int count;
	l_list *alias_node;
	char *alias_value;

	for (count = 0; count < 10; count++)
	{
		alias_node = prefix_of_firstNode(content->alias,
				content->argv[0], '=');
		if (!alias_node)
			return (0);
		free(content->argv[0]);
		alias_value = to_find_char(alias_node->str, '=');
		if (!alias_value)
			return (0);
		alias_value = clone_string(alias_value + 1);
		if (!alias_value)
			return (0);
		content->argv[0] = alias_value;
	}
	return (1);
}

/**
 * rp_val - replaces certain factors within the contentions
 * passed to it with their comparing values
 * @content: struct parameter
 * Desc: it replaces the taking after factors:
 * "$?" with the exit status of the foremost as of late
 * executed command
 * "$$" with the process ID of the current shell process.
 * "${VAR}" with the val of the env variable named VAR.
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int rp_val(sh_args *content)
{
	int arg_index = 0;
	l_list *env_var_node;

	for (arg_index = 0; content->argv[arg_index]; arg_index++)
	{
		if (content->argv[arg_index][0] != '$' || !content->argv[arg_index][1])
			continue;

		if (!strings_weigh(content->argv[arg_index], "$?"))
		{
			rm_content(&(content->argv[arg_index]),
				clone_string(selfCreated_get(content->status, 10, 0)));
			continue;
		}
		if (!strings_weigh(content->argv[arg_index], "$$"))
		{
			rm_content(&(content->argv[arg_index]),
				clone_string(selfCreated_get(getpid(), 10, 0)));
			continue;
		}
		env_var_node = prefix_of_firstNode(content->env,
				&content->argv[arg_index][1], '=');
		if (env_var_node)
		{
			rm_content(&(content->argv[arg_index]),
				clone_string(to_find_char(env_var_node->str, '=') + 1));
			continue;
		}
		rm_content(&content->argv[arg_index], clone_string(""));

	}
	return (0);
}
