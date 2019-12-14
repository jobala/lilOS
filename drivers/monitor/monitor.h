#pragma once
#include "../../common/types.h"

void monitor_put(char);
void monitor_clear();
void monitor_write(char*);
void monitor_write_hex(u32int);
void monitor_write_dec(u32int);
