#include <LedControl.h>

#define PINO_DIN 12
#define PINO_CS  11
#define PINO_CLK 10

LedControl lc = LedControl(PINO_DIN, PINO_CLK, PINO_CS, 4);

#define PINO_VRX A0
#define PINO_VRY A1
#define PINO_SW  2

#define LARGURA 32
#define ALTURA 8

int snakeX[64] = {0};
int snakeY[64] = {0};
int snakeComprimento = 3;
int direcao = 2; // 0: esquerda, 1: cima, 2: direita, 3: baixo
int ultimaDirecao = 2;
int comidaX = 10;
int comidaY = 4;

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < 4; i++) {
        lc.shutdown(i, false);
        lc.setIntensity(i, 15);
        lc.clearDisplay(i);
    }

    pinMode(PINO_SW, INPUT_PULLUP);
    reset();
}

void loop() {
    int valorVRX = analogRead(PINO_VRX);
    int valorVRY = analogRead(PINO_VRY);

    if (valorVRX < 400 && ultimaDirecao != 2 && ultimaDirecao != 0) {
        direcao = 0; // Esquerda
    }
    if (valorVRX > 600 && ultimaDirecao != 0 && ultimaDirecao != 2) {
        direcao = 2; // Direita
    }
    if (valorVRY < 400 && ultimaDirecao != 3 && ultimaDirecao != 1) {
        direcao = 1; // Cima
    }
    if (valorVRY > 600 && ultimaDirecao != 1 && ultimaDirecao != 3) {
        direcao = 3; // Baixo
    }

    ultimaDirecao = direcao;

    moverSnake();
    checarComida();
    checarColisao();

    for (int i = 0; i < 4; i++) {
        lc.clearDisplay(i);
    }

    for (int i = 0; i < snakeComprimento; i++) {
        int matrizIndice = 3 - (snakeX[i] / 8); // Inverte o índice da matriz
        int matrizX = snakeX[i] % 8;
        lc.setLed(matrizIndice, snakeY[i], matrizX, true);
    }

    int comidaIndiceMatriz = 3 - (comidaX / 8); // Inverte o índice da matriz
    int comidamatrizX = comidaX % 8;
    lc.setLed(comidaIndiceMatriz, comidaY, comidamatrizX, true);

    delay(150);
}

void moverSnake() {
    for (int i = snakeComprimento - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    if (direcao == 0) { // Esquerda
        snakeX[0] = (snakeX[0] - 1 + LARGURA) % LARGURA;
    }
    if (direcao == 1) { // Cima
        snakeY[0] = (snakeY[0] - 1 + ALTURA) % ALTURA;
    }
    if (direcao == 2) { // Direita
        snakeX[0] = (snakeX[0] + 1) % LARGURA;
    }
    if (direcao == 3) { // Baixo
        snakeY[0] = (snakeY[0] + 1) % ALTURA;
    }
}

void checarComida() {
    if (snakeX[0] == comidaX && snakeY[0] == comidaY) {
        snakeComprimento++;
        colocarComida();
    }
}

void checarColisao() {
    for (int i = 1; i < snakeComprimento; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            reset();
            break;
        }
    }
}

void colocarComida() {
    bool posicaoValida = false;

    while (!posicaoValida) {
        posicaoValida = true;
        comidaX = random(LARGURA);
        comidaY = random(ALTURA);

        for (int i = 0; i < snakeComprimento; i++) {
            if (snakeX[i] == comidaX && snakeY[i] == comidaY) {
                posicaoValida = false;
                break;
            }
        }
    }
}

void reset() {
    snakeComprimento = 3;
    direcao = 2;
    ultimaDirecao = 2;

    for (int i = 0; i < snakeComprimento; i++) {
        snakeX[i] = snakeComprimento - 1 - i;
        snakeY[i] = 0;
    }
    colocarComida();
}
