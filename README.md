# MentorBit-DetectorLluvia

## Descripción

Esta librería está específicamente diseñada para ser utilizada junto con el módulo **MentorBit Detector de Lluvia**. 

El **MentorBit Detector de Lluvia** es un sensor utilizado para detectar la presencia de lluvia mediante un umbral digital y una salida analógica. Esta librería permite interactuar fácilmente con el sensor y obtener lecturas de su estado.

Puedes encontrar nuestro Módulo MentorBit y mucho más material de electrónica y robótica en nuestra tienda oficial:  [https://digitalcodesign.com/shop](https://digitalcodesign.com/shop)

## Métodos Principales

- `MentorBitDetectorLluvia` → Constructor de la clase.
- `obtenerLecturaDigital` → Obtiene un valor de **true** o **false** dependiendo de la presencia de lluvia. El umbral es ajustable con un potenciómetro.
- `obtenerLecturaAnalogica` → Devuelve un valor analógico de 2 bytes que representa la intensidad de la lluvia detectada.

## Constructor

```cpp
MentorBitDetectorLluvia miModuloDetector(digital_pin, analog_pin);
```

Donde "digital_pin" y "analog_pin" son los puertos donde están conectadas ambas salidas del sensor que entregan las señales digital y analógica, respectivamente.

### Parámetros

- `detector_pin`: Pin digital donde se conecta el sensor de lluvia (por defecto es 0).
- `analog_detector_pin`: Pin analógico donde se conecta el sensor (por defecto es 0).

## Métodos

### `bool obtenerLecturaDigital()`

Devuelve un valor booleano **true** o **false** dependiendo de si hay lluvia o no, basado en un umbral digital que se puede ajustar.

#### Ejemplo de uso

```cpp
bool lecturaDigital = detector.obtenerLecturaDigital();
```

### `uint16_t obtenerLecturaAnalogica()`

Devuelve un valor analógico de 2 bytes que representa la intensidad de la lluvia.

#### Ejemplo de uso

```cpp
uint16_t lecturaAnalogica = detector.obtenerLecturaAnalogica();
```
