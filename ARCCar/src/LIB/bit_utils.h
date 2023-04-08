#ifndef LIB_BIT_UTILS_H_
#define LIB_BIT_UTILS_H_

#define SET_BIT(REG, BIT) REG |= (1 << BIT)
#define CLR_BIT(REG, BIT) REG &= ~(1 << BIT)
#define TGL_BIT(REG, BIT) REG ^= (1 << BIT)
#define GET_BIT(REG, BIT) ((REG >> BIT) & 1)
#define ASSIGN_BIT(REG, BIT, VALUE) \
    if (VALUE)                      \
        SET_BIT(REG, BIT);          \
    else                            \
        CLR_BIT(REG, BIT)

#define SET_BITS(REG, MASK, START) REG |= (0b##MASK << START)
#define CLR_BITS(REG, MASK, START) REG &= ~(0b##MASK << START)
#define TGL_BITS(REG, MASK, START) REG ^= (0b##MASK << START)
#define GET_BITS(REG, MASK, START) ((REG >> START) & 0b##MASK)
#define ASSIGN_BITS(REG, MASK, START, VALUE) \
    CLR_BITS(REG, MASK, START);              \
    SET_BITS(REG, VALUE, START)

#define SET_REG(REG) REG = 0xFF
#define CLR_REG(REG) REG = 0x00
#define TGL_REG(REG) REG = ~REG
#define ASSIGN_REG(REG, VALUE) REG = VALUE

#define CONC_8bit(b7, b6, b5, b4, b3, b2, b1, b0) CONC_8bit_HELP(b7, b6, b5, b4, b3, b2, b1, b0)
#define CONC_8bit_HELP(b7, b6, b5, b4, b3, b2, b1, b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0

#endif
