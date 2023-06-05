# README

- Este é o código de exemplo para controlar uma estufa com base na luminosidade, temperatura e umidade. O código utiliza um Arduino e alguns componentes adicionais.

## Integrantes

- Felipe Arnus – RM: 550923
- João Pedro Chambrone – RM: 97857
- João Pedro Vieira – RM: 99805
- Vitor Hugo – RM: 97758

## Componentes necessários

- Arduino Uno
- Display LCD
- 3 Servo motores
- Sensor de luz (LDR)
- Sensor de temperatura
- Sensor de umidade
- Potenciômetro de luminosidade
- Potenciômetro de temperatura
- 3 Botões
- 4 Resistor(1kΩ)
- 1 Resistor(1.8kΩ)
- 2 Placa de ensaio pequena

## Bibliotecas utilizadas

- LiquidCrystal.h
- Servo.h

## Funcionamento

- O código controla o ambiente com base nos valores de luz, temperatura e umidade. Ele exibe informações relevantes no display LCD e realiza ações com os servo motores de acordo com as condições do ambiente.

- O código possui um loop principal que é executado continuamente. Ele lê os valores dos sensores de luz, temperatura e umidade e realiza as ações necessárias com base nesses valores.

- Botão 1: Ao pressionar o botão 1, você entra no modo de configurações. Nesse modo, é possível ajustar a luminosidade e a temperatura desejadas utilizando os potenciômetros. As alterações feitas no modo de configurações serão aplicadas quando você pressionar o botão 1 novamente para confirmar. As alterações possiveis serão as seguintes:

- - Potenciômetros: Além dos botões, você pode utilizar os potenciômetros para ajustar a luminosidade e a temperatura desejadas. O potenciômetro de luminosidade controla a intensidade da luz, enquanto o potenciômetro de temperatura ajusta a temperatura desejada. Os valores dos potenciômetros são lidos e utilizados para definir os valores de referência para luz e temperatura.

- - Botão 2 e Botão 3: Esses botões são utilizados para alterar a frequência com que as plantas são regadas. O botão 2 aumenta, enquanto o botão 3 diminui a frequência em que isso acontece. A cada pressionamento, a frequência é atualizada e exibida no display LCD.

## CODIGO DE ARDUINO

- https://www.tinkercad.com/things/0uNN81YbWuR-copy-of-og/editel?sharecode=TYuLiQFEWRQITqid1smCfYsl2i2qUjPDpiavdgxIRDQ
