/* Arduino McpSarAdc Library
 * Copyright (C) 2011 by William Greiman
 *
 * This file is part of the Arduino McpSarAdc Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino McpSarAdc Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
  /**
 * \file
 * \brief Microchip SAR ADC

 */
#ifndef McpSarAdc_h
#define McpSarAdc_h
#include <Sd2PinMap.h>
/**
 * \defgroup McpSar Microchip Successive Approximation Register ADC
 *
 * WARNINGS
 *
 * These functions are designed to be used in an ISR, Interrupt Service
 * Routines.  If you use them in a program with interrupts enabled, access
 * to I/O ports may not be atomic.  This will be true for many pins on
 * the Mega so you should place a cli() before calls and a sei() after
 * calls to read functions from interrupt enabled code.
 *
 * On the Mega you should try to use pins on PORTA - PORTG.  These ports
 * will have faster performance and access to I/O ports will be atomic.
 *
 * @{
 */
#ifdef MCP_SAR_DBG
// You could remove the ifdef and define your pins here.
// Set MCP_SAR_DIN_PIN to -1 if it is not used by your chip.
const int8_t MCP_SAR_CLK_PIN  = 9;
const int8_t MCP_SAR_DOUT_PIN = 8;
const int8_t MCP_SAR_DIN_PIN  = 7;
const int8_t MCP3201_CS_PIN   = 6;
const int8_t MCP3202_CS_PIN   = 5;
const int8_t MCP3204_CS_PIN   = 4;
#endif  // MCP_SAR_DBG

/** bit 0 of input channel number */
const uint8_t MCP_CTRL_D0 = 1;
/** bit 1 of input channel number */
const uint8_t MCP_CTRL_D1 = 2;
/** bit 2 of input channel number */
const uint8_t MCP_CTRL_D2 = 4;
/** single-ended if set, differential if clear */
const uint8_t MCP_CTRL_SGL_DIFF = 8;
/** channel in single-ended mode or polarity in pseudo-differential mode */
const uint8_t MCP_CTRL_ODD_SIGN = 1;
//------------------------------------------------------------------------------
/** nop to tune soft SPI timing */
#define nop asm volatile ("nop\n\t")
//------------------------------------------------------------------------------
/** doxygen can't handle __attribute__ very well */
#define STATIC_ALWAYS_INLINE static inline __attribute__((always_inline))
//------------------------------------------------------------------------------
/** initialize I/O ports
 * \param[in] cs chip select pin
 */
STATIC_ALWAYS_INLINE void initMcpSar(int8_t cs) {
  cli();
  setPinMode(MCP_SAR_CLK_PIN, 1);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
  setPinMode(cs, 1);
  fastDigitalWrite(cs, 1);
  setPinMode(MCP_SAR_DOUT_PIN, 0);
  if (MCP_SAR_DIN_PIN >= 0) {
    setPinMode(MCP_SAR_DIN_PIN, 1);
    fastDigitalWrite(MCP_SAR_DIN_PIN, 1);
  }
  sei();
}
//------------------------------------------------------------------------------
/** delay n nops
 * \param[in] n nops to delay, must be a constant so compiler optimizes if().
 */
STATIC_ALWAYS_INLINE void mcpDelay(uint8_t n) {
  nop;
  if (n > 1) nop;
  if (n > 2) nop;
  if (n > 3) nop;
  }
//------------------------------------------------------------------------------
/** read next bit fast as possible
 * \param[in] v word to receive bit
 * \param[in] b bit number to be set.  v |= (1 << b) if next bit is high.
 */
STATIC_ALWAYS_INLINE void readBitFast(uint8_t &v, uint8_t b) {
  fastDigitalWrite(MCP_SAR_CLK_PIN, 1);
  if (fastDigitalRead(MCP_SAR_DOUT_PIN)) v |= (1 << b);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
}
//------------------------------------------------------------------------------
/** read next bit - 250 ns clock high/low
 * \param[in] v word to receive bit
 * \param[in] b bit number to be set.  v |= (1 << b) if next bit is high.
 */
STATIC_ALWAYS_INLINE void readBit250ns(uint16_t &v, uint8_t b) {
  mcpDelay(2);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 1);
  if (fastDigitalRead(MCP_SAR_DOUT_PIN)) v |= (1 << b);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
}
//------------------------------------------------------------------------------
/** read next bit - 312 ns clock high/low
 * \param[in] v word to receive bit
 * \param[in] b bit number to be set.  v |= (1 << b) if next bit is high.
 */
STATIC_ALWAYS_INLINE void readBit312ns(uint16_t &v, uint8_t b) {
  mcpDelay(3);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 1);
  nop;
  if (fastDigitalRead(MCP_SAR_DOUT_PIN)) v |= (1 << b);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
}
//------------------------------------------------------------------------------
/** write configuration bit
 * \param[in] b value for bit, true for high or false for low
 */
STATIC_ALWAYS_INLINE void mcpAdcWriteBit(bool b) {
  fastDigitalWrite(MCP_SAR_DIN_PIN, b);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 1);
  mcpDelay(3);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
}
//------------------------------------------------------------------------------
/** clock for don't care bits
 *\param[in] delayBefore if true, delay before raising clock*/
STATIC_ALWAYS_INLINE void mcpAdcDummy(bool delayBefore) {
  if (delayBefore) mcpDelay(3);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 1);
  mcpDelay(3);
  fastDigitalWrite(MCP_SAR_CLK_PIN, 0);
}
//------------------------------------------------------------------------------
/** read 12 bits with 2 MHz clock
 *\return value read from ADC
 */
STATIC_ALWAYS_INLINE uint16_t mcpAdcRead() {
  uint16_t v = 0;
  // NULL BIT
  mcpAdcDummy(true);
  readBit250ns(v, 11);
  readBit250ns(v, 10);
  readBit250ns(v,  9);
  readBit250ns(v,  8);
  readBit250ns(v,  7);
  readBit250ns(v,  6);
  readBit250ns(v,  5);
  readBit250ns(v,  4);
  readBit250ns(v,  3);
  readBit250ns(v,  2);
  readBit250ns(v,  1);
  readBit250ns(v,  0);
  return v;
}
//------------------------------------------------------------------------------
/** read MCP3001 8-bits - as fast as possible
 * \param[in] cs chip select pin
 * \return value read from ADC chip
 */
STATIC_ALWAYS_INLINE uint8_t readMCP3001(uint8_t cs) {
  fastDigitalWrite(cs, 0);
  uint8_t v = 0;
  // Sample
  mcpAdcDummy(false);
  // Sample
  mcpAdcDummy(false);
  // NULL BIT
  mcpAdcDummy(false);

  readBitFast(v,  7);
  readBitFast(v,  6);
  readBitFast(v,  5);
  readBitFast(v,  4);
  readBitFast(v,  3);
  readBitFast(v,  2);
  readBitFast(v,  1);
  readBitFast(v,  0);
  fastDigitalWrite(cs, 1);
  return v;
}
//------------------------------------------------------------------------------
/** read MCP3201
 * \param[in] cs chip select pin
 * \return value read from ADC chip
 */
STATIC_ALWAYS_INLINE uint16_t readMCP3201(uint8_t cs) {
  fastDigitalWrite(cs, 0);
  uint16_t v = 0;
  // Sample
  mcpAdcDummy(false);
  // Sample
  mcpAdcDummy(true);
  // NULL BIT
  mcpAdcDummy(true);
  readBit312ns(v, 11);
  readBit312ns(v, 10);
  readBit312ns(v,  9);
  readBit312ns(v,  8);
  readBit312ns(v,  7);
  readBit312ns(v,  6);
  readBit312ns(v,  5);
  readBit312ns(v,  4);
  readBit312ns(v,  3);
  readBit312ns(v,  2);
  readBit312ns(v,  1);
  readBit312ns(v,  0);
  fastDigitalWrite(cs, 1);
  return v;
}
//------------------------------------------------------------------------------
/** read MCP3202
 * \param[in] cs chip select pin
 * \param[in] ctrl control bits used to select mode and channel
 * \return value read from ADC chip
 */
STATIC_ALWAYS_INLINE uint16_t readMCP3202(uint8_t cs, uint8_t ctrl) {
  fastDigitalWrite(cs, 0);
  mcpAdcWriteBit(1);
  mcpAdcWriteBit(ctrl & MCP_CTRL_SGL_DIFF);
  mcpAdcWriteBit(ctrl & MCP_CTRL_ODD_SIGN);
  mcpAdcWriteBit(1);
  uint16_t v = mcpAdcRead();
  fastDigitalWrite(cs, 1);
  return v;
}
//------------------------------------------------------------------------------
/** read MCP3204
 * \param[in] cs chip select pin
 * \param[in] ctrl control bits used to select mode and channel
 * \return value read from ADC chip
 */
STATIC_ALWAYS_INLINE uint16_t readMCP3204(uint8_t cs, uint8_t ctrl) {
  fastDigitalWrite(cs, 0);
  mcpAdcWriteBit(1);
  mcpAdcWriteBit(ctrl & MCP_CTRL_SGL_DIFF);
  mcpAdcWriteBit(ctrl & MCP_CTRL_D2);
  mcpAdcWriteBit(ctrl & MCP_CTRL_D1);
  mcpAdcWriteBit(ctrl & MCP_CTRL_D0);
  mcpAdcDummy(true);
  uint16_t v = mcpAdcRead();
  fastDigitalWrite(cs, 1);
  return v;
}
//------------------------------------------------------------------------------
/** read MCP3208
 * \param[in] cs chip select pin
 * \param[in] ctrl control bits used to select mode and channel
 * \return value read from ADC chip
 */
STATIC_ALWAYS_INLINE uint16_t readMCP3208(uint8_t cs, uint8_t ctrl) {
  return readMCP3204(cs, ctrl);
}
/** @}*/
#endif  // McpSarAdc_h