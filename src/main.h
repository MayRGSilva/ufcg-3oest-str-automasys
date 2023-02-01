#ifndef __MAIN_H__
#define __MAIN_H__

#define MIN_TRES 0
#define MAX_TRES 60
#define MIN_TEMP 16
#define MAX_TEMP 32
#define MIN_TEMP_FR 14
#define MAX_TEMP_FR 25

typedef enum {
    Abrir_Ligar,
    Fechar_Desligar
}acionamento;

typedef enum {
    config,
    modos
}operacao;

typedef enum {
    refrig,
    autom,
    ventil
}modosArCond;

typedef enum {
    roupasPesadas,
    roupasDelicadas,
    rapida
}modosLavagem;

typedef enum {
    varrer,
    aspirar,
    limpar
}modosAsp;

acionamento xReqAcion();
int sRand(int min, int max);
void vCtrlArCond();
void vCtrlMaqLav();
void vCtrlTempFr();
void vCtrlAsp();
void vBkgServer();

#endif