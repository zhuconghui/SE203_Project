#include <stddef.h>
#include <stdint.h>

/*
    La fonction memcpy() copie n octets depuis la zone mémoire src vers la zone
    mémoire dest. Les deux zones ne doivent pas se chevaucher. 
    La fonction memcpy() renvoie un pointeur sur dest.  
*/
void *memcpy(void *dest, const void *src, size_t n) {
    uint32_t *dest_ptr = (uint32_t *)dest;
    const uint32_t *src_ptr = (const uint32_t *)src;

    for(size_t i = 0; i < n; i++){
        dest_ptr[i] = src_ptr[i];
    }

    return dest;
}

/*
    La fonction memmove() copie n octets depuis la zone mémoire src vers la zone
    mémoire dest. Les deux zones peuvent se chevaucher.
*/
void *memmove(void *dest, const void *src, size_t n) {
    uint32_t *dest_ptr = (uint32_t *)dest;
    const uint32_t *src_ptr = (const uint32_t *)src;

    if (src_ptr < dest_ptr && src_ptr + n > dest_ptr) {
        for (size_t i = n - 1; i < n; i--) {
            dest_ptr[i] = src_ptr[i];
        }
    } else if (dest_ptr < src_ptr && dest_ptr + n > src_ptr) {
        for (size_t i = 0; i < n; i++) {
            dest_ptr[i] = src_ptr[i];
        }
    } else {
        for (size_t i = 0; i < n; i++) {
            dest_ptr[i] = src_ptr[i];
        }
    }

    return dest; 
}

/* 
    La fonction memset() remplit les n premiers octets de la zone mémoire pointée par s avec l'octet c.  
*/
void *memset (void *s, int c, size_t n) {
    uint32_t *s_ptr = (uint32_t *)s;

    for(size_t i = 0; i < n; i++){
        s_ptr[i] = c;
    }

    return s;
}

/*
    La fonction memcmp() compare les n premiers octets des zones mémoire s1 et s2. 
    Elle renvoie un entier inférieur, égal, ou supérieur à zéro, si s1 est respectivement inférieure, égale ou supérieur à s2.  
*/
int memcmp(const void *s1, const void *s2, size_t n) {
    const uint32_t *s1_ptr = (const uint32_t *)s1;
    const uint32_t *s2_ptr = (const uint32_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (s1_ptr[i] < s2_ptr[i]) {
            return -1;
        } else if (s1_ptr[i] > s2_ptr[i]) {
            return 1;
        }
    }
    
    return 0;

}



