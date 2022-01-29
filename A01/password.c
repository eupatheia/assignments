/* password.c
 * Jasmine Lei
 * 27 January 2022
 * Creates a bad password from a given user-defined string,
 * presumed to be less than 50 characters long,
 * by replacing e with 3, l with 1, and a with @
 */

#include <stdio.h>
#include <string.h>

int main() {
	char password[75];
	int size;

	printf("Enter a word: ");
	scanf("%s", password);
	size = strlen(password);
	for (int i = 0; i < size; i++) {
		if (password[i] == 'e') {
			password[i] = '3';
		} else if (password[i] == 'l') {
			password[i] = '1';
		} else if (password[i] == 'a') {
			password[i] = '@';
		}
	}
	printf("Your bad password is %s\n", password);
	return 0;
}
