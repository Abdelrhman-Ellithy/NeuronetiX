/*
 * SPI_private.h
 *
 * Created: 2024-01-06 4:05:01 PM
 *  Author: Abdelrahman Ellithy
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


/************************************************************************/
/* SPI                                                                   */
/************************************************************************/
#define	   SPCR       *((volatile u8*)0x2D) /* SPI Control Register */
#define    SPIE         7		/* SPI Control Register - SPCR */
#define    SPE          6
#define    DORD         5
#define    MSTR         4
#define    CPOL         3
#define    CPHA         2
#define    SPR1         1
#define    SPR0         0
#define	   SPSR       *((volatile u8*)0x2E) /* SPI Status Register */
#define    SPIF         7 /* SPI Status Register - SPSR */
#define    WCOL         6
#define    SPI2X        0
#define	   SPDR       *((volatile u8*)0x2F) /* SPI I/O Data Register */


#endif /* SPI_PRIVATE_H_ */