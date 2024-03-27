#ifndef ARTOZERSKY_TESTS_HPP
#define ARTOZERSKY_TESTS_HPP

#include <iostream> // cout, cerr
#include <chrono>   // high_resolution_clock, duration

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

#define COLORIZE_RED(text)     ANSI_COLOR_RED text ANSI_COLOR_RESET
#define COLORIZE_GREEN(text)   ANSI_COLOR_GREEN text ANSI_COLOR_RESET
#define COLORIZE_CYAN(text)    ANSI_COLOR_CYAN text ANSI_COLOR_RESET
#define COLORIZE_YELLOW(text)  ANSI_COLOR_YELLOW text ANSI_COLOR_RESET

/*****************************************************************************
 * Example of usage:
 * int main()
 * {
 *     int a = 5;
 *     int b = 10;
 *
 *     TestEqual(6, a);
 *     TestLarger(b, a);
 *     TestUnEqual(5, b);
 *     TestExpression(a == b);
 *
 *     return 0;
 * }
 * Output:
 *
 * TestEqual failed: 6 == a in file 14.cpp at line 98; failure number: 1;
 * TestExpression failed: a == b in file 14.cpp at line 101; failure number: 2;
 * Total Tests: 4
 * Passed Tests: 2
 * Failed Tests: 2
 * Running Time: 0.072314ms
 *
 ****************************************************************************/

// MACROS of Tests, add your own
#define TestExpression(expression)                               \
    (++(testSummary.m_num_of_tests));                            \
    if (!(expression)) {                                         \
        std::cerr << COLORIZE_RED("TestExpression failed: ")     \
                  << #expression                                 \
                  << " in file " << __FILE__                     \
                  << " at line " << __LINE__                     \
                  << "; " << COLORIZE_RED("failure number: ")    \
                  << ++(testSummary.m_failureCount) << "; "      \
                  << std::endl;                                  \
    }

#define TestEqual(expected, received)                            \
    (++(testSummary.m_num_of_tests));                            \
    if (expected != received) {                                  \
        std::cerr << COLORIZE_RED("TestEqual failed: ")          \
                  << #expected " == " #received                  \
                  << " in file " << __FILE__                     \
                  << " at line " << __LINE__                     \
                  << "; " << COLORIZE_RED("failure number: ")    \
                  << ++(testSummary.m_failureCount) << "; "      \
                  << std::endl;                                  \
    }

#define TestLarger(expected, received)                           \
    (++(testSummary.m_num_of_tests));                            \
    if (!(expected > received)) {                                \
        std::cerr << COLORIZE_RED("TestLarger failed: ")         \
                  << #expected " > " #received                   \
                  << " in file " << __FILE__                     \
                  << " at line " << __LINE__                     \
                  << "; " << COLORIZE_RED("failure number: ")    \
                  << ++(testSummary.m_failureCount) << "; "      \
                  << std::endl;                                  \
    }

#define TestUnEqual(expected, received)                          \
    (++(testSummary.m_num_of_tests));                            \
    if (!(expected != received)) {                               \
        std::cerr << COLORIZE_RED("TestUnEqual failed: ")        \
                  << #expected " != " #received                  \
                  << " in file " << __FILE__                     \
                  << " at line " << __LINE__                     \
                  << "; " << COLORIZE_RED("failure number: ")    \
                  << ++(testSummary.m_failureCount) << "; "      \
                  << std::endl;                                  \
    }

class TestSummary 
{
private:
    std::chrono::high_resolution_clock::time_point m_t1;

public:
    size_t m_num_of_tests;
    size_t m_failureCount = 0;

    TestSummary() : m_t1(std::chrono::high_resolution_clock::now()), m_num_of_tests(0)
    {
        //empty
    }
    ~TestSummary()
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - m_t1;

        std::cerr << ANSI_COLOR_CYAN << "Total Tests: "     \
        << m_num_of_tests << std::endl;
        std::cerr << ANSI_COLOR_GREEN << "Passed Tests: "   \
        << (m_num_of_tests - m_failureCount) << std::endl;
        std::cerr << ANSI_COLOR_RED << "Failed Tests: "     \
        << m_failureCount << std::endl;
        std::cerr << ANSI_COLOR_YELLOW << "Running Time: "  \
        << ms_double.count() << "ms" << std::endl;
    }
    
};

// Create a static instance of TestSummary
static TestSummary testSummary;

#endif /* ARTOZERSKY_TESTS_HPP */
