/*


            ██████╗    ██╗    ██████╗    ██╗   ████████╗    █████╗    ██╗               
            ██╔══██╗   ██║   ██╔════╝    ██║   ╚══██╔══╝   ██╔══██╗   ██║               
            ██║  ██║   ██║   ██║  ███╗   ██║      ██║      ███████║   ██║               
            ██║  ██║   ██║   ██║   ██║   ██║      ██║      ██╔══██║   ██║               
            ██████╔╝   ██║   ╚██████╔╝   ██║      ██║      ██║  ██║   ███████╗          
            ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝      ╚═╝  ╚═╝   ╚══════╝          
                                                                                        
     ██████╗    ██████╗    ██████╗    ███████╗   ███████╗   ██╗    ██████╗    ███╗   ██╗
    ██╔════╝   ██╔═══██╗   ██╔══██╗   ██╔════╝   ██╔════╝   ██║   ██╔════╝    ████╗  ██║
    ██║        ██║   ██║   ██║  ██║   █████╗     ███████╗   ██║   ██║  ███╗   ██╔██╗ ██║
    ██║        ██║   ██║   ██║  ██║   ██╔══╝     ╚════██║   ██║   ██║   ██║   ██║╚██╗██║
    ╚██████╗   ╚██████╔╝   ██████╔╝   ███████╗   ███████║   ██║   ╚██████╔╝   ██║ ╚████║
     ╚═════╝    ╚═════╝    ╚═════╝    ╚══════╝   ╚══════╝   ╚═╝    ╚═════╝    ╚═╝  ╚═══╝ 
        

    Autor: Digital Codesign
    Version: 1.0.0
    Fecha de creación: Septiembre de 2024
    Fecha de version: Septiembre de 2024
    Repositorio: https://github.com/DigitalCodesign/MentorBit-DHT22
    Descripcion: 
        Este sketch muestra un ejemplo de como obtener los valores de humedad y temperatura
        del sensor DHT22 y mostrarlos por pantalla

*/

// Se incluye la libreria MentorBitDHT22
#include <MentorBitDHT22.h>

// Se define el pin al cual se esta conectando el sensor DHT22
#define DHT22_PIN A4

// Se crea el objeto dht22 y se le asigna el pin al que esta conectado
MentorBitDHT22 dht22(DHT22_PIN);

void setup() {

    // Se inicializa el monitor Serial para mostrar las lecturas por pantalla
    Serial.begin(9600);
}

void loop() {

    // Se imprime el valor de la temperatura por pantalla
    Serial.print(" Valor de temperatura: ");
    Serial.print(dht22.obtenerTemperatura());
    Serial.println(" ºC");

    // Se imprime el valor de la humedad por pantalla
    Serial.print(" Valor de humedad: ");
    Serial.print(dht22.obtenerHumedad());
    Serial.println(" %");
    Serial.println(" ");
    // Se coloca un pequeño delay para evitar llenar muy rapido el monitor serial
    delay(1000);
}