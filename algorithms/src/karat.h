#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* stradd(char *x, char *y);
char* combine(char *x, char *y);
char* strdiff(char *x, char *y);
void reverse(char *input);
int digits(int input);

char* karat(char *x, char *y) {
	printf("running, inputs: %s, %s\n", x, y);
	int n, m, len_x, len_y, x_val, y_val;
	char *a, *b, *c, *d, *mid, *product;

	len_x = strlen(x);
	len_y = strlen(y);
	if (len_x > len_y) {
		n = len_x;
	}
	else {
		n = len_y;
	}

	// base case: single digit multiplication
	if (n == 1) {
		x_val = atoi(x);
		y_val = atoi(y);
		int result = x_val * y_val;
		// store result as string
		product = malloc(3);
		itoa(result, product, 10);
		if (digits(result) == 2) {
			product[2] = '\0';
		}
		else {
			product[1] = '\0';
		}
		return product;
	}
	// for more digits: write x = a*10^(n/2) + b, y = c*10^(n/2) + d, n == max(no. digits in x or y)
	// x*y = ac*10^n + (ad + bc)*10^(n/2) + bd
	else {
		m = n/2;
		// a is first len(x) - m chars of x, b is last m chars of x
		if (len_x - m <= 0) {
			a = malloc(2);
			a[0] = '0';
			a[1] = '\0';
			b = x;
		}
		else {
			a = malloc(len_x - m + 1);
			memcpy(a, &x[0], len_x - m);
			a[len_x - m] = '\0';
			b = malloc(m + 1);
			memcpy(b, &x[len_x - m], m);
			b[m] = '\0';
		}
		// c is first len(y) - m chars of y, d is last m chars of y
		if (len_y - m <= 0) {
			c = malloc(2);
			c[0] = '0';
			c[1] = '\0';
			d = y;
		}
		else {
			c = malloc(len_y - m + 1);
			memcpy(c, &y[0], len_y - m);
			c[len_y - m] = '\0';
			d = malloc(m+1);
			memcpy(d, &y[len_y - m], m);
			d[m] = '\0';
		}
	}

	// recursively compute ac, bd, and (ad + bc) = (a+b)(c+d) - ac - bd
	char *f = karat(a, c);
	char *g = karat(b, d);
	// use addition for strings
	char *h = karat(stradd(a, b), stradd(c, d));
	// free allocated memory
	free(a);
	free(b);
	free(c);
	free(d);

	// get result for (ad + bc)
	mid = strdiff(strdiff(h, f), g);
	// pad f and mid with correct numbers of zeros
	f = (char*) realloc(f, strlen(f) + 2 * m);
	mid = (char*) realloc(mid, strlen(mid) + m);
	char fbuff[2 * m + 1];
	char midbuff[m + 1];
	for (int i = 0 ; i < 2 * m ; i++) {
		fbuff[i] = '0';
	}
	fbuff[2 * m] = '\0';
	for (int i = 0 ; i < m ; i++) {
		midbuff[i] = '0';
	}
	midbuff[m] = '\0';
	strcat(f, fbuff);
	strcat(mid, midbuff);
	// combine parts to get result
	product = stradd(f, stradd(mid, g));
	// free allocated memory
	free(f);
	free(g);
	free(h);
	free(mid);
	return product;

}

char* stradd(char *x, char *y) {
    char *result;
    if (strlen(x) > strlen(y)) {
        result = combine(x, y);
    }
    else {
        result = combine(y, x);
    }
    return result;
}

char* combine(char *x, char *y) {
    // assume len(x) >= len(y)
    char *result = malloc(strlen(x) + 2);
    reverse(x);
    reverse(y);
    int buffer = 0;
    int carry = 0;
    char ccarry;
    // add x and y digit by digit
    for (int i = 0 ; i < strlen(y) ; i++) {
        // convert each digit to an int
        int x_val = x[i] - '0';
        int y_val = y[i] - '0';
        buffer = x_val + y_val + carry;
        char temp[3];
        itoa(buffer, temp, 10);
        if (digits(buffer) == 2) {
            result[i] = temp[1];
        }
        else {
            result[i] = temp[0];
        }
        carry = buffer / 10;
    }
    for (int i = strlen(y) ; i < strlen(x) ; i++) {
        int x_val = x[i] - '0';
        buffer = x_val + carry;
        char temp[3];
        itoa(buffer, temp, 10);
        if (digits(buffer) == 2) {
            result[i] = temp[1];
        }
        else {
            result[i] = temp[0];
        }
        carry = buffer / 10;
    }
    // check if there is an extra digit to add and terminate string
    if (carry == 0) {
        result[strlen(x)] = '\0';
    }
    else {
        ccarry = '0' + carry;
        result[strlen(x)] = ccarry;
        result[strlen(x) + 1] = '\0';
    }
    reverse(result);
    return result;
}

char* strdiff(char *x, char *y) {
    // assume x > y
    char *result = malloc(strlen(x) + 1);
    int buffer = 0;
    int n = strlen(x) - strlen(y);
    // subtract y from x digit by digit
    for (int i = strlen(x) - 1 ; i > n - 1 ; i--) {
        // convert each digit to an int
        int x_val = x[i] - '0';
        int y_val = y[i - n] - '0';
        buffer = x_val - y_val;
        char temp[2];
        if (buffer < 0) {
            int count = 1;
            while (x[i - count] == '0') {
                count++;
            }
            x[i - count]--;
            for (int j = 1 ; j < count; j++) {
                x[i - j] = '9';
            }
            buffer += 10;
            itoa(buffer, temp, 10);
            result[i] = temp[0];
        }
        else {
            itoa(buffer, temp, 10);
            result[i] = temp[0];
        }
    }
    for (int i = n - 1 ; i >= 0 ; i--) {
        // convert each digit to an int
        result[i] = x[i];
    }
    // terminate string
    int m = strlen(x+1);
    while (result[m] == 0) {
        m--;
    }
    result[m+1] = '\0';
    return result;
}

int digits(int input) {
	int count = 0;
	while (input != 0) {
		input /= 10;
		++count;
	}
	return count;
}

void reverse(char *input) {
    int n = strlen(input);
    char output[n];
    for (int i = 0 ; i < n ; i++) {
        output[n - i - 1] = input[i];
    }
    output[n] = '\0';
    strcpy(input, output);
}
