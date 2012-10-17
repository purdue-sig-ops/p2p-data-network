/*
 * File:   util.h
 * Author: caleb
 *
 * Created on September 22, 2012, 6:13 AM
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ERR 1

void error (char *);
void error_t (int, char *);
int logb2 (int);

#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

