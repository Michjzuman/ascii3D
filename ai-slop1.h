/* KI-generiert von gpt-6-astra: gesamter Code in dieser Datei.
 * "Sonnenreliquie": ein Kristall in einem achteckigen Halo,
 * begleitet von drei schwebenden Splittern. Keine externen Assets.
 */
#ifndef ARTWORK_H
#define ARTWORK_H

#include "3D.h"

/* KI-generiert von gpt-6-astra: lokale Koordinaten skalieren und versetzen.
 * x = Tiefe, y = nach unten, z = nach rechts in der Startansicht.
 * Wie CUBE_BODY nur mit nebenwirkungsfreien Argumenten verwenden.
 */
#define ARTWORK_POINT(x, y, z, s, a, b, c) \
    (P){(x) + (s) * (a), (y) + (s) * (b), (z) + (s) * (c)}

/* KI-generiert von gpt-6-astra: ein Viereck aus zwei Dreiecken. */
#define ARTWORK_QUAD(a, b, c, d, color) \
    {a, b, c, color}, {a, c, d, color}

/* KI-generiert von gpt-6-astra: geschlossenes Segment des Halo.
 * Aussenradius 1, Innenradius 0.82; Vorderseite x=0.18, hinten x=0.34.
 * u/v sind die y/z-Koordinaten zweier benachbarter Aussenpunkte.
 */
#define ARTWORK_RING_SEGMENT(x, y, z, s, u0, v0, u1, v1, color) \
    ARTWORK_QUAD( \
        ARTWORK_POINT(x,y,z,s,0.18,u0,v0), \
        ARTWORK_POINT(x,y,z,s,0.18,u1,v1), \
        ARTWORK_POINT(x,y,z,s,0.18,0.82*(u1),0.82*(v1)), \
        ARTWORK_POINT(x,y,z,s,0.18,0.82*(u0),0.82*(v0)), color), \
    ARTWORK_QUAD( \
        ARTWORK_POINT(x,y,z,s,0.34,u1,v1), \
        ARTWORK_POINT(x,y,z,s,0.34,u0,v0), \
        ARTWORK_POINT(x,y,z,s,0.34,0.82*(u0),0.82*(v0)), \
        ARTWORK_POINT(x,y,z,s,0.34,0.82*(u1),0.82*(v1)), BLUE), \
    ARTWORK_QUAD( \
        ARTWORK_POINT(x,y,z,s,0.18,u1,v1), \
        ARTWORK_POINT(x,y,z,s,0.18,u0,v0), \
        ARTWORK_POINT(x,y,z,s,0.34,u0,v0), \
        ARTWORK_POINT(x,y,z,s,0.34,u1,v1), GREEN), \
    ARTWORK_QUAD( \
        ARTWORK_POINT(x,y,z,s,0.18,0.82*(u0),0.82*(v0)), \
        ARTWORK_POINT(x,y,z,s,0.18,0.82*(u1),0.82*(v1)), \
        ARTWORK_POINT(x,y,z,s,0.34,0.82*(u1),0.82*(v1)), \
        ARTWORK_POINT(x,y,z,s,0.34,0.82*(u0),0.82*(v0)), RED)

/* KI-generiert von gpt-6-astra: langgezogener Oktaeder mit acht Facetten.
 * Unterschiedliche Farben betonen die Kanten ohne Beleuchtungsmodell.
 */
#define ARTWORK_CRYSTAL(x, y, z, s) \
    {ARTWORK_POINT(x,y,z,s,0,-1,0), \
     ARTWORK_POINT(x,y,z,s,-0.35,0,0), \
     ARTWORK_POINT(x,y,z,s,0,0,-0.4), WHITE}, \
    {ARTWORK_POINT(x,y,z,s,0,-1,0), \
     ARTWORK_POINT(x,y,z,s,0,0,-0.4), \
     ARTWORK_POINT(x,y,z,s,0.35,0,0), BLUE}, \
    {ARTWORK_POINT(x,y,z,s,0,-1,0), \
     ARTWORK_POINT(x,y,z,s,0.35,0,0), \
     ARTWORK_POINT(x,y,z,s,0,0,0.4), GREEN}, \
    {ARTWORK_POINT(x,y,z,s,0,-1,0), \
     ARTWORK_POINT(x,y,z,s,0,0,0.4), \
     ARTWORK_POINT(x,y,z,s,-0.35,0,0), YELLOW}, \
    {ARTWORK_POINT(x,y,z,s,0,1,0), \
     ARTWORK_POINT(x,y,z,s,0,0,-0.4), \
     ARTWORK_POINT(x,y,z,s,-0.35,0,0), BLUE}, \
    {ARTWORK_POINT(x,y,z,s,0,1,0), \
     ARTWORK_POINT(x,y,z,s,0.35,0,0), \
     ARTWORK_POINT(x,y,z,s,0,0,-0.4), GREEN}, \
    {ARTWORK_POINT(x,y,z,s,0,1,0), \
     ARTWORK_POINT(x,y,z,s,0,0,0.4), \
     ARTWORK_POINT(x,y,z,s,0.35,0,0), WHITE}, \
    {ARTWORK_POINT(x,y,z,s,0,1,0), \
     ARTWORK_POINT(x,y,z,s,-0.35,0,0), \
     ARTWORK_POINT(x,y,z,s,0,0,0.4), RED}

/* KI-generiert von gpt-6-astra: oeffentliche Body-Schnittstelle wie CUBE_BODY.
 * (x,y,z) ist das Zentrum, s der Halo-Aussenradius in Welteinheiten (s > 0).
 * Acht Ringsegmente und vier Kristalle bilden zusammen 96 Dreiecke.
 */
#define ARTWORK_TRIANGLE_COUNT 96
#define ARTWORK_BODY(x, y, z, s) (Triangle[]){ \
    ARTWORK_RING_SEGMENT(x,y,z,s,-1,0,-0.707107,0.707107,WHITE), \
    ARTWORK_RING_SEGMENT(x,y,z,s,-0.707107,0.707107,0,1,YELLOW), \
    ARTWORK_RING_SEGMENT(x,y,z,s,0,1,0.707107,0.707107,YELLOW), \
    ARTWORK_RING_SEGMENT(x,y,z,s,0.707107,0.707107,1,0,RED), \
    ARTWORK_RING_SEGMENT(x,y,z,s,1,0,0.707107,-0.707107,RED), \
    ARTWORK_RING_SEGMENT(x,y,z,s,0.707107,-0.707107,0,-1,BLUE), \
    ARTWORK_RING_SEGMENT(x,y,z,s,0,-1,-0.707107,-0.707107,BLUE), \
    ARTWORK_RING_SEGMENT(x,y,z,s,-0.707107,-0.707107,-1,0,WHITE), \
    ARTWORK_CRYSTAL(x,y,z,0.60*(s)), \
    ARTWORK_CRYSTAL((x)-0.12*(s),(y)-1.08*(s),(z)-0.70*(s),0.18*(s)), \
    ARTWORK_CRYSTAL((x)+0.08*(s),(y)-1.08*(s),(z)+0.70*(s),0.18*(s)), \
    ARTWORK_CRYSTAL((x)-0.20*(s),(y)+1.28*(s),z,0.22*(s)) \
}

#endif
