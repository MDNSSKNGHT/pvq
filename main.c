#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum logical_operator {
	AND,
	OR,
	XOR
};

int main(int argc, char const *argv[])
{
	char *tk;
	char *d;
	char **sa;
	char **oa;

	int sc = 0;
	int vc = 0;

	enum logical_operator op;

	// TODO: free
	sa = malloc(2 * sizeof(char*));
	oa = malloc(1 * sizeof(char*));

	d = strdup(argv[1]);
	tk = strtok(d, " ");

	while (tk != NULL) {
		if (strcmp(tk, "and") == 0) {
			op = AND;
			oa[0] = "and";
		}
		else if (strcmp(tk, "or") == 0) {
			op = OR;
			oa[0] = "or";
		} else if (strcmp(tk, "xor") == 0) {
			op = XOR;
			oa[0] = "xor";
		} else {
			sa[sc] = strdup(tk);
			sc++;
		}

		tk = strtok(NULL, " ");
	}

	vc = pow(2, sc);
	bool sv[sc][vc];
	bool tv[vc];

	for (int i = sc - 1; i >= 0; --i)
		for (int j = 0; j < vc; j++)
			sv[i][j] = ~j >> (sc - i - 1) & 0x1;

	for (int i = 0; i < vc; ++i) {
		switch (op) {
			case AND:
				tv[i] = sv[0][i] & sv[1][i];
				break;
			case OR:
				tv[i] = sv[0][i] | sv[1][i];
				break;
			case XOR:
				tv[i] = sv[0][i] ^ sv[1][i];
				break;
		}
	}

	printf("%s\t%s\t%s %s %s\n", sa[0], sa[1], sa[0], oa[0], sa[1]);
	for (int i = 0; i < sc - 1; ++i)
		for (int j = 0; j < vc; ++j)
			printf("%s\t%s\t%s\n",
				sv[i][j] ? "V" : "F",
				sv[i + 1][j] ? "V" : "F",
				tv[j] ? "V" : "F");


	return 0;
}
