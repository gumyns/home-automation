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
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	return [this]() {
		if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
			listener(USART_ReceiveData(USART1));
		}
		if (USART_GetITStatus(USART1, USART_IT_TXE)) {
			if (out.pending()) {
				USART_SendData(USART1, out.pop());
			} else {
				USART_ITConfig(USART1,USART_IT_TXE, DISABLE);
			}
		}
	};
}

void ExternalSocket::write(uint8_t byte){
	out.push(byte);
}

void ExternalSocket::send() {
	out.push('\r');
	out.push('\n');
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
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
	// run usart
	USART_Cmd(USART1, ENABLE);
}

void ExternalSocket::close() {
	USART_DeInit(USART1);
}

bool ExternalSocket::idle() {
	return !out.pending();
}
