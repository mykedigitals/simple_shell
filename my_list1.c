#include "shell.h"
/**
 * updated_tail_node - adds a new node to the end of a linked list
 * @list_top: top node
 * @str: strings
 * @num: index
 *
 * Return: list size
 */
l_list *updated_tail_node(l_list **list_top, const char *str, int num)
{
        l_list *updated_node, *present_node;

        if (!list_top)
                return (NULL);

        present_node = *list_top;
        updated_node = malloc(sizeof(l_list));
        if (!updated_node)
                return (NULL);
        memset_clone((void *)updated_node, 0, sizeof(l_list));
        updated_node->num = num;
        if (str)
        {
                updated_node->str = double_str(str);
                if (!updated_node->str)
                {
                        free(updated_node);
                        return (NULL);
                }
        }
        if (present_node)
        {
                while (present_node->link)
                        present_node = present_node->link;
                present_node->link = updated_node;
        }
        else
                *list_top = updated_node;
        return (updated_node);
}

/**
 * search_node_sort - finds the index of a given node in a linked list
 * @top: top node
 * @point_node: point_node
 *
 * Return: node index starting from 0, -1 (otherwise)
 */
ssize_t search_node_sort(l_list *top, l_list *point_node)
{
        size_t index = 0;

        while (top)
        {
                if (top == point_node)
                        return (index);
                top = top->link;
                index++;
        }
        return (-1);
}

