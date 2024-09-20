# ESP8266 Control for Elgato KeyLight via Alexa

This project allows you to control an **Elgato KeyLight** using an **ESP8266** and **Alexa**. The code uses the **Espalexa** library to integrate the device with Alexa, and **mDNS** to automatically discover the KeyLight's IP on the network, eliminating the need for a static IP configuration.

## Requirements

Before starting, you will need:

- An **ESP8266** (e.g., NodeMCU or Wemos D1 Mini).
- An **Elgato KeyLight** set up and connected to your Wi-Fi network.
- The Arduino IDE installed with ESP8266 support.

## Installation and Setup of the Environment

### 1. Installing the Arduino IDE

1. Download the **Arduino IDE** from: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
2. Install the IDE according to your operating system (Windows, Mac, or Linux).

### 2. Configuring the Arduino IDE for ESP8266

1. Open the Arduino IDE.
2. Go to **File > Preferences**.
3. In **Additional Boards Manager URLs**, add the following link:

```

http://arduino.esp8266.com/stable/package_esp8266com_index.json

```

4. Now, go to **Tools > Board > Boards Manager** and search for **ESP8266**. Click **Install** to install the ESP8266 board package.
5. After installation, select your ESP8266 board by going to **Tools > Board** and choose your board (e.g., **NodeMCU 1.0** or **Wemos D1 R1**).

### 3. Installing Required Libraries

1. Open the Arduino IDE and go to **Sketch > Include Library > Manage Libraries**.
2. In the search field, look for and install the following libraries:

- **Espalexa**
- **ESP8266HTTPClient**
- **ESP8266mDNS**

### 4. Uploading the Code

1. Download or clone this repository with the provided code.
2. Open the `.ino` file (Arduino code) in the Arduino IDE.
3. In the code, configure the following variables with your network details:

```cpp
const char* wifi_ssid = "YOUR WIFI";
const char* wifi_password = "YOUR PASSWORD";
```

4. Connect the ESP8266 to your computer.
5. Select the correct port under **Tools > Port**.
6. Click **Upload** to flash the code to the ESP8266.

### 5. Elgato KeyLight Setup

1. Ensure your **Elgato KeyLight** is correctly set up and connected to the same Wi-Fi network.
2. The code will automatically discover the **KeyLight** using mDNS, based on the service `"_elg._tcp.local"`.

### 6. Alexa Integration

1. Open the Alexa app on your mobile device.
2. Go to **Devices > Lights > Add**.
3. Alexa should find the ESP8266 as a new light called "Elgato Keylight". Just follow the instructions in the app to complete the setup.

## How it Works

- The ESP8266 controls the KeyLight by sending HTTP commands to the device, adjusting brightness and on/off status.
- **mDNS** allows the ESP8266 to automatically discover the KeyLight's IP address on the local network.
- With the **Espalexa** integration, the light can be controlled directly through Alexa.

## Contributing

Contributions are welcome! Feel free to open **Issues** or submit **Pull Requests** for any improvements to the code.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

# Controle da Elgato KeyLight com ESP8266 via Alexa

Este projeto permite controlar uma **Elgato KeyLight** usando um **ESP8266** e a **Alexa**. O código utiliza a biblioteca **Espalexa** para integrar o dispositivo à Alexa e o **mDNS** para descoberta automática do IP da KeyLight na rede, eliminando a necessidade de configurar um IP fixo.

## Pré-requisitos

Antes de começar, você precisará:

- Um **ESP8266** (por exemplo, NodeMCU ou Wemos D1 Mini).
- A **KeyLight** da Elgato configurada e conectada à sua rede Wi-Fi.
- A IDE do Arduino instalada com suporte ao ESP8266.

## Instalação e Configuração do Ambiente

### 1. Instalando a IDE do Arduino

1. Baixe a **IDE do Arduino** em: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
2. Instale a IDE seguindo as instruções específicas do seu sistema operacional (Windows, Mac ou Linux).

### 2. Configurando a IDE do Arduino para ESP8266

1. Abra a IDE do Arduino.
2. Vá em **Arquivo > Preferências**.
3. Em **URLs adicionais para gerenciadores de placas**, adicione o seguinte link:

   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```

4. Agora, vá em **Ferramentas > Placa > Gerenciador de Placas** e procure por **ESP8266**. Clique em **Instalar** para instalar o pacote de placas ESP8266.
5. Depois da instalação, selecione sua placa ESP8266 correta indo em **Ferramentas > Placa** e escolha a sua (por exemplo, **NodeMCU 1.0** ou **Wemos D1 R1**).

### 3. Instalando as Bibliotecas Necessárias

1. Abra a IDE do Arduino e vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
2. No campo de busca, procure e instale as seguintes bibliotecas:
   - **Espalexa**
   - **ESP8266HTTPClient**
   - **ESP8266mDNS**

### 4. Carregando o Código

1. Baixe ou clone este repositório com o código fornecido.
2. Abra o arquivo `.ino` (código do Arduino) na IDE do Arduino.
3. No arquivo de código, configure as seguintes variáveis de acordo com sua rede:

   ```cpp
   const char* wifi_ssid = "YOUR WIFI";
   const char* wifi_password = "YOUR PASSWORD";
   ```

4. Conecte o ESP8266 ao seu computador.
5. Selecione a porta correta em **Ferramentas > Porta**.
6. Clique em **Upload** para carregar o código no ESP8266.

### 5. Configuração do KeyLight

1. Certifique-se de que seu **KeyLight** da Elgato esteja configurado corretamente e conectado à mesma rede Wi-Fi.
2. O código fará a descoberta automática do **KeyLight** usando o mDNS, baseado no serviço `"_elg._tcp.local"`.

### 6. Uso com a Alexa

1. Abra o app da Alexa no seu dispositivo móvel.
2. Vá em **Dispositivos > Luzes > Adicionar**.
3. A Alexa deverá encontrar o ESP8266 como uma nova luz chamada "Elgato Keylight". Basta seguir as instruções no app para completar a configuração.

## Funcionamento

- O ESP8266 controla a KeyLight enviando comandos HTTP para o dispositivo baseado no ajuste de brilho e estado (ligado/desligado).
- O **mDNS** permite que o ESP8266 descubra automaticamente o IP da KeyLight na rede local.
- Com a integração via **Espalexa**, a luz pode ser controlada diretamente pela Alexa.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir **Issues** ou enviar **Pull Requests** para melhorias no código.

## Licença

Este projeto está sob a licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.
