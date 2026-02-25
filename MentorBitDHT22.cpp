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
    Version: 1.1.0
    Fecha de creación: Septiembre de 2024
    Fecha de version: Febrero de 2026
    Repositorio: https://github.com/DigitalCodesign/MentorBit-DHT22
    Descripcion: 
        Esta libreria esta especificamente diseñada para ser utilizada junto con 
        el modulo MentorBit DHT22. En esta versión se ha eliminado la dependencia 
        de librerías externas, implementando el protocolo nativo 
        "One-Wire". Además, incluye un sistema de caché de lecturas (2 segundos) 
        para evitar cuelgues o errores al solicitar temperatura y humedad de forma 
        consecutiva, respetando los tiempos de recuperación del hardware.
        
    Metodos principales:
        MentorBitDHT22(uint8_t pin) -> Constructor de la clase. Define el pin de conexión del sensor.
        obtenerTemperatura() -> Devuelve la temperatura en grados Celsius (float).
        obtenerHumedad() -> Devuelve el porcentaje de humedad relativa (float).
        configPort(const Port& port) -> Reconfigura el puerto asociado al sensor.
*/

#include "MentorBitDHT22.h"

/**
 * @brief Constructor de la clase.
 */
MentorBitDHT22::MentorBitDHT22(uint8_t pin)
{

    _pin = pin;
    _port.gpios[1] = pin;
    _ultima_temperatura = -999.0;
    _ultima_humedad = -999.0;
    _ultimo_tiempo_lectura = 0;
    _reiniciarDHT();

}

/**
 * @brief Método para obtener le última Temperatura leída por el sensor en ºC.
 * @return Valor de la última temperatura medida.
 */
float MentorBitDHT22::obtenerTemperatura()
{

    _leerSensor();
    return _ultima_temperatura;

}

/**
 * @brief Método para obtener le última Humedad relativa leída por el sensor en %.
 * @return Valor de la última humedad medida.
 */
float MentorBitDHT22::obtenerHumedad()
{

    _leerSensor();
    return _ultima_humedad;

}

/**
 * @brief Método interno para gestión automática de GPIOs al utilizar Puertos MentorBit.
 */
void MentorBitDHT22::configPort(const Port& port) {

    _port.type = port.type;
    _port.location = port.location;
    _port.gpios[0] = port.gpios[0];
    _port.gpios[1] = port.gpios[1];
    _pin = _port.gpios[1];
    _reiniciarDHT();

}

/**
 * @brief Método interno para reiniciar el sensor y las lecturas.
 */
void MentorBitDHT22::_reiniciarDHT()
{

    pinMode(_pin, INPUT_PULLUP);
    _ultimo_tiempo_lectura = 0;

}

/**
 * @brief Método interno para tomar mediciones del sensor.
 * @return True si la lectura fue correcta o en muy poco tiempo desde la última, False si hubo algún error.
 */
bool MentorBitDHT22::_leerSensor()
{

    // Si ha pasado poco tiempo desde la última lectura, devolvemos True directamente
    if (millis() - _ultimo_tiempo_lectura < 2000 && _ultimo_tiempo_lectura != 0) return true;
    // Preparamos petición para el sensor
    uint8_t datos[5] = { 0, 0, 0, 0, 0 };
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(30);
    pinMode(_pin, INPUT_PULLUP);
    // Leemos la respuesta, deshabilitando interrupciones para no perder sincronía
    noInterrupts();
    uint16_t timeout = 10000;
    while(digitalRead(_pin) == HIGH) { if (--timeout == 0) { interrupts(); return false; } }
    timeout = 10000;
    while(digitalRead(_pin) == LOW) { if (--timeout == 0) { interrupts(); return false; } }
    timeout = 10000;
    while(digitalRead(_pin) == HIGH) { if (--timeout == 0) { interrupts(); return false; } }

    for (int i = 0; i < 40; i++) {
        timeout = 10000;
        while(digitalRead(_pin) == LOW) { if (--timeout == 0) { interrupts(); return false; } }
        
        uint32_t t = micros();
        timeout = 10000;
        while(digitalRead(_pin) == HIGH) { if (--timeout == 0) { interrupts(); return false; } }
        
        if ((micros() - t) > 40) {
            datos[i / 8] |= (1 << (7 - (i % 8)));
        }
    }
    interrupts();
    // Verificamos con el Checksum
    if (datos[4] == ((datos[0] + datos[1] + datos[2] + datos[3]) & 0xFF)) {
        
        // El DHT22 usa 16 bits para humedad
        _ultimaHumedad = ((word)datos[0] << 8 | datos[1]) * 0.1;
        
        // El DHT22 usa 16 bits para temperatura (el bit 15 indica si es negativa)
        float temp = (((word)(datos[2] & 0x7F)) << 8 | datos[3]) * 0.1;
        if (datos[2] & 0x80) {
            temp *= -1.0;
        }
        _ultimaTemperatura = temp;
        
        _ultimoTiempoLectura = millis();
        return true;
    }
    // Si llegamos aquí, hubo error en el Checksum
    return false;

}
