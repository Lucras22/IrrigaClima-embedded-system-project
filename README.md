## 🌱 Introdução

Este projeto visa o desenvolvimento de uma **estação meteorológica automatizada** utilizando sensores conectados ao microcontrolador **ESP32 com conectividade Wi-Fi**. A proposta é fornecer **dados meteorológicos e ambientais em tempo real**, auxiliando na tomada de decisões para a agricultura familiar e promovendo o uso eficiente de recursos naturais.

O sistema monitora variáveis como **umidade do ar, umidade do solo, temperatura ambiente, pressão atmosférica, índice de radiação UV, luminosidade e qualidade do ar**. Além disso, integra um **sistema automatizado de irrigação**, que otimiza o uso da água com base nos parâmetros coletados. A estação é alimentada por **baterias recarregáveis de 3.7V**, garantindo portabilidade e autonomia em regiões com acesso limitado à energia elétrica.

---

## ⚙️ Funcionalidades Propostas

- **Monitoramento da umidade do ar**  
  Usando o sensor **BME280**, é possível obter a umidade relativa do ar, fornecendo informações essenciais para o manejo de cultivos.

- **Medição da umidade do solo**  
  O sensor **HL69** monitora a umidade da terra, possibilitando decisões mais assertivas sobre a necessidade de irrigação.

- **Registro da temperatura ambiente**  
  O sensor **BME280** também coleta a temperatura do ambiente, importante para o controle climático e manejo agrícola.

- **Aferição da pressão atmosférica**  
  Com o **BME280**, o sistema monitora a pressão atmosférica, útil para prever mudanças climáticas.

- **Medição do nível de radiação UV (ultravioleta)**  
  O sensor **GUVA-S12SD** mede a radiação UV, ajudando a proteger plantas sensíveis à exposição solar excessiva.

- **Detecção de luminosidade**  
  O sensor de luminosidade **LDR** detecta a intensidade da luz ambiente, permitindo ajustes nos ciclos de irrigação e contribuindo para o controle de energia.

- **Monitoramento da qualidade do ar**  
  O sensor **MQ-135** detecta gases nocivos e presença de fumaça, contribuindo para a segurança ambiental e a saúde dos agricultores.

- **Detecção de chuva**  
  O sensor **YL83** detecta a presença de chuva, desativando automaticamente o sistema de irrigação quando necessário.

- **Automação da irrigação**  
  A irrigação é acionada automaticamente com base na umidade do solo, na luminosidade e nas condições meteorológicas. A bomba é ativada ou desativada por meio de um relé, garantindo o uso eficiente da água.

- **Sistema de alimentação portátil**  
  A estação é alimentada por **duas baterias 3.7V conectadas em série**, recarregáveis via **módulo carregador com proteção**, e com **regulador de tensão** para fornecer energia estável ao sistema.

---

## 🌾 Benefícios para a Agricultura Familiar

- **Decisões mais informadas**  
  Os dados fornecidos em tempo real permitem que famílias agrícolas ajustem suas práticas de manejo de forma precisa, otimizando o uso de recursos naturais e melhorando a produtividade.

- **Irrigação eficiente**  
  O sistema automatizado reduz o desperdício de água ao ativar a irrigação apenas quando necessário, promovendo uma gestão sustentável da água — recurso escasso em muitas regiões rurais.

- **Monitoramento ambiental e de segurança**  
  A medição da qualidade do ar e da intensidade solar aumenta a proteção tanto das plantações quanto dos trabalhadores no campo.

- **Acessibilidade e baixo custo**  
  Desenvolvido com componentes acessíveis e de fácil implementação, o sistema é uma solução viável para **pequenas propriedades agrícolas**, que muitas vezes enfrentam barreiras no acesso a tecnologias avançadas.

---

# Materiais Utilizados:

- ESP32: Módulo microcontrolador com conectividade Wi-Fi para enviar os dados coletados e controlar o sistema de irrigação de forma remota.
- Sensor BME280: Para medir pressão atmosférica, temperatura do ar e umidade relativa.
- Sensor GUVA-S12SD: Sensor de índice UV para medir a radiação ultravioleta.
- Sensor de Chuva YL83: Detecta a presença de chuva, automatizando o desligamento da irrigação quando necessário.
- Sensor de Umidade do Solo HL69: Monitora a umidade do solo para o acionamento da irrigação.
- Sensor de Luminosidade (LDR): Detecta a intensidade da luz ambiente, permitindo identificar se é dia ou noite, útil para ajustes no ciclo de irrigação e economia de energia.
- Sensor de Gás e Fumaça MQ-135: Detecta a presença de gases nocivos no ambiente, como monóxido de carbono, amônia e fumaça, útil para segurança ambiental e alertas preventivos.
- Relé e Bomba de Irrigação: Controlam o fluxo de água com base nos dados de umidade do solo e detecção de chuva.

---

# Sistema de Alimentação:

- 2 baterias de lítio 3.7V ligadas em série (7.4V total): Fonte de energia portátil para alimentar o sistema.
- Carregador de baterias (TP4056 com proteção ou similar): Permite recarregar as baterias de forma segura via porta USB.
- Regulador de tensão (AMS1117 ou Step-Down tipo LM2596): Reduz a tensão de 7.4V para os 5V necessários para alimentar o ESP32 e os sensores.

---

## 🚀 Funcionamento do Sistema

O sistema realiza a leitura contínua dos sensores e envia os dados para um **bot no Telegram**, que notifica o agricultor em tempo real sobre o estado ambiental da plantação. Com base nesses dados, o sistema de irrigação é **ativado ou desativado automaticamente**, garantindo maior eficiência no uso da água.

### 🔄 Lógica de Operação

- A cada **10 segundos**, o ESP32 coleta dados dos sensores de:
  - Umidade do ar
  - Umidade do solo
  - Temperatura ambiente
  - Pressão atmosférica
  - Índice UV
  - Luminosidade
  - Gás/fumaça
  - Presença de chuva

- A irrigação é **ativada** automaticamente quando:
  - A umidade do solo estiver **abaixo de 40%** (valor configurável)

- A irrigação é **suspensa** automaticamente quando:
  - O sensor de chuva detectar precipitação
  - Ou em condições de luminosidade noturna (opcional)

### 📲 Notificações via Telegram

- O bot envia relatórios automáticos com os dados coletados a cada ciclo.
- Alertas são disparados caso alguma variável ultrapasse um limite crítico (por exemplo, presença de fumaça ou temperatura excessiva).

---

Essa abordagem oferece ao agricultor informações rápidas, automação eficiente e maior controle sobre o manejo hídrico da plantação, mesmo à distância.

---

# Conclusão

Este projeto propõe uma solução acessível e eficaz para a agricultura familiar, fornecendo informações meteorológicas precisas e permitindo a automação de processos essenciais, como a irrigação. Através da combinação de sensores e automação com o ESP32, as famílias agrícolas poderão otimizar o uso de recursos naturais, aumentar a produtividade e promover a sustentabilidade em suas práticas agrícolas.

---

# Próximos Passos

- Implementar uma interface gráfica simples para visualizar os dados meteorológicos de forma mais acessível.
- Explorar novas funcionalidades, como a previsão meteorológica com base em algoritmos de machine learning, para antecipar condições climáticas adversas.

Este projeto pode ser adaptado para atender a diferentes tipos de cultivos e condições ambientais, trazendo melhorias contínuas para a agricultura familiar.

---

## Fase Beta Simulador:

<img src="https://babbf25fa0.cbaul-cdnwnd.com/ca777225d6fbd038fc560b5e3ff1f1e0/200000012-e1e71e1e74/fase%20beta%20simulador.png?ph=babbf25fa0" alt="simulador beta" width="1000"/>

## Fase Beta Prototipagem:

<img src="https://babbf25fa0.cbaul-cdnwnd.com/ca777225d6fbd038fc560b5e3ff1f1e0/200000028-933ec933ee/imagem_2024-09-15_172730375.png?ph=babbf25fa0" alt="Prototipagem beta" width="1000"/>

---

## Fase Avançada Prototipagem:

<img src="https://github.com/user-attachments/assets/3f9993af-c654-4991-8046-f82a45742108" alt="Prototipagem avançada" width="500"/>

## Fase Avançada Simulador:

<img src="https://github.com/user-attachments/assets/ff920fd0-5fb9-4136-a09b-e333b5e58527" alt="simulador beta" width="1000"/>

---

## 📡 Contribuição e Licença

Este projeto é de código aberto e pode ser adaptado para diversas finalidades educacionais e agrícolas. Sinta-se à vontade para contribuir!

---
