
// Define o pino analógico A0, onde será lido o valor do sensor
int sensorAlogPin = 8; 

int armazenaValor = 0;  

void setup(){
  // Inicializa a função Serial, configurando sua velocidade
  Serial.begin(9600);  
}

void loop(){
// Faz a leitura da porta analogica A0 e armazena na variável armazenaValor
  armazenaValor = analogRead(sensorAlogPin);  
  Serial.print("Lendo valor... ");  //   Imprime no monitor serial
  Serial.print(armazenaValor);  // Mostra o valor lido pela porta serial
  delay(1000);  // Aguarda 1 segundo
}

