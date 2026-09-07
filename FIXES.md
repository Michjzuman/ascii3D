# ASCII3D: Erklärung der vorgeschlagenen Fixes

Diese Datei erklärt die drei Fehler aus der Durchsicht und die zusätzlich erwähnten Compilerwarnungen. Die Änderungen sind Vorschläge, nicht bereits umgesetzt. Der Quellcode wurde für diese Dokumentation nicht verändert.

Die Zeilenangaben beziehen sich auf den bei der Durchsicht gelesenen Stand. Das ist keine vollständige Prüfung auf alle möglichen Fehler im Projekt.

## 1. Kamerarichtung und Bildkoordinaten korrigieren

**Stellen:** `3D.c:28–32`, `3D.c:74–84`, `3D.h:34–37`, `main.c:15–20`.

### Was momentan passiert

Die Kamera hat zwei unterschiedliche Arten von Werten:

- `x`, `y`, `z`: Position in der Welt.
- `dx`, `dy`: vorgesehene Blickwinkel.

In `take_photo()` werden aber `cam->x` und `cam->y` als Winkeloffset an `get_cam_dir()` übergeben. Dadurch beeinflusst die Position gleichzeitig die Blickrichtung. `cam->dx` und `cam->dy` werden bei der Strahlberechnung überhaupt nicht benutzt.

Zusätzlich enthält das Makro zwei weitere Probleme:

```c
#define get_cam_dir(a, b, c) (atan((a / 2 + b) / photo->fov) * 180.0 / PI + c)
```

1. `atan()` liefert einen Winkel in Radiant. Das Makro rechnet ihn in Grad um. `get_distance()` übergibt diesen Wert anschliessend an `sinf()` und `cosf()`, die aber Radiant erwarten.
2. `a / 2 + b` verschiebt die Pixelkoordinate weiter ins Positive. Für einen Blickstrahl relativ zur Bildmitte muss die halbe Bilddimension abgezogen werden.

### Wie man es korrigiert

Für eine kleine Korrektur innerhalb des bestehenden Winkelmodells:

1. `cam->dx` und `cam->dy` als Winkel verwenden.
2. Alle Winkel durchgehend in Radiant halten. Die Umrechnung `* 180.0 / PI` entfernen.
3. Pixel relativ zur Bildmitte berechnen.
4. Vertikal berücksichtigen, dass Terminalzeilen nach unten wachsen. Bei einer Welt mit positivem Y nach oben muss der obere Bildteil einen positiven vertikalen Offset erhalten.
5. Für die vorhandenen `double`-Werte `sin()` und `cos()` statt `sinf()` und `cosf()` benutzen, um unnötige Präzisionsverluste zu vermeiden.

Die folgenden Ausdrücke zeigen das Prinzip und sind noch nicht in den Code eingebaut:

```c
double screen_x = ((double)x + 0.5) - (double)photo->w / 2.0;
double screen_y = (double)photo->h / 2.0 - ((double)y + 0.5);

double dx = cam->dx + atan(screen_x / photo->fov);
double dy = cam->dy + atan(screen_y / photo->fov);
```

Das `+ 0.5` verwendet jeweils die Mitte einer Zeichenzelle. Die Umwandlung nach `double` muss vor der Subtraktion passieren: `x`, `y`, `w` und `h` sind unsigned. Eine Subtraktion direkt in diesen Typen könnte unterlaufen.

Die Richtung im bestehenden Modell lautet dann weiterhin:

```c
dir.x = cos(dy) * cos(dx);
dir.y = sin(dy);
dir.z = cos(dy) * sin(dx);
```

Die Winkelberechnung gehört vor die innere Dreiecksschleife: Für denselben Bildpunkt ändert sich die Strahlrichtung nicht von Dreieck zu Dreieck. Das ist eine zusätzliche Effizienzverbesserung, nicht die eigentliche Fehlerkorrektur.

### Wichtig: Was bedeutet `fov` hier?

In der aktuellen Formel wird `photo->fov` wie eine Brennweite beziehungsweise ein Abstand zur Bildebene benutzt, nicht wie ein Sichtwinkel. Ein kleiner Wert erzeugt grosse Winkel schon bei kleinen Abständen von der Bildmitte. Der Wert muss positiv und endlich sein.

Wenn `fov` stattdessen einen horizontalen Sichtwinkel bezeichnen soll, braucht es eine andere Definition. Für ein Lochkameramodell ist die horizontale Brennweite in Zeichenzellen:

```text
focal_length = (width / 2) / tan(horizontal_fov / 2)
```

Auch hier wird der Winkel in Radiant angegeben. Für eine unverzerrte Darstellung muss ausserdem das tatsächliche Verhältnis von Zeichenhöhe zu Zeichenbreite berücksichtigt werden. Terminalzellen sind nicht unbedingt quadratisch.

Die getrennte Addition horizontaler und vertikaler Winkel oben ist eine kleine Reparatur des vorhandenen Ansatzes, aber kein vollständig perspektivisch korrektes Lochkameramodell. Dafür würde man einen lokalen Strahl durch die Bildebene erzeugen, ihn mit der Kameraorientierung in die Welt drehen und normalisieren. Ohne Normalisierung wäre der Schnittparameter `t` nicht unmittelbar eine Entfernung.

### Wichtig: Die Kamera muss auch zum Würfel schauen

Beim bestehenden Richtungsmodell bedeutet `dx = 0` und `dy = 0`: Blick entlang der positiven X-Achse, nicht entlang der positiven Z-Achse. Die Startwerte in `main.c` garantieren deshalb nach der Reparatur noch keinen sichtbaren Würfel.

Um auf einen Zielpunkt zu schauen, kann man die Winkel aus dem Vektor von der Kamera zum Ziel bestimmen:

```c
double vx = target.x - cam->x;
double vy = target.y - cam->y;
double vz = target.z - cam->z;

cam->dx = atan2(vz, vx);
cam->dy = atan2(vy, hypot(vx, vz));
```

`target` ist hier ein beispielhafter Zielpunkt vom Typ `P`, kein bereits vorhandenes Symbol im Projekt. Ziel und Kameraposition dürfen für eine definierte Blickrichtung nicht identisch sein.

### Wie man den Fix prüft

- Eine Änderung von `cam.dx` oder `cam.dy` muss die Blickrichtung verändern.
- Eine Änderung von `cam.x`, `cam.y` oder `cam.z` darf nicht zusätzlich die Orientierung verändern. Das Bild selbst verändert sich durch die neue Position natürlich trotzdem.
- Horizontale Pixeloffsets müssen links und rechts der Bildmitte unterschiedliche Vorzeichen haben.
- Bei Blick entlang der positiven X-Achse muss ein passend davor platziertes Testdreieck in der Bildmitte getroffen werden.
- Den Würfeltest mit einer ausdrücklich auf den Würfel gerichteten Kamera durchführen, nicht nur mit den bisherigen Startwinkeln.

## 2. Entfernung vor dem Cast auf `U8` begrenzen

**Stelle:** `3D.c:79–90`.

### Was momentan passiert

`next_dis` startet mit `DBL_MAX`. Wenn kein Dreieck getroffen wird, bleibt dieser Wert unverändert.

Aktuell erfolgt zuerst der Cast:

```c
U8 value = (U8)next_dis;
if (next_dis < 0) value = 0;
if (next_dis > 255.0) value = 255;
```

`U8` kann nur Werte von 0 bis 255 speichern. Bei der Konvertierung eines Gleitkommawerts muss dessen ganzzahliger Anteil im Zieltyp darstellbar sein. Das ist bei `DBL_MAX` nicht der Fall: Der Cast hat undefiniertes Verhalten. Die spätere Zuweisung von 255 repariert den vorherigen ungültigen Cast nicht.

Dasselbe Problem betrifft ausreichend grosse Trefferentfernungen, nicht nur Strahlen ohne Treffer.

### Wie man es korrigiert

Zuerst entscheiden, welcher Bereich vorliegt. Nur im sicheren Bereich casten:

```c
U8 value;
if (!isfinite(next_dis) || next_dis >= 255.0) {
    value = 255;
} else if (next_dis <= 0.0) {
    value = 0;
} else {
    value = (U8)next_dis;
}
```

`isfinite()` kommt aus `<math.h>`, das `3D.c` bereits einbindet. Der Zweig behandelt nichtendliche Werte bewusst wie Hintergrund. `DBL_MAX` selbst ist endlich, wird aber durch den Vergleich mit 255 abgefangen.

Die Prüfung auf nichtendliche Werte ist zusätzliche Absicherung. Im normalen aktuellen Ablauf bleiben ungültige Schnittwerte wegen der Vergleiche in der Trefferauswahl normalerweise bereits unberücksichtigt.

### Warum Hintergrund weiterhin 255 ist

`draw()` invertiert die gespeicherte Entfernung:

```c
U8 value = 255 - photo->pic[y][x];
```

Ein gespeicherter Hintergrundwert von 255 wird dadurch zum Helligkeitswert 0. Der Fix erhält diese bisherige Zuordnung. Er macht aus der Entfernungsdarstellung keine Beleuchtungsberechnung und ändert auch nicht die Zeichenpalette.

### Wie man den Fix prüft

- Leere Welt: Jeder Bildpunkt bekommt den Hintergrundwert 255.
- Treffer oberhalb der darstellbaren Entfernung: Der gespeicherte Wert wird auf 255 begrenzt.
- Treffer innerhalb des Bereichs: Die Entfernung wird wie bisher durch den Cast abgeschnitten, nicht gerundet.
- Beim Lauf mit UndefinedBehaviorSanitizer und explizitem `float-cast-overflow`-Check darf keine ungültige Gleitkomma-zu-Integer-Konvertierung auftreten.

## 3. Grössere Zählertypen in `draw()` verwenden

**Stelle:** `ascii.c:61–62`; Bilddimensionen in `photo.h:6–9`.

### Was momentan passiert

Die Bilddimensionen `photo->w` und `photo->h` sind `U32`, die Schleifenzähler aber nur `U8`:

```c
for (U8 y = 0; y < photo->h; y++) {
    for (U8 x = 0; x < photo->w; x++) {
```

Ein `U8`-Zähler springt nach 255 wieder auf 0. Bei einer Breite ab 256 bleibt `x < photo->w` deshalb immer wahr. Bei einer Höhe ab 256 gilt dasselbe für `y`.

Das ist definierter unsigned Wraparound, kein undefiniertes Verhalten. Hier verursacht er aber eine Endlosschleife. `getch()` wird nicht mehr erreicht; auch `q` beendet die Darstellung dann nicht mehr.

### Wie man es korrigiert

Die Schleifenzähler an die Bilddimensionen anpassen:

```c
for (U32 y = 0; y < photo->h; y++) {
    for (U32 x = 0; x < photo->w; x++) {
```

Die Bildwerte selbst bleiben `U8`. Nur die Koordinaten brauchen den grösseren Typ. In `take_photo()` werden bereits `U32`-Zähler verwendet.

`mvaddch()` erwartet Koordinaten vom Typ `int`. Die aktuellen Dimensionen stammen aus den ncurses-Funktionen `getmaxx()` und `getmaxy()`, die ebenfalls `int` liefern. Für diese gültigen Terminaldimensionen sind die Koordinaten darstellbar. Falls später beliebige externe Bildgrössen unterstützt werden, braucht dieser Übergang eine eigene Bereichsprüfung; ein blinder Cast wäre keine solche Prüfung.

### Wie man den Fix prüft

- Mit einem normalen kleinen Terminal prüfen, dass Darstellung und `q` unverändert funktionieren.
- Mit 255, 256 und mehr als 256 Spalten testen: `draw()` muss jeweils bis zur Eingabeabfrage gelangen.
- Die entsprechende Grenze auch für die Zeilenzahl testen, nötigenfalls mit einem kontrollierten Testaufbau statt einem echten riesigen Fenster.
- Dies behebt nicht die fehlende Anpassung des Bildpuffers bei nachträglicher Terminalgrössenänderung. Das wäre ein separates Thema.

## 4. Compilerwarnungen zu leeren Parameterlisten bereinigen

**Stellen:** unter anderem `ascii.h:14–15`, `main.c:6`, `3D.c:10`, `ascii.c:25`, `ascii.c:72`, `ascii.c:76–77`.

Unter C17 bedeutet eine Deklaration wie `U32 get_term_w();` nicht ausdrücklich, dass die Funktion keine Argumente nimmt. Dafür schreibt man `void` in die Parameterliste.

Beispiele für die Bereinigung:

```c
U32 get_term_w(void);
U32 get_term_h(void);
int main(void) {
```

Dasselbe Muster sollte für die betroffenen Funktionsdefinitionen gelten, beispielsweise `World init_world(void)` und `void init(void)`. Bereits korrekt deklarierte Prototypen bleiben unverändert.

Das beseitigt die gemeldeten Prototypwarnungen und macht die Schnittstellen eindeutig. Es löst keinen der drei Laufzeitfehler oben.

## Sinnvolle Reihenfolge

1. Den ungültigen Entfernungscast beseitigen.
2. Die Schleifenzähler korrigieren, damit die Ausgabe nicht bei breiten Terminals hängt.
3. Winkel, Bildmitte und Startausrichtung der Kamera korrigieren; die Bedeutung von `fov` bewusst festlegen.
4. Die Prototypwarnungen bereinigen.
5. Erst danach weitere Darstellungsthemen wie perspektivische Projektion, Zeichen-Seitenverhältnis und Helligkeitsabstufung angehen.

## Was tatsächlich geprüft wurde

Bei der Durchsicht wurde folgender reiner Syntaxcheck ausgeführt:

```sh
clang -std=c17 -Wall -Wextra -Wpedantic -fsyntax-only main.c 3D.c ascii.c photo.c
```

Er meldete keine Syntaxfehler, aber Warnungen zu Funktionsdeklarationen beziehungsweise Definitionen ohne explizite `void`-Parameterliste.

Die oben beschriebenen Laufzeitprüfungen sind noch durchzuführen, nachdem die Fixes implementiert wurden. Das Programm wurde im Rahmen dieser Durchsicht nicht gestartet. Ein erfolgreicher Syntaxcheck beweist weder korrekte Projektion noch fehlerfreies Laufzeitverhalten.
