#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define TOKEN_CONJUCTION "and"
#define TOKEN_DISJUNCTION "or"
#define TOKEN_NEGATION "not"
#define TOKEN_EXCLUSIVE_DISJUNCTION "xor"
#define TOKEN_IMPLICATION "implies"
#define TOKEN_DOUBLE_IMPLICATION "iff"

enum logical_operator {
	CONJUCTION,
	DISJUNCTION,
	NEGATION,
	EXCLUSIVE_DISJUNCTION,
	IMPLICATION,
	DOUBLE_IMPLICATION
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
		if (strcmp(tk, TOKEN_CONJUCTION) == 0) {
			op = CONJUCTION;
			oa[0] = tk;
		} else if (strcmp(tk, TOKEN_DISJUNCTION) == 0) {
			op = DISJUNCTION;
			oa[0] = tk;
		} else if (strcmp(tk, TOKEN_EXCLUSIVE_DISJUNCTION) == 0) {
			op = EXCLUSIVE_DISJUNCTION;
			oa[0] = tk;
		} else if (strcmp(tk, TOKEN_IMPLICATION) == 0) {
			op = IMPLICATION;
			oa[0] = tk;
		} else if (strcmp(tk, TOKEN_DOUBLE_IMPLICATION) == 0) {
			op = DOUBLE_IMPLICATION;
			oa[0] = tk;
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
			case CONJUCTION:
				tv[i] = sv[0][i] & sv[1][i];
				break;
			case DISJUNCTION:
				tv[i] = sv[0][i] | sv[1][i];
				break;
			case NEGATION:
				// TODO
				break;
			case EXCLUSIVE_DISJUNCTION:
				tv[i] = sv[0][i] ^ sv[1][i];
				break;
			case IMPLICATION:
				tv[i] = (sv[0][i] ^ 0x1) | sv[1][i];
				break;
			case DOUBLE_IMPLICATION:
				tv[i] = (sv[0][i] & sv[1][i]) | ((sv[0][i] | sv[1][i]) ^ 0x1);
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
