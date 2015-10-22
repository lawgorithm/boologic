#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

void print_options(void);
void print_results(int, int, int);
static int getLine();

int main(int argc, char* argv[])
{

	int a, b, option;
	size_t sz = sizeof(char) * 3;
	char* prompt;
	char* hold;

	if (argc < 4) {
		if (argc != 3) {

			printf("\nWelcome to Evaluator 0.1!\n");

			printf("\nEnter a value for a: ");
			scanf("%d", &a);
			getchar();

			printf("\nEnter a value for b: ");
			scanf("%d", &b);
			getchar();
		}
		else {
			a = atoi(argv[1]);
			b = atoi(argv[2]);
		}

		prompt = "\n\nSelect Option: \0";
		print_options();

		sz = sizeof(char) * 3;
		hold = malloc(sz);

		getLine(prompt, hold, sz);
		option = atoi(hold);
		free(hold);
	}
	else option = atoi(argv[3]);

	print_results(a, b, option);

	printf("\n");

	return 0;
}

void print_options()
{
	printf("\n(1) < ");
	printf("\n(2) > ");
	printf("\n(3) == ");
	printf("\n(4) != ");
	printf("\n(5) && ");
	printf("\n(6) || ");
	printf("\n");
}

void print_results(int a, int b, int option)
{
	char *op;
	int result;
	char* truthValue;

	switch (option) {

		case 1:
			op = "<";
			result = a < b;
			break;
		case 11:
			op = "<=";
			result = a <= b;
			break;
		case 2:
			op = ">";
			result = a > b;
			break;
		case 22:
			op = ">=";
			result = a >= b;
			break;
		case 3:
			op = "==";
			result = a == b;
			break;
		case 4:
			op = "!=";
			result = a != b;
			break;
		case 5:
			op = "&&";
			result = a && b;
			break;
		case 55:
			op = "&";
			result = a & b;
			break;
		case 6:
			op = "||";
			result = a || b;
			break;
		case 66:
			op = "|";
			result = a | b;
			break;
	}

	if (op != NULL) {
		truthValue = result != 0 ? "TRUE" : "FALSE";
		printf("\n%d %s %d evaluates to %d (%s)\n", a, op, b, result, truthValue);
	}
}


/*
 *
 * Acquired by paxdiablo on StackOverflow
 * http://stackoverflow.com/questions/1694036/why-is-the-gets-function-dangerous-why-should-it-not-be-used
 */
static int getLine(char *prmpt, char *buff, size_t sz)
{
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff)-1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff)-1] = '\0';
	return OK;
}
