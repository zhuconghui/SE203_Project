extern char _bstart, _bend;

void init_bss() {
    for(char *dst = &_bstart; dst < &_bend; dst++){
        *dst = 0;
    }
}