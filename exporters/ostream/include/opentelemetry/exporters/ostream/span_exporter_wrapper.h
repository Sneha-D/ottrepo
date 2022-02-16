#ifndef __MYWRAPPER_H
#define __MYWRAPPER_H


typedef struct COStreamSpanExporter COStreamSpanExporter;

#ifdef __cplusplus
extern "C" {
#endif


COStreamSpanExporter* newOStreamSpanExporter();

void deleteOStreamSpanExporter(COStreamSpanExporter* v);

#ifdef __cplusplus
}
#endif
#endif