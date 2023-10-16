#include "Botao.h"
#include <Arduino.h>

Botao::Botao(int pinSalvar, int pinIncrementar, int pinMudarPonteiro, LiquidCrystal_I2C& lcdRef, bool check)
    : _pinSalvar(pinSalvar), _pinIncrementar(pinIncrementar), _pinMudarPonteiro(pinMudarPonteiro), lcd(lcdRef), _check(check) {
    pinMode(_pinSalvar, INPUT_PULLUP);
    pinMode(_pinIncrementar, INPUT_PULLUP);
    pinMode(_pinMudarPonteiro, INPUT_PULLUP);
    ponteiroPosicao = 0;
    for (int i = 0; i < 4; i++) valores[i] = 0;
}

void Botao::checarBotoes() {
    if (digitalRead(_pinIncrementar) == LOW) {
        _check = false;
        valores[ponteiroPosicao]++;
        if (ponteiroPosicao == 0 && valores[ponteiroPosicao] > 2) valores[ponteiroPosicao] = 0;
        if (ponteiroPosicao == 1 && valores[ponteiroPosicao] > 4) valores[ponteiroPosicao] = 0;
        if (ponteiroPosicao == 2 && valores[ponteiroPosicao] > 5) valores[ponteiroPosicao] = 0;
        if (ponteiroPosicao == 3 && valores[ponteiroPosicao] > 9) valores[ponteiroPosicao] = 0;
        delay(200);
        atualizarLCD();
    }

    if (digitalRead(_pinMudarPonteiro) == LOW) {
        _check = false;
        ponteiroPosicao = (ponteiroPosicao + 1) % 4;
        delay(200);
        atualizarLCD();
    }
}

void Botao::getHorario(int &hora, int &minuto) {
    if (digitalRead(_pinSalvar) == LOW) {
        hora = valores[0] * 10 + valores[1];
        minuto = valores[2] * 10 + valores[3];
        delay(200);
        _check = true;
        Serial.print("salvo");
    }
}

void Botao::atualizarLCD() {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Set: ");
    lcd.print(valores[0]);
    lcd.print(valores[1]);
    lcd.print(":");
    lcd.print(valores[2]);
    lcd.print(valores[3]);
    switch (ponteiroPosicao) {
        case 0: lcd.setCursor(5, 1); break;
        case 1: lcd.setCursor(6, 1); break;
        case 2: lcd.setCursor(8, 1); break;
        case 3: lcd.setCursor(9, 1); break;
    }
    lcd.write('_');
}
