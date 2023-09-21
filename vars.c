#include "main..h"

/**
 * is_chain - confirms if buffer current char is a chain delimeter
 * @info: it is the struct parameter
 * @buf: it is the buffer char
 * @p: it is the current position in buf address
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /*finds this command end*/
	{
		buf[j] = 0; /* null should be replaced with semicolon*/
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - confirms whether we should chain continuous based on last status
 * @info: it is the struct parameter
 * @buf: it is buffer char
 * @p: current address position in buf
 * @i: begining point in buf
 * @len: indicate buf lenght
 *
 * Return: gives  Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - responsible for replacing  aliases in the tokenized string
 * @info: it is the struct parameter
 *
 * Return: give 0 otherwise, 1 if replaced
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - resposible for replacing vars in the tokenized string
 * @info: it is the struct paramete
 *
 * Return: gives ,0 otherwise, 1 incase replaced
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - take place ofa a string
 * @old: it is the old string address
 * @new: it is new string
 *
 * Return: gives , 0 otherwise, 1 if replaced
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
