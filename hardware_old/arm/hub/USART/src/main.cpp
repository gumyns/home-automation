#include <config/Config.h>
#include <Application.h>
#include <DeviceParser.h>
#include <DeviceSocket.h>
#include <HubParser.h>
#include <ExternalSocket.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

::gumyns::sh::Socket::IRQ externalIRQ, deviceIRQ;

extern "C" {
void EXTI4_15_IRQHandler() {
	if (deviceIRQ) {
		deviceIRQ();
	}
}

void USART1_IRQHandler() {
	if (externalIRQ) {
		externalIRQ();
	} else { // callback not set - disable interrupts
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	}
}

void SPI1_IRQHandler() {
	if (deviceIRQ) {
		deviceIRQ();
	}
}

void Default_Handler() {
	if (externalIRQ) {
		externalIRQ();
	}
}

void HardFault_Handler() {
	if (externalIRQ) {
		externalIRQ();
	}
}
}

int main(int argc, char* argv[]) {
	Config::init();

	Application app(new HubParser(new ExternalSocket()), new DeviceParser(new DeviceSocket()));
	externalIRQ = app.extIRQ();
	deviceIRQ = app.devIRQ();

	app.main();
}

#pragma GCC diagnostic pop
