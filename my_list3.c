#include "shell.h"

/**
 * collect_init_node_in_title -  searches a linked list of strings for
 *      the first node whose string starts with a given prefix
 * @node: pointer to list head
 * @discover_str: string to match
 * @discover_char: the next character after discover_str to match
 *
 * Return: matching node, null
 */
l_list *collect_init_node_in_title(l_list *node, char *discover_str,
                char discover_char)
{
        char *match_ptr = NULL;

        while (node)
        {
                match_ptr = find_substr_at_start(node->str, discover_str);
                if (match_ptr && ((discover_char == -1) || (*match_ptr == discover_char)))
                        return (node);
                node = node->link;
        }
        return (NULL);
}

/**
 * screen_l_list_in_str - print all the strings stored in a singly
 *      linked list of strings, with each string followed by a
 *      newline character
 * @head: first node pointer
 *
 * Return: number of nodes traversed in the linked list
 */
size_t screen_l_list_in_str(const l_list *head)
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

