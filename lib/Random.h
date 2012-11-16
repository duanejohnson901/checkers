/* 
 * File:   Random.h
 * Author: Shariath
 *
 * Created on 15 de Novembro de 2012, 15:42
 */

#ifndef RANDOM_H
#define	RANDOM_H

#include <cstdlib>
#include <ctime>

class Random {
public:
    static Random instance;
    static int get(int min, int max) {
        srand(time(NULL));
        return min + rand() % (max + 1);
    }
    static int get(int max) {
        return rand()%(max+1);
    }
private:
    Random() { srand(time(NULL)); } 
} ;



#endif	/* RANDOM_H */

