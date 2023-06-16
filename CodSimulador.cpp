const int pinoBotaoLampada = 3;   // Pino do botão da lâmpada
const int pinoBotaoForno = 4;     // Pino do botão do forno
const int pinoBotaoAmbos = 7;     // Pino do botão para ligar/desligar ambos os relés

const int pinoLampada = 5;        // Pino de controle da lâmpada
const int pinoForno = 6;          // Pino de controle do forno

bool estadoLampada = false;       // Estado atual da lâmpada (ligada/desligada)
bool estadoForno = false;         // Estado atual do forno (ligado/desligado)
bool estadoAmbos = false;         // Estado atual de ambos os relés (ligados/desligados)

bool ultimoEstadoBotaoLampada = LOW;    // Último estado do botão da lâmpada
bool ultimoEstadoBotaoForno = LOW;      // Último estado do botão do forno
bool ultimoEstadoBotaoAmbos = LOW;      // Último estado do botão para ambos os relés

void setup() {
  pinMode(pinoBotaoLampada, INPUT);     // Configura o pino do botão da lâmpada como entrada
  pinMode(pinoBotaoForno, INPUT);       // Configura o pino do botão do forno como entrada
  pinMode(pinoBotaoAmbos, INPUT);       // Configura o pino do botão para ambos os relés como entrada

  pinMode(pinoLampada, OUTPUT);         // Configura o pino de controle da lâmpada como saída
  pinMode(pinoForno, OUTPUT);           // Configura o pino de controle do forno como saída

  Serial.begin(9600);
  Serial.println("Sistema inicializado.");
}

void loop() {
  int estadoBotaoLampada = digitalRead(pinoBotaoLampada);     // Lê o estado atual do botão da lâmpada
  if (estadoBotaoLampada != ultimoEstadoBotaoLampada) {
    if (estadoBotaoLampada == HIGH) {
      estadoLampada = !estadoLampada;                         // Inverte o estado da lâmpada
      digitalWrite(pinoLampada, !estadoLampada);               // Atualiza o estado da lâmpada
      Serial.print("Lâmpada: ");
      Serial.println(estadoLampada ? "Ligada" : "Desligada");  // Imprime o estado da lâmpada
    }
  }
  ultimoEstadoBotaoLampada = estadoBotaoLampada;

  int estadoBotaoForno = digitalRead(pinoBotaoForno);         // Lê o estado atual do botão do forno
if (estadoBotaoForno != ultimoEstadoBotaoForno) {
  if (estadoBotaoForno == HIGH) {
    estadoForno = !estadoForno;                             // Inverte o estado do forno
    digitalWrite(pinoForno, !estadoForno);                   // Atualiza o estado do forno
    Serial.print("Forno: ");
    Serial.println(estadoForno ? "Ligado" : "Desligado");    // Imprime o estado do forno
  }
}
ultimoEstadoBotaoForno = estadoBotaoForno;

int estadoBotaoAmbos = digitalRead(pinoBotaoAmbos);         // Lê o estado atual do botão para ambos os relés
if (estadoBotaoAmbos != ultimoEstadoBotaoAmbos) {
  if (estadoBotaoAmbos == HIGH) {
    estadoAmbos = !estadoAmbos;                             // Inverte o estado de ambos os relés
    digitalWrite(pinoLampada, estadoAmbos);                 // Atualiza o estado da lâmpada
    digitalWrite(pinoForno, estadoAmbos);                   // Atualiza o estado do forno
    Serial.print("Ambos: ");
    Serial.println(estadoAmbos ? "Ligados" : "Desligados");  // Imprime o estado de ambos os relés
  }
}
ultimoEstadoBotaoAmbos = estadoBotaoAmbos;
}
