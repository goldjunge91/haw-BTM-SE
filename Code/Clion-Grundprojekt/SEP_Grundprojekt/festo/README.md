# Festo Projekt

In diesem Ordner liegen alle Dateien, die für die Ansteuerung der Festo-Anlagen notwendig sind.
Darüberhinaus sind hier auch alle Dateien, die für die Simulation der Anlage erforderlich sind.

## Nutzung der Simulation
Um die Simulation zu nutzen, muss in der CMakeLists.txt in diesem Ordner (festo) die Zeile `
``` CMake
add_definitions(-DHOME -DSIMULATION)
``` 
enthalten sein.

Durch die beiden Defines wird die Simulation genutzt. 
Diese startet im Hintergrund bei der Ausführung des Programms automatisch und führt eine feste Abfolge von Ereignissen (Tastendrücke, Unterbrechung von Lichtschranken, Auflegen von Werkstücken) durch.

ACHTUNG: Bei Änderungen in einer CMakeLists.txt muss anschließend ein Reload des CMake Projekts erfolgen.

## Wahl des Simulierten Ablaufs
Für die Aufgabe 2 gibt es unterschiedliche Test-Abläufe. Eine kurze Version (die standardmäßig genutzt wird) 
und eine lange Version.

In der kurzen Version wird ein Werkstück mit Metall nach oben nach 5 Sekunden auf das Laufband gelegt.
Nach 15 Sekunden wird dieses entfernt, egal wo es zu diesem Zeitpunkt liegt.
Nach 16 Sekunden wird ein hohes Werkstück ohne Loch aufgelegt. Dieses wird nach 26 Sekunden entfernt.
(Alle Zeiten ab Start der Simulation)

In der langen Version werden alle Arten von Werkstücken auf das Band gelegt. Diese Simulation hat das letzte Ereignis bei Sekunde 272. Sie Läuft also 4 Minuten und 32 Sekunden. 

Zum ersten Testen des Automaten reicht der kurze Durchlauf. Für einen ausführlichen Test kann man dann den langen Ablauf wählen.
Dazu muss in der CMakeLists.txt in dem diesem Ordner (festo) die Zeile 
``` CMake
add_definitions(-DLONGRUN)
```
enthalten sein. 

ACHTUNG: Bei Änderungen in einer CMakeLists.txt muss anschließend ein Reload des CMake Projekts erfolgen.

## Sleep() auf nicht Windows-Systemen
Wer auf einem anderen Betriebssystem als Windows entwickelt, wird in der Regel nicht auf die `windows.h` Library zurückgreifen können und somtit nicht die `Sleep()`-Funktion daraus nutzen können.

Alternativ kann die Funktion 
``` C++
std::this_thread::sleep_for(std::chrono::milliseconds(1000));
```
genutzt werden. Hierzu müssen die Header `thread` und `chrono` eingebunden werden:
``` C++
#include <chrono>
#include <thread>
```

## Anzeigen der simulierten Zeit
Mit dem Befehl 
```CMAKE 
add_definitions(-DSIM_SHOW_TIMESTAMP)
```
in der CMakeLists.txt in diesem Ordner (festo) wird die Anzeige der simulierten Zeit aktiviert.
Die Simulation gibt dann die in ihr vergangene Zeit alle 0,2 Sekunden auf der Konsole aus.

Achtung: Wenn mittels `Sleep()` oder `std::this_thread::sleep_for()` das Programm angehalten wird, vergeht auch in der Simulation keine Zeit.


## Ausgaben der Simulation
Beispiel Ausgabe der Simulation (mit Zeitausgabe):
```
<SIM> Time: 2 s
<SIM> new HCI ACTION: 0xb00
<SIM> Button Start: pressed
<SIM> Belt moves right, fast
<SIM> LED start: on
<SIM> Time: 2.2 s
<SIM> Time: 2.4 s
<SIM> new HCI ACTION: 0xa00
<SIM> Button Start: released
<SIM> Belt stopped
<SIM> LED start: off
<SIM> Time: 2.6 s
<SIM> Time: 2.8 s
```
Alle Ausgaben die die Sumulation tätigt beginnen mit `<SIM>`
### Allgemeine Ausgaben
| Augabe | Bedeutung |
| --- | :--- |
| `<SIM> Time:`| Zeitausgabe. Siehe [Anzeigen der simulierten Zeit](#anzeigen-der-simulierten-zeit).|

### Ausgaben der Sensorik 
Die folgenden Ausgaben geben den Zustand der Sensorik an. Diese wird von der Simulation gesteuert.

| Augabe| Bedeutung|
| ----------------------: | :--- |
|<nobr>`<SIM> new HCI ACTION:`</nobr>|Die vorderen 4 Bit der Hexadezimalzahl (erste Hexziffer nach dem 0x) dahinter Zeigt den Zustand der Taster an.|
|<nobr>`<SIM> Button`</nobr>| Zeigt an, welcher Button gerade zu welchem Zustand gewechselt hat. <br />Z.B: `<SIM> Button Start: pressed` bedeutet, dass der Start Taster gerade gedrückt wurde.<br />`<SIM> Button Start: released`, dass dieser losgelassen wurde. | 
|<nobr>`<SIM> Emergency:`</nobr>| Gibt an, in welchen Zustand der E-Stop gewechselt ist. |
|<nobr>`<SIM> new LBI ACTION: LB `</nobr>|Zeigt die Veränderung der Lichtschranken an. Die Hexadezimalzahl gibt die Bitmaske der Lichtschranke(n) an die verändert wird/werden. Die Zahl dahinter gibt an, ob die Lichtschranke unterbrochen (1) oder geschlossen (0) werden soll. | 

### Ausgabe der Aktorik
Die folgenden Ausgaben geben den Zustand der Aktorik wieder. Diese muss von der selbstgeschriebenen Software angestuert werden.

| Augabe| Bedeutung|
| ---: | :--- |
|<nobr>`<SIM> Belt`</nobr>|Zeigt an, in welchen Zustand das Förderband/der Motor übergegangen ist.|
|<nobr>`<SIM> LED`</nobr>|Zeigt an, welche LED gerade in welchen Zustand gewechselt ist.| 
|`<SIM> Red:` <br /> <nobr>`<SIM> Green:`</nobr> <br /> <nobr>`<SIM> Yellow:`</nobr>| Zeigt an, in welchen Zustand die entsprechende Farbe der Ampel übergegangen ist.
|<nobr>`<SIM> Feeder:`</nobr>|Zeigt an, in welchen Zustand (`commanded open` oder `commanded closed`) die Weiche gewechselt ist. |
|<nobr>`<SIM> Feed Separator`</nobr>|Zeigt an, wohin die Werkstücke in der Weiche sortiert werden.<br />Entweder zur Rutsche (`slide`) oder zum Ende der Anlage (`pass`)|

