#include "shell.h"

/**
 * get_first_node_with_prefix -  searches a linked list of strings for
 *      the first node whose string starts with a given prefix
 * @node: pointer to list head
 * @search_str: string to match
 * @search_char: the next character after search_str to match
 *
 * Return: matching node, null
 */
l_list *get_first_node_with_prefix(l_list *node, char *search_str,
                char search_char)
{
        char *match_ptr = NULL;

        while (node)
        {
                match_ptr = find_substr_at_start(node->str, search_str);
                if (match_ptr && ((search_char == -1) || (*match_ptr == search_char)))
                        return (node);
                node = node->link;
        }
        return (NULL);
}

/**
 * prnt_l_list_str - print all the strings stored in a singly
 *      linked list of strings, with each string followed by a
 *      newline character
 * @head: first node pointer
 *
 * Return: number of nodes traversed in the linked list
 */
size_t prnt_l_list_str(const l_list *head)
{
        size_t index = 0;

        while (head)
        {
                _puts(head->str ? head->str : "(nil)");
                _puts("\n");
                head = head->link;
                index++;
        }
        return (index);
}

