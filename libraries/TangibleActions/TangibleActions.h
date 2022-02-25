#ifndef TangibleActions_h
#define TangibleActions_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


class Actions
{
public:
    void lcd_begin(void);
    void printa(char *, int);
    void scroll(char *, int);

    void pisca(int);
    void acende(int);
    void apaga(int);

    void beep(int);
    void beep_music(int);

    void doBeep(void);
    void doBlink(void);
    void doMove(void);
    void doRobot(void);
    void doFrente(void);
    void doTras(void);
    void doTurn90(void);
    void doTurn45(void);
    void doTurn30(void);
    void doTurn60(void);
};

#endif
