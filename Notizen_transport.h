Absolut – das ist ein durchdachtes, elegantes Prinzip und voll umsetzbar auf dem ESP32.
Was du beschreibst, ist eine adaptive Durchlaufsteuerung, bei der:


---

✅ Das Grundprinzip:

> Die Maschine zählt keine Filme oder Leader, sondern reagiert rein auf Sensorzustände + Zeitfenster.



Das funktioniert perfekt mit einer pipeline-artigen Steuerung:


---

🧠 Zustandslogik pro Bad (entwicklerfixiert):

Entwicklerbad:

Wenn Sensor vorn (Leader/Film erkannt):

Start Timer / Schrittmotorlauf (je nach Filmtyp: 36exp ≈ 1,8 m → z. B. 9000 Schritte)

Wenn Motor bereits läuft: Verlängere Laufzeit um Delta


Wenn Sensor hinten (Filmende) erkannt:

Stoppe Motor, wenn kein neuer Film folgt



Fixierer:

Wenn Sensor erkennt, dass Film kommt → Motor einschalten

Bleibt an, bis Film hinten erkannt


usw.


---

✅ Filmtyp als Parameter:

Der Filmtyp (120, 135-24, 135-36) wird vorher eingegeben oder erkannt (z. B. DX-Code)
→ daraus ergibt sich:

Filmtyp	Länge ca.	Schritte bei 0.2 mm/Step

135-24	~1.3 m	~6500 Schritte
135-36	~1.8 m	~9000 Schritte
120	~80–90 cm	~4500 Schritte


Das System kennt den „Motorlaufbedarf“ pro Film, verlängert oder startet bei jedem Erkennungssignal entsprechend angepasst.


---

✅ Vorteile deines Konzepts:

Unbegrenzte Leader nacheinander möglich (solange Chemie reicht)

ESP32 reagiert nur auf Sensoren und Filmtyp, nicht auf „Film-Nr.“

Keine Gefahr der Überladung eines Bades

Kein „Leerlauf“, wenn kein zweiter Film kommt

Extrem modular für verschiedene Längen/Typen



---

✅ Umsetzung:

Maschinenintern:

Für jedes Bad: ein currentMotorRuntime (Millis oder Steps)

Sensor vorne → +X Sekunden/Steps zur remainingRuntime

Im Loop: falls remainingRuntime > 0 → Motor AN

Sensor hinten → Motor AUS, außer remainingRuntime > 0



---

Willst du diese adaptive Steuerung in transport.h als Nächstes konkret integriert haben, oder lieber in ein separates Modul wie filmcontroller.h auslagern?
(Das könnte schöner trennbar sein nach „pro Bad“ Logik.)

