#pragma once

typedef struct {
    void (*Begin)(void);
    void (*End)(void);
} STDVT;

STDVT std;

