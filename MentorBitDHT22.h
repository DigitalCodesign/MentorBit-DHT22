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

#ifndef MentorBitDHT22_h
#define MentorBitDHT22_h

#include <Arduino.h>
#include <MentorPort.h>

class MentorBitDHT22 : public MentorPort
{

    public: 

        MentorBitDHT22(uint8_t pin = 0);

        float obtenerTemperatura();
        float obtenerHumedad();
        void configPort(const Port& port) override;

    private:

        Port _port;
        uint8_t _pin;

        float _ultima_temperatura;
        float _ultima_humedad;
        uint32_t _ultimo_tiempo_lectura;

        void _reiniciarDHT();
        bool _leerSensor();

};

#endif