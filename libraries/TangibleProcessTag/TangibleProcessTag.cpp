//#include "/Users/yuyi/code/Tangible-Programming/lib/ProcessTag/ProcessTag.h" //<ProcessTag.h>
//#include "C:\Users\clari\Documents\ProgTang\PROGTANG\Tangible-Programming\lib\Actions\Actions.cpp"
#include <TangibleProcessTag.h>

#include <Arduino.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#define COLUMNS 4 // Numero de COLUMNS da matriz de Leitura

//Define códigos das operações
#define OPERATION 123
#define SUM 124
#define MINUS 125
#define MULTIPLY 126
#define DIVIDE 127

#define BEEP 201
#define BLINK 202
#define TURN_90 203
#define TURN_30 204
#define TURN_60 205
#define TURN_45 206
#define MOVE 207
#define BLINK_R 211
#define BLINK_G 212
#define BLINK_Y 213

#define DECLARE_X 301
#define DECLARE_Y 302
#define DECLARE_Z 303
#define USE_X 311
#define USE_Y 312
#define USE_Z 313

#define FOR 401
#define ENDFOR 402

#define IF 501
#define ENDIF 502
#define EQUALS 503
#define GREATER 504
#define LESS 505

#define ROBO 601
#define FRENTE 602
#define TRAS 603
#define PARAR 604

#define END 999

using namespace std;

std::map<int, int> correspondenteFor;
std::map<int, int> correspondenteIf;

int globalVariables[3] = {0, 0, 0}; //casa 0 -> X, casa 1-> Y, casa 2->Z

void ProcessTag::setupLCD()
{
    Play.lcd_begin();
    Play.printa("Comece Escanear", 1);
}

void ProcessTag::runCode(int a[][COLUMNS], int startLine, int lastLine)
{
    findEndIf(a, lastLine);
    findEndFor(a, lastLine);
    process(a, startLine, lastLine);
}


// FINDS

void ProcessTag::findEndFor(int a[][COLUMNS], int linhas)
{
    vector<int> pilha;
    for (int i = 0; i <= linhas; i++)
    {
        if (a[i][0] == FOR)
        {
            pilha.push_back(i);
        }
        if (a[i][0] == ENDFOR)
        {
            correspondenteFor[pilha.back()] = i;
            pilha.pop_back();
        }
    }
}

void ProcessTag::findEndIf(int a[][COLUMNS], int linhas)
{
    vector<int> pilha;
    for (int i = 0; i <= linhas; i++)
    {
        if (a[i][0] == IF)
        {
            pilha.push_back(i);
        }
        if (a[i][0] == ENDIF)
        {
            correspondenteIf[pilha.back()] = i;
            pilha.pop_back();
        }
    }
}

//doOperation recebe a linha inteira que possui o primeiro bloco (action) de doOperation
//e executa uma operação matemática
//verificar mais de uma operação por vez e ordem de operadores

//DECLARAÇÃO

void ProcessTag::declare_x(int value) //ao receber uma ação de declare_x set globalVariables[0] para o valor a ser declarado
{
    globalVariables[0] = value;
}

void ProcessTag::declare_y(int value) //ao receber uma ação de declare_y set globalVariables[1] para o valor a ser declarado
{
    globalVariables[1] = value;
}

void ProcessTag::declare_z(int value) //ao receber uma ação de declare_z set globalVariables[2] para o valor a ser declarado
{
    globalVariables[2] = value;
}

//OPERAÇÕES

int ProcessTag::doOperation(int a[COLUMNS])
{
    switch (a[2])
    {
    case SUM:
        return a[1] + a[3];
        break;
    case MINUS:
        return a[1] - a[3];
        break;
    case MULTIPLY:
        return a[1] * a[3];
        break;
    default:
        break;
    }
}

int ProcessTag::doFor(int a[][COLUMNS], int numberFor, int start, int end)
{
    //cout << "doFOR" << '\n';
    for (int i = 0; i < numberFor; i++)
    {
        process(a, start + 1, end - 1);
    }
}

int ProcessTag::doIf(int a[][COLUMNS], int comparator, int start, int endLine)
{
    //cout << "doIf" << '\n';
    switch (comparator)
    {
    case EQUALS:
    {
        if (a[start][1] == a[start][3])
        {
            process(a, start + 1, endLine - 1);
        }
        break;
    }

    case GREATER:
    {
        if (a[start][1] > a[start][3])
        {
            process(a, start + 1, endLine - 1);
        }
        break;
    }

    case LESS:
    {
        if (a[start][1] < a[start][3])
        {
            process(a, start + 1, endLine - 1);
        }
        break;
    }

    default:
        break;
    }
}

//ACTIONS

int ProcessTag::doBeep(int a[COLUMNS])
{
    Play.doBeep();
    //cout << "BEEP!\n";
    return -1;
}

int ProcessTag::doBlink(int a[COLUMNS])
{
    Play.pisca(7);
    Play.doBlink();
    //cout << "BLINK\n";
    return -1;
}

int ProcessTag::doRobot(int a[COLUMNS])
{
    Play.doRobot();
    //cout << "TURN 90\n";
    return -1;
}

int ProcessTag::doFrente(int a[COLUMNS])
{
    Play.doFrente();
    //cout << "TURN 90\n";
    return -1;
}

int ProcessTag::doTras(int a[COLUMNS])
{
    Play.doTras();
    //cout << "TURN 90\n";
    return -1;
}

int ProcessTag::doTurn90(int a[COLUMNS])
{
    Play.doTurn90();
    //cout << "TURN 90\n";
    return -1;
}

int ProcessTag::doTurn45(int a[COLUMNS])
{
    Play.doTurn45();
    //cout << "TURN 45\n";
    return -1;
}

int ProcessTag::doTurn30(int a[COLUMNS])
{
    Play.doTurn30();
    //cout << "TURN 30\n";
    return -1;
}

int ProcessTag::doTurn60(int a[COLUMNS])
{
    Play.doTurn60();
    //cout << "TURN 60\n";
    return -1;
}

int ProcessTag::doMove(int a[COLUMNS])
{
    Play.doMove();
    //cout << "MOVER\n";
    return -1;
}

// PROCESSAMENTO

int ProcessTag::dic(int action, int a[COLUMNS])
{
    switch (action)
    {
    case OPERATION:
        return doOperation(a);
        break;
    case BEEP:
        return doBeep(a);
        break;

    case BLINK:
        return doBlink(a);
        break;

    case BLINK_R:
        Play.pisca(46);
        break;

    case BLINK_G:
        Play.pisca(28);
        break;

    case BLINK_Y:
        Play.pisca(40);
        break;

    case TURN_90:
        return doTurn90(a);
        break;

    case TURN_45:
        return doTurn45(a);
        break;

    case TURN_30:
        return doTurn30(a);
        break;

    case TURN_60:
        return doTurn60(a);
        break;

    case MOVE:
        return doMove(a);
        break;
    
    case ROBO:
    	Play.doRobot();
    	break;
    
    case FRENTE:
    	Play.doFrente();
    	break;
    
    case TRAS:
    	Play.doTras();
    	break;

    case DECLARE_X:
    {
        declare_x(a[1]);
        //return -101; //indica que executei declaração
        break;
    }

    case DECLARE_Y:
    {
        declare_y(a[1]);
        return -101; //indica que executei declaração
    }
    case DECLARE_Z:
    {
        declare_z(a[1]);
        return -101; //indica que executei declaração
    }
    case END:
    {
        Serial.println("END!!!!!!");
        //cout << "END";
        return 999;
    }
    default:
        break;
    }
}

//processa ações de linha unica
void ProcessTag::processLine(int a[COLUMNS])
{
    //Serial.println("ProcessLine ok");
    for (int i = 0; i < COLUMNS; i++)
    {
        switch (a[i])
        {
        case USE_X:
            a[i] = globalVariables[0];
            break;
        case USE_Y:
            a[i] = globalVariables[1];
            break;
        case USE_Z:
            a[i] = globalVariables[2];
            break;
        default:
            break;
        }
    }
    dic(a[0], a);
}

//doFor recebe a matriz inteira, o numero de vezes de repetição,,
//a linha que começa o for e a linha que termina o for

//process recebe matriz de entrada com as leituras do código e executa ações de saída
// start inicio das linhas a serem processadas
// end END das linhas a serem processadas
int ProcessTag::process(int a[][COLUMNS], int start, int end) //recebe matriz com numero de colunas fixo
{
    for (int i = start; i <= end; i++) //itera sobre cada uma das linhas
    {
        int action = a[i][0];
        switch (action) //analisa ação a ser realizada pela linha
        {
        case FOR: //ação de varias linhas
        {
            int startFor = i;
            int endFor = correspondenteFor[i];
            //cout<<startFor<<","<<endFor<<'\n';
            doFor(a, a[i][1], startFor, endFor); //a[i][1] numero de vezes que repito o for
            i += endFor - startFor - 1;          //pula o que ta dentro do for
            break;
        }
        case IF: //ação de varias linhas
        {
            int startIf = i;
            int endIf = correspondenteIf[i];
            //cout<<startIf<<","<<endIf<<'\n';
            doIf(a, a[i][2], startIf, endIf); // a[i][2] sinal de comparação
            i += endIf - startIf - 1;         //pula o que ta dentro do if
            break;
        }
        case ENDFOR: //apenas indica o END do for, não executa uma ação
            //cout << "endFOR" << '\n';
            break;
        case ENDIF: //apenas indica o END do for, não executa uma ação
            //cout << "endIF" << '\n';
            break;
        default:
            processLine(a[i]); //executa ação de linha única
            break;
        }
    }
    return -100; //ENDMMM
}
