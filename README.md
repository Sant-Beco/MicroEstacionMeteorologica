# ✨ Micro Estación Climática IoT ✨

Bienvenido a la **Micro Estación Climática IoT**, una solución inteligente para la monitorización en tiempo real de datos climáticos. Este proyecto está diseñado para integrarse con **ThingSpeak** y complementarse con datos de **OpenWeatherMap**, facilitando el acceso a información meteorológica desde cualquier parte del mundo.

---

## 🌱 Características Principales

- **Monitoreo en Tiempo Real**: Obtiene datos de temperatura, humedad, presión atmosférica y luminosidad mediante sensores.
- **Integración con ThingSpeak**: Los datos recolectados son enviados a **ThingSpeak**, donde se pueden visualizar en tiempo real mediante gráficas interactivas.
- **Compatibilidad con OpenWeatherMap**: Se complementan los datos locales con predicciones meteorológicas externas.
- **Fácil Configuración**: Simplemente conecta el hardware, carga el código en tu microcontrolador y comienza a recibir datos.

---

## 🔧 Requisitos del Proyecto

### 💪 Hardware
- **Microcontrolador**: ESP32 Dev Module (recomendado) o ESP8266.
- **Sensores**:
  - **DHT22/DHT11**: Medición de temperatura y humedad.
  - **BMP180**: Presión atmosférica y altitud.
  - **BH1750**: Medición de luz ambiental.
- **Conexión Wi-Fi** estable.
- **Cables y protoboard** para conexiones.

### 💻 Software
- **Arduino IDE** ([Descargar](https://downloads.arduino.cc/arduino-1.8.19-windows.exe)).
- **Bibliotecas necesarias**:
  - `DHT.h`, `Adafruit BMP085.h`, `BH1750.h`, `WiFi.h`, `HTTPClient.h`.
  - `ArduinoJson`, `Adafruit Unified Sensor`, `Adafruit SSD1306`.
- **Controladores USB a Serie CH340** ([Descargar](https://www.wch-ic.com/search?q=CH341SER&t=downloads)).
- **Cuentas en OpenWeatherMap y ThingSpeak** para obtener claves API.

---

## 🛠️ Instalación y Configuración

### 1. Configurar el Entorno de Desarrollo
1. Instalar **Arduino IDE**.
2. Agregar el soporte para **ESP32** en Arduino IDE:
   - Ir a *Archivo* > *Preferencias* y agregar:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Luego, en *Herramientas* > *Placas* > *Gestor de Tarjetas*, buscar **ESP32** e instalarlo.
3. Instalar las bibliotecas mencionadas anteriormente en el *Gestor de Bibliotecas* de Arduino IDE.

### 2. Configurar el Hardware
1. Conectar el ESP32 a la computadora.
2. Instalar el controlador **CH340** si el dispositivo no es reconocido.
3. Verificar que el ESP32 sea detectado en *Herramientas* > *Puerto*.

### 3. Configurar ThingSpeak y OpenWeatherMap
1. **ThingSpeak**: Crear una cuenta y un canal ([Crear canal](https://thingspeak.com/channels/new)) para recibir datos.
2. **OpenWeatherMap**: Crear una cuenta y obtener una clave API ([Obtener API](https://home.openweathermap.org/api_keys)).
3. Configurar las credenciales Wi-Fi y las claves API en el código fuente (`sketch-project-1-openweathermap.ino` y `sketch_project_2_ThinkSpeak.ino`).

### 4. Cargar el Código en el ESP32
1. Abrir el archivo `.ino` correspondiente en Arduino IDE.
2. Modificar los datos de Wi-Fi y claves API.
3. Seleccionar la placa *ESP32 Dev Module* en *Herramientas* > *Placas*.
4. Cargar el código y abrir el Monitor Serie para verificar el funcionamiento.

---

## 🔄 Pruebas y Validación
- **Conectividad Wi-Fi**: Verificar que el ESP32 se conecte correctamente.
- **Sensores**: Validar que cada sensor muestre datos correctos.
- **Enlace con ThingSpeak**: Confirmar la transmisión de datos y visualización en gráficas.
- **Integración con OpenWeatherMap**: Comprobar que los datos meteorológicos externos se visualicen correctamente.
- **Pantalla OLED**: Si se utiliza, verificar la correcta visualización de datos en la pantalla.

---

## 🚀 Solución de Problemas
- **No se conecta a Wi-Fi**: Revisar credenciales y acercar el ESP32 al router.
- **No aparecen datos en ThingSpeak**: Verificar la API Key y la configuración del canal.
- **La pantalla OLED no muestra datos**: Revisar conexiones y dirección I2C.
- **El ESP32 no es reconocido en Arduino IDE**: Instalar o reinstalar el driver CH340 y seleccionar el puerto correcto.
- **El código no se carga**: Asegurarse de que el ESP32 esté en modo de carga (presionar el botón *BOOT* al conectar el dispositivo).

---

## 💌 Contacto y Soporte
Si tienes dudas o sugerencias, puedes escribir a:
- **Correo**: [microestacionmeteorologica@gmail.com](mailto:microestacionmeteorologica@gmail.com)

📊 Proyecto desarrollado por **Santiago Bedoya Corrales**.

---

## 💪🏻 Contribuir
Si deseas mejorar el proyecto, síguelo en GitHub y envía tus pull requests con mejoras o correcciones.

---



