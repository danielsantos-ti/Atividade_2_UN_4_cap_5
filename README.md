# Atividade_2_UN_4_cap_5

## 📌 Descrição  
Este projeto foi desenvolvido para a **Raspberry Pi Pico W** utilizando o **SDK do Raspberry** e o **Visual Studio Code**.  
A atividade implementa o controle de um sistema de LEDs utilizando um **botão no GPIO 5** e temporizadores assíncronos com a função `add_alarm_in_ms()`.  

## 🚦 Funcionalidade  
1. Quando o botão (pushbutton) é pressionado, **todos os LEDs acendem**.  
2. Após 3 segundos, ocorre a **transição dos LEDs**, seguindo a sequência:  
   - 🔴🟡🟢 (Todos acesos) → 🔴🟡⚫ → 🔴⚫⚫ → ⚫⚫⚫ (Desligado).  
3. Durante a execução da sequência, **o botão não pode interromper o processo**.  
4. Após a finalização do ciclo (todos os LEDs apagados), o botão pode **iniciar um novo ciclo**.  
5. O código é compatível com a **Ferramenta Educacional BitDogLab**, utilizando o LED RGB (GPIOs 11, 12 e 13) e o botão A (GPIO 5).  

## 🛠️ Tecnologias e Ferramentas  
- **Microcontrolador:** Raspberry Pi Pico W  
- **Linguagem:** C  
- **SDK:** Raspberry Pi Pico  
- **IDE:** Visual Studio Code  
- **Bibliotecas:**  
  - `pico/stdlib.h`  
  - `hardware/gpio.h`  
  - `hardware/timer.h`  

