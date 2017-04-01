/*
 * ExternalSocket.cpp
 *
 *  Created on: 29.12.2016
 *      Author: gumyns
 */

#include "ExternalSocket.h"
#include <config/USART.h>

ExternalSocket::ExternalSocket() {}

ExternalSocket::~ExternalSocket() {}

::gumyns::sh::Socket::IRQ ExternalSocket::handler() {
	Usart::CR1::disable(Usart::CR1::TXE);
	return [this]() {
		if (Usart::ISR::has(Usart::ISR::RXNE)) {
			listener(Usart::read());
		}
		if (Usart::ISR::has(Usart::ISR::TXE)) {
			if (out.pending()) {
				Usart::write(out.pop());
			} else {
				Usart::CR1::disable(Usart::CR1::TXE);
			}
		}
	};
}

void ExternalSocket::write(uint8_t byte){
//	char str[3];
//	sprintf(str, "%02x ", (int)byte);
//	for(int i = 0; i < 2; i++) {
//		out.push(str[i]);
//	}
	out.push(byte);
}

void ExternalSocket::send() {
	Usart::CR1::enable(Usart::CR1::TXE);
}

void ExternalSocket::open() {
	USART_InitTypeDef uart;
	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	uart.USART_WordLength = USART_WordLength_8b;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &uart);
	//interrupts
	Usart::CR1::disable(Usart::CR1::TXE);
	Usart::CR1::enable(Usart::CR1::RXNE | Usart::CR1::USART);

	NVIC_InitTypeDef nvic;
	// Enable the USART1 interrupt
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	nvic.NVIC_IRQChannel = EXTI4_15_IRQn;
	nvic.NVIC_IRQChannelPriority = 3;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

void ExternalSocket::close() {
	USART_DeInit(USART1);
	Usart::CR1::disable(Usart::CR1::USART);
	NVIC_DisableIRQ(EXTI4_15_IRQn);
}

bool ExternalSocket::idle() {
	return !out.pending();
}
