#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <linux/prctl.h>
#include <sys/prctl.h>

#include <czext.h>

void NoThanksFuckYou(int sig);

char *line = NULL;
const char *key = "0x0f";
int failed_attempts = 0;

int main(void)
{
    signal(SIGINT, NoThanksFuckYou);
    signal(SIGTERM, NoThanksFuckYou);
    signal(SIGHUP, NoThanksFuckYou);

    prctl(PR_SET_PDEATHSIG, SIGHUP);
    
    cz_slowprintf("%s", ANSI_CLEAR_SCREEN_AND_SCROLLBACK);
    cz_slowprintf(
        "# get infekted kiddo!\n"
        "this assware is gentle..\n"
        "enter the right KEY and\n"
        "you will be let out :-)\n\n"

        "also, since i didn't want to\n"
        "make your terminal completely\n"
        "useless, you get a clock too.\n"
        "happy?\n\n"
    );

    while (1) {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        char timebuffer[9];
        strftime(timebuffer, sizeof(timebuffer), "%H:%M:%S", tm_info);

        cz_slowprintf("%s >", timebuffer);

        size_t len = 0;
        ssize_t read = getline(&line, &len, stdin);

        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, key) == 0) {
            const char *grammar = (failed_attempts >= 2)? "attempts" : "attempt";
            cz_slowprintf(
                "it took you %d %s\n"
                "%s, guessed it. now you're out.\n",
                failed_attempts, grammar, key
            );

            usleep(500*1000);   // 0.5s
            cz_slowprintf("..but not before you wait 10 more seconds. for fun.\n");

            for (int i = 10; i > 0; i--) {
                cz_slowprintf("%d..", i);
                fflush(stdout);
                usleep(1000*1000);
            }
            printf("\n");

            free(line);
            line = NULL;
            return 0;
        } else
            failed_attempts++;
    }

    free(line);
    line = NULL;
    return 0;
}

void NoThanksFuckYou(int sig)
{
    (void)sig;
}

