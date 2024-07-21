/*
 * type.h
 *
 *  Created on: Apr 16, 2024
 *      Author: IOT
 */

#ifndef INC_TYPE_H_
#define INC_TYPE_H_



enum{
	// 메세지를 받아서 cli로 던져야됨
	E_MSG_CLI = 0x1000,
	E_MSG_CLI_INIT,
	E_MSG_MAX
};


// 넣고 빼는거에 따라 크기가 바뀌도록 PACK해줌
typedef  struct __attribute__((packed)){
	// 메세지의 id
	uint16_t id;

	// 크기를 크지않게 할거임
	// union = 같은 자리를 차지한다 = type casting
	union{
		uint8_t		b[4];
		uint16_t	hw[2];
		uint32_t	w;
		void		*vPtr;
		uint8_t 	*bPtr;
		uint16_t 	*hPtr;
		uint32_t 	*wPtr;
	}body;
}MSG_T;




#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* INC_TYPE_H_ */
