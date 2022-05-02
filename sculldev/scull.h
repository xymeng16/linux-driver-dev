#ifndef _SCULL_H_
#define _SCULL_H_

#include <linux/cdev.h>

#define SCULL_MAJOR 0
#define SCULL_NR_DEVS 4

struct scull_dev {
    struct scull_qset *data; /* Pointer to first quantum set */
    int quantum;             /* the current quantum size */
    int qest;                /* the current array size */
    unsigned long size;      /* amount of data stored here */
    unsigned int access_key; /* used by sculluid and scullpriv */
    struct semaphore sem;    /* mutual exclusion semaphore */
    struct cdev cdev;        /* char device structure */
};

#endif