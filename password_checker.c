/*
 * Password Strength Checker
 * -------------------------
 * My first ever programming project, written in C.
 * Checks how strong a password is and gives tips to improve it.
 *
 * Build:  gcc password_checker.c -o password_checker
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 128

/* a struct to hold everything we learn about the password */
typedef struct {
    int length;
    int has_lower;
    int has_upper;
    int has_digit;
    int has_symbol;
    int is_common;
    int score;          /* 0 - 6 */
} PasswordReport;

/* passwords that show up in every leaked-password list */
const char *COMMON_PASSWORDS[] = {
    "password", "123456", "12345678", "qwerty", "abc123",
    "letmein", "iloveyou", "admin", "welcome", "monkey"
};
const int COMMON_COUNT = 10;

int is_common_password(const char *password)
{
    int i;
    for (i = 0; i < COMMON_COUNT; i++) {
        if (strcmp(password, COMMON_PASSWORDS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

PasswordReport analyse_password(const char *password)
{
    PasswordReport report = {0, 0, 0, 0, 0, 0, 0};
    int i;

    report.length = (int)strlen(password);

    /* loop over every character and note what kinds we find */
    for (i = 0; i < report.length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (islower(c)) {
            report.has_lower = 1;
        } else if (isupper(c)) {
            report.has_upper = 1;
        } else if (isdigit(c)) {
            report.has_digit = 1;
        } else {
            report.has_symbol = 1;
        }
    }

    report.is_common = is_common_password(password);

    /* simple scoring: one point per good thing */
    if (report.length >= 8)  report.score++;
    if (report.length >= 12) report.score++;
    if (report.has_lower)    report.score++;
    if (report.has_upper)    report.score++;
    if (report.has_digit)    report.score++;
    if (report.has_symbol)   report.score++;

    /* a common password is weak no matter what */
    if (report.is_common) {
        report.score = 0;
    }

    return report;
}

const char *strength_label(int score)
{
    if (score <= 1) return "VERY WEAK";
    if (score <= 3) return "WEAK";
    if (score <= 4) return "OKAY";
    if (score <= 5) return "STRONG";
    return "VERY STRONG";
}

void print_report(const PasswordReport *report)
{
    printf("\n--- Password Report ---\n");
    printf("Length        : %d\n", report->length);
    printf("Lowercase     : %s\n", report->has_lower ? "yes" : "no");
    printf("Uppercase     : %s\n", report->has_upper ? "yes" : "no");
    printf("Numbers       : %s\n", report->has_digit ? "yes" : "no");
    printf("Symbols       : %s\n", report->has_symbol ? "yes" : "no");
    printf("Strength      : %s (%d/6)\n", strength_label(report->score), report->score);

    if (report->is_common) {
        printf("\n!! This is one of the most common passwords in the world.\n");
        printf("!! Anyone trying to break in would guess it in seconds.\n");
    }

    /* tips to make it better */
    if (report->score < 6) {
        printf("\nTips:\n");
        if (report->length < 12) printf("  - make it longer (12+ characters)\n");
        if (!report->has_lower)  printf("  - add lowercase letters\n");
        if (!report->has_upper)  printf("  - add uppercase letters\n");
        if (!report->has_digit)  printf("  - add numbers\n");
        if (!report->has_symbol) printf("  - add symbols like ! ? # %%\n");
    } else {
        printf("\nNice - that is a strong password!\n");
    }
    printf("-----------------------\n\n");
}

int main(void)
{
    char password[MAX_LEN];

    printf("==============================\n");
    printf("  PASSWORD STRENGTH CHECKER\n");
    printf("==============================\n");
    printf("Type a password to test it, or 'quit' to exit.\n\n");

    /* keep asking until the user types quit */
    while (1) {
        printf("Password: ");
        if (fgets(password, MAX_LEN, stdin) == NULL) {
            break;
        }

        /* remove the newline that fgets keeps */
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(password, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        if (strlen(password) == 0) {
            printf("Please type something.\n");
            continue;
        }

        PasswordReport report = analyse_password(password);
        print_report(&report);
    }

    return 0;
}
