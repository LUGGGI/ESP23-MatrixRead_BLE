# GoWannaGo

## How to use

- Download VSCode https://code.visualstudio.com/Download
- Clone repository (must be local drive, no network drive), can youse Open in your IDE...
- Open repository in VSCode, if you cloned with VSCode option should pop up in down right corner
- Install recommended extensions, look for another popup to install those or use the extension menu
- Compile / Upload code with buttons in bottom bar, with the house symbol you can control platformIO

### Upload on multible Controllers

* To upload run upload.bat in _upload, it will upload the file in .pio
  * in .bat file change COM to port where controller is connected
  * to upload other versions change path

### Anleitung für SupperTuxKart

Schnelle grünes Blinken bedeutet --> lange inaktiv --> System geht aus wenn nicht betätigt wird

#### Einschalten

1. Matte/Band muss zum Controller verbunden sein (Matte: rot ist rechts)
2. Beide müssen in Ruhe/Unbelastet sein
3. Einschalten. Beim ersten Mal BT-Geräte mit Windows verbinden
4. Spiel starten "Einzelspieler" --> "Wilber" (färht langsam) --> Zeitrennen --> Strecke (links unten): Nessis Teich

#### Funktionen

Band für bremsen/rückwärts
Matte für Steuerung
Vollgas durch drücken/springen auf linkes Feld in der Matte. 
Nitro-Boost springen auf beide Felder
Adler-Rettung druch drücken/springen auf rechtes Feld in der Matte

                        ->    SuperTux                        https://gamepad-tester.com/
jump beide    ->    Nitro        Gampepad-Taste2        => B1                                            (nitro 1s lang, extra beschleunigen)
jump left     ->    Bremse    Achse 3-                    => Axis 3 toggle 1\<->0            (beschleunigen)
jump right     ->    Retten    Gampepad-Taste5        => B4                                            (Adler = zurück auf die Bahn)

Verlagerung links/rechts => Axis 0 (-0,6..0,6)

**Controllerconfig**:
"SuperTuxKartPortable\\Data\\supertuxkart\\config-0.10\\input.xml"

aus Mail von Lukas

Von: Lukas Beck \<lukas.beck@ditf.de> 
Gesendet: Freitag, 17. Februar 2023 11:59
An: Valérie Bartsch \<Valerie.Bartsch@ditf.de>; Lena Pfeiffer \<lena.pfeiffer@ditf.de>; Sven Kuijpens \<sven.kuijpens@ditf.de>
Cc: Michael Haupt \<Michael.Haupt@ditf.de>; Raphael Wolfer \<Raphael.Wolfer@ditf.de>
Betreff: Re: Go wannago Demonstrator - Anwender Forum

Hallo,

Das Band ist auch bei der derzeitigen Software nicht nötig. Man kann halt dann nicht Bremsen/ Rückwärts fahren, aber es geht auch ohne.

Hier nochmal ne kurze Zusammenfassung der Steuerung.
Man kann durch springen/ erstmaliges auf die Matte treten 3 verschiedene Befehle auslösen. Zu Ausführung dieser Befehle müssen beide Felder unbelastet sein, hierbei reicht auch Springen. Die Befehle werden durch das Landen / treten auf bestimmten Felder bzw. Kombinationen ausgelöst. Die Befehle sind
Linkes Feld    Gas geben, bzw Starten. Erneute Aktivierung stoppt das Auto. 
Rechtes Feld    Zurücksetzten des Fahrzeugs
Beide Felder    Nitro (extra Geschwindigkeit) für eine Sekunde
Hierbei empfehle ich vor Start eines Rennes vor der Matte zu stehen und dann bei start kurz auf das linke Feld zu treten bevor man beide zum Lenken benutzt.

Wichtig ist auch das bei anschalten der Controller die Matten angeschlossen und unbelastet sind da die da kalibriert werden. Dh. sollte die Steuerung abweichen einfach den Kontroller aus und einschalten.

Ich denke das @Patrick auch noch genug Kontroller für 3 Matten hat (wenn man die Bänder nicht mitbenutzt. Sonst liegen in der Werkstatt noch ein paar die aber noch nicht das aktuelle Program haben. In dem fall einfach nochmal Bescheid geben dann kann man das da auch aufspielen.

Gruß

Lukas
\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_
