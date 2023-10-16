#ifndef Botao_h
#define Botao_h

#include <LiquidCrystal_I2C.h>

class Botao {
public:
    Botao(int pinSalvar, int pinIncrementar, int pinMudarPonteiro, LiquidCrystal_I2C& lcdRef, bool check);
    void checarBotoes();
    void getHorario(int &hora, int &minuto);
private:
    int _pinSalvar, _pinIncrementar, _pinMudarPonteiro;
    int ponteiroPosicao;
    int valores[4];
    LiquidCrystal_I2C& lcd;
    bool _check;
    void atualizarLCD();
};

#endif
