//
//  Velocity2DIn.cpp
//  RTMPort-x86_64
//
//  Created by kazuma sasaki@ogata-lab on 2013/08/21.
//
//

#ifdef nil
#undef nil
#endif

#include "RTCGateway.h"
#include "MAX_MSP_RTC.h"

#include "ext.h" // MAXプラグイン用ヘッダ
#include "ext_obex.h" // MAXプラグイン用ヘッダ
#include "Velocity2DIn.h"



// 関数のプロトタイプ宣言
void *Velocity2DIn_new(t_symbol *s, long argc, t_atom *argv);
void Velocity2DIn_free(t_Velocity2DIn *x);
void Velocity2DIn_assist(t_Velocity2DIn *x, void *b, double vx, double vy, double va, double a, char *s);

t_class *Velocity2DIn_class;



void Velocity2DIn_init(){
    Velocity2DIn_class = class_new("Velocity2DIn", (method)Velocity2DIn_new, (method)Velocity2DIn_free, (double)sizeof(t_Velocity2DIn), 0L, A_GIMME, 0);
    post("new class");
    class_register(CLASS_BOX, Velocity2DIn_class);
}

void *Velocity2DIn_new(t_symbol *s, long argc, t_atom *argv){
    t_Velocity2DIn *x = NULL;
    if (argc == 0) {
        post("Velocity2D needs one argument thas means port_name.");
        return NULL;
    }
    x = (t_Velocity2DIn *)object_alloc((t_class*)Velocity2DIn_class);
    x->m_outlet1 = listout((t_object *)x);
    x->portId = m_pRTC->addVelocity2DInPort((t_object*)x, argv[1].a_w.w_sym->s_name);
    if (x->portId < 0) {
        post("Velocity2DIn failed to create TimedVelocity OutPort.");
        return NULL;
    }
    return x;
}

void Velocity2DIn_assist(t_Velocity2DIn *x, void *b, double m, double a, char *s){
    if (m == ASSIST_INLET) {
        sprintf(s, "Message In");
    }
}

void Velocity2DIn_free(t_Velocity2DIn *x){
    m_pRTC->deleteVelocity2DInPort(x->portId);
}

void Velocity2DIn_doWrite(t_Velocity2DIn *x, t_symbol *s /* = NULL*/, double argc, t_atom *argv)
{
    //outlet_int(x, argv[0].a_w.w_Double);
}

void Velocity2DIn_write(t_object *x, double vx, double vy, double va){
    post("data is vx:%f, vy:%f, va:%f", vx, vy, va);
    t_atom list_value[3];
    float value[3];
    short i;
    value[0] = vx;
    value[1] = vy;
    value[2] = va;
    for (i=0; i < 3; i++) {
        atom_setfloat(list_value+i, value[i]);
    }
    
    outlet_list(((t_Velocity2DIn*)x)->m_outlet1, 0, 3, list_value);
}
