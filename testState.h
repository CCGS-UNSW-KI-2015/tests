/* testState.h
 * Defines functions for testState.c
 * Includes color ANSI escape sequences
 * and boolean integers.
 */

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

#define RESET   "\x1b[0m"

#define TRUE 1
#define FALSE 0

typedef char boolean;

/* void advAssert(Game game, char* action, int expected, int got, char* helpText)
 * A verbose assert that checks if expected is equal to got.
 * If it is not, it prints a description, and dumps the current
 * game state. (All of it.)
 */
void advAssert(Game game, char* action, int expected, int got, char* helpText);

/* void assertState(Game game, stateSet state)
 * Performs checks on the state
 * (I think, correct this if I'm wrong)
 */
void assertState(Game game, stateSet state);
