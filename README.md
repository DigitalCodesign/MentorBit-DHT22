
# MentorBit-DHT22

## Descripción

Esta librería está construida por Digital Codesign para interactuar con el **Módulo DHT22**, diseñado principalmente para el kit educacional **MentorBit**. El **DHT22** es un sensor digital de temperatura y humedad, ideal para medir las condiciones ambientales.

Puedes encontrar nuestro **MentorBit** y mucho más material de electrónica y robótica en nuestra tienda oficial: [https://digitalcodesign.com/shop](https://digitalcodesign.com/shop)

## Modo de empleo

Una vez que tengamos la librería instalada desde el Arduino IDE, necesitamos incluir la librería con la siguiente línea:

```cpp
#include <MentorBitDHT22.h>
```

### Constructor

Una vez incluida la librería, usamos el constructor para crear el objeto del módulo **DHT22**, y definimos el pin al que está conectado el sensor:

```cpp
MentorBitDHT22 dht22(PIN_SENSOR);
```

Donde `PIN_SENSOR` es el pin al que está conectado el sensor **DHT22**.

### Uso

Con el objeto `dht22` definido, podemos obtener la lectura de la temperatura y la humedad utilizando las funciones `obtenerTemperatura()` y `obtenerHumedad()`:

#### Obtener Temperatura

```cpp
float temperatura = dht22.obtenerTemperatura();
```

Esta función devuelve el valor de la temperatura en grados Celsius.

#### Obtener Humedad

```cpp
float humedad = dht22.obtenerHumedad();
```

Esta función devuelve el valor de la humedad en porcentaje.

### Configuración de puertos

Si deseas configurar puertos personalizados, puedes usar la función `configPort()` para asignar los pines y configuraciones de puertos que necesitas:

```cpp
Port port;
port.gpios[0] = PIN_SENSOR;  // Pin de conexión
dht22.configPort(port);
```

Donde `port` es un objeto de tipo `Port` que contiene las configuraciones necesarias.

## Atributos

- `PIN_SENSOR`: Define el pin al que está conectado el sensor **DHT22**.

