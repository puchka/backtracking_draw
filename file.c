#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void string(File *file, Point point)
{
    if (file==NULL)
        exit(EXIT_FAILURE);

    Element *newElement = NULL;
    newElement = malloc(sizeof(*newElement));
    if (file==NULL || newElement==NULL)
        exit(EXIT_FAILURE);
    newElement->point = point;
    newElement->next = NULL;
    if (file->head==NULL)
        file->head=newElement;
    else
    {
        Element *actualElement = file->head;
        while (actualElement->next!=NULL)
            actualElement = actualElement->next;
        actualElement->next = newElement;
    }
}

Point march(File *file)
{
    if (file==NULL)
        exit(EXIT_FAILURE);

    Point pointHead;
    Element *actualHead = NULL;
    actualHead = file->head;
    pointHead = file->head->point;
    file->head = actualHead->next;
    free(actualHead);
    return pointHead;
}
