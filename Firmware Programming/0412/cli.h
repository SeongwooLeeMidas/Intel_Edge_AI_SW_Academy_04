/*
 * cli.h
 *
 *  Created on: Apr 12, 2024
 *      Author: IOT
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#ifdef __cplusplus
extern "C"{
#endif

void cli_init();
void cli_thread(void* arg);

#ifdef __cplusplus
}
#endif

#endif /* INC_CLI_H_ */
