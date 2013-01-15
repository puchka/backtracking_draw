#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

typedef struct Point Point;
struct Point
{
    int x;
    int y;
};

typedef struct Element Element;
struct Element
{
    Point point;
    Element *next;
};

typedef struct File File;
struct File
{
    Element *head;
};

void string(File *file, Point point);
Point march(File *file);

#endif // PILE_H_INCLUDED
