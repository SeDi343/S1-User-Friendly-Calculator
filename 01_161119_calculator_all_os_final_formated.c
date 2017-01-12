/* !* User-Friendly Calculator
 *
 * \description A user-friendly calculator calculating with
 * <Number 1> <operator> <Number 2> an operation.
 * Number 1 and Number 2 are floating-point numbers
 * operator uses + , - , * , / , ** , _/ , % for calculation operations.
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at>
 *
 * \version Rev.: 01, 08.11.2016 - Created
 * 
 * \version Rev.: 02, 09.11.2016 - Added convertion from string to float
 * 
 * \version Rev.: 03, 11.11.2016 - Added operations, and subroutine lines,
 *                                 start of errormessages, Ans as previous result
 * 
 * \version Rev.: 04, 12.11.2016 - Continue writing errormessages, including
 *                                 parameters "h", "H" , "?" for helpdesk2,
 *                                 for detailed instructions to the calculator
 * 
 * \version Rev.: 05, 13.11.2016 - Writing helpdesks
 * 
 * \version Rev.: 06, 15.11.2016 - Continue writing errormessages,
 *                                 changing float to long double
 *                                 due some problems with float,
 *                                 formating the .c file for submission
 * 
 * \version Rev.: 07, 17.11.2016 - Finding a solution for out of range strings,
 *                                 entering too many characters for each string.
 *                                 Importing different print out format for
 *                                 bigger answers (now printing X.XXE+XX).
 *                                 Also printing out "fat" letters for warnings
 *                                 and important information.
 *
 * \version Rev.: 08, 19.11.2016 - New to version 2.0 - big os support
 *                                 !!!!THIS CODE NOW SUPPORTS LINUX,
 *                                 WINDOWS AND MACOS!!!!
 * \version Rev.: 09, 21.11.2016 - Reduced code, code tested on
 *                                 Ubuntu 14.04LTS 32bit, Windows10 64bit
 *                                 and MacOS Sierra
 *                                 Added "-Ans" as avaible String for calculating
 *                                 with negative previous result (just for Linux
 *                                 and Apple)
 * \version Rev.: 10, 22.11.2016 - Removed useless code, and format for handin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

/*------------------------------------------------------------------*/
/* C O D E   F O R   M A C O S   &   L I N U X                      */
/*------------------------------------------------------------------*/

#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)

#define NUM 20


#define RESET   "\033[0m"
#define BLACK   "\033[30m"                 /* Black */
#define GREEN   "\033[32m"                 /* Green */
#define CYAN    "\033[36m"                 /* Cyan */
#define BOLD    "\033[1m"                  /* Bold */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void helpdesk_1(void);
void helpdesk_2(void);
long double addition(long double nr1, long double nr2);
long double subtraction(long double nr1, long double nr2);
long double multiplication(long double nr1, long double nr2);
long double division(long double nr1, long double nr2);
long double powerof(long double nr1, long double nr2);
long double rootof(long double nr1, long double nr2);
long double percent(long double nr1, long double nr2);

/*Variable for subroutine answers*/
long double answer;

int main(int argc, char *argv[])
{
    /*Variable for errormessages and counter for for-loop*/
    int error;
    int counter = 0;
    
    /*Variable for type of output*/
    long double maxans = 999999999999999;
    
    /*Variable for answer in main program*/
    long double ans = 0;
    char *pEnd;
    char CheckAns[] = "Ans";
    char CheckAnsNegativ[] = "-Ans";
    
    char number_1[NUM];
    long double number_1_ld;
    
    char operator[2];
    
    char number_2[NUM];
    long double number_2_ld;
    
/*------------------------------------------------------------------*/
/* H E L P D E S K                                                  */
/*------------------------------------------------------------------*/
    
    if (argc > 1)
    {
        /*If Parameter 1 (after Programmparameter (a.out)) contains h, H or ?*/
        if (argv[1][0] == 'h' || argv[1][0] == 'H' || argv[1][0] == '?')
        {
            helpdesk_2();
            return 0;
        }
        else
        {
            printf(BOLD "ERROR: UNKNOWN PARAMETER use ?, \"H\" OR \"h\"\n" RESET);
            return 0;
        }
    }
    
    helpdesk_1();
    
/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M M                                */
/*------------------------------------------------------------------*/
    
    while (1)
    {
        for (counter = 0; counter < strlen(operator); counter++)
        {
            operator[counter] = '\0';
        }
        
        printf("> ");
        /*Read 3 strings number_1, operator and number_2
         with size 19, 2 and 19*/
        scanf("%19s %2s %19s", number_1, operator, number_2);
        
        /*Set error to 0 for every loop-pass*/
        error = 0;
        
#if DEBUG
        printf("Number1 = %s\n", number_1);
        printf("Number2 = %s\n", number_2);
        printf("Operator = %s\n\n", operator);
#endif
        
/* ---- CONVERT STRING TO LONG DOUBLE ---- */
        number_1_ld = strtold(number_1, &pEnd);
        number_2_ld = strtold(number_2, &pEnd);
        
/* ---- IMPORT ANS AS AVAIBLE NUMBER ---- */
        
        if (strcmp(number_1, CheckAns) == 0)
        {
            number_1_ld = ans;
        }
        
        if (strcmp(number_2, CheckAns) == 0)
        {
            number_2_ld = ans;
        }
        
/* ---- IMPORT neg ANS AS AVAIBLE NUMBER ---- */
        if (strcmp(number_1, CheckAnsNegativ) == 0)
        {
            number_1_ld = 0 - ans;
        }
        
        if (strcmp(number_2, CheckAnsNegativ) == 0)
        {
            number_2_ld = 0 - ans;
        }
        
#if DEBUG
        printf("Number1f = %.4Lf\n", number_1_ld);
        printf("Number2f = %.4Lf\n\n", number_2_ld);
        
#endif
        
        
/*------------------------------------------------------------------*/
/* E R R O R M E S S A G E S                                        */
/*------------------------------------------------------------------*/
        
/* ---- Out of Range Characters 1 and 2 - Exits Program if true ---- */
        if (error == 0)
        {
            /* If operator includes a digit, upper letter or lower letter.
             If string 2 is to big it needs 2 passes of loop*/
            if (isdigit(operator[0]) || isupper(operator[0]) ||
                islower(operator[0]) || operator[0] == '\0')
            {
                printf(BOLD "ERROR: ABOVE AREA STRING (max. CHARACTERS of each "
                       "NUMBER-STRING is 19)\n" RESET);
                printf(BOLD "!!!PREVIOUS OR LAST INPUT TOO HIGH!!!\n" RESET);
                printf(BOLD "!!!PREVIOUS CALCULATION COULD BE WRONG!!!\n" RESET);
                error = 1;
                return -1;
            }
        }
        
/* ---- Number with wrong character input - Number 1 ---- */
        if (error == 0)
        {
            for (counter = 0; counter < strlen(number_1); counter ++)
            {
                /*If number_1 contains an upper or lower letter,
                 "," not "Ans", not "e" or not "E"*/
                if ((islower(number_1[counter]) || isupper(number_1[counter]) ||
                     number_1[counter] == ',') && (strcmp(number_1, CheckAns) != 0) &&
                    (strcmp(number_1, CheckAnsNegativ) != 0) &&
                    (number_1[counter] != 'e') && (number_1[counter] != 'E'))
                {
                    printf(BOLD "ERROR: UNKNOWN NUMBER 1 (NUMERIC CHARACTERS "
                    "(USE \".\" instead of \",\" for FLOATING POINT) or \"Ans\")\n" RESET);
                    error = 1;
                    break;
                }
            }
        }
        
/* ---- Number with wrong character input - Number 2 ---- */
        if (error == 0)
        {
            for (counter = 0; counter < strlen(number_2); counter ++)
            {
                /*If number_2 contains an upper or lower letter,
                 "," not "Ans", not "e" or not "E"*/
                if ((islower(number_2[counter]) || isupper(number_2[counter]) ||
                     number_2[counter] == ',') && (strcmp(number_2, CheckAns) != 0) &&
                    (strcmp(number_2, CheckAnsNegativ) != 0) &&
                    (number_2[counter] != 'e') && (number_2[counter] != 'E'))
                {
                    printf(BOLD "ERROR: UNKNOWN NUMBER 2 (NUMERIC CHARACTERS "
                    "(USE \".\" instead of \",\" for FLOATING POINT) or \"Ans\")\n" RESET);
                    error = 1;
                    break;
                }
            }
        }
        
/* ---- Unknown Operator ---- */
        if (error == 0)
        {
            /*If Operator is not + , - , * , / , ** , _/ , % */
            if ((operator[0] != '+' || operator[1] != '\0') &&
                (operator[0] != '-' || operator[1] != '\0') &&
                (operator[0] != '*' || operator[1] != '\0') &&
                (operator[0] != '/' || operator[1] != '\0') &&
                (operator[0] != '*' || operator[1] != '*') &&
                (operator[0] != '_' || operator[1] != '/') &&
                (operator[0] != '%' || operator[1] != '\0'))
            {
                printf(BOLD "ERROR: UNKNOWN OPERATOR (+, -, *, /, %%, _/, **)\n" RESET);
                error = 1;
            }
        }
        
/* ---- Division with ZERO ---- */
        if (error == 0)
        {
            /*If Operator is / and number_2_ld is 0*/
            if (operator[0] == '/' &&  number_2_ld == 0)
            {
                printf(BOLD "ERROR: DIVISION WITH ZERO\n" RESET);
                error = 1;
            }
        }
        
/* ---- ROOT of NEGATIVE NUMBER ---- */
        if (error == 0)
        {
            /*If Operator is _/ and number_2_ld is lower than 0*/
            if (operator[0] == '_' && operator[1] == '/' && number_2_ld < 0)
            {
                printf(BOLD "ERROR: %.0Lfth ROOT OF NEGATIVE NUMBER "
                "IS NOT ALLOWED\n" RESET, number_1_ld);
                error = 1;
            }
        }
        
/*------------------------------------------------------------------*/
/* C A L C U L A T O R                                              */
/*------------------------------------------------------------------*/
        
/* ---- CALCULATION ADDITION ---- */
        if (operator[0] == '+' && error == 0)
        {
            ans = addition(number_1_ld, number_2_ld);
            
            if (ans > maxans)
            {
                printf("Ans = %.4LE\n", ans);
            }
            else
            {
                printf("Ans = %.4Lf\n", ans);
            }
        }
        
/* ---- CALCULATION SUBTRACTION ---- */
        if (operator[0] == '-' && error == 0)
        {
            ans = subtraction(number_1_ld, number_2_ld);
            
            if (ans > maxans)
            {
                printf("Ans = %.4LE\n", ans);
            }
            else
            {
                printf("Ans = %.4Lf\n", ans);
            }
        }
        
/* ---- CALCULATION MULTIPLICATION & POWER OF ---- */
        if (operator[0] == '*' && error == 0)
        {
            if (operator[1] == '*')
            {
                ans = powerof(number_1_ld, number_2_ld);
                if (number_2_ld > 20)
                {
                    printf("Ans = %.4LE\n", ans);
                }
                else
                {
                    printf("Ans = %.4Lf\n", ans);
                }
            }
            else
            {
                ans = multiplication(number_1_ld, number_2_ld);
                
                if (ans > maxans)
                {
                    printf("Ans = %.4LE\n", ans);
                }
                else
                {
                    printf("Ans = %.4Lf\n", ans);
                }
            }
        }
        
/* ---- CALCULATION DIVISION ---- */
        if (operator[0] == '/' && error == 0)
        {
            ans = division(number_1_ld, number_2_ld);
            
            if (ans > maxans)
            {
                printf("Ans = %.4LE\n", ans);
            }
            else
            {
                printf("Ans = %.4Lf\n", ans);
            }
        }
        
/* ---- CALCULATION ROOT ---- */
        if (operator[0] == '_' && operator[1] == '/' && error == 0)
        {
            ans = rootof(number_1_ld, number_2_ld);
            
            if (ans > maxans)
            {
                printf("Ans = %.4LE\n", ans);
            }
            else
            {
                printf("Ans = %.4Lf\n", ans);
            }
        }
        
/* ---- CALCULATION PERCENT ---- */
        if (operator[0] == '%' && error == 0)
        {
            ans = percent(number_1_ld, number_2_ld);
            
            if (ans > maxans)
            {
                printf("Ans = %.4LE%%\n", ans);
            }
            else
            {
                printf("Ans = %.4Lf%%\n", ans);
            }
        }
        
        fflush(stdout);
        memset(number_1,0,strlen(number_1));
        memset(number_2,0,strlen(number_2));
    }
    return 0;
}

/*------------------------------------------------------------------*/
/* S U B R O U T I N E   L I N E S                                  */
/*------------------------------------------------------------------*/

long double addition(long double nr1, long double nr2)
{
    answer = nr1 + nr2;
    return answer;
}
long double subtraction(long double nr1, long double nr2)
{
    answer = nr1 - nr2;
    return answer;
}
long double multiplication(long double nr1, long double nr2)
{
    answer = nr1 * nr2;
    return answer;
}
long double division(long double nr1, long double nr2)
{
    answer = nr1 / nr2;
    return answer;
}
long double powerof(long double nr1, long double nr2)
{
    answer = powl(nr1,nr2);
/*           powl (long double base, long double exponent); */
    return answer;
}
long double rootof(long double nr1, long double nr2)
{
    answer = powl(nr2, 1./nr1);
    return answer;
}
long double percent(long double nr1, long double nr2)
{
    answer = (nr1 / nr2) * 100;
    return answer;
}

#endif

/*------------------------------------------------------------------*/
/* S U B R O U T I N E   L I N E S (A P P L E)                      */
/*------------------------------------------------------------------*/

#if defined(__APPLE__) && defined(__MACH__)

void helpdesk_1(void)
{
    printf("\n");
    printf(BOLD "USER FRIENDLY CALCULATOR @ v2.0_mac\n" RESET);
    printf(BOLD "Created by Sebastian Dichler, 2016\n\n" RESET);
    printf("Correct writing of input: "
    "" BOLD "<Number 1> <operator> <Number 2>\n" RESET);
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n");
    printf(BOLD "For more INFORMATION use \"h\", \"H\" or \"?\" "
    "as a parameter\n\n" RESET);
}

void helpdesk_2(void)
{
    printf("\n");
    printf(BOLD "USER FRIENDLY CALCULATOR @ v2.0_mac\n" RESET);
    printf(BOLD "Created by Sebastian Dichler, 2016\n\n" RESET);
    printf("Correct writing of input: "
    "" BOLD "<Number 1> <operator> <Number 2>\n" RESET);
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n\n");
    printf("The result is roundet to " BOLD "FOUR" RESET " decimal places\n");
    printf("If the result is a bigger number answer is printed to XX+EXX writing\n");
    printf("The previous result is also available in the next calculation\n");
    printf("by entering the String \"Ans\" as <Number 1> and/or <Number 2>.\n");
    printf("The Numbers must be a " BOLD "NUMMERIC CHARACTER "
    "" RESET " and/or " BOLD "\"Ans\"" RESET " and has a maximum\n");
    printf("of " BOLD "19 CHARACTERS" RESET " each number.\n");
    printf("The Number input can also be e, as an example \"14e+3\" or E, "
    "as an example \"14E+3\".\n");
    printf("It's not possible to divide with " BOLD "ZERO" RESET ".\n");
    printf("Root of a " BOLD "NEGATIVE NUMBER" RESET " is also forbidden.\n\n");
}

#endif

/*------------------------------------------------------------------*/
/* S U B R O U T I N E   L I N E S (L I N U X)                      */
/*------------------------------------------------------------------*/

#if defined(__linux__)

void helpdesk_1(void)
{
    printf("\n");
    printf(BOLD "USER FRIENDLY CALCULATOR @ v2.0_linux\n" RESET);
    printf(BOLD "Created by Sebastian Dichler, 2016\n\n" RESET);
    printf("Correct writing of input: "
    "" BOLD "<Number 1> <operator> <Number 2>\n" RESET);
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n");
    printf(BOLD "For more INFORMATION use \"h\", \"H\" or \"?\" "
    "as a parameter\n\n" RESET);
}

void helpdesk_2(void)
{
    printf("\n");
    printf(BOLD "USER FRIENDLY CALCULATOR @ v2.0_linux\n" RESET);
    printf(BOLD "Created by Sebastian Dichler, 2016\n\n" RESET);
    printf("Correct writing of input: "
    "" BOLD "<Number 1> <operator> <Number 2>\n" RESET);
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n\n");
    printf("The result is roundet to " BOLD "FOUR" RESET " decimal places\n");
    printf("If the result is a bigger number answer is printed to XX+EXX writing\n");
    printf("The previous result is also available in the next calculation\n");
    printf("by entering the String \"Ans\" as <Number 1> and/or <Number 2>.\n");
    printf("The Numbers must be a " BOLD "NUMMERIC CHARACTER"
    "" RESET " and/or " BOLD "\"Ans\"" RESET " and has a maximum\n");
    printf("of " BOLD "19 CHARACTERS" RESET " each number.\n");
    printf("The Number input can also be e, as an example \"14e+3\" or E, "
    "as an example \"14E+3\".\n");
    printf("It's not possible to divide with " BOLD "ZERO" RESET ".\n");
    printf("Root of a " BOLD "NEGATIVE NUMBER" RESET " is also forbidden.\n\n");
}

#endif

/*------------------------------------------------------------------*/
/* C O D E   F O R   W I N D O W S                                  */
/*------------------------------------------------------------------*/

#if defined(_WIN64) || defined(_WIN32)

#include <conio.h>

#define NUM 17


void helpdesk_1(void);
void helpdesk_2(void);
double addition(double nr1, double nr2);
double subtraction(double nr1, double nr2);
double multiplication(double nr1, double nr2);
double division(double nr1, double nr2);
double powerof(double nr1, double nr2);
double rootof(double nr1, double nr2);
double percent(double nr1, double nr2);

/*Variable for subroutine answers*/
double answer;

int main(int argc, char *argv[])
{
    int error;
    int counter = 0;
    
    /*Variable for type of output*/
    double maxans = 999999999999999;
    
    /*Variable for answer in main program*/
    double ans = 0;
    char *pEnd;
    char CheckAns[] = "Ans";
    
    char number_1[NUM-1];
    double number_1_d;
    
    char operator[3];
    
    char number_2[NUM];
    double number_2_d;
    
/*------------------------------------------------------------------*/
/* H E L P D E S K                                                  */
/*------------------------------------------------------------------*/
    
    if (argc > 1)
    {
        /*If Parameter 1 (after Programmparameter (a.out)) contains h, H or ?*/
        if (argv[1][0] == 'h' || argv[1][0] == 'H' || argv[1][0] == '?')
        {
            helpdesk_2();
            return 0;
        }
        else
        {
            printf("ERROR: UNKNOWN PARAMETER use ? or START WITH \"H\" OR \"h\"\n");
            return 0;
        }
    }
    
    helpdesk_1();
    
/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M M                                */
/*------------------------------------------------------------------*/
    
    while (1)
    {
        for (counter = 0; counter < strlen(operator); counter++)
        {
            operator[counter] = '\0';
        }
        printf("> ");
        /*Read 3 strings number_1, operator and number_2
         with size 16, 2 and 17 - we only use 16*/
        scanf("%16s %3s %17s", number_1, operator, number_2);
        
        /*Set error to 0 for every loop-pass*/
        error = 0;
        
#if DEBUG
        printf("Number1 = %s\n", number_1);
        printf("Number2 = %s\n", number_2);
        printf("Operator = %s\n\n", operator);
#endif
        
/* -----CONVERT STRING TO LONG DOUBLE----- */
        number_1_d = strtod(number_1, &pEnd);
        number_2_d = strtod(number_2, &pEnd);
        
/* -----IMPORT ANS AS AVAIBLE NUMBER----- */
        
        if (strcmp(number_1, CheckAns) == 0)
        {
            number_1_d = ans;
        }
        
        if (strcmp(number_2, CheckAns) == 0)
        {
            number_2_d = ans;
        }
        
#if DEBUG
        printf("Number1f = %.4lf\n", number_1_d);
        printf("Number2f = %.4lf\n\n", number_2_d);
        
#endif
        
        
/*------------------------------------------------------------------*/
/* E R R O R M E S S A G E S                                        */
/*------------------------------------------------------------------*/
        
/* ---- Out of Range Characters 1 and 2 - Exits Program if true ---- */
        if (error == 0)
        {
            /* If operator includes a digit, upper letter or lower letter.
             If string 2 is to big it needs 2 passes of loop*/
            if (isdigit(operator[0]) || isupper(operator[0]) ||
                islower(operator[0]) || isdigit(operator[1]) ||
                isupper(operator[1]) || islower(operator[1]) ||
                operator[0] == '\0')
            {
                printf("ERROR: ABOVE AREA STRING (max. CHARACTERS of each "
                "NUMBER-STRING is 16)\n");
                printf("!!!PREVIOUS OR LAST INPUT TOO HIGH!!!\n");
                printf("!!!PREVIOUS CALCULATION COULD BE WRONG!!!\n");
                error = 1;
                _getch();
                return -1;
            }
        }
        
/* ---- Number with wrong character input - Number 1 ---- */
        if (error == 0)
        {
            for (counter = 0; counter < strlen(number_1); counter ++)
            {
                /*If number_1 contains an upper or lower letter,
                 "," not "Ans", not "e" or not "E"*/
                if ((islower(number_1[counter]) || isupper(number_1[counter]) ||
                     number_1[counter] == ',') && (strcmp(number_1, CheckAns) != 0) &&
                    number_1[counter] != 'e' && number_1[counter] != 'E')
                {
                    printf("ERROR: UNKNOWN NUMBER 1 (NUMERIC CHARACTERS "
                    "(USE \".\" instead of \",\" for FLOATING POINT) or \"Ans\")\n");
                    error = 1;
                    break;
                }
            }
        }
        
/* ---- Number with wrong character input - Number 2 ---- */
        if (error == 0)
        {
            for (counter = 0; counter < strlen(number_2); counter ++)
            {
                /*If number_2 contains an upper or lower letter,
                 "," not "Ans", not "e" or not "E"*/
                if ((islower(number_2[counter]) || isupper(number_2[counter]) ||
                     number_2[counter] == ',') && (strcmp(number_2, CheckAns) != 0) &&
                    number_2[counter] != 'e' && number_2[counter] != 'E')
                {
                    printf("ERROR: UNKNOWN NUMBER 2 (NUMERIC CHARACTERS "
                    "(USE \".\" instead of \",\" for FLOATING POINT) or \"Ans\")\n");
                    error = 1;
                    break;
                }
            }
        }
        
/* ---- Unknown Operator ---- */
        if (error == 0)
        {
            /*If Operator is not + , - , * , / , ** , _/ , % */
            if (((operator[0] != '+' || operator[1] != '\0') &&
                 (operator[0] != '-' || operator[1] != '\0') &&
                 (operator[0] != '*' || operator[1] != '\0') &&
                 (operator[0] != '/' || operator[1] != '\0') &&
                 (operator[0] != '*' || operator[1] != '*') &&
                 (operator[0] != '_' || operator[1] != '/') &&
                 (operator[0] != '%' || operator[1] != '\0')) ||
                operator[2] != '\0')
            {
                printf("ERROR: UNKNOWN OPERATOR ( + , - , * , / , %% , _/ , ** )\n");
                error = 1;
                continue;
            }
        }
        
/* ---- Division with ZERO ---- */
        if (error == 0)
        {
            /*If Operator is / and number_2_ld is 0*/
            if (operator[0] == '/' &&  number_2_d == 0)
            {
                printf("ERROR: DIVISION WITH ZERO\n");
                error = 1;
            }
        }
        
/* ---- ROOT of NEGATIVE NUMBER ---- */
        if (error == 0)
        {
            /*If Operator is _/ and number_2_ld is lower than 0*/
            if (operator[0] == '_' && operator[1] == '/' && number_2_d < 0)
            {
                printf("ERROR: %.0fth ROOT OF NEGATIVE NUMBER "
                "IS NOT ALLOWED\n", number_1_d);
                error = 1;
            }
        }
        
/*------------------------------------------------------------------*/
/* C A L C U L A T O R                                              */
/*------------------------------------------------------------------*/
        
/* ---- CALCULATION ADDITION ---- */
        if (operator[0] == '+' && error == 0)
        {
            ans = addition(number_1_d, number_2_d);
            
            if (ans > maxans)
            {
                printf("Ans = %.4lE\n", ans);
            }
            else
            {
                printf("Ans = %.4lf\n", ans);
            }
        }
        
/* ---- CALCULATION SUBTRACTION ---- */
        if (operator[0] == '-' && error == 0)
        {
            ans = subtraction(number_1_d, number_2_d);
            
            if (ans > maxans)
            {
                printf("Ans = %.4lE\n", ans);
            }
            else
            {
                printf("Ans = %.4lf\n", ans);
            }
        }
        
/* ---- CALCULATION MULTIPLICATION & POWER OF ---- */
        if (operator[0] == '*' && error == 0)
        {
            if (operator[1] == '*')
            {
                ans = powerof(number_1_d, number_2_d);
                if (number_2_d > 20)
                {
                    printf("Ans = %.4lE\n", ans);
                }
                else
                {
                    printf("Ans = %.4lf\n", ans);
                }
            }
            else
            {
                ans = multiplication(number_1_d, number_2_d);
                
                if (ans > maxans)
                {
                    printf("Ans = %.4lE\n", ans);
                }
                else
                {
                    printf("Ans = %.4lf\n", ans);
                }
            }
        }
        
/* ---- CALCULATION DIVISION ---- */
        if (operator[0] == '/' && error == 0)
        {
            ans = division(number_1_d, number_2_d);
            
            if (ans > maxans)
            {
                printf("Ans = %.4lE\n", ans);
            }
            else
            {
                printf("Ans = %.4lf\n", ans);
            }
        }
        
/* ---- CALCULATION ROOT ---- */
        if (operator[0] == '_' && operator[1] == '/' && error == 0)
        {
            ans = rootof(number_1_d, number_2_d);
            
            if (ans > maxans)
            {
                printf("Ans = %.4lE\n", ans);
            }
            else
            {
                printf("Ans = %.4lf\n", ans);
            }
        }
        
/* ---- CALCULATION PERCENT ---- */
        if (operator[0] == '%' && error == 0)
        {
            ans = percent(number_1_d, number_2_d);
            
            if (ans > maxans)
            {
                printf("Ans = %.4lE%%\n", ans);
            }
            else
            {
                printf("Ans = %.4lf%%\n", ans);
            }
        }
        
        fflush(stdout);
        memset(number_1,0,strlen(number_1));
        memset(number_2,0,strlen(number_2));
    }
    return 0;
}

/*------------------------------------------------------------------*/
/* S U B R O U T I N E   L I N E S                                  */
/*------------------------------------------------------------------*/

void helpdesk_1(void)
{
    printf("\n");
    printf("USER FRIENDLY CALCULATOR @ v2.0_win\n");
    printf("Created by Sebastian Dichler, 2016\n\n");
    printf("Correct writing of input: <Number 1> <operator> <Number 2>\n");
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n");
    printf("For more INFORMATION use \"h\", \"H\" or \"?\" as a parameter\n\n");
}

void helpdesk_2(void)
{
    printf("\n");
    printf("USER FRIENDLY CALCULATOR @ v2.0_win\n");
    printf("Created by Sebastian Dichler, 2016\n\n");
    printf("Correct writing of input: <Number 1> <operator> <Number 2>\n");
    printf("----------------------------------------------------------\n");
    printf("Implemented operations:\n");
    printf("<operator>\t Operation\n");
    printf("+\t\t Addition\n");
    printf("-\t\t Subtraction\n");
    printf("*\t\t Multiplication\n");
    printf("/\t\t Division\n");
    printf("**\t\t <Number 1> to the power of <Number 2>\n");
    printf("_/\t\t The <Number 1> -th root of <Number 2>\n");
    printf("%%\t\t <Number 1> in percent of <Number 2>\n");
    printf("----------------------------------------------------------\n\n");
    printf("The result is roundet to FOUR decimal places\n");
    printf("If the result is a bigger number answer is printed to XX+EXX writing\n");
    printf("The previous result is also available in the next calculation\n");
    printf("by entering the String \"Ans\" as <Number 1> and/or <Number 2>.\n");
    printf("The Numbers must be a NUMMERIC CHARACTER "
    "and/or \"Ans\" and has a maximum\n");
    printf("of 16 CHARACTERS each number.\n");
    printf("The Number input can also be e, as an example \"14e+3\" or E, "
    "as an example \"14E+3\".\n");
    printf("It's not possible to divide with ZERO.\n");
    printf("Root of a NEGATIVE NUMBER is also forbidden.\n\n");
}

double addition(double nr1, double nr2)
{
    answer = nr1 + nr2;
    return answer;
}
double subtraction(double nr1, double nr2)
{
    answer = nr1 - nr2;
    return answer;
}
double multiplication(double nr1, double nr2)
{
    answer = nr1 * nr2;
    return answer;
}
double division(double nr1, double nr2)
{
    answer = nr1 / nr2;
    return answer;
}
double powerof(double nr1, double nr2)
{
    answer = pow(nr1,nr2);
/*           pow (double base, double exponent); */
    return answer;
}
double rootof(double nr1, double nr2)
{
    answer = pow(nr2, 1./nr1);
    return answer;
}
double percent(double nr1, double nr2)
{
    answer = (nr1 / nr2) * 100;
    return answer;
}

#endif
