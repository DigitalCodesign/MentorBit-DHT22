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
        Esta libreria esta especificamente diseñada para ser utilizada junto con 
        el modulo MentorBit DHT22
    Metodos principales:
        MentorBitDHT22 -> constructor de la clase
        obtenerTemperatura -> Obtiene y devuelve el valor de temperatura leido por el sensor DHT22 (float)
        obtenerHumedad -> Obtiene y devuelve el valor de humedad leido por el sensor DHT22 (float)

*/

#include "MentorBitDHT22.h"

MentorBitDHT22::MentorBitDHT22(uint8_t pin = 0):myDHT(pin, DHT22){
    myDHT.begin();
    _port.gpios[1] = pin;
}

float MentorBitDHT22::obtenerTemperatura(){
    float valor;
    valor = myDHT.readTemperature();
    return valor;
}

float MentorBitDHT22::obtenerHumedad(){
    float valor;
    valor = myDHT.readHumidity();
    return valor;
}

void MentorBitDHT22::configPort(const Port& port) {

    _port.type = port.type;
    _port.location = port.location;
    _port.gpios[0] = port.gpios[0];
    _port.gpios[1] = port.gpios[1];

    _reiniciarDHT();    

}

void MentorBitDHT11::_reiniciarDHT()
{

    myDHT = DHT(_port.gpios[1], DHT11);
    myDHT.begin();

}
