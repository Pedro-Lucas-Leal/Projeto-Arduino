#include <ESP8266WiFi.h>

// Define o nome e senha da rede Wi-Fi
const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

// Define o endereço IP e porta do servidor
IPAdress serverIp(192, 168, 1, 100); // Substitua pelo endereço do seu servidor
const int serverPort = 80; // Porta padrão para conexões HTTP

// Define os pinos dos relés
const int pinoLampada = 3;
const int pinoForno = 4;

// Define o estado atual dos relés
bool estadoLampada = false;
bool estadoForno = false;

// Cria o objeto WiFiClient para fazer a conexão com o servidor
WiFiClient cliente;

void setup() {
  // Inicializa os relés como saídas
  pinMode(pinoLampada, OUTPUT);
  pinMode(pinoForno, OUTPUT);

  // Conecta à rede Wi-Fi
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("Conectando-se à rede Wi-Fi ");
  Serial.print(ssid);
  Serial.println("...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado à rede Wi-Fi");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Se a conexão com o servidor foi estabelecida
  if (cliente.connected()) {
    // Envia uma solicitação HTTP para o servidor para verificar o estado da lâmpada
    cliente.println("GET /lampada HTTP/1.1");
    cliente.println("Host: " + serverIp.toString());
    cliente.println("Connection: close");
    cliente.println();

    // Aguarda a resposta do servidor
    while (cliente.connected()) {
      if (cliente.available()) {
        // Lê a resposta do servidor
        String resposta = cliente.readStringUntil('\r');
        Serial.println(resposta);

        // Verifica se a resposta contém a palavra "ON"
        if (resposta.indexOf("ON") != -1) {
          estadoLampada = true;
        }

        // Verifica se a resposta contém a palavra "OFF"
        if (resposta.indexOf("OFF") != -1) {
          estadoLampada = false;
        }

        // Atualiza o estado da lâmpada
        digitalWrite(pinoLampada, estadoLampada);
      }
    }

    // Envia uma solicitação HTTP para o servidor para verificar o estado do forno
    cliente.println("GET /forno HTTP/1.1");
    cliente.println("Host: " + serverIp.toString());
    cliente.println("Connection: close");
    cliente.println();

    // Aguarda a resposta do servidor
    while (cliente.connected()) {
      if (cliente.available()) {
        // Lê a resposta do servidor
        String resposta = cliente.readStringUntil('\r');
        Serial.println(resposta);

        // Verifica se a resposta contém a palavra "ON"
        if (resposta.indexOf("ON") != -1) {
          estadoForno = true;
        }

        // Verifica se a resposta contém a palavra "OFF"
        if (resposta.indexOf("OFF") != -1) {
          estadoForno = false;
       
	  // Atualiza o estado do forno
	  digitalWrite(pinoForno, estadoForno);
	  }
	  }
	  } else {
	  // Se a conexão com o servidor foi perdida, tenta se reconectar
	  Serial.println("Conexão perdida. Tentando reconectar...");
	  cliente.connect(serverIp, serverPort);
	  }

	// Aguarda por um curto período antes de verificar novamente o estado dos relés
	delay(1000);
	}
