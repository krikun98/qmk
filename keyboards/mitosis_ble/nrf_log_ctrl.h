#ifndef NRF_LOG_CTRL_H
#define NRF_LOG_CTRL_H

#include "app_uart.h"
#include <stdarg.h>

#define UART_TX_BUF_SIZE                 256                                        /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                 1                                          /**< UART RX buffer size. */

#undef printf
#define printf my_debug_log

#undef NRF_LOG_INFO
#undef NRF_LOG_DEBUG
#undef NRF_LOG_PROCESS
#undef NRF_LOG_FINAL_FLUSH

#define NRF_LOG_INFO my_debug_log
#define NRF_LOG_DEBUG my_debug_log

#define NRF_LOG_PROCESS() false
#define NRF_LOG_FINAL_FLUSH() false

#undef NRF_LOG_INIT
#define NRF_LOG_INIT my_debug_init

#undef RX_PIN_NUMBER
#undef TX_PIN_NUMBER
#undef CTS_PIN_NUMBER
#undef RTS_PIN_NUMBER
#undef HWFC

#define RX_PIN_NUMBER  -1
#define TX_PIN_NUMBER  DEBUG_PIN
#define CTS_PIN_NUMBER -1
#define RTS_PIN_NUMBER -1
#define HWFC false

#undef APP_ERROR_CHECK
#define APP_ERROR_CHECK(x) if (x!=NRF_SUCCESS) printf("ERROR 0x%04x in line %u\n", (int)x, __LINE__)

uint32_t my_debug_init(void *p);
void my_debug_log(const char *fmt, ...);
void uart_error_handle(app_uart_evt_t * p_event);

#endif //NRF_LOG_CTRL_H
