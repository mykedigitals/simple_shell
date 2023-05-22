#include "shell.h"
/**
 * new_end_node - adds a new node to the end of a linked list
 * @list_head: head node
 * @str: strings
 * @num: index
 *
 * Return: list size
 */
l_list *new_end_node(l_list **list_head, const char *str, int num)
{
        l_list *new_node, *current_node;

        if (!list_head)
                return (NULL);

        current_node = *list_head;
        new_node = malloc(sizeof(l_list));
        if (!new_node)
                return (NULL);
        memset_clone((void *)new_node, 0, sizeof(l_list));
        new_node->num = num;
        if (str)
        {
                new_node->str = str_dup(str);
                if (!new_node->str)
                {
                        free(new_node);
                        return (NULL);
                }
        }
        if (current_node)
        {
                while (current_node->link)
                        current_node = current_node->link;
                current_node->link = new_node;
        }
        else
                *list_head = new_node;
        return (new_node);
}

/**
 * find_node_index - finds the index of a given node in a linked list
 * @head: head node
 * @target_node: target_node
 *
 * Return: node index starting from 0, -1 (otherwise)
 */
ssize_t find_node_index(l_list *head, l_list *target_node)
{
        size_t index = 0;

        while (head)
        {
                if (head == target_node)
                        return (index);
                head = head->link;
                index++;
        }
        return (-1);
}

