#ifndef __INIT_H__
#define __INIT_H__

inline void initIO(void);       /* Ki- és bemeneti kapuk inicalizálása */
inline void initTimer0(void);   /* Timer0 modul inicializálása */
inline void initA2D(void);      /* Analóg-digitális átalakító inicializálása */
inline void initUART(void);     /* UART inicializálása */
inline void initLCD(void);      /* LCD kijelző inicializálása */

#endif /* __INIT_H__ */
