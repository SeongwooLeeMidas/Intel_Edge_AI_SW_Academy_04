/*
 * cli.h
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void cli_init(void);
void cli_thread(void *);
void cli_msg_put(void *arg);

#ifdef __cplusplus
}
#endif

#endif /* INC_CLI_H_ */
