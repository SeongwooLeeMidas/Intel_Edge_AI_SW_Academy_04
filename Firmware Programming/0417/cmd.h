/*
 * cli.h
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#ifndef INC_CMD_H_
#define INC_CMD_H_

#include "main.h"

enum{
	E_CMD_LED,
	E_CMD_CLI,
	E_CMD_MAX
};


#ifdef __cplusplus
extern "C" {
#endif

void cmd_init(void);
void cmd_thread(void *);

#ifdef __cplusplus
}
#endif
#endif /* INC_CMD_H_ */
