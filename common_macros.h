/*
 * common_macros.h
 *
 * Created: 17/02/2020 11:35:08 ص
 *  Author: TOSHIBA
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* ERROR_GANDLING_STATUS */
#define E_OK           (0)  //NO error
#define E_NOK          (1)  //Error exist


#define CLEAR_BIT(REG,BIT) (REG&=~(BIT))
#define SET_BIT(REG,BIT)   (REG|=(BIT))
#define READ_BIT(REG,BIT) (REG&(BIT))

typedef char u8_ERROR_STATUS_t ;


#endif /* COMMON_MACROS_H_ */