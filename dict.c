#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct trie {
struct trie *children[100];
int isEnd;
} trie;

void insert(trie *ele, char *word) {

trie *root = ele;

int len = strlen(word);

for (int i = 0; i < len; i++) {

trie *curr = ele->children[word[i] % 97];

if (curr == NULL) {
curr = malloc (sizeof (trie));
curr->isEnd = 0;
for(int i = 0; i < 100; i++) curr->children[i] = NULL;
}

if(i + 1 == len) curr->isEnd = 1;

ele->children[word[i] % 97] = curr;
ele = ele->children[word[i] % 97];
}

ele = root;
}

int islast(trie *ele)
{
int count=0;
for(int i=0;i<100;i++)
{
if(ele->children[i]==NULL)
count=count;
else
count++;
}
return (count==0?0:1);
}

char *push (char *slice, char part) {

char *str = malloc (sizeof (char) * (strlen (slice) + 2));

int i = 0;
while (slice[i] != '\0') str[i] = slice[i++];

str[i++] = part;
str[i] = '\0';

return str;
}


void autocomplete(trie *ele, char *slice) {



if (ele == NULL) return;

if (ele->isEnd) printf("%s\n", slice);

for (int i = 0; i < 100; i++)
{

if(ele->children[i] != NULL)

autocomplete(ele->children[i], push (slice, i + 97));
}
}

void print(trie *root, char *prefix) {

int len = strlen (prefix);
int ch;
trie *ele=root;
for (int i = 0; i < len; i++)
{
if(ele->children[prefix[i] % 97]!=NULL)
ele=ele->children[prefix[i] % 97];
else
{

printf("\nword does not exist\n");
printf("would you like to add the word to the dictionary?");
scanf("%d",&ch);
if(ch==1)
insert(root,prefix);
return;
}

}
autocomplete (ele, prefix);
}

int main() {

trie root;
root.isEnd = 0;
for (int i = 0; i < 100; i++) root.children[i] = NULL;

FILE *fp = fopen ("dict.txt", "r");

char str[25];

while (!feof (fp)) {
fscanf (fp, "%s", str);
insert (&root, str);
}

fclose (fp);

char input[100];
char ch=1;
while(1)
{

printf ("\n>> ");
scanf ("%s", input);
print(&root, input);
}


return 0;
}


