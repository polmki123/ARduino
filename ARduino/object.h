/*
	2�� �̻��� ��Ŀ�� �ν��ϱ� ���� ���Ǵ� ���
*/

#ifndef OBJECT_H
#define OBJECT_H


#define   OBJECT_MAX       30

typedef struct {
    char       name[256];
    int        id;
    int        visible;
	int		   collide;
    double     marker_coord[4][2];
    double     trans[3][4];
    double     marker_width;
    double     marker_center[2];
	float	   ar_trs[5];
	float	   ar_rot[4];
} ObjectData_T;

ObjectData_T  *read_ObjData( char *name, int *objectnum );

#endif
