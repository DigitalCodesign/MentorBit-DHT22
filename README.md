# MentorBitDHT22

Librería para la lectura de temperatura y humedad utilizando el sensor DHT22 en módulos compatibles con MentorBit.

## Descripción

La librería `MentorBitDHT22` facilita la lectura de datos de temperatura y humedad relativa desde el sensor DHT22 (también conocido como AM2302) en módulos compatibles con MentorBit. Ofrece un rango de medición más amplio y una mayor precisión que el DHT11, siendo ideal para aplicaciones de monitoreo ambiental, estaciones meteorológicas y proyectos que requieren mediciones precisas de temperatura y humedad.

**Nota:** La librería depende de la librería `DHT.h`.

## Modo de Empleo

1.  **Instalación:**
    * Abre el IDE compatible con MentorBit.
    * Ve a "Herramientas" -> "Gestionar librerías..."
    * Busca "MentorBitDHT22" e instálala.
    * **Nota:** Asegúrate de que la librería `DHT.h` esté instalada.

2.  **Ejemplo básico:**

    ```c++
    #include <MentorBitDHT22.h>

    MentorBitDHT22 dht(2); // Sensor DHT22 conectado al pin 2

    void setup() {
      Serial.begin(9600);
      Serial.println("Sensor DHT22 inicializado.");
    }

    void loop() {
      float temperatura = dht.obtenerTemperatura();
      float humedad = dht.obtenerHumedad();

      if (isnan(temperatura) || isnan(humedad)) {
        Serial.println("Error al leer el sensor DHT22.");
        delay(2000); // Espera antes de reintentar la lectura
        return;
      }

      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");

      Serial.print("Humedad: ");
      Serial.print(humedad);
      Serial.println(" %");

      delay(2000);
    }
    ```

## Constructor y Métodos Públicos

### Constructor

* `MentorBitDHT22(uint8_t pin = 0)`: Crea un objeto `MentorBitDHT22`.
    * `pin`: Número de pin al que está conectado el sensor DHT22. Si no se especifica, se asume que no está conectado a ningún pin inicialmente.

### Métodos

* `float obtenerTemperatura()`: Lee la temperatura en grados Celsius.
* `float obtenerHumedad()`: Lee la humedad relativa en porcentaje.

### Métodos Privados

* `void _reiniciarDHT()`: Re-inicializa el sensor DHT22.
