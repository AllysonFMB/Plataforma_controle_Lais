const int led1 = 2; //led subida
const int led2 = 3; //led descida
const int led3 = 4; //led peso
const int led4 = 5; //led manutencao

const int MR1 = 8; //rele acionamento geral
const int MR2 = 7; //rele de subida
const int MR3 = 6; //rele de descida

float Sp = 0.0; //Sensor de peso
int Cont = 0; //Contador de uso para manutencao

int Sm1 = 0; //sensor magnetico reed switch inferior
int Sm2 = 0; //sensor magnetico reed switch superior
int Botao = 0; //botao de acionamento subida/descida

void moveup();
void movedown();

void setup() {
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(9, INPUT); //sensor magnetico reed switch inferior
  pinMode(10, INPUT); //sensor magnetico reed switch superior
  
  pinMode(11, INPUT); //botao de acionamento subida/descida

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(MR3, OUTPUT);

  //Modulo rele inicialmente desligado
  digitalWrite(MR1, LOW); 
  digitalWrite(MR2, LOW);
  digitalWrite(MR3, LOW);
}

void loop() {
  
    Sp = 300/1024 * analogRead(A0); //leitura do sensor de peso 300kg 

    if (Sp <= 250){
        if (Cont <= 100){
            Sm1 = digitalRead(9);
            Sm2 = digitalRead(10);
            Botao = digitalRead(11);
            
            if (Botao == 1 && Sm1 == 1){
                moveup();
                Cont = Cont + 1;
            }
  
            if (Botao == 1 && Sm2 == 1){
                movedown();
                Cont = Cont + 1;
            }
        }
        else{
            //aciona o led de manutencao e desliga os reles
            digitalWrite(led4, HIGH);
            digitalWrite(MR1, LOW); 
            digitalWrite(MR2, LOW);
            digitalWrite(MR3, LOW);
        }
    }
    else {
        //aciona o led de sobrepeso e desliga os reles
        digitalWrite(led3, HIGH);
        digitalWrite(MR1, LOW); 
        digitalWrite(MR2, LOW);
        digitalWrite(MR3, LOW);
    }
}

void moveup(){
    Sm2 = digitalRead(10);

    while (Sm2 == 0){
        //aciona os reles para a plataforma subir e liga o led indicativo de subida
        digitalWrite(MR1, HIGH); 
        digitalWrite(MR2, HIGH);
        digitalWrite(led1, HIGH);
        Sm2 = digitalRead(10); //Atualiza o valor de Sm2
    }

    digitalWrite(MR1, LOW); 
    digitalWrite(MR2, LOW);
    digitalWrite(led1, LOW);
}

void movedown(){
    Sm1 = digitalRead(9);

    while (Sm1 == 0){
        //aciona os reles para a plataforma subir e liga o led indicativo de descida
        digitalWrite(MR1, HIGH); 
        digitalWrite(MR3, HIGH);
        digitalWrite(led2, HIGH);
        Sm1 = digitalRead(9); //Atualiza o valor de Sm1
    }

    digitalWrite(MR1, LOW); 
    digitalWrite(MR3, LOW);
    digitalWrite(led2, LOW);
}
