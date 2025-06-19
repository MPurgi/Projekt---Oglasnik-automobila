#pragma once

#include <stdio.h>
#include <string.h>
#include <time.h>

static inline void clearInputBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static inline int safeInputInt(const char* prompt) {
	int value;
	char end;
	while (1) {
		printf("%s", prompt);

		if (scanf("%d%c", &value, &end) == 2 && end == '\n' && value >= 0) {
			return value;
		}
		else {
			printf("Neispravan unos! Po potrebni pritisnite bilo koju tipku za nastavak!\n");
			clearInputBuffer();

		}
	}
}

static inline float safeInputFloat(const char* prompt) {
	float value;
	char end;
	while (1) {
		printf("%s", prompt);
		if (scanf("%f%c", &value, &end) == 2 && end == '\n' && value >= 0) {
			return value;
		}
		else {
			printf("Neispravan unos! Po potrebi pritisnite bilo koju tipku za nastavak!\n");
			clearInputBuffer();
		}
	}
}

static inline void safeInputString(const char* prompt, char* buffer, int size) {
	printf("%s", prompt);
	if (fgets(buffer, size, stdin) != NULL) {
		if (strchr(buffer, '\n') == NULL) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Upozorenje: Unos je bio predug te je automatski skracen na %d znakova.\n", size - 1);
		}
		buffer[strcspn(buffer, "\n")] = 0;
	}
}

static inline int safeInputYear(const char* prompt) {
	int value;
	char end;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int currentYear = tm.tm_year + 1900;
	while (1) {
		printf("%s", prompt);
		if (scanf("%d%c", &value, &end) == 2 && end == '\n' && value >= 1884 && value <= currentYear) {
			return value;
		}
		else {
			printf("Neispravan unos! Unesite ispravnu godinu!\n");
			clearInputBuffer();
		}
	}
}