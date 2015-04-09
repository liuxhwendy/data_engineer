#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLANK ('\0')

typedef struct trie_node_t {
	char key;
	unsigned int number;
	struct trie_node_t *children,
					   *next;
} trie_node;

static trie_node *trie_create(void)
{
	trie_node *p = (trie_node *)malloc(sizeof(trie_node));
	if (NULL == p) {
		printf("memory malloc fail when creating a sub-trie!\n");
	} else {
		p->key = BLANK;
		p->number = 0;
		p->children = NULL;
		p->next = NULL;
	}
	return p;
}

static int trie_destroy(trie_node *p)
{
	if (NULL != p) {
		if (NULL != p->children)
			trie_destroy(p->children);
		if (NULL != p->next)
			trie_destroy(p->next);
		free(p);
	}
	return 0;
}

static int trie_add(trie_node *p, const char keys[])
{
	const char c = keys[0];
	trie_node *curr=NULL, *temp=NULL;

	// Search c in the current level, the first one of each level is BLANK.
	for (curr=p; curr!=NULL; curr=curr->next) {
		if (c == curr->key) {
			if (c == BLANK) {
				curr->value++;
			} else {
				if (curr->children == NULL)
					curr->children = trie_create();
				trie_add(curr->children, &keys[1]);
			}
			break;
		} else if (c > curr->key) {
			if (curr->next == NULL) {
				curr->next = trie_create();
				curr->next->key = c;
				trie_add(curr->next, &keys[1]);
				break;
			} else if (c < curr->next->key) {
				temp = curr->next;
				curr->next = trie_create();
				curr->next->key = c;
				curr->next->next = temp;
				trie_add(curr->next, &keys[1]);
				break;
			} else { // c >= next->key
				// Do nothing.
			}
		} else { // c < curr->key
			printf("Your code has bugs.\n");
		}
	}

	return 0;
}

static char word[100];
static char *p_w = word;
static int trie_print_init(void)
{
	word[0] = BLANK;
	p_w = &word[0];
}
static void push(char c)
{
	*p_w++ = c;
	*p_w = BLANK;
}
static void pop(void)
{
	*p_w--;
    *p_w = BLANK;
}

static void trie_print(trie_node *p)
{
	if (NULL != p) {
		if (p->key == BLANK) {
			if (p->value != 0) {
				printf("%s, %d\n", word, p->value);
			}
		} else {
			push(p->key);
			if (p->value != 0) {
				printf("%s, %d\n", word, p->value);
			}
			if (NULL != p->children) {
				trie_print(p->children);
				pop();
			}
			if (NULL != p->next) {
				trie_print(p->next);
				pop();
			}
		}
	}
}

int main(void)
{
	char so[] = "so";
	char call[] = "call";
	char a[] = "a";
	trie_node *root = trie_create();

	trie_add(root, so);
	trie_add(root, call);
	trie_add(root, a);
	trie_add(root, call);
	trie_add(root, a);

	trie_print_init();
	trie_print(root);
	trie_destroy(root);

	return 0;
}
