#ifndef TangibleProcessTag_h
#define TangibleProcessTag_h

#include <TangibleActions.h>


#include <iostream>
#include <map>


#define COLUMNS 4 //Número de sensores

class ProcessTag
{
public:
    std::map<int, int> correspondenteFor;
    std::map<int, int> correspondenteIf;
    Actions Play;
    void setupLCD();
    void runCode(int a[][COLUMNS], int startLine, int lastLine);
    int process(int a[][COLUMNS], int start, int end);
    int doIf(int a[][COLUMNS], int comparator, int start, int end);
    int doFor(int a[][COLUMNS], int numberFor, int start, int end);
    void findEndFor(int a[][COLUMNS], int linhas);
    void findEndIf(int a[][COLUMNS], int linhas);
    void processLine(int a[COLUMNS]);
    int dic(int action, int a[COLUMNS]);
    int doOperation(int a[COLUMNS]);
    void declare_x(int value);
    void declare_y(int value);
    void declare_z(int value);

    int doBeep(int a[COLUMNS]);
    int doBlink(int a[COLUMNS]);
    int doMove(int a[COLUMNS]);
    int doRobot(int a[COLUMNS]);
    int doFrente(int a[COLUMNS]);
    int doTras(int a[COLUMNS]);
    int doTurn90(int a[COLUMNS]);
    int doTurn45(int a[COLUMNS]);
    int doTurn30(int a[COLUMNS]);
    int doTurn60(int a[COLUMNS]);

private:
};

#endif
