# Monitoramento de Temperatura (ESP32 + DS18B20)

Projeto de estudo em automação/IoT: o ESP32 lê temperatura com **DS18B20**, acende um LED quando passa de um limite e registra os dados em uma planilha do **Google Sheets** via **Google Apps Script**.

**Status:** em construção / testes.  
A estrutura do projeto já está organizada; validação em hardware será feita assim que os componentes estiverem disponíveis.

---

## O que já está implementado
- Leitura de temperatura (DS18B20)
- Lógica de controle do LED por limite
- Envio HTTP para endpoint (Apps Script)
- Registro no Google Sheets (data/hora, temperatura, LED)

## Próximos passos
- [ ] Ajustar intervalo para 1 hora (no momento está em 1 minuto para testes)
- [ ] Melhorar retries/erros de rede
- [ ] (Opcional) salvar localmente quando sem Wi-Fi

---

## Componentes
- ESP32 DevKit (WROOM-32)
- DS18B20
- Resistor 4.7k (pull-up)
- LED (ou LED onboard)

## Ligações (DS18B20)
- VCC → 3.3V  
- GND → GND  
- DATA → GPIO 4 (pode alterar no código)  
- Resistor 4.7k entre DATA e VCC  

---

## Como configurar e rodar (resumo)
1. Abra `esp32/monitoramento_temperatura.ino` na Arduino IDE  
2. Instale bibliotecas: `OneWire` e `DallasTemperature`  
3. Copie `esp32/secrets.example.h` para `esp32/secrets.h` e preencha SSID/senha/URL  
4. Faça upload e abra o Serial Monitor (115200)

> Obs.: o arquivo `secrets.h` não é enviado ao GitHub (está no `.gitignore`).
