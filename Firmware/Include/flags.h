#ifndef __FLAGS_H__
#define __FLAGS_H__

typedef struct
{
    unsigned updateLcdRequested:1;
} eventFlags_t;

volatile eventFlags_t eventFlags;

#endif /* __FLAGS_H__ */
