#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

void find_comments(int*, int*);
int find_idents(void);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

void find_comments(int *line_comment_counter, int *block_comment_counter)
{
	char c;
	*line_comment_counter = *block_comment_counter = 0;
    while ((c = getchar()) != EOF) 
	{
		if (c == '/') 
		{
		    c=getchar(); // get the next char
			if (c == '*')
			{
				*block_comment_counter += 1;
			}
			else if (c == '/')
			{
				*line_comment_counter += 1; 
			}
		}
	}

}

int is_keyword(const char *word) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int find_idents(void) {
    int c;
    int idents_count = 0;
    int in_block_comment = 0;
    int in_line_comment = 0;
    int in_string = 0;
    int in_char = 0;
    char buffer[MAX_ID_LEN];
    int buf_idx = 0;

    while ((c = getchar()) != EOF) {
        if (in_block_comment) {
            if (c == '*' && (c = getchar()) == '/') {
                in_block_comment = 0;
            }
            continue;
        }
        if (in_line_comment) {
            if (c == '\n') {
                in_line_comment = 0;
            }
            continue;
        }
        if (in_string) {
            if (c == '\\') { // pomijamy sekwencje jak \" 
                getchar();
            } else if (c == '"') {
                in_string = 0;
            }
            continue;
        }
        if (in_char) {
            if (c == '\\') { // pomijamy sekwencje jak \'
                getchar();
            } else if (c == '\'') {
                in_char = 0;
            }
            continue;
        }

        // początek komentarza lub stringa
        if (c == '/') {
            int next = getchar();
            if (next == '*') {
                in_block_comment = 1;
                continue;
            } else if (next == '/') {
                in_line_comment = 1;
                continue;
            } else if (next != EOF) {
                ungetc(next, stdin);
            }
        } else if (c == '"') {
            in_string = 1;
            continue;
        } else if (c == '\'') {
            in_char = 1;
            continue;
        }

        // identyfikatory
        if (isalpha(c) || c == '_') {
            buf_idx = 0;
            buffer[buf_idx++] = c;
            while (buf_idx < MAX_ID_LEN - 1 && (isalnum(c = getchar()) || c == '_')) {
                buffer[buf_idx++] = c;
            }
            buffer[buf_idx] = '\0';

            if (c != EOF) {
                ungetc(c, stdin);
            }

            if (!is_keyword(buffer)) {
                // sprawdzanie unikalności
                int found = 0;
                for (int i = 0; i < idents_count; i++) {
                    if (strcmp(identifiers[i], buffer) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found && idents_count < MAX_IDS) {
                    strcpy(identifiers[idents_count++], buffer);
                }
            }
        }
    }

    return idents_count;
}


int read_int() {
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin); // to get the whole line
	return (int)strtol(line, NULL, 10);
}

int main(void) {
	int line_comment_counter, block_comment_counter;
	const int to_do = read_int();
	switch (to_do) {
		case 1:
			find_comments(&line_comment_counter, &block_comment_counter);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		case 2:
			printf("%d\n", find_idents());
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

